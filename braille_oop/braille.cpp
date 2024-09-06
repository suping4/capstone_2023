#include "braille.h"

Braille::Braille(int data_pin, int latch_pin, int clock_pin, int no)
    : dataPin(data_pin), latchPin(latch_pin), clockPin(clock_pin), braille_no(no) {
    memset(data, 0, sizeof(data));
}

void Braille::begin() {
    pinMode(dataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
}

void Braille::on(int no, int index) {
    data[braille_no - no - 1] |= (0b00000001 << index);
}

void Braille::off(int no, int index) {
    data[braille_no - no - 1] &= ~(0b00000001 << index);
}

void Braille::refresh() {
    digitalWrite(latchPin, LOW);
    for (int i = 0; i < braille_no; i++) {
        shiftOut(dataPin, clockPin, LSBFIRST, data[i]);
    }
    digitalWrite(latchPin, HIGH);
}

void Braille::all_off() {
    memset(data, 0, sizeof(data));
}