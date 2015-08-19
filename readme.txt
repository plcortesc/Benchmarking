
Pablo L Cortes

0.- Script execution

There are the following scripts that you have to execute as are sorted (you can find them in the “scripts” folder):
	1. script_comp.sh (to compile all the files but GPU Benchmrking)
	2. script_exe.sh (to execute all the files but GPU Benchmarking)
	3. once inside jarvis: script_comp_gpu.sh (to compile the GPU benchmarking)
	4. script_exe_gpu.sh (to execute the GPU benchmarking)

If you want to examine any of the benchmark parts you will find the source code in the “submit” folder.


1.- CPU Benchmarking

I have designed CPU benchmark in four files, classified by the number of threads. 

So:	 		cpu1.cpp -> 1 thread
			cpu2.cpp -> 2 threads
			cpu4.cpp -> 4 threads
			cpu8.cpp -> 8 threads

First, need to compile the file, for example cpu1.cpp:

g++ cpu1.cpp –o cpu1

And then execute:

./cpu1


2.- GPU Benchmarking

There are three files (gpu.cu, gpu1.cu, gpu2.cu and gpu3.cu).
First of all, I needed to login to Jarvis server (IIT)

Once inside, to compile:
	nvcc gpu.cu -o gpu

And for executing:
	./gpu


3.- Memory Benchmarking

6 files for every experiment depending on the number of threads and the blocksize (mem1.cpp, mem2.cpp, mem3.cpp……)

Compiling the file:
	g++ mem1.cpp –o mem1

Executing:
	./mem1



4.- Disk Benchmarking

9 different files which are classified by number of threads (1, 2 & 4), then the blocksize (B, KB & MB).

So the first file: 	disk1.cpp   ->  1 Thread , 1 Byte
			disk2.cpp   ->  1 Thread , 1 KB
			disk3.cpp   ->  1 Thread , 1 MB
			disk4.cpp   ->  2 Threads, 1 Byte
				     ….
			disk9.cpp   ->  4 Threads, 1 MB

In each file we calculate SPEED and LATENCY for sequential/random access and read/write operation.

Example: disk1.cpp

Compiling the file:

	g++ disk1.cpp –o disk1

Executing:

	./disk1


5.- Network Benchmarking

Files are divided into TCP and UDP, and then one file for every experiment.

For example, for:

 TCP, 1 thread and 1 Byte 	->	Server1.java, Client1.java
 UDP, 2 Threads and 1 KB 	->	UDPServer5.java, UDPClient5.java

Open two terminals, one for the Server and another for the Client. Example: TCP 1 thread and 1 byte:
Server:

javac Server1.java
java Server1
Client:
	javac Client1.java
	java Client1

Finally, the screen will show the metrics:
	
	LATENCY 7 ms
	THROUGHPUT 748
