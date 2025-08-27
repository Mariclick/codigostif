#define sensor A1          
#define RL 10.0       
#define RO 6.31            

void setup() {
  Serial.begin(9600);
  Serial.println("Midiendo CO con sensor MQ-9...");
}

void loop() {
  float Rs = calcularRs();
  float ratio = Rs / RO;
  float ppmCO = calppm(ratio);

  Serial.print("Rs: ");
  Serial.print(Rs, 2);
  Serial.print(" kΩ | Rs/Ro: ");
  Serial.print(ratio, 2);
  Serial.print(" | CO: ");
  Serial.print(ppmCO, 2);
  Serial.println(" ppm");

  delay(2000);
}

float calcularRs() {
  int adcValue = analogRead(sensor);
  float voltage = (adcValue / 1023.0) * 5.0;
  float rs = (5.0 - voltage) / voltage * RL;
  return rs;
}

float calppm(float ratio) {
  float logRatio = log10(ratio);
  float logPPM = -0.77 * logRatio + 0.91; // Curva estimada del datasheet
  return pow(10, logPPM);
}
