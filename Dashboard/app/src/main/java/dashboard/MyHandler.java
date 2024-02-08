package dashboard;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

public class MyHandler implements HttpHandler {
    private String apertura = "";

    public MyHandler() {}

    @Override
    public void handle(HttpExchange t) throws IOException {
        if ("POST".equals(t.getRequestMethod())) {
            // Se la richiesta è di tipo POST, leggi il corpo della richiesta per ottenere il contenuto inviato dal client
            StringBuilder requestBody = new StringBuilder();
            try (BufferedReader reader = new BufferedReader(new InputStreamReader(t.getRequestBody()))) {
                String line;
                while ((line = reader.readLine()) != null) {
                    requestBody.append(line);
                }
            }

            // Il contenuto della richiesta POST è ora disponibile in requestBody
            System.out.println("Contenuto della richiesta POST: " + requestBody.toString());

            // Puoi quindi utilizzare il contenuto della richiesta come necessario per elaborare la richiesta e generare una risposta
            String response = Dashboard.getLabelValue();

            // Invia la risposta al client
            t.sendResponseHeaders(200, response.length());
            try (OutputStream os = t.getResponseBody()) {
                os.write(response.getBytes());
            }
        } else {
            // Se la richiesta non è di tipo POST, invia una risposta di metodo non consentito (405 Method Not Allowed)
            String response = "Metodo non consentito";
            t.sendResponseHeaders(405, response.length());
            try (OutputStream os = t.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }
}
