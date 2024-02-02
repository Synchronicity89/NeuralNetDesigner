#pragma once
//#include "pch.h"
#include "Matrix.h"
#include <vector>
#include "Neuron.h"
#include "Layer.h"
#include "MultiplyMatrix.h"

using namespace std;
class __declspec(dllexport) NeuralNetwork {
public:
    void feedForward();
    void setCurrentInput(vector<double> input);
    NeuralNetwork(vector<int> topology);
	void printToConsole();
    Matrix* getNeuronMatrix(int layerIndex);
    Matrix* getActivatedNeuronMatrix(int layerIndex);
    Matrix* getDerivedNeuronMatrix(int layerIndex);
    Matrix* getWeightMatrix(int layerIndex);
    void setNeuronValue(int indexLayer, int indexNeuron, double val) {
		this->layers.at(indexLayer)->setVal(indexNeuron, val);
    }


private:
    vector<int> topology;
    vector<Layer *> layers;
    vector<Matrix *> weightMatrices;
    int topologySize;
    vector<double> input;
};
