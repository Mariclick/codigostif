#define sensor A1            
#define RL 10.0              
#define factordatasheet 9.6    

int cantmuestra = 50;             

void setup() {
  Serial.begin(9600);
   
  float ro = calibrarRo();
  
  Serial.print("Valor estimado de Ro: ");
  Serial.print(ro, 2);
  Serial.println(" kΩ");
}

void loop() {
  
}

float calcularRs() {
  int adcValue = analogRead(sensor);
  float voltage = (adcValue / 1023.0) * 5.0;
  float rs = (5.0 - voltage) / voltage * RL;
  return rs;
}


float calibrarRo() {
  float rsTotal = 0.0;
  for (int i = 0; i < cantmuestra; i++) {
    float rs = calcularRs();
    rsTotal += rs;
    Serial.print("Lectura ");
    Serial.print(i + 1);
    Serial.print(": Rs = ");
    Serial.print(rs, 2);
    Serial.println(" kΩ");
    delay(500);
  }
  float rsProm = rsTotal / cantmuestra;
  float ro = rsProm / factordatasheet;
  return ro;
}
