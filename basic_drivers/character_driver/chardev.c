#include <linux/init.h>
#include <linux/printk.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/string.h>

#define DEVICE_NAME "CharDev"
#define MIN_MAJOR_NUM 0
#define BUFF_LEN 100

static int majnum; 
static int status = 0;

MODULE_LICENSE("GPL"); //define license
MODULE_AUTHOR("Thomas Bakewell"); //define my name
MODULE_DESCRIPTION("A basic character driver");
MODULE_VERSION("0.1"); //driver version

static int __init chardev_init(void);
static void __exit chardev_exit(void);

static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file* fil, char __user *, size_t, loff_t *);
static ssize_t dev_write(char *, size_t, loff_t *);

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = dev_read,
	//.write = dev_write,
	//.open = dev_open,
	//.release = dev_release
};

static int __init chardev_init(void) {
	if (majnum = register_chrdev(MIN_MAJOR_NUM, DEVICE_NAME, &fops) < 0){
		printk(KERN_INFO "ERROR: NO MAJOR NUMBER AVAILABLE");
		return -1;
	}
	return 0;
}

static void __exit chardev_exit(void) {
	unregister_chrdev(majnum, DEVICE_NAME);
	return;
}

static ssize_t dev_read(struct file* fil, char __user *buff, size_t siz, loff_t *offs){
	char* data;
	int try_copy, read_bytes;
	
	data = "hello userspace!";

	if (siz < strnlen(data, 30))
		return -EFAULT;

	if (*offs + siz > strnlen(data, 30))
		return 0;

	if (try_copy = copy_to_user(buff, data, siz) > 0)
		read_bytes = siz - try_copy;

	else
		read_bytes = siz;	

	*offs += siz;	
	return read_bytes;
}



module_init(chardev_init); //init driver
module_exit(chardev_exit); //clean driver
