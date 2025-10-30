#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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
    quickSort(arr, 0, n - 1);
    clock_t end = clock();
    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
    printf("Time taken %f for %d\n", time_taken, n);

    return 0;
}