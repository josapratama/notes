#include <WiFi.h>

const char* ssid = "Empat Putra";
const char* password = "joni1973";

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  Serial.print("connection to ");
  Serial.print(ssid);

  WiFi.begin(ssid, password);
  while (Wifi.status()!= WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  if(client){
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()){
      if(client.available()){
        char c = client.read();
        Serial.write(c);
        if(c == '\n') {
          if(currentLine.length() == 0){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("Click <a href=\"/H\">here</a> to turn the LeD on pin 5 on.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn the LeD on pin 5 on.<br>");
            client.println();
            break;
          }else{
            currentLine = "";
          }
        }else if ( c!='\r'){
          currentLine +=c;
        }
        if(currentLine.endsWith("Get /H")){
          digitalWrite(2, HIGH);
        }
        if(currentLine.endsWith("Get /L")){
          digitalWrite(2, LOW);
        }
      }
    }
    client.stop();
    Serial.println("Client Disconnected");
  }
}
