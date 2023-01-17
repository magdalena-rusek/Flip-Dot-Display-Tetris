#ifndef _SoftwareSPI_H
#define _SoftwareSPI_H

#if (ARDUINO >= 100)
# include <Arduino.h>
#else
# include <WProgram.h>
#endif

//#include "SoftwareSPI.h"
//#include <SPI.h>

class SoftwareSPI {
    private:
        uint8_t _delay;
        uint8_t _mosi;
        uint8_t _sck;

    public:
        //SoftwareSPI();
        void begin(uint8_t mosi, uint8_t sck);
        void end();
        void setClockDivider(uint8_t);
        uint8_t transfer(uint8_t);
};

#endif