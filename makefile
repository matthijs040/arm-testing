CC=arm-none-eabi-gcc 
CC_FLAGS=-Wall -Wpedantic -Werror -std=gnu17 -Os -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -fsingle-precision-constant --specs=picolibc.specs  # --specs=nosys.specs # ARM-specific flags  
CC_IN_FILES=main.c
CC_OUT_FILE=main.bin
CC_DEFINES=
UL=st-flash

CC_LINK_SRC+=
CC_LINK_SRC+=

CLEAN_COMMAND:=rm -rf

upload: $(CC_OUT_FILE)
	$(UL) write $(CC_OUT_FILE) 0x8000000

$(CC_OUT_FILE) compile: $(CC_IN_FILES)
	$(CC)$(CC_FLAGS) $(CC_INCLUDES) $(CC_LINK_SRC) $(CC_IN_FILES) -o $(CC_OUT_FILE)

clean: $(CC_OUT_FILE)
	$(CLEAN_COMMAND) $(CC_OUT_FILE) 



