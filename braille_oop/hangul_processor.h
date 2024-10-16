#ifndef HANGUL_PROCESSOR_H
#define HANGUL_PROCESSOR_H

#include <Arduino.h>
#include "braille.h"  // braille 헤더 파일 포함


class HangulProcessor {
public:
    static void split_han_cho_jung_jong(char byte1, char byte2, char byte3, 
                                        unsigned int &cho, unsigned int &jung, unsigned int &jong);
    static void han_braille(int index1, int index2, int index3, Braille &bra);
    static const byte hangul_cho[19];
    static const byte hangul_jung[21];
    static const byte hangul_jong[28];
    static const byte hangul2_cho[19];
    static const byte hangul2_jung[21];
    static const byte hangul2_jong[28];
};

#endif
