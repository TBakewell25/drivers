/************************************************************************************
*  This is a basic character driver. It will implement four file operations: read,  *
*  write, open, and release. It also registers its own major and minor number,	    *
*  and later releases it.							    *
*************************************************************************************/

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

/*
*  The init function of this driver will only need
*  to do one thing: register a new chardev, and by
*  extension assign it a major number.
*/
static int __init chardev_init(void);

/*
*  The exit function only needs to clean up the 
*  assignment of a major number from the init.
*/

static void __exit chardev_exit(void);

static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);

/*
*  This function provides a means to "read" from a
*  nonexistent device. It takes 4 arguments, but
*  only uses 3, as I don't care about preserving 
*  state between calls.
*  
*  @ARGS
*	struct file* - unused
*	char __user * - a buffer from userspace
*	size_t - the size in bytes to read
*	loff_t - the offset in bytes to read from
*
*  @RETURN
*	returns bytes read upon succes, error upon failure
*/

static ssize_t dev_read(struct file*, char __user *, size_t, loff_t *);

/*
*  This function provides a means to "write" to a 
*  nonexistent device, which will then print to the
*  kernel log. Just as with write it doesn't preserve
*  state.
*
*  @ARGS
*	struct file* - unused
*	char * - data to write
*	size_t - amount to write in bytes
*	loff_t - offset into data
*
*  @RETURN
*	returns bytes writted upon success, error upon failutre
*/

static ssize_t dev_write(struct file*, char *, size_t, loff_t *);

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = dev_read,
	.write = dev_write,
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

static ssize_t dev_read(struct file* filp, char __user *buff, size_t size, loff_t *offs){
	char *data;
	int data_len, try_copy, read_bytes;
	
	data = "hello userspace!";
	data_len = strnlen(data, 30);

	if (!buff)
		return -EINVAL;

	if (*offs + size > data_len)
		size = data_len - *offs;

	if ((try_copy = copy_to_user(buff, data, size)) > 0)
		read_bytes = size - try_copy;

	else
		read_bytes = size;	

	*offs += size;	
	return read_bytes;
}

static ssize_t dev_write(struct file* filp, char * buff, size_t size, loff_t *offs){
	char data[64];
	int try_copy, written_bytes;
	
	if (!buff)
		return -EINVAL;	

	if (*offs >= sizeof(data))
		return -EFAULT;

	if (*offs + size > sizeof(data) -1)
		size = sizeof(data) -1 - *offs;

	if ((try_copy = copy_from_user(data, buff, size)) > 0)
		written_bytes = size - try_copy;

	else
		written_bytes = size;

	*offs += size;
	data[*offs] ' '\0';
	return written_bytes;
}

module_init(chardev_init); //init driver
module_exit(chardev_exit); //clean driver
