#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateRandomMatrix(int n, int matrix[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = rand() % 100; // Random numbers between 0 and 99
        }
    }
}

void iterativeMatrixMultiplication(int n, int A[n][n], int B[n][n], int C[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main()
{
    int n;
    printf("Enter the size of the matrix : ");
    scanf("%d", &n);

    if (n % 2 != 0)
    {
        printf("Error: n must be a power of 2.\n");
        return -1;
    }

    int mat1[n][n], mat2[n][n], matRes[n][n];

    generateRandomMatrix(n, mat1);
    generateRandomMatrix(n, mat2);

    clock_t start = clock();

    iterativeMatrixMultiplication(n, mat1, mat2, matRes);

    clock_t end = clock();

    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
    printf("Time taken for matrix multiplication: %.3f ms\n", time_taken);

    return 0;
}