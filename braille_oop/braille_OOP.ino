#include "braille.h"
#include "bluetooth_handler.h"

Braille bra(2, 3, 4, 3);  // dataPin, latchPin, clockPin, no_module
BluetoothHandler bt_handler(6, 7);  // RX, TX

void setup() {
    Serial.begin(9600);
    bt_handler.begin();
    bra.begin();
    delay(1000);
    bra.all_off();
    bra.refresh();
}

void loop() {
    bt_handler.handle_incoming_data(bra);
}