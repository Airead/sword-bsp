# search path
VPATH := $(subst /, , $(shell ls -d */))

# Generic code
find_files = $(wildcard $(dir)/*.[c])
dirs := $(subst :, , $(VPATH))

SRC_OBJS_PRE := $(foreach dir,$(dirs),$(find_files))
SRC_OBJS := $(patsubst %.c, %.o, $(SRC_OBJS_PRE))
SRC_OBJS := $(patsubst %.S, %.o, $(SRC_OBJS))
SRC_OBJS_DEPEND := $(notdir $(SRC_OBJS))

find_elf = $(wildcard $(dir)/*.elf)
find_bin = $(wildcard $(dir)/*.bin)
find_map = $(wildcard $(dir)/*.map)
find_~ =  $(wildcard $(dir)/*~)
find_obj =  $(wildcard $(dir)/*.o)
ELFANDBIN := $(foreach dir,$(dirs),$(find_elf))
ELFANDBIN += $(foreach dir,$(dirs),$(find_bin))
ELFANDBIN += $(foreach dir,$(dirs),$(find_map))
ELFANDBIN += $(foreach dir,$(dirs),$(find_~))
ELFANDBIN += $(foreach dir,$(dirs),$(find_obj))

.PHONY: clean, cleanall

clean:
	@echo Cleaning...
	@echo Files:
	rm -rf $(PROJ).elf $(PROJ).bin *.o *~ *.map \
	$(BOOT_LAYOUT_OUT) $(SRC_OBJS) *.files *.out

cleanall:
	make clean
	make cleanall -C src
	rm -f $(ELFANDBIN)
