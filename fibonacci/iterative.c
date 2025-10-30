#include <stdio.h>
#include <time.h>

void iterativeFibonacci(int n)
{
    int t1 = 0, t2 = 1, nextTerm;
    for (int i = 0; i < n; i++)
    {
        nextTerm = t1 + t2;
        t1 = t2;
        t2 = nextTerm;
    }
}

int main()
{
    int n;
    printf("Enter number of terms: ");
    scanf("%d", &n);

    clock_t start = clock();

    iterativeFibonacci(n);

    clock_t end = clock();

    double time_taken_ms = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;
    printf("Iterative time for n=%d: %.3f ms\n", n, time_taken_ms);

    return 0;
}

