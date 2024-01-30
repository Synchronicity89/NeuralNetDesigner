#include "pch.h"
#include "CppUnitTest.h"
#include "../UnmanagedNN/Matrix.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnmanagedNNTest
{
	TEST_CLASS(MatrixTest)
	{
	public:
		
		TEST_METHOD(MatrixConstructorWithDimensions)
		{
			Matrix matrix(2, 3);
			Assert::AreEqual(matrix.getRows(), 2);
			Assert::AreEqual(matrix.getCols(), 3);
		}

		TEST_METHOD(MatrixDefaultConstructor)
		{
			Matrix matrix;
			Assert::AreEqual(matrix.getRows(), 0);
			Assert::AreEqual(matrix.getCols(), 0);
		}

		TEST_METHOD(MatrixAddition)
		{
			Matrix matrix1(2, 2);
			matrix1(0, 0) = 1;
			matrix1(0, 1) = 2;
			matrix1(1, 0) = 3;
			matrix1(1, 1) = 4;

			Matrix matrix2(2, 2);
			matrix2(0, 0) = 5;
			matrix2(0, 1) = 6;
			matrix2(1, 0) = 7;
			matrix2(1, 1) = 8;

			Matrix result = matrix1 + matrix2;

			Assert::AreEqual(result(0, 0), 6.0);
			Assert::AreEqual(result(0, 1), 8.0);
			Assert::AreEqual(result(1, 0), 10.0);
			Assert::AreEqual(result(1, 1), 12.0);
		}

		TEST_METHOD(MatrixSubtraction)
		{
			Matrix matrix1(2, 2);
			matrix1(0, 0) = 1;
			matrix1(0, 1) = 2;
			matrix1(1, 0) = 3;
			matrix1(1, 1) = 4;

			Matrix matrix2(2, 2);
			matrix2(0, 0) = 5;
			matrix2(0, 1) = 6;
			matrix2(1, 0) = 7;
			matrix2(1, 1) = 8;

			Matrix result = matrix1 - matrix2;

			Assert::AreEqual(result(0, 0), -4.0);
			Assert::AreEqual(result(0, 1), -4.0);
			Assert::AreEqual(result(1, 0), -4.0);
			Assert::AreEqual(result(1, 1), -4.0);
		}

		TEST_METHOD(MatrixMultiplication)
		{
			Matrix matrix1(2, 2);
			matrix1(0, 0) = 1;
			matrix1(0, 1) = 2;
			matrix1(1, 0) = 3;
			matrix1(1, 1) = 4;

			Matrix matrix2(2, 2);
			matrix2(0, 0) = 5;
			matrix2(0, 1) = 6;
			matrix2(1, 0) = 7;
			matrix2(1, 1) = 8;

			Matrix result = matrix1 * matrix2;

			Assert::AreEqual(result(0, 0), 19.0);
			Assert::AreEqual(result(0, 1), 22.0);
			Assert::AreEqual(result(1, 0), 43.0);
			Assert::AreEqual(result(1, 1), 50.0);
		}

		TEST_METHOD(MatrixScalarMultiplication)
		{
			Matrix matrix(2, 2);
			matrix(0, 0) = 1;
			matrix(0, 1) = 2;
			matrix(1, 0) = 3;
			matrix(1, 1) = 4;

			Matrix result = matrix * 2.0;

			Assert::AreEqual(result(0, 0), 2.0);
			Assert::AreEqual(result(0, 1), 4.0);
			Assert::AreEqual(result(1, 0), 6.0);
			Assert::AreEqual(result(1, 1), 8.0);
		}

		TEST_METHOD(MatrixScalarAddition)
		{
			Matrix matrix(2, 2);
			matrix(0, 0) = 1;
			matrix(0, 1) = 2;
			matrix(1, 0) = 3;
			matrix(1, 1) = 4;

			Matrix result = matrix + 2.0;

			Assert::AreEqual(result(0, 0), 3.0);
			Assert::AreEqual(result(0, 1), 4.0);
			Assert::AreEqual(result(1, 0), 5.0);
			Assert::AreEqual(result(1, 1), 6.0);
		}

		TEST_METHOD(MatrixApplyFunction)
		{
			Matrix matrix(2, 2);
			matrix(0, 0) = 1;
			matrix(0, 1) = 2;
			matrix(1, 0) = 3;
			matrix(1, 1) = 4;

			matrix.applyFunction([](double value) { return value * 2; });

			Assert::AreEqual(matrix(0, 0), 2.0);
			Assert::AreEqual(matrix(0, 1), 4.0);
			Assert::AreEqual(matrix(1, 0), 6.0);
			Assert::AreEqual(matrix(1, 1), 8.0);
		}

		TEST_METHOD(MatrixTranspose)
		{
			Matrix matrix(2, 3);
			matrix(0, 0) = 1;
			matrix(0, 1) = 2;
			matrix(0, 2) = 3;
			matrix(1, 0) = 4;
			matrix(1, 1) = 5;
			matrix(1, 2) = 6;

			Matrix result = Matrix::transpose(matrix);

			Assert::AreEqual(result.getRows(), 3);
			Assert::AreEqual(result.getCols(), 2);
			Assert::AreEqual(result(0, 0), 1.0);
			Assert::AreEqual(result(0, 1), 4.0);
			Assert::AreEqual(result(1, 0), 2.0);
			Assert::AreEqual(result(1, 1), 5.0);
			Assert::AreEqual(result(2, 0), 3.0);
			Assert::AreEqual(result(2, 1), 6.0);
		}

	};
}
