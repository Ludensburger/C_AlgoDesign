#include <stdbool.h>

#include <stdio.h>

#define N 8

int queenCount = 0;

char board[N][N];

void initializeBoard() {

    for (int i = 0; i < N; i++) {

        for (int j = 0; j < N; j++) {

            board[i][j] = ' ';
        }
    }
}

// void displayBoard() {
//     printf(" ");
//     for (int i = 1; i < N; i++) {
//         printf("   %d", i);
//     }
//     printf("\n");
//     for (int i = 0; i < N; i++) {
//         printf("%d |", i + 1);
//         for (int j = 0; j < N; j++) {
//             printf("%2c|", board[i][j]);
//         }
//         printf("\n");
//     }
// }

void displayBoard() {

    printf("  ");

    for (int i = 1; i <= N; i++) {

        printf(" %2d", i);
    }

    printf("\n");

    for (int i = 0; i < N; i++) {

        printf("%d |", i + 1);

        for (int j = 0; j < N; j++) {

            printf("%c |", board[i][j]);
        }

        printf("\n");
    }
}

bool canPlaceQueen(int row, int col) {

    for (int i = 0; i < N; i++) {

        if (board[row][i] == 'Q' || board[i][col] == 'Q') {
            return false;
        }

        if (row + i < N && col + i < N && board[row + i][col + i] == 'Q') {
            return false;
        }

        if (row - i >= 0 && col - i >= 0 && board[row - i][col - i] == 'Q') {
            return false;
        }

        if (row + i < N && col - i >= 0 && board[row + i][col - i] == 'Q') {
            return false;
        }

        if (row - i >= 0 && col + i < N && board[row - i][col + i] == 'Q') {
            return false;
        }
    }

    return true;
}

void placeQueen(int row, int col) {

    if (canPlaceQueen(row, col)) {

        queenCount++;

        for (int i = 0; i < N; i++) {

            if (i != col) {
                // Marking horizontal path
                board[row][i] = '*';
            }

            if (i != row) { // Marking vertical path
                board[i][col] = '*';
            }

            if (row + i < N && col + i < N) {
                // Marking diagonal path (bottom-right)
                board[row + i][col + i] = '*';
            }

            if (row - i >= 0 && col - i >= 0) {
                // Marking diagonal path (top-left)
                board[row - i][col - i] = '*';
            }

            if (row + i < N && col - i >= 0) {
                // Marking diagonal path (bottom-left)
                board[row + i][col - i] = '*';
            }

            if (row - i >= 0 && col + i < N) {
                // Marking diagonal path (top-right)
                board[row - i][col + i] = '*';
            }
        }

        board[row][col] = 'Q'; // Placing queen
        printf("\n%d Queen placed successfully!\n", queenCount);

    } else {
        printf("\n");
        printf("Cannot place queen at (%d, %d)!\n", row + 1, col + 1);
    }
}

int checkBoard() {

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

            if (board[i][j] == ' ') {
                return 1; // Board has empty spaces
            }
        }
    }
    return 0; // Board is full
}

// Solution for Queen's Puzzle
//  R6 C1
//  R2 C2
//  R7 C3
//  R1 C4
//  R4 C5
//  R8 C6
//  R5 C7
//  R3 C8

int main() {

    printf("+=*EIGHT QUEENS PUZZLE*=+ \n\n");

    initializeBoard();
    displayBoard();

    printf("\n\n");

    int x, y;
    while (queenCount < 8) {

        printf("Enter x (1-8): ");
        scanf("%d", &x);

        printf("Enter y (1-8): ");
        scanf("%d", &y);

        x--;
        y--;

        placeQueen(x, y);
        displayBoard();

        if (!checkBoard()) {

            printf("%d/8 Queens placed!\n", queenCount);
            printf("Cannot place more queens on the board.\n");
            break;
        }

        if (queenCount == 8) {
            printf("\nCongratulations!!!\n");
            printf("All queens placed successfully!\n");

            printf("\n\n");
        }
    }

    return 0;
}
