CPPCOMP=g++

STD_CPPCOMP_FLAGS=-std=c++17 -Wall -pedantic -g
CPPCOMP_FLAGS=$(STD_CPPCOMP_FLAGS)
CPPLINK_FLAGS=-Wall

STD_LIBS=-lm
OPENCV_LIBS=-lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio

OPENCV_INCLUDE=-I/usr/include/opencv4
INCLUDE=$(OPENCV_INCLUDE)

SRC_DIR=./src
BLD_DIR=./bld
BIN_DIR=./bin

# Adds BLD_DIR to object parameter names.
OBJS=$(patsubst %.o,$(BLD_DIR)/%.o,$@.o)

MKDIR=mkdir -p
RM=rm -rf

all: create opencv

# Builds binaries.
opencv: create
	@printf "\n"
	$(CPPCOMP) $(CPPCOMP_FLAGS) -c $(SRC_DIR)/$@.cpp -o $(BLD_DIR)/$@.o $(INCLUDE)
	$(CPPCOMP) $(CPPLINK_FLAGS) $(OBJS) -o $(BIN_DIR)/$@ $(STD_LIBS) $(OPENCV_LIBS) $(BEHEMA_LIBS)
	@printf "\nCreated $@!\n"


# Creates temporary working directories.
create:
	$(MKDIR) $(BLD_DIR)
	$(MKDIR) $(BIN_DIR)

# Removes temporary working directories.
clean:
	$(RM) $(BLD_DIR)
	$(RM) $(BIN_DIR)
