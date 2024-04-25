#include <stdio.h>

// Function to get maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }

// Function prototype for printTable
void printTable(int n, int W, int wt[], int K[n + 1][W + 1]);

// Returns the maximum value that can be put in a knapsack of capacity W
int knapSack(int W, int wt[], int val[], int n) {
    int i, w;
    int K[n + 1][W + 1];

    // Build table K[][] in bottom up manner
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                K[i][w] = 0;
            } else if (wt[i - 1] <= w) {
                // V[i, w] = max {V[i-1, w] , V[ i-1, w-w[i] ] + P[i]}
                int x = K[i - 1][w];                          // Previous
                int y = K[i - 1][w - wt[i - 1]] + val[i - 1]; // Total Value

                K[i][w] = max(x, y);
            } else {
                K[i][w] = K[i - 1][w]; // Previous
            }
        }
    }

    printTable(n, W, wt, K);

    return K[n][W];
}

// Definition of printTable function
void printTable(int n, int W, int wt[], int K[n + 1][W + 1]) {
    printf("Table:\n");

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            printf("%d   ", K[i][w]);
        }
        printf("\n");
    }

    for (int i = 0; i < W * 5; i++) {
        printf("-");
    }

    printf("^ Goal");

    printf("\n\n");

    printf("Included items:\n");

    int w = W;
    int included[n + 1];
    for (int i = 0; i <= n; i++) {
        included[i] = 0;
    }

    for (int i = n; i > 0 && w > 0; i--) {
        if (K[i][w] != K[i - 1][w]) {
            included[i] = 1;
            w = w - wt[i - 1];
        }
    }

    for (int i = n; i > 0; i--) {
        printf("x%d = %d\n", i, included[i]);
    }

    printf("\nOr simply, Items: ");

    w = W;
    for (int i = 1; i <= n; i++) {
        if (K[i][w] != K[i - 1][w]) {
            printf("%d", i); // This item is included.
            w = w - wt[i - 1];
            if (i < n - 1) {
                printf(", ");
            }
        }
    }
    printf("\n");
}

int main() {

    // Weights of the items
    int W[] = {2, 1, 3, 2};

    // Values of the items
    int V[] = {12, 10, 20, 15};

    // Get the number of items
    int n = sizeof(W) / sizeof(W[0]);

    int Wmax = 5; // Maximum weight that the knapsack can hold

    int result = knapSack(Wmax, W, V, n);

    printf("Maximum value that can be put in a knapsack of capacity %d is %d\n", Wmax, result);

    return 0;
}