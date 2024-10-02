# USB_device_info
A little tool to read USB info and print it to console

Tested on Windows 10 64bit, OSX 13.6.7

The tool prints all the USB devices in the Console.

Compiled used MinGW on windows
(winlibs-x86_64-posix-seh-gcc-14.2.0-llvm-18.1.8-mingw-w64ucrt-12.0.0-r1)

Please share any improvements :)

# Idea behind the project
It started with the simple idea that I wanted to read as much information about the USB capabuilities in the machine.

# Limitations
There is a huge difference what readable using this method. The tool discover each interface but information on chip level is not that comprehensive.

# output (windows)

Device: USB\ROOT_HUB30\xxxxxxxxxxxxxxxx
Description: USB Root Hub (USB 3.0)
Model: Unknown
IDs: USB\ROOT_HUB30\xxxxxxxxxxx
Make: (USB-standardhub)
Driver: {xxxxxxxxxxxxxxxxxxxxxxxxxxxx}\0002
Driver Version: {xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx}\0002
Driver Location: {xxxxxxxxxxxxxxxxxxxxxxxxxxx}\0002
Speed: Unknown Speed
WCID:
Serial Number: USB\ROOT_HUB30&VIDxxxxxxxxxxxxxxxxxxxxxxxxx
Port Name (FTDI): \Device\USBPDO-1
USB Version: Unknown USB Version

