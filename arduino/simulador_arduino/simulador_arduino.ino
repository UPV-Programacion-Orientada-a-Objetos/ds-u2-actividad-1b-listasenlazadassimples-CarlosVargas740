/**
 * @file simulador_arduino.ino
 * @brief Código SIMPLE para Arduino - Simulador de Sensores IoT
 * @author Carlos Vargas
 * @date 30 de octubre de 2025
 * 
 * CÓMO USAR:
 * 1. Conecta el Arduino por USB
 * 2. Abre Arduino IDE
 * 3. Carga este código
 * 4. Abre Monitor Serial (Ctrl+Shift+M) a 9600 baudios
 * 5. Verás los datos enviándose automáticamente
 * 
 * Formato de datos: TIPO:ID:VALOR
 * Ejemplo: TEMP:T-001:25.3
 */

// Variables simples
int contador = 0;

void setup() {
  // Iniciar comunicación serial
  Serial.begin(9600);
  Serial.println("Arduino listo - Enviando datos...");
  delay(1000);
}

void loop() {
  // Enviar temperatura (simulada)
  float temperatura = 20.0 + random(0, 100) / 10.0;  // 20-30°C
  Serial.print("TEMP:T-001:");
  Serial.println(temperatura, 1);
  delay(1000);
  
  // Enviar presión (simulada)
  int presion = 1000 + random(0, 50);  // 1000-1050 kPa
  Serial.print("PRES:P-105:");
  Serial.println(presion);
  delay(1000);
  
  // Enviar vibración (simulada)
  int vibracion = random(0, 150);  // 0-150 Hz
  Serial.print("VIBR:V-201:");
  Serial.println(vibracion);
  delay(1000);
  
  contador++;
  
  // Pausa de 2 segundos entre ciclos
  delay(2000);
}

/*
 * INSTRUCCIONES PARA USAR CON SENSORES REALES:
 * 
 * 1. SENSOR DE TEMPERATURA (DHT11 o DHT22):
 *    - Instala librería: Sketch -> Include Library -> DHT sensor library
 *    - Conecta: VCC->5V, GND->GND, DATA->Pin 2
 *    - Código:
 *      #include <DHT.h>
 *      DHT dht(2, DHT11);
 *      float temp = dht.readTemperature();
 * 
 * 2. SENSOR DE PRESIÓN (BMP180 o BMP280):
 *    - Instala librería: Adafruit BMP280
 *    - Conecta: VCC->3.3V, GND->GND, SDA->A4, SCL->A5
 *    - Código:
 *      #include <Adafruit_BMP280.h>
 *      Adafruit_BMP280 bmp;
 *      float presion = bmp.readPressure() / 100;
 * 
 * 3. SENSOR DE VIBRACIÓN (Módulo SW-420):
 *    - Conecta: VCC->5V, GND->GND, DO->Pin 3
 *    - Código:
 *      int vibracion = digitalRead(3);
 */
