#pragma once
#include "ISettingsReader.h"
#include <windows.h>
#include <string>
#include <iostream>

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

        DWORD type = 0;
        BYTE buffer[256];
        DWORD bufferSize = sizeof(buffer);

        LONG result = RegQueryValueExW(hKey, valueName.c_str(), nullptr, &type, buffer, &bufferSize);
        std::cout << "Typ wartoœci z rejestru: " << type << std::endl;
        RegCloseKey(hKey);

        if (result != ERROR_SUCCESS)
            return "";

        if (type == REG_SZ) {
            std::wstring wval(reinterpret_cast<wchar_t*>(buffer));
            return std::string(wval.begin(), wval.end());
        }
        else if (type == REG_DWORD && bufferSize == sizeof(DWORD)) {
            DWORD dwVal = *reinterpret_cast<DWORD*>(buffer);
            return std::to_string(dwVal);
        }

        return "";
    }

private:
    std::wstring registryPath;
};

