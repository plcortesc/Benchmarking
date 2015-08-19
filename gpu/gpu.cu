#include <stdio.h>
#include <sys/time.h>

__global__
void flops(int n, float c, float *x, float *y){

  int i = blockIdx.x*blockDim.x + threadIdx.x;

  if(c==2.0f){
    if (i < n) y[i] = c*x[i] + y[i];
  }else{
    if (i<n){};
  }

}

__global__
void iops(int n, int c, int *a, int *b){

  int i = blockIdx.x*blockDim.x + threadIdx.x;
  if (i < n) b[i] = c*a[i] + b[i];

}

double read_timer(){

    struct timeval start;
    gettimeofday( &start, NULL );
    return (double)((start.tv_sec) + 1.0e-6 * (start.tv_usec))*1000;

}

int main(void){

  printf("\n\nYou are executing the GPU Benchmarking\n\n");
   
  int N = 20*(1<<20);
  float *x, *y, *dev_x, *dev_y;
  int *a, *b, *dev_a, *dev_b;

  x = (float*)malloc(N*sizeof(float));
  y = (float*)malloc(N*sizeof(float));

  a = (int*)malloc(N*sizeof(int));
  b = (int*)malloc(N*sizeof(int));

  cudaMalloc(&dev_x, N*sizeof(float));
  cudaMalloc(&dev_y, N*sizeof(float));

  cudaMalloc(&dev_a, N*sizeof(int));
  cudaMalloc(&dev_b, N*sizeof(int));

  for (int i = 0; i < N; i++) {

    x[i] = 1.0f;
    y[i] = 2.0f;
    a[i] = 1;
    b[i] = 2;

  }

  cudaMemcpy(dev_x, x, N*sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(dev_y, y, N*sizeof(float), cudaMemcpyHostToDevice);

  double b1=read_timer();

  flops<<<(N+447)/448,448>>>(N, 2.0f, dev_x, dev_y);

  double e1=read_timer();

  cudaMemcpy(y, dev_y, N*sizeof(float), cudaMemcpyDeviceToHost);

  double t1 = e1-b1;

  double b2=read_timer();

  flops<<<(N+447)/448,448>>>(N, 1.0f, dev_x, dev_y);

  double e2=read_timer();


  double t2 = e2-b2;

  double tf = t1 - t2;

  // 2 = flops per kernel (add and mult)
  printf("GFLOPS/s: %f \n", (2*N)/(tf*1e6));

  cudaMemcpy(dev_a, a, N*sizeof(int), cudaMemcpyHostToDevice);
  cudaMemcpy(dev_b, b, N*sizeof(int), cudaMemcpyHostToDevice);

  double b3=read_timer();
  iops<<<(N+447)/448,448>>>(N, 2, dev_a, dev_b);
  double e3=read_timer();

  cudaMemcpy(b, dev_b, N*sizeof(int), cudaMemcpyDeviceToHost);

  double t3=e3-b3;

  double ti = t3 - t2;
  
  // 2 = iops per kernel (add and mult)
  printf("GIOPS/s: %f \n", (2*N)/(ti*1e6));

  cudaFree(dev_x);
  cudaFree(dev_y);
  cudaFree(dev_a);
  cudaFree(dev_b);
}

