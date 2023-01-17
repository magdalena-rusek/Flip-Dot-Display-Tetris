#include "SoftwareSPI.h"

//SoftwareSPI::SoftwareSPI() {
//    _mosi = mosi;
//    _sck = sck;
//    _delay = 2;
//}

void SoftwareSPI::begin(uint8_t mosi, uint8_t sck) {
    _mosi = mosi;
    _sck = sck;
    //_delay = 2;
    pinMode(_mosi, OUTPUT);
    pinMode(_sck, OUTPUT);
}

void SoftwareSPI::end() {
    pinMode(_mosi, INPUT);
    pinMode(_sck, INPUT);
}

void SoftwareSPI::setClockDivider(uint8_t div) {
	_delay = div;
}

uint8_t SoftwareSPI::transfer(uint8_t val) {
    uint8_t del = _delay >> 1;

    uint8_t bval = 0;
    for (int8_t bit = 7; bit >= 0; bit--) {
        digitalWrite(_mosi, val & (1<<bit) ? HIGH : LOW);

        for (uint8_t i = 0; i < del; i++) {
            asm volatile("nop");
        }

        digitalWrite(_sck, LOW);

        for (uint8_t i = 0; i < del; i++) {
            asm volatile("nop");
        }

        digitalWrite(_sck, HIGH);
    }
    return 0;
}