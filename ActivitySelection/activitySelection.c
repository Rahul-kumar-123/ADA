#include <stdio.h>
#include <stdlib.h>

struct Activity
{
    int start;
    int end;
};

void merge(struct Activity arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    struct Activity L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (L[i].end <= R[j].end)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(struct Activity arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main()
{
    int n;
    printf("Enter number of activities: ");
    scanf("%d", &n);

    struct Activity *activities = malloc(n * sizeof(struct Activity));

    for (int i = 0; i < n; i++)
    {
        printf("Enter start time and end time for activity %d: ", i + 1);
        scanf("%d %d", &activities[i].start, &activities[i].end);
    }

    mergeSort(activities, 0, n - 1);

    printf("\nSelected activities:\n");

    int i = 0;
    printf("Activity (Start: %d, End: %d)\n", activities[i].start, activities[i].end);

    for (int j = 1; j < n; j++)
    {
        if (activities[j].start >= activities[i].end)
        {
            printf("Activity (Start: %d, End: %d)\n", activities[j].start, activities[j].end);
            i = j;
        }
    }

    free(activities);

    return 0;
}