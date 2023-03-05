#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QWindow>
#include <QOpenGLFunctions_4_1_Core>
#include <QTimer>
#include <QElapsedTimer>
#include <vector>
#include "visualobject.h"
#include "cube.h"
#include "xyz.h"
#include "camera.h"
#include <unordered_map>



class QOpenGLContext;
class Shader;
class MainWindow;
class Scene;

class Tetraeder;
class GameObject;
class Player;


/// This inherits from QWindow to get access to the Qt functionality and
// OpenGL surface.
// We also inherit from QOpenGLFunctions, to get access to the OpenGL functions
// This is the same as using "glad" and "glw" from general OpenGL tutorials
class RenderWindow : public QWindow, protected QOpenGLFunctions_4_1_Core
{
    Q_OBJECT
public:
    RenderWindow(const QSurfaceFormat &format, MainWindow *mainWindow);
    ~RenderWindow() override;

    static RenderWindow* instance;

    static int* MVPnumber;

    QOpenGLContext *context() { return mContext; }

    void exposeEvent(QExposeEvent *) override;  //gets called when app is shown and resized

    bool mRotate{true};     //Check if triangle should rotate

    inline static std::unordered_map<int,bool> Keymap;

    std::vector<GameObject*> GetAllObjects();
    std::vector<GameObject*> GetColliderObjects(int scene);
    std::vector<GameObject*> GetPhysicsObjects(int scene);

    GLint GetMatrixUniform() { return mMatrixUniform;}
    GLint GetVMatrixUniform() { return mVMatrixUniform;}
    GLint GetPMatrixUniform() { return mPMatrixUniform;}


    void changeScene(int scene);

private slots:
    void render();          //the actual render - function

private:
    void init();            //initialize things we need before rendering
    void input();

    QOpenGLContext *mContext{nullptr};  //Our OpenGL context
    bool mInitialized{false};

    Shader *mShaderProgram{nullptr};    //holds pointer the GLSL shader program


    QVector2D mousePos;

    GLint  mMatrixUniform;                 //OpenGL reference to the Uniform in the shader program
    GLint mPMatrixUniform;
    GLint mVMatrixUniform;

    QTimer *mRenderTimer{nullptr};           //timer that drives the gameloop
    QElapsedTimer mTimeStart;               //time variable that reads the calculated FPS

    MainWindow *mMainWindow{nullptr};        //points back to MainWindow to be able to put info in StatusBar


    Scene* currentScene;

    Scene* scene1;
    Scene* scene2;
    Scene* scene3;
    Player* player;


    class QOpenGLDebugLogger *mOpenGLDebugLogger{nullptr};  //helper class to get some clean debug info from OpenGL
    class Logger *mLogger{nullptr};         //logger - Output Log in the application

    ///Helper function that uses QOpenGLDebugLogger or plain glGetError()
    void checkForGLerrors();

    void calculateFramerate();          //as name says

    ///Starts QOpenGLDebugLogger if possible
    void startOpenGLDebugger();


protected:
    //The QWindow that we inherit from have these functions to capture
    // - mouse and keyboard.
    // Uncomment to use (you also have to make the definitions of
    // these functions in the cpp-file to use them of course!)
    //
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;              //the only one we use now
    void keyReleaseEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *) override;
    //    void wheelEvent(QWheelEvent *event) override{}
};

#endif // RENDERWINDOW_H
