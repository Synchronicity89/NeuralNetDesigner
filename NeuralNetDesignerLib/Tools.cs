using System;
using System.Collections.Generic;
using System.IO.Compression;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NeuralNetDesignerLib
{
    public class Tools
    {
        // A function that adds a new entry to an existing or a new zip archive
        public static void AddEntryToZip(string zipPath, string entryName, string entryContent, bool entryContentIsPath = false)
        {
            // Check if the zip file exists
            if (!File.Exists(zipPath))
            {
                // Create a new zip file
                using (var zipFile = ZipFile.Open(zipPath, ZipArchiveMode.Create))
                {
                    // Create and write the new entry
                    CreateEntry(entryName, entryContent, entryContentIsPath, zipFile);
                }
            }
            else
            {
                // Open the existing zip file to update
                using (var zipFile = ZipFile.Open(zipPath, ZipArchiveMode.Update))
                {
                    // Delete the existing entry if any
                    DeleteEntryIfExists(zipFile, entryName);

                    CreateEntry(entryName, entryContent, entryContentIsPath, zipFile);
                }
            }
        }

        private static void CreateEntry(string entryName, string entryContent, bool entryContentIsPath, ZipArchive zipFile)
        {
            if (entryContentIsPath)
            {
                // Write the content of the file to the entry
                zipFile.CreateEntryFromFile(entryContent, entryName);
            }
            else
            {
                CreateAndWriteEntry(zipFile, entryName, entryContent);
            }
        }

        // A helper function that creates a new entry and writes some content to it
        private static void CreateAndWriteEntry(ZipArchive zipFile, string entryName, string entryContent)
        {
            // Create a new entry with the name and the optimal compression level
            var newEntry = zipFile.CreateEntry(entryName, CompressionLevel.Optimal);

            // Write some content to the entry using a stream
            using (var entryStream = newEntry.Open())
            using (var streamWriter = new StreamWriter(entryStream))
            {
                streamWriter.Write(entryContent);
            }
        }

        // A helper function that deletes an existing entry if it exists
        private static void DeleteEntryIfExists(ZipArchive zipFile, string entryName)
        {
            // Check if the entry already exists
            var existingEntry = zipFile.Entries.FirstOrDefault(e => e.FullName.ToLower() == entryName.ToLower());
            if (existingEntry != null)
            {
                // Delete the existing entry
                existingEntry.Delete();
            }
        }

        public static List<List<double>> ReadCSV(string filePath)
        {
            // Read the content of the file
            string[] lines = File.ReadAllLines(filePath);

            // Parse the content of the file
            List<List<double>> data = new List<List<double>>();
            foreach (string line in lines)
            {
                // Split the line into a list of strings
                string[] values = line.Split(',');

                // Convert the list of strings to a list of doubles
                List<double> row = values.Select(v => double.Parse(v)).ToList();

                // Add the list of doubles to the list of lists of doubles
                data.Add(row);
            }

            return data;
        }

        public static void UnzipProject(string text, out string configContent, out string xTrainingFile, out string yLabelsFile)
        {
            // Initialize the out parameters
            configContent = null;
            xTrainingFile = null;
            yLabelsFile = null;

            // Check if the file exists
            if (!File.Exists(text))
            {
                return;
            }

            // Open the zip file
            using (var zipFile = ZipFile.OpenRead(text))
            {
                // Get the config file entry
                var configEntry = zipFile.Entries.FirstOrDefault(e => e.FullName.ToLower() == "config.dist");
                if (configEntry != null)
                {
                    // Read the content of the config file
                    using (var configStream = configEntry.Open())
                    using (var streamReader = new StreamReader(configStream))
                    {
                        configContent = streamReader.ReadToEnd();
                    }
                    // Extract the training and label data file names from the config file
                    //find the index of "trainingFile": in the configContent, and read the quoted string after it
                    string xTrainingEntryPath = GetEntryNameFromConfig(configContent, "trainingFile");

                    // Get the training data file entry
                    var xTrainingEntry = zipFile.Entries.FirstOrDefault(e => e.FullName.ToLower() == xTrainingEntryPath.ToLower());
                    if (xTrainingEntry != null)
                    {
                        xTrainingFile = xTrainingEntry.FullName;
                    }

                    // Get the label data file entry

                    string yLabelsEntryPath = GetEntryNameFromConfig(configContent, "labelsFile");
                    var yLabelsEntry = zipFile.Entries.FirstOrDefault(e => e.FullName.ToLower() == yLabelsEntryPath.ToLower());
                    if (yLabelsEntry != null)
                    {
                        yLabelsFile = yLabelsEntry.FullName;
                    }
                }
            }
        }

        public static string GetEntryNameFromConfig(string configContent, string target)
        {
            // Find the index of the target string
            int index = configContent.ToLower().IndexOf(target.ToLower());
            if (index == -1)
            {
                return null;
            }
            index += target.Length + 1;
            // Find the index of the first quote after the target string
            int quoteIndex = configContent.IndexOf('"', index);
            if (quoteIndex == -1)
            {
                return null;
            }

            // Find the index of the second quote after the target string
            int secondQuoteIndex = configContent.IndexOf('"', quoteIndex + 1);
            if (secondQuoteIndex == -1)
            {
                return null;
            }

            // Extract the quoted string
            string entryName = configContent.Substring(quoteIndex + 1, secondQuoteIndex - quoteIndex - 1);
            return entryName;
        }

        public static string ExtractEntryToTempFile(string text, string entryFile)
        {
            string entryTempFile;
            // Create a temporary file with a unique name
            entryTempFile = Path.GetTempFileName();
            
            // Open the zip file
            using (var zipFile = ZipFile.OpenRead(text))
            {
                // Get the training data file entry
                var entry = zipFile.Entries.FirstOrDefault(e => e.FullName.ToLower() == entryFile.ToLower());
                if (entry != null)
                {
                    int size = (int)entry.Length;
                    // Extract the training data file to the temporary file
                    entry.ExtractToFile(entryTempFile, true);
                    //throw an exception if the file is not the same size as the entry
                    if (new FileInfo(entryTempFile).Length != size)
                    {
                        throw new Exception("Error extracting file");
                    }
                }
                else
                {
                    throw new Exception("Error extracting file");
                }
            }
            return entryTempFile;
        }
    }
}
