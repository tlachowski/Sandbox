#pragma once

#include <string>

class ISettingsReader
{
public:
    virtual std::string GetSetting(const std::wstring& key) = 0;
    virtual ~ISettingsReader() = default;
};

