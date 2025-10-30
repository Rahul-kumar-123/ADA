#include <stdio.h>

int linearSearch(int arr[], int size, int key)
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

int main()
{
    int arr[] = {78, 56, 23, 89, 45, 5, 2};
    int size = sizeof(arr) / sizeof(arr[0]);
    int key;
    printf("Enter key : ");
    scanf("%d", &key);
    printf("Index of key is %d", linearSearch(arr, size, key));

    return 0;
}