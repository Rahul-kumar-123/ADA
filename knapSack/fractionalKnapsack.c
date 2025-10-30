#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double fractionalKnapsack(int capacity, int weights[], int values[], int n)
{
    float ratios[n];
    int indices[n];

    for (int i = 0; i < n; i++)
    {
        ratios[i] = (double)values[i] / weights[i];
        indices[i] = i;
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (ratios[indices[i]] < ratios[indices[j]])
            {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }
    double totalValue = 0;

    for (int i = 0; i < n; i++)
    {
        int idx = indices[i];
        if (capacity >= weights[idx])
        {
            capacity -= weights[idx];
            totalValue += values[idx];
            printf("Adding... item %d completely. Remaining capacity = %d - %d = %d total value = %f\n", idx + 1, capacity + weights[idx], weights[idx], capacity, totalValue);
        }
        else
        {
            totalValue += ratios[idx] * capacity;
            printf("Adding... fraction %f of item %d. Remaining capacity = %d total value = %f\n", capacity / (float)weights[i], idx + 1, capacity - capacity, totalValue);
            break;
        }
    }
    return totalValue;
}

int main()
{
    int n, capacity;
    printf("Enter the number of items: ");
    scanf("%d", &n);

    int weights[n], values[n];
    printf("Enter the weight and value of each item:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Item %d: ", i + 1);
        scanf("%d %d", &weights[i], &values[i]);
    }

    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &capacity);
    clock_t start, end;
    double cpuTimeUsed;

    start = clock();
    double maxValue = fractionalKnapsack(capacity, weights, values, n);
    end = clock();
    cpuTimeUsed = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    int totalSpace = n*sizeof(float) + n*sizeof(int);

    printf("Maximum value in the knapsack: %.2f\n", maxValue);
    printf("Algorithm Execution Time: %f milli seconds\n", cpuTimeUsed);
    printf("Extra space taken : %d bytes \n", totalSpace);

    return 0;
}