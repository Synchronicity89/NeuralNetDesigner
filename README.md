# NeuralNetDesigner Usage:  Just run the WPF app NeuralNetDesigner in the debugger after rebuilding everything.  A xcopy command in the build event of AnnDll project will copy a dll where it needs to be.
You can debug the unmanaged NN DLL project, AnnDll, using the unit tests and the UnmanagedNNCmd console app, however...
In order to debug the C++ DLL project UnmanagedNN as it is used by the WPF EXE project named the same as the solution, which loads the C++/CLI assembly, DeepLearning.dll, which loads the AnnDll.DLL, you have to do a manual step that is not stored in repo source code
- Open the properties of the AnnDll project.  This is the only project properties you need to tweak
- Find the Debugging tab.  You are going to specify the host app that will be loading both the C++/CLI project DeepLearning which in turn will load AnnDll.dll.  No spaces so no quotes.  Chose the Debug configuration.
- Put text in the command text box: ../../$(SolutionName)/bin/$(Configuration)/net8.0-windows/$(SolutionName).exe
- Put text in the working directory: $(TargetDir)
- Always rebuilding everything because the WPF app NeuralNetDesigner.exe has a choice from where to load the AnnDll.DLL from
  - The TargetDir of the WPF project NeuralNetDesigner
  - The TargetDir of the DLL project AnnDll
