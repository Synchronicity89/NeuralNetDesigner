//using DeepLearning;
using System;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using TimHanewich.Chess;
using TimHanewich.Chess.PGN;
namespace NeuralNetDesignerLib
{
    public enum ChessPiece
    {
        Empty = 0,
        B_Pawn = 1,
        B_Knight = 2,
        B_Bishop = 3,
        B_Rook = 4,
        B_Queen = 5,
        B_King = 6,
        W_Pawn = 1 + 8,
        W_Knight = 2 + 8,
        W_Bishop = 3 + 8,
        W_Rook = 4 + 8,
        W_Queen = 5 + 8,
        W_King = 6 + 8,
    }


    public class ChessGameCompressor
    {
        // Main method to compress a chess game from a PGN string
        //public double[] CompressGameFromPGN(string pgn)
        //{
        //    var moves = ParsePGNMoves(pgn);
        //    return CompressGame(moves);
        //}

        // Parse moves from a PGN string
        public List<BoardPosition> ParsePGNMoves(string pgn, BoardPosition board)
        {
            //var movesList = new List<string>();
            //var matches = Regex.Matches(pgn, @"(\d+\.\s)?([a-h][1-8]|[NBRQK][a-h]?[1-8]?x?[a-h][1-8])\s?([a-h][1-8]|[NBRQK][a-h]?[1-8]?x?[a-h][1-8])?");
            //foreach (Match match in matches)
            //{
            //    if (match.Groups[2].Success) movesList.Add(match.Groups[2].Value);
            //    if (match.Groups[3].Success) movesList.Add(match.Groups[3].Value);
            //}

            var movesList2 = new List<BoardPosition>();
            PgnFile pgnFile = PgnFile.ParsePgn(pgn);
            foreach (var moveString in pgnFile.Moves)
            {
                if (String.IsNullOrEmpty(moveString)) { continue; }
                var move = new Move(moveString, board);
                board.ExecuteMove(move);
                
                movesList2.Add(board.Copy());
            }

            return movesList2;
        }

        // The existing CompressGame method
        public double[] CompressGame(List<string> moves)
        {
            double[] compressedGame = new double[64]; // 64 squares
                                                      // ... existing implementation ...

            return compressedGame;
        }

        // Existing helper methods
        private static bool UpdateSquareHistory(ref Int64 squareHistory, ChessPiece piece)
        {
            bool success = true;
            // ... existing implementation ...
            return success;
        }

        private static int ConvertMoveToSquareIndex(string move)
        {
            int index = 0;
            // ... existing implementation
            return index;
        }

        private static ChessPiece IdentifyPieceFromMove(string move)
        {
            ChessPiece piece = (ChessPiece)(-1); //black pawn
                                                 // ... existing implementation ...
            return piece;
        }

        public string[] SamplesSplit(string path = null)
        {
            if(string.IsNullOrWhiteSpace(path))
            {
                //split the sample PGN into individual games
                string[] games = samplePGN.Split(new string[] { "\r\n[Event" }, StringSplitOptions.RemoveEmptyEntries);

                return games.Select(g => g.StartsWith("[Event") ? g : "[Event" + g).ToArray();
            }
            else
            {
                // load the PGN from the file path
                string pgn = System.IO.File.ReadAllText(path);
                //find all the indicies of where the string "[Event" occurs
                List<int> indicies = new List<int>();
                int index = pgn.IndexOf("[Event ");
                while (index != -1)
                {
                    indicies.Add(index);
                    index = pgn.IndexOf("[Event ", index + 1);
                }
                //split the PGN into individual games
                string[] games = new string[indicies.Count];
                for (int i = 0; i < indicies.Count; i++)
                {
                    if (i == indicies.Count - 1)
                    {
                        games[i] = pgn.Substring(indicies[i]);
                    }
                    else
                    {
                        games[i] = pgn.Substring(indicies[i], indicies[i + 1] - indicies[i]);
                    }
                }
                return games;
            }
        }

