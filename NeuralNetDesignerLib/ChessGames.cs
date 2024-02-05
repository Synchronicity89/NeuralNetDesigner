using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;


namespace NeuralNetDesignerLib
{
    internal class ChessGames
    {
        private static readonly HttpClient client = new HttpClient();

        // Method to download chess games
        public static async Task DownloadChessGames(string url, string outputPath)
        {
            HttpResponseMessage response = await client.GetAsync(url);
            response.EnsureSuccessStatusCode();
            string responseBody = await response.Content.ReadAsStringAsync();

            // Write the data to a file
            System.IO.File.WriteAllText(outputPath, responseBody);
        }

        // Method to convert PGN to double representation
        public static List<double> ConvertPGNToDouble(string pgnData)
        {
            List<double> gameDataAsDoubles = new List<double>();

            // Parsing PGN data and converting to double representation
            // Implement the parsing logic here

            return gameDataAsDoubles;
        }

        // Main method for demonstration
        static async Task Download(string[] args)
        {
            string url = "https://lichess.org/api/games/user/username"; // Replace with actual URL
            string outputPath = "chess_games.pgn";

            await DownloadChessGames(url, outputPath);

            string pgnData = System.IO.File.ReadAllText(outputPath);
            List<double> encodedData = ConvertPGNToDouble(pgnData);

            // Further processing for neural network input
        }
    }
}
