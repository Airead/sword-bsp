CURRENTDIR	= .

# Linker script
BOOT_LAYOUT_OUT =$(CURRENTDIR)/../swordbsp.lds

CROSS_COMPILE ?= arm-none-eabi-

AS	= $(CROSS_COMPILE)as
CC	= $(CROSS_COMPILE)gcc
LD	= $(CROSS_COMPILE)ld
CPP	= $(CROSS_COMPILE)cpp
STRIP	= $(CROSS_COMPILE)strip
OBJCOPY	= $(CROSS_COMPILE)objcopy
OBJDUMP	= $(CROSS_COMPILE)objdump

# search path
VPATH := $(shell ls -d ../*/ ) #| cut -d '/' -f 2)

# Generic code
find_files = $(wildcard $(dir)*.[cS])
dirs := $(subst :, , $(VPATH))

SRC_OBJS_PRE := $(foreach dir,$(dirs),$(find_files))
SRC_OBJS := $(patsubst %.c, %.o, $(SRC_OBJS_PRE))
SRC_OBJS := $(patsubst %.S, %.o, $(SRC_OBJS))
SRC_OBJS_DEPEND := $(notdir $(SRC_OBJS))


# Project name
PROJ := beeptest

# Project ELF,binary image
PROJ_ELF = $(PROJ).elf
PROJ_BIN = $(PROJ).bin

LIBGCCDIR = 
LDFLAGS = -static -nostdlib -T $(BOOT_LAYOUT_OUT)

# Generic code

.PHONY: test, build_pre, build, clean

build: build_pre $(PROJ_BIN) 

build_pre:
	 make -C $(CURRENTDIR)/..

test:
	@echo SRC_OBJS = $(SRC_OBJS)
	@echo VPATH = $(VPATH)
	@echo dirs = $(dirs)
	@echo SRC_OBJS_PRE = $(SRC_OBJS_PRE)
	@echo SRC_OBJS_DEPEND = $(SRC_OBJS_DEPEND)
clean:
	@echo Cleaning...
	@echo Files:
	rm -rf $(PROJ).elf $(PROJ).bin *.o *~ *.map

# 
# Rules to link and convert project image
# 

$(PROJ_BIN): $(PROJ_ELF)
	$(OBJCOPY) -O binary $< $@

$(PROJ_ELF): $(SRC_OBJS) $(BOOT_LAYOUT_OUT)
	$(LD) -o $@ $(SRC_OBJS) $(LDFLAGS)
	@nm -n $@ > $@.map
