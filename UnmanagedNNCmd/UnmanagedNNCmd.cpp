#include "UnmanagedNNCmd.h"
#include "../AnnDll/src/train.cpp"

using namespace std;
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
void printToConsole(NeuralNetwork *nn) {

    for (int i = 0; i < nn->layers.size(); i++)
    {
        cout << "LAYER: " << i << endl;
        if (i == 0) {
            Matrix* m = nn->layers.at(i)->matrixifyVals();
            m->printToConsole();
        }
        else
        {
            Matrix* m = nn->layers.at(i)->matrixifyActivatedVals();
            m->printToConsole();
        }
        cout << "==============================" << endl;
        if (i != nn->layers.size() - 1)
        {
            cout << "Weight Matrix between layer " << i << " and layer " << i + 1 << ":" << endl;
            nn->getWeightMatrix(i)->printToConsole();
        }
        cout << "==============================" << endl;
    }
}


string LinearAlgebra(std::vector<std::vector<double>>& y_data, std::vector<std::vector<double>>& x_data)
{
    for (int i = 0; i < 5000; i++) {
        double m = (double)rand() / RAND_MAX;
        double x;
        vector<double> y;
        vector<double> m_vec; // boring vector only has one value

        // vary the y intercept in a quasi-random way


        double yIntercept = (double)rand() / RAND_MAX;
        for (int j = 0; j < 10; j++) {
            x = (double)j / 10;
            y.push_back(m * x + yIntercept);
        }
        // push m to m_data
        m_vec.push_back(m);
        y_data.push_back(y);
        x_data.push_back(m_vec);
    }
    return "configNN.dist";
}

