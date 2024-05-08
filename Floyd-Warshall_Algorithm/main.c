#include <stdio.h>
#define SIZE 4
#define INF 99999

void printMatrix(int matrix[SIZE][SIZE]);

void floydWarshall(int graph[SIZE][SIZE]) {
    int dist[SIZE][SIZE];

    // Initialize the solution matrix same as input graph matrix
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            dist[i][j] = graph[i][j];

    // Pick all vertices one by one as the source
    for (int k = 0; k < SIZE; k++) {
        // Pick all vertices as destination for the above picked source
        for (int i = 0; i < SIZE; i++) {
            // If vertex k is on the shortest path from i to j, then update the value of dist[i][j]
            for (int j = 0; j < SIZE; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    printMatrix(dist);
}

void printMatrix(int matrix[SIZE][SIZE]) {
    printf("Shortest distances between every pair of vertices:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int graph[SIZE][SIZE] = {{0, INF, -2, INF},
                             {4, 0, 3, INF},
                             {INF, INF, 0, 2},
                             {-1, INF, INF, 0}};

    floydWarshall(graph);
    return 0;
}