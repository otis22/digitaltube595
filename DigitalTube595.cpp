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
};


void DigitalTube595::update(){
  //_show[0] = 0b11000001;
  for(byte i = 0; i <= 3; i++){ 
    digitalWrite(_rclk, LOW);
    shiftOut(_dio, _sclk, MSBFIRST, _show[i]); 
    shiftOut(_dio, _sclk, MSBFIRST, _chr[i]);   // включаем разряд
    digitalWrite(_rclk, HIGH); // защелкиваем регистры
    delayMicroseconds(1); // ждем немного перед отправкой следующего "числа"
  }      
};

bool DigitalTube595::_isDelimiter(char ch){
    return ch == '.' 
        || ch == ':'
        || ch == ','
        || ch == ';'; 
};

byte DigitalTube595::_getSymbol(char ch, char nextCh, char noLower){
    byte digit; 
    byte res;
    if (isDigit(ch)) {
        digit = (ch - '0');
        return _symbols[digit];
    } else {    
        switch (noLower) {
            case 'A': res = 0b10001000; break;
            case 'b': res = 0b10000011; break;
            case 'C': res = 0b11000110; break;
            case 'd': res = 0b10100001; break;
            case 'E': res = 0b10000110; break;
            case 'F': res = 0b10001110; break;
            case 'r': res = 0b10101111; break;
            case 'h': res = 0b10001011; break;
            case 'H': res = 0b10001001; break;
            case 'L': res = 0b11000111; break;
            case '-': res = 0b10111111; break;
            case ' ': res = 0b11111111; break;
            case 'p': 
            case 'р':
            case 'Р':
            case 'P': res = 0b10001100; break;
            case 'i': res = 0b11111011; break;
            case 'I': res = 0b11111001; break;
            case 'U': res = 0b11100011; break; 
            case 'u': res = 0b11000001; break;                
            case 'Г': res = 0b11001110; break;                 
            default: return 0; break; // ignored (off)
        }        
        return res;
    }   
};

void DigitalTube595::show(String str){  
  char ch;
  char nextCh = ' ';  
   
  byte len = str.length();
  byte last = len - 1;
  byte cnt = 0;
  //Если строка короче длины дисплее, забиваем пробелы.
  if (len < _length) {
    str + "     ";
  }
  for ( byte i=0; i < len; i++ ) {
    ch = tolower(str[i]);
    //Находим следующий символ
    if (i < last) {
        nextCh = tolower(str[i + 1]);
    } else {
        nextCh = ' ';
    }
    _show[cnt] = _getSymbol(ch, nextCh, str[i]);
    if (_isDelimiter(nextCh)) {
        i++;
        //отражаем точку на дисплее
        _show[cnt] = bitWrite(_show[cnt], 7, 0);
    }     
    cnt++;
    //Если длина исчерпана завершаем
    if (cnt > _length) {
        break;
    }
  }
};
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
const byte DigitalTube595::_chr[4] = {
  0b00001000,  
  0b00000100,  
  0b00000010,  
  0b00000001      
};	
