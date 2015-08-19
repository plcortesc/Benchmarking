#! /bin/sh 

cd ..
cd cpu

g++ cpu1.cpp -o cpu1
g++ cpu2.cpp -o cpu2
g++ cpu3.cpp -o cpu3
g++ cpu4.cpp -o cpu4

cd ..
cd memory

g++ mem1.cpp -o mem1
g++ mem2.cpp -o mem2
g++ mem3.cpp -o mem3
g++ mem4.cpp -o mem4
g++ mem5.cpp -o mem5
g++ mem6.cpp -o mem6

cd ..
cd disk

g++ disk1.cpp -o disk1
g++ disk2.cpp -o disk2
g++ disk3.cpp -o disk3
g++ disk4.cpp -o disk4
g++ disk5.cpp -o disk5
g++ disk6.cpp -o disk6
g++ disk7.cpp -o disk7
g++ disk8.cpp -o disk8
g++ disk9.cpp -o disk9

cd ..
cd network
cd udp

javac UDPServer1.java
javac UDPServer2.java
javac UDPServer4.java
javac UDPServer5.java

javac UDPClient1.java 
javac UDPClient2.java 
javac UDPClient4.java 
javac UDPClient5.java 

cd ..
cd tcp

javac Server1.java
javac Server2.java
javac Server3.java
javac Server4.java
javac Server5.java
javac Server6.java

javac Client1.java
javac Client2.java
javac Client3.java
javac Client4.java
javac Client5.java
javac Client6.java

cd ..
cd ..

echo "Thank you"
