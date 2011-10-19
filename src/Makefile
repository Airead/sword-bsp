CURRENTDIR	= .
#COMPILER_DIR	= /home/airead/armtool/arm-gcc/lib/gcc/arm-none-eabi/4.5.2
INCLUDEDIR	= $(CURRENTDIR)/../include
OBJECTDIR	= $(CURRENTDIR)/objs


# Linker script
BASE_ADDR	?= 0x00000000
BOOT_LAYOUT_IN	= $(CURRENTDIR)/swordbsp.ld.in
BOOT_LAYOUT_OUT =$(CURRENTDIR)/swordbsp.lds

CROSS_COMPILE ?= arm-none-eabi-

AS	= $(CROSS_COMPILE)as
CC	= $(CROSS_COMPILE)gcc
LD	= $(CROSS_COMPILE)ld
CPP	= $(CROSS_COMPILE)cpp
STRIP	= $(CROSS_COMPILE)strip
OBJCOPY	= $(CROSS_COMPILE)objcopy
OBJDUMP	= $(CROSS_COMPILE)objdump

LIBGCCDIR = 
CFLAGS = -Wall -g -nostdinc -I$(INCLUDEDIR)

# 
# Define an implicit rule for assembler files
# to run them through C preprocessor
# 
%.o: %.S
	$(CC) -c $(CFLAGS) -o $(dir $<)$@ $<

%.o: %.c
	$(CC) -c $(CFLAGS) -o $(dir $<)$@ $<

# search path
VPATH := $(subst /, , $(shell ls -d */))

# Generic code
find_files = $(wildcard $(dir)/*.[cS])
dirs := $(subst :, , $(VPATH))

SRC_OBJS_PRE := $(foreach dir,$(dirs),$(find_files))
SRC_OBJS := $(patsubst %.c, %.o, $(SRC_OBJS_PRE))
SRC_OBJS := $(patsubst %.S, %.o, $(SRC_OBJS))
SRC_OBJS := $(filter-out %entry.o, $(SRC_OBJS))
SRC_OBJS_DEPEND := $(notdir $(SRC_OBJS))

find_elf = $(wildcard $(dir)/*.elf)
find_bin = $(wildcard $(dir)/*.bin)
find_map = $(wildcard $(dir)/*.map)
find_~ =  $(wildcard $(dir)/*~)
find_obj =  $(wildcard $(dir)/*.o)
find_files =  $(wildcard $(dir)/*.files)
find_out =  $(wildcard $(dir)/*.out)
ELFANDBIN := $(foreach dir,$(dirs),$(find_elf))
ELFANDBIN += $(foreach dir,$(dirs),$(find_bin))
ELFANDBIN += $(foreach dir,$(dirs),$(find_map))
ELFANDBIN += $(foreach dir,$(dirs),$(find_~))
ELFANDBIN += $(foreach dir,$(dirs),$(find_obj))
ELFANDBIN += $(foreach dir,$(dirs),$(find_files))
ELFANDBIN += $(foreach dir,$(dirs),$(find_out))

.PHONY: test, build_objs, build, clean, cleanall

build_objs: $(SRC_OBJS_DEPEND) $(BOOT_LAYOUT_OUT)

test:
	@echo -----------test---------------
	@echo SRC_OBJS = $(SRC_OBJS)
	@echo BOOT_LAYOUT_IN = $(BOOT_LAYOUT_IN)
	@echo SRC_OBJS_DEPEND = $(SRC_OBJS_DEPEND)
	@echo SRC_OBJS = $(SRC_OBJS)
	@echo find_files = $(find_files)
	@echo search_path = $(search_path)
	@echo VPATH = $(VPATH)
	@echo dirs = $(dirs)
	@echo SRC_OBJS_PRE = $(SRC_OBJS_PRE)
	@echo ELFANDBIN = $(ELFANDBIN)
clean:
	@echo Cleaning...
	@echo Files:
	rm -rf $(PROJ).elf $(PROJ).bin *.o *~ *.map \
	$(BOOT_LAYOUT_OUT) $(SRC_OBJS)
cleanall:
	make clean
	rm -f $(ELFANDBIN)

# 
# Rules to link and convert project image
# 

$(BOOT_LAYOUT_OUT): $(BOOT_LAYOUT_IN)
	$(CPP) -P -DBASE_ADDR=$(BASE_ADDR) -o $@ $<
