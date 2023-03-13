#include "renderwindow.h"
#include <QTimer>
#include <QMatrix4x4>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLDebugLogger>
#include <QKeyEvent>
#include <QStatusBar>
#include <QDebug>

#include <string>

#include "shader.h"
#include "mainwindow.h"
#include "logger.h"



#include "xyz.h"
#include "trianglesurface.h"
#include "surfaceo1.h"
#include "curveo1.h"
#include "octahedron.h"
#include "tetraeder.h"
#include "disc.h"
#include "parabel.h"
#include "landscape.h"
#include "house.h"
#include "movers.h"
#include "gameobject.h"
#include "player.h"
#include "pickups.h"
#include "door.h"
#include "visualobjectcomponent.h"
#include "physicscomponent.h"
#include "scene.h"
#include "basicmesh.h"
#include "npco2.h"
#include "neuralnetwork.h"
#include "texture.h"


RenderWindow* RenderWindow::instance;


RenderWindow::RenderWindow(const QSurfaceFormat &format, MainWindow *mainWindow)
    : mContext(nullptr), mInitialized(false), mMainWindow(mainWindow)

{

    if (instance == nullptr)
    {
        instance = this;
    }

    //This is sent to QWindow:
    setSurfaceType(QWindow::OpenGLSurface);
    setFormat(format);
    //Make the OpenGL context
    mContext = new QOpenGLContext(this);
    //Give the context the wanted OpenGL format (v4.1 Core)
    mContext->setFormat(requestedFormat());
    if (!mContext->create()) {
        delete mContext;
        mContext = nullptr;
        qDebug() << "Context could not be made - quitting this application";
    }

    //Make the gameloop timer:
    mRenderTimer = new QTimer(this);



    // all hard coded objects

    player = new Player();


    scene1 = new Scene();
    scene2 = new Scene();
    scene3 = new Scene();
    neuralNetworkScene = new Scene();
    neuralNetworkScene->addObject(new NeuralNetwork(), "Network");

    // Add objects to scenes
    scene1->addObject(new BasicMesh(new XYZ(), "XYZ"), "XYZ");
    scene2->addObject(new BasicMesh(new XYZ(), "XYZ"), "XYZ");
    scene3->addObject(new BasicMesh(new XYZ(), "XYZ"), "XYZ");


    neuralNetworkScene->addObject(new BasicMesh(new XYZ(), "XYZ"), "XYZ");



    BasicMesh* TextureSurface = new BasicMesh(new TriangleSurface(), "TextureSurface", "TextureShader");
    TextureSurface->Mesh->setTexture(new Texture("../3Dprog22/image.png", TextureSurface->Mesh));
    neuralNetworkScene->addObject(TextureSurface, "TextureSurface");
    neuralNetworkScene->getObject("TextureSurface")->move(QVector3D(5,0,0));
    neuralNetworkScene->getObject("TextureSurface")->rotate(90,QVector3D(0,1,0));
    neuralNetworkScene->getObject("TextureSurface")->rotate(270,QVector3D(0,0,1));
    neuralNetworkScene->getObject("TextureSurface")->rotate(180,QVector3D(0,1,0));
    neuralNetworkScene->getObject("TextureSurface")->scale(3);

    scene1->addObject(player, "Player");
    scene1->addObject(new BasicMesh(new Landscape(QVector2D(-10,-10), QVector2D(10,10)), "Landscape"), "Landscape");
    GameObject* house = scene1->addObject(new BasicMesh(new House(), "House"), "House");
    scene1->addObject(new NPCO2(), "NPC");
    scene1->addObject(new BasicMesh(new Parabel(), "Parabel"), "Parabel");
    scene1->addObject(new Door(), "Door");
    scene1->getCamera()->setFollowGameObject(player);

    for (int i{}; i < 10; i++)
    {

        GameObject* pickup = scene1->addObject(new Pickups(), "Pickup" + std::to_string(i));

        float angle = std::rand() % 361;
        float radians = angle * (M_PI / 180.f);
        float magnitude = (float)(std::rand() % 100) / 20.f;

        magnitude += 5;

        QVector3D randomPos = QVector3D();
        randomPos.setX(cos(radians));
        randomPos.setY(sin(radians));
        randomPos *= magnitude;

        pickup->setPosition(randomPos);
    }

    scene2->addObject(new BasicMesh(new Landscape(QVector2D(-10,-10), QVector2D(10,10)), "Landscape"), "Landscape");
    scene2->getCamera()->setFollowGameObject(player);

    GameObject* wall1 = scene2->addObject(new BasicMesh(new Cube(), "Wall1"), "Wall1");
    GameObject* wall2 = scene2->addObject(new BasicMesh(new Cube(), "Wall2"), "Wall2");
    GameObject* wall3 = scene2->addObject(new BasicMesh(new Cube(), "Wall3"), "Wall3");
    GameObject* wall4 = scene2->addObject(new BasicMesh(new Cube(), "Wall4"), "Wall4");

    wall1->setPosition(0,10,0);
    wall1->scale(QVector3D(10,0.1f,10));

    wall2->setPosition(0,-10,0);
    wall2->scale(QVector3D(10,0.1f,10));

    wall3->setPosition(10,0,0);
    wall3->scale(QVector3D(0.1f,10,10));

    wall4->setPosition(-10,0,0);
    wall4->scale(QVector3D(0.1f,10,10));


    for (int i{}; i < 3; i++)
    {
        scene3->addObject(new Movers(), "Mover" + std::to_string(i));
    }
    scene3->addObject(new Movers(QVector3D(0,0,0)), "Sun");


    house->setPosition(QVector3D(0,-10,3));
    house->rotate(180,QVector3D(0,0,1));
    house->scale(3);


    currentScene = neuralNetworkScene;

}

