#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	///Example: AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "TurboSync", "1");
	bool MainPage::AdlRegistrySettingSet(int gpuAdapterIndex, std::string subKey, std::string key, std::string value)
	{
		try
		{
			const int charsize = (int)(value.length()) * sizeof(wchar_t);
			char* chararray = (char*)value.c_str();

			adl_Res0 = _ADL2_Adapter_RegValueString_Set(adl_Context, gpuAdapterIndex, ADL_REG_DEVICE_FUNCTION_1, subKey.c_str(), key.c_str(), charsize, chararray);
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
	bool MainPage::AdlRegistrySettingSet(int gpuAdapterIndex, std::string subKey, std::string key, int value)
	{
		try
		{
			//Fix does not seem to save value as expected REG_DWORD but REG_BINARY using UTF-16LE instead
			adl_Res0 = _ADL2_Adapter_RegValueInt_Set(adl_Context, gpuAdapterIndex, ADL_REG_DEVICE_FUNCTION_1, subKey.c_str(), key.c_str(), value);
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
	std::optional<std::string> MainPage::AdlRegistrySettingGetString(int gpuAdapterIndex, std::string subKey, std::string key)
	{
		try
		{
			const int charsize = 1024;
			char chararray[charsize]{};

			adl_Res0 = _ADL2_Adapter_RegValueString_Get(adl_Context, gpuAdapterIndex, ADL_REG_DEVICE_FUNCTION_1, subKey.c_str(), key.c_str(), charsize, chararray);
			if (adl_Res0 == ADL_OK)
			{
				//AVDebugWriteLine("ADL get string registry setting: " << adl_Res0);

				//Remove \0 from string
				int string_position = 0;
				for (int string_index = 0; string_index < charsize; string_index++)
				{
					if (chararray[string_index] != '\0')
					{
						chararray[string_position++] = chararray[string_index];
					}
				}
				if (string_position < charsize)
				{
					chararray[string_position] = '\0';
				}

				//Return result
				return chararray;
			}
			else
			{
				//Return result
				AVDebugWriteLine("ADL failed to get string registry setting.");
				return std::nullopt;
			}
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("ADL failed to get string registry setting.");
			return std::nullopt;
		}
	}

	///Example: AdlRegistrySettingGetInt(gpuAdapterIndex, "", "KMD_10BitMode");
	std::optional<INT> MainPage::AdlRegistrySettingGetInt(int gpuAdapterIndex, std::string subKey, std::string key)
	{
		try
		{
			int returnInt = -1;
			adl_Res0 = _ADL2_Adapter_RegValueInt_Get(adl_Context, gpuAdapterIndex, ADL_REG_DEVICE_FUNCTION_1, subKey.c_str(), key.c_str(), &returnInt);
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