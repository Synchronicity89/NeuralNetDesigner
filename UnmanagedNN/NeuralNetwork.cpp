#include "pch.h"
#include "NeuralNetwork.h"
//#include "matrix.h"
//#include "layer.h"

// Constructor for NeuralNetwork class
void NeuralNetwork::setCurrentInput(vector<double> input)
{
	this->input = input;

	for (int i = 0; i < input.size(); i++)
	{
		this->layers.at(0)->setVal(i, input.at(i));
	}
}

NeuralNetwork::NeuralNetwork(vector<int> topology)
{
	this->topology = topology;
	this->topologySize = topology.size();

	// Create layers
	for (int i = 0; i < topologySize; i++) {
		Layer *layer = new Layer(topology.at(i));
		this->layers.push_back(layer);
	}

	// Create weight matrices
	for (int i = 0; i < topology.size() - 1; i++) {
		Matrix *matrix = new Matrix(topology.at(i), topology.at(i + 1), true);

		this->weightMatrices.push_back(matrix);
	}
}
