#include "pch.h"
#include "NeuralNetwork.h"

using namespace std;

void NeuralNetwork::feedForward() {
	for (int i = 0; i < this->layers.size() - 1; i++) {
		Matrix *a = this->layers.at(i)->matrixifyVals();

		if (i != 0)
		{
			a = this->getActivatedNeuronMatrix(i);
		}

		Matrix *b = this->getWeightMatrix(i);
		Matrix *c = (new utils::MultiplyMatrix(a, b))->execute();
		
		for (int c_index = 0; c_index < c->getNumCols(); c_index++) {
			this->setNeuronValue(i + 1, c_index, c->getValue(0, c_index));
		}
	}
}
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

void NeuralNetwork::printToConsole()
{
	for (int i = 0; i < this->layers.size(); i++)
	{
		if (i == 0) {
			Matrix* m = this->layers.at(i)->matrixifyVals();
		}
		else
		{
			Matrix *m = this->layers.at(i)->matrixifyActivatedVals();
		}
	}
}

Matrix* NeuralNetwork::getNeuronMatrix(int layerIndex)
{
	return this->layers.at(layerIndex)->matrixifyVals();
}

Matrix* NeuralNetwork::getActivatedNeuronMatrix(int layerIndex)
{
	return this->layers.at(layerIndex)->matrixifyActivatedVals();
}

Matrix* NeuralNetwork::getDerivedNeuronMatrix(int layerIndex)
{
	return this->layers.at(layerIndex)->matrixifyDerivedVals();
}

Matrix* NeuralNetwork::getWeightMatrix(int layerIndex)
{
	return this->weightMatrices.at(layerIndex);
}
