#ifndef NEURON_H
#define NEURON_H
#include <iostream>
#include <vector>
#include <QVector2D>

class Neuron
{
public:
    Neuron()
    {
        for(int i{}; i < 3; i++)
        {
            int r = std::rand() % 2000;
            float random = (float)r / 100.f;
            random -= 1.f;
            weights.push_back(random);
        }
        learningRate = 0.1f;
    }


    float guess(std::vector<float> inputs)
    {
        float sum = 0;
        for (size_t i{}; i < inputs.capacity(); i++)
        {
            sum += inputs[i] * weights[i];
        }

        if (sum >= 0)
        {
            return 1;
        }

        return -1;
    }


    void train(std::vector<float> inputs, float target)
    {
        float g = guess(inputs);
        float error = target - g;

        // Tune the weights
        for (size_t i{}; i < weights.capacity(); i++)
        {
            weights[i] += error * inputs[i] * learningRate;
        }
    }


    float learningRate;
    std::vector<float> weights;
};

#endif // NEURON_H
