# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# HP206C
# This code is designed to work with the HP206C_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Analog-Digital-Converters?sku=HP206C_I2CS#tabs-0-product_tabset-2

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# HP206C address, 0x76(118)
# Send OSR and channel setting command, 0x44(68)
bus.write_byte(0x76, 0x44 | 0x00)

time.sleep(0.5)

# HP206C address, 0x76(118)
# Read data back from 0x10(16), 6 bytes
# cTemp MSB, cTemp CSB, cTemp LSB, pressure MSB, pressure CSB, pressure LSB
data = bus.read_i2c_block_data(0x76, 0x10, 6)

# Convert the data to 20-bits
cTemp = (((data[0] & 0x0F) * 65536) + (data[1] * 256) + data[2]) / 100.00
fTemp = (cTemp * 1.8) + 32
pressure = (((data[3] & 0x0F) * 65536) + (data[4] * 256) + data[5]) / 100.00

# HP206C address, 0x76(118)
# Send OSR and channel setting command, 0x44(68)
bus.write_byte(0x76, 0x44 | 0x01)

time.sleep(0.5)

# HP206C address, 0x76(118)
# Read data back from 0x31(49), 3 bytes
# altitude MSB, altitude CSB, altitude LSB
data = bus.read_i2c_block_data(0x76, 0x31, 3)

# Convert the data to 20-bits
altitude = (((data[0] & 0x0F) * 65536) + (data[1] * 256) + data[2]) / 100.00

# Output data to screen
print "Altitude : %.2f m" %altitude
print "Pressure : %.2f Pa" %pressure
print "Temperature in Celsius : %.2f C" %cTemp
print "Temperature in Fahrenheit : %.2f F" %fTemp
