#include "pch.h"
#include "Neuron.h"
using namespace std;
Neuron::Neuron(double val)
{
	this->val = val;
	//call activate and derive functions
	this->activate();
	this->derive();
}

void Neuron::setVal(double v)
{
	this->val = v;
	//call activate and derive functions
	this->activate();
	this->derive();
}

void Neuron::activate()
{
	// Fast Sigmoid Function
	this->activatedVal = this->val / (1 + abs(this->val));
}

void Neuron::derive()
{
	this->derivedVal = this->activatedVal * (1 - this->activatedVal);
}
