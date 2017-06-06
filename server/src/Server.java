import java.io.*;
import java.net.*;

public class Server {
    private static int PORT = 4444;

    private Server() {
        ServerSocket serverSocket = null;
        Socket socket = null;
        try {
            serverSocket = new ServerSocket(PORT);
            System.out.println("Server is running...(port=" + serverSocket.getLocalPort() + ")");
            while(true) {
                socket = serverSocket.accept();
                new ServerThread(socket).start();
            }
        } catch(IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if(serverSocket != null) {
                    serverSocket.close();
                }
            } catch(IOExcception e) {

            }
        }
    }
}
