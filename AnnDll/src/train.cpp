#include <iostream>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <streambuf>
#include <ostream>
#include <time.h>
#include "../include/json.hpp"
#include "../include/NeuralNetwork.hpp"
#include "../include/utils/Misc.hpp"

using namespace std;
using json = nlohmann::json;

void printSyntax() {
  cout << "Syntax:" << endl;
  cout << "train [configFile]" << endl;
}

ANNConfig buildConfig(json configObject) {
  ANNConfig config;

  double learningRate   = configObject["learningRate"];
  double momentum       = configObject["momentum"];
  double bias           = configObject["bias"];
  int epoch             = configObject["epoch"];
  string trainingFile = configObject["trainingFile"];
  string labelsFile = configObject["labelsFile"];
  string weightsFile = configObject["weightsFile"];


  vector<int> topology  = configObject["topology"];

  ANN_ACTIVATION hActivation = configObject["hActivation"];
  ANN_ACTIVATION oActivation = configObject["oActivation"];

  config.topology     = topology;
  config.bias         = bias;
  config.learningRate = learningRate;
  config.momentum     = momentum;
  config.epoch        = epoch;
  config.hActivation  = hActivation;
  config.oActivation  = oActivation;
  config.trainingFile = trainingFile;
  config.labelsFile   = labelsFile;
  config.weightsFile  = weightsFile;

  return config;
}
