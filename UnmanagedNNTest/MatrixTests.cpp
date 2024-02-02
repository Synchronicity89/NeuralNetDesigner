#include "pch.h"
#include "CppUnitTest.h"
#include "../AnnDll/include/Matrix.hpp"
#include "../AnnDll/include/utils/Math.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnmanagedNNTest
{
	TEST_CLASS(MatrixTest)
	{
	public:
		
		TEST_METHOD(MatrixConstructorWithDimensions)
		{
			Matrix matrix(2, 3, false);
			Assert::AreEqual(matrix.getNumRows(), 2);
			Assert::AreEqual(matrix.getNumCols(), 3);
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

			Matrix result(2, 2);

			utils::Math::multiplyMatrix(&matrix1, &matrix2, &result);

			Assert::AreEqual(result(0, 0), 19.0);
			Assert::AreEqual(result(0, 1), 22.0);
			Assert::AreEqual(result(1, 0), 43.0);
			Assert::AreEqual(result(1, 1), 50.0);
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

			Matrix result = *matrix.transpose();

			Assert::AreEqual(result.getNumRows(), 3);
			Assert::AreEqual(result.getNumCols(), 2);
			Assert::AreEqual(result(0, 0), 1.0);
			Assert::AreEqual(result(0, 1), 4.0);
			Assert::AreEqual(result(1, 0), 2.0);
			Assert::AreEqual(result(1, 1), 5.0);
			Assert::AreEqual(result(2, 0), 3.0);
			Assert::AreEqual(result(2, 1), 6.0);
		}

	};
}
