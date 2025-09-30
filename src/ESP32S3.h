#if defined(PLATFORM_ESP32)
#ifndef ESP32S2_H
#define ESP32S2_H

#include "IDevice.h"
#include "ESP32S3Pins.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_LSM6DS33.h>

class ESP32S3: public IDevice
{
private:

UartPins uart;
DisplayPins disp;
GyroPins gyro;

GFXcanvas16 canvas16={240,240};
Adafruit_ST7789 display;
Adafruit_LSM6DS33 lsm6ds33;

void startDisplay() override;
void startGyro() override;
void startSerial() override ;


public:

ESP32S3(const UartPins& m_uart, const DisplayPins& m_disp, const GyroPins& m_gyro);

void start() override;
void gyroGetData() override;
bool serialHaveData()override;
void UARTgetData() override;
void UARTsendData() override;
void printValues()override;
};


#endif
#endif