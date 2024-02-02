#pragma once

#include "Neuron.h"
#include "Matrix.h"

using namespace std;
class Layer
{
	public:
	Layer(int size);
	void setVal(int index, double val);
	double getVal(int index);
	int getSize() { return this->size; }
	
	Matrix *matrixify();
private:
	int size;
	vector<Neuron *> neurons;
	Matrix* matrixifyVals();
	Matrix* matrixifyActivatedVals();
	Matrix* matrixifyDerivedVals();
};

