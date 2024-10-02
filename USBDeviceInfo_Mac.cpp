#ifdef __APPLE__
// macOS-specifika bibliotek
#include "USBDeviceInfo.h"
#include <IOKit/IOKitLib.h>
#include <IOKit/usb/IOUSBLib.h>
#include <CoreFoundation/CoreFoundation.h>

USBDeviceInfo::USBDeviceInfo() {}

USBDeviceInfo::~USBDeviceInfo() {}

void USBDeviceInfo::listUSBDevices() {
    listUSBDevicesMac();
}

void USBDeviceInfo::listUSBDevicesMac() {
    // macOS-specifik kod för att lista USB-enheter
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "USB Devices (macOS):" << std::endl;
    
    CFMutableDictionaryRef matchingDict = IOServiceMatching(kIOUSBDeviceClassName); // Matcha USB-enheter
    io_iterator_t iterator;

    kern_return_t result = IOServiceGetMatchingServices(kIOMainPortDefault, matchingDict, &iterator);
    if (result != KERN_SUCCESS) {
        std::cerr << "Failed to get USB devices" << std::endl;
        return;
    }

    io_object_t usbDevice;
    while ((usbDevice = IOIteratorNext(iterator))) {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Device: " << getPropertyString(usbDevice, CFSTR("kUSBProductString")) << std::endl;
        std::cout << "Vendor: " << getPropertyString(usbDevice, CFSTR("kUSBVendorString")) << std::endl;
        std::cout << "Serial Number: " << getPropertyString(usbDevice, CFSTR("kUSBSerialNumberString")) << std::endl;
        std::cout << "USB Version: " << getPropertyString(usbDevice, CFSTR("kUSBDeviceReleaseNumber")) << std::endl;
        std::cout << "Speed: " << getPropertyString(usbDevice, CFSTR("kUSBDeviceSpeed")) << std::endl;
        std::cout << "Location ID: " << getPropertyString(usbDevice, CFSTR("kUSBDeviceLocationID")) << std::endl;
        std::cout << "Class: " << getPropertyString(usbDevice, CFSTR("kUSBDeviceClass")) << std::endl;
        std::cout << "Sub Class: " << getPropertyString(usbDevice, CFSTR("kUSBDeviceSubClass")) << std::endl;
        std::cout << "Protocol: " << getPropertyString(usbDevice, CFSTR("kUSBDeviceProtocol")) << std::endl;
        std::cout << "Config Index: " << getPropertyString(usbDevice, CFSTR("kUSBDeviceConfigIndex")) << std::endl;
        std::cout << "Interface Count: " << getPropertyString(usbDevice, CFSTR("kUSBDeviceInterfaceCount")) << std::endl;
        std::cout << "Current Config: " << getPropertyString(usbDevice, CFSTR("kUSBDeviceCurrentConfig")) << std::endl;
        std::cout << "Current Alternate Setting: " << getPropertyString(usbDevice, CFSTR("kUSBDeviceCurrentAlternateSetting")) << std::endl;

        IOObjectRelease(usbDevice);
    }

    IOObjectRelease(iterator);
}

std::string USBDeviceInfo::getPropertyString(io_object_t device, CFStringRef property) {
    CFTypeRef propertyValue = IORegistryEntryCreateCFProperty(device, property, kCFAllocatorDefault, 0);
    if (propertyValue) {
        if (CFGetTypeID(propertyValue) == CFStringGetTypeID()) {
            char buffer[256];
            CFStringGetCString((CFStringRef)propertyValue, buffer, sizeof(buffer), kCFStringEncodingUTF8);
            CFRelease(propertyValue);
            return std::string(buffer);
        }
        CFRelease(propertyValue);
    }
    return "Unknown";
}

#endif // __APPLE__/*

