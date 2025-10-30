#include <stdio.h>
#include <time.h>

long long int memo[1000];

long long int fibTopDown(int n)
{
    if (n <= 1)
        return n;
    if (memo[n] != -1)
        return memo[n];
    memo[n] = fibTopDown(n - 1) + fibTopDown(n - 2);
    return memo[n];
}

int main()
{
    int n;
    printf("Enter number of terms: ");
    scanf("%d", &n);

    for (int i = 0; i < 1000; i++)
        memo[i] = -1;

    clock_t start = clock();

    for (int i = 0; i < n; i++)
        fibTopDown(i);

    clock_t end = clock();

    double time_taken_ms = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;
    printf("Top-Down DP time for n=%d: %.3f ms\n", n, time_taken_ms);

    return 0;
}


