#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/gpio.h>
#include <asm/gpio.h>


#define DEVICE_NAME "suzanne_tim_driver"
#define DEVICE_MAJOR  69
#define GPIO_LED_PIN 21


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Character Device");
MODULE_AUTHOR("Suzanne Peerdeman & Tim Visser");

static unsigned long procfs_buffer_size = 0;
static char buffer_data[3];
static char led_status = 0;

static int device_open(struct inode *inode, struct file *file);
static int device_release(struct inode *inode, struct file *file);
static ssize_t device_write(struct file *file, const char *buffer, size_t len, loff_t *offset);

static struct file_operations fops = 
{
  .owner    = THIS_MODULE,
  .open     = device_open,
  .release  = device_release,
  .write    = device_write,
};


int suzanne_tim_init(void) {
	pr_alert("Character Device van Suzanne Peerdeman & Tim Visser\n");
	int ret;
	ret = register_chrdev(DEVICE_MAJOR, DEVICE_NAME, &fops);

	return 0;
}

void suzanne_tim_exit(void) {
	gpio_free(GPIO_LED_PIN);
	unregister_chrdev(DEVICE_MAJOR, DEVICE_NAME);
	pr_alert("Character Device ontkoppeld...\n");
}

static ssize_t device_write(struct file *file, const char *buffer, size_t len, loff_t *offset) {
	procfs_buffer_size = len;
	if (copy_from_user(buffer_data, buffer, procfs_buffer_size)) {
	  return -EFAULT;
	}
	*offset += len;
	if (buffer_data[0] == '1') {
	  led_status = 1;
	}
	if (buffer_data[0] == '0') {
	  led_status = 0;
	}
	pr_info("Received data...");
	pr_info("Data received: %s\n", buffer_data);
	return procfs_buffer_size;
}

static int device_open(struct inode *inode, struct file *file) {
	gpio_set_value(GPIO_LED_PIN, led_status);
	printk(KERN_ALERT "GPIO %d is set HIGH\n", GPIO_LED_PIN);
	return 0;
}

static int device_release(struct inode *inode, struct file *file) {
	gpio_set_value(GPIO_LED_PIN, led_status);
	printk(KERN_ALERT "GPIO %d is set LOW\n", GPIO_LED_PIN);
	return 0;
}

module_init(suzanne_tim_init);
module_exit(suzanne_tim_exit);
