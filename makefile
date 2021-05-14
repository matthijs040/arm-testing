CC=arm-none-eabi-gcc 

FP_FLAGS	?= -mfloat-abi=hard -mfpu=fpv4-sp-d16
ARCH_FLAGS	= -mthumb -mcpu=cortex-m4 $(FP_FLAGS)

CC_FLAGS	=-std=gnu18 -ggdb3 -Os -Wall -Wpedantic -Werror -mcpu=cortex-m4 -mthumb --specs=picolibc.specs 
CC_IN_FILES	=main.c
CC_OUT_FILE	=main.elf
CC_DEFINES	=

UL			=st-flash

CC_LINK_SRC+=
CC_LINK_SRC+=

CLEAN_COMMAND:=rm -rf

upload: $(CC_OUT_FILE)
	$(UL) write $(CC_OUT_FILE) 0x8000000

$(CC_OUT_FILE) compile: $(CC_IN_FILES)
	$(CC)$(CC_FLAGS) $(CC_INCLUDES) $(CC_LINK_SRC) $(CC_IN_FILES) -o $(CC_OUT_FILE)

clean: $(CC_OUT_FILE)
	$(CLEAN_COMMAND) $(CC_OUT_FILE) 



