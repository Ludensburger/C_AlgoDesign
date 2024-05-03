#include <limits.h>  // Include this for INT_MAX
#include <stdbool.h> // Include this for bool
#include <stdio.h>

#define V 7 // Number of vertices in the graph

int minWeight(int weight[], bool mstSet[]) {

    int min = INT_MAX;
    int min_index;

    // Find the vertex with minimum weight value, from the set of vertices not yet included in MST
    for (int v = 0; v < V; v++) {

        // If vertex v is not included in MST and weight[v] is less than min
        // Then update min and min_index
        // ADD IF THE VERTEX IS MINIMUM AND NOT YET INCLUDED IN MST
        if (mstSet[v] == false && weight[v] < min) {

            // update the minimum weight
            // and the minimum index
            min = weight[v];
            min_index = v;
        }
    }

    // return the minimum weight vertex
    return min_index;
}

void printSumOfMinWeights(int weight[]) {
    int sum = 0;
    for (int i = 0; i < V; i++) {
        sum += weight[i];
    }
    printf("Sum of all minimum weights: %d\n", sum);
}

void printMST(int parent[], int graph[V][V]) {
    printf("Edge   Weight\n");
    for (int i = 1; i < V; i++) {
        printf("%c - %c    %d \n", parent[i] + 'A', i + 'A', graph[i][parent[i]]);
    }
}

void primMST(int graph[V][V]) {

    int parent[V];
    int weight[V];
    bool mstSet[V];

    // Initialize all weights as INFINITE and mstSet[] as false
    for (int i = 0; i < V; i++) {

        // set the weight to the maximum integer value
        // and set the mstSet to false
        weight[i] = INT_MAX;
        mstSet[i] = false;
    }

    // STEP 1: Choose a starting vertex
    // In this case, the starting vertex is the first vertex
    // FROM A with weight 0

    weight[0] = 0;
    parent[0] = -1;

    // STEP 2: Keep including connected edges to the MST set until V-1 edges are included
    // FIND ALL NODES THAT CONNECT A
    for (int count = 0; count < V - 1; count++) {

        // Pick the minimum weight vertex from the set of vertices not yet included in MST
        // FIND THE MINIMUM WEIGHT OF THE EDGES CONNECTED TO A
        int u = minWeight(weight, mstSet);

        // then include the vertex to the MST set
        mstSet[u] = true;

        // Update weight value and parent index of the adjacent vertices of the picked vertex.
        // so if the starting vertex is 0, then we will update the weight according to the minimum weight of the edges connected to 0
        // FROM A TO B or could be A TO C, it depends on the minimum weight of the edges
        for (int v = 0; v < V; v++) {

            // Update the weight value of the vertex if the graph[u][v] is not 0
            // and the vertex is not included in the MST set
            // and the weight value of the vertex is greater than the weight of the edge
            if (graph[u][v] &&
                mstSet[v] == false &&
                graph[u][v] < weight[v]) {

                // update to the minimum weight of the edges connected to the vertex
                parent[v] = u;

                // update the weight value of the vertex
                weight[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph);
    printSumOfMinWeights(weight);
}

int main() {
    int graph[V][V] = {
        // 1   2    3    4    5    6    7
        {0, 28, 0, 0, 0, 10, 0},  // 1
        {28, 0, 16, 0, 0, 0, 14}, // 2
        {0, 16, 0, 12, 0, 0, 0},  // 3
        {0, 0, 12, 0, 22, 0, 0},  // 4
        {0, 0, 0, 22, 0, 25, 24}, // 5
        {10, 0, 0, 0, 25, 0, 0},  // 6
        {0, 14, 0, 0, 24, 0, 0}   // 7
    };

    primMST(graph);

    return 0;
}