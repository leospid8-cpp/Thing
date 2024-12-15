#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>

using namespace std;

// Represents a single piece on the chessboard
struct Piece {
    char type; // Type of the piece (K=King, Q=Queen, R=Rook, N=Knight, B=Bishop, P=Pawn)
    char color; // Color of the piece (B=White, N=Black)

    // Constructor to initialize the piece with a type and color
    Piece(char t = ' ', char c = ' ') : type(t), color(c) {}
};

// The chessboard is represented as an 8x8 array of pieces
class ChessBoard {
public:
    Piece board[8][8]; // 8x8 matrix representing the chessboard

    // Constructor: Initializes the chessboard with the pieces in their starting positions
    ChessBoard() {
        // Initialize white pieces
        board[0][0] = board[0][7] = Piece('R', 'B');  // Rooks at a1 and h1
        board[0][1] = board[0][6] = Piece('N', 'B');  // Knights at b1 and g1
        board[0][2] = board[0][5] = Piece('B', 'B');  // Bishops at c1 and f1
        board[0][3] = Piece('Q', 'B');                 // Queen at d1
        board[0][4] = Piece('K', 'B');                 // King at e1
        for (int i = 0; i < 8; i++) board[1][i] = Piece('P', 'B'); // Pawns on the second row

        // Initialize black pieces
        board[7][0] = board[7][7] = Piece('R', 'N');  // Rooks at a8 and h8
        board[7][1] = board[7][6] = Piece('N', 'N');  // Knights at b8 and g8
        board[7][2] = board[7][5] = Piece('B', 'N');  // Bishops at c8 and f8
        board[7][3] = Piece('Q', 'N');                 // Queen at d8
        board[7][4] = Piece('K', 'N');                 // King at e8
        for (int i = 0; i < 8; i++) board[6][i] = Piece('P', 'N'); // Pawns on the seventh row
    }

    // Function to print the chessboard (without row/column labels)
    void printBoard() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                // Print the piece's type (empty space is represented by a '.')
                cout << (board[i][j].type == ' ' ? '.' : board[i][j].type) << " ";
            }
            cout << endl;
        }
    }

    // Function to execute a move by transferring a piece from one square to another
    bool makeMove(int x1, int y1, int x2, int y2) {
        // Check if the destination is within bounds
        if (x2 >= 0 && x2 < 8 && y2 >= 0 && y2 < 8) {
            // Move the piece: set the destination square to the piece from the source square
            board[x2][y2] = board[x1][y1];
            // Clear the source square (set it to an empty piece)
            board[x1][y1] = Piece();
            return true; // Move was successful
        }
        return false; // Invalid move (out of bounds)
    }

    // Converts column letters (e.g., 'a') to array indices (0 for 'a', 1 for 'b', etc.)
    int letterToIndex(char letter) {
        return letter - 'a'; // Converts 'a' to 0, 'b' to 1, etc.
    }

    // Converts row numbers (e.g., '1') to array indices (7 for '1', 6 for '2', etc.)
    int numberToIndex(char number) {
        return 8 - (number - '0'); // Converts '1' to 7, '2' to 6, etc.
    }
};

// Function to parse a move given in algebraic notation and execute it on the chessboard
bool parseMove(string move, ChessBoard& chess, char playerColor) {
    // A move could be in the form "e2 e4", "Nf3", "Qd1 d3", etc.
    stringstream ss(move); // Create a stringstream to extract parts of the move
    string from, to;

    // Read the starting square of the move (e.g., "e2")
    ss >> from;

    // If the from part is invalid (less than 2 characters), the move format is incorrect
    if (from.size() < 2) {
        cout << "Invalid move format. Try again." << endl;
        return false;
    }

    // Convert the starting position from algebraic notation (e.g., "e2") to array indices
    int fromX = chess.numberToIndex(from[1]);
    int fromY = chess.letterToIndex(from[0]);

    // Read the destination part of the move (e.g., "e4")
    if (ss >> to) {
        // If the destination is not valid (not two characters), the move format is incorrect
        if (to.size() != 2) {
            cout << "Invalid move format. Try again." << endl;
            return false;
        }
        // Convert the destination position from algebraic notation to array indices
        int toX = chess.numberToIndex(to[1]);
        int toY = chess.letterToIndex(to[0]);

        // Try to execute the move on the chessboard
        if (!chess.makeMove(fromX, fromY, toX, toY)) {
            cout << "Invalid move. Try again." << endl;
            return false;
        }
    }
    else {
        // If there is no destination (e.g., a knight move such as Nf3), it's an invalid format
        cout << "Move not implemented for this piece or invalid format." << endl;
        return false;
    }

    return true; // The move was parsed and executed successfully
}

int main() {
    srand(time(0));  // Set the seed for random number generation (if needed for random moves)

    ChessBoard chess; // Create a chessboard object to manage the game state
    bool gameOver = false; // A flag to track whether the game is over
    char turn = 'B'; // Start with white's turn (B = White, N = Black)

    // Main game loop
    while (!gameOver) {
        chess.printBoard(); // Print the current state of the board

        // Prompt the player for their move in algebraic notation (e.g., "e2 e4")
        cout << "Player " << (turn == 'B' ? "White" : "Black") << ", your move (in algebraic notation, e.g. e2 e4): ";
        string move;
        getline(cin, move); // Read the move from the user

        // Parse and execute the move; if invalid, the loop will prompt for a new move
        if (!parseMove(move, chess, turn)) {
            continue; // If the move is invalid, prompt for a new move
        }

        // Switch turns between the players
        turn = (turn == 'B') ? 'N' : 'B'; // If it's white's turn (B), switch to black's turn (N)
    }

    return 0;
}

//created by leospid8