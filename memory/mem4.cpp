#include <iostream> 
#include <pthread.h> 
#include <limits.h>
#include <time.h> 
#include <cstdlib> 

#define NUM_IT 1024

struct data_t { 
	int blockSize;
};

void SEQ(char* b1, char* b1_2, char* b2, char* b2_2, char* tm, char* tm2, data_t* data)
{

	clock_t start, fin, t_total = 0;
	double transfTime, emptyTime;

	start = clock();
	for( long j =0; j < SHRT_MAX; j++) {
		for( int i = 0; i < NUM_IT; i++ ){}
	}
	fin = clock() - start;

	emptyTime = fin / CLOCKS_PER_SEC;

	for( long j = 0; j < SHRT_MAX ; j++) {
		for( int i = 0; i < NUM_IT; i++ ) {
			start = clock();
			memcpy(tm, b1, data->blockSize); 
			memcpy(b1, b2, data->blockSize); 
			memcpy(b2,tm, data->blockSize); 

			fin = (clock() - start); 
			t_total += fin;

			b1 += data->blockSize; 
			b2 += data->blockSize; 
			tm += data->blockSize;
		}

		b1 = b1_2; 
		b2 = b2_2; 
		tm = tm2;
	}
	

	transfTime = (t_total/ CLOCKS_PER_SEC) - emptyTime;
	long totalBytes = (long)data->blockSize * (long)SHRT_MAX * NUM_IT * 6;
	std::cout << "\nSequential access throughput(MB/sec): " << totalBytes / (transfTime * 1024 * 1024) << std::endl;

	start = clock();
	for( long j = 0; j < SHRT_MAX; j++) {

		for ( int i = 0; i < NUM_IT; i++) { 
			memset(b1, '-', data->blockSize);
			b1 += data->blockSize;
		}

		b1 = b1_2;
	}
	
	fin = clock() - start;
	double divis = CLOCKS_PER_SEC * NUM_IT * SHRT_MAX;
	double latency = fin / divis;
	std::cout << "\nSequential access latency(ms): " << latency << std::endl;
}


int rand_lim(long bound) {

	int randlim;
	int divis = RAND_MAX/(bound+1); 
	while (randlim > bound){
		randlim = rand() / divis;
	} 	
	return randlim; 
}


char* initializeBlock(bool data, int size) {

	int tot = size * 1024;
	char* buf = new char[tot]; 
	const char* const num = "02390293402384092841" ;

	if(data) {
		for(int i = 0; i < tot; i++) {
			*(buf+i) = num[rand_lim(20)]; 
		}
	}
	return buf; 
}


void RAND(char* b1, char* b1_2, char* b2, char* b2_2, char* tm, char* tm2, data_t* data){

	clock_t start, fin, t_total = 0; 
	double transfTime, emptyTime; 
	double mult = 1024;

	start = clock();

	for( long j =0; j < SHRT_MAX; j++) {
		for( int i = 0; i < NUM_IT; i++ ){}
	}
	
	fin = clock() - start;

	emptyTime = fin / CLOCKS_PER_SEC;
	
	for( long j = 0; j < SHRT_MAX; j++) {
		for( int i = 0; i < NUM_IT; i++ ) {
			
			start = clock();
			
			memcpy(tm, b1, data->blockSize); 
			memcpy(b1, b2, data->blockSize); 
			memcpy(b2,tm, data->blockSize); 

			fin = clock() - start ;
			t_total += fin;
			
			b1 = b1_2;
			b2 = b2_2;
			tm = tm2;

			b1 += data->blockSize * rand_lim(mult - 1);
			b2 += data->blockSize * rand_lim(mult - 1);
			tm += data->blockSize * rand_lim(mult - 1);
		}
	}

	long totalBytes = (long)data->blockSize * (long)SHRT_MAX * mult * 6;
	transfTime = (t_total/ CLOCKS_PER_SEC) - emptyTime ;
	std::cout << "\nRandom access throughput(MB/sec): " << totalBytes / (transfTime * 1024 * 1024) << std::endl;

	start = clock();
	for( long j = 0; j < SHRT_MAX; j++) {
		for ( int i = 0; i < NUM_IT; i++) { 
			memset(b1, '-', data->blockSize);
			b1 = b1_2;
			b1 += rand_lim(mult - 1) * data->blockSize; 
		}
	}
	
	fin = clock() - start;
	
	double divis = CLOCKS_PER_SEC * NUM_IT * SHRT_MAX;
	double latency = fin / divis;
	std::cout << "\nRandom access latency(ms): " << latency << std::endl;
}


void * rwOp(void* arg) {
	struct data_t *data;
	data = (struct data_t *) arg;
	char* b1 = initializeBlock(true,data -> blockSize); 
	char* b2 = initializeBlock(true, data -> blockSize); 
	char* tm = initializeBlock(false, data -> blockSize);

	char* b1_2 = b1; 
	char* b2_2 = b2; 
	char* tm2 = tm;

	SEQ(b1, b1_2, b2, b2_2, tm, tm2, data);
	RAND(b1, b1_2, b2, b2_2, tm, tm2, data);

	pthread_exit(NULL); 
}

void memory() {
	int num_th = 2;
	pthread_t threads[num_th]; 
	struct data_t data; 
	data.blockSize = 1;

	pthread_create(&threads[0], NULL, rwOp, (void *)&data);
	pthread_create(&threads[1], NULL, rwOp, (void *)&data);

	pthread_exit(NULL);
}

int main() {

	std::cout << "\nTwo threads, 1B \n";
	memory();
	return 0; 
}

