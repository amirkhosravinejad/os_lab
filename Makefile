KERNELDIR=/lib/modules/$(shell uname -r)/build

#MODULES = birth.ko
obj-m += birth.o

all:
	make -C $(KERNELDIR) M=$(PWD) modules
clean:
	make -C $(KERNELDIR) M=$(PWD) clean