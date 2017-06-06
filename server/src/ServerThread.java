import java.net.*;
import java.io.*;

class ServerThread extends Thread {
    private Socket socket;

    public ServerThread(Socket socket) {
        this.socket = socket;
        System.out.println("Connected to client!");
    }

    public void run() {
        try {
            BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter pw = new PrintWriter(socket.getOutputStream(), true);
            String line;
            while((line = br.readLine()) != null) {
                System.out.println("received message : " + line);
            }
        } catch(IOException e) {

        } finally {
            try {
                if(socket != null) {
                    socket.close();
                }
            } catch(IOExcception e) {

            }
            System.out.println("Disconnected to client : " + socket.getRemoteSocketAddress());
        }
    }
}
