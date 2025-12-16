#include <stdio.h>
#include <limits.h>

#define MAX 100

struct Edge
{
    int u, v, w;
};

int main()
{
    int n, e;
    struct Edge edges[MAX];
    int dist[MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges (u v w):\n");
    for (int i = 0; i < e; i++)
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);

    int src;
    printf("Enter source node: ");
    scanf("%d", &src);

    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX;

    dist[src] = 0;

    // Relax edges V-1 times
    for (int i = 1; i <= n - 1; i++)
    {
        for (int j = 0; j < e; j++)
        {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;

            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    // Check for negative cycle
    for (int j = 0; j < e; j++)
    {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].w;

        if (dist[u] != INT_MAX && dist[u] + w < dist[v])
        {
            printf("\nGraph contains negative weight cycle.\n");
            return 0;
        }
    }

    printf("\nShortest Distances using Bellman-Ford:\n");
    for (int i = 0; i < n; i++)
        printf("Node %d: %d\n", i, dist[i]);

    return 0;
}
