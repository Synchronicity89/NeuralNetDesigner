#include <iostream>
#include <vector>
#include <stdio.h>
#include "..\trainNet.h"

using namespace std;
using json = nlohmann::json;

void trainNet::printSyntax() {
	cout << "Syntax:" << endl;
	cout << "train [configFile]" << endl;
}

ANNConfig trainNet::buildConfig(json configObject) {
	ANNConfig config;

	double learningRate = configObject["learningRate"];
	double momentum = configObject["momentum"];
	double bias = configObject["bias"];
	int epoch = configObject["epoch"];
	string trainingFile = configObject["trainingFile"];
	string labelsFile = configObject["labelsFile"];
	string weightsFile = configObject["weightsFile"];


	vector<int> topology = configObject["topology"];

	ANN_ACTIVATION hActivation = configObject["hActivation"];
	ANN_ACTIVATION oActivation = configObject["oActivation"];

	config.topology = topology;
	config.bias = bias;
	config.learningRate = learningRate;
	config.momentum = momentum;
	config.epoch = epoch;
	config.hActivation = hActivation;
	config.oActivation = oActivation;
	config.trainingFile = trainingFile;
	config.labelsFile = labelsFile;
	config.weightsFile = weightsFile;

	return config;
}

void trainNet::printToConsole(NeuralNetwork* nn) {

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


string trainNet::LinearAlgebra(std::vector<std::vector<double>>& y_data, std::vector<std::vector<double>>& x_data)
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

string trainNet::ChessGame(std::vector<std::vector<double>>& y_data, std::vector<std::vector<double>>& x_data,
	string xTraining, string yLabels)
{
	//load the X_training.csv into x_data, and the Y_Labels.csv into y_data
	if (xTraining.size() == 0) {
		xTraining = "X_training.csv";
	}
	if (yLabels.size() == 0) {
		yLabels = "Y_Labels.csv";
	}
	ifstream xFile(xTraining);
	ifstream yFile(yLabels);

	string line;
	while (getline(xFile, line)) {
		vector<double>  dRow;
		string          tok;
		stringstream    ss(line);

		while (getline(ss, tok, ',')) {
			dRow.push_back(stof(tok) / 10.0);
		}

		x_data.push_back(dRow);
	}

	while (getline(yFile, line)) {

		vector<double>  dRow;
		string          tok;
		stringstream    ss(line);

		while (getline(ss, tok, ',')) {
			dRow.push_back(stof(tok) / 10.0);
		}

		y_data.push_back(dRow);
	}

	return "ChessGame.dist";
}

int trainNet::trainNetwork()
{
	string xTrainingFileName = "trainingFile.csv";
	string yLabelsFileName = "labelsFile.csv";
	string configContents = "";
	int retVal = trainNetwork(xTrainingFileName, yLabelsFileName, configContents);
	return retVal;
}

int trainNet::trainNetwork(std::string& xTrainingFileName, std::string& yLabelsFileName, std::string& configContents)
{
	vector< vector<double> > y_data;
	vector< vector<double> > x_data;

	//string configNN = LinearAlgebra(y_data, x_data);
	string configNN = ChessGame(y_data, x_data, xTrainingFileName, yLabelsFileName);

	// if the files are not found then write the data to the files

	// look for the file xTrainingFileName and set a bool to true if it is found
	ifstream xFile(xTrainingFileName);
	bool xFileFound = xFile.good();
	ifstream yFile(yLabelsFileName);
	bool yFileFound = yFile.good();


	if(!xFileFound) utils::Misc::writeData(xTrainingFileName, x_data);
	if(!yFileFound) utils::Misc::writeData(yLabelsFileName, y_data);

	//ifstream configFile(configNN);

	//// validate that the file was found
	//if (!configFile) {
	//	cerr << "File not found." << endl;
	//	return 1;
	//}

	//string str((std::istreambuf_iterator<char>(configFile)),
	//	std::istreambuf_iterator<char>());

	NeuralNetwork* n = new NeuralNetwork(buildConfig(json::parse(configContents)));
	//string trainingFile = n->config.trainingFile;
	//string labelsFile = n->config.labelsFile;

	string trainingFile = xTrainingFileName;
	string labelsFile = yLabelsFileName;

	cout << trainingFile << endl;
	cout << labelsFile << endl;

	vector< vector<double> > trainingData = utils::Misc::fetchData(trainingFile);
	vector< vector<double> > labelData = utils::Misc::fetchData(labelsFile);

	cout << "Training Data Size: " << trainingData.size() << endl;
	cout << "Label Data Size: " << labelData.size() << endl;

	for (int i = 0; i < n->config.epoch; i++) {
		for (int tIndex = 0; tIndex < trainingData.size(); tIndex++) {
			vector<double> input = trainingData.at(tIndex);
			vector<double> target = labelData.at(tIndex);

			n->train(
				input,
				target,
				n->config.bias,
				n->config.learningRate,
				n->config.momentum
			);
		}
		cout << n->error << endl;
	}

	cout << "Done! Writing to " << n->config.weightsFile << "..." << endl;
	n->saveWeights(n->config.weightsFile);
	return 0;
}


