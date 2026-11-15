#include <ESP8266WiFi.h>

// Konfigurasi Wi-Fi (Ganti dengan kredensial jaringan Anda)
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Pin LED internal ESP8266 (NodeMCU / D1 Mini umumnya GPIO 2)
const int LED_PIN = 2;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // Default OFF untuk ESP8266 (Active LOW)

  Serial.println();
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Tunggu koneksi Wi-Fi berhasil
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected successfully!");
  Serial.print("IP Address: http://");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("HTTP Server started on port 80.");
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected.");
    String currentLine = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c == '\n') {
          // Baris kosong menandakan akhir HTTP request headers
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();

            // Web Dashboard interaktif modern
            client.println("<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<title>ESP8266 Web Control</title>");
            client.println("<style>body{font-family:Arial,sans-serif;text-align:center;padding:40px;background:#f3f4f6;}");
            client.println(".card{background:#fff;border-radius:12px;padding:30px;max-width:380px;margin:auto;box-shadow:0 4px 12px rgba(0,0,0,0.1);}");
            client.println(".btn{display:block;width:100%;padding:14px;margin:12px 0;font-size:16px;border-radius:8px;text-decoration:none;font-weight:bold;color:#fff;}");
            client.println(".btn-on{background:#2563eb;}.btn-off{background:#dc2626;}</style></head>");
            client.println("<body><div class=\"card\"><h2>ESP8266 Web Server</h2><p>Kontrol GPIO LED Pin 2</p>");
            client.println("<a href=\"/H\" class=\"btn btn-on\">Nyalakan LED (ON)</a>");
            client.println("<a href=\"/L\" class=\"btn btn-off\">Matikan LED (OFF)</a>");
            client.println("</div></body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        // Deteksi request HTTP GET (Active LOW pada NodeMCU)
        if (currentLine.indexOf("GET /H") >= 0) {
          digitalWrite(LED_PIN, LOW); // ON
        }
        if (currentLine.indexOf("GET /L") >= 0) {
          digitalWrite(LED_PIN, HIGH); // OFF
        }
      }
    }

    client.stop();
    Serial.println("Client disconnected.");
  }
}
