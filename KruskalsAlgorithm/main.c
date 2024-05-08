#include <stdio.h>
#include <stdlib.h>

// A structure to represent a weighted edge in graph
struct Edge {
    int src, dest, weight;
};

// A structure to represent a connected, undirected
// and weighted graph
struct Graph {
    int V, E;
    struct Edge *edge;
};

// Creates a graph with V vertices and E edges
struct Graph *createGraph(int V, int E) {
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge *)malloc(graph->E * sizeof(struct Edge));
    return graph;
}

// A structure to represent a subset for union-find
struct subset {
    int parent;
    int rank;
};

// A utility function to find set of an element i
int find(struct subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// A function that does union of two sets of x and y
void Union(struct subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Compare two edges according to their weights.
// Used in qsort() for sorting an array of edges
int myComp(const void *a, const void *b) {
    struct Edge *a1 = (struct Edge *)a;
    struct Edge *b1 = (struct Edge *)b;
    return a1->weight > b1->weight;
}

// The main function to construct MST using Kruskal's algorithm
struct Edge *KruskalMST(struct Graph *graph, int *edgeCount) {
    int V = graph->V;
    struct Edge *result = malloc(V * sizeof(struct Edge)); // This will store the resultant MST
    int e = 0;                                             // An index variable, used for result[]
    int i = 0;                                             // An index variable, used for sorted edges

    // Step 1:  Sort all the edges in non-decreasing order of their weight
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);

    // Allocate memory for creating V subsets
    struct subset *subsets = (struct subset *)malloc(V * sizeof(struct subset));

    // Create V subsets with single elements
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Number of edges to be taken is equal to V-1
    while (e < V - 1 && i < graph->E) {
        // Step 2: Pick the smallest edge. And increment the index for next iteration
        struct Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge doesn't cause a cycle, include it in result and increment the index of result for the next edge
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
        // Else discard the next_edge
    }

    *edgeCount = e;
    return result;
}

// Print MST edges with better visualization and minimum distance
void printMST(struct Edge result[], int e) {
    int totalDistance = 0;
    printf("Constructed Minimum Spanning Tree (MST):\n");
    printf("Edge   | Weight\n");
    printf("---------------\n");
    for (int i = 0; i < e; ++i) {
        printf("%c - %c   | %d\n", result[i].src + 'A', result[i].dest + 'A', result[i].weight);
        totalDistance += result[i].weight;
    }
    printf("Minimum distance of MST: %d\n", totalDistance);
}

int main() {
    int V = 4; // Number of vertices in graph
    int E = 5; // Number of edges in graph
    struct Graph *graph = createGraph(V, E);

    // add edge 0-1
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = 10;

    // add edge 0-2
    graph->edge[1].src = 0;
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 6;

    // add edge 0-3
    graph->edge[2].src = 0;
    graph->edge[2].dest = 3;
    graph->edge[2].weight = 5;

    // add edge 1-3
    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 15;

    // add edge 2-3
    graph->edge[4].src = 2;
    graph->edge[4].dest = 3;
    graph->edge[4].weight = 4;

    int edgeCount;                                       // Declare the variable 'edgeCount'
    struct Edge *result = KruskalMST(graph, &edgeCount); // Pass 'edgeCount' as an argument to the function call

    printMST(result, edgeCount); // Call the 'printMST' function with 'result' and 'edgeCount' as arguments

    return 0;
}
