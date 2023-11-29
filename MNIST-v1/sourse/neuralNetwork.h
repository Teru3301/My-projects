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










/*
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>

double sigmoid(double x)
{
    return 1.0f / (1.0f + std::pow(2.718, -x));
}
double derivate(double x)
{
    if (x * (1.0f - x) == 0) std::cout << "!!!!!!!!!!\n";
    return x * (1.0f - x);
}

double calc(std::vector<double> inputs, std::vector<double> weights)
{
    double sum = 0.0f;
    for (int connect = 0; connect < inputs.size(); connect++) sum += inputs[connect] * weights[connect];
    return sigmoid(sum);
}

int main()
{
    const int inp = 784;
    const int hid = 200;
    const int out = 10;

    const double LR = 0.01f;

    std::vector<double> inputs(inp);
    ///std::vector<std::vector<double>> weights1;
    std::vector<double> hiddens(hid);
    ///std::vector<std::vector<double>> weights2;
    std::vector<double> outputs(out);

    //load weights
    std::fstream weights;
    weights.open("weights.txt");
    weights1.resize(hid);
    for (int i = 0; i < hid; i++)
    {
        weights1[i].resize(inp);
        for (int j = 0; j < inp; j++)
        {
            weights >> weights1[i][j];
        }
    }
    weights2.resize(out);
    for (int i = 0; i < out; i++)
    {
        weights2[i].resize(hid);;
        for (int j = 0; j < hid; j++)
        {
            weights >> weights2[i][j];
        }
    }
    weights.close();


    for (int ep = 0; ep < 5000; ep++)
    {
        double* err = new double[out];
        for (int i = 0; i < out; i++) err[i] = 0.0f;

        //load dataset
        int target = 0;
        std::fstream dataset;
        dataset.open("dataset (training).txt");
        while (!dataset.eof())
        {
            for (int i = 0; i < inp; ++i)
            {
                dataset >> inputs[i];
                inputs[i] = inputs[i] / 200000.0f;
            }
            dataset >> target;


            //forwardprop
            for (int neuron = 0; neuron < hid; neuron++) hiddens[neuron] = calc(inputs, weights1[neuron]);
            for (int neuron = 0; neuron < out; neuron++) outputs[neuron] = calc(hiddens, weights2[neuron]);


            //backprop
            std::vector<double> outErrors(out);
            std::vector<double> hidErrors(hid);

            //outputs errors
            for (int neuron = 0; neuron < out; neuron++) outErrors[neuron] = outputs[neuron] * derivate(outputs[neuron]);
            outErrors[target] = (outputs[target] - 1.0f) * derivate(outputs[target]);

            //hidden errors
            for (int neuron = 0; neuron < hid; neuron++)
            {
                for (int con = 0; con < out; con++)
                {
                    hidErrors[neuron] += outErrors[con] * weights2[con][neuron];
                }
                hidErrors[neuron] *= derivate(hiddens[neuron]);
            }

            //weights
            for (int neuron = 0; neuron < out; neuron++)
            {
                for (int connect = 0; connect < hid; connect++)
                {
                    weights2[neuron][connect] -= (hiddens[connect] * outErrors[neuron] * derivate(outputs[neuron])) * LR;
                }
            }
            for (int neuron = 0; neuron < hid; neuron++)
            {
                for (int connect = 0; connect < inp; connect++)
                {
                    weights1[neuron][connect] -= (inputs[connect] * hidErrors[neuron] * derivate(hiddens[neuron])) * LR;
                }
            }

            //statistic
            for (int i = 0; i < out; i++) err[i] += outputs[i];
        }
        dataset.close();


        std::cout << "save ";
        //save
        weights.open("weights.txt");
        for (int neuron = 0; neuron < hid; neuron++)
        {
            for (int connect = 0; connect < inp; connect++)
            {
                if (connect % 28 == 0) weights << '\n';
                weights << std::fixed << weights1[neuron][connect] << '\t';
            }
            weights << '\n';
        }
        for (int neuron = 0; neuron < out; neuron++)
        {
            for (int connect = 0; connect < hid; connect++)
            {
                weights << std::fixed << weights2[neuron][connect] << '\t';
            }
            weights << '\n';
        }
        weights.close();



        //statistic
        double totalErr = 0.0f;
        for (int i = 0; i < 10; i++)
        {
            err[i] /= 60000;
            totalErr += err[i];
        }
        std::cout << "epoh " << ep << " is complete! errors: " << std::fixed << std::setprecision(9);
        for (int i = 0; i < 10; i++) std::cout << i << ' ' << err[i] << ' ';
        std::cout << "total " << totalErr << '\n';
    }

    return 0;
}
*/



#endif // NEURALNETWORK_H
