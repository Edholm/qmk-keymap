KEYMAP_CWD    := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
KEYMAP_NAME   := "bobby"
KEYBOARD_NAME := "kinesis/kint41"
KEYBOARD_MCU  := "TEENSY41"

all: compile flash

compile:
	qmk compile --clean --keymap $(KEYMAP_NAME) --keyboard $(KEYBOARD_NAME)

flash:
	teensy_loader_cli -w -v --mcu=$(KEYBOARD_MCU) $(KEYMAP_CWD)/../../../../.build/kinesis_kint41_$(KEYMAP_NAME).hex

qmk-flash: 
	qmk --verbose flash --keymap $(KEYMAP_NAME) --keyboard $(KEYBOARD_NAME)
