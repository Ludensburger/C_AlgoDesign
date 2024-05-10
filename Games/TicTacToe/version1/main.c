#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

int is_valid_move(char board[SIZE][SIZE], int row, int col);

// Function to initialize the board with empty spaces
void initialize_board(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

int is_valid_move(char board[SIZE][SIZE], int row, int col) {
    // Check if the row and column are within the bounds of the board
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        return 0;
    }

    // Check if the square is empty
    if (board[row][col] != ' ') {
        return 0;
    }

    // If we've made it this far, the move is valid
    return 1;
}

int is_game_over(char board[SIZE][SIZE], char player) {
    // Check rows
    for (int row = 0; row < SIZE; row++) {
        if (board[row][0] == player && board[row][1] == player && board[row][2] == player) {
            return 1;
        }
    }

    // Check columns
    for (int col = 0; col < SIZE; col++) {
        if (board[0][col] == player && board[1][col] == player && board[2][col] == player) {
            return 1;
        }
    }

    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return 1;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return 1;
    }

    // No win found
    return 0;
}

int is_board_full(char board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] == ' ') {
                return 0; // Found an empty cell, so the board is not full
            }
        }
    }
    return 1; // No empty cells found, so the board is full
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

// Function for the computer to make a move
// Initial approach: Randomly select a valid move
// void computer_move(char board[SIZE][SIZE]) {
//     int row, col;
//     srand(time(0)); // Seed the random number generator
//     do {
//         row = rand() % SIZE;
//         col = rand() % SIZE;
//     } while (!is_valid_move(board, row, col));
//     board[row][col] = 'O';
// }

// Function for the computer to make a move
// Improved approach: Check for winning move, block opponent's winning move, then make a random move
/*
    To further improve the AI, we can add more strategic decision-making. Here's a more advanced strategy:

    If there's a winning move, take it.
    If the opponent has a winning move, block it.
    If the center square (1,1) is free, take it.
    If the opponent is in a corner and the opposite corner is free, take it.
    Take a free corner if one exists.
    Otherwise, make a random move.

*/
void computer_move(char board[SIZE][SIZE], char player) {
    int row, col;

    // 1. Check if we have a winning move
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (is_valid_move(board, row, col)) {
                board[row][col] = player;
                if (is_game_over(board, player) == 1) {
                    return; // We found a winning move
                }
                board[row][col] = ' '; // Undo move
            }
        }
    }

    // 2. Check if the opponent has a winning move and block it
    char opponent = (player == 'O') ? 'X' : 'O';
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (is_valid_move(board, row, col)) {
                board[row][col] = opponent;
                if (is_game_over(board, opponent) == 1) {
                    board[row][col] = player; // Block the opponent's winning move
                    return;
                }
                board[row][col] = ' '; // Undo move
            }
        }
    }

    // 3. If the center square is free, take it
    if (is_valid_move(board, 1, 1)) {
        board[1][1] = player;
        return;
    }

    // 4. If the opponent is in a corner and the opposite corner is free, take it
    int corners[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
    for (int i = 0; i < 4; i++) {
        if (board[corners[i][0]][corners[i][1]] == opponent && is_valid_move(board, corners[(i + 2) % 4][0], corners[(i + 2) % 4][1])) {
            board[corners[(i + 2) % 4][0]][corners[(i + 2) % 4][1]] = player;
            return;
        }
    }

    // 5. Take a free corner if one exists
    for (int i = 0; i < 4; i++) {
        if (is_valid_move(board, corners[i][0], corners[i][1])) {
            board[corners[i][0]][corners[i][1]] = player;
            return;
        }
    }

    // 6. If there's no strategic move, make a random move
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (!is_valid_move(board, row, col));
    board[row][col] = player;
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

void play_game() {
    char board[SIZE][SIZE];
    initialize_board(board);

    while (1) {
        // Computer 1's turn
        computer_move(board, 'O');
        print_board(board);
        if (is_game_over(board, 'O')) {
            printf("Computer 1 wins!\n");
            break;
        }
        if (is_board_full(board)) {
            printf("It's a draw!\n");
            break;
        }

        // Computer 2's turn
        computer_move(board, 'X');
        print_board(board);
        if (is_game_over(board, 'X')) {
            printf("Computer 2 wins!\n");
            break;
        }
        if (is_board_full(board)) {
            printf("It's a draw!\n");
            break;
        }
    }
}

int main() {
    char board[3][3];
    int gameMode;
    char currentPlayer = 'X';
    int row, col;

    printf("Select game mode:\n1. Player vs Player\n2. Player vs Computer\n3. Computer vs Computer\n");
    scanf("%d", &gameMode);

    initialize_board(board);
    printf("Player 1: X, Player 2: O\n");

    while (1) {
        print_board(board);
        if (gameMode == 1 || (gameMode == 2 && currentPlayer == 'X')) {
            printf("Player %c's turn. Enter row (1-3) and column (1-3): ", currentPlayer);
            scanf("%d %d", &row, &col);
            row--;
            col--;
            if (is_valid_move(board, row, col)) {
                board[row][col] = currentPlayer;
            } else {
                printf("Invalid move. Try again.\n");
                continue;
            }
        } else if (gameMode == 2 && currentPlayer == 'O') {
            computer_move(board, currentPlayer);
        } else if (gameMode == 3) {
            computer_move(board, currentPlayer);
        }

        int game_status = is_game_over(board, currentPlayer);
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

    return 0;
}