        public IEnumerable<ulong> GetBitBoard(BoardPosition move)
        {
            List<ulong> bitBoard = new List<ulong>();
            bitBoard.AddRange(move.BoardRepresentation().Select(br => (ulong)br));

            string enPassantTargetSquare = move.EnPassantTarget.HasValue ?
                Enum.GetName(typeof(Position), move.EnPassantTarget.Value) : "";
            if(!string.IsNullOrEmpty(enPassantTargetSquare))
            {
                int flatIndex = GetFlatPositionIndex(enPassantTargetSquare);
                bitBoard[flatIndex] += 16;
            }
            bitBoard.Add(move.BlackKingSideCastlingAvailable ? 1UL : 0UL);
            bitBoard.Add(move.BlackQueenSideCastlingAvailable ? 1UL : 0UL);
            bitBoard.Add(move.WhiteKingSideCastlingAvailable ? 1UL : 0UL);
            bitBoard.Add(move.WhiteQueenSideCastlingAvailable ? 1UL : 0UL);
            bitBoard.Add(move.IsCheckMate() ? 1UL : 0UL);
            bitBoard.Add((ulong)move.AvailableMoves().Length);
            return bitBoard;
        }

        public int GetFlatPositionIndex(string enPassantTargetSquare)
        {
            // The hard way, it shows that the indexing is based on the column offset by row and not the row offset by column
            int flatIndex = 0;
            if (!string.IsNullOrEmpty(enPassantTargetSquare))
            {
                int column = GetColumnIndex(enPassantTargetSquare[0]);
                int row = int.Parse(enPassantTargetSquare[1].ToString()) - 1;
                flatIndex = GetFlatBoardIndex(row, column);
            }
            else
            {
                //throw Invalid Argument Exception
                flatIndex = 0;
                throw new ArgumentException("Invalid Argument Exception: Position enum incorrect");
            }
            // Now do it the easy way
            int actual = (int) Enum.Parse(typeof(Position), enPassantTargetSquare);
            if (actual != flatIndex)
            {
                throw new ArgumentException("Invalid Argument Exception: unexpected Position enum name");
            }

            return flatIndex;
        }

        public const string InitialPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        public const string columns = "abcdefgh";
        //DeepNetwork deepNetwork;
        BoardPosition selfPlayBoard;
        List<Move?> moves;
        public int GetColumnIndex(char column)
        {
            return columns.IndexOf(char.ToLower(column));
        }

        public int GetFlatBoardIndex(int row, int column)
        {
            return row + column * 8;
        }

        public IEnumerable<ulong> ConvertFENToBitBoard(string fenText)
        {
            string fen = "";
            BoardPosition bp = new BoardPosition(fenText);
            //convert the FEN to a bitboard
            return GetBitBoard(bp);
        }

