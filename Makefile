obj-m:=SystemCall.o
CURRENT_PATH:=$(shell pwd)
LINUX_KERNEL_PATH:=/usr/src/linux-headers-5.3.0-46-generic
all:
	make -C  $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:
	make -C  $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean