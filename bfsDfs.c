#include <stdio.h>
#include <stdlib.h>

#define MAX 50

struct Node
{
    int data;
    struct Node *next;
};

struct Node *adjList[MAX];
int adjMatrix[MAX][MAX];
int visited[MAX];
int queue[MAX], front = -1, rear = -1;;

void enqueue(int x)
{
    if (rear == MAX - 1)
        return;
    if (front == -1)
        front = 0;;;
    queue[++rear] = x;
}

int dequeue()
{
    if (front > rear || front == -1)
        return -1;
    return queue[front++];
}

void addEdgeList(int u, int v)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = v;
    newNode->next = adjList[u];
    adjList[u] = newNode;
}

void DFS(int start)
{
    printf("%d ", start);
    visited[start] = 1;

    struct Node *temp = adjList[start];
    while (temp != NULL)
    {
        if (!visited[temp->data])
        {
            DFS(temp->data);
        }
        temp = temp->next;
    }
}

void BFS(int start)
{
    for (int i = 0; i < MAX; i++)
        visited[i] = 0;

    enqueue(start);
    visited[start] = 1;

    while (front <= rear)
    {
        int node = dequeue();
        printf("%d ", node);

        struct Node *temp = adjList[node];
        while (temp != NULL)
        {
            if (!visited[temp->data])
            {
                enqueue(temp->data);
                visited[temp->data] = 1;
            }
            temp = temp->next;
        }
    }
}

int main()
{
    int n, e;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    // Initialize structures
    for (int i = 0; i < n; i++)
    {
        adjList[i] = NULL;
        for (int j = 0; j < n; j++)
        {
            adjMatrix[i][j] = 0;
        }
    }

    printf("Enter edges (u v): \n");
    for (int i = 0; i < e; i++)
    {
        int u, v;
        scanf("%d", &u);
        scanf("%d", &v);

        // Adjacency Matrix
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;

        // Adjacency List
        addEdgeList(u, v);
        addEdgeList(v, u);
    }

    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", adjMatrix[i][j]);
        printf("\n");
    }

    printf("\nAdjacency List:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d -> ", i);
        struct Node *temp = adjList[i];
        while (temp != NULL)
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++)
        visited[i] = 0;
    int start;
    printf("\nEnter starting node for DFS and BFS: ");
    scanf("%d", &start);

    printf("DFS Traversal: ");
    DFS(start);

    printf("\nBFS Traversal: ");
    BFS(start);

    return 0;
}
