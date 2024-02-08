package dashboard;

import java.net.InetSocketAddress;

import javax.swing.SwingUtilities;

import java.io.IOException;
import java.net.InetSocketAddress;
import com.sun.net.httpserver.HttpServer;

public class Main {
    public static void main(String[] args) {

        HttpServer server;
        try{
            
            server =  HttpServer.create(new InetSocketAddress(7000), 0);
            server.createContext("/remote", new MyHandler());
            server.setExecutor(null);
            server.start();
        }catch (IOException e){
            e.printStackTrace();
        }
        
        SwingUtilities.invokeLater(() -> {
            Dashboard example;
            try {
                example = new Dashboard();
                example.setVisible(true);

            } catch (Exception e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        });
    }
}
