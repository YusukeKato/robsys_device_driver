#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <linux/io.h>

MODULE_AUTHOR("Yusuke Kato");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");

#define LED_SIZE 17

static dev_t dev;
static struct cdev cdv;

static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;

static int led_number[LED_SIZE] = {21, 26, 20, 19, 16, 13, 12, 6, 5, 7, 8, 11, 25, 9, 10, 24, 23};

static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos)
{
    int i = 0;
    char c;
    int c_num = 0;
    if(copy_from_user(&c, buf, sizeof(char))) {
        return -EFAULT;
    }

    if(c == '0') {
	for(i = 0; i < LED_SIZE; i++) {
            gpio_base[10] = 1 << led_number[i];
	}
    }

    if(c == '1') gpio_base[7] = 1 << led_number[0];
    if(c == '2') gpio_base[7] = 1 << led_number[1];
    if(c == '3') gpio_base[7] = 1 << led_number[2];
    if(c == '4') gpio_base[7] = 1 << led_number[3];
    if(c == '5') gpio_base[7] = 1 << led_number[4];
    if(c == '6') gpio_base[7] = 1 << led_number[5];
    if(c == '7') gpio_base[7] = 1 << led_number[6];
    if(c == '8') gpio_base[7] = 1 << led_number[7];
    if(c == '9') gpio_base[7] = 1 << led_number[8];
    if(c == 'a') gpio_base[7] = 1 << led_number[9];
    if(c == 'b') gpio_base[7] = 1 << led_number[10];
    if(c == 'c') gpio_base[7] = 1 << led_number[11];
    if(c == 'd') gpio_base[7] = 1 << led_number[12];
    if(c == 'e') gpio_base[7] = 1 << led_number[13];
    if(c == 'f') gpio_base[7] = 1 << led_number[14];
    if(c == 'g') gpio_base[7] = 1 << led_number[15];
    if(c == 'h') gpio_base[7] = 1 << led_number[16];
    printk(KERN_INFO "receive %c\n", c);
    return 1;
}

static struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .write = led_write
};

static int __init init_mod(void)
{
    int i = 0;
    int retval;
    gpio_base = ioremap_nocache(0x3f200000, 0xA0);
    for(i = 0; i < LED_SIZE; i++) {
        const u32 led = led_number[i];
        const u32 index = led/10;
        const u32 shift = (led%10)*3;
        const u32 mask = ~(0x7 << shift);
        gpio_base[index] = (gpio_base[index] & mask) | (0x1 << shift);
    }
    retval = alloc_chrdev_region(&dev, 0, 1, "myled");
    if(retval < 0){
        printk(KERN_ERR "alloc_chrdev_region failed.\n");
        return retval;
    }
    printk(KERN_INFO "%s is loaded.major:%d\n",__FILE__,MAJOR(dev));
    
    cdev_init(&cdv, &led_fops);
    retval = cdev_add(&cdv, dev, 1);
    if(retval < 0) {
        printk(KERN_ERR "cdev_add failed. major:%d, minor:%d",MAJOR(dev),MINOR(dev));
        return retval;
    }
    
    cls = class_create(THIS_MODULE, "myled");
    if(IS_ERR(cls)) {
	printk(KERN_ERR "class_create failed.");
	return PTR_ERR(cls);
    }
    device_create(cls, NULL, dev, NULL, "myled%d", MINOR(dev));
    return 0;
}

static void __exit cleanup_mod(void)
{
    cdev_del(&cdv);
    device_destroy(cls, dev);
    class_destroy(cls);
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "%s is unloaded.\n",__FILE__);
}

module_init(init_mod);
module_exit(cleanup_mod);

