#include <stdio.h>
#include <cuda.h>

__global__ void anyStep(int *in, int *out, int size, int step){
    int temp;
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    
    if( idx % 2 == step && idx < size - 1){
        if( in[idx] > in[idx + 1] ){
            temp = in[idx];
            in[idx] = in[idx + 1];
            in[idx + 1] = temp;
        }
    }
    __syncthreads();

    if( idx < size )
        out[idx] = in[idx]
}

int main(void){
    int *a, *a_sorted;
    int *d_a, *d_sorted;
    int blocks = 1024;
    int threads = 1024;
    int n = blocks * threads;
    int size = sizeof(int) * n;
    cudaMalloc( (void**) &d_a, size);
    cudaMalloc( (void**) &d_sorted, size);
    a = (int*) malloc(size);
    a_sorted = (int*) malloc(size);
    printf("Enter the unsorted numbers:\n")
    for(int i=0; i<n; i++){
        scanf("%d", &a[i]);
    }
    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    for(int i=1; i <= n / 2; i++){
        anyStep<<<blocks, threads>>>(d_a, d_sorted, n, 1);
        __syncthreads();
        anyStep<<<blocks, threads>>>(d_sorted, d_a, n, 0);
        __syncthreads();
    }
    cudaMemcpy(a_sorted, d_a, size, cudaMemcpyDeviceToHost);
    for(int i=0; i < n; i++){
        printf("%d\t", a_sorted[i]);
    }
}