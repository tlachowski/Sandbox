#include "pch.h"

#include "gtest/gtest.h"
#include "..\TrayIconApp\ISettingsReader.h"
#include "..\TrayIconApp\WindowsRegistrySettingsReader.h"
#include <windows.h>


const std::wstring TEST_KEY_PATH = L"Software\\TrayIconApp\\TestConfig";

// Pomocnicza funkcja do ustawiania wartoœci w rejestrze
void WriteTestRegistryValue(const std::wstring& name, const std::wstring& value) {
    HKEY hKey;
    RegCreateKeyExW(HKEY_CURRENT_USER, TEST_KEY_PATH.c_str(), 0, nullptr, 0, KEY_WRITE, nullptr, &hKey, nullptr);
    RegSetValueExW(hKey, name.c_str(), 0, REG_SZ, (const BYTE*)value.c_str(), (DWORD)((value.size() + 1) * sizeof(wchar_t)));
    RegCloseKey(hKey);
}

void DeleteTestRegistryKey() {
    RegDeleteTreeW(HKEY_CURRENT_USER, TEST_KEY_PATH.c_str());
}

TEST(RegistryIntegrationTest, ReadsValueFromRegistry) {
    // Arrange
    std::wstring testKey = L"AutoStart";
    std::wstring expectedValue = L"1";
    WriteTestRegistryValue(testKey, expectedValue);

    // Act
    WindowsRegistrySettingsReader reader(TEST_KEY_PATH);  // Zak³adamy, ¿e konstruktor przyjmuje œcie¿kê
    std::string result = reader.GetSetting(testKey);

    std::cout << "Resultat z funkcji GetSeting(): " << result << std::endl;
    // Assert
    EXPECT_EQ(result, "1");

    // Cleanup
    DeleteTestRegistryKey();
}
