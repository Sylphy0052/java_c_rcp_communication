import java.io.*;
import java.net.*;
import java.util.*;
import java.lang.Class;
import java.lang.reflect.Method;

class ServerThread extends Thread {
    private Socket socket;
    private static HashMap<String, Object> services;

    public ServerThread(Socket socket) {
        this.socket = socket;
        System.out.println("Connected to client!");
        services = new HashMap<String, Object>();
        services.put("Task", new Task());
    }

    public void run() {
        try {
            DataInputStream dis = new DataInputStream(socket.getInputStream());

            String command = "";
            char c;
            while ((c = (char)dis.readByte()) != '\n') {
                command += c;
            }
            System.out.println("command: " + command);

            Iterator<String> commands = Arrays.asList(command.split(" ")).iterator();
            String command1 = commands.next();

            if(command1.equals("Get")) {
                ObjectOutputStream oos = new ObjectOutputStream(socket.getOutputStream());
                Object service = services.get(commands.next());
                oos.writeObject(service);
            } else if (command1.equals("Call")) {
                String className = commands.next();
                String methodName = commands.next();
                int len = dis.readInt();
                System.out.println("args bytes lenth: " + len);
                byte[] bytes = new byte[len];

                System.out.println("hexdump:");
                for (int i = 0; i < len; i++) {
                    byte b = dis.readByte();
                    System.out.print(String.format("%02x", b & 0xFF));
                    System.out.print(i % 10 == 9 ? "\n" : " ");
                    bytes[i] = (byte)b;
                }
                System.out.println();

                System.out.println("call:");
                try (ObjectInputStream ois = new ObjectInputStream(new ByteArrayInputStream(bytes))) {
                    Object arg1 = ois.readObject();
                    Object service = services.get(className);
                    Class<?> call_class = Class.forName(className);
                    Method method = call_class.getMethod(methodName, arg1.getClass());
                    method.invoke(service, arg1);
                } catch(Exception e) {
                    e.printStackTrace();
                }
            }
        } catch(IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if(socket != null) {
                    socket.close();
                }
            } catch(IOException e) {
                e.printStackTrace();
            }
            System.out.println("Disconnected to client : " + socket.getRemoteSocketAddress());
        }
    }
}
