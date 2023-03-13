#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "gameobject.h"
class Neuron;
class VisualObjectComponent;
class Line;

struct Point
{
    Point(QVector2D p)
        : pos(p)
    {
        if (pos.y() > f(pos.x()))
        {
            target = -1;
        }
        else
        {
            target = 1;
        }
        bias = 1;
    }

    float f(float x) { return (-1.f * (1.f/3.f)*x) - 0; }

    float x() { return pos.x(); }
    float y() { return pos.y(); }

    std::vector<float> inputs() { std::vector<float> i; i.push_back(x()); i.push_back(y()); i.push_back(bias);return i; }
    int target;
    QVector2D pos;
    float bias;
};

class NeuralNetwork : public GameObject
{
public:
    NeuralNetwork();
    ~NeuralNetwork() override;

    VisualObjectComponent* mLine;
    VisualObjectComponent* correctLine;

    void awake() override;
    void update(float deltaTime) override;
    float guessY(float x);
private:
    std::vector<Point> points;
    std::vector<Neuron*> neurons;

    Neuron* brain;
    std::vector<VisualObjectComponent*> VisualObjects;

    int size;
    float timer;
    float deltaTimer;



};

#endif // NEURALNETWORK_H
