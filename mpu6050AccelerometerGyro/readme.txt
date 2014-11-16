Good overview

http://playground.arduino.cc/Main/MPU-6050

Introduction

The InvenSense MPU-6050 sensor contains a MEMS accelerometer and a MEMS gyro in a single chip. It is very accurate, as it contains 16-bits analog to digital conversion hardware for each channel. Therefor it captures the x, y, and z channel at the same time. The sensor uses the I2C-bus to interface with the Arduino.

The MPU-6050 is not expensive, especially given the fact that it combines both an accelerometer and a gyro.


Photo: GY-521 breakout board

Also note that Invensense has combined the MPU-6050 with a magnetometer (compass) in a single chip called MPU-9150.

Reading raw values is easy, the rest is not

Reading the raw values for the accelerometer and gyro is easy. The sleep mode has to be disabled, and then the registers for the accelerometer and gyro can be read.

But the sensor also contains a 1024 byte FIFO buffer. The sensor values can be programmed to be placed in the FIFO buffer. And the buffer can be read by the Arduino.

The FIFO buffer is used together with the interrupt signal. If the MPU-6050 places data in the FIFO buffer, it signals the Arduino with the interrupt signal so the Arduino knows that there is data in the FIFO buffer waiting to be read.
A little more complicated is the ability to control a second I2C-device.
The MPU-6050 always acts as a slave to the Arduino with the SDA and SCL pins connected to the I2C-bus.
But beside the normal I2C-bus, it has it's own I2C controller to be a master on a second (sub)-I2C-bus. It uses the pins AUX_DA and AUX_CL for that second (sub)-I2C-bus.
It can control, for example, a magnetometer. The values of the magnetometer can be passed on to the Arduino.

Things get really complex with the "DMP".
The sensor has a "Digital Motion Processor" (DMP), also called a "Digital Motion Processing Unit". This DMP can be programmed with firmware and is able to do complex calculations with the sensor values.
For this DMP, InvenSense has a discouragement policy, by not supplying enough information how to program the DMP. However, some have used reverse engineering to capture firmware.

The DMP ("Digital Motion Processor") can do fast calculations directy on the chip. This reduces the load for the microcontroller (like the Arduino). The DMP is even able to do calculations with the sensor values of another chip, for example a magnetometer connected to the second (sub)-I2C-bus.

Code

The accelerometer and gyro values are called the "raw" values. This is just as with other accelerometer and gyro sensors. A more sophisticated application is using the DMP to retrieve specific computed values from the sensor.

The Short example sketch on this page is a very short sketch that shows all the raw values. Click "Get code" at right, below the sketch, and copy it into a sketch.

The Example sketch (base code) on this page is also just showing the raw values, but it is an attempt to be a complete base for more functions.

For serious use of the MPU-6050, Jeff Rowberg has done an excellent job.
See his I2C lib: http://www.i2cdevlib.com/devices/mpu6050
Or the latest code on github: https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050

The FreeIMU library includes the MPU-6050 code from Jeff Rowberg.
The FreeIMU library: http://www.varesano.net/projects/hardware/FreeIMU

To start with the MPU-6050, see the page of InvenSense: http://www.invensense.com/mems/gyro/mpu6050.html

For other programs and sensors, see the Degrees Of Freedom, 6DOF, 9DOF, 10DOF, 11DOF-section in the Playground index.

Multiple sensors

The pin "AD0" selects between I2C address 0x68 and 0x69. That makes it possible to have two of these sensors in a project. Most breakout boards have a pullup or pulldown resistor to make AD0 default low or high. Connect AD0 to GND or 3.3V for the other I2C address.

When more MPU-6050 sensors are needed in a project, the I2C-bus can be extended with multiplexers. However, someone in the forum mentioned a nice trick:

Trick
Using more than two MPU-6050 sensors can be achieved by connecting each of the AD0 pins to a seperate output of the Arduino. If the number of pins is a problem, then a shift register or a port expander can be used.

The output of a 5V Arduino can not be used. In that case a voltage divider or level shifter for 3.3 volts on each of the outputs is needed. The 5V output pins can also be converted in 3.3V open collector outputs by using transistors or an open-collector driver. Pullup resistors to 3.3V should be added for a high level of 3.3V.
Suppose all AD0 lines are default high (3.3V), so every MPU-6050 is I2C address 0x69. That I2C address is however never used ! The Arduino makes one of the AD0 lines low, and uses that sensor at I2C address 0x68. After that is finished, the Arduino selects another AD0 line, and can use that sensor.
So every sensor is used at I2C address 0x68 (one by one) and 0x69 is never used.

This should make it possible to have many MPU-6050 sensors in a project. Even more than 10 sensor should be possible.
Note that requesting data from many MPU-6050 sensors is slow, because the I2C-bus is slow. A sensor with SPI interface is faster.

At this moment (15 July 2014) it is not known if this trick works for the MPU-6050.
