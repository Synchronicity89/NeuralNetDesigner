#pragma once
#include "Matrix.h"
#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;

namespace utils
{
	class __declspec(dllexport) MultiplyMatrix
	{
	public:
		MultiplyMatrix(Matrix *a, Matrix *b);

		Matrix *execute();
	private:
		Matrix *a;
		Matrix *b;
		Matrix *c;
	};

	class __declspec(dllexport) MatrixToVector
	{
	public:
		MatrixToVector(Matrix* a);
		vector<double> execute();

	private:
		Matrix* a;
	};
}
