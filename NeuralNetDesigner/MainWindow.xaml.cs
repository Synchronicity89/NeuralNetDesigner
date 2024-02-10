using DeepLearning;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using TimHanewich.Chess.PGN;
using TimHanewich.Chess;
using NeuralNetDesignerLib;
using System.IO.Compression;
using System.IO;
using System.Net;
using System.Net.Http;

namespace NeuralNetDesigner
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        // function to convert Piece type to NeuralNetDesignerLib.Piece enum,
        // using a switch statement to set a variable of type NeuralNetDesignerLib.Piece
        // to the appropriate value based on the input Piece type
        // then add 8 to the value of the variable if the piece is white
        private NeuralNetDesignerLib.ChessPiece ConvertPieceType(Piece piece)
        {
            NeuralNetDesignerLib.ChessPiece pieceType;
            switch (piece.Type)
            {
                case PieceType.Pawn:
                    pieceType = NeuralNetDesignerLib.ChessPiece.B_Pawn;
                    break;
                case PieceType.Knight:
                    pieceType = NeuralNetDesignerLib.ChessPiece.B_Knight;
                    break;
                case PieceType.Bishop:
                    pieceType = NeuralNetDesignerLib.ChessPiece.B_Bishop;
                    break;
                case PieceType.Rook:
                    pieceType = NeuralNetDesignerLib.ChessPiece.B_Rook;
                    break;
                case PieceType.Queen:
                    pieceType = NeuralNetDesignerLib.ChessPiece.B_Queen;
                    break;
                case PieceType.King:
                    pieceType = NeuralNetDesignerLib.ChessPiece.B_King;
                    break;
                default:
                    pieceType = 0;
                    break;
            }
            if (piece.Color == TimHanewich.Chess.Color.White)
            {
                pieceType += 8;
            }
            return pieceType;
        }


        private void Grid_Loaded(object sender, RoutedEventArgs e)
        {

        }

        private void btnDownload_Click(object sender, RoutedEventArgs e)
        {

            string url = txtChessDatabase.Text;
            byte[] response = null;
            // Download the zip file to a local file
            using (var webClient = new HttpClient())
            {
                response = webClient.GetByteArrayAsync(url).Result;
            }
            //create a memory stream from the byte array and pass it to the ZipArchive class
            using (MemoryStream stream = new MemoryStream(response))
            {
                using (ZipArchive archive = new ZipArchive(stream))
                {

                    // Create a memory stream for the entry
                    using (var entryStream = new MemoryStream())
                    {
                        // Copy the entry content to the memory stream
                        using (var zipStream = archive.Entries[0].Open())
                        {
                            zipStream.CopyTo(entryStream);
                        }
                        // write the memory stream zipStream to disk
                        File.WriteAllBytes("chess_games.pgn", entryStream.ToArray());
                    }
                }
            }
        }


        // Download the chess games from the URL
        // get the content of the txtDownloadURL textbox and save it to a string variable
        //// download the zip file into memory and unzip it in memory, then write the PGN file to disk
        //ChessGames.DownloadChessGamesZip(url).Wait();


        private void btnProcess_Click(object sender, RoutedEventArgs e)
        {
            //
            Dictionary<string, IEnumerable<BoardPosition>> continuations = new Dictionary<string, IEnumerable<BoardPosition>>();
            List<List<ulong[]>> bitGames = new List<List<ulong[]>>();
            if(chessGameCompressor == null) chessGameCompressor = new ChessGameCompressor();
            var games = chessGameCompressor.SamplesSplit( File.Exists("chess_games.pgn") ? "chess_games.pgn": "");
            foreach (var game in games)
            {
                if(game.ToLower().Contains("chess960") || game.ToLower().Contains("chess 960")) continue;
                string previousFEN = "";
                var board = new BoardPosition(ChessGameCompressor.InitialPosition);
                List<BoardPosition> moves = chessGameCompressor.ParsePGNMoves(game, board);
                foreach (var move in moves)
                {
                    if (continuations.ContainsKey(previousFEN))
                    {
                        continuations[previousFEN] = continuations[previousFEN].Concat(new List<BoardPosition> { move });
                    }
                    else
                    {
                        continuations.Add(previousFEN, new List<BoardPosition> { move });
                    }
                    previousFEN = move.ToFEN();
                }
            }
            var commonContinuations = continuations.Where(x => x.Value.Count() > 1).OrderByDescending(x => x.Value.Count()).ToDictionary(x => x.Key, x => x.Value.OrderBy(p => p.ToFEN()));
            // go through each key in the dictionary, find the most common continuation, 
            // Convert the key FEN to a bitboard to be saved as X training, and the the most value FENs to bitboards to be saved as Y labels

            List<ulong[]> X_training = new List<ulong[]>();
            List<ulong[]> Y_Labels = new List<ulong[]>();
            List<string> X_trainingComment = new List<string>();
            List<string> Y_LabelsComment = new List<string>();

            foreach (var key in commonContinuations.Keys)
            {
                if (string.IsNullOrEmpty(key))
                {
                    continue;
                }
                var keyBoard = new BoardPosition(key);
                var distinctContinuations = commonContinuations[key].Distinct().OrderByDescending(p => commonContinuations[key].Where(cck => cck.ToFEN() == p.ToFEN()).Count());
                var mostCommonContinuation = distinctContinuations.First();
                X_training.Add(chessGameCompressor.GetBitBoard(keyBoard).ToArray());
                Y_Labels.Add(chessGameCompressor.GetBitBoard(mostCommonContinuation).ToArray());
                X_trainingComment.Add(key);
                Y_LabelsComment.Add(mostCommonContinuation.ToFEN());
            }

            //Write X_training and Y_Labels to separate CSV files
            StringBuilder sb = new StringBuilder();
            foreach (var bitboard in X_training)
            {
                sb.AppendLine(string.Join(",", bitboard.Select(bb => (double)bb / (double)10.0)));
            }
            System.IO.File.WriteAllText("X_training.csv", sb.ToString());

            sb = new StringBuilder();
            foreach (var bitboard in Y_Labels)
            {
                sb.AppendLine(string.Join(",", bitboard.Select(bb => (double)bb / (double)10.0)));
            }
            System.IO.File.WriteAllText("Y_Labels.csv", sb.ToString());

            //Write X_trainingComment and Y_LabelsComment to same CSV file, side by side attach
            // prefix each with "https://lichess.org/analysis/" and replace the spaces in the FENs with "_"
            sb = new StringBuilder();
            for (int i = 0; i < X_trainingComment.Count; i++)
            {
                sb.AppendLine($"https://lichess.org/analysis/{X_trainingComment[i].Replace(" ", "_")}," +
                    $"https://lichess.org/analysis/{Y_LabelsComment[i].Replace(" ", "_")}");
            }
            System.IO.File.WriteAllText("X_training_Y_Labels_Comment.csv", sb.ToString());

        }

        private void btnSelfPlay_Click(object sender, RoutedEventArgs e)
        {
            // for i in range(10):
            for(int i = 0; i < 10; i++)
            {
                // copy the FEN from the prediction textbox to the current FEN textbox
                txtFENCurrent.Text = txtPrediction.Text;
                // clear the prediction textbox
                txtPrediction.Text = "";
                // execute the load weights button click event
                btnLoadWeights_Click(null, null);
                //fetch the saved moves from ChessGameCompressor instance
                var moves = chessGameCompressor.FetchSelfPlayMoves();
                // if there are moves, show them in the txtSelfPlayMoves textbox
                if (moves != null)
                {
                    txtSelfPlayPGN.Text = string.Join(" ", moves);
                }
            }

        }

        private void txtWeightsPath_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void btnBrowseWeights_Click(object sender, RoutedEventArgs e)
        {
            // Create OpenFileDialog
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            
            // Set filter for file extension and default file extension
            dlg.DefaultExt = ".json";
            dlg.Filter = "JSON Files (*.json)|*.json";
            //dlg.DefaultDirectory = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetEntryAssembly().Location);
            // Display OpenFileDialog by calling ShowDialog method
            Nullable<bool> result = dlg.ShowDialog();
            if (result.HasValue)
            {
                   // Get the selected file name and display in a TextBox
                if (result.Value)
                {
                    // Open document
                    string filename = dlg.FileName;
                    txtWeightsPath.Text = filename;
                }
            }
        }
        DeepNetwork network;
        ChessGameCompressor chessGameCompressor = null;
        private void btnLoadWeights_Click(object sender, RoutedEventArgs e)
        {
            if(chessGameCompressor == null) chessGameCompressor = new ChessGameCompressor();
            string weightsPath = txtWeightsPath.Text;
            if (File.Exists(weightsPath))
            {
                var bitBoard = chessGameCompressor.ConvertFENToBitBoard(txtFENCurrent.Text);
                network = new DeepNetwork();
                var bitBoardPrediction = network.LoadWeights(weightsPath, bitBoard.Select(bb => (double)bb).ToList());
                txtPrediction.Text = chessGameCompressor.ConvertBitBoardToFEN(txtFENCurrent.Text, bitBoardPrediction.ToArray());
            }
        }
    }
}