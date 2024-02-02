#pragma once
//#include "pch.h"
#include "Matrix.h"
#include <vector>
#include "Neuron.h"
#include "Layer.h"

using namespace std;
class __declspec(dllexport) NeuralNetwork {
public:
    void setCurrentInput(vector<double> input);
    NeuralNetwork(vector<int> topology);




private:
    vector<int> topology;
    vector<Layer *> layers;
    vector<Matrix *> weightMatrices;
    int topologySize;
    vector<double> input;
};
