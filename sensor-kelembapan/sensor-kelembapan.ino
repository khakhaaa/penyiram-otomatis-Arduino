#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int soilMoisturePin = A0; // Pin analog untuk sensor kelembapan tanah
const int pumpPin = 7; //Pin pompa air

void setup() {
  Serial.begin(9600);
  lcd.init(); // Inisialisasi LCD
  lcd.backlight(); // Aktifkan pencahayaan LCD
  lcd.setCursor(0, 0);
  lcd.print("Soil Moisture:");
  lcd.setCursor(0, 1);
}

void loop() {
  int soilMoistureValue = analogRead(soilMoisturePin); //Deklarasi variabel soilMoist & Baca nilai kelembapan tanah
  int soilMoisturePercent = map(soilMoistureValue, 1023, 0, 0, 100); // Konversi nilai analog menjadi persentase

  // Menampilkan nilai kelembapan pada LCD
  lcd.setCursor(0, 1);
  lcd.print("                "); // Menghapus baris sebelumnya
  lcd.setCursor(0, 1);
  lcd.print("Moisture: ");
  lcd.print(soilMoisturePercent); //Menampilkan value dari variabel soilMoist
  lcd.print("%");

  // Menentukan tanah kering atau basah berdasarkan nilai kelembapan
  if (soilMoisturePercent < 30) { //Jika kelembapan kurang dari 30% maka:
    lcd.setCursor(0, 0);
    lcd.print("Soil Status: Dry  ");
    digitalWrite(pumpPin, HIGH); //Pompa air nyala
  } else { //Jika kelembapan lebih dari 30% maka:
    lcd.setCursor(0, 0);
    lcd.print("Soil Status: Wet  ");
    digitalWrite(pumpPin, LOW); //Pompa air mati
  }

  delay(1000); //delay 1 detik
}
