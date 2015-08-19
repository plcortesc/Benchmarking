import java.io.*;
import java.net.*;

class UDPServer2 {
   public static void main(String args[]) throws Exception{

      DatagramSocket serverSocket = new DatagramSocket(9876);
      
      //BUFFERS
      byte[] receiveBuf = new byte[1024];
      byte[] sendBuf = new byte[1024];

      while(true)
      {

         DatagramPacket receivePacket = new DatagramPacket(receiveBuf, receiveBuf.length);

         serverSocket.receive(receivePacket);

         String sentence = new String(receivePacket.getData(), 0, receivePacket.getLength());

         InetAddress IPAddress = receivePacket.getAddress();

         int port = receivePacket.getPort();

         String capitalizedSentence = sentence.toUpperCase();

         sendBuf = capitalizedSentence.getBytes();

         DatagramPacket sendPacket = new DatagramPacket(sendBuf, sendBuf.length, IPAddress, port);

         serverSocket.send(sendPacket);
      }
   }
}