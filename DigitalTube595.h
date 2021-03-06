/**
DigitalTube595 - class for work with digital led tube on two 74HC595
*/

#ifndef DigitalTube595_h
#define DigitalTube595_h

#include <Arduino.h>
class DigitalTube595
{
	public:
		DigitalTube595(uint8_t sclk, uint8_t rclk, uint8_t dio, uint8_t length);
		void update();
		void show(String str);
		int delay;
	private:
		uint8_t _sclk;
		uint8_t _rclk;
		uint8_t _dio;
		uint8_t _length;
		static const byte _symbols[];
		static const byte _chr[];
		byte _show[4];
		void _init();
		byte _getSymbol(char ch, char nextCh, char noLower);
		bool _isDelimiter(char ch);
};
#endif
