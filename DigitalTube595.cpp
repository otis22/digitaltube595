/**
DigitalTube595 - class for work with digital led tube on two 74HC595
*/
#include "Arduino.h"
#include "DigitalTube595.h"
DigitalTube595::DigitalTube595(uint8_t sclk, uint8_t rclk, uint8_t dio, uint8_t length)
{
    _sclk = sclk;
    _rclk = rclk;
    _dio = dio;
    _length = length;
    delay = 5;
    _init();
    
}
void DigitalTube595::_init(){
    pinMode(_sclk, OUTPUT);
    pinMode(_rclk, OUTPUT);
    pinMode(_dio, OUTPUT);
    digitalWrite( _sclk, LOW );
    digitalWrite( _rclk, LOW );
}
void DigitalTube595::update(){
  for(byte i = 0; i <= 3; i++){ 
    digitalWrite(_rclk, LOW);
    shiftOut(_dio, _sclk, MSBFIRST, _show[i]); 
    shiftOut(_dio, _sclk, MSBFIRST, _chr[i]);   // включаем разряд
    digitalWrite(_rclk, HIGH); // защелкиваем регистры
    delayMicroseconds(1); // ждем немного перед отправкой следующего "числа"
  }      
}

void DigitalTube595::show(String str){
  
  char ch;
  char nextCh = ' ';  
  byte digit;  
  byte len = str.length();
  byte last = len - 1;
  byte cnt = 0;
  
  for ( byte i=0; i < len; i++ ) {
     ch = tolower(str[i]);
     if (i < last) {
        nextCh = tolower(str[i + 1]);
     } else {
        nextCh = ' ';
     }
     if ('0' <= ch && ch <= '9') {
       digit = (ch - '0');
       if (nextCh != '.') {
           _show[cnt] = _symbols[digit];
       } else {
           _show[cnt] = _symbolsWithDot[digit];
           i++;
       }
       cnt++;
     }
  }
}
const byte DigitalTube595::_symbols[] = {
  0b11000000, // 0
  0b11111001, // 1
  0b10100100, // 2
  0b10110000, // 3
  0b10011001, // 4
  0b10010010, // 5
  0b10000010, // 6
  0b11111000, // 7
  0b10000000, // 8
  0b10010000, // 9 
};
const byte DigitalTube595::_symbolsWithDot[] = {
  0b01000000, // 0
  0b01111001, // 1
  0b00100100, // 2
  0b00110000, // 3
  0b00011001, // 4
  0b00010010, // 5
  0b00000010, // 6
  0b01111000, // 7
  0b00000000, // 8
  0b00010000, // 9 
};	
const byte DigitalTube595::_chr[4] = {
  0b00001000,  
  0b00000100,  
  0b00000010,  
  0b00000001      
};	
