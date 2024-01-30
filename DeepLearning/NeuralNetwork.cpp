#include "pch.h"
#include "NeuralNetwork.h"
#include "matrix.h"
// implement the rows function
int NeuralNetwork::rows(const Matrix& m) {
	return m.getRows();
}

void NeuralNetwork::updateWeightsAndBiases(double learningRate) {
    for (size_t i = 0; i < weights.size(); i++) {
        weights[i] = weights[i] + weightGradients[i] * learningRate;
        biases[i] = biases[i] + biasGradients[i] * learningRate;
    }
}

double NeuralNetwork::computeLoss(const Matrix& output, const Matrix& target) {
    // Mean Squared Error
    double mse = 0.0;
    // loop through rows summing squared error
    for (int i = 0; i < output.getRows(); ++i) {
        mse += std::pow(output(i, 0) - target(i, 0), 2);
    }

    return mse / output.getRows();
}

void NeuralNetwork::forwardPropagation(const Matrix& input)
{
	// Set first layer to input
	layers[0] = input;
	// Loop through layers
	for (size_t i = 0; i < weights.size(); i++) {
		// Calculate net input
		Matrix net = weights[i] * layers[i] + biases[i];
		// Apply activation function
		layers[i + 1] = activation(net);
	}
}

void NeuralNetwork::backwardPropagation(Matrix& target, double learningRate) {
    // Calculate error for the output layer
    Matrix error = target - layers.back();
    // Loop through layers in reverse order
    for (int i = weights.size() - 1; i >= 0; i--) {
        // Calculate gradients
        Matrix gradient = error * derivative(layers[i + 1]);
        // Update error for next layer
        error = weights[i].transpose() * error;
        // Store gradients for weight and bias update
        weightGradients[i] = gradient;
        biasGradients[i] = error;
    }
}
