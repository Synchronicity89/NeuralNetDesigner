#pragma once
#include "..\AnnDll\include\NeuralNetwork.hpp"
#include "..\AnnDll\include\Matrix.hpp"

using namespace System;
using namespace System::Collections::Generic;
class __declspec(dllimport) Matrix;
class __declspec(dllimport) NeuralNetwork;
namespace DeepLearning {
	public ref class DeepNetwork
	{
		// TODO: Add your methods for this class here.
public:
		// Function to test adding two numbers
		//string Predict(string pathToWeights, string inputData)
		//{
  //          ANNConfig config;
  //          config.topology = topology;
  //          config.bias = 0.0;
  //          config.learningRate = 0.01;
  //          config.momentum = 0.0;
  //          config.epoch = 1000;
  //          config.hActivation = ANN_ACTIVATION::A_SIGM;
  //          config.oActivation = ANN_ACTIVATION::A_SIGM;
  //          config.cost = ANN_COST::COST_MSE;
  //          config.trainingFile = "training.txt";
  //          config.labelsFile = "labels.txt";
  //          config.weightsFile = "weights.txt";

		//	NeuralNetwork nn(config);
		//	//nn.predict({ 1, 2 });
		//	//return a + b;
  //          string output = "";
  //          return output;
		//}

        List<System::Double>^ LoadWeights(String^ pathToWeights, List<System::Double>^ inputData)
        {
			// instantiate a new neural network with 3 layers
			ANNConfig config;
			config.topology = { 71, 51, 31, 51, 71 };
			config.bias = 1.0;
			config.learningRate = 0.09;
			config.momentum = 1.0;
			config.epoch = 100;
			config.hActivation = /*ANN_ACTIVATION.*/A_SIGM;
			config.oActivation = /*ANN_ACTIVATION.*/A_SIGM;
			config.cost = /*ANN_COST.*/COST_MSE;
			config.trainingFile = "training.txt";
			config.labelsFile = "labels.txt";
			config.weightsFile = "weights.txt";

			
			//config.topology = topology;
			//config.bias = 0.0;
			//config.learningRate = 0.01;
			//config.momentum = 0.0;
			//config.epoch = 1000;
			//config.hActivation = ANN_ACTIVATION::A_SIGM;
			//config.oActivation = ANN_ACTIVATION::A_SIGM;
			//config.cost = ANN_COST::COST_MSE;
			//config.trainingFile = "training.txt";
			//config.labelsFile = "labels.txt";
			//config.weightsFile = "weights.txt"
			List<System::Double>^ input = gcnew List<System::Double>();
			for (int i = 0; i < inputData->Count; i++)
			{
				input->Add(((double)inputData[i]/(double)10.0));
			}
		
			NeuralNetwork nn(config);
			//convert System::String to std::string
			std::string weightsString;
			for (int i = 0; i < pathToWeights->Length; i++)
			{
				weightsString.push_back(static_cast<char>(pathToWeights[i])); // String^ to std::string
			}
			nn.loadWeights(weightsString);
			vector<double> input2;
			for (int i = 0; i < input->Count; i++)
			{
				input2.push_back(input[i]);
			}
			nn.setCurrentInput(input2);
			nn.feedForward();
			//return the output layer of nn as a List<System::UInt64>
			List<System::Double>^ output = gcnew List<System::Double>();
			auto outputLayer = nn.layers[nn.layers.size() - 1];
			for (int i = 0; i < outputLayer->getNeurons().size(); i++)
			{
				output->Add(outputLayer->getNeurons()[i]->getVal()*10.0);
			}
			return output;
		}
		
	};
}
