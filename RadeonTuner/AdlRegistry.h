#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlVariables.h"

namespace winrt::RadeonTuner::implementation
{
	///Example: AdlRegistrySettingSet(adlDisplayId, "UMD", "TurboSync", "1");
	bool MainPage::AdlRegistrySettingSet(ADLDisplayID displayID, std::string subKey, std::string key, std::string value)
	{
		try
		{
			const int charsize = (int)(value.length()) * sizeof(wchar_t);
			char* chararray = (char*)value.c_str();

			int adlResult = _ADL2_Adapter_RegValueString_Set(_ADL2_Context, displayID.iDisplayLogicalAdapterIndex, ADL_REG_DEVICE_FUNCTION_1, subKey.c_str(), key.c_str(), charsize, chararray);
			AVDebugWriteLine("ADL set registry setting: " << adlResult);
			return adlResult == ADL_OK;
		}
		catch (...)
		{
			AVDebugWriteLine("ADL failed to set registry setting.");
			return false;
		}
	}

	///Example: AdlRegistrySettingGet(adlDisplayId, "UMD", "TurboSync");
	std::string MainPage::AdlRegistrySettingGet(ADLDisplayID displayID, std::string subKey, std::string key)
	{
		std::string returnString;
		try
		{
			const int charsize = 1024;
			char chararray[charsize]{};

			int adlResult = _ADL2_Adapter_RegValueString_Get(_ADL2_Context, displayID.iDisplayLogicalAdapterIndex, ADL_REG_DEVICE_FUNCTION_1, subKey.c_str(), key.c_str(), charsize, chararray);
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
			AVDebugWriteLine("ADL get registry setting: " << adlResult);
		}
		catch (...)
		{
			AVDebugWriteLine("ADL failed to get registry setting.");
		}
		return returnString;
	}
}