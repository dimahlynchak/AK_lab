obj-m := hello_lab6.o

KDIR := /home/dimahlynchak/repos/linux-stable
PWD := $(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) ARCH=arm CROSS_COMPILE=ccache\ arm-linux-gnueabihf- modules

clean:
	make -C $(KDIR) M=$(PWD) clean

