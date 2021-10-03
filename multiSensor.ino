#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define rain_sensor 8
#define temp_sensor A0
#define fix_button 7
LiquidCrystal_I2C lcd_screen(0x27, 16, 2);

int temp_value = 0;
float temp_voltage = 0;
float temperature = 0;
int wait = 100;
bool is_fix = 0;
bool rain_sensor_check = 0;

void setup() {
  pinMode(rain_sensor, INPUT);
  pinMode(fix_button,INPUT);              
  Serial.begin(9600);

  lcd_screen.init();// lcd screen starting
  lcd_screen.backlight();
  lcd_screen.setCursor(0, 0);
  lcd_screen.print("Starting App..");
  delay(1000);
  lcd_screen.clear();// lcd screen started

}

void loop() {

  is_fix = digitalRead(fix_button);
  rain_sensor_check = digitalRead(rain_sensor);// Yağmur yoksa true, varsa false döndürür.
  temp_value = analogRead(temp_sensor);
  temp_voltage = (5000 / 1023.0) * temp_value;
  temperature = temp_voltage / 10.0;


  lcd_screen.setCursor(0, 1);
  lcd_screen.print("Sicaklik ");
  lcd_screen.print(temperature);

  lcd_screen.setCursor(0, 0);
  lcd_screen.print("Yagmur");

  if (!rain_sensor_check) {
    lcd_screen.setCursor(7, 0);
    lcd_screen.print("var");
    Serial.println("Yağmur Var!");
  } else {
    lcd_screen.setCursor(7, 0);
    lcd_screen.print("yok");
    Serial.println("Yağmur Yok!");
  }
  if (is_fix)
    wait = 100;
  if (wait < 120000)
    wait = wait * 11 / 10;

  delay(wait);
}
