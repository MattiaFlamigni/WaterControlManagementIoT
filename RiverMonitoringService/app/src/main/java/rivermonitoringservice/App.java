package rivermonitoringservice;

import java.io.IOException;
import java.net.InetSocketAddress;
import com.sun.net.httpserver.HttpServer;
import rivermonitoringservice.HTTPServer.MyHandler;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;  

public class App {

    private static MqttSubscriber mqttSubscriber;
    

    public static void main(String[] args) {
        try {
            mqttSubscriber = new MqttSubscriber("tcp://broker.mqtt-dashboard.com:1883", "JavaSubscriber", "WaterLevel"   );
            mqttSubscriber.start();
        } catch (Exception e) {
            e.printStackTrace();
        }

        HttpServer server;
        HttpServer server1;
        HttpServer server2;
        HttpServer server3;



        try {
            server = HttpServer.create(new InetSocketAddress(8000), 0);
            server1 = HttpServer.create(new InetSocketAddress(8001), 0);
            server2 = HttpServer.create(new InetSocketAddress(8002), 0);
            server3 = HttpServer.create(new InetSocketAddress(8003), 0);
            

            server.createContext("/endpoint", new MyHandler());
            server1.createContext("/valvola", new HTTPValvola.MyHandler());
            server2.createContext("/stato", new HTTPStato.MyHandler());
            server3.createContext("/up<<<<<<<<<d>>>>>>>>>ate-data", new HTTPData.MyHandler());
            
            
            server.setExecutor(null); // creates a default executor
            server.start();
            server1.start();
            server2.start();
            server3.start();
        } catch (IOException e) {
            System.out.println("Errore nella creazione del server");
        }
        
    }


    



    
}
