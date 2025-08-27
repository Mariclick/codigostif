#include <LiquidCrystal.h>
LiquidCrystal lcd(5,6,8,9,10,11);
  
#define RL 10.0       
#define RO 6.31  
int rojo = 2;
int verde = 3;
int buzzer = 4;
int sensor1 = A1;
int referencia = 9;
int relemotor = 7;
int forvent = 12;
char dato;

void setup()
{
pinMode(relemotor, OUTPUT);
pinMode(forvent, OUTPUT);
pinMode(rojo, OUTPUT);
pinMode(verde,OUTPUT);
pinMode(buzzer,OUTPUT);
pinMode(sensor1,INPUT);
Serial.begin(9600);
Serial1.begin(9600);
lcd.begin(16,2);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("INICIANDO");
delay(60000);
}

void loop()
{
  if (Serial1.available()){
    dato = Serial1.read();
    }
    
  float Rs = calcularRs();
  float ratio = Rs / RO;
  float ppmCO = calppm(ratio);
  Serial1.println(ppmCO,2);
  
  //Serial.print("Rs: ");
  //Serial.print(Rs, 2);
  //Serial.print(" kohm  Rs/Ro: ");
  //Serial.print(ratio, 2);
  //Serial.print("  CO: ");
  //Serial.print(ppmCO, 2);  
  //Serial.println(ppmCO,2);  
  //Serial.println(" ppm");

  if(ppmCO>=referencia || dato == '1')
  {
    digitalWrite(rojo,HIGH);
    digitalWrite(verde,LOW);
    digitalWrite(relemotor,HIGH);
    tone(buzzer,1000,10000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ALERTA");
    lcd.setCursor(0,1);
    lcd.print(ppmCO);
    lcd.setCursor(6,1);
    lcd.print("PPM");
    delay(2000);
  }
  else
  {
    digitalWrite(verde,HIGH);
    digitalWrite(relemotor,LOW);
    digitalWrite(rojo,LOW);
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("AMBIENTE");
    lcd.setCursor(9,0);
    lcd.print("SEGURO");
    lcd.setCursor(0,1);
    lcd.print(ppmCO);
    lcd.setCursor(6,1);
    lcd.print("PPM");
    delay(2000);
  }  
   }
float calcularRs() {
  int adcValue = analogRead(sensor1);
  float voltage = (adcValue / 1023.0) * 5.0;
  float rs = (5.0 - voltage) / voltage * RL;
  return rs;
}

float calppm(float ratio) {
  float logRatio = log10(ratio);
  float logPPM = -0.77 * logRatio + 0.91; // Curva estimada del datasheet
  return pow(10, logPPM);
}
