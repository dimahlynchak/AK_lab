ifneq ($(KERNELRELEASE),)
# kbuild part
obj-m := hello1.o hello2.o

ccflags-y := -I$(src)/inc
else
# normal makefile
KDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
endif

