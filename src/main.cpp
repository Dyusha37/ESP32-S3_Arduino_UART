#include <Arduino.h>
#include <Arduino.h>

#if defined(PLATFORM_ARDUINO)
  #include "ArduinoUno.h"
  #define RX 10
  #define TX 11

  ArduinoUno device(RX, TX);

#elif defined(PLATFORM_ESP32)
  #include "ESP32S3Pins.h"
  #include "ESP32S3.h"
  
  UartPins uart = { .rxd = 4, .txd = 5 };
  DisplayPins disp = { .mosi = 11, .miso=13, .sclk = 12, .dc = 10, .rst = 9, .cs = -1 };
  GyroPins gyro = { .cs = 15, .sck = 16, .miso = 17, .mosi = 18 };
  SDPins sd = { .cs = 39, .sck = 40, .miso = 41, .mosi = 42 };
  
  ESP32S3 device(uart, disp, gyro,sd);

#endif

unsigned long timeStamp=0;
int8_t timeDelay = 50;

void setup() {
  device.start();
}
void loop() {
  device.gyroGetData();
  if(millis()>=timeStamp+timeDelay && device.serialHaveData()){
      timeStamp=millis();
      device.UARTgetData();
      device.UARTsendData();
      device.printValues();
  }
  else{
    device.loggerSendData();
  }
}
