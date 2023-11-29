#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <cmath>
#include <QProgressBar>
#include <QFile>
#include <QDebug>

double sigmoid(double x)
{
    return 1.0f / (1.0f + std::pow(2.718, -x));
}

double calc(double *inputs, double *weights, double bias, int size)
{
    double sum = 0.0f;
    for (int connect = 0; connect < size; connect++) sum += inputs[connect] * weights[connect];
    sum += bias;
    return sigmoid(sum);
}

 void calcs(bool **pixels, QProgressBar *pBar, double **weights1, double **weights2, double **weights3, double *bias)
{
    double inputs[784];
    double hiddens[200];
    double hiddens2[100];
    double outputs[10];

    for (int hor = 0; hor < 28; ++hor)
    {
        for (int ver = 0; ver < 28; ++ver)
        {
            pixels[ver][hor] ? inputs[ver+28*hor] = 0.5f : inputs[ver+28*hor] = 0.0f;
        }
    }

    double sum = 0.0f;
    //forwardprop
    for (int neuron = 0; neuron < 200; neuron++) hiddens[neuron] = calc(inputs, weights1[neuron], bias[0], 784);
    for (int neuron = 0; neuron < 100; neuron++) hiddens2[neuron] = calc(hiddens, weights2[neuron], bias[1], 200);
    for (int neuron = 0; neuron < 10; neuron++)
    {
        outputs[neuron] = calc(hiddens2, weights3[neuron], bias[2], 100);
        sum += outputs[neuron];
        qDebug() << outputs[neuron] << '\n';
    }

    for (int i = 0; i < 10; i++) pBar[i].setValue(100*(outputs[i]/sum));
}


#endif // NEURALNETWORK_H
