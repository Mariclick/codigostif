// Definir el pin analógico conectado al sensor MQ-9
const int MQ_PIN = A0;    // Pin del sensor
const int RL_VALUE = 5;    // Resistencia RL del módulo en Kilo ohms
const int R0 = 10;         // Resistencia R0 del sensor en Kilo ohms

// Datos de la curva de calibración
const float X0 = 200;
const float Y0 = 1.7;
const float X1 = 10000;
const float Y1 = 0.28;

// Puntos de la curva de concentración {X, Y}
const float punto0[] = { log10(X0), log10(Y0) };
const float punto1[] = { log10(X1), log10(Y1) };

// Calcular pendiente y coordenada de la curva
const float scope = (punto1[1] - punto0[1]) / (punto1[0] - punto0[0]);
const float coord = punto0[1] - punto0[0] * scope;

// Configuración inicial
void setup() {
  Serial.begin(9600);  // Inicializar comunicación serial
}

void loop() {
  // Leer la resistencia del sensor
  float rs_med = readMQ(MQ_PIN);   // Obtener la Rs promedio
  float concentration = getConcentration(rs_med / R0);  // Obtener la concentración de CO
  
  // Mostrar el valor de la concentración de CO en ppm por serial
  Serial.print("Concentración de CO (ppm): ");
  Serial.println(concentration);
  
  delay(1000);  // Esperar 1 segundo antes de la siguiente lectura
}

// Función para obtener la resistencia promedio en N muestras
float readMQ(int mq_pin) {
  float rs = 0;
  for (int i = 0; i < 5; i++) {  // Tomamos 5 muestras para promedio
    rs += getMQResistance(analogRead(mq_pin));
    delay(100);  // Tiempo entre lecturas (100 ms)
  }
  return rs / 5;  // Promedio de las resistencias
}

// Función para convertir la lectura analógica en resistencia
float getMQResistance(int raw_adc) {
  return (((float)RL_VALUE / 1000.0 * (1023 - raw_adc) / raw_adc));  // Cálculo de resistencia
}

// Función para calcular la concentración de CO en ppm
float getConcentration(float rs_ro_ratio) {
  return pow(10, coord + scope * log(rs_ro_ratio));  // Aplicar la fórmula de la curva de calibración
}