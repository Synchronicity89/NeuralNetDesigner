////#include "catch.hpp"
//#include "pch.h"
//#include "..\UnmanagedNN\matrix.h"
//
//#include "CppUnitTest.h"
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//namespace UnmanagedNNTest
//
//TEST_CASE("Matrix Constructor with dimensions", "[Matrix]") {
//    Matrix matrix(2, 3);
//    REQUIRE(matrix.getRows() == 2);
//    REQUIRE(matrix.getCols() == 3);
//}
//
//TEST_CASE("Matrix Default Constructor", "[Matrix]") {
//    Matrix matrix;
//    REQUIRE(matrix.getRows() == 0);
//    REQUIRE(matrix.getCols() == 0);
//}
//
//TEST_CASE("Matrix Addition", "[Matrix]") {
//    Matrix matrix1(2, 2);
//    matrix1(0, 0) = 1.0;
//    matrix1(0, 1) = 2.0;
//    matrix1(1, 0) = 3.0;
//    matrix1(1, 1) = 4.0;
//
//    Matrix matrix2(2, 2);
//    matrix2(0, 0) = 5.0;
//    matrix2(0, 1) = 6.0;
//    matrix2(1, 0) = 7.0;
//    matrix2(1, 1) = 8.0;
//
//    Matrix result = matrix1 + matrix2;
//
//    REQUIRE(result.getRows() == 2);
//    REQUIRE(result.getCols() == 2);
//    REQUIRE(result(0, 0) == 6.0);
//    REQUIRE(result(0, 1) == 8.0);
//    REQUIRE(result(1, 0) == 10.0);
//    REQUIRE(result(1, 1) == 12.0);
//}
//
//TEST_CASE("Matrix Subtraction", "[Matrix]") {
//    Matrix matrix1(2, 2);
//    matrix1(0, 0) = 5.0;
//    matrix1(0, 1) = 6.0;
//    matrix1(1, 0) = 7.0;
//    matrix1(1, 1) = 8.0;
//
//    Matrix matrix2(2, 2);
//    matrix2(0, 0) = 1.0;
//    matrix2(0, 1) = 2.0;
//    matrix2(1, 0) = 3.0;
//    matrix2(1, 1) = 4.0;
//
//    Matrix result = matrix1 - matrix2;
//
//    REQUIRE(result.getRows() == 2);
//    REQUIRE(result.getCols() == 2);
//    REQUIRE(result(0, 0) == 4.0);
//    REQUIRE(result(0, 1) == 4.0);
//    REQUIRE(result(1, 0) == 4.0);
//    REQUIRE(result(1, 1) == 4.0);
//}
//
//TEST_CASE("Matrix Multiplication", "[Matrix]") {
//    Matrix matrix1(2, 2);
//    matrix1(0, 0) = 1.0;
//    matrix1(0, 1) = 2.0;
//    matrix1(1, 0) = 3.0;
//    matrix1(1, 1) = 4.0;
//
//    Matrix matrix2(2, 2);
//    matrix2(0, 0) = 5.0;
//    matrix2(0, 1) = 6.0;
//    matrix2(1, 0) = 7.0;
//    matrix2(1, 1) = 8.0;
//
//    Matrix result = matrix1 * matrix2;
//
//    REQUIRE(result.getRows() == 2);
//    REQUIRE(result.getCols() == 2);
//    REQUIRE(result(0, 0) == 19.0);
//    REQUIRE(result(0, 1) == 22.0);
//    REQUIRE(result(1, 0) == 43.0);
//    REQUIRE(result(1, 1) == 50.0);
//}
//
//TEST_CASE("Matrix Scalar Multiplication", "[Matrix]") {
//    Matrix matrix(2, 2);
//    matrix(0, 0) = 1.0;
//    matrix(0, 1) = 2.0;
//    matrix(1, 0) = 3.0;
//    matrix(1, 1) = 4.0;
//
//    Matrix result = matrix * 2.0;
//
//    REQUIRE(result.getRows() == 2);
//    REQUIRE(result.getCols() == 2);
//    REQUIRE(result(0, 0) == 2.0);
//    REQUIRE(result(0, 1) == 4.0);
//    REQUIRE(result(1, 0) == 6.0);
//    REQUIRE(result(1, 1) == 8.0);
//}
//
//TEST_CASE("Matrix Scalar Addition", "[Matrix]") {
//    Matrix matrix(2, 2);
//    matrix(0, 0) = 1.0;
//    matrix(0, 1) = 2.0;
//    matrix(1, 0) = 3.0;
//    matrix(1, 1) = 4.0;
//
//    Matrix result = matrix + 2.0;
//
//    REQUIRE(result.getRows() == 2);
//    REQUIRE(result.getCols() == 2);
//    REQUIRE(result(0, 0) == 3.0);
//    REQUIRE(result(0, 1) == 4.0);
//    REQUIRE(result(1, 0) == 5.0);
//    REQUIRE(result(1, 1) == 6.0);
//}
//
//TEST_CASE("Matrix Transpose", "[Matrix]") {
//    Matrix matrix(2, 3);
//    matrix(0, 0) = 1.0;
//    matrix(0, 1) = 2.0;
//    matrix(0, 2) = 3.0;
//    matrix(1, 0) = 4.0;
//    matrix(1, 1) = 5.0;
//    matrix(1, 2) = 6.0;
//
//    Matrix result = Matrix::transpose(matrix);
//
//    REQUIRE(result.getRows() == 3);
//    REQUIRE(result.getCols() == 2);
//    REQUIRE(result(0, 0) == 1.0);
//    REQUIRE(result(0, 1) == 4.0);
//    REQUIRE(result(1, 0) == 2.0);
//    REQUIRE(result(1, 1) == 5.0);
//    REQUIRE(result(2, 0) == 3.0);
//    REQUIRE(result(2, 1) == 6.0);
//}
//
//TEST_CASE("Matrix Apply Function", "[Matrix]") {
//    Matrix matrix(2, 2);
//    matrix(0, 0) = 1.0;
//    matrix(0, 1) = 2.0;
//    matrix(1, 0) = 3.0;
//    matrix(1, 1) = 4.0;
//
//    matrix.applyFunction([](double x) { return x * x; });
//
//    REQUIRE(matrix.getRows() == 2);
//    REQUIRE(matrix.getCols() == 2);
//    REQUIRE(matrix(0, 0) == 1.0);
//    REQUIRE(matrix(0, 1) == 4.0);
//    REQUIRE(matrix(1, 0) == 9.0);
//    REQUIRE(matrix(1, 1) == 16.0);
//}
