#include <IRremote.h>


#define BUTTON_PIN 2  // Pin donde está el botón
// #define IR_LED_PIN 3  // Pin donde está el emisor IR

int DELAY_BETWEEN_REPEAT = 50;  // Retardo entre envíos
bool sendFirstCode = true;  // Alternar entre dos códigos
bool lastButtonState = HIGH;  // Estado anterior del botón

// Código IR para enviar
// unsigned long code1 = 0x1FE48B7;  // Ejemplo de código IR 1 (NEC)
uint16_t code1[67] = {9000, 4500, 650, 550, 650, 1650, 600, 550, 650, 550,
                        600, 1650, 650, 550, 600, 1650, 650, 1650, 650, 1650,
                        600, 550, 650, 1650, 650, 1650, 650, 550, 600, 1650,
                        650, 1650, 650, 550, 650, 550, 650, 1650, 650, 550,
                        650, 550, 650, 550, 600, 550, 650, 550, 650, 550,
                        650, 1650, 600, 550, 650, 1650, 650, 1650, 650, 1650,
                        650, 1650, 650, 1650, 650, 1650, 600};
// unsigned long code2 = 0x1FE58A7;  // Ejemplo de código IR 2 (NEC)
uint16_t code2[67] = {9000, 4500, 650, 550, 650, 1650, 600, 550, 650, 550,
                        600, 1650, 650, 550, 600, 1650, 650, 1650, 650, 1650,
                        600, 550, 650, 1650, 650, 1650, 650, 550, 600, 1650,
                        650, 1650, 650, 550, 650, 550, 650, 1650, 650, 550,
                        650, 550, 650, 550, 600, 550, 650, 550, 650, 550,
                        650, 1650, 600, 550, 650, 1650, 650, 1650, 650, 1650,
                        650, 1650, 650, 1650, 650, 1650, 600};
const uint16_t IR_LED_PIN = 3;
IRsend irsend(IR_LED_PIN);

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Configura el botón con resistencia pull-up
  // Configura el emisor IR en el pin 3 (o el que uses)
  Serial.begin(115200);  // Inicia la comunicación serial
  Serial.println("Listo");
  Serial.println(F("Sistema IR listo"));
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);
  Serial.println(buttonState);
  // Detecta si el botón fue presionado
  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(50);  // Debouncing simple
    if (digitalRead(BUTTON_PIN) == LOW) {  // Confirma que el botón sigue presionado
      if (sendFirstCode) {
        // Envía el primer código IR
        Serial.println(F("Enviando código 1"));
        irsend.sendRaw(code1, 67, 38);  // Envía el código 1
      } else {
        // Envía el segundo código IR
        Serial.println(F("Enviando código 2"));
        irsend.sendRaw(code1, 67, 38);  // Envía el código 2
      }

      // Alterna entre los dos códigos
      sendFirstCode = !sendFirstCode;

      delay(DELAY_BETWEEN_REPEAT);  // Espera antes de aceptar otro envío
    }
  }

  // Guarda el estado del botón para el siguiente ciclo
  lastButtonState = buttonState;
}
