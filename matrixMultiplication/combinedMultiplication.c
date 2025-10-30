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

void add(int n, int A[n][n], int B[n][n], int C[n][n])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(int n, int A[n][n], int B[n][n], int C[n][n])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
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

void divideConquor(int n, int A[n][n], int B[n][n], int C[n][n])
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

    divideConquor(k, A11, B11, M1);
    divideConquor(k, A12, B21, M2);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C11[i][j] = M1[i][j] + M2[i][j];

    divideConquor(k, A11, B12, M1);
    divideConquor(k, A12, B22, M2);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C12[i][j] = M1[i][j] + M2[i][j];

    divideConquor(k, A21, B11, M1);
    divideConquor(k, A22, B21, M2);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C21[i][j] = M1[i][j] + M2[i][j];

    divideConquor(k, A21, B12, M1);
    divideConquor(k, A22, B22, M2);
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

void strassen(int n, int A[n][n], int B[n][n], int C[n][n])
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
    int P1[k][k], P2[k][k], P3[k][k], P4[k][k], P5[k][k], P6[k][k], P7[k][k];
    int temp1[k][k], temp2[k][k];
    for (int i = 0; i < k; i++)
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
    add(k, A11, A22, temp1);
    add(k, B11, B22, temp2);
    strassen(k, temp1, temp2, P1);
    add(k, A21, A22, temp1);
    strassen(k, temp1, B11, P2);
    subtract(k, B12, B22, temp1);
    strassen(k, A11, temp1, P3);
    subtract(k, B21, B11, temp1);
    strassen(k, A22, temp1, P4);
    add(k, A11, A12, temp1);
    strassen(k, temp1, B22, P5);
    subtract(k, A21, A11, temp1);
    add(k, B11, B12, temp2);
    strassen(k, temp1, temp2, P6);
    subtract(k, A12, A22, temp1);
    add(k, B21, B22, temp2);
    strassen(k, temp1, temp2, P7);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
        {
            C11[i][j] = P1[i][j] + P4[i][j] - P5[i][j] + P7[i][j];
            C12[i][j] = P3[i][j] + P5[i][j];
            C21[i][j] = P2[i][j] + P4[i][j];
            C22[i][j] = P1[i][j] - P2[i][j] + P3[i][j] + P6[i][j];
        }
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <matrix_size>\n", argv[0]);
        return -1;
    }

    int n = atoi(argv[1]);

    if (n <= 0 || (n & (n - 1)) != 0)
    {
        printf("Error: n must be a positive power of 2.\n");
        return -1;
    }

    int mat1[n][n], mat2[n][n], matRes[n][n];
    generateRandomMatrix(n, mat1);
    generateRandomMatrix(n, mat2);

    clock_t start1 = clock();
    iterativeMatrixMultiplication(n, mat1, mat2, matRes);
    clock_t end1 = clock();
    double time_taken1 = ((double)(end1 - start1) / CLOCKS_PER_SEC) * 1000;

    clock_t start2 = clock();
    divideConquor(n, mat1, mat2, matRes);
    clock_t end2 = clock();
    double time_taken2 = ((double)(end2 - start2) / CLOCKS_PER_SEC) * 1000;

    clock_t start3 = clock();
    strassen(n, mat1, mat2, matRes);
    clock_t end3 = clock();
    double time_taken3 = ((double)(end3 - start3) / CLOCKS_PER_SEC) * 1000;

    printf("Iterative: %.3f ms\n", time_taken1);
    printf("DivideConquor: %.3f ms\n", time_taken2);
    printf("Strassen: %.3f ms\n", time_taken3);

    return 0;
}