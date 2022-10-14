#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/of_device.h>
#include <linux/gpio/consumer.h>
#include <linux/platform_device.h>


/********Show/Store functions declaration********/
static ssize_t show_value( struct class *class, struct class_attribute *attr, char *buf ); 
static ssize_t show_enableDP( struct class *class, struct class_attribute *attr, char *buf );
static ssize_t store_value( struct class *class, struct class_attribute *attr, const char *buf, size_t count );
static ssize_t store_enableDP( struct class *class, struct class_attribute *attr, const char *buf, size_t count);
/******Device Tree Functions declaration********/
static int gpio_init_probe(struct platform_device *pdev);
static int gpio_exit_remove(struct platform_device *pdev);
/***************Global variables*****************/
static struct class *device_class = NULL;
struct class_attribute *attr_value = NULL;
struct class_attribute *attr_enableDP = NULL;
struct gpio_desc *a, *b, *c, *d;
struct gpio_desc *e, *f, *g, *dp;
volatile int value_display; 
volatile int enable_dp;
int type;
/***************Global Structs******************/

static struct of_device_id driver_ids[] = {
    {.compatible = "emc-logic,7segment"},
    {/* end node */}
};

static struct platform_driver display_driver = {
    .probe = gpio_init_probe,
    .remove = gpio_exit_remove,
    .driver = {
        .name = "display_driver",
                .owner = THIS_MODULE,
                .of_match_table = driver_ids,
    }
};


/********Show/Store functions definition*********/

static ssize_t show_value( struct class *class, struct class_attribute *attr, char *buf ){
    printk("Display value - READ!");
    return sprintf(buf, "%d", value_display); 
}

static ssize_t store_value( struct class *class, struct class_attribute *attr, const char *buf, size_t count ){
    printk("Display value - WRITE!");
    sscanf(buf,"%d",&value_display);
    switch(value_display){
    	case 0:
    		gpiod_set_value(a, 1);
		gpiod_set_value(b, 1);
		gpiod_set_value(c, 1);
		gpiod_set_value(d, 1);
	        gpiod_set_value(e, 1);
		gpiod_set_value(f, 1);
		gpiod_set_value(g, 0);
		break; 

    	case 1:
    		gpiod_set_value(a, 0);
		gpiod_set_value(b, 1);
		gpiod_set_value(c, 1);
		gpiod_set_value(d, 0);
	        gpiod_set_value(e, 0);
		gpiod_set_value(f, 0);
		gpiod_set_value(g, 0);
		break;

	case 2:
		gpiod_set_value(a, 1);
		gpiod_set_value(b, 1);
		gpiod_set_value(c, 0);
		gpiod_set_value(d, 1);
	        gpiod_set_value(e, 1);
		gpiod_set_value(f, 0);
		gpiod_set_value(g, 1);
		break;

	case 3:
		gpiod_set_value(a, 1);
		gpiod_set_value(b, 1);
		gpiod_set_value(c, 1);
		gpiod_set_value(d, 1);
	        gpiod_set_value(e, 0);
		gpiod_set_value(f, 0);
		gpiod_set_value(g, 1);
		break;

	case 4:
    		gpiod_set_value(a, 0);
		gpiod_set_value(b, 1);
		gpiod_set_value(c, 1);
		gpiod_set_value(d, 0);
	        gpiod_set_value(e, 0);
		gpiod_set_value(f, 1);
		gpiod_set_value(g, 1);
		break;

    	case 5:
    		gpiod_set_value(a, 1);
		gpiod_set_value(b, 0);
		gpiod_set_value(c, 1);
		gpiod_set_value(d, 1);
	        gpiod_set_value(e, 0);
		gpiod_set_value(f, 1);
		gpiod_set_value(g, 1);
		break;

    	case 6:
    		gpiod_set_value(a, 1);
		gpiod_set_value(b, 0);
		gpiod_set_value(c, 1);
		gpiod_set_value(d, 1);
	        gpiod_set_value(e, 1);
		gpiod_set_value(f, 1);
		gpiod_set_value(g, 1);
		break; 

    	case 7:
    		gpiod_set_value(a, 1);
		gpiod_set_value(b, 1);
		gpiod_set_value(c, 1);
		gpiod_set_value(d, 0);
	        gpiod_set_value(e, 0);
		gpiod_set_value(f, 0);
		gpiod_set_value(g, 0);
		break; 

    	case 8:
    		gpiod_set_value(a, 1);
		gpiod_set_value(b, 1);
		gpiod_set_value(c, 1);
		gpiod_set_value(d, 1);
	        gpiod_set_value(e, 1);
		gpiod_set_value(f, 1);
		gpiod_set_value(g, 1);
		break; 
	
    	case 9:
    		gpiod_set_value(a, 1);
		gpiod_set_value(b, 1);
		gpiod_set_value(c, 1);
		gpiod_set_value(d, 0);
	        gpiod_set_value(e, 0);
		gpiod_set_value(f, 1);
		gpiod_set_value(g, 1);
		break;

       default:	
		printk("Not able to write this number!");
		gpiod_set_value(a, 1);
		gpiod_set_value(b, 0);
		gpiod_set_value(c, 0);
		gpiod_set_value(d, 1);
	        gpiod_set_value(e, 1);
		gpiod_set_value(f, 1);
		gpiod_set_value(g, 1);

		break;
    } 
    return count;
}

