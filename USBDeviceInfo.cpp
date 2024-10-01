#include "USBDeviceInfo.h"
#include <setupapi.h>
#include <initguid.h>
#include <regstr.h>
#include <Cfgmgr32.h>
#include <windows.h>
#include <sstream>

USBDeviceInfo::USBDeviceInfo() {}

USBDeviceInfo::~USBDeviceInfo() {}

void USBDeviceInfo::listUSBDevices() {
    HDEVINFO deviceInfoSet;
    SP_DEVINFO_DATA deviceInfoData;
    DWORD i;

    // Hämta alla enheter som är anslutna och tillgängliga i systemet
    deviceInfoSet = SetupDiGetClassDevs(NULL, 0, 0, DIGCF_PRESENT | DIGCF_ALLCLASSES);
    if (deviceInfoSet == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to get device info set." << std::endl;
        return;
    }

    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    // Iterera igenom alla hittade enheter
    for (i = 0; SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData); i++) {
        // Hämta enhetsinstans-ID
        char deviceInstanceID[256];
        if (SetupDiGetDeviceInstanceIdA(deviceInfoSet, &deviceInfoData, deviceInstanceID, sizeof(deviceInstanceID), NULL)) {
            // Kontrollera om det är en USB-enhet
            if (strstr(deviceInstanceID, "USB")) {
                std::cout << "----------------------------------------" << std::endl;
                std::cout << "Device: " << deviceInstanceID << std::endl;

                // Beskrivning
                std::cout << "Description: " << getDeviceProperty(deviceInfoSet, deviceInfoData, SPDRP_DEVICEDESC) << std::endl;

                // Modell
                std::cout << "Model: " << getDeviceProperty(deviceInfoSet, deviceInfoData, SPDRP_FRIENDLYNAME) << std::endl;

                // IDs
                std::cout << "IDs: " << deviceInstanceID << std::endl;

                // Tillverkare (Make)
                std::cout << "Make: " << getDeviceProperty(deviceInfoSet, deviceInfoData, SPDRP_MFG) << std::endl;

                // Drivrutinsinformation
                std::cout << "Driver: " << getDriverInfo(deviceInfoSet, deviceInfoData) << std::endl;
                std::cout << "Driver Version: " << getDriverVersion(deviceInfoSet, deviceInfoData) << std::endl;
                std::cout << "Driver Location: " << getDriverLocation(deviceInfoSet, deviceInfoData) << std::endl;

                // Enhetens hastighet
                std::cout << "Speed: " << getDeviceSpeed(deviceInfoSet, deviceInfoData) << std::endl;

                // Kompatibla ID:n (WCID)
                std::cout << "WCID: " << getDeviceProperty(deviceInfoSet, deviceInfoData, SPDRP_COMPATIBLEIDS) << std::endl;

                // Serienummer
                std::cout << "Serial Number: " << getDeviceProperty(deviceInfoSet, deviceInfoData, SPDRP_HARDWAREID) << std::endl;

                // FTDI Portnamn (för seriella USB-enheter)
                std::cout << "Port Name (FTDI): " << getDeviceProperty(deviceInfoSet, deviceInfoData, SPDRP_PHYSICAL_DEVICE_OBJECT_NAME) << std::endl;

                // USB Version (placeholder)
                //std::cout << "USB Version: " << getUSBVersion(deviceInfoSet, deviceInfoData) << std::endl;
            }
        }
    }

    // Frigör resurser
    SetupDiDestroyDeviceInfoList(deviceInfoSet);
}

// Hämtar USB-versionen (placeholder, för full implementering kan vi använda IOCTL)
//std::string USBDeviceInfo::getUSBVersion(HDEVINFO deviceInfoSet, SP_DEVINFO_DATA& deviceInfoData) {
    // Placeholder, kan använda DeviceIoControl med IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX_V2
  //  return "Unknown USB Version";
//}

std::string USBDeviceInfo::getDeviceProperty(HDEVINFO deviceInfoSet, SP_DEVINFO_DATA& deviceInfoData, DWORD property) {
    char buffer[256];
    if (SetupDiGetDeviceRegistryPropertyA(deviceInfoSet, &deviceInfoData, property, NULL, (PBYTE)buffer, sizeof(buffer), NULL)) {
        return std::string(buffer);
    }
    return "Unknown";
}

std::string USBDeviceInfo::getDriverInfo(HDEVINFO deviceInfoSet, SP_DEVINFO_DATA& deviceInfoData) {
    char buffer[256];
    if (SetupDiGetDeviceRegistryPropertyA(deviceInfoSet, &deviceInfoData, SPDRP_DRIVER, NULL, (PBYTE)buffer, sizeof(buffer), NULL)) {
        return std::string(buffer);
    }
    return "Unknown";
}

std::string USBDeviceInfo::getDriverVersion(HDEVINFO deviceInfoSet, SP_DEVINFO_DATA& deviceInfoData) {
    char buffer[256];
    if (SetupDiGetDeviceRegistryPropertyA(deviceInfoSet, &deviceInfoData, SPDRP_DRIVER, NULL, (PBYTE)buffer, sizeof(buffer), NULL)) {
        // Här kan vi vidareutveckla för att hämta specifik version om tillgängligt
        return std::string(buffer);
    }
    return "Unknown Version";
}

std::string USBDeviceInfo::getDriverLocation(HDEVINFO deviceInfoSet, SP_DEVINFO_DATA& deviceInfoData) {
    char buffer[256];
    if (SetupDiGetDeviceRegistryPropertyA(deviceInfoSet, &deviceInfoData, SPDRP_DRIVER, NULL, (PBYTE)buffer, sizeof(buffer), NULL)) {
        // Här kan vi hämta sökvägen till drivrutinen om den finns
        return std::string(buffer);
    }
    return "Unknown Location";
}

std::string USBDeviceInfo::getDeviceSpeed(HDEVINFO deviceInfoSet, SP_DEVINFO_DATA& deviceInfoData) {
    // För att få enhetens hastighet måste vi använda specifika anrop som eventuellt är USB-specifika.
    // Detta är en enkel platsinnehavare för vidare utveckling.
    return "Unknown Speed";
}
