# Makefile for compiling USB Device Info project
# Supports both Windows and macOS

# Compiler
CXX = g++

# Source files
SRCS = main.cpp

# Output file
TARGET = list_usb

# Define defaults for empty variables, these are filled based on OS
CXXFLAGS =
LIBS =

# Platform check for Windows and macOS
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
    # macOS-specific compilation
    SRCS += USBDeviceInfo_Mac.cpp
    CXXFLAGS += -framework IOKit -framework CoreFoundation
    # Corrected path to IOKit header files
    CXXFLAGS += -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/IOKit.framework/Headers 
else ifeq ($(UNAME_S), Linux)
    # Linux-specific compilation
    SRCS += USBDeviceInfo_Linux.cpp
    CXXFLAGS += -lrt
else ifeq ($(UNAME_S), Windows_NT)
    # Windows-specific compilation (assuming MinGW or similar)
    SRCS += USBDeviceInfo_Windows.cpp
    CXXFLAGS += -static-libgcc -static-libstdc++ -static
    LIBS += -lsetupapi
endif

# Debug flag
ifeq ($(DEBUG), 1)
    CXXFLAGS += -g -Wall -Wextra -Werror
endif

# Verbose flag
ifeq ($(VERBOSE), 1)
    CXXFLAGS += -v
endif

# Default rule for building the project
all: $(TARGET)

# Rule for building the executable program
$(TARGET): $(SRCS)
	$(CXX) -o $(TARGET) $(SRCS) $(LIBS) $(CXXFLAGS)

# Rule for cleaning up
clean:
	rm -f $(TARGET) *.o