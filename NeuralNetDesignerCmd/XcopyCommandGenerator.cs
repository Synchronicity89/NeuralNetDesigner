using System;
using System.IO;

namespace NeuralNetDesignerCmd
{
    public class XCopyCommandGenerator
    {
        public static string GenerateXCopyCommand(string sourcePath, string targetPath, string workingDirectory)
        {
            // Get the full paths in case relative paths are provided
            string fullSourcePath = Path.GetFullPath(sourcePath, workingDirectory);
            string fullTargetPath = Path.GetFullPath(targetPath, workingDirectory);

            // Generate relative paths from the working directory
            string relativeSourcePath = Path.GetRelativePath(workingDirectory, fullSourcePath);
            string relativeTargetPath = Path.GetRelativePath(workingDirectory, fullTargetPath);

            // Construct the xcopy command
            string xcopyCommand = $"xcopy \"{relativeSourcePath}\" \"{relativeTargetPath}\" /Y";

            return xcopyCommand;
        }
    }
}