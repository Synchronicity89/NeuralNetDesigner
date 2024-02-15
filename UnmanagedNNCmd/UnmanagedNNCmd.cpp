#include "UnmanagedNNCmd.h"
#include "../AnnDll/trainNet.h"

using namespace std;
//TODO: this is probably broken now
int main(int argc, char* argv[])
{
	trainNet* t = new trainNet();
	t->trainNetwork();
	return 0;
}
//// A function to check if two matrices have the same dimensions
//bool sameDimensions(const Matrix& m1, const Matrix& m2) {
//    return (m1.getRows() == m2.getRows() && m1.getCols() == m2.getCols());
//}
//
//// A function to check if a vector of matrices have the same dimensions as a vector of integers
//bool sameDimensionsRows(const std::vector<Matrix>& matrices, const std::vector<int>& sizes) {
//    //if (matrices.size() != sizes.size()) return false;
//    for (int i = 0; i < matrices.size(); i++) {
//        if (matrices[i].getRows() != sizes[i]) return false;
//    }
//    return true;
//}
//
//// A function to check if a vector of matrices have the same dimensions as a vector of integers
//bool sameDimensions(const std::vector<Matrix>& matrices, const std::vector<int>& sizes) {
//    //if (matrices.size() != sizes.size()) return false;
//    for (int i = 0; i < matrices.size(); i++) {
//        if (matrices[i].getRows() * matrices[i].getCols() != sizes[i]) return false;
//    }
//    return true;
//}
//
//// A function to print the dimensions of a matrix
//void printDimensions(const Matrix& m) {
//    std::cout << m.getRows() << " x " << m.getCols() << std::endl;
//}
//
//// A function to print the dimensions of a vector of matrices
//void printDimensions(const std::vector<Matrix>& matrices) {
//    for (int i = 0; i < matrices.size(); i++) {
//        printDimensions(matrices[i]);
//    }
//}
//
//// A function to generate a random matrix of given dimensions
//Matrix randomMatrix(int rows, int cols) {
//    Matrix m(rows, cols); // Create a matrix of given dimensions
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < cols; j++) {
//            m(i, j) = (double)rand() / RAND_MAX; // Assign a random value between 0 and 1
//        }
//    }
//    return m;
//}
//
//// A function to generate a vector of random matrices of given sizes
//std::vector<Matrix> randomMatrices(const std::vector<int>& sizes) {
//    std::vector<Matrix> matrices; // Create an empty vector of matrices
//    for (int i = 0; i < sizes.size() - 1; i++) {
//        matrices.push_back(randomMatrix(sizes[i], sizes[i + 1])); // Add a random matrix of size sizes[i] x sizes[i + 1]
//    }
//    return matrices;
//}
//
//// A function to generate a one-hot encoded matrix of given size and index
//Matrix oneHot(int size, int index) {
//    Matrix m(1, size); // Create a matrix of size 1 x size
//    m.setZero(); // Set all elements to zero
//    m(0, index) = 1; // Set the element at index to one
//    return m;
//}
//
//// A function to generate a vector of one-hot encoded matrices of given size and indices
//std::vector<Matrix> oneHots(int size, const std::vector<int>& indices) {
//    std::vector<Matrix> matrices; // Create an empty vector of matrices
//    for (int i = 0; i < indices.size(); i++) {
//        matrices.push_back(oneHot(size, indices[i])); // Add a one-hot encoded matrix of size size and index indices[i]
//    }
//    return matrices;
//}
//
//// A function to calculate the accuracy of a neural network on a given dataset
//double accuracy(NeuralNetwork& nn, const std::vector<Matrix>& inputs, const std::vector<Matrix>& outputs) {
//    int correct = 0; // Initialize the number of correct predictions
//    for (int i = 0; i < inputs.size(); i++) {
//        Matrix prediction = nn.predict(inputs[i]); // Get the prediction of the neural network for the input
//        int maxIndex = 0; // Initialize the index of the maximum element
//        double maxValue = prediction(0, 0); // Initialize the maximum element
//        for (int j = 0; j < prediction.getCols(); j++) {
//            if (prediction(0, j) > maxValue) { // If the current element is greater than the maximum element
//                maxIndex = j; // Update the index of the maximum element
//                maxValue = prediction(0, j); // Update the maximum element
//            }
//        }
//        int outputsi = (int)outputs[i](0, maxIndex); // Get the output at the index of the maximum element
//
//        if (outputsi == 1) { // If the output has a one at the same index as the prediction
//            correct++; // Increment the number of correct predictions
//        }
//    }
//    return (double)correct / inputs.size(); // Return the accuracy as the ratio of correct predictions to total inputs
//}
//
