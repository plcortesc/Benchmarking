import java.io.*;
import java.net.*;
import java.util.*;

class UDPClient5 implements Runnable {

   public void run(){ 

      try{

         InetAddress IPAddress = InetAddress.getByName("127.0.0.1");

         //BUFFERS
         byte[] sendBuf = new byte[(1024)];
         byte[] receiveBuf = new byte[(1024)];

         DatagramSocket clientSocket = new DatagramSocket(); 

         File input = new File("textUDP.txt");
         FileInputStream fis = new FileInputStream(input); 

         int l=0;

         long start1 = System.nanoTime();     

         while((l=fis.read(sendBuf))>0) { 

            DatagramPacket sendPacket = new DatagramPacket(sendBuf, sendBuf.length, IPAddress, 9876);

            clientSocket.send(sendPacket);

         }

         long finish1 = System.nanoTime();
         long total1 = finish1-start1;

         System.out.println("UDP Client-Server SPEED = "+ (input.length()/(total1/(1000))) +" MB/s");

         long start2 = System.nanoTime();
         DatagramPacket receivePacket;

         while((l=fis.read(receiveBuf))>0) {

            receivePacket = new DatagramPacket(receiveBuf, receiveBuf.length);

            clientSocket.receive(receivePacket);
         }        

         long finish2 = System.nanoTime();
         long total2 = finish2-start2;

         System.out.println("UDP Server-Client SPEED = "+ (receiveBuf.length/(total2/(1000))) +" MB/s");

         System.out.println("LATENCY = "+ (((total1+total2)/(1000))/(input.length()/sendBuf.length)) +" microsec");

         clientSocket.close();

      }catch(Exception e) { 
         e.printStackTrace(); 
      }
   }

   public static void main(String args[]) {

      new Thread(new UDPClient5()).start();
      new Thread(new UDPClient5()).start();

   }
}
