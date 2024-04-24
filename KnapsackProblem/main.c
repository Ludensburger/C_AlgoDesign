#include <stdio.h>

// Function to get maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }

// Function prototype for printTable
void printTable(int K[][8], int n, int W);

// Returns the maximum value that can be put in a knapsack of capacity W
int knapSack(int W, int wt[], int val[], int n)
{
    int i, w;
    int K[n + 1][W + 1];

    // Build table K[][] in bottom up manner
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
            {
                K[i][w] = 0;
            }
            else if (wt[i - 1] <= w)
            {
                // V[i, w] = max {V[i-1, w] , V[ i-1, w-w[i] ] + P[i]}
                int x = K[i - 1][w];                          // Previous
                int y = K[i - 1][w - wt[i - 1]] + val[i - 1]; // Total Value

                K[i][w] = max(x, y);
            }
            else
            {
                K[i][w] = K[i - 1][w]; // Previous
            }
        }
    }

    printTable(K, n, W);

    return K[n][W];
}

// Definition of printTable function
void printTable(int K[][8], int n, int W)
{
    printf("Table:\n");
    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            printf("%d  ", K[i][w]);
        }
        printf("\n");
    }
}

int main()
{
    int V[4] = {15, 20, 30, 35}; // Values of the items
    int W[4] = {1, 3, 4, 5};     // Weights of the items

    int n = 4;    // Number of items
    int Wmax = 7; // Maximum weight that the knapsack can hold

    int result = knapSack(Wmax, W, V, n);

    printf("Maximum value that can be put in a knapsack of capacity %d is %d\n", Wmax, result);

    return 0;
}