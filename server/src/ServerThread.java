import java.net.*;
import java.io.*;
import java.io.IOException;

class ServerThread extends Thread {
    private Socket socket;
    private Task task;

    public ServerThread(Socket socket) {
        this.socket = socket;
        System.out.println("Connected to client!");
        task = new Task();
    }

    public void run() {
        try {
            BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter pw = new PrintWriter(socket.getOutputStream(), true);
            String line;
            // while((line = br.readLine()) != null) {
            //     System.out.println("received message : " + line);
            // }
            line = br.readLine();
            System.out.println("recv: " + line);
            String[] lines = line.split(" ");
            System.out.println("type : " + lines[0] + "/ class : " + lines[1]);

            ObjectOutputStream oos = new ObjectOutputStream(socket.getOutputStream());
            oos.writeObject(task);


        } catch(IOException e) {

        } finally {
            try {
                if(socket != null) {
                    socket.close();
                }
            } catch(IOException e) {

            }
            System.out.println("Disconnected to client : " + socket.getRemoteSocketAddress());
        }
    }
}
