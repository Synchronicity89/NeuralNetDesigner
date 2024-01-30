#pragma once
//#include "pch.h"
#include "Matrix.h"
#include <vector>


class __declspec(dllexport) NeuralNetwork {
public:
    NeuralNetwork(const std::vector<int>& layers);

    void train(const std::vector<Matrix>& inputs, const std::vector<Matrix>& outputs, double learningRate, int epochs);
    Matrix predict(const Matrix& input);

//private:
    std::vector<int> layerSizes;
    std::vector<Matrix> weights;
    std::vector<Matrix> weightGradients;
    std::vector<Matrix> biases;
    std::vector<Matrix> biasGradients;
    std::vector<Matrix> layers;

    void forwardPropagation(const Matrix& input);
    void backwardPropagation(const Matrix& target, double learningRate);
    Matrix calculateOutputLayerError(const Matrix& target);
    Matrix calculateLayerGradient(int layerIndex, const Matrix& error);
    Matrix calculateErrorForNextLayer(int layerIndex, const Matrix& gradient);
    void updateWeightsAndBiases(double learningRate);
    double computeLoss(const Matrix& output, const Matrix& target);
    Matrix derivative(const Matrix& m);
    Matrix activation(const Matrix& m);
    int rows(const Matrix& m);
    void validateMatrixSize();
};
