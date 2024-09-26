#include <IRremote.h>
#include <WiFiNINA.h>

#define BUTTON_PIN 2  // Pin donde está el botón
// #define IR_LED_PIN 3  // Pin donde está el emisor IR

// Configuración de la red WiFi
char ssid[] = "itmerida";      // Cambia por tu SSID
char pass[] = "";  // Cambia por tu contraseña

int DELAY_BETWEEN_REPEAT = 50;  // Retardo entre envíos
bool sendFirstCode = true;      // Alternar entre dos códigos
bool lastButtonState = HIGH;    // Estado anterior del botón

// Código IR para enviar
// unsigned long code1 = 0x1FE48B7;  // Ejemplo de código IR 1 (NEC)
const uint16_t  on[] = {6050, 7450, 550, 1650, 550, 1650, 500, 1700, 500, 1700, 500, 1700, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 550, 550, 550, 550, 1650, 550, 1650, 550, 1650, 550, 1650, 550, 1650, 550, 1650, 550, 1650, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 500, 1700, 500, 1700, 500, 1700, 500, 1650, 550, 1650, 550, 1650, 550, 550, 550, 550, 550, 600, 500, 550, 550, 550, 550, 550, 550, 550, 550, 600, 500, 1650, 550, 550, 550, 1650, 550, 550, 500, 1700, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 1700, 500, 600, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 500, 600, 500, 1650, 550, 600, 500, 1650, 550, 1650, 550, 1650, 550, 550, 550, 600, 500, 1650, 550, 550, 550, 1650, 550, 550, 550, 600, 500, 600, 500, 1650, 550, 550, 550, 1650, 500, 650, 450, 1700, 500, 600, 500, 600, 500, 1700, 500, 600, 500, 1700, 500, 600, 500, 1700, 500, 600, 500, 1700, 500, 1700, 500, 7400, 500};
// unsigned long code2 = 0x1FE58A7;  // Ejemplo de código IR 2 (NEC)
const uint16_t off[] = {6100, 7350, 600, 1600, 600, 1600, 600, 1600, 600, 1600, 600, 1600, 600, 1600, 600, 1600, 600, 1600, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 550, 1600, 600, 1600, 600, 1600, 600, 1600, 600, 1600, 600, 1600, 600, 1600, 600, 1600, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 550, 550, 550, 550, 550, 550, 550, 1650, 550, 1650, 550, 1600, 600, 1600, 600, 1600, 600, 1600, 600, 1600, 600, 1600, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 1600, 600, 1600, 600, 1600, 600, 500, 600, 1600, 600, 1600, 550, 1650, 550, 1650, 550, 550, 550, 550, 550, 550, 550, 1600, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 1600, 600, 1600, 600, 550, 550, 1600, 600, 500, 600, 1600, 600, 1600, 600, 1600, 600, 500, 600, 500, 600, 1600, 600, 500, 600, 1600, 600, 500, 600, 500, 600, 500, 600, 1600, 600, 500, 550, 1650, 600, 500, 600, 1600, 550, 550, 550, 550, 550, 1600, 600, 500, 600, 1600, 600, 500, 600, 1600, 600, 500, 600, 1600, 600, 1600, 600, 7300, 600 };
const uint16_t IR_LED_PIN = 3;
IRsend irsend(IR_LED_PIN);
WiFiServer server(80);

void setup() {
  Serial.begin(115200);


  // Conectar a la red WiFi
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Conectando a ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    Serial.println(WiFi.localIP());
    delay(10000);
  }

  Serial.println("Conectado a WiFi.");
  server.begin();
  Serial.println(WiFi.localIP());
}
void enviarSenalEncendido() {
  irsend.sendRaw(on, sizeof(on) , 38);  // Enviar señal de encendido
  Serial.println("Señal de encendido enviada.");
}

void enviarSenalApagado() {
  irsend.sendRaw(off, sizeof(off) , 38);  // Enviar señal de apagado
  Serial.println("Señal de apagado enviada.");
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Cliente conectado.");
    String req = client.readStringUntil('\r');
    Serial.println(req);
    Serial.println("Holap");
    client.flush();

    // Procesar el comando recibido
    if (req.indexOf("/comando/encender") != -1) {
      enviarSenalEncendido();
    }
    if (req.indexOf("/comando/apagar") != -1) {
      enviarSenalApagado();
    }

    // Responder al cliente
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();
    client.println("{ \"status\": \"ok\" }");
    client.println();
    client.stop();
    Serial.println("Cliente desconectado.");
  }
}
