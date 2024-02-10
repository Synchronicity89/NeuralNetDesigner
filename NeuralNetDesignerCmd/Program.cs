// See https://aka.ms/new-console-template for more information
using NeuralNetDesignerCmd;
using NeuralNetDesignerLib;
using TimHanewich.Chess;

Console.WriteLine("Functional Tests for NeuralNetDesignerLib");
Console.WriteLine("=========================================");

Console.WriteLine();

Console.WriteLine("Tests for enum conversion to board position flat index");

Console.WriteLine();

// verify that when an enum value is converted to a board position flat index, the correct index is returned
ChessGameCompressor chessGameCompressor = new ChessGameCompressor();
int flatIndex = chessGameCompressor.GetFlatPositionIndex(Position.A1.ToString());
Console.WriteLine($"Expected index: {0}, Actual index: {flatIndex}");

flatIndex = chessGameCompressor.GetFlatPositionIndex(Position.B2.ToString());
Console.WriteLine($"Expected index: {9}, Actual index: {flatIndex}");

flatIndex = chessGameCompressor.GetFlatPositionIndex(Position.C3.ToString());
Console.WriteLine($"Expected index: {18}, Actual index: {flatIndex}");

flatIndex = chessGameCompressor.GetFlatPositionIndex(Position.H8.ToString());
Console.WriteLine($"Expected index: {63}, Actual index: {flatIndex}");

flatIndex = chessGameCompressor.GetFlatPositionIndex(Position.G7.ToString());
Console.WriteLine($"Expected index: {54}, Actual index: {flatIndex}");


// double check that BoardRepresentation is based on column offset by row and not the row offset by column
Console.WriteLine("Tests for BoardRepresentation");

Console.WriteLine();

// verify that when a board position is converted to a board representation, the correct representation is returned
BoardPosition boardPosition = new BoardPosition();
boardPosition.AddPiece(new Piece(Color.White, PieceType.Rook, Position.E2));
boardPosition.AddPiece(new Piece(Color.Black, PieceType.Pawn, Position.E7));
boardPosition.AddPiece(new Piece(Color.White, PieceType.Pawn, Position.D2));
//enough pieces, no need to add more.  Export the position as an array of integers and double check that the board representation is correct
int[] boardRepresentation = boardPosition.BoardRepresentation();

// verify that the board representation is correct in column offset by row order
Console.WriteLine("Expected board representation:");

// Get the column offset by row flat board position index of E2, E7, and D2   
int e2 = chessGameCompressor.GetFlatPositionIndex(Position.E2.ToString());
int e7 = chessGameCompressor.GetFlatPositionIndex(Position.E7.ToString());
int d2 = chessGameCompressor.GetFlatPositionIndex(Position.D2.ToString());

// Note that the Position for the actual pieces is not set correctly and defaults to A1.
// This apparently is by design, and has to be worked around, and doesn't represent a bug in the code.
Console.WriteLine($"Expected index and piece: {e2}, {new Piece(Color.White, PieceType.Rook, Position.E2).ToMeaningfulString()}, Actual piece: {Piece.FromCode(boardRepresentation[e2]).ToMeaningfulString()}");
Console.WriteLine($"Expected index and piece: {e7}, {new Piece(Color.Black, PieceType.Pawn, Position.E7).ToMeaningfulString()}, Actual piece: {Piece.FromCode(boardRepresentation[e7]).ToMeaningfulString()}");
Console.WriteLine($"Expected index and piece: {d2}, {new Piece(Color.White, PieceType.Pawn, Position.D2).ToMeaningfulString()}, Actual piece: {Piece.FromCode(boardRepresentation[d2]).ToMeaningfulString()}");


string source = @"C:\Users\baker\source\repos\NeuralNetDesigner\x64\Debug\AnnDll.*";
string target = @"C:\Users\baker\source\repos\NeuralNetDesigner\NeuralNetDesigner\bin\Debug\net8.0-windows";
string workingDirectory = @"C:\Users\baker\source\repos\NeuralNetDesigner\AnnDll";

string deepLearningTarget = @"C:\Users\baker\source\repos\NeuralNetDesigner\NeuralNetDesignerLib\bin\Debug\net8.0";

string xcopyCommand = XCopyCommandGenerator.GenerateXCopyCommand(source, target, workingDirectory);
Console.WriteLine(xcopyCommand);
xcopyCommand = XCopyCommandGenerator.GenerateXCopyCommand(source, deepLearningTarget, workingDirectory);
Console.WriteLine(xcopyCommand);
