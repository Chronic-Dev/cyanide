#  greenpois0n - Makefile
#  (c) 2010 Chronic-Dev Team
#

ifneq ($(DEVICE),)
-include bundles/$(DEVICE)/device.mk
endif

devices ?= $(patsubst bundles/%/,%,$(wildcard bundles/*/))
OUTPUT_DIR = bin/$(DEVICE)/$(FIRMWARE)/$(PAYLOAD)
firmwares ?= $(patsubst bundles/$(DEVICE)/%/,%,$(wildcard bundles/$(DEVICE)/*/))
payloads ?= $(patsubst bundles/$(DEVICE)/$(FIRMWARE)/%/,%,$(wildcard bundles/$(DEVICE)/$(FIRMWARE)/*/))
INPUT_FILES = $(wildcard src/*.S)
INPUT_FILES += $(wildcard src/*.c)
OBJ_FILES = $(patsubst src/%,bin/$(DEVICE)/$(FIRMWARE)/$(PAYLOAD)/%.o,$(INPUT_FILES))

ARM_PREFIX ?= arm-elf-
ARM_CC := $(ARM_PREFIX)gcc
ARM_AS := $(ARM_PREFIX)as
ARM_LD := $(ARM_PREFIX)ld
ARM_OBJCOPY := $(ARM_PREFIX)objcopy
SELF = $(shell echo "$(PAYLOAD)" | tr a-z A-Z)
PAYLOAD_CFLAGS=-I./includes -I./includes/hardware -Ibundles/$(DEVICE) -Ibundles/$(DEVICE)/$(FIRMWARE) -D$(SELF) -fPIC -mthumb-interwork -ffixed-r12 -nostdlib
PAYLOAD_LDFLAGS=-lc -lgcc

all:
	@for i in $(devices); do $(MAKE) $(MAKEFLAG) _device DEVICE="$$i"; done

clean:
	find bin -iname '*.o' -and -delete -or -iname 'payload*' -and -delete

.PHONY: _device _firmware _payload Makefile
.SUFFIXES:
.SUFFIXES: .c .S

_device::
	@for i in $(firmwares); do $(MAKE) $(PRINT_DIR_FLAG) --no-keep-going _firmware DEVICE="$(DEVICE)" FIRMWARE="$$i" || exit 1; done
_firmware::
	@for i in $(payloads); do echo Building $(DEVICE) $(FIRMWARE) $$i...; $(MAKE) $(PRINT_DIR_FLAG) --no-keep-going _payload DEVICE="$(DEVICE)" FIRMWARE="$(FIRMWARE)" PAYLOAD="$$i" || exit 1; done
_payload:: $(OUTPUT_DIR) $(OUTPUT_DIR)/payload

$(OUTPUT_DIR):
	mkdir -p $@

$(OUTPUT_DIR)/%.S.o: src/%.S
	$(ECHO_COMPILING)$(ARM_CC) $(PAYLOAD_CFLAGS) $(CFLAGS) -c -o $@ $<$(ECHO_END)
$(OUTPUT_DIR)/%.c.o: src/%.c
	$(ECHO_COMPILING)$(ARM_CC) $(PAYLOAD_CFLAGS) $(CFLAGS) -c -o $@ $<$(ECHO_END)

$(OUTPUT_DIR)/payload.elf: $(OBJ_FILES)
	$(ECHO_LINKING)$(ARM_CC) $(PAYLOAD_CFLAGS) $(PAYLOAD_LDFLAGS) $(LDFLAGS) -o $@ -Ttext=$(PAYLOAD_ADDRESS) $^$(ECHO_END)

$(OUTPUT_DIR)/payload: $(OUTPUT_DIR)/payload.elf
	$(ECHO_NOTHING)$(ARM_OBJCOPY) -O binary $< $@$(ECHO_END)


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
