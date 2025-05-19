// Include library for LCD and define pins 
#include <LiquidCrystal.h> 

const int rs = 9, en = 8, d4 = 4, d5 = 5, d6 = 6, d7 = 7; 
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); 

#define GasSensorPin A5  
const int buzzer = 11; 
const int mq135_aqi_sensor = A3; 
const int smokeA0 = A1; 

int aqi_ppm = 0; 
int sensorThres = 500; 
int gasThreshold = 350;

void setup() { 
  pinMode(mq135_aqi_sensor, INPUT); 
  pinMode(smokeA0, INPUT); 
  pinMode(buzzer, OUTPUT); 
  digitalWrite(buzzer, LOW); 
  
  Serial.begin(9600); 
  lcd.begin(16, 2); 
  lcd.clear(); 
  Serial.println("AQI Alert System"); 
  delay(1000); 
} 

void loop() { 
  // ---------- MQ-9 SENSOR ----------
  int gasValue = analogRead(GasSensorPin); 
  lcd.setCursor(0, 0); 
  lcd.print("MQ-9 SENSOR: "); 
  lcd.print(gasValue); 
  delay(2000); 
  Serial.print("MQ-9 SENSOR: "); 
  Serial.println(gasValue); 

  if (gasValue > gasThreshold) { 
    while (gasValue > gasThreshold) { 
      gasValue = analogRead(GasSensorPin); 
      digitalWrite(buzzer, HIGH); 
      Serial.println("Gas detected! Buzzer is ON"); 
      lcd.setCursor(0, 1); 
      lcd.print("Gas detected!   "); 
      delay(1000); 
      lcd.clear(); 
    } 
  } else { 
    digitalWrite(buzzer, LOW); 
    Serial.println("No gas detected. Buzzer is OFF"); 
    lcd.setCursor(0, 1); 
    lcd.print("No gas detected "); 
    delay(2000); 
    lcd.clear(); 
  } 

  // ---------- MQ-135 SENSOR ----------
  aqi_ppm = analogRead(mq135_aqi_sensor); 
  Serial.print("Air Quality: "); 
  Serial.println(aqi_ppm); 
  lcd.setCursor(0, 0); 
  lcd.print("Air Quality: "); 
  lcd.print(aqi_ppm); 
  delay(2000); 

  lcd.setCursor(0, 1); 
  if (aqi_ppm <= 50) { 
    lcd.print("AQI Good       "); 
    Serial.println("AQI Good"); 
  } else if (aqi_ppm <= 100) { 
    lcd.print("AQI Moderate   "); 
    Serial.println("AQI Moderate"); 
  } else if (aqi_ppm <= 200) { 
    lcd.print("AQI Unhealthy  "); 
    Serial.println("AQI Unhealthy"); 
  } else if (aqi_ppm <= 300) { 
    lcd.print("AQI V.Unhealthy"); 
    Serial.println("AQI V.Unhealthy"); 
  } else { 
    lcd.print("AQI Hazardous  "); 
    Serial.println("AQI Hazardous"); 
  } 
  delay(2000); 
  lcd.clear(); 

  // ---------- MQ-2 SENSOR ----------
  int analogSensor = analogRead(smokeA0); 
  lcd.setCursor(0, 0); 
  lcd.print("MQ-2 SENSOR: "); 
  lcd.print(analogSensor); 
  delay(2000); 
  Serial.print("MQ-2: "); 
  Serial.println(analogSensor); 

  if (analogSensor > sensorThres) { 
    while (analogSensor > sensorThres) { 
      analogSensor = analogRead(smokeA0); 
      digitalWrite(buzzer, HIGH); 
      lcd.setCursor(0, 1); 
      lcd.print("Smoke detected!"); 
      Serial.println("Smoke detected!"); 
      delay(1000); 
      lcd.clear(); 
    } 
  } else { 
    digitalWrite(buzzer, LOW); 
    lcd.setCursor(0, 1); 
    lcd.print("No Smoke Detect"); 
    delay(1000); 
    lcd.clear(); 
  } 
}
