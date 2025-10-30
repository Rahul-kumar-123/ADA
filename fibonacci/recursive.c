#include <stdio.h>
#include <time.h>

long long int recursiveFibonacci(int n)
{
    if (n <= 1)
        return n;
    return recursiveFibonacci(n - 1) + recursiveFibonacci(n - 2);
}

int main()
{
    int n;
    printf("Enter number of terms: ");
    scanf("%d", &n);

    clock_t start = clock();

    for (int i = 0; i < n; i++)
        recursiveFibonacci(i);

    clock_t end = clock();

    double time_taken_ms = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;
    printf("Recursive time for n=%d: %.3f ms\n", n, time_taken_ms);

    return 0;
}

