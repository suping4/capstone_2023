// ascii_processor.h
#ifndef ASCII_PROCESSOR_H
#define ASCII_PROCESSOR_H

#include <Arduino.h>
#include "braille.h"

class ASCIIProcessor {
public:
    static void ascii_braille(int code, Braille &bra);
    static const byte ascii_data[127];
};

#endif // ASCII_PROCESSOR_H

