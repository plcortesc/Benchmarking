import java.io.File;
import java.io.FileInputStream; 
import java.io.FileOutputStream; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.net.Socket;
import java.util.Scanner;

public class Client6 implements Runnable {

	public void run() { 
		try {

			long start = System.nanoTime();
			
			Socket socket = new Socket("localhost", 5555); 

			OutputStream os = socket.getOutputStream();
			InputStream is = socket.getInputStream();
			
			File input = new File("textTCP.txt");
			FileInputStream fis = new FileInputStream(input); 

			// DEFINE BLOCKSIZE
			byte[] data = new byte[64*1024];

			int len=0;

			while((len=fis.read(data))>0) { 
				os.write(data, 0, len); 
				os.flush();
			} 

			fis.close();
			
			try { 
				Thread.sleep(2000);
			} catch (InterruptedException e) {
				e.printStackTrace(); 
			}
			
			File output = new File(System.currentTimeMillis()+".down");

			FileOutputStream fos = new FileOutputStream(output); 

			len = 0;

			while((len=is.read(data))>0) { 
				fos.write(data, 0, len);
				fos.flush(); 
			}
			
			fos.close(); 
			is.close();
			socket.close();

			long finish = System.nanoTime();

			long latency = (finish-start)/(1000000000);

			System.out.println("LATENCY " +latency+" ms");
			System.out.println("THROUGHPUT "+(64*1024*8*1000)/(latency*1000) +"Kb/s");

		} catch(Exception e) { 
			e.printStackTrace();
		} 
	}

	public static void main(String args[]) {

		new Thread(new Client6()).start();
		new Thread(new Client6()).start();

	}
}