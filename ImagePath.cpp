#include <windows.h>
#include <iostream>
#include <string>

const wchar_t SERVICES_PATH[] = L"SYSTEM\\CurrentControlSet\\Services";

void GetServiceImagePath(HKEY hKey, const std::wstring& serviceName) {
    HKEY hSubKey;
    std::wstring fullPath = std::wstring(SERVICES_PATH) + L"\\" + serviceName;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, fullPath.c_str(), 0, KEY_READ, &hSubKey) == ERROR_SUCCESS) {
        wchar_t imagePath[MAX_PATH] = {0};
        DWORD size = sizeof(imagePath);
        if (RegQueryValueExW(hSubKey, L"ImagePath", NULL, NULL, (LPBYTE)imagePath, &size) == ERROR_SUCCESS) {
            std::wcout << L"--------------------------------------------------\n";
            std::wcout << L"Subcheie:    " << serviceName << L"\n";
            std::wcout << L"ImagePath:   " << imagePath << L"\n";
            std::wcout << L"--------------------------------------------------\n";
        }
        RegCloseKey(hSubKey);
    }
}

void EnumerateServices() {
    HKEY hKey;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, SERVICES_PATH, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        DWORD index = 0;
        wchar_t serviceName[MAX_PATH];
        DWORD nameSize = MAX_PATH;
        while (RegEnumKeyExW(hKey, index, serviceName, &nameSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
            GetServiceImagePath(hKey, serviceName);
            nameSize = MAX_PATH;
            index++;
        }
        RegCloseKey(hKey);
    } else {
        std::cerr << "Failed to open registry key!" << std::endl;
    }
}

int main() {
    EnumerateServices();
    return 0;
}
