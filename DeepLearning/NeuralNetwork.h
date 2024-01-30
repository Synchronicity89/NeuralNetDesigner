#pragma once
#include "pch.h"
#include "Matrix.h"
#include <vector>


class NeuralNetwork {
public:
    NeuralNetwork(const std::vector<int>& layers);

    void train(const std::vector<Matrix>& inputs, const std::vector<Matrix>& outputs, double learningRate, int epochs);
    Matrix predict(const Matrix& input);

private:
    std::vector<int> layerSizes;
    std::vector<Matrix> weights;
    std::vector<Matrix> weightGradients; // KJB
    std::vector<Matrix> biases;
    std::vector<Matrix> biasGradients; // KJB
    //define the layers variable
    std::vector<Matrix> layers;

    void forwardPropagation(const Matrix& input);
    void backwardPropagation(Matrix& target, double learningRate);
    void updateWeightsAndBiases(double learningRate);
    double computeLoss(const Matrix& output, const Matrix& target);
    //define the derivative function
    Matrix derivative(const Matrix& m);
    Matrix activation(const Matrix& m);
    //define the rows function
    int rows(const Matrix& m);
};
