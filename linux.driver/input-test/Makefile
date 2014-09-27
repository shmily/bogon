
obj-m := input-test.o

KERNEL_DIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	make -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

clean:
	@rm -rf *.o *.ko *.mod.c *.cmd
	@rm -rf Module.symvers
	@rm -rf *.order
	@rm -rf .tmp_versions
	@echo "+++ clean... +++"

.PHONY: clean
