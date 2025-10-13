#ifndef ACCELGYRO_H
#define ACCELGYRO_H
#include <Arduino.h>

struct vector3D
{
    int16_t x=0;
    int16_t y=0;
    int16_t z=0;
};

struct accelGyro{
  vector3D accel;
  vector3D gyro ;
};


#endif