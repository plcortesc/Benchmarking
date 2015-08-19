#include <stdio.h>
#include <sys/time.h>

__global__
void bw(int n, float c, float *x, float *y){

  int j = blockIdx.x;

  if (j < n) y[j] = x[j] + c*y[j];

}

int main(void){

  float *x, *y, *dev_x, *dev_y;
  int N = 1<<20;

  x = (float*)malloc(N*sizeof(float));
  y = (float*)malloc(N*sizeof(float));

  cudaMalloc(&dev_x, N*sizeof(float));
  cudaMalloc(&dev_y, N*sizeof(float));

  for (int j = 0; j < N; j++) {
    x[j] = 4.0f;
    y[j] = 1.0f;

  }

  cudaMemcpy(dev_x, x, N*sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(dev_y, y, N*sizeof(float), cudaMemcpyHostToDevice);

  cudaEvent_t start1, stop1;
  cudaEventCreate(&start1);
  cudaEventCreate(&stop1);

  cudaEventRecord(start1);

  bw<<<(N+447)/448,448>>>(N, 2.0f, dev_x, dev_y);

  cudaEventRecord(stop1);

  cudaEventSynchronize(stop1);
  float time = 0;
  cudaEventElapsedTime(&time, start1, stop1);

  // N*4 number of bytes transferred r/w
  // 3 = rx + ry + wy
  printf("Bandwidth(GB/s): %f \n", N*4*3/time/1e6);
  cudaFree(dev_x);
  cudaFree(dev_y);

}

