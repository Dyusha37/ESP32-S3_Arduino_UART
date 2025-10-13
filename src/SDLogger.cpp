#if defined(PLATFORM_ESP32)
#include "SDLogger.h"

void SDLogger::start(SPIClass &spi){
  SD.begin(39, spi, 1000000);
  setupDataLogFile();
  setupNewLogFile();
}


int SDLogger::getConfigValue(const char* key,const char *path){
      File file = SD.open(path,FILE_READ);
  if (!file) return -1;
  String line;
  while (file.available()) {
    line = file.readStringUntil('\n');
    line.trim();
    if (line.startsWith(key)) {
      int eq = line.indexOf('=');
      if (eq > 0) {
        return line.substring(eq + 1).toInt();
      }
    }
  }
  file.close();
  return -1;
}

void SDLogger::setupNewLogFile(){
  logName = folderLogDataPath+"/log_";
  filesCount++;
  if(filesCount<10){
    logName += "0";
  }
  logName +=String(filesCount);
  logName+=".txt";
  updateDataLogFile();
  dataFile = SD.open(logName, FILE_APPEND);
}


void SDLogger::setupDataLogFile(){
  dataFile = SD.open(folderLogDataPath);
  if(!dataFile.isDirectory()){
    SD.mkdir(folderLogDataPath);
    dataFile.close();
  }
  else{
    dataFile.close();
    filesCount = getConfigValue(keyFilesCount.c_str(), logDataPath.c_str());
    if(filesCount<=0){
      filesCount=1;
    }
    dataFile.close();
  }
}

void SDLogger::updateDataLogFile(){
  String dataLogWrite;
  dataLogWrite = keyFilesCount+"="+String(filesCount);
  dataFile = SD.open(logDataPath, FILE_WRITE);
  dataFile.print(dataLogWrite);
  dataFile.close();
}

void SDLogger::writeAccelGyroLog(String name, accelGyro accelGyro, float gyroDivider, float accelDivider){
  dataString+="\n";
  dataString+= name;
  dataString+=":\nGyroscope:\n";
  dataString+="\tX "+ String(accelGyro.gyro.x/ gyroDivider);
  dataString+=" Y "+ String(accelGyro.gyro.y/ gyroDivider);
  dataString+=" Z "+ String(accelGyro.gyro.z/ gyroDivider);
  dataString+=":\nAccelerometr:\n";
  dataString+="\tX "+ String(accelGyro.accel.x/ accelDivider);
  dataString+=" Y "+ String(accelGyro.accel.y/ accelDivider);
  dataString+=" Z "+ String(accelGyro.accel.z/ accelDivider);
}

void SDLogger::writeDivider(){
  dataString+="\nTime: ";
  dataString+=String((millis()));
  dataString+="----------------------------------------";
}

void SDLogger::sendData(){
  if(dataString==""){
    return;
  }
  else{
    if (dataFile) {
      dataFile.println(dataString);
      dataString="";
      if(millis()>=timeStamp+timeFlush){
        timeStamp=millis();
        dataFile.flush();
      }
    }
  }
}
#endif