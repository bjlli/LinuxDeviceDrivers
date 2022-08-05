#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>
#include <linux/fs.h>
#include <linux/slab.h>

/***************Global variables*****************/
static struct class *device_class = NULL;
volatile int value_display; 
volatile int enable_dp;
/***************Global Structs******************/
static const struct file_operations fops = {
	.owner = THIS_MODULE,
};



/***************Module Functions****************/
static int segmentsDisplay_init(void)
{
    int ret;
    static struct lock_class_key key; 
    printk(KERN_ALERT "7 segmente display module init!");

    /*Creating a class in /sys/class*/    
    device_class = (struct class *)kzalloc(sizeof(struct class),GFP_ATOMIC);;       if(!device_class){
    	printk("Class allocation error!");
    }
    printk("Teste");
    device_class->name = "segments_display";
    device_class->owner = THIS_MODULE;
    ret = __class_register(device_class,&key);

    

    return 0;

}

static void segmentsDisplay_exit(void)
{
    
    class_unregister(device_class);
    class_destroy(device_class);
    printk(KERN_ALERT "7 segment display module exit!");


}


MODULE_LICENSE("GPL");
module_init(segmentsDisplay_init);
module_exit(segmentsDisplay_exit);
