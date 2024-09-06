#include "bluetooth_handler.h"

BluetoothHandler::BluetoothHandler(int rx, int tx) : msg_serial(rx, tx) {}

void BluetoothHandler::begin() {
    msg_serial.begin(9600);
}

void BluetoothHandler::handle_incoming_data(Braille &bra) {
    if (msg_serial.available()) {
        String str = msg_serial.readStringUntil('\n');
        str.replace("\r", "");
        strcpy(string_buffer, str.c_str());

        int ind = 0;
        int len = strlen(string_buffer);
        int index = 0;

        while (ind < len) {
            int bytes = get_char_byte(string_buffer + ind);
            if (bytes == 1) {
                string_buffer_serial[index][0] = *(string_buffer + ind);
                string_buffer_serial[index][1] = 0;
                string_buffer_serial[index][2] = 0;
                string_buffer_serial[index][3] = 0;
                index++;
            } else if (bytes == 3) {
                string_buffer_serial[index][0] = *(string_buffer + ind);
                string_buffer_serial[index][1] = *(string_buffer + ind + 1);
                string_buffer_serial[index][2] = *(string_buffer + ind + 2);
                string_buffer_serial[index][3] = 0;
                index++;
            }
            ind += bytes;
        }
        str_char_count = index;

        for (int i = 0; i < str_char_count; i++) {
            if (string_buffer_serial[i][1] == 0) {
                int code = string_buffer_serial[i][0];
                ASCIIProcessor::ascii_braille(code, bra);
                delay(500);
                bra.all_off();
                bra.refresh();
                delay(200);
                Serial.print(" - ASCII: ");
                Serial.println(ASCIIProcessor::ascii_data[code], BIN);
            } else {
                unsigned int cho, jung, jong;
                HangulProcessor::split_han_cho_jung_jong(string_buffer_serial[i][0], 
                                                         string_buffer_serial[i][1], 
                                                         string_buffer_serial[i][2], 
                                                         cho, jung, jong);
                HangulProcessor::han_braille(cho, jung, jong, bra);
                delay(500);
                bra.all_off();
                bra.refresh();
                delay(200);
                Serial.print(" - Hangul: ");
                Serial.print(HangulProcessor::hangul_cho[cho], BIN);
                Serial.print(",");
                Serial.print(HangulProcessor::hangul_jung[jung], BIN);
                Serial.print(",");
                Serial.println(HangulProcessor::hangul_jong[jong], BIN);
            }
        }
        Serial.println("");
    }
}

unsigned char BluetoothHandler::get_char_byte(char *pos) {
    char val = *pos;
    if ((val & 0b10000000) == 0) {
        return 1;
    } else if ((val & 0b11100000) == 0b11000000) {
        return 2;
    } else if ((val & 0b11110000) == 0b11100000) {
        return 3;
    } else if ((val & 0b11111000) == 0b11110000) {
        return 4;
    } else if ((val & 0b11111100) == 0b11111000) {
        return 5;
    } else {
        return 6;
    }
}