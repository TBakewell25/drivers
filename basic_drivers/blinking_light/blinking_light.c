/*********************************************************
*  I'm writing this driver to practice interfacing with  *
*  "custom hardware", which in this case is an LED.      *
*  The LED will be plugged directly into the 5V src pin  *
*  of the USB. This driver will write that pin high and  *
*  low.							 *
**********************************************************/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL"); //define license
MODULE_AUTHOR("Thomas Bakewell"); //define my name
MODULE_DESCRIPTION("This driver will blink a light through usb");
MODULE_VERSION("0.1"); //driver version

/*********************************************************
*  The init function of this driver is at least going    *
*  to need to register a major number, and select gpio   *
*  pins. Honestly, I'm not quite sure what is necessary  *
*  yet. Stay tuned.					 *
**********************************************************/

static int __init init_led_blink(void);

/********************************************************
*  The exit function will need to clean up the init     *
*  function. This entails unregistering the major number*
*  and likely some other stuff defined in the init.     *
*********************************************************/

static void __exit exit_led_blink(void);

module_init(init_led_blink); //init driver
module_exit(exit_led_blink); //clean driver
