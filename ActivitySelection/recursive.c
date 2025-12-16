#include <stdio.h>
#include <stdlib.h>

struct Activity
{
    int start;
    int end;
};

// --- MERGE SORT FUNCTIONS (Same as before) ---
void merge(struct Activity arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    struct Activity L[n1], R[n2];

    for (i = 0; i < n1; i++) L[i] = arr[left + i];
    for (j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    i = 0; j = 0; k = left;
    while (i < n1 && j < n2)
    {
        if (L[i].end <= R[j].end) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
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

// --- NEW RECURSIVE SELECTOR FUNCTION ---
void recursiveSelect(struct Activity arr[], int last_selected_idx, int current_idx, int n)
{
    // Base Case: If we have checked all activities
    if (current_idx >= n)
        return;

    // Greedy Step: Check compatibility
    if (arr[current_idx].start >= arr[last_selected_idx].end)
    {
        // Activity is compatible -> Select it
        printf("Activity (Start: %d, End: %d)\n", arr[current_idx].start, arr[current_idx].end);
        
        // Recurse: 'current' becomes the new 'last_selected'
        recursiveSelect(arr, current_idx, current_idx + 1, n);
    }
    else
    {
        // Activity not compatible -> Skip it
        // Recurse: 'last_selected' stays the same, move to next index
        recursiveSelect(arr, last_selected_idx, current_idx + 1, n);
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

    // 1. Sort the activities by end time
    mergeSort(activities, 0, n - 1);

    printf("\nSelected activities:\n");

    // 2. Select the first activity manually (Greedy choice property always picks the first sorted item)
    printf("Activity (Start: %d, End: %d)\n", activities[0].start, activities[0].end);

    // 3. Call the recursive function
    // Start checking from index 1, with index 0 being the "last selected"
    recursiveSelect(activities, 0, 1, n);

    free(activities);
    return 0;
}