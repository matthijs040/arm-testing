CC=arm-none-eabi-gcc 
CC_FLAGS=-Wall -std=gnu17 -Os -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -fsingle-precision-constant # ARM-specific flags --specs=nosys.specs
CC_IN_FILES=main.c
CC_OUT_FILE=main.bin
CC_DEFINES=-DSTM32F303xE -DUSE_STDPERIPH_DRIVER -D
UL=st-flash

#dependency-defines:
MAIN_ST_LIB_DIR:=/home/matthijs/code/lib/STM32F30x_DSP_StdPeriph_Lib_V1.2.3/Libraries
CMSIS_LIB=$(MAIN_ST_LIB_DIR)/CMSIS
DEV_DRIVER_LIB=$(MAIN_ST_LIB_DIR)/CMSIS/Device/ST/STM32F30x
MCU_DRIVER_LIB=$(MAIN_ST_LIB_DIR)/STM32F30x_StdPeriph_Driver
# CPAL_DRIVER_LIB=$(MAIN_ST_LIB_DIR)/STM32F30x_I2C_CPAL_Driver

# adding the dependencies:
# CC_INCLUDES+=-I$(shell find $(MAIN_ST_LIB_DIR) -name *.h)
CC_INCLUDES+=-I./
CC_INCLUDES+=-I$(CMSIS_LIB)/Include
CC_INCLUDES+=-I$(DEV_DRIVER_LIB)/Include
CC_INCLUDES+=-I$(MCU_DRIVER_LIB)/inc
# CC_INCLUDES+=-I$(CPAL_DRIVER_LIB)/inc

# CC_LINK_SRC+=-L$(shell find $(MAIN_ST_LIB_DIR) -name *.c)
# CC_LINK_SRC+=-L$(CMSIS_LIB)/Src
CC_LINK_SRC+=$(MCU_DRIVER_LIB)/src/*
# CC_LINK_SRC+=$(CPAL_DRIVER_LIB)/src/*
CC_LINK_SRC+=$(DEV_DRIVER_LIB)/Source/*

upload: $(CC_OUT_FILE)
	$(UL) write $(CC_OUT_FILE) 0x8000000



$(CC_OUT_FILE) compile: $(CC_IN_FILES)
	$(CC)$(CC_FLAGS) $(CC_INCLUDES) $(CC_LINK_SRC) $(CC_IN_FILES) -o $(CC_OUT_FILE)



