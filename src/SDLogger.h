#if defined(PLATFORM_ESP32)
#ifndef SDLOGGER_H
#define SDLOGGER_H
#include <Arduino.h>
#include "FS.h"
#include "SD.h"
#include "accelGyro.h"

class SDLogger
{
private:

File dataFile;
String logName;
String folderLogDataPath = "/ESP32_logs";
String logDataName = "/datalog.txt";
String logDataPath= folderLogDataPath+logDataName;
String keyFilesCount = "files_count";
String dataString;

int filesCount=0;
int pinSC=10;
unsigned long timeStamp=0;
int timeFlush = 1000;

int getConfigValue(const char* key,const char *path);
void setupNewLogFile();
void setupDataLogFile();
void updateDataLogFile();

public:

void start(SPIClass &spi);
void writeAccelGyroLog(String name,accelGyro accelGyro, float gyroDivider, float accelDivider);
void writeDivider();
void sendData();
};
#endif
#endif