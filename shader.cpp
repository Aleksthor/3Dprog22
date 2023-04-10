#include "shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "material.h"
#include "uniforms.h"
#include <QVector3D>

//#include "GL/glew.h" - using QOpenGLFunctions instead

#include "logger.h" //For our utility Logger class

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath)
{
    initializeOpenGLFunctions();    //must do this to get access to OpenGL functions in QOpenGLFunctions

    //Get the instance of the Output logger
    //Have to do this, else program will crash (or you have to put in nullptr tests...)
    mLogger = Logger::getInstance();

    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // Open files and check for errors
    vShaderFile.open( vertexPath );
    if(!vShaderFile)
        mLogger->logText("ERROR SHADER FILE " + std::string(vertexPath) + " NOT SUCCESFULLY READ", LogType::REALERROR);
    fShaderFile.open( fragmentPath );
    if(!fShaderFile)
        mLogger->logText("ERROR SHADER FILE " + std::string(fragmentPath) + " NOT SUCCESFULLY READ", LogType::REALERROR);
    std::stringstream vShaderStream, fShaderStream;
    // Read file's buffer contents into streams
    vShaderStream << vShaderFile.rdbuf( );
    fShaderStream << fShaderFile.rdbuf( );
    // close file handlers
    vShaderFile.close( );
    fShaderFile.close( );
    // Convert stream into string
    vertexCode = vShaderStream.str( );
    fragmentCode = fShaderStream.str( );

    const GLchar *vShaderCode = vertexCode.c_str( );
    const GLchar *fShaderCode = fragmentCode.c_str( );

    // 2. Compile shaders
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];
    // Vertex Shader
    vertex = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertex, 1, &vShaderCode, nullptr );
    glCompileShader( vertex );
    // Print compile errors if any
    glGetShaderiv( vertex, GL_COMPILE_STATUS, &success );
    if ( !success )
    {
        glGetShaderInfoLog( vertex, 512, nullptr, infoLog );
        mLogger->logText("ERROR SHADER VERTEX " + std::string(vertexPath) +
                         " COMPILATION_FAILED\n" + infoLog, LogType::REALERROR);
    }
    // Fragment Shader
    fragment = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragment, 1, &fShaderCode, nullptr );
    glCompileShader( fragment );
    // Print compile errors if any
    glGetShaderiv( fragment, GL_COMPILE_STATUS, &success );
    if ( !success )
    {
        glGetShaderInfoLog( fragment, 512, nullptr, infoLog );
        mLogger->logText("ERROR SHADER VERTEX " + std::string(fragmentPath) +
                         " COMPILATION_FAILED\n" + infoLog, LogType::REALERROR);
    }
    // Shader Program linking
    this->mProgram = glCreateProgram();
    glAttachShader( this->mProgram, vertex );
    glAttachShader( this->mProgram, fragment );
    glLinkProgram( this->mProgram );
    // Print linking errors if any
    glGetProgramiv( this->mProgram, GL_LINK_STATUS, &success );

    //making nice output name for printing:
    std::string shadername{vertexPath};
    shadername.resize(shadername.size()-5); //deleting ".vert"

    if (!success)
    {
        glGetProgramInfoLog( this->mProgram, 512, nullptr, infoLog );
        mLogger->logText("ERROR::SHADER::PROGRAM::LINKING_FAILED\n" +
                          shadername +  "\n   " + infoLog, LogType::REALERROR);
    }
    else
    {
       mLogger->logText("GLSL shader " + shadername + " was successfully compiled");
    }
    // Delete the shaders as they're linked into our program now and no longer needed
    // The shader program is now on the GPU and we reference it by using the mProgram variable
    glDeleteShader( vertex );
    glDeleteShader( fragment );
}

void Shader::use()
{
    glUseProgram( this->mProgram );
}

GLuint Shader::getProgram() const
{
    return this->mProgram;
}


void Shader::setObjectColorUniform(GLint objectLightUniform)
{
    uniform->mObjectColor = objectLightUniform;
}

void Shader::setLightColorUniform(GLint objectLightUniform)
{
    uniform->mLightColor = objectLightUniform;
}

void Shader::setLightPosUniform(GLint lightPosUniform)
{
    uniform->mLightPos = lightPosUniform;
}

void Shader::setObjectColor(QVector3D color)
{
    glUniform3f(uniform->mObjectColor, color.x(),color.y(),color.z());
}

void Shader::setLightColor(QVector3D color)
{
    glUniform3f(uniform->mLightColor, color.x(),color.y(),color.z());
}

void Shader::setLightPos(QVector3D lightPos)
{
    glUniform3f(uniform->mLightPos, lightPos.x(),lightPos.y(),lightPos.z());
}

void Shader::setViewPos(QVector3D viewpos)
{
    glUniform3f(uniform->mViewPos, viewpos.x(),viewpos.y(),viewpos.z());
}

void Shader::uploadMaterial(const Material& material)
{
    glUniform3f(uniform->mObjectColor, material.color.x(),material.color.y(),material.color.z());
    glUniform3f(uniform->mAmbientUniform, material.ambient.x(),material.ambient.y(),material.ambient.z());
    glUniform3f(uniform->mDiffuseUniform, material.diffuse.x(),material.diffuse.y(),material.diffuse.z());
    glUniform3f(uniform->mSpecularUniform, material.specular.x(),material.specular.y(),material.specular.z());
    glUniform1f(uniform->mShininessUniform, material.shininess);
}
