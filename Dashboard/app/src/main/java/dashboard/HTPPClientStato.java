package dashboard;




import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

public class HTPPClientStato {
    static HttpURLConnection con;

    public HTPPClientStato() throws Exception {
        URL url = new URL("http://localhost:8002/stato");
        con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("GET");
    }

    public static String getResponse() throws Exception {
        URL url = new URL("http://localhost:8002/stato");
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("GET");

        try (BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()))) {
            StringBuilder response = new StringBuilder();
            String inputLine;
            while ((inputLine = in.readLine()) != null) {
                response.append(inputLine);
            }
            return response.toString();
        } finally {
            con.disconnect(); // Chiudi la connessione
        }
    }
}
