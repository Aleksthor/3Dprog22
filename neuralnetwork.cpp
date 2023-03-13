#include "neuralnetwork.h"
#include "octahedron.h"
#include "visualobjectcomponent.h"
#include "octahedron.h"
#include "neuron.h"
#include "vertex.h"
#include "line.h"
#include "logger.h"

NeuralNetwork::NeuralNetwork() : GameObject()
{
    size = 200;

    for (int i{}; i < size; i++)
    {
        points.push_back(Point(QVector2D((std::rand() % 20)-10,(std::rand() % 20)-10)));
        neurons.push_back(new Neuron());
        VisualObjects.push_back(new VisualObjectComponent(new Octahedron(3),this,"PlainShader"));
        VisualObjects[i]->getObject()->setPosition(QVector3D(0, points[i].x(), points[i].y()));
        VisualObjects[i]->getObject()->scale(0.25f);
        if (points[i].target == -1)
        {
            //VisualObjects[i]->getObject()->setColor(Color::Red);
        }
        else
        {
            //VisualObjects[i]->getObject()->setColor(Color::Blue);
        }
    }
    brain = new Neuron();
    correctLine = new VisualObjectComponent(new Line(Vertex(QVector3D(0,-10,points[0].f(-10.f)), Color::White),Vertex(QVector3D(0,10,points[0].f(10.f)), Color::White)),this,"PlainShader");
    mLine = new VisualObjectComponent(new Line(Vertex(QVector3D(0,-10,0), Color::Red),Vertex(QVector3D(0,10,0), Color::Red)),this,"PlainShader");

    timer = 0;
    deltaTimer = 0;



}

NeuralNetwork::~NeuralNetwork()
{

}

void NeuralNetwork::awake()
{
    GameObject::awake();


    //BasicMesh* mesh = new BasicMesh(new Octahedron(2), "BasicMesh");

    //getWorld()->Instantiate(new BasicMesh(new Octahedron(2), "BasicMesh"), QVector3D(0,pos[1][0],pos[1][1]), "BasicMesh");

}

void NeuralNetwork::update(float deltaTime)
{
    GameObject::update(deltaTime);
    float delta = deltaTime - deltaTimer;

    timer += delta;
    //Logger::getInstance()->logText(std::to_string(timer));


    for (int i{}; i < size; i++)
    {

        if (brain->guess(points[i].inputs()) == -1)
        {
            VisualObjects[i]->getObject()->setColor(Color::Red);
        }
        else
        {
            VisualObjects[i]->getObject()->setColor(Color::Blue);
        }

        if (timer > 5)
        {
            timer = 4;
            for (int i{}; i < size; i++)
            {
                brain->train(points[i].inputs(), points[i].target);
            }
        }

    }
    Line* line = (Line*)mLine->getObject();
    line->updateLine(QVector3D(0,-10,guessY(-10.f)), QVector3D(0,10,guessY(10.f)));

    deltaTimer = deltaTime;

}


float NeuralNetwork::guessY(float x)
{
    float w0 = brain->weights[0];
    float w1 = brain->weights[1];
    float w2 = brain->weights[2];
    return -(w2/w1) - (w0/w1) * x;
}






