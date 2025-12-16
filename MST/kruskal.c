#include <stdio.h>
#include <stdlib.h>

int comparator(const void *p1, const void *p2)
{
    const int *a = (const int *)p1;
    const int *b = (const int *)p2;
    return a[2] - b[2];
}
void makeset(int parent[], int rank[], int n)
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
}
int findparent(int parent[], int component)
{
    if (parent[component] == component)
        return component;

    return parent[component] = findparent(parent, parent[component]);
}
void unionset(int u, int v, int parent[], int rank[], int n)
{
    u = findparent(parent, u);
    v = findparent(parent, v);
    if (u != v)
    {
        if (rank[u] < rank[v])
        {
            parent[u] = v;
        }
        else if (rank[v] < rank[u])
            parent[v] = u;
        else
        {
            parent[v] = u;
            rank[u]++;
        }
    }
}
int kruskal(int n, int edge[n][3])
{
    qsort(edge, n, sizeof(edge[0]), comparator);
    int parent[n];
    int rank[n];
    makeset(parent, rank, n);
    int mincost = 0;
    for (int i = 0; i < n; i++)
    {
        int v1 = findparent(parent, edge[i][0]);
        int v2 = findparent(parent, edge[i][1]);
        int wt = edge[i][2];
        if (v1 != v2)
        {
            unionset(v1, v2, parent, rank, n);
            mincost += wt;
        }
    }
    return mincost;
}
int main()
{
    int edge[5][3] = {{0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}};
    printf("%d", kruskal(5, edge));
    return 0;
}