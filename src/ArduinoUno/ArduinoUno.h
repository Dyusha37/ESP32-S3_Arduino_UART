#if defined(PLATFORM_ARDUINO)

#ifndef ARDUINOUNO_H
#define ARDUINOUNO_H

#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "IDevice.h"

class ArduinoUno: public IDevice
{
private:

SoftwareSerial arduinoSerial;
MPU6050 mpu;
Adafruit_SSD1306 display={128, 64, &Wire, -1};

void startDisplay() override;
void startGyro() override;
void startSerial() override;

public:

ArduinoUno(int m_RX = 10, int m_TX = 11);

void start() override;
void gyroGetData()override;
bool serialHaveData()override;
void UARTgetData()override;
void UARTsendData()override;
void printValues()override;
void loggerSendData()override;
};

#endif
#endif