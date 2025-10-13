#ifndef IDEVICE_H
#define IDEVICE_H

#include <Arduino.h>
#include "accelGyro.h"

class IDevice
{
private:

virtual void startDisplay() = 0;
virtual void startSerial() = 0;
virtual void startGyro() = 0;

protected:

accelGyro getAccelGyro;
accelGyro sendAccelGyro;

public:

virtual void start() {
  startDisplay();
  startGyro();
	startSerial();
}

virtual void gyroGetData()=0;
virtual bool serialHaveData()=0;
virtual void UARTgetData()=0;
virtual void UARTsendData()=0;
virtual void printValues()=0;
virtual void loggerSendData()=0;
};

#endif