RenderWindow::~RenderWindow()
{

}
// Sets up the general OpenGL stuff and the buffers needed to render a triangle
void RenderWindow::init()
{
    //Get the instance of the utility Output logger
    //Have to do this, else program will crash (or you have to put in nullptr tests...)
    mLogger = Logger::getInstance();

    //Connect the gameloop timer to the render function:
    //This makes our render loop
    connect(mRenderTimer, SIGNAL(timeout()), this, SLOT(render()));
    //********************** General OpenGL stuff **********************

    //The OpenGL context has to be set.
    //The context belongs to the instanse of this class!
    if (!mContext->makeCurrent(this)) {
        mLogger->logText("makeCurrent() failed", LogType::REALERROR);
        return;
    }

    //just to make sure we don't init several times
    //used in exposeEvent()
    if (!mInitialized)
        mInitialized = true;

    //must call this to use OpenGL functions
    initializeOpenGLFunctions();

    //Print render version info (what GPU is used):
    //Nice to see if you use the Intel GPU or the dedicated GPU on your laptop
    // - can be deleted
    mLogger->logText("The active GPU and API:", LogType::HIGHLIGHT);
    std::string tempString;
    tempString += std::string("  Vendor: ") + std::string((char*)glGetString(GL_VENDOR)) + "\n" +
            std::string("  Renderer: ") + std::string((char*)glGetString(GL_RENDERER)) + "\n" +
            std::string("  Version: ") + std::string((char*)glGetString(GL_VERSION));
    mLogger->logText(tempString);

    //Start the Qt OpenGL debugger
    //Really helpfull when doing OpenGL
    //Supported on most Windows machines - at least with NVidia GPUs
    //reverts to plain glGetError() on Mac and other unsupported PCs
    // - can be deleted
    startOpenGLDebugger();

    //general OpenGL stuff:
    glEnable(GL_DEPTH_TEST);            //enables depth sorting - must then use GL_DEPTH_BUFFER_BIT in glClear
    //    glEnable(GL_CULL_FACE);       //draws only front side of models - usually what you want - test it out!
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);    //gray color used in glClear GL_COLOR_BUFFER_BIT





    scene1->init();
    scene2->init();
    scene3->init();
    neuralNetworkScene->init();

    scene3->getCamera()->lookAt(QVector3D(50,0,50), QVector3D(0,0,0), QVector3D(0,0,1));
    neuralNetworkScene->getCamera()->lookAt(QVector3D(15,0,0), QVector3D(0,0,0), QVector3D(0,0,1));

    GameObject* sun = scene3->getObject("Sun");
    sun->getPhysicsComponent()->setUsingGravitationalAttraction(false);
    sun->getPhysicsComponent()->setVelocity(QVector3D(0,0,0));
    sun->getPhysicsComponent()->setMass(500);
    sun->transform->scale(2);

    glBindVertexArray(0);       //unbinds any VertexArray - good practice
}

