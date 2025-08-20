#include <HardwareSerial.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
HardwareSerial pmsSerial(2);  // Usamos UART2 (puede ser 1 o 2)

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // OLED

// Pines personalizados
#define PMS_RX 16  // Lo que recibe el ESP32 (va al TX del sensor)
#define PMS_TX 17  // Lo que transmite el ESP32 (va al RX del sensor)

void setup() {
  Serial.begin(115200);  // Monitor Serial
  pmsSerial.begin(9600, SERIAL_8N1, PMS_RX, PMS_TX);  // PMS5003 baud rate
  u8g2.begin();  // Iniciar OLED
  Serial.println("iniciando pantalla OLED");
  Serial.println("Iniciando lectura del sensor PMS5003...");
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 10, "Esperando datos...");
  u8g2.sendBuffer();
  delay(3000);
}

void loop() {
  if (pmsSerial.available() >= 32) {  // El paquete tiene 32 bytes
    if (pmsSerial.read() == 0x42) {   // Cabecera byte 1
      if (pmsSerial.read() == 0x4D) { // Cabecera byte 2

        uint8_t data[30];
        pmsSerial.readBytes(data, 30);

        uint16_t pm1_0 = (data[2] << 8) | data[3];
        uint16_t pm2_5 = (data[4] << 8) | data[5];
        uint16_t pm10  = (data[6] << 8) | data[7];

        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_ncenB08_tr);
        u8g2.drawStr(0, 10, "Datos del sensor:");
        u8g2.setCursor(0, 30);
        u8g2.print("PM 1.0: "); u8g2.print(pm1_0); u8g2.print(" ug/m3");
        u8g2.setCursor(0, 40);
        u8g2.print("PM 2.5: "); u8g2.print(pm2_5); u8g2.print(" ug/m3");
        u8g2.setCursor(0, 50);
        u8g2.print("PM 10: "); u8g2.print(pm10); u8g2.print(" ug/m3");
        u8g2.sendBuffer();

        Serial.print("PM 1.0: "); Serial.print(pm1_0); Serial.print(" ug/m3  ");
        Serial.print("PM 2.5: "); Serial.print(pm2_5); Serial.print(" ug/m3  ");
        Serial.print("PM 10: "); Serial.print(pm10); Serial.println(" ug/m3");

        delay(2000);  // Espera antes de leer de nuevo
      }
    }
  }
}