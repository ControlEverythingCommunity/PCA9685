# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# PCA9685
# This code is designed to work with the PCA9685_I2CPWM8W16I12V I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/FET-Drivers?sku=PCA9685_I2CPWM8W16I12V#tabs-0-product_tabset-2

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# PCA9685 I2C address, 0x40(64)
# Select MODE2 register, 0x01(01)
#		0x04(04)	All pin's outputs are configured with a totem pole structure.
bus.write_byte_data(0x40, 0x01, 0x04)
# PCA9685 I2C address, 0x40(64)
# Select MODE1 register, 0x00(00)
#		0x01(01)	Response to LED all-call I2C address
bus.write_byte_data(0x40, 0x00, 0x01)
time.sleep(0.005)

# PCA9685 I2C address, 0x40(64)
# Read 1 byte of data from address 0x00(00)
mode = bus.read_byte_data(0x40, 0x00)

# PCA9685 I2C address, 0x40(64)
# Select MODE1 register, 0x00(00)
#		0x10(16)	sleep mode
bus.write_byte_data(0x40, 0x00, 0x10)
# PCA9685 I2C address, 0x40(64)
# Select PRE_SCALE register, 0xFE(254)
#		0x65(101)	Set prescale frequency to 101
bus.write_byte_data(0x40, 0xFE, 0x65)

# PCA9685 I2C address, 0x40(64)
# Select MODE1 register, 0x00(00)
#		0x01(01)	Response to LED all-call I2C address
bus.write_byte_data(0x40, 0x00, mode)
time.sleep(0.005)

# PCA9685 I2C address, 0x40(64)
# Select MODE1 register, 0x00(00)
#		Restart Enabled
bus.write_byte_data(0x40, 0x00, mode | 0x80)

# Config data for led start
# data = 0x0000(00)
LED_START = [0x00, 0x00]

# Config data for led stop
# data = 0x0258(600)
LED_STOP = [0x58, 0x02]

print "Enter CTRL + c to quit "
# Blink all the LEDS with 50% duty cycle
while True :
	for i in range(0, 4096, 3):
		# PCA9685 I2C address, 0x40(64)
		# Select ALL_LED_ON_L register, 0xFA(250)
		bus.write_byte_data(0x40, 0xFA, 0x00)
		# PCA9685 I2C address, 0x40(64)
		# Select ALL_LED_ON_H register, 0xFB(251)
		bus.write_byte_data(0x40, 0xFB, 0x00)
		# PCA9685 I2C address, 0x40(64)
		# Select ALL_LED_OFF_L register, 0xFC(252)
		bus.write_byte_data(0x40, 0xFC, (i & 0xFF))
		# PCA9685 I2C address, 0x40(64)
		# Select ALL_LED_OFF_H register, 0xFD(253)
		bus.write_byte_data(0x40, 0xFD, (i / 256))
		time.sleep(0.001)
	time.sleep(2.5)
	
	for i in range(4095, -1, -3):
		# PCA9685 I2C address, 0x40(64)
		# Select ALL_LED_ON_L register, 0xFA(250)
		bus.write_byte_data(0x40, 0xFA, 0x00)
		# PCA9685 I2C address, 0x40(64)
		# Select ALL_LED_ON_H register, 0xFB(251)
		bus.write_byte_data(0x40, 0xFB, 0x00)
		# PCA9685 I2C address, 0x40(64)
		# Select ALL_LED_OFF_L register, 0xFC(252)
		bus.write_byte_data(0x40, 0xFC, (i & 0xFF))
		# PCA9685 I2C address, 0x40(64)
		# Select ALL_LED_OFF_H register, 0xFD(253)
		bus.write_byte_data(0x40, 0xFD, (i / 256))
		time.sleep(0.001)
	time.sleep(2.5)	