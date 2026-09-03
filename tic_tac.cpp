#include <iostream>
#include <vector>

using namespace std;

// Function to draw the 3x3 Tic Tac Toe board
void drawBoard(const vector<vector<char>>& board) {
    cout << "\n";
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " \n";
    cout << "---|---|---\n";
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " \n";
    cout << "---|---|---\n";
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " \n";
    cout << "\n";
}

// Function to check if a player has won
bool checkWin(const vector<vector<char>>& board, char player) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

// Function to check if the board is full (Draw)
bool checkDraw(const vector<vector<char>>& board) {
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (board[r][c] != 'X' && board[r][c] != 'O') {
                return false; // Found an empty spot
            }
        }
    }
    return true;
}

// Main game function
void playGame() {
    // Initialize 3x3 board with numbers 1 to 9
    vector<vector<char>> board = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    char currentPlayer = 'X';
    bool gameOver = false;

    while (!gameOver) {
        drawBoard(board);
        int choice;
        cout << "Player " << currentPlayer << ", enter a position (1-9): ";
        cin >> choice;

        // Map choice (1-9) to row and column indices
        int row = (choice - 1) / 3;
        int col = (choice - 1) % 3;

        // Validate player input
        if (choice < 1 || choice > 9 || board[row][col] == 'X' || board[row][col] == 'O') {
            cout << "Invalid move! Spot is already taken or out of range. Try again.\n";
            continue;
        }

        // Place move
        board[row][col] = currentPlayer;

        // Check for win condition
        if (checkWin(board, currentPlayer)) {
            drawBoard(board);
            cout << "🎉 Player " << currentPlayer << " wins!\n";
            gameOver = true;
        } 
        // Check for draw condition
        else if (checkDraw(board)) {
            drawBoard(board);
            cout << "🤝 It's a draw!\n";
            gameOver = true;
        } 
        // Switch player turn
        else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}

int main() {
    char replayChoice;
    do {
        cout << "===============================\n";
        cout << "    TIC TAC TOE MINI GAME      \n";
        cout << "===============================\n";
        
        playGame();

        cout << "Do you want to play again? (y/n): ";
        cin >> replayChoice;

    } while (replayChoice == 'y' || replayChoice == 'Y');

    cout << "Thanks for playing!\n";
    return 0;
}