// Called each frame - doing the rendering!!!
void RenderWindow::render()
{

    mContext->makeCurrent(this);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    input();
    if (currentScene != nullptr)
    {
        currentScene->update();
    }

    calculateFramerate();
    mTimeStart.restart();

    mContext->swapBuffers(this);

}



void RenderWindow::input()
{
    // Camera
    if (Keymap[Qt::Key_W] == true)
    {
        currentScene->getCamera()->translate(0.1f,0,0);
    }
    if (Keymap[Qt::Key_S] == true)
    {
        currentScene->getCamera()->translate(-0.1f,0,0);
    }
    if (Keymap[Qt::Key_A] == true)
    {
        currentScene->getCamera()->translate(0,-0.1f,0);
    }
    if (Keymap[Qt::Key_D] == true)
    {
        currentScene->getCamera()->translate(0,0.1f,0);
    }
    if (Keymap[Qt::Key_R] == true)
    {
        currentScene->getCamera()->translate(0,0,0.1f);
    }
    if (Keymap[Qt::Key_F] == true)
    {
        currentScene->getCamera()->translate(0,0,-0.1f);
    }
    if (Keymap[Qt::Key_Z] == true)
    {

    }
    if (Keymap[Qt::Key_X] == true)
    {

    }



    if (Keymap[Qt::Key_Up] == true)
    {

    }
    if (Keymap[Qt::Key_Down] == true)
    {

    }
    if (Keymap[Qt::Key_Right] == true)
    {

    }
    if (Keymap[Qt::Key_Left] == true)
    {

    }

    if (Keymap[Qt::Key_1] == true)
    {
        changeScene(1);
    }
    if (Keymap[Qt::Key_2] == true)
    {
        changeScene(2);
    }
    if(Keymap[Qt::Key_3])
    {
        changeScene(3);
    }


}



//This function is called from Qt when window is exposed (shown)
// and when it is resized
//exposeEvent is a overridden function from QWindow that we inherit from
void RenderWindow::exposeEvent(QExposeEvent *)
{
    //if not already initialized - run init() function - happens on program start up
    if (!mInitialized)
        init();

    //This is just to support modern screens with "double" pixels (Macs and some 4k Windows laptops)
    const qreal retinaScale = devicePixelRatio();

    //Set viewport width and height to the size of the QWindow we have set up for OpenGL
    glViewport(0, 0, static_cast<GLint>(width() * retinaScale), static_cast<GLint>(height() * retinaScale));

    //If the window actually is exposed to the screen we start the main loop
    //isExposed() is a function in QWindow
    if (isExposed())
    {
        //This timer runs the actual MainLoop
        //16 means 16ms = 60 Frames pr second (should be 16.6666666 to be exact...)
        mRenderTimer->start(16);
        mTimeStart.start();
    }
}


void RenderWindow::changeScene(int scene)
{
    switch(scene)
    {
    case 1:
        currentScene = scene1;
        break;
    case 2:
        currentScene = scene2;
        break;
    case 3:
        currentScene = scene3;
        break;
    default:
        break;
    }

}

//The way this function is set up is that we start the clock before doing the draw call,
// and check the time right after it is finished (done in the render function)
//This will approximate what framerate we COULD have.
//The actual frame rate on your monitor is limited by the vsync and is probably 60Hz
void RenderWindow::calculateFramerate()
{
    long nsecElapsed = mTimeStart.nsecsElapsed();
    static int frameCount{0};                       //counting actual frames for a quick "timer" for the statusbar

    if (mMainWindow)            //if no mainWindow, something is really wrong...
    {
        ++frameCount;
        if (frameCount > 30)    //once pr 30 frames = update the message == twice pr second (on a 60Hz monitor)
        {
            //showing some statistics in status bar
            mMainWindow->statusBar()->showMessage(" Time pr FrameDraw: " +
                                                  QString::number(nsecElapsed/1000000.f, 'g', 4) + " ms  |  " +
                                                  "FPS (approximated): " + QString::number(1E9 / nsecElapsed, 'g', 7));
            frameCount = 0;     //reset to show a new message in 30 frames
        }
    }
}

