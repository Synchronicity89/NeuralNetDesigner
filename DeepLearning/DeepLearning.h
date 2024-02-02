#pragma once
#include "..\UnmanagedNN\NeuralNetwork.h"
#include "..\UnmanagedNN\Matrix.h"
using namespace System;
class __declspec(dllimport) Matrix;
class __declspec(dllimport) NeuralNetwork;
namespace DeepLearning {
	public ref class Class1
	{
		// TODO: Add your methods for this class here.
public:
		// Function to test adding two numbers
		int Add(int a, int b)
		{
			// instantiate a new neural network with 3 layers
			NeuralNetwork nn({ 2, 2, 2 });
			//nn.predict({ 1, 2 });
			return a + b;

		}

	};
}
