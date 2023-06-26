//CUDA version of vector_add program
//program computes the addition of two vectors stored in array a and b, and put the result in out.

//OBSERVATION: 
//with only __global__ specifier and function call, the program will execute but the functionality will not be performed
//we can see the first index of the out still being 0 instead of designated 3
//The reason is that we need to allocate device (GPU) memory manually and perform data transfer between host (CPU) and device memory
//Following steps in the note
//time: real 0m1.063s

#include <stdio.h>
#include <cstdlib>

#define N 10000000

//add __global__ specifier for the function to execute on GPU
__global__ void vector_add(float *out, float *a, float *b, int n) { //GPU kernel
    for(int i = 0; i < n; i++){
        out[i] = a[i] + b[i];
    }
}

int main(){
    float *a, *b, *out; //CPU
    float *d_a, *d_b, *d_out; //GPU

    // Allocate memory for host
    a   = (float*)malloc(sizeof(float) * N);
    b   = (float*)malloc(sizeof(float) * N);
    out = (float*)malloc(sizeof(float) * N);

    // Initialize array
    for(int i = 0; i < N; i++){
        a[i] = 1.0f; b[i] = 2.0f;
    }

    // Allocate memory for device
    cudaMalloc((void**)&d_a, sizeof(float) * N);
    cudaMalloc((void**)&d_b, sizeof(float) * N);
    cudaMalloc((void**)&d_out, sizeof(float) * N);

    // Transfer data from host to device memory
    cudaMemcpy(d_a, a, sizeof(float) * N, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, sizeof(float) * N, cudaMemcpyHostToDevice);
    cudaMemcpy(d_out, out, sizeof(float) * N, cudaMemcpyHostToDevice);

    // Main function
    //vector_add(out, a, b, N);

    //need to change function call to CUDA's way of function call
    vector_add<<<1,1>>>(d_out, d_a, d_b, N);

    //need to transfer data back from 
    cudaMemcpy(out, d_out, sizeof(float) * N, cudaMemcpyDeviceToHost);

    printf("first index first: %f\n", out[0]);
    printf("last index last: %f\n", out[9999999]);
    printf("out of boundary index: %f\n", out[10000000]);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_out);
    free(a);
    free(b);
    free(out);
}
