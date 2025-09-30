#if defined(PLATFORM_ESP32)
#ifndef ESP32S2PINS_H
#define ESP32S2PINS_H

struct UartPins {
    int rxd;
    int txd;
};

struct DisplayPins {
    int mosi;
    int sclk;
    int dc;
    int rst;
    int cs;
};

struct GyroPins {
    int cs;
    int sck;
    int miso;
    int mosi;
};

#endif
#endif