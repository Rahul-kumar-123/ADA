#include <stdio.h>
#include<time.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void knapsack_dp(int capacity, int weights[], int profits[], int n)
{

    int C[n + 1][capacity + 1];
    printf("Space taken by DP table: (%.2f KB)\n", (double)sizeof(C) / 1024);

    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= capacity; w++)
        {

            if (i == 0 || w == 0)
            {
                C[i][w] = 0;
            }

            else if (weights[i - 1] > w)
            {
                C[i][w] = C[i - 1][w];
            }
            else
            {
                int profit_without_item = C[i - 1][w];
                int profit_with_item = profits[i - 1] + C[i - 1][w - weights[i - 1]];
                C[i][w] = max(profit_with_item, profit_without_item);
            }
        }
    }

    int max_profit = C[n][capacity];
    printf("Maximum profit: %d\n", max_profit);

    printf("Items to include for maximum profit:\n");
    int total_weight = 0;
    int w = capacity;
    for (int i = n; i > 0 && max_profit > 0; i--)
    {
        if (C[i][w] != C[i - 1][w])
        {
            printf("  - Item %d (Weight: %d, Profit: %d)\n", i, weights[i - 1], profits[i - 1]);
            total_weight += weights[i - 1];
            w = w - weights[i - 1];
        }
    }
    printf("Total weight of selected items: %d\n", total_weight);
}

int main()
{
    int n, capacity;

    printf("Enter the number of items: ");
    scanf("%d", &n);

    int profits[n];
    int weights[n];

    printf("Enter the weight and profit of each item:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Item %d: ", i + 1);
        scanf("%d %d", &weights[i], &profits[i]);
    }

    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &capacity);

    clock_t start, end;
    double cpuTimeUsed;

    start = clock();
    knapsack_dp(capacity, weights, profits, n);
    end = clock();

    cpuTimeUsed = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    printf("Time taken to execute: %f milliseconds\n", cpuTimeUsed);

    return 0;
}
