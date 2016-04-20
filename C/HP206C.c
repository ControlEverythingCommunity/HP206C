// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// HP206C
// This code is designed to work with the HP206C_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Analog-Digital-Converters?sku=HP206C_I2CS#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main() 
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if ((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, HP206C I2C address is 0x76(118)
	ioctl(file, I2C_SLAVE, 0x76);

	// Send OSR and channel setting command(0x44 | 0x00)
	char config[1] = {0x44 | 0x00};
	write(file, config, 1);
	sleep(1);

	// Read 6 bytes of data from register(0x10)
	// temp msb, temp csb, temp lsb, pressure msb, pressure csb, pressure lsb
	char reg[1] = {0x10};
	write(file, reg, 1);
	char data[6] ={0};
	if(read(file, data, 6) != 6)
	{
		printf("Erorr : Input/output Erorr \n");
	}
	else 
	{
		// Convert the data to 20-bits
		float cTemp = (((data[0] & 0x0F) * 65536) + ((data[1] * 256) + data[2])) / 100.0;
		float fTemp = (cTemp * 1.8) + 32;
		float pressure = (((data[3] & 0x0F) * 65536) + (data[4] * 256 + data[5])) / 100.0;

		// Output data to screen
		printf("Pressue: %.2f Pa \n", pressure);
		printf("Temperature in Celsius : %.2f C \n", cTemp);
		printf("Temperature in Fahrenheit : %.2f F \n", fTemp);
	}

	// Send OSR and channel setting command(0x44 | 0x01)
	config[0] = 0x44 | 0x01;
	write(file, config, 1);
	sleep(1);

	// Read 3 bytes of data from register(0x31)
	// altitude msb, altitude csb, altitude lsb
	reg[0] = 0x31;
	write(file, reg, 1);
	if(read(file, data, 3) != 3)
	{
		printf("Erorr : Input/output Erorr \n");
	}
	else 
	{
		// Convert the data to 20-bits
		float altitude = (((data[0] & 0x0F) * 65536) + (data[1] * 256+ data[2])) / 100.0;

		// Output data to screen
		printf("Altitude: %.2f meters \n", altitude);
	}
}
