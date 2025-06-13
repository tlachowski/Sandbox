#pragma once
#include "ISettingsReader.h"
#include <windows.h>
#include <string>

class WindowsRegistrySettingsReader {
public:
    explicit WindowsRegistrySettingsReader(const std::wstring& subKeyPath)
        : registryPath(subKeyPath) {
    }

    std::string GetSetting(const std::wstring& valueName) const {
        HKEY hKey;
        std::wstring fullPath = L"Software\\" + registryPath;

        if (RegOpenKeyExW(HKEY_CURRENT_USER, fullPath.c_str(), 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
            return "";
        }

        wchar_t buffer[256];
        DWORD bufferSize = sizeof(buffer);
        DWORD type = 0;

        if (RegQueryValueExW(hKey, valueName.c_str(), nullptr, &type, reinterpret_cast<LPBYTE>(&buffer), &bufferSize) != ERROR_SUCCESS) {
            RegCloseKey(hKey);
            return "";
        }

        RegCloseKey(hKey);

        std::wstring wvalue(buffer);

        if (type == REG_SZ) {
            return std::string(wvalue.begin(), wvalue.end());
        }

        return "";
    }

private:
    std::wstring registryPath;
};

