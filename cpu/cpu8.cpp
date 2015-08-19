#include <iostream> 
#include <limits.h>
#include <pthread.h> 
#include <time.h> 
#include <cstdlib> 



float getRandomVal(float bound) {
	return static_cast<float>(rand() / (static_cast<float>(RAND_MAX/ bound))); 
}

void getFlops(void *threadId) {

	volatile long i;
	volatile float x, y;

	long thId = (long)threadId;
	float bound = 1e6;
	
	double emptyTime, addTime;

	clock_t start = clock();

	for(i = 0; i < INT_MAX; i++ ){}

	clock_t fin = clock() - start;

	emptyTime = fin / CLOCKS_PER_SEC;

	x = getRandomVal(bound); 
	y = getRandomVal(bound); 
	
	start = clock();

	for(i = 0; i < INT_MAX; i++ ){
		x += y;
	}

	fin = clock() - start;

	addTime = fin / CLOCKS_PER_SEC; 
	addTime -= emptyTime;

	std::cout << "Time of the add loop (FLOPS): " << addTime << " s in thread #"<< thId << "\n\n";

	float flops = INT_MAX / addTime;
	std::cout << "GFLOPS in thread #"<< thId << ": " << flops/1e9 << "\n\n";
}

void getIops(void *threadId) {

	volatile long i;
	volatile int x, y;

	long thId = (long)threadId;
	double emptyTime, addTime;

	clock_t start = clock();

	for(i = 0; i < INT_MAX; i++ ) {}

	clock_t fin = clock() - start;
	emptyTime = fin / CLOCKS_PER_SEC;

	x = rand();
	y = rand();
	
	start = clock();
	for(i = 0; i < INT_MAX; i++ ) {
		x += y; 
	}
	fin = clock() - start;

	addTime = fin / CLOCKS_PER_SEC; 
	addTime -= emptyTime;
	
	std::cout << "Time of the add loop (IOPS): " << addTime << " s in thread #"<< thId << "\n\n";
	float iops = INT_MAX / addTime; 
	std::cout << "GIOPS in thread #"<< thId << ": " << iops/1e9 << "\n\n";
}

void *benchmark(void *threadId) {
	getFlops(threadId); 
	getIops(threadId); 
	pthread_exit(NULL);
}

void cpu(){
	std::cout << "\n 8 THREADS \n";

	pthread_t thread[8];

	for(int i = 0; i < 8; i++) {
		pthread_create(&thread[i], NULL, benchmark, (void*)i);
	} 
	pthread_exit(NULL);
}

int main () {
	srand(static_cast<unsigned>(time(0)));
	cpu(); 
}

