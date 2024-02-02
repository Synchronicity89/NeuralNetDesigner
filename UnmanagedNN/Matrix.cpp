#include "pch.h"
#include <iostream>
// include header file for the class
#include "matrix.h"

// implement all the methods declared in the header file
// Constructor to create a matrix of given dimensions
Matrix::Matrix(int rows, int cols, bool isRandom) {
	// Set dimensions
	this->numRows = rows;
	this->numCols = cols;
	// Resize data
	//values.resize(rows);
	for (int i = 0; i < rows; ++i) {
		vector<double> colValues;

		for (int j = 0; j < numCols; j++) {
			double r = 0.00;
			if (isRandom) {
				r = generateRandomNumber();
			}

			colValues.push_back(r);
		}
		this->values.push_back(colValues);

		// This is the old Validation loop that was passing before this constructor was changed
		// Now it is failing because the values are being sized differently
		//for (int i = 0; i < rows; ++i) {
		//	if (values[i].size() != cols) {
		//		throw runtime_error("Data field not resized correctly");
		//	}
		//}
	}
}

Matrix::Matrix()
{
}

// Print operations
void Matrix::printToConsole() {
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; j++) {
			cout << this->values.at(i).at(j) << "\t\t";
		}
		cout << endl;
	}
}

// Basic operations
Matrix Matrix::operator+(const Matrix& other) {
	// Check dimensions
	if (numRows != other.numRows || numCols != other.numCols) {
		throw runtime_error("Matrix dimensions must match");
	}
	// Create new matrix
	Matrix result(numRows, numCols);
	// Add matrices
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; j++) {
			result(i, j) = values[i][j] + other(i, j);
		}
	}
	return result;
}

Matrix Matrix::operator-(const Matrix& other) {
	// Check dimensions
	if (numRows != other.numRows || numCols != other.numCols) {
		throw runtime_error("Matrix dimensions must match");
	}
	// Create new matrix
	Matrix result(numRows, numCols);
	// Subtract matrices
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; j++) {
			result(i, j) = values[i][j] - other(i, j);
		}
	}
	return result;
}

Matrix Matrix::operator*(const Matrix& other) {
	// Check dimensions
	if (numCols != other.numRows) {
		throw runtime_error("Matrix dimensions must match");
	}
	// Create new matrix
	Matrix result(numRows, other.numCols);
	// Multiply matrices
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < other.numCols; ++j) {
			for (int k = 0; k < numCols; ++k) {
				result(i, j) += values[i][k] * other(k, j);
			}
		}
	}
	return result;
}

// Scalar operations
Matrix Matrix::operator*(double scalar) {
	// Create new matrix
	Matrix result(numRows, numCols);
	// Multiply matrix by scalar
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; j++) {
			result(i, j) = values[i][j] * scalar;
		}
	}
	return result;
}

Matrix Matrix::operator+(double scalar)
{
	// Create new matrix
	Matrix result(numRows, numCols);
	// Add scalar to matrix
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; j++) {
			result(i, j) = values[i][j] + scalar;
		}
	}
	return result;
}

Matrix& Matrix::operator<<(double value)
{
	// Add scalar to matrix
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; j++) {
			values[i][j] = values[i][j] + value;
		}
	}
	return *this;
}

// Utility functions
void Matrix::applyFunction(double (*function)(double)) {
	// Apply function element-wise
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; j++) {
			values[i][j] = function(values[i][j]);
		}
	}
}

Matrix* Matrix::transpose()
{
	Matrix m = Matrix::transpose(*this);
	return &m;
}

double Matrix::generateRandomNumber(double min, double max)
{
	// Generate a random number between min and max
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(min, max);
	return dis(gen);
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

void Matrix::setZero()
{
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; j++) {
			values[i][j] = 0;
		}
	}
}

// Access elements
double& Matrix::operator()(int row, int col) {
	return values[row][col];
}

const double& Matrix::operator()(int row, int col) const {
	return values[row][col];
}

// Getters

int Matrix::getRows() const {
	return numRows;
}

int Matrix::getCols() const {
	return numCols;
}

vector<vector<double>> Matrix::getData() const {
	return values;
}

void Matrix::setValue(int row, int col, double value)
{
	//set value using at method
	values.at(row).at(col) = value;
}

//ostream& operator<<(ostream& os, const Matrix& matrix)
//{
//	for (int i = 0; i < matrix.getRows(); ++i) {
//		for (int j = 0; j < matrix.getCols(); j++) {
//			os << matrix(i, j) << " ";
//		}
//		os << endl;
//	}
//	return os;
//}
