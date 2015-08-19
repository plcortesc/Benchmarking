#include <iostream> 
#include <ctime> 
#include <time.h> 
#include <pthread.h> 

#define BYTE 1
#define KILO 1024
#define MEG 1024*1024

#define NUM_ITb 100000

clock_t start, fin;
double readTime, writeTime;
void *stat; 
char c;

void* b_tranfer (void *) {

	char *buf = new char[BYTE];
		
	FILE *f = fopen("byte.txt","w+");

	start = clock();
	for(int i=0;i<NUM_ITb;i++) {
		fwrite(buf,BYTE,1,f);
	}
	fin = clock();

	writeTime = (double)(fin-start)/CLOCKS_PER_SEC;

	std::cout<<"\n SEQ Byte write LATENCY: "<<(writeTime/NUM_ITb)*1000<<" msec";
	std::cout<<"\n SEQ Byte write SPEED: "<<(double)(NUM_ITb*BYTE/(1024*1024*writeTime))<<" MB/s";

	start = clock();
	for(int i=0;i<NUM_ITb;i++) {
		fread(buf,BYTE,1,f); //reading data from file 
	}
	fin = clock();

	readTime = (double)(fin-start)/CLOCKS_PER_SEC;
	
	std::cout<<"\n SEQ Byte read LATENCY: "<<(readTime/NUM_ITb)*1000<<" msec";
	std::cout<<"\n SEQ Byteread SPEED: = "<<(double)(NUM_ITb*BYTE/(1024*1024*readTime))<<" MB/s \n";
	
	start = clock();
	for(int i=0;i<NUM_ITb;i++) {
		double r = rand()%(BYTE);
		fseek(f,r,SEEK_SET);
		fwrite(buf,BYTE,1,f);
	}
	fin = clock();

	writeTime = (double)(fin-start)/CLOCKS_PER_SEC;

	std::cout<<"\n RAND Byte write LATENCY: "<<((writeTime/NUM_ITb)*1000)<<" msec"; 
	std::cout<<"\n RAND Byte write SPEED: "<<(double)(NUM_ITb*BYTE/(1024*1024*writeTime))<<" MB/s";
	
	start = clock(); 
	for(int i=0;i<NUM_ITb;i++){
		double r = rand()%(BYTE); 
		fseek(f,r,SEEK_SET); 
		fread(buf,BYTE,1,f);
	}
	fin = clock();
	
	readTime = (double)(fin-start)/CLOCKS_PER_SEC;

	std::cout<<"\n RAND Byte read LATENCY: "<<((readTime/NUM_ITb)*1000)<<" msec";
	std::cout<<"\n RAND Byte read SPEED: "<<(double)(NUM_ITb*BYTE/(1024*1024*readTime))<<" MB/s \n\n";

	fclose (f);
	pthread_exit(NULL); 

}

int main() {

	pthread_t *thread = new pthread_t[10];
	pthread_attr_t attr;
	pthread_attr_init (&attr); 
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	std::cout<<"\n\n 2 THREADS, Byte ";
	for(int i=0; i<2; i++){
		pthread_create(&thread[i],&attr,b_tranfer,NULL); 
		pthread_join(thread[i], &stat); 
	}

}







