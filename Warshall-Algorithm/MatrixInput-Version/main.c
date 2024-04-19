#include <stdio.h>
#include <stdlib.h>

// set the maximum number of nodes before input
#define MAX_NODES 5 // Maximum number of nodes

// Function to perform Warshall's Algorithm to calculate transitive closure
void warshallTransitiveClosure(int adjacencyMatrix[MAX_NODES][MAX_NODES], int numNodes) {
    int i, j, k;

    // Warshall's Algorithm
    for (k = 0; k < numNodes; k++) {
        for (i = 0; i < numNodes; i++) {
            for (j = 0; j < numNodes; j++) {
                adjacencyMatrix[i][j] = adjacencyMatrix[i][j] || (adjacencyMatrix[i][k] && adjacencyMatrix[k][j]);
            }
        }
    }
}

// Function to display the adjacency matrix
void displayAdjacencyMatrix(int adjacencyMatrix[MAX_NODES][MAX_NODES], int numNodes) {
    printf("Adjacency Matrix (Transitive Closure):\n");
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            printf("%d ", adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Define the adjacency matrix based on the given connections
    int adjacencyMatrix[MAX_NODES][MAX_NODES] = {
        {0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 1},
        {0, 0, 1, 0, 0}};

    // Calculate transitive closure
    warshallTransitiveClosure(adjacencyMatrix, MAX_NODES);

    // Display the adjacency matrix (transitive closure)
    displayAdjacencyMatrix(adjacencyMatrix, MAX_NODES);

    return 0;
}
