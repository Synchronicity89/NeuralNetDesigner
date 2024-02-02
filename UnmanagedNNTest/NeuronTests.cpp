#include "pch.h"
#include "CppUnitTest.h"
#include "../UnmanagedNN/Neuron.h"
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

			// Assert
			Assert::AreEqual(neuron.getVal(), val);
			Assert::AreEqual(neuron.getActivatedVal(), 0.33333333333333331, .000001);
			Assert::AreEqual(neuron.getDerivedVal(), 0.22222222222222221, .000001);
		}

		TEST_METHOD(NeuronSetVal)
		{
			// Arrange
			double val = 0.5;
			Neuron neuron(val);

			// Act
			neuron.setVal(0.7);

			// Assert
			Assert::AreEqual(neuron.getVal(), 0.7);
			Assert::AreEqual(neuron.getActivatedVal(), 0.41176470588235292, .01);
			Assert::AreEqual(neuron.getDerivedVal(), 0.24000000000000002, .01);
		}
	};
}