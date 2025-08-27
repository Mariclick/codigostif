#define sensor A1          
#define RL 10.0       

void setup() {
  Serial.begin(9600);
}

void loop() {
  int valor_A0 = analogRead(sensor); // Lectura analógica (0 - 1023)
  float voltage = (valor_A0 / 1023.0) * 5.0; // Convertimos a voltaje (Vrl)
  float rs = ((5.0 - voltage) / voltage) * RL; // Cálculo de Rs en kΩ

  Serial.print("Entrada: ");
  Serial.print(valor_A0);
  Serial.print(" | Volt: ");
  Serial.print(voltage, 2);
  Serial.print(" V | Rs: ");
  Serial.print(rs, 2);
  Serial.println(" kΩ");

  delay(2000); // Espera 2 segundos entre lecturas
}
