#include <LiquidCrystal_I2C.h>
#include <ESPAsyncWebServer.h>
#include <Wifi.h>

LiquidCrystal_I2C lcd(0x27,16, 2);

const char* ssid= "wifinev";
const char* password = "wifijelszo";

AsyncWebServer server(80);  // Beállítjuk a szervert a 80-as portra

int relay1State = LOW;
int relay2State = LOW; 
int relay3State = LOW; 
int relay4State = LOW; 

void setup() {

  pinMode(19, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(16, OUTPUT);

  Serial.begin(115200);   
  WiFi.begin(ssid, password);
  lcd.init();
  lcd.backlight();

  while(WiFi.status() != WL_CONNECTED){           // Kapcsolódás a hálózathoz
    delay(1000);
    Serial.println("Kapcsolódás a hálózathoz...");
    lcd.setCursor(0,0);
    lcd.print("Kapcsolodas");
  }

  Serial.println("Kapcsolódva a hálózathoz!");
  Serial.print("AZ ESP32 Web szerver IP címe: ");
  Serial.println(WiFi.localIP());
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Kapcsolodva");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
    html += "<title>Relay Vezérlés</title></head><body>";
    html += "<h1>IN1 " + String(relay1State == LOW ? "BE" : "KI") + "</h1>";
    html += "<a href=\"/IN1_on\"><button>KI</button></a>";
    html += "<a href=\"/IN1_off\"><button>BE</button></a>";
    html += "<h1>IN2 " + String(relay2State == LOW ? "BE" : "KI") + "</h1>";
    html += "<a href=\"/IN2_on\"><button>KI</button></a>";
    html += "<a href=\"/IN2_off\"><button>BE</button></a>";
    html += "<h1>IN3 " + String(relay3State == LOW ? "BE" : "KI") + "</h1>";
    html += "<a href=\"/IN3_on\"><button>KI</button></a>";
    html += "<a href=\"/IN3_off\"><button>BE</button></a>";
    html += "<h1>IN4 " + String(relay4State == LOW ? "BE" : "KI") + "</h1>";
    html += "<a href=\"/IN4_on\"><button>KI</button></a>";
    html += "<a href=\"/IN4_off\"><button>BE</button></a>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  server.on("/IN1_on", HTTP_GET, [](AsyncWebServerRequest *request){
    relay1State = HIGH;
    digitalWrite(19, HIGH);
    request->redirect("/");
  });
  server.on("/IN1_off", HTTP_GET, [](AsyncWebServerRequest *request){
    relay1State = LOW;
    digitalWrite(19, LOW);
    request->redirect("/");
  });

  server.on("/IN2_on", HTTP_GET, [](AsyncWebServerRequest *request){
    relay2State = HIGH;
    digitalWrite(18, HIGH);
    request->redirect("/");
  });
  server.on("/IN2_off", HTTP_GET, [](AsyncWebServerRequest *request){
    relay2State = LOW;
    digitalWrite(18, LOW);
    request->redirect("/");
  });

  server.on("/IN3_on", HTTP_GET, [](AsyncWebServerRequest *request){
    relay3State = HIGH;
    digitalWrite(17, HIGH);
    request->redirect("/");
  });
  server.on("/IN3_off", HTTP_GET, [](AsyncWebServerRequest *request){
    relay3State = LOW;
    digitalWrite(17, LOW);
    request->redirect("/");
  });

  server.on("/IN4_on", HTTP_GET, [](AsyncWebServerRequest *request){
    relay4State = HIGH;
    digitalWrite(16, HIGH);
    request->redirect("/");
  });
  server.on("/IN4_off", HTTP_GET, [](AsyncWebServerRequest *request){
    relay4State = LOW;
    digitalWrite(16, LOW);
    request->redirect("/");
  });

  server.begin();    // A szerver indítása
  lcd.clear();
}

void loop() {
  
  if(digitalRead(19)){
    lcd.setCursor(0,0);
    lcd.print("IN1: L");
  }
  else{
    lcd.setCursor(0,0);
    lcd.print("IN1: H");
  }
  if(digitalRead(18)){
    lcd.setCursor(0,1);
    lcd.print("IN2: L");
  }
  else{
    lcd.setCursor(0,1);
    lcd.print("IN2: H");
  }
  if(digitalRead(17)){
    lcd.setCursor(8,0);
    lcd.print("IN3: L");
  }
  else{
    lcd.setCursor(8,0);
    lcd.print("IN3: H");
  }
  if(digitalRead(16)){
    lcd.setCursor(8,1);
    lcd.print("IN4: L");
  }
  else{
    lcd.setCursor(8,1);
    lcd.print("IN4: H");
  }
}