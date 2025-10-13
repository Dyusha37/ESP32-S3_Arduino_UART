#if defined(PLATFORM_ESP32)
#ifndef ESP32S2_H
#define ESP32S2_H

#include "IDevice.h"
#include "ESP32S3Pins.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_LSM6DS33.h>
#include "SDLogger.h"


class ESP32S3: public IDevice
{
private:
SDLogger logger;
UartPins uart;
DisplayPins disp;
GyroPins gyro;
SDPins sdPins;

GFXcanvas16 canvas16={240,240};
Adafruit_ST7789 display;
Adafruit_LSM6DS33 lsm6ds33;
SPIClass spi = SPIClass();
SPIClass spiSD = SPIClass();

void startDisplay() override;
void startGyro() override;
void startSerial() override ;


public:

ESP32S3(const UartPins& m_uart, const DisplayPins& m_disp, const GyroPins& m_gyro,const SDPins& m_sdPins);

void start() override;
void gyroGetData() override;
bool serialHaveData()override;
void UARTgetData() override;
void UARTsendData() override;
void printValues()override;
void loggerSendData()override;
};


#endif
#endif