        public string ConvertBitBoardToFEN(string previousMoveFEN, double[] bitBoard)
        {
            if(moves == null) moves = new List<Move?>();
            // the previous Move FEN is the initial position clear the moves list
            if (previousMoveFEN == InitialPosition)
            {
                moves.Clear();
                selfPlayBoard = new BoardPosition(previousMoveFEN);
            }
            //convert the bitboard to a FEN
            // for now just join the ulong array into a string with a comma between each element.  2 decimal places max per element
            //return string.Join(",", bitBoard.Select(ul => ul.ToString("F4")));

            //convert the bitboard to a FEN
            // How to choose a move that the predicted bitboard represents?
            // 1.  Use the previous move FEN to create a BoardPosition
            BoardPosition previousMove = new BoardPosition(previousMoveFEN);

            // The problem is that some of the predicted bitboard values are not valid for a BoardPosition
            // So, loop through the legal moves from the previousMove and compare the bitboard to the bitboard of the legal move, using a cost function
            // The cost function will be the sum of the absolute differences between the bitboard values
            // The lowest cost will be the move that was made

            // create a scaled and biased version of the predicted bitboard that more closely matches the board position of the previous move
            var bitBoardPrev = GetBitBoard(previousMove);
            var bitBoardPrevDoubles = bitBoardPrev.Select(ul => (double)ul).ToArray();
            // use gradient descent to bias first and then scale the predicted bitboard to match the previous move bitboard
            // the cost function is the sum of the absolute differences between the predicted bitboard and the previous move bitboard
            // the gradient is the sign of the difference between the predicted bitboard and the previous move bitboard
            // the learning rate is 0.1
            double learningRate = 0.1;
            // the bias and scale are initialized to 0 and 1 respectively
            double bias = 0;
            double scale = 1;
            // the bias and scale are updated by subtracting the learning rate times the gradient
            // the learning rate is halved every 1000 iterations
            // the process is repeated until the cost function is less than 0.1
            int iterations = 0;
            double cost = 0;
            // the predicted bitboard is then scaled and biased by the final bias and scale

            // calculate the range of previousMove bitboard values
            double minPreviousMove = double.MaxValue;
            double maxPreviousMove = double.MinValue;
            for (int i = 0; i < 64; i++)
            {
                if (bitBoardPrevDoubles[i] < minPreviousMove) minPreviousMove = bitBoardPrevDoubles[i];
                if (bitBoardPrevDoubles[i] > maxPreviousMove) maxPreviousMove = bitBoardPrevDoubles[i];
            }
            // Do the same for the predicted bitboard
            double minPredicted = double.MaxValue;
            double maxPredicted = double.MinValue;
            for (int i = 0; i < 64; i++)
            {
                if (bitBoard[i] < minPredicted) minPredicted = bitBoard[i];
                if (bitBoard[i] > maxPredicted) maxPredicted = bitBoard[i];
            }

            // scale the predicted bitboard to the range of the previousMove bitboard
            double rangePreviousMove = maxPreviousMove - minPreviousMove;
            double rangePredicted = maxPredicted - minPredicted;
            double scalePredicted = rangePreviousMove / rangePredicted;
            double biasPredicted = minPreviousMove - minPredicted * scalePredicted;
            var bitBoardSB = bitBoard.Select(ul => ((double)ul) * scalePredicted).ToArray();
            var averageBBSB = bitBoardSB.Average();
            var averageBBPrev = bitBoardPrevDoubles.Average();
            //subtract the averages to get the bias
            bias = averageBBPrev - averageBBSB;
            scale = scalePredicted;

            // the scaled and biased predicted bitboard is then compared to the bitboards of the legal moves from the previous move as follows

            bitBoardSB = bitBoard.Select(ul => ((double)ul + bias) * scale).ToArray();

            // the scaled and biased predicted bitboard is then compared to the bitboards of the legal moves from the previous move as follows

            double lowestCost = double.MaxValue;
            BoardPosition bestMove = null;
            Move? bestM = default(Move?);
            foreach (var move in previousMove.AvailableMoves())
            {
                BoardPosition movePosition = previousMove.Copy();
                movePosition.ExecuteMove(move);
                double cost2 = 0;
                var bitBoard2 = GetBitBoard(movePosition);
                for (int i = 0; i < bitBoardSB.Length; i++)
                {
                    cost2 += Math.Abs((double)bitBoardSB[i] - (double)bitBoard2.ElementAt(i));
                }
                if (cost2 < lowestCost)
                {
                    lowestCost = cost2;
                    bestMove = movePosition;
                    bestM = move;
                }
            }
            if (bestM != null) selfPlayBoard.ExecuteMove(bestM);
            moves.Add(bestM);
            //return the FEN of the best move
            return bestMove != null ? bestMove.ToFEN() : "No legal move found";
        }

