#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>


/***************Global variables*****************/
static struct class *device_class = NULL;
volatile int value_display; 
volatile int enable_dp;




/***************Module Functions****************/
static int __init segmentsDisplay_init(void)
{
    
    printk(KERN_ALERT "7 segment display module init!");

    return 0;

}

static void __exit segmentsDisplay_exit(void)
{
    
    printk(KERN_ALERT "7 segment display module exit!");

}


MODULE_LICENSE("GPL");
module_init(segmentsDisplay_init);
module_exit(segmentsDisplay_exit);
