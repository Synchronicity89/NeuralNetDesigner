#pragma once
#include <iostream>
#include <math.h>
using namespace std;

class Neuron
{
public:
	Neuron(double val);
	void setVal(double v);

	double getVal() { return this->val; }
	double getActivatedVal() { return this->activatedVal; }
	double getDerivedVal() { return this->derivedVal; }

private: 
	double val;
	double activatedVal;
	double derivedVal;
};