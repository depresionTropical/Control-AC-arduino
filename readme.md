# Proyecto: Control por Infrarrojo con Arduino

Este proyecto utiliza dos Arduinos para enviar y recibir señales infrarrojas (IR) a través de un emisor y un receptor IR. Adicionalmente, el control de las señales se puede realizar desde una página web con un interruptor y temporizador configurables por el usuario.

## Componentes

1. **Arduino Emisor**: Envía códigos IR basados en la interacción con un botón.
2. **Arduino Receptor**: Recibe y decodifica las señales IR para interpretarlas.
3. **Página Web**: Permite al usuario enviar comandos al emisor de IR a través de una interfaz web.

### Hardware Necesario

- 2 x Arduino (uno para el emisor y otro para el receptor)
- Emisor IR (LED IR)
- Receptor IR (sensor IR)
- 1 x Botón
- 1 x Resistencia 10kΩ
- Jumpers y protoboard
- Conexión WiFi para el Arduino Nano 33 IoT (para control vía web)

---

### Esqueme de proyecto