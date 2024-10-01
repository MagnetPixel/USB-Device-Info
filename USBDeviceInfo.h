#ifndef USBDEVICEINFO_H
#define USBDEVICEINFO_H

#include <windows.h>
#include <setupapi.h>
#include <string>
#include <iostream>

class USBDeviceInfo {
public:
    // Konstruktorn
    USBDeviceInfo();
    // Destruktorn
    ~USBDeviceInfo();

    // Funktion för att hämta och visa alla USB-enheter
    void listUSBDevices();

private:
    // Hjälpfunktioner för att få specifik information om en enhet
    std::string getDeviceProperty(HDEVINFO deviceInfoSet, SP_DEVINFO_DATA& deviceInfoData, DWORD property);
    std::string getDriverInfo(HDEVINFO deviceInfoSet, SP_DEVINFO_DATA& deviceInfoData);
    std::string getDriverVersion(HDEVINFO deviceInfoSet, SP_DEVINFO_DATA& deviceInfoData);
    std::string getDriverLocation(HDEVINFO deviceInfoSet, SP_DEVINFO_DATA& deviceInfoData);
    std::string getDeviceSpeed(HDEVINFO deviceInfoSet, SP_DEVINFO_DATA& deviceInfoData);
};

#endif // USBDEVICEINFO_H
