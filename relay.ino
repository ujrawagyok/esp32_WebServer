/* Ebben a projektben egy esp32 Wroom, egy I2C LCD kijelző 
   és egy relé modul irányítását gyakorlom web serveres megvalósítással.

   Az ötlet egyszrű: a böngészőben bármely relé állapotát lehet szabályozni, 
   és az lcd kijelző mindig az aktuális állapotot mutatja a reléknek.

   Eszközök: esp32 wroom dev-kit
             4 realy module
             I2C LCD kijelző
            
   I2C:    d22-SCL, d21-SDA
   Relay modul: D19-IN4, D18-IN3, D17-IN2, D16-IN1
*/
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16, 2);


void setup() {

  pinMode(19, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(17, OUTPUT);                          // Ez az alapkód amiből fejlesztem a projektet.
  pinMode(16, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello World!");
  lcd.setCursor(0, 1);
  lcd.print("Hello World!");
}

void loop() {
  digitalWrite(19, LOW);
  digitalWrite(18, LOW);
  digitalWrite(17, LOW);
  digitalWrite(16, LOW);
  delay(5000);

  digitalWrite(19, HIGH);
  digitalWrite(18, HIGH);
  digitalWrite(17, HIGH);
  digitalWrite(16, HIGH);
  delay(5000);
/*
  lcd.setCursor(0, 0)
  lcd.print("R1: ", IN1);
  lcd.setCursor(8, 0)
  lcd.print("R2: ", IN2);
  lcd.setCursor(0, 1)
  lcd.print("R3: ", IN3);
  lcd.setCursor(8, 1)
  lcd.print("R4: ", IN4);*/
}
