#include <stdio.h>

#define SIZE 3

// Function to initialize the board with empty spaces
void initialize_board(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

// Function to print the current board state
void print_board(char board[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1)
                printf("|");
        }
        printf("\n");
        if (i < SIZE - 1)
            printf("---|---|---\n");
    }
    printf("\n");
}

// Function to check if the current move is valid
int is_valid_move(char board[SIZE][SIZE], int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        return 0; // Out of bounds
    }
    if (board[row][col] != ' ') {
        return 0; // Cell already occupied
    }
    return 1; // Valid move
}

// Function to check if there's a win in any row
int is_row_win(char board[SIZE][SIZE], char player) {
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return 1; // Win
        }
    }
    return 0; // No win
}

// Function to check if there's a win in any column
int is_col_win(char board[SIZE][SIZE], char player) {
    for (int i = 0; i < SIZE; i++) {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return 1; // Win
        }
    }
    return 0; // No win
}

// Function to check if there's a win in any diagonal
int is_diag_win(char board[SIZE][SIZE], char player) {
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return 1; // Win
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return 1; // Win
    }
    return 0; // No win
}

// Function to check if the game is over
int is_game_over(char board[SIZE][SIZE], char player) {
    if (is_row_win(board, player) || is_col_win(board, player) || is_diag_win(board, player)) {
        return 1; // Win
    }
    // Check for a draw
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                return 0; // Game still ongoing
            }
        }
    }
    return -1; // Draw
}

int main() {
    char board[SIZE][SIZE];
    int row, col;
    char currentPlayer = 'X';
    initialize_board(board);
    printf("Let's play Tic Tac Toe!\n");
    printf("Player 1: X, Player 2: O\n");

    while (1) {
        print_board(board);
        printf("Player %c's turn. Enter row (0-2) and column (0-2): ", currentPlayer);
        scanf("%d %d", &row, &col);

        if (is_valid_move(board, row, col)) {
            board[row][col] = currentPlayer;
            int game_status = is_game_over(board, currentPlayer);
            if (game_status == 1) {
                print_board(board);
                printf("Player %c wins!\n", currentPlayer);
                break;
            } else if (game_status == -1) {
                print_board(board);
                printf("It's a draw!\n");
                break;
            }
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; // Switch players
        } else {
            printf("Invalid move. Try again.\n");
        }
    }

    return 0;
}