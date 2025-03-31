#include <windows.h>
#include <setupapi.h>
#include <initguid.h>
#include <usbiodef.h>
#include <iostream>

#pragma comment(lib, "setupapi.lib")

void ListUSBDevices() {
    HDEVINFO deviceInfoSet;
    SP_DEVINFO_DATA deviceInfoData;
    DWORD index = 0;
    TCHAR deviceName[256];

    
    deviceInfoSet = SetupDiGetClassDevs(&GUID_DEVINTERFACE_USB_DEVICE, nullptr, nullptr, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
    if (deviceInfoSet == INVALID_HANDLE_VALUE) {
        std::cerr << "Eroare la obținerea listei de dispozitive USB.\n";
        return;
    }

    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    while (SetupDiEnumDeviceInfo(deviceInfoSet, index, &deviceInfoData)) {
        index++;

        
        if (SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData, SPDRP_DEVICEDESC, nullptr,
            (PBYTE)deviceName, sizeof(deviceName), nullptr)) {
            std::wcout << L"Dispozitiv USB: " << deviceName << std::endl;
        }
    }

    SetupDiDestroyDeviceInfoList(deviceInfoSet);
}

int main() {
    std::cout << "Lista dispozitivelor USB conectate:\n";
    ListUSBDevices();
    return 0;
}