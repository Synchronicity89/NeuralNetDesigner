#pragma once
#include <iostream>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <streambuf>
#include <ostream>
#include <time.h>
//put a precprocessor directive to include the json.hpp file from a certain path if the the current project is AnnDll
//otherwise include the json.hpp file relative from the path of the current project
#ifdef ANNDLL_EXPORTS
#include "../include/json.hpp"
#include "../include/NeuralNetwork.hpp"
#include "../include/utils/Misc.hpp"
#else
#include "../AnnDll/include/json.hpp"
#include "../AnnDll/include/NeuralNetwork.hpp"
#include "../AnnDll/include/utils/Misc.hpp"
#endif


using namespace std;	
class __declspec (dllexport) trainNet
{
public:
	string ChessGame(std::vector<std::vector<double>>& y_data, std::vector<std::vector<double>>& x_data, string xTraining = "", string yLabels = "");
	int trainNetwork();
	int trainNetwork(std::string& xTrainingFileName, std::string& yLabelsFileName, std::string& configContents);
	void printSyntax();
	ANNConfig buildConfig(json configObject);
	void printToConsole(NeuralNetwork* nn);
	string LinearAlgebra(std::vector<std::vector<double>>& y_data, std::vector<std::vector<double>>& x_data);
};

