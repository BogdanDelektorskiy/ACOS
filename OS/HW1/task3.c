#include <stdio.h>
#include <stdlib.h>

void free_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

int main(void) {
    int N, M;
    printf("Enter matrix dimensions (N M): ");
    scanf("%d %d", &N, &M);

    int **matrix = (int **)malloc(N * sizeof(int *));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < N; ++i) {
        matrix[i] = (int *)malloc(M * sizeof(int));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (int j = 0; j < i; ++j) free(matrix[j]);
            free(matrix);
            return 1;
        }
    }

    printf("Enter %d integers for the matrix:\n", N * M);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            scanf("%d", &matrix[i][j]);

    int **transposed = (int **)malloc(M * sizeof(int *));
    if (transposed == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_matrix(matrix, N);
        return 1;
    }
    for (int i = 0; i < M; ++i) {
        transposed[i] = (int *)malloc(N * sizeof(int));
        if (transposed[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (int j = 0; j < i; ++j) free(transposed[j]);
            free(transposed);
            free_matrix(matrix, N);
            return 1;
        }
    }

    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            transposed[i][j] = matrix[j][i];

    printf("Transposed matrix (%d x %d):\n", M, N);
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j)
            printf("%d ", transposed[i][j]);
        printf("\n");
    }

    free_matrix(matrix, N);
    free_matrix(transposed, M);

    return 0;
}