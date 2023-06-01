#include <dht.h>
#include <LiquidCrystal.h>
#include <DS3231.h>
 
#define dht_dpin0 8
//
dht DHT1;

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
DS3231  rtc(SDA, SCL);

float hum = 0.0;
float tem = 0.0;
//
Time  t;

void setup() {
  rtc.begin();
  Serial.begin(9600);
  lcd.begin(20, 4);                        
}

void loop() {
  // Get data from the DS3231
  t = rtc.getTime();
  String current_date = String(rtc.getDateStr());
  current_date.replace('.','-');
  // Send a command to retrieve the temperature and humidity
  DHT1.read11(dht_dpin0);
  // Read humidity
  hum = DHT1.humidity;
  // Read temperature as Celsius (the default)
  tem = DHT1.temperature;
  //
  delay(500);
  Serial.println(current_date + 'A' + String(tem));
  Serial.flush();
  for(int i = 0; i <= 300; i++){
    if(Serial.available() > 0){
      i = 300;
      //
      String readText = "";
      //
      readText = Serial.readStringUntil('\n');
      delay(10);
      readText.toUpperCase();
      //
      // Display values on LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Today: " + current_date);
      lcd.setCursor(0, 1);
      lcd.print("Temperature: " + String(tem,1) + "\337C"); 
      lcd.setCursor(0, 2);
      lcd.print("Tomorrow Forecast: ");
      lcd.setCursor(0, 3);
      lcd.print("Temperature: " + String(readText) + "\337C");
      //
      delay(500);
    }
    delay(10);
  }
}
