package rivermonitoringservice;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

public class Remote {
    static HttpURLConnection con;
    private static boolean fetchData = false;

    public Remote() throws Exception {
        URL url = new URL("http://localhost:7000/remote");
        con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("GET");
    }

    public static String fetchData() throws Exception {
        if (fetchData) {
            URL url = new URL("http://localhost:7000/remote");
            HttpURLConnection con = (HttpURLConnection) url.openConnection();
            con.setRequestMethod("GET");

            try (BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream(), "utf-8"))) {
                StringBuilder response = new StringBuilder();
                String inputLine;
                while ((inputLine = in.readLine()) != null) {
                    response.append(inputLine);
                }
                fetchData = false; // Resetta il flag dopo aver letto i dati


                System.out.println("YYYYYYYYYYY");
                return response.toString();
            } finally {
                con.disconnect(); // Chiudi la connessione
            }
        } else {
            return null; // Nessuna nuova richiesta di dati
        }
    }

    public static void setFetchData(boolean value) {
        fetchData = value;
    }
}
