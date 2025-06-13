#pragma once
#include "ISettingsReader.h"
class WindowsRegistrySettingsReader :
    public ISettingsReader
{
public:
    std::string GetSetting(const std::wstring& key) override {
        // u¿yj RegOpenKeyEx, RegQueryValueEx itd.
        return "wartoœæ"; // uproszczony przyk³ad
    }
};

