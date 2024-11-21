ifneq ($(KERNELRELEASE),)
# kbuild частина makefile
obj-m := hello.o
EXTRA_CFLAGS += -std=gnu99
else
# Звичайний makefile
KDIR ?= /home/dimahlynchak/repos/linux-stable  # Шлях до каталогу з ARM ядром
ARCH := arm
CROSS_COMPILE := ccache\ arm-linux-gnueabihf-

default:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
endif

