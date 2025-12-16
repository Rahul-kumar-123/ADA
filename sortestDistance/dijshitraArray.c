#include <stdio.h>
#include <limits.h>

#define MAX 50

int main()
{
    int n, e;
    int graph[MAX][MAX];
    int dist[MAX], visited[MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    // Initialize graph
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges (u v w):\n");
    for (int i = 0; i < e; i++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
    }

    int src;
    printf("Enter source node: ");
    scanf("%d", &src);

    // Initialize distances
    for (int i = 0; i < n; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[src] = 0;

    // Dijkstra using linear search O(V²)
    for (int c = 0; c < n - 1; c++)
    {
        int u = -1;
        int min = INT_MAX;

        for (int i = 0; i < n; i++)
            if (!visited[i] && dist[i] < min)
            {
                min = dist[i];
                u = i;
            }

        visited[u] = 1;

        for (int v = 0; v < n; v++)
        {
            if (graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("\nShortest Distances (Array Version):\n");
    for (int i = 0; i < n; i++)
        printf("Node %d: %d\n", i, dist[i]);

    return 0;
}
