#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 26 // Maximum number of nodes (assuming uppercase letters)

// Structure to represent an edge between nodes
struct Edge {
    struct Node *destination;
    struct Edge *next;
};

// Structure to represent a node in the graph
struct Node {
    char data;
    struct Node *next;
    struct Edge *edge;
};

// Function to create a new node with the given data
struct Node *createNode(char data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->edge = NULL;
    return newNode;
}

// Function to create a new edge between nodes
struct Edge *createEdge(struct Node *destination) {
    struct Edge *newEdge = (struct Edge *)malloc(sizeof(struct Edge));
    newEdge->destination = destination;
    newEdge->next = NULL;
    return newEdge;
}

// Function to add an edge between nodes
void addEdge(struct Node *source, struct Node *destination) {
    struct Edge *newEdge = createEdge(destination);
    newEdge->next = source->edge;
    source->edge = newEdge;
}

// Function to print the graph in the specified style
void printGraph(struct Node *head) {
    struct Node *temp = head;
    while (temp != NULL) {
        printf("%c:\n", temp->data);
        struct Edge *edge = temp->edge;
        while (edge != NULL) {
            printf(" -> %c\n", edge->destination->data);
            edge = edge->next;
        }
        printf("\n");
        temp = temp->next;
    }
}

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

void clean(struct Node *head) {
    struct Node *currentNode = head;
    while (currentNode != NULL) {
        struct Node *nextNode = currentNode->next;
        struct Edge *currentEdge = currentNode->edge;
        while (currentEdge != NULL) {
            struct Edge *nextEdge = currentEdge->next;
            free(currentEdge);
            currentEdge = nextEdge;
        }
        free(currentNode);
        currentNode = nextNode;
    }
}

int main() {

    printf("Welcome to Graphs and Warshall's Algorithm\n");

    // Create nodes
    struct Node *nodeA = createNode('A');
    struct Node *nodeB = createNode('B');
    struct Node *nodeD = createNode('D');
    struct Node *nodeC = createNode('C');

    // Connect A to B
    addEdge(nodeA, nodeB);

    // Connect B to D
    addEdge(nodeB, nodeD);

    // Connect D to A and C
    addEdge(nodeD, nodeA);
    addEdge(nodeD, nodeC);

    // Print the graph
    printf("Graph:\n");
    printGraph(nodeA);
    printGraph(nodeB);
    printGraph(nodeD);

    // Calculate and display transitive closure
    int numNodes = 4;                                // Assuming 4 nodes A, B, C, D
    int adjacencyMatrix[MAX_NODES][MAX_NODES] = {0}; // Initialize adjacency matrix with all zeros

    // Populate adjacency matrix based on graph connections
    adjacencyMatrix[0][1] = 1; // A->B
    adjacencyMatrix[1][3] = 1; // B->D
    adjacencyMatrix[3][0] = 1; // D->A
    adjacencyMatrix[3][2] = 1; // D->C

    // Calculate transitive closure
    warshallTransitiveClosure(adjacencyMatrix, numNodes);

    // Display adjacency matrix (transitive closure)
    displayAdjacencyMatrix(adjacencyMatrix, numNodes);

    clean(nodeA);
    clean(nodeB);
    clean(nodeC);
    clean(nodeD);

    return 0;
}