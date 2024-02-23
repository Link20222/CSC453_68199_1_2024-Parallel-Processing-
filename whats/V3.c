#include <stdio.h>
#include <cuda.h>

__global__ void sortKernel(int *in, int *out, int size){
    __shared__ bool swappedodd;
    __shared__ bool swappedeven;
    bool odd = true;
    int temp;
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    while(true){
        __syncthreads();
        
        if(odd == true){
            swappedodd = false;
            __syncthreads();
            if( idx % 2 == 1 && idx < size - 1){
                if(in[idx] > in[idx + 1]){
                    temp = in[idx];
                    in[idx] = in[idx + 1];
                    in[idx + 1] = temp;
                    swappedodd = true;
                }
            }
        }
        else{
            swappedeven = false;
            __syncthreads();
            if( idx % 2 == 0 && idx < size - 1){
                if(in[idx] > in[idx + 1]){
                    temp = in[idx];
                    in[idx] = in[idx + 1];
                    in[idx + 1] = temp;
                    swappedodd = true;
                }
            }
        }
        __syncthreads();
        if( !(swappedodd || swappedeven))
            break;
        
        odd =! odd;
    }
    __syncthreads();
    if( idx < size)
        out[idx] = in[idx];
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
    sortKernel<<<blocks, threads>>>(d_a, d_sorted, n);
    cudaMemcpy(a_sorted, d_sorted, size, cudaMemcpyDeviceToHost);
    for(int i=0; i < n; i++){
        printf("%d\t", a_sorted[i]);
    }
}