//Uses QOpenGLDebugLogger if this is present
//Reverts to glGetError() if not
void RenderWindow::checkForGLerrors()
{
    if(mOpenGLDebugLogger)  //if our machine got this class to work
    {
        const QList<QOpenGLDebugMessage> messages = mOpenGLDebugLogger->loggedMessages();
        for (const QOpenGLDebugMessage &message : messages)
        {
            if (!(message.type() == message.OtherType)) // get rid of uninteresting "object ...
                                                        // will use VIDEO memory as the source for
                                                        // buffer object operations"
                // valid error message:
                mLogger->logText(message.message().toStdString(), LogType::REALERROR);
        }
    }
    else
    {
        GLenum err = GL_NO_ERROR;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            mLogger->logText("glGetError returns " + std::to_string(err), LogType::REALERROR);
            switch (err) {
            case 1280:
                mLogger->logText("GL_INVALID_ENUM - Given when an enumeration parameter is not a "
                                "legal enumeration for that function.");
                break;
            case 1281:
                mLogger->logText("GL_INVALID_VALUE - Given when a value parameter is not a legal "
                                "value for that function.");
                break;
            case 1282:
                mLogger->logText("GL_INVALID_OPERATION - Given when the set of state for a command "
                                "is not legal for the parameters given to that command. "
                                "It is also given for commands where combinations of parameters "
                                "define what the legal parameters are.");
                break;
            }
        }
    }
}

//Tries to start the extended OpenGL debugger that comes with Qt
//Usually works on Windows machines, but not on Mac...
void RenderWindow::startOpenGLDebugger()
{
    QOpenGLContext * temp = this->context();
    if (temp)
    {
        QSurfaceFormat format = temp->format();
        if (! format.testOption(QSurfaceFormat::DebugContext))
            mLogger->logText("This system can not use QOpenGLDebugLogger, so we revert to glGetError()",
                             LogType::HIGHLIGHT);

        if(temp->hasExtension(QByteArrayLiteral("GL_KHR_debug")))
        {
            mLogger->logText("This system can log extended OpenGL errors", LogType::HIGHLIGHT);
            mOpenGLDebugLogger = new QOpenGLDebugLogger(this);
            if (mOpenGLDebugLogger->initialize()) // initializes in the current context
                mLogger->logText("Started Qt OpenGL debug logger");
        }
    }


}

void RenderWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MouseButton(1))
    {
        Keymap[Qt::MouseButton(1)] = true;
    }

}

void RenderWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MouseButton(1))
    {
        Keymap[Qt::MouseButton(1)] = false;
    }
}

void RenderWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (Keymap[Qt::MouseButton(1)] == true)
    {
        float xDelta = event->pos().x() - mousePos.x();
        xDelta /= 10;

        float yDelta = mousePos.y() - event->pos().y();
        yDelta /= 10;

        currentScene->getCamera()->rotate(-yDelta, -xDelta, 0);
    }

    mousePos = QVector2D(event->pos().x(), event->pos().y());

}

//Event sent from Qt when program receives a keyPress
// NB - see renderwindow.h for signatures on keyRelease and mouse input
void RenderWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        mMainWindow->close();       //Shuts down the whole program
    }

    //You get the keyboard input like this
