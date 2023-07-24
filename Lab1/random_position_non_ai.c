// Using Random Postions

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function prototypes
void initializeBoard(char board[3][3]);
void printBoard(char board[3][3]);
int isMoveValid(char board[3][3], int row, int col);
int isGameOver(char board[3][3]);
int evaluateBoard(char board[3][3], char player);
void computerMove(char board[3][3]);
void playerMove(char board[3][3]);

int main() {
    char board[3][3];
    int currentPlayer = 1; // 1 for player, 2 for computer
    int row, col;

    initializeBoard(board);
    srand(time(0));

    printf("Tic-Tac-Toe Game\n");
    printf("Player: X, Computer: O\n");

    while (!isGameOver(board)) {
        printBoard(board);

        if (currentPlayer == 1) {
            playerMove(board);
            currentPlayer = 2;
        } else {
            computerMove(board);
            currentPlayer = 1;
        }
    }

    printBoard(board);

    int winner = evaluateBoard(board, 'X');
    if (winner == 1)
        printf("Congratulations! You win!\n");
    else if (winner == -1)
        printf("The computer wins!\n");
    else
        printf("It's a draw!\n");

    return 0;
}

// Initialize the Tic-Tac-Toe board with empty spaces
void initializeBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

// Print the Tic-Tac-Toe board
void printBoard(char board[3][3]) {
    printf("-------------\n");
    for (int i = 0; i < 3; i++) {
        printf("| %c | %c | %c |\n", board[i][0], board[i][1], board[i][2]);
        printf("-------------\n");
    }
}

// Check if a move is valid (within bounds and the cell is empty)
int isMoveValid(char board[3][3], int row, int col) {
    return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ');
}

// Check if the game is over (win or draw)
int isGameOver(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        // Check rows and columns for a win
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return 1;
    }

    // Check diagonals for a win
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' '))
        return 1;

    // Check if the board is full (draw)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ')
                return 0;
        }
    }

    return -1; // Draw
}

// Evaluate the board and determine the winner
int evaluateBoard(char board[3][3], char player) {
    if ((board[0][0] == player && board[0][1] == player && board[0][2] == player) ||
        (board[1][0] == player && board[1][1] == player && board[1][2] == player) ||
        (board[2][0] == player && board[2][1] == player && board[2][2] == player) ||
        (board[0][0] == player && board[1][0] == player && board[2][0] == player) ||
        (board[0][1] == player && board[1][1] == player && board[2][1] == player) ||
        (board[0][2] == player && board[1][2] == player && board[2][2] == player) ||
        (board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return 1;

    if ((board[0][0] != ' ' && board[0][1] != ' ' && board[0][2] != ' ' &&
         board[1][0] != ' ' && board[1][1] != ' ' && board[1][2] != ' ' &&
         board[2][0] != ' ' && board[2][1] != ' ' && board[2][2] != ' '))
        return 0;

    return -1;
}

// Computer makes a random move
void computerMove(char board[3][3]) {
    int row, col;
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (!isMoveValid(board, row, col));

    board[row][col] = 'O';
}

// Player makes a move
void playerMove(char board[3][3]) {
    int row, col;
    do {
        printf("Enter your move (row [0-2] and column [0-2]): ");
        scanf("%d %d", &row, &col);
    } while (!isMoveValid(board, row, col));

    board[row][col] = 'X';
}