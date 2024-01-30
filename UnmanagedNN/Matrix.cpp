#include "pch.h"
#include <iostream>
// include header file for the class
#include "matrix.h"

// implement all the methods declared in the header file
// Constructor to create a matrix of given dimensions
Matrix::Matrix(int rows, int cols) {
    // Set dimensions
    this->rows = rows;
    this->cols = cols;
    // Resize data
    data.resize(rows);
    for (int i = 0; i < rows; ++i) {
        data[i].resize(cols);
    }

    // Validation loop
    for (int i = 0; i < rows; ++i) {
        if (data[i].size() != cols) {
            throw std::runtime_error("Data field not resized correctly");
        }
    }
}

Matrix::Matrix()
{
}

// Basic operations
Matrix Matrix::operator+(const Matrix& other) {
	// Check dimensions
	if (rows != other.rows || cols != other.cols) {
		throw std::runtime_error("Matrix dimensions must match");
	}
	// Create new matrix
	Matrix result(rows, cols);
	// Add matrices
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; j++) {
			result(i, j) = data[i][j] + other(i, j);
		}
	}
	return result;
}

Matrix Matrix::operator-(const Matrix& other) {
	// Check dimensions
	if (rows != other.rows || cols != other.cols) {
		throw std::runtime_error("Matrix dimensions must match");
	}
	// Create new matrix
	Matrix result(rows, cols);
	// Subtract matrices
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; j++) {
			result(i, j) = data[i][j] - other(i, j);
		}
	}
	return result;
}

Matrix Matrix::operator*(const Matrix& other) {
	// Check dimensions
	if (cols != other.rows) {
		throw std::runtime_error("Matrix dimensions must match");
	}
	// Create new matrix
	Matrix result(rows, other.cols);
	// Multiply matrices
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < other.cols; ++j) {
			for (int k = 0; k < cols; ++k) {
				result(i, j) += data[i][k] * other(k, j);
			}
		}
	}
	return result;
}

// Scalar operations
Matrix Matrix::operator*(double scalar) {
	// Create new matrix
	Matrix result(rows, cols);
	// Multiply matrix by scalar
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; j++) {
			result(i, j) = data[i][j] * scalar;
		}
	}
	return result;
}

Matrix Matrix::operator+(double scalar)
{
// Create new matrix
	Matrix result(rows, cols);
	// Add scalar to matrix
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; j++) {
			result(i, j) = data[i][j] + scalar;
		}
	}
	return result;
}

// Utility functions
void Matrix::applyFunction(double (*function)(double)) {
	// Apply function element-wise
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; j++) {
			data[i][j] = function(data[i][j]);
		}
	}
}

// transpose function
Matrix Matrix::transpose(const Matrix& matrix) {
	Matrix result(matrix.getCols(), matrix.getRows()); // Fix: Swap rows and cols in the constructor
	// Transpose matrix
	for (int i = 0; i < matrix.getRows(); ++i) { // Fix: Iterate over rows instead of cols
		for (int j = 0; j < matrix.getCols(); j++) { // Fix: Iterate over cols instead of rows
			result(j, i) = matrix(i, j); // Fix: Swap indices for accessing elements
		}
	}
	return result;
}

// Access elements
double& Matrix::operator()(int row, int col) {
	return data[row][col];
}

const double& Matrix::operator()(int row, int col) const {
	return data[row][col];
}

// Getters

int Matrix::getRows() const {
	return rows;
}

int Matrix::getCols() const {
	return cols;
}

std::vector<std::vector<double>> Matrix::getData() const {
	return data;
}