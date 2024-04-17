#include <stdio.h>

void PascalTriangleIterative(int n) {

    // base case for n = 0
    if (n <= 0) {
        printf("1\n");
        return;
    }

    int coefficient[n + 1][n + 1];

    coefficient[0][0] = 1;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i) {
                coefficient[i][j] = 1;
            } else {
                coefficient[i][j] = coefficient[i - 1][j - 1] + coefficient[i - 1][j];
            }
            printf("%d ", coefficient[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void PascalTriangleRecursive(int n, int arr[]) {

    // base case for recursion
    if (n == 0) {
        arr[0] = 1;
        printf("%d\n", arr[0]);
        return;
    }

    PascalTriangleRecursive(n - 1, arr);

    for (int i = n; i > 0; i--) {

        // Formula from book
        // calculate the value of the current element
        arr[i] = arr[i] + arr[i - 1];
    }

    arr[0] = 1;

    for (int i = 0; i <= n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {

    int n;
    printf("Pascal Triangle\n");

    // Input
    printf("Enter n: ");
    scanf("%d", &n);

    // Invokation
    PascalTriangleIterative(n);

    // Initialization
    // initialize array with 0
    int arr[n + 1];
    for (int i = 0; i <= n; i++) {
        arr[i] = 0;
    }

    // Invokation
    // pass the array to the recursive function
    PascalTriangleRecursive(n, arr);

    return 0;
}