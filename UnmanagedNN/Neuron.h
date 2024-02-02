#pragma once
#include <iostream>
#include <math.h>
using namespace std;

class __declspec(dllexport) Neuron
{
public:
	Neuron(double val);
	void setVal(double v);

	void activate();

	void derive();

	//Getters
	double getVal() { return this->val; }
	double getActivatedVal() { return this->activatedVal; }
	double getDerivedVal() { return this->derivedVal; }

private: 
	double val;
	double activatedVal;
	double derivedVal;
};