#pragma once
//#include "pch.h"

//include standard libraries
#include <vector>
#include <random>
#include <string>

using namespace std;

class __declspec(dllexport) Matrix {
public:
    // Constructor to create a matrix of given dimensions
    Matrix(int numRows, int numCols, bool isRandom = false);
    // Default constructor
    Matrix();

    // Print operations
    void printToConsole();

    // Basic operations
    Matrix operator+(const Matrix& other);
    Matrix operator-(const Matrix& other);
    Matrix operator*(const Matrix& other);
    // Scalar operations
    Matrix operator*(double scalar);
    Matrix operator+(double scalar);

    // Compound operations
    Matrix& operator<<(double value);
    // Matrix prediction = nn.predict(inputs[i]); // Get the prediction of the neural network for the input
    // cout << "Prediction: " << prediction << endl;
    // a << operator to output the matrix to the console
    //friend ostream& operator<<(ostream& os, const Matrix& matrix);

    // Utility functions
    void applyFunction(double (*function)(double)); // Apply function element-wise
    Matrix *transpose(); // Transpose the matrix
    double generateRandomNumber(double min = 0, double max = 1); // Generate a random number between min and max

    static Matrix transpose(const Matrix& matrix);
    // setZero function to set all elements to 0
    void setZero();

    // Access elements
    double& operator()(int row, int col);
    const double& operator()(int row, int col) const;
    // Getters
    int getRows() const;
    int getCols() const;
    vector<vector<double>>  getData() const;
    double getValue(int row, int col) { return this->values.at(row).at(col); }
    // Setters
    void setValue(int row, int col, double value);

private:
    vector<vector<double>> values;
    int numRows, numCols;
};
