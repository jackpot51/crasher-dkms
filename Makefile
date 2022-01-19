name := crasher
obj-m := $(name).o
KERNEL_DIR = /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C "$(KERNEL_DIR)" M="$(PWD)" modules

clean:
	$(MAKE) -C "$(KERNEL_DIR)" M="$(PWD)" clean

insert: all
	sudo insmod $(name).ko

remove:
	sudo rmmod -f $(name)
