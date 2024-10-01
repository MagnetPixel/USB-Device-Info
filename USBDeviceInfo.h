#ifndef USBDEVICEINFO_H
#define USBDEVICEINFO_H


#include <string>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <setupapi.h>
#endif

#ifdef __APPLE__
#include <IOKit/IOKitLib.h>
#include <CoreFoundation/CoreFoundation.h>
#endif

class USBDeviceInfo {
public:
    // Construktor
    USBDeviceInfo();
    // Destruktor
    ~USBDeviceInfo();

    // function to get all USB devices
    void listUSBDevices();

private:
    #ifdef _WIN32
    // Helpfunctions
    std::string getDeviceProperty(HDEVINFO deviceInfoSet, SP_DEVINFO_DATA& deviceInfoData, DWORD property);
    std::string getDriverInfo(HDEVINFO deviceInfoSet, SP_DEVINFO_DATA& deviceInfoData);
    std::string getDriverVersion(HDEVINFO deviceInfoSet, SP_DEVINFO_DATA& deviceInfoData);
    std::string getDriverLocation(HDEVINFO deviceInfoSet, SP_DEVINFO_DATA& deviceInfoData);
    std::string getDeviceSpeed(HDEVINFO deviceInfoSet, SP_DEVINFO_DATA& deviceInfoData);
    std::string getUSBVersion(HDEVINFO deviceInfoSet, SP_DEVINFO_DATA& deviceInfoData);
    #endif

    #ifdef __APPLE__
    // macOS-specific
    void listUSBDevicesMac();
    void printUSBDeviceInfo(io_object_t usbDevice);
    std::string getPropertyString(io_object_t device, CFStringRef property);
    #endif
};

#endif // USBDEVICEINFO_H
