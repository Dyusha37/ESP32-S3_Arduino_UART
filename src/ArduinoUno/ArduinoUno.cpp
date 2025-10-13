#if defined(PLATFORM_ARDUINO)
#include "ArduinoUno.h"


ArduinoUno::ArduinoUno(int m_RX = 10, int m_TX = 11):
arduinoSerial(SoftwareSerial(m_RX,m_TX))
{
}

void ArduinoUno::startDisplay() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed!"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(F("System Start"));
  display.display();
}

void ArduinoUno::startGyro(){
  mpu.initialize();
  if (!mpu.testConnection()) {
    display.println(F("MPU6050 connection failed"));
    while (1);
  }
  display.println(F("MPU6050 OK"));
}

void ArduinoUno::startSerial()  {
  arduinoSerial.begin(9600);
  arduinoSerial.write((uint8_t*)&sendAccelGyro,sizeof(sendAccelGyro));
};

void ArduinoUno::start(){
  Wire.begin();
  IDevice::start();
}

void ArduinoUno::gyroGetData(){
  mpu.getMotion6(&sendAccelGyro.accel.x, &sendAccelGyro.accel.y, &sendAccelGyro.accel.z,
    &sendAccelGyro.gyro.x, &sendAccelGyro.gyro.y, &sendAccelGyro.gyro.z);
}

bool ArduinoUno::serialHaveData(){
  return arduinoSerial.available()>= sizeof(getAccelGyro);
}

void ArduinoUno::UARTgetData(){
  arduinoSerial.readBytes((uint8_t*)&getAccelGyro,sizeof(getAccelGyro));
}

void ArduinoUno::UARTsendData(){
  arduinoSerial.write((uint8_t*)&sendAccelGyro,sizeof(sendAccelGyro));
}

void ArduinoUno::printValues(){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println (F("Gyro: deg/s"));
  display.print("X ");
  display.print(getAccelGyro.gyro.x/1.75f);
  display.print(" Y ");
  display.println(getAccelGyro.gyro.y/1.75f);
  display.print("Z ");
  display.println(getAccelGyro.gyro.z/1.75f);
  display.println (F("Acceleration: g"));
  display.print("X ");
  display.print(getAccelGyro.accel.x/980.0f);
  display.print(" Y ");
  display.println(getAccelGyro.accel.y/980.0f);
  display.print("Z ");
  display.print(getAccelGyro.accel.z/980.0f);
  display.display();	
}

void ArduinoUno::loggerSendData(){}

#endif
