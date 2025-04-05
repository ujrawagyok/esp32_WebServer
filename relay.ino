#include <LiquidCrystal_I2C.h>
#include <ESPAsyncWebServer.h>
#include <Wifi.h>

LiquidCrystal_I2C lcd(0x27,16, 2);

const char* ssid= "wifinev";
const char* password = "wifijelszo";

AsyncWebServer server(80);  // Beállítjuk a szervert a 80-as portra
String header;          // a http request-ek tárolására.

void setup() {
  Serial.begin(115200);   
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){           // Kapcsolódás a hálózathoz
    delay(1000);
    Serial.println("Kapcsolódás a hálózathoz...");
  }

  Serial.println("Kapcsolódva a hálózathoz!");
  Serial.print("AZ ESP32 Web szerver IP címe: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [] (AsyncWebServerRequest* request){
    Serial.println("Új kapcsolat érkezet:");
    Serial.println("GET /");
    request->send(200, "text/html", 
    "<html><body><h1>Hello, ESP32!</h1></body></html>");
  });

  server.begin();    // A szerver indítása
}

void loop() {
  
}
