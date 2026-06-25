#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4

int *array;
int N;
long long global_sum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int start;
    int end;
} Range;

void *thread_sum(void *arg) {
    Range *r = (Range *)arg;
    long long local_sum = 0;
    for (int i = r->start; i < r->end; i++) {
        local_sum += array[i];
    }
    pthread_mutex_lock(&mutex);
    global_sum += local_sum;
    pthread_mutex_unlock(&mutex);
    free(r);
    return NULL;
}

int main() {
    printf("Enter N (>= 16): ");
    scanf("%d", &N);
    if (N < 16) {
        fprintf(stderr, "N must be at least 16\n");
        return 1;
    }

    array = (int *)malloc(N * sizeof(int));
    if (!array) {
        perror("malloc");
        return 1;
    }

    srand(time(NULL));
    printf("Array: ");
    for (int i = 0; i < N; i++) {
        array[i] = rand() % 100;
        printf("%d ", array[i]);
    }
    printf("\n");

    pthread_t threads[NUM_THREADS];
    int chunk = N / NUM_THREADS;
    int remainder = N % NUM_THREADS;
    int start = 0;

    for (int i = 0; i < NUM_THREADS; i++) {
        Range *r = (Range *)malloc(sizeof(Range));
        r->start = start;
        r->end = start + chunk + (i < remainder ? 1 : 0);
        start = r->end;
        pthread_create(&threads[i], NULL, thread_sum, r);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Total sum = %lld\n", global_sum);

    pthread_mutex_destroy(&mutex);
    free(array);
    return 0;
}