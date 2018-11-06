// A sample Java code to mark a Statuscope task as successful

import java.net.URL;
import java.io.OutputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.io.IOException;

public class Sample {

    public static void main(String[] args) {
        try {
            // Define endpoint of the task and set request type
            URL url = new URL("https://www.statuscope.io/tasks/jigqqiCXZgJHyjmsE");
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setDoOutput(true);
            connection.setRequestMethod("POST");
            connection.setRequestProperty("Content-Type", "application/json");

            // Define parameters matching the task
            String input = "{\"token\":\"839b41ac\", \"status\":\"OK\"}";

            // Make the request
            OutputStream os = connection.getOutputStream();
            os.write(input.getBytes());
            os.flush();

            // Any HTTP response code other than 200 indicates an error
            if (connection.getResponseCode() != HttpURLConnection.HTTP_OK) {
                throw new RuntimeException("HTTP response code: " + connection.getResponseCode());
            }

            // Read the response
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader((connection.getInputStream())));
            String output;
            while ((output = bufferedReader.readLine()) != null) {
                System.out.println(output);
            }

            connection.disconnect();

        } catch (MalformedURLException e) {
            e.printStackTrace();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
