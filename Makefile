CPPCOMP=g++

STD_CPPCOMP_FLAGS=-std=c++17 -Wall -pedantic -g
CPPCOMP_FLAGS=$(STD_CCOMP_FLAGS)
CPPLINK_FLAGS=-Wall -fopenmp

STD_LIBS=-lm

SRC_DIR=./src
BLD_DIR=./bld
BIN_DIR=./bin

SYSTEM_INCLUDE_DIR=
SYSTEM_LIB_DIR=

# Adds BLD_DIR to object parameter names.
OBJS=$(patsubst %.o,$(BLD_DIR)/%.o,$^)

MKDIR=mkdir -p
RM=rm -rf

# Check what the current operating system is.
UNAME_S=$(shell uname -s)

# The curren OS is Linux.
ifeq ($(UNAME_S),Linux)
	SYSTEM_INCLUDE_DIR=/usr/include
	SYSTEM_LIB_DIR=/usr/lib
endif

# The current OS is MacOS.
ifeq ($(UNAME_S),Darwin)
	SYSTEM_INCLUDE_DIR=/usr/local/include
	SYSTEM_LIB_DIR=/usr/local/lib
endif

all: create build

# Builds binaries.
build: create
	@printf "\n"
	$(CPPCOMP) $(CPPCOMP_FLAGS) -c $(SRC_DIR)/$@.c -o $(BLD_DIR)/$@.o
	$(CPPCOMP) $(CPPLINK_FLAGS) $(OBJS) -o $(BIN_DIR)/$@ $(STD_LIBS) $(BEHEMA_LIBS)
	@printf "\nCreated $@!\n"

# Builds object files from source.
%.o: $(SRC_DIR)/%.c
	$(CPPCOMP) $(CPPCOMP_FLAGS) -c $^ -o $(BLD_DIR)/$@


# Creates temporary working directories.
create:
	$(MKDIR) $(BLD_DIR)
	$(MKDIR) $(BIN_DIR)

# Removes temporary working directories.
clean:
	$(RM) $(BLD_DIR)
	$(RM) $(BIN_DIR)
