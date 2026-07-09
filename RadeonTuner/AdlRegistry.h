#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	///Example: AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "TurboSync", "1");
	bool MainPage::AdlRegistrySettingSet(int gpuAdapterIndex, std::string subKey, std::string keyName, std::wstring keyValue)
	{
		try
		{
			if (keyValue.empty()) { keyValue = L" "; }
			int keyValueSize = keyValue.size() * sizeof(WCHAR);
			adl_Res0 = _ADL2_Adapter_RegValueString_Set(adl_Context, gpuAdapterIndex, ADL_REG_DEVICE_FUNCTION_1, subKey.c_str(), keyName.c_str(), keyValueSize, keyValue.c_str());
			AVDebugWriteLine("ADL set string registry setting: " << adl_Res0);
			return adl_Res0 == ADL_OK;
		}
		catch (...)
		{
			AVDebugWriteLine("ADL failed to set string registry setting.");
			return false;
		}
	}

	///Example: AdlRegistrySettingSet(gpuAdapterIndex, "", "KMD_10BitMode", 2);
	bool MainPage::AdlRegistrySettingSet(int gpuAdapterIndex, std::string subKey, std::string keyName, int keyValue)
	{
		try
		{
			adl_Res0 = _ADL2_Adapter_RegValueInt_Set(adl_Context, gpuAdapterIndex, ADL_REG_DEVICE_FUNCTION_1, subKey.c_str(), keyName.c_str(), keyValue);
			AVDebugWriteLine("ADL set int registry setting: " << adl_Res0);
			return adl_Res0 == ADL_OK;
		}
		catch (...)
		{
			AVDebugWriteLine("ADL failed to set int registry setting.");
			return false;
		}
	}

	///Example: AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "TurboSync");
	std::optional<std::wstring> MainPage::AdlRegistrySettingGetString(int gpuAdapterIndex, std::string subKey, std::string keyName, bool decodeBinary)
	{
		try
		{
			//Note: ADL2_Adapter_RegValueString_Get is not reliable, older drivers save integer as REG_BINARY and newer drivers as REG_DWORD which RegValueStringGet not seems to handle properly.

			//Check registry value type
			std::wstring subKeyW = string_to_wstring(subKey);
			std::wstring keyNameW = string_to_wstring(keyName);
			std::wstring registryPathW = L"System\\CurrentControlSet\\Control\\Class\\" + gpuRegistryPath + L"\\" + subKeyW;
			REGTYPE_ENUM regValueType = RegistryType(HKEY_ENUM::LOCAL_MACHINE, registryPathW, keyNameW);

			//Get registry value
			if (regValueType == REGTYPE_ENUM::SZ)
			{
				//Return result
				return RegistryGetString(HKEY_ENUM::LOCAL_MACHINE, registryPathW, keyNameW);
			}
			else if (regValueType == REGTYPE_ENUM::DWORD)
			{
				std::optional<DWORD> regValue = RegistryGetDword(HKEY_ENUM::LOCAL_MACHINE, registryPathW, keyNameW);
				if (regValue.has_value())
				{
					//Return result
					return number_to_wstring(regValue.value());
				}
			}
			else if (regValueType == REGTYPE_ENUM::BINARY)
			{
				std::vector<BYTE> regValue = RegistryGetBinary(HKEY_ENUM::LOCAL_MACHINE, registryPathW, keyNameW);
				if (regValue.size() == 0)
				{
					//Return result
					return std::nullopt;
				}
				if (decodeBinary)
				{
					//Check registry value encoding
					bool valueIsInteger = regValue.size() == 4 && regValue[2] == 0;
					if (valueIsInteger)
					{
						//Decode bytes 32-Bit LE integer
						//Example value: 01 00 00 00 (1) / 3C 00 00 00 (60) / E8 03 00 00 (1000) / FF FF 00 00 (65535)
						uint32_t integerValue = *(uint32_t*)regValue.data();

						//Return result
						return number_to_wstring(integerValue);
					}
					else
					{
						//Decode bytes UTF16 LE string
						//Example value: 31 00 (1) / 2D 00 31 00 (-1) / 36 00 34 00 (64) / 41 00 4D 00 44 00 20 00 52 00 61 00 64 00 65 00 6F 00 6E 00 (AMD Radeon)
						return std::wstring((WCHAR*)regValue.data(), regValue.size() / sizeof(WCHAR));
					}
				}
				else
				{
					std::wstring regValueW;
					regValueW.reserve(regValue.size() * 3);

					//Add converted byte
					for (BYTE byte : regValue)
					{
						regValueW += number_to_hexwstring(byte, 2, false);
					}

					//Remove last space
					if (!regValueW.empty())
					{
						regValueW.pop_back();
					}

					//Return result
					return regValueW;
				}
			}

			//Return result
			return std::nullopt;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("ADL failed to get string registry setting.");
			return std::nullopt;
		}
	}

	///Example: AdlRegistrySettingGetInt(gpuAdapterIndex, "", "KMD_10BitMode");
	std::optional<INT> MainPage::AdlRegistrySettingGetInt(int gpuAdapterIndex, std::string subKey, std::string keyName)
	{
		try
		{
			int returnInt = -1;
			adl_Res0 = _ADL2_Adapter_RegValueInt_Get(adl_Context, gpuAdapterIndex, ADL_REG_DEVICE_FUNCTION_1, subKey.c_str(), keyName.c_str(), &returnInt);
			if (adl_Res0 == ADL_OK)
			{
				//AVDebugWriteLine("ADL get int registry setting: " << adl_Res0);
				return returnInt;
			}
			else
			{
				AVDebugWriteLine("ADL failed to get int registry setting.");
				return std::nullopt;
			}
		}
		catch (...)
		{
			AVDebugWriteLine("ADL failed to get int registry setting.");
			return std::nullopt;
		}
	}
}