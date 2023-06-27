//modified based on sample code taken from: https://cuda-tutorial.readthedocs.io/en/latest/tutorials/tutorial01/
//program computes the addition of two vectors stored in array a and b, and put the result in out.

#include <stdio.h>
#include <cstdlib>

#define N 10000000

void vector_add(float *out, float *a, float *b, int n) {
    for(int i = 0; i < n; i++){
        out[i] = a[i] + b[i];
    }
}

int main(){
    float *a, *b, *out; 

    // Allocate memory
    a   = (float*)malloc(sizeof(float) * N);
    b   = (float*)malloc(sizeof(float) * N);
    out = (float*)malloc(sizeof(float) * N);

    // Initialize array
    for(int i = 0; i < N; i++){
        a[i] = 1.0f; b[i] = 2.0f;
    }

    // Main function
    vector_add(out, a, b, N);

    //result will be each index in the output being 1+2=3, size will be 10000000 as designed

    printf("first index first: %f\n", out[0]);
    printf("last index last: %f\n", out[9999999]);
    printf("out of boundary index: %f\n", out[10000000]);

    //deallocate memory
    free(a);
    free(b);
    free(out);
}
