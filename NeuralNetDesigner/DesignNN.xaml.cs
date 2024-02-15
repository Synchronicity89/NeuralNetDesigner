using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.IO;
using DeepLearning;
using NeuralNetDesignerLib;

namespace NeuralNetDesigner
{
    /// <summary>
    /// Interaction logic for DesignNN.xaml
    /// </summary>
    public partial class DesignNN : Window
    {
        public DesignNN()
        {
            InitializeComponent();
        }

        string defaultConfigPath =
            Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "defaultConfig.dist");
        string defaultWeightsPath =
            Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "defaultWeights.json");

        string defaultConfigDist = @"
{
	""topology"": [ 71, 51, 31, 51, 71 ],
	""learningRate"": 0.09,
	""momentum"": 1.0,
	""bias"": 1.0,
	""epoch"": 100,
	""trainingFile"": ""X_training.csv"",
	""labelsFile"": ""Y_Labels.csv"",
	""weightsFile"": ""ChessGame.json"",
	""hActivation"": 2,
	""oActivation"": 2
}";
        private void Grid_Loaded(object sender, RoutedEventArgs e)
        {
            if (File.Exists(defaultConfigPath))
            {
                // Read the default config file
                txtConfigDist.Text = File.ReadAllText(defaultConfigPath);
            }
            else
            {
                txtConfigDist.Text = defaultConfigDist;
            }
        }


        private void btnSetProjectPath_Click(object sender, RoutedEventArgs e)
        {
            if(string.IsNullOrEmpty(txtProjectPath.Text) || !File.Exists(txtProjectPath.Text))
            {
                MainWindow.BrowseForFilename(Environment.SpecialFolder.MyDocuments.ToString(), (p) => txtProjectPath.Text = p, ".nnd", false);
                string configContent;
                string xTrainingFile;
                string yLabelsFile;
                // unzip the project file in memory and use out parameters to get the config file and the training and label data file names
                Tools.UnzipProject(txtProjectPath.Text, out configContent, out xTrainingFile, out yLabelsFile);
                txtConfigDist.Text = configContent;
                txtXTraining.Text = xTrainingFile;
                if (!string.IsNullOrEmpty(txtXTraining.Text))
                    lblSizeXTraining.Content = $"Size: {new FileInfo(txtXTraining.Text).Length} bytes";
                txtYLabels.Text = yLabelsFile;
                if (!string.IsNullOrEmpty(txtYLabels.Text))
                    lblSizeYLabels.Content = $"Size: {new FileInfo(txtYLabels.Text).Length} bytes";
            }
            else
                MainWindow.BrowseForFilename(Environment.SpecialFolder.MyDocuments.ToString(), (p) => txtProjectPath.Text = p, ".nnd", true);
        }

        private void btnSaveProject_Click(object sender, RoutedEventArgs e)
        {
            Tools.AddEntryToZip(txtProjectPath.Text, "config.dist", txtConfigDist.Text);

            if (!ValidateOrAddEntry(txtXTraining, Tools.GetEntryNameFromConfig(txtConfigDist.Text, "trainingFile")) && 
                !ValidateOrAddEntry(txtYLabels, Tools.GetEntryNameFromConfig(txtConfigDist.Text, "labelsFile")))
                    return;
        }

        private bool ValidateOrAddEntry(TextBox textBox, string entryName)
        {
            bool success = true;
            string name = (new FileInfo(textBox.Text)).Name.ToLower();
            if (string.IsNullOrEmpty(textBox.Text) || !File.Exists(textBox.Text))
            {
                MessageBox.Show($"Please select the {textBox.Name} data file");
                success = false;
            }
            else
            {
                // if the lower case of the training data file name is not found in lower case of the config information in the txtConfigDist
                // then show a warning MessageBox and return (except for temp files)
                if (!txtConfigDist.Text.ToLower().Contains(name.ToLower()) && !textBox.Text.ToLower().Contains("temp"))
                {
                    MessageBoxResult result = 
                        MessageBox.Show($"The {textBox.Name} data file name is not found in the config file.  Press OK to proceed, Cancel to cancel.", 
                        "Warning", MessageBoxButton.OKCancel);
                    success = result == MessageBoxResult.OK? true : false;
                    if (!success)
                        return success;
                }
                Tools.AddEntryToZip(txtProjectPath.Text, entryName, textBox.Text, true);
            }

            return success;
        }

        private void btnTrain_Click(object sender, RoutedEventArgs e)
        {
            //TODO: get the training and label data from the zip file listed in the project path. Some redundancy here
            // The file names are in the config file and if the training and label data files have the same name in the config
            // then network type is autoencoder, and the label data is the same as the training data. TODO: such autoencoder use not tested yet

            // TODO: probably redundant: read the CSV training data out of the zip file into a temporary file with a unique name
            txtXTraining.Text = ExtractEntryToTempFile("trainingFile");
            lblSizeXTraining.Content = $"Size: {new FileInfo(txtXTraining.Text).Length} bytes";
            // TODO: probably redundant: read the CSV label data out of the zip file into a temporary file with a unique name
            txtYLabels.Text = ExtractEntryToTempFile("labelsFile");
            lblSizeYLabels.Content = $"Size: {new FileInfo(txtYLabels.Text).Length} bytes";

            if (!string.IsNullOrEmpty(txtXTraining.Text) && File.Exists(txtXTraining.Text))
            {
                //List<List<double>> xtrain = Tools.ReadCSV(txtXTraining.Text);
                //List<List<double>> ylabels = Tools.ReadCSV(txtYLabels.Text);
                string weights = null;
                DeepNetwork deepLearning = new DeepNetwork();

                // call the Train method of the DeepNetwork class
                deepLearning.Train(txtXTraining.Text, txtYLabels.Text, txtConfigDist.Text);
            }
        }
        private void PasteExecuted(object sender, ExecutedRoutedEventArgs e)
        {
            // Do something with the pasted text, such as validating or formatting it
            string text = Clipboard.GetText();
            ((TextBox)sender).Text = text;
        }
        private string ExtractEntryToTempFile(string entryKey)
        {
            string entryFile = Tools.GetEntryNameFromConfig(txtConfigDist.Text, entryKey);
            string entryTempFile = Tools.ExtractEntryToTempFile(txtProjectPath.Text, entryFile);
            return entryTempFile;
        }

        private void btnOpenXTrainingPath_Click(object sender, RoutedEventArgs e)
        {
            TextBox textBox = txtXTraining;
            if (string.IsNullOrEmpty(textBox.Text) || !File.Exists(textBox.Text))
            {
                MainWindow.BrowseForFilename(Environment.SpecialFolder.MyDocuments.ToString(), (p) => textBox.Text = p, ".csv", true);
            }
            else
                MainWindow.BrowseForFilename(Environment.SpecialFolder.MyDocuments.ToString(), (p) => textBox.Text = p, ".csv", false);

        }

        private void btnOpenYLabelsPath_Click(object sender, RoutedEventArgs e)
        {
            TextBox textBox = txtYLabels;
            if (string.IsNullOrEmpty(textBox.Text) || !File.Exists(textBox.Text))
            {
                MainWindow.BrowseForFilename(Environment.SpecialFolder.MyDocuments.ToString(), (p) => textBox.Text = p, ".csv", true);
            }
            else
                MainWindow.BrowseForFilename(Environment.SpecialFolder.MyDocuments.ToString(), (p) => textBox.Text = p, ".csv", false);

        }

        private void btnOpenProject_Click(object sender, RoutedEventArgs e)
        {
            MainWindow.BrowseForFilename(Environment.SpecialFolder.MyDocuments.ToString(), (p) => txtProjectPath.Text = p, ".nnd", true);
            // Extract the config file from the project zip file
            // TODO: extract it a string directly from the zip file, though there is a chance that this is actually quite efficient
            txtConfigDist.Text = File.ReadAllText(Tools.ExtractEntryToTempFile(txtProjectPath.Text, "config.dist"));
            txtXTraining.Text = ExtractEntryToTempFile("trainingFile");
            lblSizeXTraining.Content = $"Size: {new FileInfo(txtXTraining.Text).Length} bytes";
            txtYLabels.Text = ExtractEntryToTempFile("labelsFile");
            lblSizeYLabels.Content = $"Size: {new FileInfo(txtYLabels.Text).Length} bytes";
        }
    }
}
