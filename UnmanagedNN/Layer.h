#pragma once

#include "Neuron.h"
#include "Matrix.h"

using namespace std;
class __declspec(dllexport) Layer
{
	public:
	Layer(int size);
	void setVal(int index, double val);
	double getVal(int index);
	int getSize() { return this->size; }
	
	Matrix* matrixifyVals();
	Matrix* matrixifyActivatedVals();
	Matrix* matrixifyDerivedVals();

	vector<Neuron *> getNeurons() { return this->neurons; }
	void setNeurons(vector<Neuron *> neurons) { this->neurons = neurons; }
private:
	int size;
	vector<Neuron *> neurons;
};

