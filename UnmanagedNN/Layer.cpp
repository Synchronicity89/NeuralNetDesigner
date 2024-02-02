#include "pch.h"
#include "Layer.h"


Layer::Layer(int size)
{
	this->size = size;
	for (int i = 0; i < size; i++)
	{
		Neuron *n = new Neuron(0.0);
		this->neurons.push_back(n);
	}
}

void Layer::setVal(int index, double val)
{
	this->neurons.at(index)->setVal(val);
}

double Layer::getVal(int index)
{
	return this->neurons.at(index)->getVal();
}

Matrix* Layer::matrixifyVals()
{
	Matrix *m = new Matrix(1, this->neurons.size(), false);
	for (int i = 0; i < this->neurons.size(); i++)
	{
		m->setValue(
			0, 
			i, 
			this->neurons.at(i)->getVal()
		);
	}
	return m;
}

Matrix* Layer::matrixifyActivatedVals()
{
	Matrix *m = new Matrix(1, this->neurons.size(), false);
	for (int i = 0; i < this->neurons.size(); i++)
	{
		m->setValue(
			0, 
			i, 
			this->neurons.at(i)->getActivatedVal()
		);
	}
	return m;
}

Matrix* Layer::matrixifyDerivedVals()
{
	Matrix *m = new Matrix(1, this->neurons.size(), false);
	for (int i = 0; i < this->neurons.size(); i++)
	{
		m->setValue(
			0, 
			i, 
			this->neurons.at(i)->getDerivedVal()
		);
	}
	return m;
}


