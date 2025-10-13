# ESP32-S3_Arduino_UART

The project demonstrates the operation of connection and interaction between **ESP32-S3** and **Arduino Uno**.  
Each device is connected to an accelerometer/gyroscope and a display.  
ESP32 is connected to **LSM6DS33** and **ST7789** via the **SPI** interfaces,  
and Arduino is connected to **MPU6050** and **SSD1306** via **I2C**.  
Both devices are connected to each other via **UART**.  

Each device reads data from its own sensor, sends it to the other device,  
and that device displays the received data on its display.  
Also, ESP32 is connected to a **microSD card adapter**, where logs of transmitted and received data are recorded.

The architecture is built through the universal interface **IDevice**,  
so that the code remains common for both platforms.

---

## Logic of operation

When creating a class object, the constructor receives the pins for the connections.  
In the `setup()` method, the device calls the `start()` method. Inside it:

1. The connection interfaces are initialized.  
2. The methods `startDisplay()`, `startGyro()`, and `startSerial()` are called to connect all devices.  
3. ESP32 also calls the method `start(SPIClass &spi)` of the **SDLogger** class to connect and start the SD card for log recording.

---

### In `loop()`:

1. The method `gyroGetData()` is called, inside which data from the gyroscope/accelerometer is taken.  
2. It is checked whether enough time has passed and whether there is data to receive.  
3. If both conditions are met:  
   - The devices receive each other's data in the method `UARTgetData()` and send their own data in the method `UARTsendData()`.  
   - The devices display the received data on the display in the function `printValues()`.  
   - At the end of `printValues()`, ESP32 calls the method `writeAccelGyroLog()` of the **SDLogger** class to send data from both devices to the logger.  
4. If the conditions are not met, the method `loggerSendData()` is called, so that while the main work is not performed, the log is written to the microSD card.  
   - Inside this method, only the method `sendData()` of the **SDLogger** class is called.

---

To initialize **SDLogger**, the method `start(SPIClass &spi)` is called.  
As a parameter, it takes `spi`, through which the microSD card adapter will be connected.  

Inside the method:
- The memory card is connected, and in the method `setupDataLogFile()` the configuration file is read.  
  If such a file does not exist, it is created from scratch.  
- A new log file is created.  
- The method `updateDataLogFile()` is called, in which the number of log files in the configuration file is updated.  
- A new log file is opened.

When the method `writeAccelGyroLog()` is called, it adds data to a string that will be written to the log file.

When the method `sendData()` is called, it checks whether there is data in the string that can be written to the log file,  
and if there is, this data is written. After that, the string is cleared.

---

## Result

- Connection and data transmission via **UART**, **SPI**, **I2C** protocols  
- Universal class architecture with a common **IDevice** interface  
- Data logging to a **microSD card**
