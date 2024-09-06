#include "hangul_processor.h"

// 배열 정의
const byte HangulProcessor::hangul_cho[19] =
{
  0b00010000,//ㄱ
  0b00010000,//ㄲ
  0b00110000,//ㄴ
  0b00011000,//ㄷ
  0b00011000,//ㄸ
  0b00000100,//ㄹ
  0b00100100,//ㅁ
  0b00010100,//ㅂ
  0b00010100,//ㅃ
  0b00000001,//ㅅ
  0b00000001,//ㅆ
  0b00111100,//o
  0b00010001,//ㅈ
  0b00010001,//ㅉ
  0b00000101,//ㅊ
  0b00111000,//ㅋ
  0b00101100,//ㅌ
  0b00110100,//ㅍ
  0b00011100 //ㅎ
};
const byte HangulProcessor::hangul_jung[21] =
{
  0b00101001, // ㅏ
  0b00101110, // ㅐ
  0b00010110, // ㅑ 
  0b00010110, // ㅒ
  0b00011010, // ㅓ
  0b00110110, // ㅔ
  0b00100101, // ㅕ
  0b00010010, // ㅖ
  0b00100011, // ㅗ
  0b00101011, // ㅘ
  0b00101011, // ㅙ
  0b00110111, // ㅚ
  0b00010011, // ㅛ
  0b00110010, // ㅜ
  0b00111010, // ㅝ
  0b00111010, // ㅞ
  0b00110010, // ㅟ
  0b00110001, // ㅠ
  0b00011001, // ㅡ
  0b00011101, // ㅢ
  0b00100110 // ㅣ
};
const byte HangulProcessor::hangul_jong[28] =
{
  0b00000000, // 없음
  0b00100000, // ㄱ
  0b00100000, // ㄲ
  0b00100000, // ㄳ
  0b00001100, // ㄴ
  0b00001100, // ㄵ
  0b00001100, // ㄶ
  0b00000110, // ㄷ
  0b00001000, // ㄹ
  0b00001000, // ㄺ
  0b00001000, // ㄻ
  0b00001000, // ㄼ
  0b00001000, // ㄽ
  0b00001000, // ㄾ
  0b00001000, // ㄿ
  0b00001000, // ㅀ
  0b00001001, // ㅁ
  0b00101000, // ㅂ
  0b00101000, // ㅄ
  0b00000010, // ㅅ
  0b00000010, // ㅆ
  0b00001111, // ㅇ
  0b00100010, // ㅈ
  0b00001010, // ㅊ
  0b00001110, // ㅋ
  0b00001011, // ㅌ
  0b00001101, // ㅍ
  0b00000111 // ㅎ
};
const byte HangulProcessor::hangul2_cho[19] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
const byte HangulProcessor::hangul2_jung[21] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
const byte HangulProcessor::hangul2_jong[28] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27};

void HangulProcessor::split_han_cho_jung_jong(char byte1, char byte2, char byte3, 
                                              unsigned int &cho, unsigned int &jung, unsigned int &jong) {
    unsigned int utf16 = (byte1 & 0b00001111) << 12 | (byte2 & 0b00111111) << 6 | (byte3 & 0b00111111);
    unsigned int val = utf16 - 0xac00;
    unsigned char _jong = val % 28;
    unsigned char _jung = (val % (28 * 21)) / 28;
    unsigned char _cho = val / (28 * 21);
    
    cho = 0;
    for (int i = 0; i < 19; i++) {
        if (_cho == hangul2_cho[i]) {
            cho = i;
            break;
        }
    }
    
    jung = 0;
    for (int i = 0; i < 21; i++) {
        if (_jung == hangul2_jung[i]) {
            jung = i;
            break;
        }
    }
    
    jong = 0;
    for (int i = 0; i < 28; i++) {
        if (_jong == hangul2_jong[i]) {
            jong = i;
            break;
        }
    }
}

void HangulProcessor::han_braille(int index1, int index2, int index3, Braille &bra) {
    bra.all_off();
    
    // 초성
    for (int i = 0; i < 6; i++) {
        int on_off = hangul_cho[index1] >> (5 - i) & 0b00000001;
        if (on_off != 0) {
            bra.on(0, i);
        } else {
            bra.off(0, i);
        }
    }
    
    // 중성
    for (int i = 0; i < 6; i++) {
        int on_off = hangul_jung[index2] >> (5 - i) & 0b00000001;
        if (on_off != 0) {
            bra.on(1, i);
        } else {
            bra.off(1, i);
        }
    }
    
    // 종성
    for (int i = 0; i < 6; i++) {
        int on_off = hangul_jong[index3] >> (5 - i) & 0b00000001;
        if (on_off != 0) {
            bra.on(2, i);
        } else {
            bra.off(2, i);
        }
    }
    
    bra.refresh();
}