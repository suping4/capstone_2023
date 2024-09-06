#ifndef BRAILLE_H
#define BRAILLE_H

#include <Arduino.h>

#define MAX_BRAILLE_NO 10

class Braille {
public:
    Braille(int data_pin, int latch_pin, int clock_pin, int no);
    void begin();
    void on(int no, int index);
    void off(int no, int index);
    void refresh();
    void all_off();

private:
    uint8_t data[MAX_BRAILLE_NO];
    int braille_no;
    int dataPin;
    int latchPin;
    int clockPin;
};

#endif