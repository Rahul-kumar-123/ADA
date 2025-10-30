#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binarySearch(int arr[], int size, int key)
{
    int low = 0;
    int high = size - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (arr[mid] == key)
        {
            return mid;
        }

        if (key > arr[mid])
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1;
}

void initailizeArray(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = i + 1;
    }
}

int main()
{
    int n = 0;
    printf("Enter number : ");
    scanf("%d", &n);
    printf("Allocating space...\n");
    int REPEAT = 1000000;
    int *arr = (int *)malloc(sizeof(int) * n);
    if (arr == NULL)
    {
        printf("Allocation failed !");
        return -1;
    }
    printf("Space allocated.\n");
    printf("Generating elements...\n");
    initailizeArray(arr, n);
    printf("Array generated.\n");
    printf("Search started...\n");
    clock_t start = clock();
    for (int i = 0; i < REPEAT; i++)
    {
        int res = binarySearch(arr, n, 0);
    }

    clock_t end = clock();
    printf("Search completed...\n");
    //micro second
    double time_taken = (((double)(end - start) / CLOCKS_PER_SEC) / REPEAT) * 1000000;
    printf("Time taken %f for %d", time_taken, n);

    return 0;
}