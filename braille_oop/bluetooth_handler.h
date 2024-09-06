#ifndef BLUETOOTH_HANDLER_H
#define BLUETOOTH_HANDLER_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "braille.h"
#include "hangul_processor.h"
#include "ascii_processor.h"

class BluetoothHandler {
public:
    BluetoothHandler(int rx, int tx);
    void begin();
    void handle_incoming_data(Braille &bra);

private:
    SoftwareSerial msg_serial;
    char string_buffer[100];
    char string_buffer_serial[100][4];
    int str_char_count;

    unsigned char get_char_byte(char *pos);
};

#endif