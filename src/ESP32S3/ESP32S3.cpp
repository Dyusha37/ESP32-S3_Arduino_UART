#if defined(PLATFORM_ESP32)
#include "ESP32S3.h"

ESP32S3::ESP32S3(const UartPins& m_uart, const DisplayPins& m_disp, const GyroPins& m_gyro,const SDPins& m_sdPins)
    : uart(m_uart),
      disp(m_disp),
      gyro(m_gyro),
      sdPins(m_sdPins),
      display(Adafruit_ST7789(m_disp.cs, m_disp.dc, m_disp.rst))
{
}

void ESP32S3::startDisplay() {
  display.init(240, 240, SPI_MODE3);
  display.setRotation(2);
  display.fillScreen(ST77XX_BLACK);
  display.setTextColor(ST77XX_WHITE);
  display.setTextSize(2);
  display.setCursor(10, 10);
  display.println("System Start");
}

void ESP32S3::startGyro() {
  if (!lsm6ds33.begin_SPI(gyro.cs, gyro.sck, gyro.miso, gyro.mosi)) {
    //display.println("Failed to find LSM6DS33 chip");
    while (1) {
      delay(10);
    }
  }
  //display.println("LSM6DS33 Found!");
  lsm6ds33.getAccelRange();
  lsm6ds33.getGyroRange();
  lsm6ds33.getAccelDataRate();
  lsm6ds33.getGyroDataRate();
  lsm6ds33.configInt1(false, false, true);
  lsm6ds33.configInt2(false, true, false);
}

void ESP32S3::startSerial()  {
  Serial1.begin(9600, SERIAL_8N1, uart.rxd, uart.txd);
  Serial1.write((uint8_t*)&sendAccelGyro,sizeof(sendAccelGyro));
}

void ESP32S3::start() {
  spi.begin(disp.sclk, disp.miso, disp.mosi);
  spiSD.begin(sdPins.sck,sdPins.miso,sdPins.mosi);
  IDevice::start();
  logger.start(spiSD);
}

void ESP32S3::gyroGetData() {
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  lsm6ds33.getEvent(&accel,&gyro,&temp);
  sendAccelGyro.accel.x=accel.acceleration.x*100;
  sendAccelGyro.accel.y=accel.acceleration.y*100;
  sendAccelGyro.accel.z=accel.acceleration.z*100;
  sendAccelGyro.gyro.x=gyro.gyro.x*100;
  sendAccelGyro.gyro.y=gyro.gyro.y*100;
  sendAccelGyro.gyro.z=gyro.gyro.z*100;
}

bool ESP32S3::serialHaveData(){
  return Serial1.available()>= sizeof(getAccelGyro);
}

void ESP32S3::UARTgetData() {
  Serial1.read((uint8_t*)&getAccelGyro,sizeof(getAccelGyro));
}

void ESP32S3::UARTsendData() {
  Serial1.write((uint8_t*)&sendAccelGyro,sizeof(sendAccelGyro));
}

void ESP32S3::printValues(){
  canvas16.fillScreen(0); 
  canvas16.setTextSize(2);
  canvas16.setCursor(0, 10);	
  canvas16.print ("Gyro: deg/s");	
  canvas16.setCursor(0, 30);	
  canvas16.print("X ");
  canvas16.print(getAccelGyro.gyro.x/ 131.0f);
  canvas16.print(" Y ");
  canvas16.print(getAccelGyro.gyro.y/ 131.0f);
  canvas16.setCursor(0, 50);
  canvas16.print("Z ");
  canvas16.print(getAccelGyro.gyro.z/ 131.0f);
  canvas16.setCursor(0, 70);	
  canvas16.print ("Acceleration: g");	
  canvas16.setCursor(0, 90);	
  canvas16.print("X ");
  canvas16.print(getAccelGyro.accel.x /16384.0f);
  canvas16.print(" Y ");
  canvas16.print(getAccelGyro.accel.y/ 16384.0f);
  canvas16.setCursor(0, 110);
  canvas16.print("Z ");
  canvas16.print(getAccelGyro.accel.z/ 16384.0f);

  display.drawRGBBitmap(0,0,canvas16.getBuffer(), canvas16.width(),canvas16.height());
  logger.writeDivider();
  logger.writeAccelGyroLog("Arduino", getAccelGyro,131.0f,16384.0f);
  logger.writeAccelGyroLog("ESP32", sendAccelGyro, 1.75f,980.0f);
}


void ESP32S3::loggerSendData(){
  logger.sendData();
}
#endif