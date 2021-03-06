
/* PJON MAX485 serial modules RS485 communication example */

#include <PJON.h>

// <Strategy name> bus(selected device id)
PJON<ThroughSerial> bus(45);

void setup() {
  // Initialize LED 13 to be off
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  // Initialize Serial instance used for PJON communication
  Serial.begin(9600);
  bus.strategy.set_serial(&Serial);
  // Set enable pins
  bus.strategy.set_RS485_rxe_pin(3);
  bus.strategy.set_RS485_txe_pin(2);
  bus.set_error(error_handler);
  bus.begin();
  // Send B to device 44 every 1.5s
  bus.send_repeatedly(44, "B", 1, 1500000);
}

void error_handler(uint8_t code, uint8_t data) {
  if(code == PJON_CONNECTION_LOST)
    digitalWrite(13, HIGH); // Light up LED 13 if a packet transmission failed
}

void loop() {
    bus.update();
    bus.receive();
};
