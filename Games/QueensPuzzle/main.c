#include <stdbool.h>
#include <stdio.h>

#define N 8

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
        board[row][col] = 'Q';
        for (int i = 0; i < N; i++) {
            if (i != col)
                // Marking horizontal path
                board[row][i] = '*';
            if (i != row)
                // Marking vertical path
                board[i][col] = '*';
            if (row + i < N && col + i < N)
                // Marking diagonal path (bottom-right)
                board[row + i][col + i] = '*';
            if (row - i >= 0 && col - i >= 0)
                // Marking diagonal path (top-left)
                board[row - i][col - i] = '*';
            if (row + i < N && col - i >= 0)
                board[row + i][col - i] = '*'; // Marking diagonal path (bottom-left)
            if (row - i >= 0 && col + i < N)
                board[row - i][col + i] = '*'; // Marking diagonal path (top-right)
        }
        board[row][col] = 'Q'; // Placing queen
        printf("Queen placed successfully!\n");
    } else {
        printf("Cannot place queen at (%d, %d)!\n", row + 1, col + 1);
    }
}

int main() {

    int queenCount = 0;

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
        queenCount++;
        displayBoard();

        if (queenCount == 8) {
            printf("Congratulations!!!\n");
            printf("All queens placed successfully!\n");
            break;
        } else if (queenCount == 7) {
            printf("SO CLOSE!\n");
        } else if (queenCount == 6) {
            printf("Almost there...\n");
        }
        // Add more conditions here if needed

        printf("\n\n");
    }

    return 0;
}
