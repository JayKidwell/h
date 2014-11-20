Example sketch (base code)

The sketch below is ment to be a base for interfacing the MPU-6050.

The sketch uses the Arduino functions as much as possible. For now, it is just a simple and basic sketch to get the MPU-6050 working.

The I2C-address depends on the AD0 pin of the sensor. If it is connected to ground, the address is 0x68. If it is connected to VLOGIC (+3.3V) it is 0x69. There are a few sensor boards with the MPU-6050 sensor already soldered on it. Some of those boards have a pull-down resistor at AD0 (address = 0x68), others have a pull-up resistor (address = 0x69).

Search in the sketch for "MPU6050_I2C_ADDRESS" and set that to your own I2C address.
A i2c_scanner can be used to check if the device is connected to the i2c bus.
The acceleration and gyro values of the sketch are raw values, which are not yet compensated for offset. The very first acceleration and gyro values after power up are sometimes not valid.

The sketch is about 7kbyte, and will fit in a ATmega8.