static ssize_t show_enableDP( struct class *class, struct class_attribute *attr, char *buf ){
    printk("Enable DP - READ!");
    return sprintf(buf, "%d", enable_dp); 
}

static ssize_t store_enableDP( struct class *class, struct class_attribute *attr, const char *buf, size_t count ){
    
    sscanf(buf, "%d", &enable_dp);
    if(enable_dp<2){
	printk("Enable DP - WRITE!");
	gpiod_set_value(dp,enable_dp);
    }else{
    	printk("You shouldn't write a number higher than 1!");
    } 
    return count;
}

/********Probe/Remove functions definition*********/

static int gpio_init_probe(struct platform_device *pdev){
    int ret;
    printk("GPIO PROBE!");
    a = devm_gpiod_get(&pdev->dev, "a", GPIOD_OUT_LOW);
    b = devm_gpiod_get(&pdev->dev, "b", GPIOD_OUT_LOW);
    c = devm_gpiod_get(&pdev->dev, "c", GPIOD_OUT_LOW);
    d = devm_gpiod_get(&pdev->dev, "d", GPIOD_OUT_LOW);
    e = devm_gpiod_get(&pdev->dev, "e", GPIOD_OUT_LOW);
    f = devm_gpiod_get(&pdev->dev, "f", GPIOD_OUT_LOW);
    g = devm_gpiod_get(&pdev->dev, "g", GPIOD_OUT_LOW);
    dp = devm_gpiod_get(&pdev->dev, "dp", GPIOD_OUT_LOW);
    ret = device_property_read_u32(&pdev->dev,"type",&type);
    return 0;

}

static int gpio_exit_remove(struct platform_device *pdev){
    printk("GPIO REMOVE!");
    return 0;

}

/***************Module Functions****************/

MODULE_LICENSE("GPL");

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
    device_class->name = "7segment";
    device_class->owner = THIS_MODULE;
    ret = __class_register(device_class,&key);

    /*Creating the file /sys/class/7segment/value*/
    attr_value = (struct class_attribute *)kzalloc(sizeof(struct class_attribute ),GFP_ATOMIC); 
    attr_value->show = show_value;
    attr_value->store = store_value;
    attr_value->attr.name = "value";
    attr_value->attr.mode = 0777 ;
    ret = class_create_file(device_class, attr_value);

    /*Creating the file /sys/class/7segment/enableDP*/
    attr_enableDP = (struct class_attribute *)kzalloc(sizeof(struct class_attribute ),GFP_ATOMIC); 
    attr_enableDP->show = show_enableDP;
    attr_enableDP->store = store_enableDP;
    attr_enableDP->attr.name = "enableDP";
    attr_enableDP->attr.mode = 0777 ;
    ret = class_create_file(device_class, attr_enableDP);

    /*Loading the GPIO's via device tree*/
    if(platform_driver_register(&display_driver)) {
	printk("Error! Could not load the 7 segments display driver\n");
	return -1;
	}


    return 0;

}

static void segmentsDisplay_exit(void)
{
    /*Destroying the class in /sys/class*/
    class_unregister(device_class);
    class_destroy(device_class);
    /*Destroying the files in /sys/class*/
    kfree(attr_value);
    kfree(attr_enableDP);
    /*Unregister the device tree gpio driver*/
    platform_driver_unregister(&display_driver);

    printk(KERN_ALERT "7 segment display module exit!");
}


module_init(segmentsDisplay_init);
module_exit(segmentsDisplay_exit);
