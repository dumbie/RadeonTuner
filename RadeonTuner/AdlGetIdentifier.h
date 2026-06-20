#pragma once
#include "pch.h"

namespace winrt::RadeonTuner::implementation
{
	std::wstring MainPage::AdlxGetGpuIdentifier(int adapterIndex)
	{
		//Example old: 1002 7550 - 148C 2435 - C0 - 768
		//Example new: VEN_1002&DEV_7550&SUBSYS_2435148C&REV_C0
		std::wstring device_id = L"";
		try
		{
			//Get gpu information
			std::optional<AdapterInfo> gpuInfo = AdlGetGpuByAdapterIndex(adapterIndex);
			if (gpuInfo.has_value())
			{
				AdapterInfo adapterInfo = gpuInfo.value();

				//Device identifier
				device_id = char_to_wstring(adapterInfo.strPNPString);
				device_id = wstring_get_between(device_id, L"\\", L"\\");
			}
		}
		catch (...) {}
		//AVDebugWriteLine("Got gpu identifier: " << device_id);
		return device_id;
	}

	std::wstring MainPage::AdlxGetDisplayIdentifier(int displayIndex)
	{
		//Example old: 27934 LG TV SSCR2 7118370396267366160
		//Example new: LG TV SSCR2
		std::wstring device_id = L"";
		try
		{
			//Get display information
			std::optional<ADLDisplayInfo> displayInfo = AdlGetDisplayByDisplayIndex(displayIndex);
			if (displayInfo.has_value())
			{
				ADLDisplayInfo adapterInfo = displayInfo.value();

				//Device identifier
				device_id = char_to_wstring(adapterInfo.strDisplayName);
			}
		}
		catch (...) {}
		//AVDebugWriteLine("Got display identifier: " << device_id);
		return device_id;
	}
}