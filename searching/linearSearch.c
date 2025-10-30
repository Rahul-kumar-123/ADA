#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int linearSearch(int *arr, int size, int key)
{
    for (int i = 0; i < size; i++)
    {
        if (key == arr[i])
        {
            return i;
        }
    }
    return -1;
}

void generateRandomArray(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        int rnd = rand() % 100;
        arr[i] = rnd;
    }
}

int main()
{
    int n = 0;
    printf("Enter number : ");
    scanf("%d", &n);
    printf("Allocating space...\n");
    int *arr = (int *)malloc(sizeof(int) * n);
    if (arr == NULL)
    {
        printf("Allocation failed !");
        return -1;
    }
    printf("Space allocated.\n");
    printf("Generating elements...\n");
    generateRandomArray(arr, n);
    printf("Array generated.\n");
    printf("Search started...\n");
    clock_t start = clock();
    linearSearch(arr, n, 200);
    clock_t end = clock();
     printf("Search completed...\n");
    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC);
    printf("Time taken %f for %d", time_taken, n);

    return 0;
}