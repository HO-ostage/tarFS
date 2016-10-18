KERN = $(shell uname -r)
KDIR = /lib/modules/$(KERN)/build
PWD = $(shell pwd)
TARGET = tarfs

obj-m := $(TARGET).o

SRC_DIR = src

$(TARGET)-objs := $(SRC_DIR)/super.o

CFLAGS_super.o := -DDEBUG

all: default

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	@rm -f $(SRC_DIR)/*.o $(SRC_DIR)/.*.cmd

clean:
	@rm -f *.o .*.cmd .*.flags *.mod.c *.order
	@rm -f .*.*.cmd *~ *.*~ TODO.*
	@rm -fR .tmp*
	@rm -rf .tmp_versions

disclean: clean
	@rm *.ko *.symvers *.ko.*
