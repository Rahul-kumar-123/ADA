#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// --- Structure Definitions ---

// Represents a node in the adjacency list
struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
};

// Represents the adjacency list for a specific vertex
struct AdjList {
    struct AdjListNode* head;
};

// Represents the Graph itself
struct Graph {
    int V; // Number of vertices
    struct AdjList* array;
};

// --- Graph Helper Functions ---

// Function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest, int weight) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph of V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;

    // Create an array of adjacency lists
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

    // Initialize each adjacency list as empty by making head NULL
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    // Add an edge from src to dest
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// --- Prim's Algorithm Functions ---

// Function to find the vertex with the minimum key value
// from the set of vertices not yet included in MST
int minKey(int key[], bool mstSet[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

// Function to print the constructed MST
void printMST(int parent[], int n, struct Graph* graph) {
    printf("Edge \tWeight\n");
    // Starting from 1 because parent[0] is -1 (root)
    for (int i = 1; i < n; i++) {
        // We need to find the weight between i and parent[i]
        // In a matrix this is easy, in a list we iterate to find it for display
        struct AdjListNode* pCrawl = graph->array[i].head;
        while(pCrawl != NULL) {
            if(pCrawl->dest == parent[i]) {
                printf("%d - %d \t%d \n", parent[i], i, pCrawl->weight);
                break;
            }
            pCrawl = pCrawl->next;
        }
    }
}

// Main function to construct MST using Prim's algorithm
void PrimMST(struct Graph* graph) {
    int V = graph->V;
    int parent[V]; // Array to store constructing MST
    int key[V];    // Key values used to pick minimum weight edge
    bool mstSet[V]; // To represent set of vertices included in MST

    // Initialize all keys as INFINITE and mstSet[] as false
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    // Always include first 1st vertex in MST.
    key[0] = 0;     // Make key 0 so that this vertex is picked first
    parent[0] = -1; // First node is always root of MST

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++) {
        
        // Pick the minimum key vertex from the set of vertices
        // not yet included in MST
        int u = minKey(key, mstSet, V);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Iterate through all adjacent vertices of the picked vertex u
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;

            // If v is not in mstSet and weight of (u,v) is smaller
            // than current key of v
            if (mstSet[v] == false && pCrawl->weight < key[v]) {
                parent[v] = u;
                key[v] = pCrawl->weight;
            }
            pCrawl = pCrawl->next;
        }
    }

    // Print the constructed MST
    printMST(parent, V, graph);
}

// --- Main Driver ---
int main() {
    int V = 5;
    struct Graph* graph = createGraph(V);

    // Creating the graph (Example)
    // 0 --(2)-- 1 --(3)-- 2
    // |       / |       / 
    //(6)   (8) (5)   (7) 
    // |   /     |   /     
    // 3 --(9)-- 4 
    
    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 3, 6);
    addEdge(graph, 1, 2, 3);
    addEdge(graph, 1, 3, 8);
    addEdge(graph, 1, 4, 5);
    addEdge(graph, 2, 4, 7);
    addEdge(graph, 3, 4, 9);
    // Note: Edge 2-4 (weight 9) in typical examples helps test cycles
    // Adding edge 2 to 4 with weight 7 as per standard examples

    printf("Prim's Minimum Spanning Tree (Adjacency List):\n");
    PrimMST(graph);

    return 0;
}