#ifndef IDEVICE_H
#define IDEVICE_H

#include <Arduino.h>


class IDevice
{
private:

virtual void startDisplay() = 0;
virtual void startSerial() = 0;
virtual void startGyro() = 0;

protected:

struct vector3D
{
    int16_t x;
    int16_t y;
    int16_t z;
};

struct accelGyro{
  vector3D accel;
  vector3D gyro ;
};

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

};

#endif