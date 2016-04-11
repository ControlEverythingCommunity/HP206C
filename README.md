[![HP206C]( HP206C_I2CS.png)](https://www.controleverything.com/content/Analog-Digital-Converters?sku=HP206C_I2CS)
# HP206C
HP206C Barometer and Altimeter Sensor.

The HP206C is a device that measures the altitude, pressure and the temperature by an internal 24-bit ADC

This Device is available from ControlEverything.com [SKU:  HP206C_I2CS]

https://www.controleverything.com/content/Analog-Digital-Converters?sku=HP206C_I2CS

This Sample code can be used with Raspberry pi, Arduino and Particle.

## Java
Download and install pi4j library on Raspberry pi. Steps to install pi4j are provided at:

http://pi4j.com/install.html

Download (or git pull) the code in pi.

Compile the java program.
```cpp
$> pi4j HP206C.java
```

Run the java program.
```cpp
$> pi4j HP206C
```

## Python
Download and install smbus library on Raspberry pi. Steps to install smbus are provided at:

https://pypi.python.org/pypi/smbus-cffi/0.5.1

Download (or git pull) the code in pi. Run the program.

```cpp
$> python HP206C.py
```

## Arduino
Download and install Arduino Software (IDE) on your machine. Steps to install Arduino are provided at:

https://www.arduino.cc/en/Main/Software

Download (or git pull) the code and double click the file to run the program.

Compile and upload the code on Arduino IDE and see the output on Serial Monitor.

#####The code output is the altitude in meters, pressure in Pa and temperature reading in degree celsius and fahrenheit
