#include "pch.h"
#include "MultiplyMatrix.h"

utils::MultiplyMatrix::MultiplyMatrix(Matrix* a, Matrix* b)
{
	this->a = a;
	this->b = b;

	if (a->getNumCols() != b->getNumRows()) {
		cerr << "A_rows: " << a->getNumRows() << " != B_colls: " << b->getNumCols() << endl;
		assert(false);
	}

	this->c = new Matrix(a->getNumRows(), b->getNumCols(), false);
}

Matrix* utils::MultiplyMatrix::execute()
{
	for (int i = 0; i < this->a->getNumRows(); i++)
	{
		for (int j = 0; j < this->b->getNumCols(); j++)
		{
			for (int k = 0; k < this->b->getNumRows(); k++)
			{
				double p = this->a->getValue(i, k) * this->b->getValue(k, j);
				double newVal = this->c->getValue(i, j) + p;
				this->c->setValue(i, j, newVal);
			}
		}
	}
	return this->c;
}

utils::MatrixToVector::MatrixToVector(Matrix* a)
{
	this->a = a;
}

vector<double> utils::MatrixToVector::execute()
{
	vector<double> result;

	for (int r = 0; r < this->a->getNumRows(); r++)
	{
		for (int c = 0; c < this->a->getNumCols(); c++)
		{
			result.push_back(this->a->getValue(r, c));
		}
	}

	return result;
}
