

.PHONY: clean

clean:
	@echo Cleaning...
	@echo Files:
	rm -rf $(PROJ).elf $(PROJ).bin *.o *~ *.map \
	$(BOOT_LAYOUT_OUT) $(SRC_OBJS) *.files *.out
