#  greenpois0n - Makefile
#  (c) 2010 Chronic-Dev Team
#

ifneq ($(DEVICE),)
-include bundles/$(DEVICE)/device.mk
endif

devices ?= $(patsubst bundles/%/,%,$(wildcard bundles/*/))
OUTPUT_DIR = bin/$(DEVICE)/$(FIRMWARE)
firmwares ?= $(patsubst bundles/$(DEVICE)/%/,%,$(wildcard bundles/$(DEVICE)/*/))
targets ?= $(patsubst bundles/$(DEVICE)/$(FIRMWARE)/%/,%,$(wildcard bundles/$(DEVICE)/$(FIRMWARE)/*/))
INPUT_FILES = $(wildcard src/*.S)
INPUT_FILES += $(wildcard src/*.c)
OBJ_FILES = $(patsubst src/%,bin/$(DEVICE)/$(FIRMWARE)/objects/$(TARGET)_%.o,$(INPUT_FILES))

ARM_PREFIX ?= arm-elf-
ARM_CC := $(ARM_PREFIX)gcc
ARM_AS := $(ARM_PREFIX)as
ARM_LD := $(ARM_PREFIX)ld
ARM_OBJCOPY := $(ARM_PREFIX)objcopy
SELF = $(shell echo "$(TARGET)" | tr a-z A-Z)
TARGET_CFLAGS = -I./includes -I./includes/hardware -I./bundles/$(DEVICE) -I./bundles/$(DEVICE)/$(FIRMWARE) -I./bundles/$(DEVICE)/$(FIRMWARE)/$(TARGET) -D$(SELF) -fPIC -mthumb-interwork -ffixed-r12 -nostdlib
TARGET_LDFLAGS = -lc -lgcc

all:
	@for i in $(devices); do $(MAKE) $(MAKEFLAG) _device DEVICE="$$i"; done

clean:
	@rm -rf bin

.PHONY: _device _firmware _target Makefile
.SUFFIXES:
.SUFFIXES: .c .S

_device::
	@for i in $(firmwares); do $(MAKE) $(PRINT_DIR_FLAG) --no-keep-going _firmware DEVICE="$(DEVICE)" FIRMWARE="$$i" || exit 1; done
_firmware::
	@for i in $(targets); do echo Building $(DEVICE) $(FIRMWARE) $$i...; $(MAKE) $(PRINT_DIR_FLAG) --no-keep-going _target DEVICE="$(DEVICE)" FIRMWARE="$(FIRMWARE)" TARGET="$$i" || exit 1; done
_target:: $(OUTPUT_DIR) $(OUTPUT_DIR)/$(TARGET)

ifneq ($(TARGET),)
$(OUTPUT_DIR):
	@mkdir -p $@
	@mkdir -p $@/objects

$(OUTPUT_DIR)/objects/$(TARGET)_%.S.o: src/%.S
	$(ECHO_COMPILING)$(ARM_CC) $(TARGET_CFLAGS) $(CFLAGS) -c -o $@ $<$(ECHO_END)
$(OUTPUT_DIR)/objects/$(TARGET)_%.c.o: src/%.c
	$(ECHO_COMPILING)$(ARM_CC) $(TARGET_CFLAGS) $(CFLAGS) -c -o $@ $<$(ECHO_END)

$(OUTPUT_DIR)/objects/$(TARGET).elf: $(OBJ_FILES)
	$(ECHO_LINKING)$(ARM_CC) $(TARGET_CFLAGS) $(TARGET_LDFLAGS) $(LDFLAGS) -o $@ -Ttext=$(TARGET_ADDRESS) $^$(ECHO_END)

$(OUTPUT_DIR)/$(TARGET): $(OUTPUT_DIR)/objects/$(TARGET).elf
	$(ECHO_NOTHING)$(ARM_OBJCOPY) -O binary $< $@$(ECHO_END)
endif


ifneq ($(messages),yes)
ECHO_COMPILING=@(echo "  Compiling $@...";
ECHO_LINKING=@(echo "  Linking $@...";
ECHO_NOTHING=@(
ECHO_END=)
PRINT_DIR_FLAG=--no-print-directory
else
ECHO_COMPILING=
ECHO_LINKING=
ECHO_NOTHING=
ECHO_END=
PRINT_DIR_FLAG=
endif
