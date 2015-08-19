import java.io.File;
import java.io.FileInputStream; 
import java.io.FileOutputStream;
import java.io.InputStream; 
import java.io.OutputStream; 
import java.net.ServerSocket; 
import java.net.Socket;

public class Server3 {

	public static void main(String[] args) {	
		try {

			System.out.println("Running"); 
			ServerSocket serverSocket = new ServerSocket(5555); 

			while(true) {
				Socket connect = serverSocket.accept(); 
				if(connect != null) {
					new Process(connect).start(); 
				}
			}
		} catch(Exception e) {
			e.printStackTrace(); 
		}
	}
}

class Process extends Thread { 
	Socket socket;

	Process(Socket socket) {
		this.socket = socket; 
	}

	public void run() {

		try {
			InputStream is = socket.getInputStream(); 
			OutputStream os = socket.getOutputStream();

	
			File output = new File(System.nanoTime()+".up");

			FileOutputStream fos = new FileOutputStream(output); 

			//DEFINE THE BLOCK SIZE:
			byte[] data = new byte[64*1024];

			int len=0;

			int readtimeout = 1000; 
			
			socket.setSoTimeout(readtimeout);

			try {
				while((len=is.read(data)) > 0 ) { 
					fos.write(data, 0, len);
					fos.flush();
				}
				fos.close();

			} catch(Exception e) {
				System.err.println(e.toString()); 
			}

			try { 
				Thread.sleep(1000);
			} catch (InterruptedException e) { 
				e.printStackTrace();
			}
				
			FileInputStream fis = new FileInputStream(output);

			len = 0;

			long start = System.nanoTime();

			while((len = fis.read(data)) > 0) { 
				os.write(data,0,len); 
				os.flush();
			} 

			long finish = System.nanoTime(); 

			fis.close(); 
			os.close(); 
			socket.close();

		} catch (Exception e) { 
			e.printStackTrace();
		}
	} 
}