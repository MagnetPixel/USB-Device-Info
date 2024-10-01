# Makefile for compiling USB Device Info project
#Command: 
#g++ -o list_usb USBDeviceInfo.cpp main.cpp -lsetupapi -static-libgcc -static-libstdc++ -static
#
# Kompilator
CXX = g++

# Kompilatorflaggor
CXXFLAGS = -static-libgcc -static-libstdc++ -static

# Bibliotek att länka mot
LIBS = -lsetupapi

# Källkodsfiler
SRCS = USBDeviceInfo.cpp main.cpp

# Output-fil
TARGET = list_usb

# Standardregel för att bygga projektet
all: $(TARGET)

# Regel för att bygga det körbara programmet
$(TARGET): $(SRCS)
	$(CXX) -o $(TARGET) $(SRCS) $(LIBS) $(CXXFLAGS)

# Regel för att städa upp
clean:
	rm -f $(TARGET) *.o
