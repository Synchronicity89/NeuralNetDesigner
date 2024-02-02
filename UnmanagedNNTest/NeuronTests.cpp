#include "pch.h"
#include "CppUnitTest.h"
#include "../AnnDll/include/Neuron.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnmanagedNNTest
{
	TEST_CLASS(NeuronTests)
	{
	public:
		TEST_METHOD(NeuronConstructor)
		{
			// Arrange
			double val = 0.5;

			// Act
			Neuron neuron(val);

			//(1 / (1 + exp(-this->val)))  is the default activation function - sigmoid
			// generate the expected result
			double expectedActivatedVal = 1 / (1 + exp(-val));

			//generate the expected derived value
			double expectedDerivedVal = expectedActivatedVal * (1 - expectedActivatedVal);

			// Assert
			Assert::AreEqual(neuron.getVal(), val);
			Assert::AreEqual(neuron.getActivatedVal(), expectedActivatedVal, .000001);
			Assert::AreEqual(neuron.getDerivedVal(), expectedDerivedVal, .000001);
		}

		TEST_METHOD(NeuronSetVal)
		{
			// Arrange
			double val = 0.5;
			Neuron neuron(val);

			// Act
			neuron.setVal(0.7);

			// generate the expected result
			double expectedActivatedVal = 1 / (1 + exp(-0.7));

			//generate the expected derived value
			double expectedDerivedVal = expectedActivatedVal * (1 - expectedActivatedVal);

			// Assert
			Assert::AreEqual(neuron.getVal(), 0.7);
			Assert::AreEqual(neuron.getActivatedVal(), expectedActivatedVal, .000001);
			Assert::AreEqual(neuron.getDerivedVal(), expectedDerivedVal, .000001);
		}
	};
}