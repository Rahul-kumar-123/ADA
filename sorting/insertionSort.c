#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int insertionSort(int arr[], int size)
{

    for (int i = 1; i < size; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
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
    int *arr = (int *)malloc(sizeof(int) * n);
    if (arr == NULL)
    {
        printf("Allocation failed !");
        return -1;
    }
    generateRandomArray(arr, n);
    clock_t start = clock();
    insertionSort(arr, n);
    clock_t end = clock();
    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
    printf("Time taken %f for %d\n", time_taken, n);

    return 0;
}