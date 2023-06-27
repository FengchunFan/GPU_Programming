//pthread version of vector_add program
//program computes the addition of two vectors stored in array a and b, and put the result in out.

//chatgpt generated code: pthread version of vector add program

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10000000
#define NUM_THREADS 4

typedef struct {
    float *out;
    float *a;
    float *b;
    int start;
    int end;
} ThreadData;

void *vector_add_thread(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    float *out = data->out;
    float *a = data->a;
    float *b = data->b;
    int start = data->start;
    int end = data->end;

    for (int i = start; i < end; i++) {
        out[i] = a[i] + b[i];
    }

    pthread_exit(NULL);
}

int main() {
    float *a, *b, *out;
    pthread_t threads[NUM_THREADS];
    ThreadData threadData[NUM_THREADS];

    // Allocate memory
    a = (float *)malloc(sizeof(float) * N);
    b = (float *)malloc(sizeof(float) * N);
    out = (float *)malloc(sizeof(float) * N);

    // Initialize array
    for (int i = 0; i < N; i++) {
        a[i] = 1.0f;
        b[i] = 2.0f;
    }

    // Divide the work among threads
    int chunkSize = N / NUM_THREADS;
    int remaining = N % NUM_THREADS;
    int start = 0;

    for (int i = 0; i < NUM_THREADS; i++) {
        int end = start + chunkSize;
        if (i < remaining) {
            end++;
        }

        threadData[i].out = out;
        threadData[i].a = a;
        threadData[i].b = b;
        threadData[i].start = start;
        threadData[i].end = end;

        pthread_create(&threads[i], NULL, vector_add_thread, (void *)&threadData[i]);

        start = end;
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Result will be each index in the output being 1 + 2 = 3, size will be 10000000 as designed
    printf("first index: %f\n", out[0]);
    printf("last index: %f\n", out[N - 1]);
    printf("out of boundary index: %f\n", out[N]); // This will give undefined behavior

    // Deallocate memory
    free(a);
    free(b);
    free(out);

    return 0;
}