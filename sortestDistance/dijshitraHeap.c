#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 50

struct Node
{
    int vertex, weight;
    struct Node *next;
};

struct PQ
{
    int vertex, dist;
};

struct Node *adj[MAX];
int size = 0;
struct PQ heap[1000];

// Min-heap helpers
void swap(struct PQ *a, struct PQ *b)
{
    struct PQ temp = *a;
    *a = *b;
    *b = temp;
}

void push(int v, int d)
{
    heap[++size].vertex = v;
    heap[size].dist = d;

    int i = size;
    while (i > 1 && heap[i].dist < heap[i / 2].dist)
    {
        swap(&heap[i], &heap[i / 2]);
        i /= 2;
    }
}

struct PQ pop()
{
    struct PQ top = heap[1];
    heap[1] = heap[size--];

    int i = 1;
    while (1)
    {
        int left = 2 * i, right = 2 * i + 1, smallest = i;

        if (left <= size && heap[left].dist < heap[smallest].dist)
            smallest = left;
        if (right <= size && heap[right].dist < heap[smallest].dist)
            smallest = right;

        if (smallest == i)
            break;

        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }
    return top;
}

void addEdge(int u, int v, int w)
{
    struct Node *new = malloc(sizeof(struct Node));
    new->vertex = v;
    new->weight = w;
    new->next = adj[u];
    adj[u] = new;
}

int main()
{
    int n, e;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    for (int i = 0; i < n; i++)
        adj[i] = NULL;

    printf("Enter edges (u v w):\n");
    for (int i = 0; i < e; i++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }

    int src;
    printf("Enter source node: ");
    scanf("%d", &src);

    int dist[MAX];
    int visited[MAX] = {0};

    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX;

    dist[src] = 0;
    push(src, 0);

    while (size > 0)
    {
        struct PQ node = pop();
        int u = node.vertex;

        if (visited[u])
            continue;
        visited[u] = 1;

        struct Node *temp = adj[u];

        while (temp != NULL)
        {
            int v = temp->vertex;
            int w = temp->weight;

            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                push(v, dist[v]);
            }
            temp = temp->next;
        }
    }

    printf("\nShortest Distances (Min-Heap Version):\n");
    for (int i = 0; i < n; i++)
        printf("Node %d: %d\n", i, dist[i]);

    return 0;
}
