#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int bubbleSort(int arr[], int size)
{

    for (int i = 0; i < size - 1; i++)
    {

        for (int j = 0; j < size - i - 1; j++)
        {

            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
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
    bubbleSort(arr, n);
    clock_t end = clock();
    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
    printf("Time taken %f for %d\n", time_taken, n);

    return 0;
}