//    if(event->key() == Qt::Key_A)
//    {
//        mMainWindow->statusBar()->showMessage(" AAAA");
//    }
//    if(event->key() == Qt::Key_S)
//    {
//        mMainWindow->statusBar()->showMessage(" SSSS");
//    }

    if(event->key() == Qt::Key_W)
    {
        Keymap[Qt::Key_W] = true;
    }
    if(event->key() == Qt::Key_S)
    {
        Keymap[Qt::Key_S] = true;
    }
    if(event->key() == Qt::Key_A)
    {
        Keymap[Qt::Key_A] = true;
    }
    if(event->key() == Qt::Key_D)
    {
        Keymap[Qt::Key_D] = true;
    }

    if(event->key() == Qt::Key_Z)
    {
        Keymap[Qt::Key_Z] = true;
    }
    if(event->key() == Qt::Key_X)
    {
        Keymap[Qt::Key_X] = true;
    }
    if(event->key() == Qt::Key_R)
    {
        Keymap[Qt::Key_R] = true;
    }
    if(event->key() == Qt::Key_F)
    {
        Keymap[Qt::Key_F] = true;
    }   
    if(event->key() == Qt::Key_E)
    {
        Keymap[Qt::Key_E] = true;
    }
    if(event->key() == Qt::Key_Q)
    {
        Keymap[Qt::Key_Q] = true;
    }

    if(event->key() == Qt::Key_1)
    {
        Keymap[Qt::Key_1] = true;
    }
    if(event->key() == Qt::Key_2)
    {
        Keymap[Qt::Key_2] = true;
    }
    if(event->key() == Qt::Key_3)
    {
        Keymap[Qt::Key_3] = true;
    }
    if(event->key() == Qt::Key_4)
    {
        Keymap[Qt::Key_4] = true;
    }
    if(event->key() == Qt::Key_5)
    {
        Keymap[Qt::Key_5] = true;
    }
    if(event->key() == Qt::Key_6)
    {
        Keymap[Qt::Key_6] = true;
    }


    if(event->key() == Qt::Key_Up)
    {
        Keymap[Qt::Key_Up] = true;
    }
    if(event->key() == Qt::Key_Down)
    {
        Keymap[Qt::Key_Down] = true;
    }
    if(event->key() == Qt::Key_Right)
    {
        Keymap[Qt::Key_Right] = true;
    }
    if(event->key() == Qt::Key_Left)
    {
        Keymap[Qt::Key_Left] = true;
    }

}

 void RenderWindow::keyReleaseEvent(QKeyEvent *event)
 {
     if(event->key() == Qt::Key_W)
     {
         Keymap[Qt::Key_W] = false;
     }
     if(event->key() == Qt::Key_S)
     {
         Keymap[Qt::Key_S] = false;
     }
     if(event->key() == Qt::Key_A)
     {
         Keymap[Qt::Key_A] = false;
     }
     if(event->key() == Qt::Key_D)
     {
         Keymap[Qt::Key_D] = false;
     }

     if(event->key() == Qt::Key_Z)
     {
         Keymap[Qt::Key_Z] = false;
     }
     if(event->key() == Qt::Key_X)
     {
         Keymap[Qt::Key_X] = false;
     }
     if(event->key() == Qt::Key_1)
     {
         Keymap[Qt::Key_1] = false;
     }
     if(event->key() == Qt::Key_2)
     {
         Keymap[Qt::Key_2] = false;
     }
     if(event->key() == Qt::Key_3)
     {
         Keymap[Qt::Key_3] = false;
     }
     if(event->key() == Qt::Key_4)
     {
         Keymap[Qt::Key_4] = false;
     }
     if(event->key() == Qt::Key_5)
     {
         Keymap[Qt::Key_5] = false;
     }
     if(event->key() == Qt::Key_6)
     {
         Keymap[Qt::Key_6] = false;
     }
     if(event->key() == Qt::Key_R)
     {
         Keymap[Qt::Key_R] = false;
     }
     if(event->key() == Qt::Key_F)
     {
         Keymap[Qt::Key_F] = false;
     }
     if(event->key() == Qt::Key_E)
     {
         Keymap[Qt::Key_E] = false;
     }
     if(event->key() == Qt::Key_Q)
     {
         Keymap[Qt::Key_Q] = false;
     }


     if(event->key() == Qt::Key_Up)
     {
         Keymap[Qt::Key_Up] = false;
     }
     if(event->key() == Qt::Key_Down)
     {
         Keymap[Qt::Key_Down] = false;
     }
     if(event->key() == Qt::Key_Right)
     {
         Keymap[Qt::Key_Right] = false;
     }
     if(event->key() == Qt::Key_Left)
     {
         Keymap[Qt::Key_Left] = false;
     }
 }

 void RenderWindow::resizeEvent(QResizeEvent *)
 {
    scene1->refreshCamera();
    scene2->refreshCamera();
    scene3->refreshCamera();
    neuralNetworkScene->refreshCamera();
 }

