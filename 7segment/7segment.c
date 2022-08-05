#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>
#include <linux/fs.h>
#include <linux/slab.h>

/********Show/Store functions declaration********/
static ssize_t show_value( struct class *class, struct class_attribute *attr, char *buf ); 
static ssize_t show_enableDP( struct class *class, struct class_attribute *attr, char *buf );
static ssize_t store_value( struct class *class, struct class_attribute *attr, const char *buf, size_t count );
static ssize_t store_enableDP( struct class *class, struct class_attribute *attr, const char *buf, size_t count);
/***************Global variables*****************/
static struct class *device_class = NULL;
struct class_attribute *attr_value = NULL;
struct class_attribute *attr_enableDP = NULL;
volatile int value_display; 
volatile int enable_dp;
/***************Global Structs******************/
static const struct file_operations fops = {
	.owner = THIS_MODULE,
};

/********Show/Store functions definition*********/

static ssize_t show_value( struct class *class, struct class_attribute *attr, char *buf ){
    printk("Display value - READ!");
    return sprintf(buf, "%d", value_display); 
}

static ssize_t store_value( struct class *class, struct class_attribute *attr, const char *buf, size_t count ){
    printk("Display value - WRITE!");
    sscanf(buf,"%d",&value_display); 
    return count;
}

static ssize_t show_enableDP( struct class *class, struct class_attribute *attr, char *buf ){
    printk("Enable DP - READ!");
    return sprintf(buf, "%d", enable_dp); 
}

static ssize_t store_enableDP( struct class *class, struct class_attribute *attr, const char *buf, size_t count ){
    printk("Enable DP - WRITE!");
    sscanf(buf,"%d",&enable_dp); 
    return count;
}

/***************Module Functions****************/
static int segmentsDisplay_init(void)
{
    int ret;
    static struct lock_class_key key; 
    printk(KERN_ALERT "7 segmente display module init!");

    /*Creating a class in /sys/class*/    
    device_class = (struct class *)kzalloc(sizeof(struct class),GFP_ATOMIC);       
    if(!device_class){
    	printk("Class allocation error!");
    }
    printk("Teste");
    device_class->name = "7segment";
    device_class->owner = THIS_MODULE;
    ret = __class_register(device_class,&key);

    /*Creating the file /sys/class/7segment/value*/
    attr_value = (struct class_attribute *)kzalloc(sizeof(struct class_attribute ),GFP_ATOMIC); 
    attr_value->show = show_value;
    attr_value->store = store_value;
    attr_value->attr.name = "value";
    attr_value->attr.mode = 0664 ;
    ret = class_create_file(device_class, attr_value);

    /*Creating the file /sys/class/7segment/enableDP*/
    attr_enableDP = (struct class_attribute *)kzalloc(sizeof(struct class_attribute ),GFP_ATOMIC); 
    attr_enableDP->show = show_enableDP;
    attr_enableDP->store = store_enableDP;
    attr_enableDP->attr.name = "enableDP";
    attr_enableDP->attr.mode = 0664 ;
    ret = class_create_file(device_class, attr_enableDP);

    return 0;

}

static void segmentsDisplay_exit(void)
{
    /*Destroying the class in /sys/class*/
    class_unregister(device_class);
    class_destroy(device_class);

    printk(KERN_ALERT "7 segment display module exit!");


}


MODULE_LICENSE("GPL");
module_init(segmentsDisplay_init);
module_exit(segmentsDisplay_exit);
