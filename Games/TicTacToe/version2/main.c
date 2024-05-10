
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 3

// Function prototypes
void initialize_board(char board[SIZE][SIZE]);
int is_valid_move(char board[SIZE][SIZE], int row, int col);
int is_game_over(char board[SIZE][SIZE]);
int is_board_full(char board[SIZE][SIZE]);
void print_board(char board[SIZE][SIZE]);
void computer_move(char board[SIZE][SIZE], char player);
void play_game(int gameMode);
int main();

void initialize_board(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

int is_valid_move(char board[SIZE][SIZE], int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        return 0; // Out of bounds
    }
    if (board[row][col] != ' ') {
        return 0; // Cell already occupied
    }
    return 1; // Valid move
}

int is_game_over(char board[SIZE][SIZE]) {
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < SIZE; i++) {
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') ||
            (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')) {
            return 1; // Win
        }
    }
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')) {
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

int is_board_full(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                return 0; // Found an empty cell, so the board is not full
            }
        }
    }
    return 1; // No empty cells found, so the board is full
}

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

void computer_move(char board[SIZE][SIZE], char player) {
    int row, col;
    srand(time(0)); // Seed the random number generator

    // If there's a winning move, take it.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (is_valid_move(board, i, j)) {
                board[i][j] = player;
                if (is_game_over(board)) {
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // If the opponent has a winning move, block it.
    char opponent = (player == 'X') ? 'O' : 'X';
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (is_valid_move(board, i, j)) {
                board[i][j] = opponent;
                if (is_game_over(board)) {
                    board[i][j] = player;
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // If the center square (1,1) is free, take it.
    if (is_valid_move(board, 1, 1)) {
        board[1][1] = player;
        return;
    }

    // If the opponent is in a corner and the opposite corner is free, take it.
    int corners[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
    for (int i = 0; i < 4; i++) {
        if (board[corners[i][0]][corners[i][1]] == opponent && is_valid_move(board, 2 - corners[i][0], 2 - corners[i][1])) {
            board[2 - corners[i][0]][2 - corners[i][1]] = player;
            return;
        }
    }

    // Take a free corner if one exists.
    for (int i = 0; i < 4; i++) {
        if (is_valid_move(board, corners[i][0], corners[i][1])) {
            board[corners[i][0]][corners[i][1]] = player;
            return;
        }
    }

    // Otherwise, make a random move.
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (!is_valid_move(board, row, col));
    board[row][col] = player;
}

void play_game(int gameMode) {
    char board[SIZE][SIZE];
    char currentPlayer = 'X';
    initialize_board(board);

    while (1) {
        print_board(board);
        if (gameMode == 1 || (gameMode == 2 && currentPlayer == 'X')) {
            int row, col;
            printf("Player %c's turn. Enter row (1-3) and column (1-3): ", currentPlayer);
            scanf("%d %d", &row, &col);
            row--; // Adjust for 0-based indexing
            col--; // Adjust for 0-based indexing
            if (is_valid_move(board, row, col)) {
                board[row][col] = currentPlayer;
            } else {
                printf("Invalid move. Try again.\n");
                continue;
            }
        } else if (gameMode == 2 && currentPlayer == 'O') {
            computer_move(board, currentPlayer);
        }

        int game_status = is_game_over(board);
        if (game_status == 1) {
            print_board(board);
            printf("Player %c wins!\n", currentPlayer);
            break;
        } else if (game_status == -1 || is_board_full(board)) {
            print_board(board);
            printf("It's a draw!\n");
            break;
        }
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; // Switch players
    }
}

int main() {
    int gameMode;
    printf("Select game mode:\n1. Player vs Player\n2. Player vs Computer\n");
    scanf("%d", &gameMode);
    if (gameMode < 1 || gameMode > 2) {
        printf("Invalid game mode. Please select 1 or 2.\n");
        return 0;
    }
    play_game(gameMode);
    return 0;
}