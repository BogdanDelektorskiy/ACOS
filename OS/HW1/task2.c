#include <stdio.h>
#include <stdlib.h>

void reverse_array(int *arr, int size) {
    for (int i = 0; i < size / 2; ++i) {
        int tmp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = tmp;
    }
}

int main(void) {
    int N;
    printf("Enter array size N: ");
    scanf("%d", &N);

    int *arr = (int *)malloc(N * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter %d integers:\n", N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &arr[i]);
    }

    reverse_array(arr, N);

    printf("Reversed array:\n");
    for (int i = 0; i < N; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}