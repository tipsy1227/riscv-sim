#
# Compiler configurations and target environment definitions
#

SHELL := /bin/bash
CROSS_COMPILE      ?= riscv64-unknown-elf-
CC                 = $(CROSS_COMPILE)gcc
AR                 = $(CROSS_COMPILE)ar
DB                 = $(CROSS_COMPILE)gdb
CFLAGS             = -O0 -Wall -march=rv32im -mabi=ilp32 $(incds) \
                     -mcmodel=medany -ffunction-sections -fdata-sections 
LDFLAGS            = -nolibc -nostdlib -nostdinc -static \
                     -Wl,--nmagic -Wl,--gc-sections

# directories
module_dir         = modules
lib_dir            = env/lib
build_dir          = build
arch_dir            = env/arch

#
# tools
#
rsearch            = $(shell find $2 -iname $1)

ifdef V
cmd = @mkdir -p `dirname $1` ; echo "$2"; $2
else
cmd = @echo "$1"; mkdir -p `dirname $1` ; $2
endif

# libraries and modules
modules            = $(sort $(foreach d,$(shell ls -d $(module_dir)/*/ 2>/dev/null),$(shell basename $(d))))
libs               = $(sort $(foreach d,$(shell ls -d $(lib_dir)/*/ 2>/dev/null),$(shell basename $(d))))
incds          = $(sort -I$(arch_dir)/include $(foreach l,$(libs),-I$(lib_dir)/$(l)/include))
arch_setups         = $(wildcard $(arch_dir)/*.c) $(wildcard $(arch_dir)/*.s)

# prerequesites for archives and executables
define obj_list
$(1) = $(sort $(patsubst %.c,%.o,$(call rsearch,*.c,$(2))) \
  $(patsubst %.s,%.o,$(call rsearch,*.s,$(2))))
endef
$(foreach l,$(libs),$(eval $(call obj_list,lib_$(l)_objs,$(lib_dir)/$(l))))
$(foreach m,$(modules),$(eval $(call obj_list,module_$(m)_objs,$(module_dir)/$(m))))
arch_objs = $(sort $(patsubst %.c,%.o,$(patsubst %.s,%.o,$(arch_setups))))

#
# make rules
#

.SUFFIXES:
.PHONY: all clean clean-all list list-all run gdb

all: $(addprefix $(module_dir)/,$(modules))

clean:
	rm -rf $(build_dir)/bin $(build_dir)/obj/$(module_dir)

clean-all:
	rm -rf $(build_dir)

list:
	@echo $(modules)

list-all:
	@echo "modules:";
	@echo $(modules);
	@echo "libraries:";
	@echo $(libs);

run:
	@if [ "$(target)" == "" ]; then \
		echo "Usage: make run target=module"; \
	else \
		qemu-system-riscv32 -nographic -M virt -bios none -kernel $(build_dir)/bin/$(target); \
	fi

gdb:
	@if [ "$(target)" == "" ]; then \
		echo "Usage: make gdb target=module"; \
	else \
		qemu-system-riscv32 -nographic -M virt -bios none -s -S -kernel $(build_dir)/bin/$(target) & \
		$(DB); \
	fi

define obj_rule
$(build_dir)/obj/%.o: %.$(1)
	$(call cmd,$$@,$(CC) $(CFLAGS) \
	  -c $$^ -o $$@)
endef

define arch_rule
$(build_dir)/obj/$(lib_dir)/$(1).a: $$(addprefix $(build_dir)/obj/,$$(lib_$(1)_objs))
	$(call cmd,$$@,$(AR) cr $$@ $$^)
endef

define exec_rule
$(build_dir)/bin/$(1): $(addprefix $(build_dir)/obj/,$(arch_objs)) \
  $(addprefix $(build_dir)/obj/,$(module_$(1)_objs)) $(foreach l,$(libs),$(build_dir)/obj/$(lib_dir)/$(l).a) 
	$$(call cmd,$$@,$(CC) $(CFLAGS)  \
	$$(LDFLAGS) -T env/default.lds $$^ /usr/local/Cellar/riscv-gnu-toolchain/master/lib/gcc/riscv64-unknown-elf/11.1.0/rv32im/ilp32/libgcc.a -o $$@)
endef

# rule for object files
$(eval $(call obj_rule,c))
$(eval $(call obj_rule,s))

# rule for archives
$(foreach l,$(libs),$(eval $(call arch_rule,$(l))))

# rule for executables
$(foreach m,$(modules),$(eval $(call exec_rule,$(m))))

define phony_obj
$(1): $(build_dir)/obj/$(1)
endef

define phony_exec
$(1): $(build_dir)/bin/$(shell basename $(1))
endef

# create phony target
$(foreach o,$(arch_objs),$(eval $(call phony_obj,$(o))))
$(foreach m,$(modules),$(foreach o,$(module_$(m)_objs),$(eval $(call phony_obj,$(o)))))
$(foreach l,$(libs),$(foreach o,$(lib_$(l)_objs),$(eval $(call phony_obj,$(o)))))
$(foreach l,$(libs),$(eval $(call phony_obj,$(lib_dir)/$(l).a)))
$(foreach m,$(modules),$(eval $(call phony_exec,$(module_dir)/$(m))))

