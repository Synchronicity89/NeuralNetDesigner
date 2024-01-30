# NeuralNetDesigner
You can debug the UnmanagedNN DLL project using the unit tests, however...
In order to debug the C++ DLL project UnmanagedNN as it is used by the WPF which loads the C++/CLI assembly which loads the C++ DLL, you have to do a manual step that is not stored in repo source code
- Open the properties of that project,
- Find the Debugging tab.  You are going to specify the host app that will be loading both the C++/CLI project DeepLearning which in turn will load UnmanagedNN.dll.  No spaces so no quotes.  Chose the Debug configuration.
- Put text in the command text box: ../../$(SolutionName)/bin/$(Configuration)/net8.0-windows/$(SolutionName).exe
- Put text in the working directory: $(TargetDir)
- Always rebuilding everything because the WPF app NeuralNetDesigner.exe has a choice from where to load the UnmanagedNN.DLL from
  - The TargetDir of the WPF project NeuralNetDesigner
  - The TargetDir of the DLL project UnmanagedNN 