int main() {

    // define x_data and y_data
    vector< vector<double> > y_data;
    vector< vector<double> > x_data;

    string configNN = LinearAlgebra(y_data, x_data);

    utils::Misc::writeData("trainingFile.csv", y_data);
    utils::Misc::writeData("labelsFile.csv", x_data);

    ifstream configFile(configNN);

    // validate that the file was found
    if (!configFile) {
		cerr << "File not found." << endl;
		return 1;
	}

    string str((std::istreambuf_iterator<char>(configFile)),
              std::istreambuf_iterator<char>());

    NeuralNetwork *n  = new NeuralNetwork(buildConfig(json::parse(str)));
    string trainingFile = n->config.trainingFile;
    string labelsFile = n->config.labelsFile;

    cout << trainingFile << endl;
    cout << labelsFile << endl;
    
    vector< vector<double> > trainingData = utils::Misc::fetchData(trainingFile);
    vector< vector<double> > labelData    = utils::Misc::fetchData(labelsFile);
    
    cout << "Training Data Size: " << trainingData.size() << endl;
    cout << "Label Data Size: " << labelData.size() << endl;
    
    for(int i = 0; i < n->config.epoch; i++) {
    for(int tIndex = 0; tIndex < trainingData.size(); tIndex++) {
        vector<double> input    = trainingData.at(tIndex);
        vector<double> target   = labelData.at(tIndex);
    
        n->train(
        input,
        target,
        n->config.bias,
        n->config.learningRate,
        n->config.momentum
        );
    }
    cout << n->error << endl;
    
    //cout << "Error at epoch " << i+1 << ": " << n->error << endl;
    }
    
    cout << "Done! Writing to " << n->config.weightsFile << "..." << endl;
    n->saveWeights(n->config.weightsFile);

	//print the activatedVals values to

//    // Set the random seed for reproducibility
//    srand(42);
//
//    // Create a neural network with {2, 3, 1} topology and 0.01 learning rate
//    std::vector<int> topology = { 2, 3, 1 };
//    NeuralNetwork nn = NeuralNetwork(topology);
//
//    // Create some input and output data for testing
//    //std::vector<Matrix> inputs = {
//    //    Matrix(1, 2) << 0, 0,
//    //    Matrix(1, 2) << 0, 1,
//    //    Matrix(1, 2) << 1, 0,
//    //    Matrix(1, 2) << 1, 1
//    //};
//    // create a vector of matrices and fill it with the input data using simplistic syntax, not using operator overloading
//    std::vector<Matrix> inputs;
//    Matrix m1(1, 2);
//    m1(0, 0) = 0;
//    m1(0, 1) = 0;
//    inputs.push_back(m1);
//    Matrix m2(1, 2);
//    m2(0, 0) = 0;
//    m2(0, 1) = 1;
//    inputs.push_back(m2);
//    Matrix m3(1, 2);
//    m3(0, 0) = 1;
//    m3(0, 1) = 0;
//    inputs.push_back(m3);
//    Matrix m4(1, 2);
//    m4(0, 0) = 1;
//    m4(0, 1) = 1;
//    inputs.push_back(m4);
//        
//
//    std::vector<Matrix> outputs = {
//        Matrix(1, 1) << 0,
//        Matrix(1, 1) << 1,
//        Matrix(1, 1) << 1,
//        Matrix(1, 1) << 0
//    };
//
//    // Use the global methods to check the dimensions of every vector, matrix and vector of matrices in nn
//    assert(sameDimensions(nn.weights, std::vector<int>{ 6, 3 })); // Check the dimensions of the weights
//
//    assert(sameDimensions(nn.biases, std::vector<int>{ 3, 1 })); // Check the dimensions of the biases
//    // on the nn object, call the forward propagation method using input as the input
//    nn.forwardPropagation(inputs[0]);
//    
//    assert(sameDimensions(nn.layers, std::vector<int>{ 2, 3, 1 })); // Check the dimensions of the layers
//
//    assert(sameDimensions(nn.weightGradients, std::vector<int>{ 6, 3 })); // Check the dimensions of the weight gradients
//
//    assert(sameDimensions(nn.biasGradients, std::vector<int>{ 3, 1 })); // Check the dimensions of the bias gradients
//
//    // Print the dimensions of the neural network
//    printDimensions(nn.weights);
//
//    printDimensions(nn.biases);
//
//    printDimensions(nn.layers);
//
//    printDimensions(nn.weightGradients);
//
//    printDimensions(nn.biasGradients);
//
//        // Print the dimensions of the input and output data
//
//        printDimensions(inputs);
//
//        printDimensions(outputs);
//
//
//
//    // Train the neural network for 1000 epochs
//    nn.train(inputs, outputs, 0.01, 1000);
//
//    // Test the neural network on the same data
//    std::cout << "Testing the neural network on the same data..." << std::endl;
//    for (int i = 0; i < inputs.size(); i++) {
//        Matrix prediction = nn.predict(inputs[i]); // Get the prediction of the neural network for the input
//        //std::cout << "Input: " << inputs[i] << std::endl; // Print the input
//        //std::cout << "Output: " << outputs[i] << std::endl; // Print the output
//        //std::cout << "Prediction: " << prediction << std::endl; // Print the prediction
//        // print the Input, Output, Prediction without using operator overloading, just the simple syntax
//        std::cout << "Input: " << inputs[i].getData()[0][0] << " " << inputs[i].getData()[0][1] << std::endl;
//        std::cout << "Output: " << outputs[i].getData()[0][0] << std::endl;
//        std::cout << "Prediction: " << prediction.getData()[0][0] << std::endl;
//
//        std::cout << "Loss: " << nn.computeLoss(prediction, outputs[i]) << std::endl; // Print the loss
//        std::cout << std::endl;
//    }
//
//    // Check the accuracy of the neural network on the same data
//    std::cout << "Accuracy: " << accuracy(nn, inputs, outputs) << std::endl; // Print the accuracy
//
//    // Create some random input and output data for testing
//    std::vector<Matrix> randomInputs = randomMatrices({ 2, 2, 1 }); // Generate four random inputs of size 1 x 2
//    std::vector<Matrix> randomOutputs = oneHots(2, { 0, 1, 1, 0 }); // Generate four random outputs of size 1 x 2
//
//    // Test the neural network on the random data
//    std::cout << "Testing the neural network on the random data..." << std::endl;
//    for (int i = 0; i < randomInputs.size(); i++) {
//        Matrix prediction = nn.predict(randomInputs[i]); // Get the prediction of the neural network for the input
//        //std::cout << "Input: " << randomInputs[i] << std::endl; // Print the input
//        //std::cout << "Output: " << randomOutputs[i] << std::endl; // Print the output
//        //std::cout << "Prediction: " << prediction << std::endl; // Print the prediction
//        // print the Input, Output, Prediction without using operator overloading, just the simple syntax. first create string variables for each
//        // then print the string variables
//        std::string inputString = "Input: " + std::to_string(randomInputs[i].getData()[0][0]) + " " + std::to_string(randomInputs[i].getData()[0][1]);
//        std::cout << inputString << std::endl;
//        std::cout << "Loss: " << nn.computeLoss(prediction, randomOutputs[i]) << std::endl; // Print the loss
//        std::cout << std::endl;
//    }
//
//    // Check the accuracy of the neural network on the random data
//    std::cout << "Accuracy: " << accuracy(nn, randomInputs, randomOutputs) << std::endl; // Print the accuracy
//
    return 0;
}
