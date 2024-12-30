// Kendali 3 Led dengan Sensor Suhu
#include <LiquidCrystal_I2C.h>//Menambahkan Library LCD
LiquidCrystal_I2C lcd(0x27,16,2);// Mengatur Alamat LCD

#include "DHT.h"
#define DHTPIN 15 
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE); 

#define led_red 14
#define led_yellow 13
#define led_green 12


void setup() {
    dht.begin();
    lcd.init();// Inisialisasi LCD
    lcd.backlight();// Mengaktifkan Cahaya Latar LCD
    lcd.setCursor(1,0);// Mengatur Posisi Teks pada LCD
    lcd.print("PEMANAS OTOMATIS"); // Menuliskan Teks Pada LCD
    lcd.setCursor(2,1);// Mengatur Posisi Teks pada LCD
    lcd.print("SENSOR SUHU"); // Menuliskan Teks Pada LCD
    delay(5000); // Waktu Tunda

  Serial.begin(9600);
  pinMode(led_red, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_green, OUTPUT);
  
}

void loop() {
  int Kelembaban = dht.readHumidity();
  float tempC = dht.readTemperature();

  lcd.setCursor(0,0);
  lcd.print("T=");
  lcd.print(tempC,1);lcd.write(0xdf);lcd.print("C  ");
  lcd.print("H=");
  lcd.print(Kelembaban);lcd.print("%  ");

  if ( isnan(tempC&&Kelembaban)) {
    Serial.println("Gagal membaca data dari sensor DHT!");
    lcd.setCursor(0,0);
    lcd.print("Sensor Error");
  } 
  else if(tempC>=35) {
    digitalWrite(led_red, HIGH); 
    digitalWrite(led_yellow, LOW);
    digitalWrite(led_green, LOW); 
    Serial.println("SUHU PANAS");
    lcd.setCursor(0,1);
    lcd.print("SUHU PANAS     ");

     } else if (tempC>=21) {
    digitalWrite(led_red, LOW); 
    digitalWrite(led_yellow, HIGH); 
    digitalWrite(led_green, LOW); 
    Serial.println("SUHU SEDANG");
    lcd.setCursor(0,1);
    lcd.print("SUHU SEDANG     ");

   } else if (tempC<20.9) {
    digitalWrite(led_red, LOW);  
    digitalWrite(led_yellow, LOW); 
    digitalWrite(led_green, HIGH);  
     Serial.println("SUHU DINGIN");
     lcd.setCursor(0,1);
    lcd.print("SUHU DINGIN     ");

  }
  delay(1000);
}