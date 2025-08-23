#include <Arduino.h>
#include <HardwareSerial.h>
#include <U8g2lib.h>
#include <Wire.h>

// --- Definiciones y Constantes ---
// Pines para la comunicación con el sensor PMS5003
const int PMS_RX_PIN = 16;  // Pin RX del ESP32 (conectado al TX del sensor)
const int PMS_TX_PIN = 17;  // Pin TX del ESP32 (conectado al RX del sensor)

// Objeto para la comunicación serial con el sensor PMS5003
HardwareSerial pmsSerial(2);

// Objeto para el control de la pantalla OLED
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

// Estructura para almacenar los datos de partículas
struct PMSData {
  uint16_t pm1_0;
  uint16_t pm2_5;
  uint16_t pm10;
};

// --- Prototipos de Funciones ---
void setupOLED();
bool readPMSSensor(PMSData &data);
void displayData(const PMSData &data);

// --- Configuración Inicial ---
void setup() {
  Serial.begin(115200);
  pmsSerial.begin(9600, SERIAL_8N1, PMS_RX_PIN, PMS_TX_PIN);
  
  setupOLED();
  
  Serial.println("Iniciando lectura del sensor PMS5003...");
}

// --- Bucle Principal ---
void loop() {
  PMSData pmsData;
  if (readPMSSensor(pmsData)) {
    displayData(pmsData);
    delay(2000); // Espera antes de la siguiente lectura
  }
}

// --- Implementación de Funciones ---

/**
 * @brief Inicializa y muestra un mensaje de bienvenida en la pantalla OLED.
 */
void setupOLED() {
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 10,"Iniciando...");
  u8g2.sendBuffer();
  delay(2000);
  u8g2.clearBuffer();
  u8g2.drawStr(0, 10,"Esperando datos...");
  u8g2.sendBuffer();
}

/**
 * @brief Lee los datos del sensor PMS5003 y los almacena en la estructura.
 * @param data Referencia a la estructura donde se guardarán los datos.
 * @return true si la lectura fue exitosa, false en caso contrario.
 */
bool readPMSSensor(PMSData &data) {
  if (pmsSerial.available() < 32) {
    return false; // No hay suficientes datos disponibles
  }

  // Busca los bytes de cabecera 0x42 y 0x4D
  if (pmsSerial.read() != 0x42 || pmsSerial.read() != 0x4D) {
    return false;
  }

  uint8_t buffer[30];
  pmsSerial.readBytes(buffer, 30);

  // Calcula los valores de PM
  data.pm1_0 = (buffer[2] << 8) | buffer[3];
  data.pm2_5 = (buffer[4] << 8) | buffer[5];
  data.pm10  = (buffer[6] << 8) | buffer[7];

  return true;
}

/**
 * @brief Muestra los datos de partículas en la pantalla OLED y en el monitor serie.
 * @param data Estructura con los datos a mostrar.
 */
void displayData(const PMSData &data) {
  // --- Mostrar en Pantalla OLED ---
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 10,"Datos del sensor:");
  
  u8g2.setCursor(0, 30);
  u8g2.print(F("PM 1.0: "));
  u8g2.print(data.pm1_0);
  u8g2.print(F(" ug/m3"));

  u8g2.setCursor(0, 40);
  u8g2.print(F("PM 2.5: "));
  u8g2.print(data.pm2_5);
  u8g2.print(F(" ug/m3"));

  u8g2.setCursor(0, 50);
  u8g2.print(F("PM 10: "));
  u8g2.print(data.pm10);
  u8g2.print(F(" ug/m3"));
  
  u8g2.sendBuffer();

  // --- Mostrar en Monitor Serie ---
  Serial.print(F("PM 1.0: ")); Serial.print(data.pm1_0); Serial.print(F(" ug/m3  "));
  Serial.print(F("PM 2.5: ")); Serial.print(data.pm2_5); Serial.print(F(" ug/m3  "));
  Serial.print(F("PM 10: ")); Serial.print(data.pm10); Serial.println(F(" ug/m3"));
}