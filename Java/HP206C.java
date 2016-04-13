// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// HP206C
// This code is designed to work with the HP206C_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Analog-Digital-Converters?sku=HP206C_I2CS#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class HP206C
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus Bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, HP206C I2C address is 0x76(118)
		I2CDevice device = Bus.getDevice(0x76);
		
		// Send OSR and channel setting command
		device.write((byte)(0x44 | 0x00));
		Thread.sleep(500);
		
		// Read 6 bytes of data
		// temp msb, temp csb, temp lsb, pressure msb, pressure csb, pressure lsb
		byte[] data = new byte[6];
		device.read(0x10, data, 0, 6);
		
		// Convert the data to 20-bits
		double cTemp = (((data[0] & 0x0F) * 65536) + ((data[1] & 0xFF) * 256) + (data[2] & 0xFF)) / 100.0;
		double fTemp = (cTemp * 1.8) + 32;
		double pressure = (((data[3] & 0x0F) * 65536) + ((data[4] & 0xFF) * 256) + (data[5] & 0xFF)) / 100.0;
		
		// Send OSR and channel setting command
		device.write((byte)(0x44 | 0x01));
		
		// Read 3 bytes of data
		// altitude msb, altitude csb, altitude lsb
		byte[] data = new byte[3];
		device.read(0x31, data1, 0, 3);
		
		// Convert the data to 20-bits
		double altitude = (((data[0] & 0x0F) * 65536) + ((data[1] & 0xFF)* 256) + (data[2] & 0xFF)) / 100.0;
		
		// Output data to screen
		System.out.printf("Altitude: %.2f meters %n", altitude);
		System.out.printf("Pressue: %.2f Pa %n", pressure);
		System.out.printf("Temperature in Celsius : %.2f C %n", cTemp);
		System.out.printf("Temperature in Fahrenheit : %.2f F %n", fTemp);
		
	}
}
