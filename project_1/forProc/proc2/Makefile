obj-m := proc2.o
#obj-m := project.o
KERN_DIR := /lib/modules/$(shell uname -r)/build
#KERN_DIR := /lib/modules/$(shell uname -r)/build 
#或者写成
#KERN_DIR := /usr/src/linux-headers-$(shell uname -r)
PWD := $(shell pwd)
#PWD := $(shell pwd)
all:
#module:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules clean
#modules_install目标我目前了解到的是会把生成的.ko文件放到/lib/modules/2.6.31-14-generic/extra/文件夹下
modules_install:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules_install
