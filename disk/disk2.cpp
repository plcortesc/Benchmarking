#include <iostream> 
#include <ctime> 
#include <time.h> 
#include <pthread.h> 

#define BYTE 1
#define KILO 1024
#define MEG 1024*1024

#define NUM_ITkb 100

clock_t start, fin;
double readTime, writeTime;
void *stat; 
char c;

void* kb_tranfer (void *) {

	char *buf = new char[KILO];
		
	FILE *f = fopen("byte.txt","w+");//file opened in read and write mode
	
	start = clock();
	for(int i=0;i<NUM_ITkb;i++){
		fwrite(buf,KILO,1,f);
	}
	fin = clock();

	writeTime = (double)(fin-start)/CLOCKS_PER_SEC;

	std::cout<<"\n SEQ Kilobyte write LATENCY: "<<((writeTime/NUM_ITkb)*1000)<<" msec";
	std::cout<<"\n SEQ Kilobyte write SPEED: "<<(double)(NUM_ITkb*KILO/(MEG*(writeTime)))<<" MB/s";
	
	start = clock();
	for(int i=0;i<NUM_ITkb;i++) {
		fread(buf,KILO,1,f);
	}
	fin = clock();

	readTime = (double)(fin-start)/CLOCKS_PER_SEC;
	
	std::cout<<"\n SEQ Kilobyte read LATENCY: "<<((readTime/NUM_ITkb)*1000)<<" msec";
	std::cout<<"\n SEQ Kilobyte read SPEED: "<<(double)(NUM_ITkb*KILO/(MEG*(readTime)))<<" MB/s \n";

	start = clock();
	for(int i=0;i<NUM_ITkb;i++){
		int r = rand()%1024;
		fseek(f,r,SEEK_SET); 
		fwrite(buf,KILO,1,f);
	}
	fin = clock();

	writeTime = (double)(fin-start)/CLOCKS_PER_SEC;

	std::cout<<"\n RAND Kilobyte write LATENCY: "<<((writeTime/NUM_ITkb)*1000)<<" msec";
	std::cout<<"\n RAND Kilobyte write SPEED: "<<(double)(NUM_ITkb*KILO/(MEG*(writeTime)))<<" MB/s";
	
	start = clock();
	for(int i=0;i<NUM_ITkb;i++) {
		int r = rand()%1024; 
		fseek(f,r,SEEK_SET);
		fread(buf,KILO,1,f);		
	}
	fin = clock();

	readTime = (double)(fin-start)/CLOCKS_PER_SEC;

	std::cout<<"\n RAND Kilobyte read LATENCY: "<<((readTime/NUM_ITkb)*1000)<<" msec";
	std::cout<<"\n RAND Kilobyte read SPEED: "<<(double)((NUM_ITkb*KILO)/(MEG*(readTime)))<<" MB/s \n\n";
	
	fclose (f);
	pthread_exit(NULL); 

}

int main() {

	pthread_t *thread = new pthread_t[10];
	pthread_attr_t attr;
	pthread_attr_init (&attr); 
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	std::cout<<"\n\n 1 THREAD, KB";
	pthread_create(&thread[0],&attr,kb_tranfer,NULL); 
	pthread_join(thread[0], &stat);

}







