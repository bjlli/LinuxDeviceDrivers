obj-m += 7segment.o
all : module dt

dt: overlay.dts
	dtc -@ -I dts -O dtb -o overlay.dtbo overlay.dts	

module:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -rf overlay.dtbo
