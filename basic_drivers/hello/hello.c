/***********************************************************
*   This is my third attempt at getting this driver on git *
*   I swear I know how to use git, and I swear I know how  *
*   to write a basic LKM like this, I've just had some     *
*   trouble. This file was produced by Claude.ai, and      *
*   annotated by me to proce I know what I'm doing.        *
************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL"); //define license
MODULE_AUTHOR("Thomas Bakewell"); //define my name
MODULE_DESCRIPTION("My third attempt at getting a basic driver on git");
MODULE_VERSION("1,0");

/****************************************************************
*   Throughout this file function prototypes are used to better *
*   adhere to the linux standard. Although not necessary in such*
*   a small driver, I did it because it's good practice. 	*
*   								*
*   The following function prototype declare the init function, *
*   which marks the entry point for the driver, just as main()  *
*   might for a standard .c file. It accepts no arguments,	*
*   initializes the necessary data (none in this case), 	*
*   and returns 0 for success, or non 0 for failure (by 	*
*   convention)							*
*****************************************************************/

static int __init hello_init(void);

//can also be defined as static int hello_init(void) __init;

/****************************************************************
*   Just as the previous function defines an entry point, 	*
*   the following function defines an exit pont.		*
*								*
*   Again, it accepts no arguments, and this time returns	*
*   nothing. The exit function should clean up variables defined*
*   by the __init function in reverse order.			*
*****************************************************************/

static void __exit hello_exit(void);

**********END FUNCTION PROTOTYPES**********

static int __init hello_init(void) {
    printk(KERN_INFO "Hello, Kernel!\n"); //print to kernel log
    return 0;
}

static void __exit hello_exit(void) {
    printk(KERN_INFO "Goodbye, Kernel!\n"); //print to kernel log
}

module_init(hello_init); //init driver
module_exit(hello_exit); //clean driver
