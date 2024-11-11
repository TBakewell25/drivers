#include <linux/init.h>
#include <linux/printk.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

#Define DEVICE_NAME "CharDev"
#Define MIN_MAJOR_NUM 0
#Define BUFF_LEN 100

static int majnum; //let majnum be global
static int status = 0;

MODULE_LICENSE("GPL"); //define license
MODULE_AUTHOR("Thomas Bakewell"); //define my name
MODULE_DESCRIPTION("A basic character driver");
MODULE_VERSION("0.1"); //driver version

struct file_operations fops = {
	.read = dev_read,
	.write = dev_write,
	.open = dev_open,
	.release = dev_release
};

static int __init chardev_init(void);
static void __exit chardev_exit(void);

static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, char *, size_t, loff_t *);


static int __init chardev_init(void) {
	if (majnum = register_chrdev(MIN_MAJOR_NUM, DEVICE_NAME, &fops) < 0){
		printk(KERN_INFO "ERROR: NO MAJOR NUMBER AVAILABLE");
		return -1;
	}
		
	return 0;
}

static void __exit chardev_exit(void) {
	int result;

	if (result = unregister_chrdev(majnum, DEVICE_NAME) < 0){
		printk(KERN_INFO "WARNING: COULD NOT UNREGISTER MAJOR NUMBER");
		return -1;
	}

	return 0;
}

module_init(chardev_init); //init driver
module_exit(chardev_exit); //clean driver
