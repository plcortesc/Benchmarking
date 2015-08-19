#include <iostream> 
#include <ctime> 
#include <time.h> 
#include <pthread.h> 

#define BYTE 1
#define KILO 1024
#define MEG 1024*1024

#define NUM_ITmb 10

clock_t start, fin;
double readTime, writeTime;
void *stat; 
char c;

void* mb_tranfer (void *) {

	char *buf = new char[MEG];

	FILE *f = fopen("byte.txt","w+");

	start = clock();
	
	for(int i=0;i<NUM_ITmb;i++){
		fwrite(buf,MEG,1,f);
	}

	fin = clock();
	writeTime = (double)(fin-start)/CLOCKS_PER_SEC;
	std::cout<<"\n SEQ Megabyte write LATENCY: "<<(writeTime/NUM_ITmb)*1000<<" msec";
	std::cout<<"\n SEQ Megabyte write SPEED: "<<(double)(NUM_ITmb/(writeTime))<<" MB/s";
	
	start = clock(); 
	for(int i=0;i<NUM_ITmb;i++) {
		fread(buf,MEG,1,f);
	}
	fin = clock();

	readTime = (double)(fin-start)/CLOCKS_PER_SEC; 
	
	std::cout<<"\n SEQ Megabyte read LATENCY: "<<(readTime/NUM_ITmb)*1000<<" msec";
	std::cout<<"\n SEQ Megabyte read SPEED: "<<(double)(NUM_ITmb/(readTime))<<" MB/s \n";

	start = clock();
	for(int i=0;i<NUM_ITmb;i++) {
		double r = rand()%MEG;
		fseek(f,r,SEEK_SET);
		fwrite(buf,MEG,1,f);
	}
	fin = clock();

	writeTime = (double)(fin-start)/CLOCKS_PER_SEC; 

	std::cout<<"\n RAND Megabyte write LATENCY: "<<((writeTime/NUM_ITmb)*1000)<<" msec"; 
	std::cout<<"\n RAND Megabyte write SPEED: "<<(double)(NUM_ITmb/(writeTime))<<" MB/s";
	
	start = clock(); 
	for(int i=0;i<NUM_ITmb;i++){
		double r = rand()%(MEG); 
		fseek(f,r,SEEK_SET); 
		fread(buf,MEG,1,f);
	}
	fin = clock();

	readTime = (double)(fin-start)/CLOCKS_PER_SEC;

	std::cout<<"\n RAND Megabyte read LATENCY: "<<((readTime/NUM_ITmb)*1000)<<" msec";
	std::cout<<"\n RAND Megabyte read SPEED: "<<(double)(NUM_ITmb/(readTime))<<" MB/s \n\n";

	fclose (f);
	pthread_exit(NULL);
}



int main() {

	pthread_t *thread = new pthread_t[10];
	pthread_attr_t attr;
	pthread_attr_init (&attr); 
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	std::cout<<"\n\n 1 THREAD, MB ";
	pthread_create(&thread[0],&attr,mb_tranfer,NULL); 
	pthread_join(thread[0], &stat);

}







