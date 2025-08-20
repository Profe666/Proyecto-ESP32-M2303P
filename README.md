# 🌱 Medidor de Pureza del Aire — M2303P

## 👥 Integrantes
- **Camilo Gómez**
- **Efren Alba**
- **Jenson Raba**  
📍 Colegio de Boyacá

---

## 📖 Introducción
El proyecto **"Medidor de pureza del aire" M2303P** busca medir la calidad del aire en el entorno cercano utilizando un **sensor de partículas PMS5003**, un **ESP32 con base de expansión** y una **pantalla OLED de 128x64 píxeles**.  

La motivación de este trabajo es crear una herramienta educativa y práctica que permita visualizar en tiempo real el nivel de pureza del aire, acercando conceptos de electrónica, programación y ciencias ambientales a los estudiantes.

---

## ⚙️ Componentes principales

### 🟢 ESP32 + base de expansión
El **ESP32** es el microcontrolador central del proyecto.  
- Se encarga de **recibir datos** del sensor PMS5003.  
- Procesa la información y la traduce en valores comprensibles.  
- Envía la información a la **pantalla OLED** para su visualización.  

La **base de expansión** facilita las conexiones eléctricas entre el ESP32, el sensor y la pantalla.

---

### 🟣 Sensor PMS5003
El **PMS5003** es un sensor de partículas que mide la concentración de contaminantes en el aire.  
Detecta partículas en suspensión de diferentes tamaños:  

- **PM1.0** → partículas muy finas (humo, aerosoles, polvo microscópico).  
- **PM2.5** → partículas respirables (contaminación urbana, combustión).  
- **PM10** → polvo, polen y partículas más grandes.  

Estos valores son importantes para evaluar la **calidad del aire** y sus efectos sobre la salud humana.

#### 📊 Traducción de datos
El PMS5003 envía los datos en forma de **tramas binarias** a través de comunicación serial (UART).  
El ESP32 interpreta estas tramas y extrae los valores de concentración:  

- Los bytes del mensaje contienen los valores de PM en microgramos por metro cúbico (µg/m³).  
- El ESP32 traduce esos valores y los organiza para mostrarlos en la pantalla OLED.  

---

### 🟡 Pantalla OLED 128x64
La pantalla OLED se encarga de **mostrar en tiempo real** los valores recibidos del PMS5003.  
Gracias a la librería **U8g2**, es posible dibujar texto y gráficos en la pantalla, lo que facilita la visualización de los niveles de pureza del aire.

---

## 📚 Librerías necesarias
Para compilar y ejecutar este proyecto en **PlatformIO (VSCode)**, se requieren las siguientes librerías:

- **U8g2** → para controlar la pantalla OLED.  
- **SoftwareSerial** o equivalente en ESP32 → para la comunicación con el PMS5003 (dependiendo de la implementación).  
- Librerías básicas de **Arduino-ESP32** incluidas en PlatformIO.

*(El archivo `platformio.ini` ya contiene la configuración necesaria para las dependencias.)*

---

## 🔄 Funcionamiento del proyecto
1. El ESP32 enciende y establece comunicación serial con el PMS5003.  
2. El sensor envía datos binarios con las concentraciones de partículas.  
3. El ESP32 procesa estos datos y los interpreta en valores de **PM1.0, PM2.5 y PM10**.  
4. Los valores son desplegados en la pantalla OLED para ser visualizados por el usuario.  

De esta manera, el sistema entrega una visión clara del **nivel de pureza del aire** en el ambiente donde se encuentra el sensor.

---

## ⚠️ Advertencia
Este proyecto se encuentra **en desarrollo**.  
Los valores obtenidos pueden variar según el entorno, el montaje y las condiciones ambientales.  
No se recomienda usar este sistema como sustituto de equipos de medición certificados.

---

✍️ *Proyecto académico desarrollado en el marco del Colegio de Boyacá.*
