gridDim.x= give us the coloum of block
gridDim.y=give us the row of blocks

blockDim.x= g ive us the column of threads
blockDim.y= give us the row of threads

blockIdx.x=tell us which colum the block in
blockIdx.y=tell us which row the block in

threadIdx.x=tell us which colum the thread in
threadId.y=tell us which row the block in
 -------------------------------------------------------------
 __global__ void mykernel(void) {  // Since it is mykernel the fun should start with __global__ and return type must be void
 }

 int main(void) {
 mykernel<<<1,1>>>(); //يخلي الكول من الهوست الى الديفايس
 printf("Hello World!\n");
 return 0;
} //  والباقي هو الباريل my mykernel هذي الفنكشن بس الباريل حقها هو استدعاء ال

to print in Device use this:
__global__ void mykernel(void){
printf("Hello World!\n");
}

int main(void) {
mykernel<<<1,1>>>();
return 0;
}// output: Hello World!

int main(void) {
mykernel<<<2,2>>>();
return 0;
}//<<<2,2>>> -> 2 block Each block have 2 thread and each thread print
output:
Hello World!
Hello World!
Hello World!
Hello World!
-------------------------------------------------------------
                    Sum of 2 arrays

int main(void) {
int a, b, c; // host copies of a, b, c
int *d_a, *d_b, *d_c; // device copies of a, b, c
int size = sizeof(int);
// Allocate space for device copies of a, b, c
cudaMalloc((void **)&d_a, size);
cudaMalloc((void **)&d_b, size);
cudaMalloc((void **)&d_c, size);
// Setup input values
a = 2;
b = 7;

// Copy inputs to device
cudaMemcpy(d_a, &a, size, cudaMemcpyHostToDevice);
cudaMemcpy(d_b, &b, size, cudaMemcpyHostToDevice);
// Launch add() kernel on GPU
add<<<1,1>>>(d_a, d_b, d_c);
// Copy result back to host
cudaMemcpy(&c, d_c, size, cudaMemcpyDeviceToHost);
// Cleanup
cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);
return 0;
}
-------------------------------------------------------------
__global__ void add(int *a, int *b, int *c) {   // <<<N,1>>
c[blockIdx.x] = a[blockIdx.x] + b[blockIdx.x];
}
#define N 512
int main(void) {
int *a, *b, *c; // host copies of a, b, c  (array of int)
int *d_a, *d_b, *d_c; // device copies of a, b, c
int size = N * sizeof(int);
// Alloc space for device copies of a, b, c
cudaMalloc((void **)&d_a, size);
cudaMalloc((void **)&d_b, size);
cudaMalloc((void **)&d_c, size);
// Alloc space for host copies of a, b, c and setup input values (since its array we need to alloc in host)
a = (int *)malloc(size); random_ints(a, N);
b = (int *)malloc(size); random_ints(b, N);
c = (int *)malloc(size)
// Copy inputs to device
cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
// Launch add() kernel on GPU with N blocks
add<<<N,1>>>(d_a, d_b, d_c);
// Copy result back to host
cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
// Cleanup
free(a); free(b); free(c);
cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);
return 0;
}

__global__ void add(int *a, int *b, int *c) { //<<<1,N>>>
c[threadIdx.x] = a[threadIdx.x] + b[threadIdx.x];
}
int main(void) {
int *a, *b, *c; // host copies of a, b, c
int *d_a, *d_b, *d_c; // device copies of a, b, c
int size = N * sizeof(int);
// Alloc space for device copies of a, b, c
cudaMalloc((void **)&d_a, size);
cudaMalloc((void **)&d_b, size);
cudaMalloc((void **)&d_c, size);
// Alloc space for host copies of a, b, c and setup input values
a = (int *)malloc(size); random_ints(a, N);
b = (int *)malloc(size); random_ints(b, N);
c = (int *)malloc(size);

// Copy inputs to device
cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
// Launch add() kernel on GPU with N blocks
add<<<1, N>>>(d_a, d_b, d_c);
// Copy result back to host
cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
// Cleanup
free(a); free(b); free(c);
cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);
return 0;
}

__global__ void add(int *a, int *b, int *c) { //<<<N,N>>>
int index = threadIdx.x + blockIdx.x * blockDim.x;
c[index] = a[index] + b[index];
}

#define N (2048*2048)
#define THREADS_PER_BLOCK 512
int main(void) {
int *a, *b, *c; // host copies of a, b, c
int *d_a, *d_b, *d_c; // device copies of a, b, c
int size = N * sizeof(int);
// Alloc space for device copies of a, b, c
cudaMalloc((void **)&d_a, size);
cudaMalloc((void **)&d_b, size);
cudaMalloc((void **)&d_c, size);
// Alloc space for host copies of a, b, c and setup input values
a = (int *)malloc(size); random_ints(a, N);
b = (int *)malloc(size); random_ints(b, N);
c = (int *)malloc(size);
// Copy inputs to device
cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
// Launch add() kernel on GPU
add<<<N/THREADS_PER_BLOCK,,THREADS_PER_BLOCK>>>(d_a, d_b, d_c);
// Copy result back to host
cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
// Cleanup
free(a); free(b); free(c);
cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);
return 0;
}
