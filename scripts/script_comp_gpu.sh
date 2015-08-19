#! /bin/sh 

cd ..
cd gpu

nvcc gpu.cu -o gpu
nvcc gpuB.cu -o gpuB
nvcc gpuKB.cu -o gpuKB
nvcc gpuMB.cu -o gpuMB

cd ..

echo "Thank you"