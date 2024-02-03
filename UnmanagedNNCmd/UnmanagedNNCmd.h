#pragma once
#include <iostream>
#include "..\AnnDll\include\Matrix.hpp" // Assuming this is the header file for your  class
#include "..\AnnDll\include\NeuralNetwork.hpp" // Assuming this is the header file for your  class
#include <fstream> // For file I/O
#include <string> // For using string objects
#include <sstream> // For using string streams
#include "..\AnnDll\include\utils\misc.hpp"

#include <cassert> // For using assert statements
#include <vector>
#include <cmath> // For using math functions

Matrix oneHot(int size, int index);

int main();
