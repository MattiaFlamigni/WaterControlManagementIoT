package rivermonitoringservice;


import java.io.IOException;
import java.io.OutputStream;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;



public class HTTPData {

    

    static class MyHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange t) throws IOException {
            
            String response = "Dati aggiornati correttamente!";
            t.sendResponseHeaders(200, response.length());
            OutputStream os = t.getResponseBody();
            os.write(response.getBytes());
            os.close();


            try{
                Remote remote = new Remote();
                remote.setFetchData(true);
            }catch(Exception e){
                e.printStackTrace();
            }



        }
    }

}
