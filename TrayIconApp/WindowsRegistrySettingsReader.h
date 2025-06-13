#include <windows.h>
#include <string>
#include <iostream>

class WindowsRegistrySettingsReader {
public:
    explicit WindowsRegistrySettingsReader(const std::wstring& subKey)
        : registryPath(subKey) {
    }

    std::string GetSetting(const std::wstring& valueName) const {
        HKEY hKey;
        std::wstring fullPath = L"Software\\" + registryPath;

        LONG openStatus = RegOpenKeyExW(HKEY_CURRENT_USER, fullPath.c_str(), 0, KEY_READ, &hKey);
        if (openStatus != ERROR_SUCCESS) {
            std::cerr << "[RegOpenKeyExW] B³¹d " << openStatus << std::endl;
            return "";
        }

        BYTE buffer[512];
        DWORD bufferSize = sizeof(buffer);
        DWORD type = 0;

        LONG queryStatus = RegQueryValueExW(hKey, valueName.c_str(), nullptr, &type, buffer, &bufferSize);
        RegCloseKey(hKey);

        if (queryStatus != ERROR_SUCCESS) {
            std::cerr << "[RegQueryValueExW] B³¹d " << queryStatus << std::endl;
            return "";
        }

        std::cout << "[Registry] Typ wartoœci: " << type << std::endl;

        if (type == REG_SZ || type == REG_EXPAND_SZ) {
            std::wstring wval(reinterpret_cast<wchar_t*>(buffer));
            return std::string(wval.begin(), wval.end());
        }
        else if (type == REG_DWORD && bufferSize == sizeof(DWORD)) {
            DWORD dwVal = *reinterpret_cast<DWORD*>(buffer);
            return std::to_string(dwVal);
        }

        std::cerr << "[Registry] Nieobs³ugiwany typ: " << type << std::endl;
        return "";
    }

private:
    std::wstring registryPath;
};
