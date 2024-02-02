#include "pch.h"
#include "Neuron.h"

Neuron::Neuron(double val)
{
	this->val = val;
	//this->activatedVal = this->activate();
	//this->derivedVal = this->derive();
}

void Neuron::setVal(double v)
{
	this->val = v;
	//this->activatedVal = this->activate();
	//this->derivedVal = this->derive();
}
