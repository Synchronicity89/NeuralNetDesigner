#include "pch.h"
#include "NeuralNetwork.h"
#include "matrix.h"

// Implement the rows function
int NeuralNetwork::rows(const Matrix& m) {
    return m.getRows();
}

// Validate the size of weight and weight gradient matrices
void NeuralNetwork::validateMatrixSize() {
    for (size_t i = 0; i < layerSizes.size() - 1; i++) {
        if (weights[i].getData().size() != layerSizes[i + 1] * layerSizes[i]) {
            throw std::invalid_argument("Invalid weight matrix data size.");
        }
        if (weightGradients[i].getData().size() != layerSizes[i + 1] * layerSizes[i]) {
            throw std::invalid_argument("Invalid weight gradient matrix data size.");
        }
    }
}

// Constructor for NeuralNetwork class
NeuralNetwork::NeuralNetwork(const std::vector<int>& layerSizes)
    : layerSizes(layerSizes),
    weights(layerSizes.size() - 1),
    weightGradients(layerSizes.size() - 1),
    biases(layerSizes.size() - 1),
    biasGradients(layerSizes.size() - 1),
    layers(layerSizes.size())
{
    // Validate layers size
    if (layerSizes.size() < 2) {
        throw std::invalid_argument("Invalid number of layers. At least 2 layers are required.");
    }

    // Initialize weights, weightGradients, biases, and biasGradients
    for (size_t i = 0; i < layerSizes.size() - 1; i++) {
        // Validate matrix sizes
        if (layerSizes[i] <= 0 || layerSizes[i + 1] <= 0) {
            throw std::invalid_argument("Invalid matrix size. Matrix dimensions must be greater than 0.");
        }

        weights[i] = Matrix(layerSizes[i + 1], layerSizes[i]);
        weightGradients[i] = Matrix(layerSizes[i + 1], layerSizes[i]);
        biases[i] = Matrix(layerSizes[i + 1], 1);
        biasGradients[i] = Matrix(layerSizes[i + 1], 1);
    }

    // Validate data size
    if (layerSizes == std::vector<int>{2, 2, 2}) {
        validateMatrixSize();
    }
}

// Update weights and biases based on the given learning rate
void NeuralNetwork::updateWeightsAndBiases(double learningRate) {
    for (size_t i = 0; i < weights.size(); i++) {
        try
        {
            weights[i] = weights[i] + weightGradients[i] * learningRate;
        }
        catch (const std::exception&)
        {
//			weights[i] = weights[i] + Matrix::transpose(weightGradients[i] * learningRate);
            //transpose the sum of the transposed weights[i] and the transposed product of weightGradients[i] and learningRate
            weights[i] = Matrix::transpose(Matrix::transpose(weights[i]) + /*Matrix::transpose(*/weightGradients[i] * learningRate)/*)*/;
		}
        biases[i] = biases[i] + biasGradients[i] * learningRate;
    }
}

// Compute the mean squared error loss between the output and target matrices
double NeuralNetwork::computeLoss(const Matrix& output, const Matrix& target) {
    double mse = 0.0;
    for (int i = 0; i < output.getRows(); ++i) {
        mse += std::pow(output(i, 0) - target(i, 0), 2);
    }
    return mse / output.getRows();
}

// Perform forward propagation through the neural network
void NeuralNetwork::forwardPropagation(const Matrix& input) {
    // Set first layer to input
    layers[0] = input;
    // Loop through layers
    for (size_t i = 0; i < weights.size(); i++) {
        // Calculate net input
        // define net but don't initialize it
        Matrix net;
        try
        {
			net = weights[i] * Matrix::transpose(layers[i]);// + biases[i];
		}
        catch (const std::exception&)
        {
            net = weights[i] * layers[i];// + biases[i];
        }
        // Apply activation function
        layers[i + 1] = activation(net);
    }
}

// Perform backward propagation through the neural network
void NeuralNetwork::backwardPropagation(const Matrix& target, double learningRate) {
    // Calculate error for the output layer
    Matrix error = calculateOutputLayerError(target);
    // Loop through layers in reverse order
    for (int i = static_cast<int>(weights.size()) - 1; i >= 0; i--) {
        // Calculate gradients
        Matrix gradient = calculateLayerGradient(i + 1, error);
        // Update error for next layer
        error = calculateErrorForNextLayer(i, gradient);
        // Store gradients for weight and bias update
        weightGradients[i] = gradient;
        biasGradients[i] = error;
    }
}

// Calculate the error for the output layer
Matrix NeuralNetwork::calculateOutputLayerError(const Matrix& target) {
    // Validate dimensions
    if (layers.back().getRows() != target.getRows() || layers.back().getCols() != target.getCols()) {
        throw std::invalid_argument("Dimensions of output layer and target matrix do not match.");
    }
    // Calculate error for the output layer
    return (layers.back() * -1.) + target;
}

