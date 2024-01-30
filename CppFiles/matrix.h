#pragma once
#include "pch.h"

//include standard libraries
#include <vector>
#include <random>
#include <string>


class Matrix {
public:
    // Constructor to create a matrix of given dimensions
    Matrix(int rows, int cols);

    // Basic operations
    Matrix operator+(const Matrix& other);
    Matrix operator-(const Matrix& other);
    Matrix operator*(const Matrix& other);
    // Scalar operations
    Matrix operator*(double scalar);

    // Utility functions
    void applyFunction(double (*function)(double)); // Apply function element-wise
    static Matrix transpose(/*const Matrix& matrix*/);

    // Access elements
    double& operator()(int row, int col);
    const double& operator()(int row, int col) const;
    // Getters
    int getRows() const;
    int getCols() const;

private:
    std::vector<std::vector<double>> data;
    int rows, cols;
};
