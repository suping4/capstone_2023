#include "ascii_processor.h"

// ascii_data 배열 정의
const byte ASCIIProcessor::ascii_data[127] =
{
  0b00000000, // 0
  0b00000000, // 1
  0b00000000, // 2
  0b00000000, // 3
  0b00000000, // 4
  0b00000000, // 5
  0b00000000, // 6
  0b00000000, // 7
  0b00000000, // 8
  0b00000000, // 9
  0b00000000, // 10
  0b00000000, // 11
  0b00000000, // 12
  0b00000000, // 13
  0b00000000, // 14
  0b00000000, // 15
  0b00000000, // 16
  0b00000000, // 17
  0b00000000, // 18
  0b00000000, // 19
  0b00000000, // 20
  0b00000000, // 21
  0b00000000, // 22
  0b00000000, // 23
  0b00000000, // 24
  0b00000000, // 25
  0b00000000, // 26
  0b00000000, // 27
  0b00000000, // 28
  0b00000000, // 29
  0b00000000, // 30
  0b00000000, // 31
  0b00000000, // 32 SPACE
  0b00001110, // 33 !
  0b00001011, // 34 "
  0b00000000, // 35 #
  0b00000000, // 36 $
  0b00010010, // 37 %
  0b00000000, // 38 &
  0b00000000, // 39 '
  0b00001011, // 40 (
  0b00000001, // 41 )
  0b00100001, // 42 *
  0b00001001, // 43 +
  0b00000100, // 44 ,
  0b00000110, // 45 -
  0b00001101, // 46 .
  0b00010101, // 47 /
  0b00011100, // 48 0
  0b00100000, // 49 1
  0b00101000, // 50 2
  0b00110000, // 51 3
  0b00110100, // 52 4
  0b00100100, // 53 5
  0b00111000, // 54 6
  0b00111100, // 55 7
  0b00101100, // 56 8
  0b00011000, // 57 9
  0b00000100, // 58 :
  0b00000101, // 59 ;
  0b00000100, // 60 <
  0b00001100, // 61 =
  0b00000111, // 62 >
  0b00001011, // 63 ?
  0b00000000, // 64 @
  0b00100000, // 65 A
  0b00101000, // 66 B
  0b00110000, // 67 C
  0b00110100, // 68 D
  0b00100100, // 69 E
  0b00111000, // 70 F
  0b00111100, // 71 G
  0b00101100, // 72 H
  0b00011000, // 73 I
  0b00011100, // 74 J
  0b00100010, // 75 K
  0b00101010, // 76 L
  0b00110010, // 77 M
  0b00110110, // 78 N
  0b00100110, // 79 O
  0b00111010, // 80 P
  0b00111110, // 81 Q
  0b00101110, // 82 R
  0b00011010, // 83 S
  0b00011110, // 84 T
  0b00100011, // 85 U
  0b00101011, // 86 V
  0b00011101, // 87 W
  0b00110011, // 88 X
  0b00110111, // 89 Y
  0b00100111, // 90 Z
  0b00001011, // 91 [
  0b00010000, // 92 \  //
  0b00000101, // 93 ]
  0b00000000, // 94 ^
  0b00000011, // 95 _
  0b00000000, // 96 '
  0b00100000, // 97 a
  0b00101000, // 98 b
  0b00110000, // 99 c
  0b00110100, // 100 d
  0b00100100, // 101 e
  0b00111000, // 102 f
  0b00111100, // 103 g
  0b00101100, // 104 h
  0b00011000, // 105 i
  0b00011100, // 106 j
  0b00100010, // 107 k
  0b00101010, // 108 l
  0b00110010, // 109 m
  0b00110110, // 110 n
  0b00100110, // 111 o
  0b00111010, // 112 p
  0b00111110, // 113 q
  0b00101110, // 114 r
  0b00011010, // 115 s
  0b00011110, // 116 t
  0b00100011, // 117 u
  0b00101011, // 118 v
  0b00011101, // 119 w
  0b00110011, // 120 x
  0b00110111, // 121 y
  0b00100111, // 122 z
  0b00001011, // 123 {
  0b00000000, // 124 |
  0b00000100, // 125 }
  0b00000000, // 126 ~
};

void ASCIIProcessor::ascii_braille(int code, Braille &bra) {
    bra.all_off();
    for (int i = 0; i < 6; i++) {
        int on_off = ascii_data[code] >> (5 - i) & 0b00000001;
        if (on_off != 0) {
            bra.on(0, i);
        } else {
            bra.off(0, i);
        }
    }
    bra.refresh();
}