        public List<Move?> FetchSelfPlayMoves()
        {
            return moves;
        }
        private string samplePGN = @"
[Event ""81st Tata Steel GpA""]
[Site ""Wijk aan Zee NED""]
[Date ""2019.01.12""]
[Round ""1.1""]
[White ""Ding Liren""]
[Black ""Carlsen,M""]
[Result ""1/2-1/2""]
[WhiteTitle ""GM""]
[BlackTitle ""GM""]
[WhiteElo ""2813""]
[BlackElo ""2835""]
[ECO ""A05""]
[Opening ""Reti""]
[Variation ""King's Indian attack, Spassky's variation""]
[EventDate ""2019.01.12""]
[WhiteFideId ""8603677""]
[BlackFideId ""1503014""]

1. Nf3 Nf6 2. g3 b5 3. d4 e6 4. Bg5 c5 5. d5 Qa5+ 6. Bd2 Qb6 7. dxe6 fxe6
8. a4 b4 9. a5 Qd8 10. Bg2 Nc6 11. Ne5 Nxe5 12. Bxa8 d5 13. a6 Bd7 14. Bb7
Bd6 15. Bg5 Nf7 16. Bxf6 Qxf6 17. Nd2 O-O 18. O-O Qxb2 19. e4 Qd4 20. exd5
e5 21. Nb3 Qe4 22. Qd3 Qg4 23. f3 Qh5 24. Nd2 Ng5 25. Bc6 Bh3 26. Bb5 Bxf1
27. Rxf1 Rxf3 28. Nxf3 e4 29. Qe3 Nxf3+ 30. Rxf3 Qxf3 31. Qxf3 exf3 32. Kf2
1/2-1/2

[Event ""81st Tata Steel GpA""]
[Site ""Wijk aan Zee NED""]
[Date ""2019.01.12""]
[Round ""1.2""]
[White ""Giri,A""]
[Black ""Nepomniachtchi,I""]
[Result ""0-1""]
[WhiteTitle ""GM""]
[BlackTitle ""GM""]
[WhiteElo ""2783""]
[BlackElo ""2763""]
[ECO ""B07""]
[Opening ""Pirc defence""]
[EventDate ""2019.01.12""]
[WhiteFideId ""24116068""]
[BlackFideId ""4168119""]

1. e4 d6 2. d4 Nf6 3. Nc3 g6 4. Be3 a6 5. Qd2 b5 6. f3 Nbd7 7. O-O-O Nb6 8.
g4 Bb7 9. Nh3 Nfd7 10. Be2 e6 11. Bg5 Be7 12. Qe3 Bxg5 13. Nxg5 h6 14. Nh3
Qh4 15. Nf2 O-O-O 16. f4 f5 17. Bf3 b4 18. exf5 bxc3 19. fxe6 cxb2+ 20. Kb1
Nf6 21. Bxb7+ Kxb7 22. Qf3+ d5 23. Nd3 Ne4 24. Nc5+ Ka7 25. Qa3 Nxc5 26.
Qxc5 Kb7 0-1

[Event ""81st Tata Steel GpA""]
[Site ""Wijk aan Zee NED""]
[Date ""2019.01.12""]
[Round ""1.3""]
[White ""Fedoseev,Vl3""]
[Black ""Rapport,R""]
[Result ""1/2-1/2""]
[WhiteTitle ""GM""]
[BlackTitle ""GM""]
[WhiteElo ""2724""]
[BlackElo ""2731""]
[ECO ""E12""]
[Opening ""Queen's Indian""]
[Variation ""Petrosian system""]
[EventDate ""2019.01.12""]
[WhiteFideId ""24130737""]
[BlackFideId ""738590""]

1. d4 Nf6 2. Nf3 e6 3. c4 b6 4. a3 Bb7 5. Nc3 Ne4 6. Nxe4 Bxe4 7. Nd2 Bb7
8. e4 g6 9. Bd3 Bg7 10. Nf3 O-O 11. O-O d6 12. Rb1 Nd7 13. Bg5 Qc8 14. Re1
Re8 15. Qd2 c5 16. d5 exd5 17. exd5 Qc7 18. Kh1 Ba6 19. b3 Nf6 20. h3 Rxe1+
21. Rxe1 Re8 22. Rxe8+ Nxe8 23. g4 Qd7 24. Kg2 Nc7 25. a4 Bc8 26. Qe3 Ne8
27. Kf1 Bf6 28. Bf5 gxf5 29. Bxf6 fxg4 30. hxg4 Nxf6 31. Qg5+ Kf8 32. Qxf6
Qxg4 33. Qxd6+ Kg7 34. Qe5+ f6 35. Qe7+ Kg6 36. Qe8+ Kg7 37. Qe7+ Kg6 38.
Qe8+ Kg7 39. Qe7+ 1/2-1/2

[Event ""81st Tata Steel GpA""]
[Site ""Wijk aan Zee NED""]
[Date ""2019.01.12""]
[Round ""1.6""]
[White ""Shankland,S""]
[Black ""Mamedyarov,S""]
[Result ""1/2-1/2""]
[WhiteTitle ""GM""]
[BlackTitle ""GM""]
[WhiteElo ""2725""]
[BlackElo ""2817""]
[ECO ""C42""]
[Opening ""Petrov's defence""]
[EventDate ""2019.01.12""]
[WhiteFideId ""2004887""]
[BlackFideId ""13401319""]

1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. Bd3 Nf6 6. O-O Be7 7. c3 O-O
8. Bc2 c5 9. d4 Be6 10. Re1 Re8 11. Bg5 Nbd7 12. Nbd2 Qb6 13. dxc5 dxc5 14.
Bb3 Nf8 15. Bxe6 Nxe6 16. Qb3 Qxb3 17. axb3 Nxg5 18. Nxg5 a6 19. g3 Rad8
20. Nc4 h6 21. Nf3 Kf8 22. Kf1 Bd6 23. Na5 Rb8 24. Rxe8+ Kxe8 25. Re1+ Kf8
26. Rd1 Ke7 27. Ne1 Bc7 28. Nc4 b5 29. Ne3 g6 30. Nd3 Bd6 31. Ra1 Rb6 32.
c4 b4 33. Ke2 Ke6 34. Ra5 Rc6 35. Nd5 Nd7 36. f4 f5 37. Kf3 Nf6 38. Ra1
Nxd5 39. Re1+ Ne3 40. Rxe3+ Kd7 41. g4 fxg4+ 42. Kxg4 Rc8 43. Rh3 Rh8 44.
Kf3 Ke6 45. Ke4 Kf6 46. Ne5 Re8 47. Rf3 Bb8 48. h4 a5 49. Rf1 h5 50. Rf3
Bc7 51. Rf1 Rd8 52. Nf3 Re8+ 53. Ne5 Rd8 54. Nf3 Re8+ 1/2-1/2

[Event ""81st Tata Steel GpA""]
[Site ""Wijk aan Zee NED""]
[Date ""2019.01.12""]
[Round ""1.7""]
[White ""Radjabov,T""]
[Black ""Kramnik,V""]
[Result ""1/2-1/2""]
[WhiteTitle ""GM""]
[BlackTitle ""GM""]
[WhiteElo ""2757""]
[BlackElo ""2777""]
[ECO ""C50""]
[Opening ""Giuoco Piano""]
[EventDate ""2019.01.12""]
[WhiteFideId ""13400924""]
[BlackFideId ""4101588""]

1. e4 e5 2. Nf3 Nc6 3. Bc4 Bc5 4. O-O Nf6 5. d3 d6 6. c3 a6 7. a4 O-O 8.
Re1 Ba7 9. h3 h6 10. Nbd2 Re8 11. b4 Be6 12. Bxe6 Rxe6 13. Bb2 Ne7 14. c4
Ng6 15. Nf1 b5 16. axb5 axb5 17. Ng3 bxc4 18. dxc4 Re8 19. Qc2 Qb8 20. Reb1
Qb7 21. c5 dxc5 22. bxc5 Qc6 23. Rc1 Nd7 24. Ra5 Reb8 25. Ba3 Nf4 26. Nf5
Re8 27. g3 Ne6 28. Kg2 Nf6 29. Re1 Nd7 30. Rc1 Kh7 31. Qc4 Bxc5 32. Rxc5
Ndxc5 33. Bxc5 Ra4 34. Qd5 Qa8 35. Qd7 Kg8 36. Nxe5 Ng5 37. Nc6 Raxe4 38.
Nfe7+ Kh7 39. Ra1 Ra4 40. Rxa4 Qxa4 41. Qxe8 Qe4+ 42. Kf1 Qb1+ 43. Kg2
1/2-1/2

[Event ""81st Tata Steel GpA""]
[Site ""Wijk aan Zee NED""]
[Date ""2019.01.13""]
[Round ""2.1""]
[White ""Carlsen,M""]
[Black ""Nepomniachtchi,I""]
[Result ""1/2-1/2""]
[WhiteTitle ""GM""]
[BlackTitle ""GM""]
[WhiteElo ""2835""]
[BlackElo ""2763""]
[ECO ""E60""]
[Opening ""King's Indian defence""]
[EventDate ""2019.01.12""]
[WhiteFideId ""1503014""]
[BlackFideId ""4168119""]

1. d4 Nf6 2. c4 g6 3. f3 e6 4. e4 c5 5. d5 d6 6. Nc3 Bg7 7. Nge2 exd5 8.
cxd5 a6 9. a4 O-O 10. Ng3 Nbd7 11. Be2 Ne8 12. Bf4 Rb8 13. O-O c4 14. Bxc4
Qb6+ 15. Rf2 Bd4 16. Qd2 Ne5 17. Bf1 Bxf2+ 18. Qxf2 Qxf2+ 19. Kxf2 Bd7 20.
Be3 f5 21. exf5 gxf5 22. Bd4 Nf6 23. Kg1 Rbc8 24. Ra3 Nc4 25. Rb3 b5 26.
axb5 Nd2 27. Rb4 Nxf1 28. bxa6 Nxg3 29. hxg3 Rb8 30. Rxb8 Rxb8 31. Bxf6 Ra8
32. Nd1 1/2-1/2

[Event ""81st Tata Steel GpA""]
[Site ""Wijk aan Zee NED""]
[Date ""2019.01.13""]
[Round ""2.2""]
[White ""Kramnik,V""]
[Black ""Giri,A""]
[Result ""0-1""]
[WhiteTitle ""GM""]
[BlackTitle ""GM""]
[WhiteElo ""2777""]
[BlackElo ""2783""]
[ECO ""A28""]
[Opening ""English""]
[Variation ""four knights, Capablanca variation""]
[EventDate ""2019.01.12""]
[WhiteFideId ""4101588""]
[BlackFideId ""24116068""]

1. c4 e5 2. Nc3 Nf6 3. Nf3 Nc6 4. d3 d5 5. cxd5 Nxd5 6. e4 Nxc3 7. bxc3 Bc5
8. Be2 O-O 9. O-O Bb6 10. a4 Re8 11. Qc2 Qf6 12. Kh1 h6 13. Ng1 Qd6 14. f4
Bxg1 15. Rxg1 exf4 16. d4 Ne7 17. Ba3 Qd8 18. Raf1 Ng6 19. e5 b6 20. Bf3
Ba6 21. Rf2 c5 22. g3 fxg3 23. Rxg3 cxd4 24. cxd4 Rc8 25. Qf5 Bc4 26. Bd6
Be6 27. Qb1 Nf4 28. d5 Nxd5 29. Qg1 Kh8 30. Rd2 Nf4 31. Rd4 Ng6 32. Be4 Rc4
33. Rxc4 Bxc4 34. Qd4 Be6 35. Bc6 Ne7 36. Be4 Nf5 37. Bxf5 Bxf5 38. Kg1 Be6
39. h4 Qd7 40. Qe4 Rc8 41. h5 Rc1+ 42. Kh2 Qd8 0-1
[Event ""81st Tata Steel GpA""]
[Site ""Wijk aan Zee NED""]
[Date ""2019.01.12""]
[Round ""1.1""]
[White ""Ding Liren""]
[Black ""Carlsen,M""]
[Result ""1/2-1/2""]
[WhiteTitle ""GM""]
[BlackTitle ""GM""]
[WhiteElo ""2813""]
[BlackElo ""2835""]
[ECO ""A05""]
[Opening ""Reti""]
[Variation ""King's Indian attack, Spassky's variation""]
[EventDate ""2019.01.12""]
[WhiteFideId ""8603677""]
[BlackFideId ""1503014""]

1. Nf3 Nf6 2. g3 b5 3. d4 e6 4. Bg5 c5 5. d5 Qa5+ 6. Bd2 Qb6 7. dxe6 fxe6
8. a4 b4 9. a5 Qd8 10. Bg2 Nc6 11. Ne5 Nxe5 12. Bxa8 d5 13. a6 Bd7 14. Bb7
Bd6 15. Bg5 Nf7 16. Bxf6 Qxf6 17. Nd2 O-O 18. O-O Qxb2 19. e4 Qd4 20. exd5
e5 21. Nb3 Qe4 22. Qd3 Qg4 23. f3 Qh5 24. Nd2 Ng5 25. Bc6 Bh3 26. Bb5 Bxf1
27. Rxf1 Rxf3 28. Nxf3 e4 29. Qe3 Nxf3+ 30. Rxf3 Qxf3 31. Qxf3 exf3 32. Kf2
1/2-1/2

[Event ""81st Tata Steel GpA""]
[Site ""Wijk aan Zee NED""]
[Date ""2019.01.12""]
[Round ""1.2""]
[White ""Giri,A""]
[Black ""Nepomniachtchi,I""]
[Result ""0-1""]
[WhiteTitle ""GM""]
[BlackTitle ""GM""]
[WhiteElo ""2783""]
[BlackElo ""2763""]
[ECO ""B07""]
[Opening ""Pirc defence""]
[EventDate ""2019.01.12""]
[WhiteFideId ""24116068""]
[BlackFideId ""4168119""]

1. e4 d6 2. d4 Nf6 3. Nc3 g6 4. Be3 a6 5. Qd2 b5 6. f3 Nbd7 7. O-O-O Nb6 8.
g4 Bb7 9. Nh3 Nfd7 10. Be2 e6 11. Bg5 Be7 12. Qe3 Bxg5 13. Nxg5 h6 14. Nh3
Qh4 15. Nf2 O-O-O 16. f4 f5 17. Bf3 b4 18. exf5 bxc3 19. fxe6 cxb2+ 20. Kb1
Nf6 21. Bxb7+ Kxb7 22. Qf3+ d5 23. Nd3 Ne4 24. Nc5+ Ka7 25. Qa3 Nxc5 26.
Qxc5 Kb7 0-1

[Event ""81st Tata Steel GpA""]
[Site ""Wijk aan Zee NED""]
[Date ""2019.01.12""]
[Round ""1.3""]
[White ""Fedoseev,Vl3""]
[Black ""Rapport,R""]
[Result ""1/2-1/2""]
[WhiteTitle ""GM""]
[BlackTitle ""GM""]
[WhiteElo ""2724""]
[BlackElo ""2731""]
[ECO ""E12""]
[Opening ""Queen's Indian""]
[Variation ""Petrosian system""]
[EventDate ""2019.01.12""]
[WhiteFideId ""24130737""]
[BlackFideId ""738590""]

1. d4 Nf6 2. Nf3 e6 3. c4 b6 4. a3 Bb7 5. Nc3 Ne4 6. Nxe4 Bxe4 7. Nd2 Bb7
8. e4 g6 9. Bd3 Bg7 10. Nf3 O-O 11. O-O d6 12. Rb1 Nd7 13. Bg5 Qc8 14. Re1
Re8 15. Qd2 c5 16. d5 exd5 17. exd5 Qc7 18. Kh1 Ba6 19. b3 Nf6 20. h3 Rxe1+
21. Rxe1 Re8 22. Rxe8+ Nxe8 23. g4 Qd7 24. Kg2 Nc7 25. a4 Bc8 26. Qe3 Ne8
27. Kf1 Bf6 28. Bf5 gxf5 29. Bxf6 fxg4 30. hxg4 Nxf6 31. Qg5+ Kf8 32. Qxf6
Qxg4 33. Qxd6+ Kg7 34. Qe5+ f6 35. Qe7+ Kg6 36. Qe8+ Kg7 37. Qe7+ Kg6 38.
Qe8+ Kg7 39. Qe7+ 1/2-1/2

[Event ""81st Tata Steel GpA""]
[Site ""Wijk aan Zee NED""]
[Date ""2019.01.12""]
[Round ""1.6""]
[White ""Shankland,S""]
[Black ""Mamedyarov,S""]
[Result ""1/2-1/2""]
[WhiteTitle ""GM""]
[BlackTitle ""GM""]
[WhiteElo ""2725""]
[BlackElo ""2817""]
[ECO ""C42""]
[Opening ""Petrov's defence""]
[EventDate ""2019.01.12""]
[WhiteFideId ""2004887""]
[BlackFideId ""13401319""]

1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. Bd3 Nf6 6. O-O Be7 7. c3 O-O
8. Bc2 c5 9. d4 Be6 10. Re1 Re8 11. Bg5 Nbd7 12. Nbd2 Qb6 13. dxc5 dxc5 14.
Bb3 Nf8 15. Bxe6 Nxe6 16. Qb3 Qxb3 17. axb3 Nxg5 18. Nxg5 a6 19. g3 Rad8
20. Nc4 h6 21. Nf3 Kf8 22. Kf1 Bd6 23. Na5 Rb8 24. Rxe8+ Kxe8 25. Re1+ Kf8
26. Rd1 Ke7 27. Ne1 Bc7 28. Nc4 b5 29. Ne3 g6 30. Nd3 Bd6 31. Ra1 Rb6 32.
c4 b4 33. Ke2 Ke6 34. Ra5 Rc6 35. Nd5 Nd7 36. f4 f5 37. Kf3 Nf6 38. Ra1
Nxd5 39. Re1+ Ne3 40. Rxe3+ Kd7 41. g4 fxg4+ 42. Kxg4 Rc8 43. Rh3 Rh8 44.
Kf3 Ke6 45. Ke4 Kf6 46. Ne5 Re8 47. Rf3 Bb8 48. h4 a5 49. Rf1 h5 50. Rf3
Bc7 51. Rf1 Rd8 52. Nf3 Re8+ 53. Ne5 Rd8 54. Nf3 Re8+ 1/2-1/2

[Event ""81st Tata Steel GpA""]
[Site ""Wijk aan Zee NED""]
[Date ""2019.01.12""]
[Round ""1.7""]
[White ""Radjabov,T""]
[Black ""Kramnik,V""]
[Result ""1/2-1/2""]
[WhiteTitle ""GM""]
[BlackTitle ""GM""]
[WhiteElo ""2757""]
[BlackElo ""2777""]
[ECO ""C50""]
[Opening ""Giuoco Piano""]
[EventDate ""2019.01.12""]
[WhiteFideId ""13400924""]
[BlackFideId ""4101588""]

1. e4 e5 2. Nf3 Nc6 3. Bc4 Bc5 4. O-O Nf6 5. d3 d6 6. c3 a6 7. a4 O-O 8.
Re1 Ba7 9. h3 h6 10. Nbd2 Re8 11. b4 Be6 12. Bxe6 Rxe6 13. Bb2 Ne7 14. c4
Ng6 15. Nf1 b5 16. axb5 axb5 17. Ng3 bxc4 18. dxc4 Re8 19. Qc2 Qb8 20. Reb1
Qb7 21. c5 dxc5 22. bxc5 Qc6 23. Rc1 Nd7 24. Ra5 Reb8 25. Ba3 Nf4 26. Nf5
Re8 27. g3 Ne6 28. Kg2 Nf6 29. Re1 Nd7 30. Rc1 Kh7 31. Qc4 Bxc5 32. Rxc5
Ndxc5 33. Bxc5 Ra4 34. Qd5 Qa8 35. Qd7 Kg8 36. Nxe5 Ng5 37. Nc6 Raxe4 38.
Nfe7+ Kh7 39. Ra1 Ra4 40. Rxa4 Qxa4 41. Qxe8 Qe4+ 42. Kf1 Qb1+ 43. Kg2
1/2-1/2

[Event ""81st Tata Steel GpA""]
[Site ""Wijk aan Zee NED""]
[Date ""2019.01.13""]
[Round ""2.1""]
[White ""Carlsen,M""]
[Black ""Nepomniachtchi,I""]
[Result ""1/2-1/2""]
[WhiteTitle ""GM""]
[BlackTitle ""GM""]
[WhiteElo ""2835""]
[BlackElo ""2763""]
[ECO ""E60""]
[Opening ""King's Indian defence""]
[EventDate ""2019.01.12""]
[WhiteFideId ""1503014""]
[BlackFideId ""4168119""]

1. d4 Nf6 2. c4 g6 3. f3 e6 4. e4 c5 5. d5 d6 6. Nc3 Bg7 7. Nge2 exd5 8.
cxd5 a6 9. a4 O-O 10. Ng3 Nbd7 11. Be2 Ne8 12. Bf4 Rb8 13. O-O c4 14. Bxc4
Qb6+ 15. Rf2 Bd4 16. Qd2 Ne5 17. Bf1 Bxf2+ 18. Qxf2 Qxf2+ 19. Kxf2 Bd7 20.
Be3 f5 21. exf5 gxf5 22. Bd4 Nf6 23. Kg1 Rbc8 24. Ra3 Nc4 25. Rb3 b5 26.
axb5 Nd2 27. Rb4 Nxf1 28. bxa6 Nxg3 29. hxg3 Rb8 30. Rxb8 Rxb8 31. Bxf6 Ra8
32. Nd1 1/2-1/2

[Event ""81st Tata Steel GpA""]
[Site ""Wijk aan Zee NED""]
[Date ""2019.01.13""]
[Round ""2.2""]
[White ""Kramnik,V""]
[Black ""Giri,A""]
[Result ""0-1""]
[WhiteTitle ""GM""]
[BlackTitle ""GM""]
[WhiteElo ""2777""]
[BlackElo ""2783""]
[ECO ""A28""]
[Opening ""English""]
[Variation ""four knights, Capablanca variation""]
[EventDate ""2019.01.12""]
[WhiteFideId ""4101588""]
[BlackFideId ""24116068""]

1. c4 e5 2. Nc3 Nf6 3. Nf3 Nc6 4. d3 d5 5. cxd5 Nxd5 6. e4 Nxc3 7. bxc3 Bc5
8. Be2 O-O 9. O-O Bb6 10. a4 Re8 11. Qc2 Qf6 12. Kh1 h6 13. Ng1 Qd6 14. f4
Bxg1 15. Rxg1 exf4 16. d4 Ne7 17. Ba3 Qd8 18. Raf1 Ng6 19. e5 b6 20. Bf3
Ba6 21. Rf2 c5 22. g3 fxg3 23. Rxg3 cxd4 24. cxd4 Rc8 25. Qf5 Bc4 26. Bd6
Be6 27. Qb1 Nf4 28. d5 Nxd5 29. Qg1 Kh8 30. Rd2 Nf4 31. Rd4 Ng6 32. Be4 Rc4
33. Rxc4 Bxc4 34. Qd4 Be6 35. Bc6 Ne7 36. Be4 Nf5 37. Bxf5 Bxf5 38. Kg1 Be6
39. h4 Qd7 40. Qe4 Rc8 41. h5 Rc1+ 42. Kh2 Qd8 0-1
";
    }
}