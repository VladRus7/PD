#include <windows.h>
#include <iostream>

void PrintImagePath(HKEY hKey, const std::wstring& subKey) {
    HKEY hSubKey;
    if (RegOpenKeyExW(hKey, subKey.c_str(), 0, KEY_QUERY_VALUE, &hSubKey) == ERROR_SUCCESS) {
        wchar_t imagePath[MAX_PATH];
        DWORD size = sizeof(imagePath);
        if (RegQueryValueExW(hSubKey, L"ImagePath", nullptr, nullptr, (LPBYTE)imagePath, &size) == ERROR_SUCCESS) {
            std::wcout << L"[" << subKey << L"] -> " << imagePath << std::endl;
        }
        RegCloseKey(hSubKey);
    }
}

void EnumerateServices() {
    HKEY hKey;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Services", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        wchar_t subKeyName[MAX_PATH];
        DWORD index = 0, subKeySize = MAX_PATH;
        while (RegEnumKeyExW(hKey, index, subKeyName, &subKeySize, nullptr, nullptr, nullptr, nullptr) == ERROR_SUCCESS) {
            PrintImagePath(hKey, subKeyName);
            subKeySize = MAX_PATH;
            ++index;
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
