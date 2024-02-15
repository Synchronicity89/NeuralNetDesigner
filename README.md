# NeuralNetDesigner
Usage:  Just run the WPF app NeuralNetDesigner in the debugger after rebuilding everything.  A xcopy command in the build event of AnnDll project will copy a dll where it needs to be.
You can debug the unmanaged C++ AnnDLL project using the unit tests and the UnmanagedNNCmd console app.  Due to Debug Properties being set to mixed in the WPF C# project NeuralNetDesigner, you can also debug all three languages used in this solution:
- C#
- C++/CLI
- C++
