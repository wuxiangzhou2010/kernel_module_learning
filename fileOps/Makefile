# CC = clang
obj-m += solidmodule.o
KDIR = /usr/src/linux-headers-4.8.0-39-generic
all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	rm -rf *.o *.ko *.sysvers *.order