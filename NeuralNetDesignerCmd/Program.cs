// See https://aka.ms/new-console-template for more information
using NeuralNetDesignerCmd;

Console.WriteLine("Hello, World!");

string source = @"C:\Users\baker\source\repos\NeuralNetDesigner\x64\Debug\AnnDll.*";
string target = @"C:\Users\baker\source\repos\NeuralNetDesigner\NeuralNetDesigner\bin\Debug\net8.0-windows";
string workingDirectory = @"C:\Users\baker\source\repos\NeuralNetDesigner\AnnDll";

string xcopyCommand = XCopyCommandGenerator.GenerateXCopyCommand(source, target, workingDirectory);
Console.WriteLine(xcopyCommand);
