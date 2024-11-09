/*********************************************************
*  I'm writing this driver to practice interfacing with  *
*  "custom hardware", which in this case is an LED.      *
*  The LED will be plugged directly into the 5V src pin  *
*  of the USB. This driver will write that pin high and  *
*  low. This driver will be heavily based on skeleton    *
*  code from kernel.org					 *
**********************************************************/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h> //find gpio info
#include <linux/fs.h> //handle major number
#include <linux/usb.h> //duh

MODULE_LICENSE("GPL"); //define license
MODULE_AUTHOR("Thomas Bakewell"); //define my name
MODULE_DESCRIPTION("This driver will blink a light through usb");
MODULE_VERSION("0.1"); //driver version

/*
*  Defining a struct that allows us to pass data
*  to the USB subsystem in order to register the device
*/

static struct usb_driver blink_driver = {
        //device name
	.name        = "blinky", 
	//probe function
        .probe       = blink_probe, 
	//disconnect function
        .disconnect  = blink_disconnect,
	//list of file ops
	.fops = &blink_ops,
	//minor num
        .minor       = USB_BLINK_MINOR_BASE, 
	//if the device matches the data in
	//this table, register it
        .id_table    = BLINK_table, 
				   
};

/*********************************************************
*  The init function of this driver is at least going    *
*  to need to register a major number (180), and select  * 
*  gpio pins. Honestly, I'm not quite sure what is	 * 
*  necessary yet. Stay tuned.				 *
**********************************************************/

static int __init init_led_blink(void);

/********************************************************
*  The exit function will need to clean up the init     *
*  function. This entails unregistering the major number*
*  and likely some other stuff defined in the init.     *
*********************************************************/

static void __exit exit_led_blink(void);

static int __init init_led_blink(void){
	int result;

	//register with usb subsystem
	result = usb_register(&blink_driver);
	if (result < 0){
		err("usb_register failted for the "__FILE__ "driver."
			"Error number %d", result);
		return -1;
	}
	return 0;
}

static void __exit exit_led_blink(void){
	//deregister from the USB subsystem
	usb_deregister(&blink_driver);
	
module_init(init_led_blink); //init driver
module_exit(exit_led_blink); //clean driver
