# Makefile for compiling USB Device Info project
# Supports both Windows and macOS

# Compilator
CXX = g++

# Sourcode
SRCS = USBDeviceInfo.cpp main.cpp

# Output-fil
TARGET = list_usb

# Definiera standard för tomma variabler, dessa fylls beroende på OS
CXXFLAGS =
LIBS =

# Plattformskontroll för Windows och macOS
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
    # macOS-specifik kompilering
    CXXFLAGS += -framework IOKit -framework CoreFoundation 
    # Korrigerad sökväg till IOKit-headerfiler
    CXXFLAGS += -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/IOKit.framework/Headers 
else
    # Windows-specifik kompilering (förutsatt MinGW eller liknande)
    CXXFLAGS += -static-libgcc -static-libstdc++ -static
    LIBS += -lsetupapi
endif

# Debug-flagga
ifeq ($(DEBUG), 1)
    CXXFLAGS += -g -Wall -Wextra -Werror
endif

# Verbose-flagga
ifeq ($(VERBOSE), 1)
    CXXFLAGS += -v
endif

# Standardregel för att bygga projektet
all: $(TARGET)

# Regel för att bygga det körbara programmet
$(TARGET): $(SRCS)
	$(CXX) -o $(TARGET) $(SRCS) $(LIBS) $(CXXFLAGS)

# Regel för att städa upp
clean:
	rm -f $(TARGET) *.o