#! /bin/sh 

cd ..
cd cpu

./cpu1
./cpu2
./cpu4
./cpu8

cd ..
cd memory

./mem1
./mem2
./mem3
./mem4
./mem5
./mem6

cd ..
cd disk

./disk1
./disk2
./disk3
./disk4
./disk5
./disk6
./disk7
./disk8
./disk9

cd ..
cd network
cd udp

java UDPServer1
java UDPServer2
java UDPServer4
java UDPServer5

java UDPClient1 
java UDPClient2 
java UDPClient4 
java UDPClient5 

cd ..
cd tcp

java Server1
java Server2
java Server3
java Server4
java Server5
java Server6

java Client1
java Client2
java Client3
java Client4
java Client5
java Client6

cd ..
cd ..

echo "Thank you"
