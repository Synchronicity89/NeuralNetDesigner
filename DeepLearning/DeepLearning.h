#pragma once
#include "..\AnnDll\include\NeuralNetwork.hpp"
#include "..\AnnDll\include\Matrix.hpp"
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
            vector<int> topology;
            topology.push_back(3);
            topology.push_back(2);
            topology.push_back(3);

            vector<double> input;
            input.push_back(1.0);
            input.push_back(0.0);
            input.push_back(1.0);
            ANNConfig config;
            config.topology = topology;
            config.bias = 0.0;
            config.learningRate = 0.01;
            config.momentum = 0.0;
            config.epoch = 1000;
            config.hActivation = ANN_ACTIVATION::A_SIGM;
            config.oActivation = ANN_ACTIVATION::A_SIGM;
            config.cost = ANN_COST::COST_MSE;
            config.trainingFile = "training.txt";
            config.labelsFile = "labels.txt";
            config.weightsFile = "weights.txt";

			NeuralNetwork nn(config);
			//nn.predict({ 1, 2 });
			return a + b;

		}

	};
}
