# CC = clang
obj-m += solidmodule.o
KDIR = /usr/src/linux-headers-${shell uname -r}
all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	rm -rf *.o *.ko *.sysvers *.order *.symvers *.mod.c
