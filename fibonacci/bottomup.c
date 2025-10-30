#include <stdio.h>
#include <time.h>


int nthFibonacci(int n) {

    if (n <= 1) return n;


    int dp[n + 1];


    dp[0] = 0;
    dp[1] = 1;


    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    clock_t start = clock();

    for (int i = 0; i <= n; i++) {
        nthFibonacci(i);
    }

    clock_t end = clock();

    double time_taken_ms = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;
    printf("Time taken: %.3f ms\n", time_taken_ms);

    return 0;
}
