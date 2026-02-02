#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "AdlVariables.h"

namespace winrt::RadeonTuner::implementation
{
	///Example: AdlRegistrySettingSet(adlAdapterIndex, "UMD", "TurboSync", "1");
	bool MainPage::AdlRegistrySettingSet(int adlAdapterIndex, std::string subKey, std::string key, std::string value)
	{
		try
		{
			const int charsize = (int)(value.length()) * sizeof(wchar_t);
			char* chararray = (char*)value.c_str();

			int adlResult = _ADL2_Adapter_RegValueString_Set(adl_Context, adlAdapterIndex, ADL_REG_DEVICE_FUNCTION_1, subKey.c_str(), key.c_str(), charsize, chararray);
			AVDebugWriteLine("ADL set string registry setting: " << adlResult);
			return adlResult == ADL_OK;
		}
		catch (...)
		{
			AVDebugWriteLine("ADL failed to set string registry setting.");
			return false;
		}
	}

	///Example: AdlRegistrySettingSet(adlAdapterIndex, "", "KMD_10BitMode", 2);
	bool MainPage::AdlRegistrySettingSet(int adlAdapterIndex, std::string subKey, std::string key, int value)
	{
		try
		{
			//Fix does not seem to save value as expected REG_DWORD but REG_BINARY using UTF-16LE instead
			int adlResult = _ADL2_Adapter_RegValueInt_Set(adl_Context, adlAdapterIndex, ADL_REG_DEVICE_FUNCTION_1, subKey.c_str(), key.c_str(), value);
			AVDebugWriteLine("ADL set int registry setting: " << adlResult);
			return adlResult == ADL_OK;
		}
		catch (...)
		{
			AVDebugWriteLine("ADL failed to set int registry setting.");
			return false;
		}
	}

	///Example: AdlRegistrySettingGetString(adlAdapterIndex, "UMD", "TurboSync");
	std::string MainPage::AdlRegistrySettingGetString(int adlAdapterIndex, std::string subKey, std::string key)
	{
		std::string returnString;
		try
		{
			const int charsize = 1024;
			char chararray[charsize]{};

			int adlResult = _ADL2_Adapter_RegValueString_Get(adl_Context, adlAdapterIndex, ADL_REG_DEVICE_FUNCTION_1, subKey.c_str(), key.c_str(), charsize, chararray);
			if (adlResult == ADL_OK)
			{
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

				//Convert array to string
				returnString = std::string(chararray);
			}
			AVDebugWriteLine("ADL get string registry setting: " << adlResult);
		}
		catch (...)
		{
			AVDebugWriteLine("ADL failed to get string registry setting.");
		}
		return returnString;
	}

	///Example: AdlRegistrySettingGetInt(adlAdapterIndex, "", "KMD_10BitMode");
	int MainPage::AdlRegistrySettingGetInt(int adlAdapterIndex, std::string subKey, std::string key)
	{
		int returnInt = -1;
		try
		{
			int adlResult = _ADL2_Adapter_RegValueInt_Get(adl_Context, adlAdapterIndex, ADL_REG_DEVICE_FUNCTION_1, subKey.c_str(), key.c_str(), &returnInt);
			AVDebugWriteLine("ADL get int registry setting: " << adlResult);
		}
		catch (...)
		{
			AVDebugWriteLine("ADL failed to get int registry setting.");
		}
		return returnInt;
	}
}