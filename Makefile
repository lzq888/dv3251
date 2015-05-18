.PHONY: clean All

All:
	@echo "----------Building project:[ AX325X - Debug ]----------"
	@$(MAKE) -f  "AX325X.mk" && $(MAKE) -f  "AX325X.mk" PostBuild
clean:
	@echo "----------Cleaning project:[ AX325X - Debug ]----------"
	@$(MAKE) -f  "AX325X.mk" clean
