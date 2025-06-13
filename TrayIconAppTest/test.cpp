#include "pch.h"

#include "gtest/gtest.h"
#include "..\TrayIconApp\ISettingsReader.h"

// Fa³szywa wersja klasy do testu
class FakeSettingsReader : public ISettingsReader {
public:
    std::string GetSetting(const std::wstring& key) override {
        if (key == L"TrayIconEnabled") return "true";
        return "unknown";
    }
};

TEST(SettingsTest, ReturnsCorrectValueFromFakeRegistry) {
    FakeSettingsReader reader;
    EXPECT_EQ(reader.GetSetting(L"TrayIconEnabled"), "true");
    EXPECT_EQ(reader.GetSetting(L"UnknownKey"), "unknown");
}