// Calculate the gradient for a specific layer
Matrix NeuralNetwork::calculateLayerGradient(int layerIndex, const Matrix& error) {
    // Validate dimensions
    if (layers[layerIndex].getRows() != error.getRows() || layers[layerIndex].getCols() != error.getCols()) {
        throw std::invalid_argument("Dimensions of layer and error matrix do not match.");
    }
    // Calculate gradients
    Matrix result;
    try
    {
    result = derivative(layers[layerIndex]) * error;
	}
    catch (const std::exception&)
    {
		result = derivative(layers[layerIndex]) * Matrix::transpose(error);
	}
    return result;
}

// Calculate the error for the next layer
Matrix NeuralNetwork::calculateErrorForNextLayer(int layerIndex, const Matrix& gradient) {
    // Validate dimensions
    if (weights[layerIndex].getRows() != gradient.getRows() || weights[layerIndex].getCols() != gradient.getCols()) {
        //throw std::invalid_argument("Dimensions of weight matrix and gradient matrix do not match.");
    }
    // Update error for next layer
    try
    {
		return Matrix::transpose(weights[layerIndex]) * gradient;
	}
    catch (const std::exception&)
    {
		return weights[layerIndex] * gradient;
    }
}

// Calculate the derivative of the matrix using the activation function
Matrix NeuralNetwork::derivative(const Matrix& m) {
    Matrix result = m;
    result.applyFunction([](double x) { return x * (1.0 - x); });
    return result;
}

// Apply the activation function to the matrix
Matrix NeuralNetwork::activation(const Matrix& m) {
    Matrix result = m;
    result.applyFunction([](double x) { return 1.0 / (std::exp(x * -1.0) + 1.0); });
    return result;
}

//// Constructor for NeuralNetwork class
//NeuralNetwork::NeuralNetwork(const std::vector<int>& layerSizes)
//    : layerSizes(layerSizes),
//    weights(layerSizes.size() - 1),
//    weightGradients(layerSizes.size() - 1),
//    biases(layerSizes.size() - 1),
//    biasGradients(layerSizes.size() - 1),
//    layers(layerSizes.size())
//{
//    // Validate layers size
//    if (layerSizes.size() < 2) {
//        throw std::invalid_argument("Invalid number of layers. At least 2 layers are required.");
//    }
//
//    // Initialize weights, weightGradients, biases, and biasGradients
//    for (size_t i = 0; i < layerSizes.size() - 1; i++) {
//        // Validate matrix sizes
//        if (layerSizes[i] <= 0 || layerSizes[i + 1] <= 0) {
//            throw std::invalid_argument("Invalid matrix size. Matrix dimensions must be greater than 0.");
//        }
//
//        weights[i] = Matrix(layerSizes[i + 1], layerSizes[i]);
//        weightGradients[i] = Matrix(layerSizes[i + 1], layerSizes[i]);
//        biases[i] = Matrix(layerSizes[i + 1], 1);
//        biasGradients[i] = Matrix(layerSizes[i + 1], 1);
//    }
//
//    // Validate data size
//    if (layerSizes == std::vector<int>{2, 2, 2}) {
//        for (size_t i = 0; i < layerSizes.size() - 1; i++) {
//            if (weights[i].getData().size() != layerSizes[i + 1] * layerSizes[i]) {
//                throw std::invalid_argument("Invalid weight matrix data size.");
//            }
//            if (weightGradients[i].getData().size() != layerSizes[i + 1] * layerSizes[i]) {
//                throw std::invalid_argument("Invalid weight gradient matrix data size.");
//            }
//            if (biases[i].getData().size() != layerSizes[i + 1]) {
//                throw std::invalid_argument("Invalid bias matrix data size.");
//            }
//            if (biasGradients[i].getData().size() != layerSizes[i + 1]) {
//                throw std::invalid_argument("Invalid bias gradient matrix data size.");
//            }
//        }
//    }
//}

// Train the neural network using the given inputs, outputs, learning rate, and number of epochs
void NeuralNetwork::train(const std::vector<Matrix>& inputs, const std::vector<Matrix>& outputs, double learningRate, int epochs) {
    // Loop through epochs
    for (int i = 0; i < epochs; i++) {
        // Loop through training data
        for (size_t j = 0; j < inputs.size(); j++) {
            // Forward propagation
            forwardPropagation(inputs[j]);
            // Backward propagation
            backwardPropagation(outputs[j], learningRate);
            // Update weights and biases
            updateWeightsAndBiases(learningRate);
        }
        // Print loss
        //std::cout << "Epoch: " << i + 1 << " Loss: " << computeLoss(layers.back(), outputs[0]) << std::endl;
    }
}

// Predict the output for the given input using the trained neural network
Matrix NeuralNetwork::predict(const Matrix& input) {
    // Forward propagation
    forwardPropagation(input);
    // Return output layer
    return layers.back();
}
