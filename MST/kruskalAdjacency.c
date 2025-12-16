#include <stdio.h>
#include <stdlib.h>

// --- Adjacency List Structures ---
struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
};

struct Graph {
    int V; // Vertices
    int E; // Edges
    struct AdjListNode** array; // Adjacency lists
};

// --- Edge Structure ---
typedef struct {
    int u, v, weight;
} Edge;

// --- Union-Find Structures ---
typedef struct {
    int parent;
    int rank;
} Subset;

// Helper: Create new adjacency list node
struct AdjListNode* newAdjListNode(int dest, int weight) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Helper: Create graph
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = 0;
    graph->array = (struct AdjListNode**)malloc(V * sizeof(struct AdjListNode*));
    for (int i = 0; i < V; ++i)
        graph->array[i] = NULL;
    return graph;
}

// Helper: Add undirected edge
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src];
    graph->array[src] = newNode;

    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest];
    graph->array[dest] = newNode;
    
    graph->E++; 
}

// --- MERGE SORT IMPLEMENTATION ---

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(Edge arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    Edge* L = (Edge*)malloc(n1 * sizeof(Edge));
    Edge* R = (Edge*)malloc(n2 * sizeof(Edge));

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i].weight <= R[j].weight) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

// Main function that sorts arr[l..r] using merge()
void mergeSort(Edge arr[], int l, int r) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// --- Union-Find Operations ---
int findSet(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = findSet(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void unionSets(Subset subsets[], int x, int y) {
    int xroot = findSet(subsets, x);
    int yroot = findSet(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// --- Kruskal's Function ---
void kruskalMST(struct Graph* graph) {
    int V = graph->V;
    int E = graph->E;
    
    // 1. Convert Adjacency List to Edge Array
    Edge* allEdges = (Edge*)malloc(E * sizeof(Edge));
    int edgeCount = 0;

    for (int u = 0; u < V; u++) {
        struct AdjListNode* pCrawl = graph->array[u];
        while (pCrawl) {
            // Only add edge if u < dest to avoid duplicates in undirected graph
            if (u < pCrawl->dest) {
                allEdges[edgeCount].u = u;
                allEdges[edgeCount].v = pCrawl->dest;
                allEdges[edgeCount].weight = pCrawl->weight;
                edgeCount++;
            }
            pCrawl = pCrawl->next;
        }
    }

    // 2. Sort the edges using Merge Sort
    mergeSort(allEdges, 0, E - 1);

    // 3. Prepare Union-Find
    Subset* subsets = (Subset*)malloc(V * sizeof(Subset));
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    Edge results[V - 1]; 
    int e = 0; 
    int i = 0; 

    // 4. Iterate and Build MST
    while (e < V - 1 && i < E) {
        Edge next_edge = allEdges[i++];

        int x = findSet(subsets, next_edge.u);
        int y = findSet(subsets, next_edge.v);

        if (x != y) {
            results[e++] = next_edge;
            unionSets(subsets, x, y);
        }
    }

    // Print Result
    printf("Edges in the Constructed MST (Sorted via Merge Sort):\n");
    int minCost = 0;
    for (i = 0; i < e; ++i) {
        printf("%c -- %c == %d\n", results[i].u + 'A', results[i].v + 'A', results[i].weight);
        minCost += results[i].weight;
    }
    printf("Total Cost: %d\n", minCost);

    free(allEdges);
    free(subsets);
}

int main() {
    int V = 4;
    struct Graph* graph = createGraph(V);

    // Add edges (A=0, B=1, C=2, D=3)
    addEdge(graph, 0, 1, 3); // A-B
    addEdge(graph, 0, 2, 1); // A-C
    addEdge(graph, 1, 2, 7); // B-C
    addEdge(graph, 1, 3, 5); // B-D
    addEdge(graph, 2, 3, 2); // C-D

    kruskalMST(graph);

    return 0;
}