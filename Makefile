#	Last Edit: 2020-06-07
#	Author: Elias Mawa

## config
OBJ_NAME = sorbet
LIB_NAME = lib$(OBJ_NAME)

SRC_DIR = src
BUILD_DIR = bin

INCLUDE_DIR = include
LIB_DIR = lib

COMPILER_FLAGS = -Wall
LINKER_FLAGS = -lglfw -llua -lm -ldl

CXX = gcc
CXX_WIN = x86_64-w64-mingw32-gcc

SORBET_INCLUDE = sorbet/include

## targets
SRC = $(wildcard $(SRC_DIR)/*.c)
SRC += $(wildcard $(SRC_DIR)/*/*.c)
SRC += $(wildcard $(SRC_DIR)/*/*/*.c)
SRC += $(wildcard $(SRC_DIR)/*/*/*/*.c)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

## scripts
all : $(OBJS) $(LIB_DIR)/$(LIB_NAME)
	mkdir -p $(LIB_DIR)
	mkdir -p $(INCLUDE_DIR)/$(OBJ_NAME)
	cd src && cp -r ./**/*.h ../$(INCLUDE_DIR)/$(OBJ_NAME) --parents && cd ..
	cd src && cp -r ./**.h ../$(INCLUDE_DIR)/$(OBJ_NAME) --parents && cd ..

## helpers
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CXX) -fPIC -c $? -o $@

$(LIB_DIR)/$(LIB_NAME):
	mkdir -p $(@D)
	ar -rcs $@.a $(OBJS)

## utility
clean :
	rm -rf $(BUILD_DIR) $(LIB_DIR) $(INCLUDE_DIR)