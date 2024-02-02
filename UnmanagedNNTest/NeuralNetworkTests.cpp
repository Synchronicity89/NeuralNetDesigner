#include "pch.h"
#include "CppUnitTest.h"
#include "../UnmanagedNN/Matrix.h"
#include "../UnmanagedNN/NeuralNetwork.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnmanagedNNTest
{
	//TEST_CLASS(NeuralNetworkTests)
	//{
	//public:
	//	TEST_METHOD(FeedForwardTest)
	//	{
	//		// Arrange
	//		std::vector<int> layers = { 2, 3, 1 };
	//		NeuralNetwork neuralNetwork(layers);
	//		Matrix input(2, 1);
	//		input(0, 0) = 0.5;
	//		input(1, 0) = 0.7;

	//		// Act
	//		Matrix output = neuralNetwork.predict(input);

	//		// Assert
	//		Assert::AreEqual(1, output.getRows());
	//		Assert::AreEqual(1, output.getCols());
	//	}


	//	TEST_METHOD(BackwardPropagationTest)
	//	{
	//		// Arrange
	//		std::vector<int> layers = { 2, 3, 1 };
	//		NeuralNetwork neuralNetwork(layers);
	//		Matrix input(2, 1);
	//		input(0, 0) = 0.5;
	//		input(1, 0) = 0.7;
	//		Matrix target(1, 1);
	//		target(0, 0) = 0.8;
	//		double learningRate = 0.1;

	//		// Act
	//		neuralNetwork.forwardPropagation(input);
	//		neuralNetwork.backwardPropagation(target, learningRate);

	//		// Assert
	//		// Check weight gradients
	//		Matrix weightGradient1 = neuralNetwork.weightGradients[0];
	//		Matrix weightGradient2 = neuralNetwork.weightGradients[1];
	//		Assert::AreEqual(3, weightGradient1.getRows());
	//		Assert::AreEqual(2, weightGradient1.getCols());
	//		Assert::AreEqual(1, weightGradient2.getRows());
	//		Assert::AreEqual(3, weightGradient2.getCols());

	//		// Check bias gradients
	//		Matrix biasGradient1 = neuralNetwork.biasGradients[0];
	//		Matrix biasGradient2 = neuralNetwork.biasGradients[1];
	//		Assert::AreEqual(3, biasGradient1.getRows());
	//		Assert::AreEqual(1, biasGradient1.getCols());
	//		Assert::AreEqual(1, biasGradient2.getRows());
	//		Assert::AreEqual(1, biasGradient2.getCols());
	//	}

	//	TEST_METHOD(BackwardPropagationSameLayerSizeTest)
	//	{
	//		// Arrange
	//		std::vector<int> layers = { 2,2, 2 };
	//		NeuralNetwork neuralNetwork(layers);
	//		Matrix input(1, 1);
	//		input(0, 0) = 0.5;
	//		input(1, 0) = 0.7;
	//		Matrix target(1, 1);
	//		target(0, 0) = 0.8;
	//		double learningRate = 0.1;

	//		// Act
	//		neuralNetwork.forwardPropagation(input);
	//		neuralNetwork.backwardPropagation(target, learningRate);

	//		// Assert
	//		// Check weight gradients
	//		Matrix weightGradient1 = neuralNetwork.weightGradients[0];
	//					Matrix weightGradient2 = neuralNetwork.weightGradients[1];
	//		Assert::AreEqual(3, weightGradient1.getRows());
	//		Assert::AreEqual(2, weightGradient1.getCols());
	//		Assert::AreEqual(1, weightGradient2.getRows());
	//		Assert::AreEqual(3, weightGradient2.getCols());

	//		// Check bias gradients
	//		Matrix biasGradient1 = neuralNetwork.biasGradients[0];
	//		Matrix biasGradient2 = neuralNetwork.biasGradients[1];
	//		Assert::AreEqual(3, biasGradient1.getRows());
	//		Assert::AreEqual(1, biasGradient1.getCols());
	//		Assert::AreEqual(1, biasGradient2.getRows());
	//		Assert::AreEqual(1, biasGradient2.getCols());
	//	}

	//	TEST_METHOD(CalculateOutputLayerErrorTest)
	//	{
	//		// Arrange
	//		Matrix output(1, 1);
	//		output(0, 0) = 0.5;
	//		Matrix target(1, 1);
	//		target(0, 0) = 0.7;
	//		NeuralNetwork neuralNetwork({ 2, 3, 1 });

	//		// Act
	//		Matrix error = neuralNetwork.calculateOutputLayerError(target);

	//		// Assert
	//		Assert::AreEqual(1, error.getRows());
	//		Assert::AreEqual(1, error.getCols());
	//		Assert::AreEqual(-0.2, error(0, 0), 0.001);
	//	}

	//	TEST_METHOD(CalculateLayerGradientTest)
	//	{
	//		// Arrange
	//		Matrix error(1, 1);
	//		error(0, 0) = -0.2;
	//		NeuralNetwork neuralNetwork({ 2, 3, 1 });

	//		// Act
	//		Matrix gradient = neuralNetwork.calculateLayerGradient(1, error);

	//		// Assert
	//		Assert::AreEqual(3, gradient.getRows());
	//		Assert::AreEqual(1, gradient.getCols());
	//		Assert::AreEqual(-0.06, gradient(0, 0), 0.001);
	//		Assert::AreEqual(-0.06, gradient(1, 0), 0.001);
	//		Assert::AreEqual(-0.06, gradient(2, 0), 0.001);
	//	}

	//	TEST_METHOD(CalculateErrorForNextLayerTest)
	//	{
	//		// Arrange
	//		Matrix gradient(3, 1);
	//		gradient(0, 0) = -0.06;
	//		gradient(1, 0) = -0.06;
	//		gradient(2, 0) = -0.06;
	//		NeuralNetwork neuralNetwork({ 2, 3, 1 });

	//		// Act
	//		Matrix error = neuralNetwork.calculateErrorForNextLayer(1, gradient);

	//		// Assert
	//		Assert::AreEqual(2, error.getRows());
	//		Assert::AreEqual(1, error.getCols());
	//		Assert::AreEqual(-0.18, error(0, 0), 0.001);
	//		Assert::AreEqual(-0.18, error(1, 0), 0.001);
	//	}
	//	TEST_METHOD(TrainTest)
	//	{
	//		// Arrange
	//		std::vector<int> layers = { 2, 3, 1 };
	//		NeuralNetwork neuralNetwork(layers);
	//		std::vector<Matrix> inputs = { Matrix(2, 1), Matrix(2, 1) };
	//		inputs[0](0, 0) = 0.5;
	//		inputs[0](1, 0) = 0.7;
	//		inputs[1](0, 0) = 0.3;
	//		inputs[1](1, 0) = 0.9;
	//		std::vector<Matrix> outputs = { Matrix(1, 1), Matrix(1, 1) };
	//		outputs[0](0, 0) = 0.8;
	//		outputs[1](0, 0) = 0.2;
	//		double learningRate = 0.1;
	//		int epochs = 10;

	//		// Act
	//		neuralNetwork.train(inputs, outputs, learningRate, epochs);

	//		// Assert
	//		Matrix output1 = neuralNetwork.predict(inputs[0]);
	//		Matrix output2 = neuralNetwork.predict(inputs[1]);
	//		Assert::AreEqual(1, output1.getRows());
	//		Assert::AreEqual(1, output1.getCols());
	//		Assert::AreEqual(1, output2.getRows());
	//		Assert::AreEqual(1, output2.getCols());
	//	}

	//	TEST_METHOD(UpdateWeightsAndBiasesTest)
	//	{
	//		// Arrange
	//		std::vector<int> layers = { 2, 3, 1 };
	//		NeuralNetwork neuralNetwork(layers);
	//		Matrix input(2, 1);
	//		input(0, 0) = 0.5;
	//		input(1, 0) = 0.7;
	//		double learningRate = 0.1;

	//		// Act
	//		neuralNetwork.forwardPropagation(input);
	//		neuralNetwork.backwardPropagation(input, learningRate);
	//		neuralNetwork.updateWeightsAndBiases(learningRate);

	//		// Assert
	//		//Assert::AreEqual({ 3, 3 }, neuralNetwork.weights.size());
	//		//Assert::AreEqual({ 3, 3 }, neuralNetwork.biases.size());
	//	}

	//	TEST_METHOD(ComputeLossTest)
	//	{
	//		// Arrange
	//		Matrix output(1, 1);
	//		output(0, 0) = 0.5;
	//		Matrix target(1, 1);
	//		target(0, 0) = 0.7;
	//		NeuralNetwork neuralNetwork({ 2, 3, 1 });

	//		// Act
	//		double loss = neuralNetwork.computeLoss(output, target);

	//		// Assert
	//		Assert::AreEqual(0.04, loss, 0.001);
	//	}

	//	TEST_METHOD(DerivativeTest)
	//	{
	//		// Arrange
	//		Matrix m(2, 1);
	//		m(0, 0) = 0.5;
	//		m(1, 0) = 0.7;
	//		NeuralNetwork neuralNetwork({ 2, 3, 1 });

	//		// Act
	//		Matrix result = neuralNetwork.derivative(m);

	//		// Assert
	//		Assert::AreEqual(2, result.getRows());
	//		Assert::AreEqual(1, result.getCols());
	//	}

	//	TEST_METHOD(ActivationTest)
	//	{
	//		// Arrange
	//		Matrix m(2, 1);
	//		m(0, 0) = 0.5;
	//		m(1, 0) = 0.7;
	//		NeuralNetwork neuralNetwork({ 2, 3, 1 });

	//		// Act
	//		Matrix result = neuralNetwork.activation(m);

	//		// Assert
	//		Assert::AreEqual(2, result.getRows());
	//		Assert::AreEqual(1, result.getCols());
	//	}

	//	TEST_METHOD(RowsTest)
	//	{
	//		// Arrange
	//		Matrix m(2, 3);
	//		NeuralNetwork neuralNetwork({ 2, 3, 1 });

	//		// Act
	//		int numRows = neuralNetwork.rows(m);

	//		// Assert
	//		Assert::AreEqual(2, numRows);
	//	}


 //       TEST_METHOD(ValidateMatrixSizeTest)
 //       {
 //           // Arrange
 //           std::vector<int> layers1 = { 2, 3, 1 };
 //           std::vector<int> layers2 = { 2, 2, 2 };
 //           std::vector<int> layers3 = { 1, 1, 1 };
 //           NeuralNetwork neuralNetwork1(layers1);
 //           NeuralNetwork neuralNetwork2(layers2);
 //           NeuralNetwork neuralNetwork3(layers3);

 //           // Act & Assert
 //           Assert::ExpectException<std::invalid_argument>([&]() { neuralNetwork1.validateMatrixSize(); });
 //           Assert::ExpectException<std::invalid_argument>([&]() { neuralNetwork2.validateMatrixSize(); });
 //           Assert::ExpectException<std::invalid_argument>([&]() { neuralNetwork3.validateMatrixSize(); });
 //       }
	//};
}