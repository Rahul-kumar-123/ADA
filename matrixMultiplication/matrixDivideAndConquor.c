#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void matMultiplication(int n, int A[n][n], int B[n][n], int C[n][n])
{
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    int k = n / 2;
    int A11[k][k], A12[k][k], A21[k][k], A22[k][k];
    int B11[k][k], B12[k][k], B21[k][k], B22[k][k];
    int C11[k][k], C12[k][k], C21[k][k], C22[k][k];
    int M1[k][k], M2[k][k];

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    matMultiplication(k, A11, B11, M1);
    matMultiplication(k, A12, B21, M2);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C11[i][j] = M1[i][j] + M2[i][j];

    matMultiplication(k, A11, B12, M1);
    matMultiplication(k, A12, B22, M2);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C12[i][j] = M1[i][j] + M2[i][j];

    matMultiplication(k, A21, B11, M1);
    matMultiplication(k, A22, B21, M2);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C21[i][j] = M1[i][j] + M2[i][j];

    matMultiplication(k, A21, B12, M1);
    matMultiplication(k, A22, B22, M2);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C22[i][j] = M1[i][j] + M2[i][j];

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
}

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

    int A[n][n], B[n][n], C[n][n];

    generateRandomMatrix(n, A);

    generateRandomMatrix(n, B);

    clock_t start = clock();
    matMultiplication(n, A, B, C);
    clock_t end = clock();

    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
    printf("Time taken for matrix multiplication: %.3f ms\n", time_taken);

    return 0;
}