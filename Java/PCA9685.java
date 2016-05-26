// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// PCA9685
// This code is designed to work with the PCA9685_I2CPWM8W16I12V I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/FET-Drivers?sku=PCA9685_I2CPWM8W16I12V#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class PCA9685
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, PCA9685 I2C address is 0x40(64)
		I2CDevice device = bus.getDevice(0x40);
		
		// Select MODE2 register
		// All pin's outputs are configured with a totem pole structure
		device.write(0x01, (byte)0x04);
		// Select MODE1 register
		// Response to LED all-call I2C address
		device.write(0x00, (byte)0x01);
		Thread.sleep(5);
		
		// Read 1 byte of data from address 0x00(0)
		byte mode = (byte)device.read(0x00);
		
		// Select MODE1 register
		// Set sleep mode
		device.write(0x00, (byte)0x10);
		// Select PRE_SCALE register
		// Set prescale frequency to 60 Hz
		device.write(0xFE, (byte)0x65);
		
		// Select MODE1 register
		// Response to LED all-call I2C address
		device.write(0x00, (byte)mode);
		Thread.sleep(5);
		// Select MODE1 register
		// Restart
		device.write(0x00, (byte)(mode | 0x80));
		
		// Blink all the LEDS with 50% duty cycle
		System.out.println("Enter CTRL + c to quit ");
		
		while(true)
		{
			// Increase Brightness of ALL LED
			for(int i = 0; i < 4096; i += 3)
			{ 
			   // Select ALL_LED_ON_L register
			   device.write(0xFA, (byte)0x00);
			   // Select ALL_LED_ON_H register
			   device.write(0xFB, (byte)0x00);
			   // Select ALL_LED_OFF_L register
			   device.write(0xFC, (byte)(i & 0xFF));
			   // Select ALL_LED_OFF_H register
			   device.write(0xFD, (byte)(i / 256));
			   Thread.sleep(1);
			}
			Thread.sleep(2500);
   
			// Decrease Brightness of ALL LED
			for(int i = 4095; i >= 0; i -= 3)
			{	 
                // Select ALL_LED_ON_L register
				device.write(0xFA, (byte)0x00);
                // Select ALL_LED_ON_H register
                device.write(0xFB, (byte)0x00);
                // Select ALL_LED_OFF_L register
                device.write(0xFC, (byte)(i & 0xFF));
                // Select ALL_LED_OFF_H register
                device.write(0xFD, (byte)(i / 256));
                Thread.sleep(1);
			}
			Thread.sleep(2500);
		}
	}
}
