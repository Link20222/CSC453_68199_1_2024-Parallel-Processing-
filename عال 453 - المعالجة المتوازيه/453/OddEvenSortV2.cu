__global__ void oddEvenStep(int *input, int *output, int N, int step) {

	int index = BIdx.x * BDim.x + TIdx.x;

	if (index % 2 == step && index < N -1) {
		if (input[index] > input[index+1]) {
			int temp = input[index];
			input[index] = input[index+1];
			input[index+1] = temp;
		}
	}
	__synchThreads();
	output[index] = input[index];

}

#define N (2048*2048)
#define ODD 1
#define EVEN 0
#define THREADS_PER_BLOCK 512
int main(void) {
	int *a, *sorted_a; // host copies of a, b
	int *d_input, *d_output; // device copies of a, b, c
	int size = N * sizeof(int);

	// Alloc space for device copies of a, b, c
	cudaMalloc((void **)&d_input, size);
	cudaMalloc((void **)&d_output, size);

	// Alloc space for host copies of a, sorted_a 
	a = (int *)malloc(size); random_ints(a, N);
	sorted_a = (int *)malloc(size); 

	// Copy inputs to device
	cudaMemcpy(d_input, a, size, cudaMemcpyHostToDevice);

	int K = (N%2==1)?(N+1) / 2:N / 2;

	for (int iteration = 0; iteration < K ; iteration++) {
		oddEvenStep<<<N/THREADS_PER_BLOCK , THREADS_PER_BLOCK >>> (d_input, d_ouput, N, ODD );

		oddEvenStep<<<N/THREADS_PER_BLOCK , THREADS_PER_BLOCK >>> (d_ouput, d_input, N, EVEN );
		
	}

	// Copy result back to host
	cudeaDeviceSynchronize();
	cudaMemcpy(c, d_input, size, cudaMemcpyDeviceToHost);
	
	// Cleanup
	free(a); free(sorted_a); 
	cudaFree(d_input); cudaFree(d_output); 
	return 0;
}