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

	std::wstring MainPage::AdlxGetDisplayIdentifier(int adapterIndex, int displayIndex)
	{
		//Example old: 27934 LG TV SSCR2 7118370396267366160
		//Example new: 27934 LG TV SSCR2
		std::wstring deviceIdentifier = L"";
		try
		{
			//Device strings
			std::wstring deviceManufacturerId = L"";
			std::wstring deviceDisplayName = L"";

			//Get display DDC information
			ADLDDCInfo2 ADLDDCInfo2;
			adl_Res0 = _ADL2_Display_DDCInfo2_Get(adl_Context, adapterIndex, displayIndex, &ADLDDCInfo2);
			if (adl_Res0 == ADL_OK)
			{
				//Set manufacturer id
				deviceManufacturerId = number_to_wstring(ADLDDCInfo2.ulManufacturerID);

				//Set display name
				deviceDisplayName = char_to_wstring(ADLDDCInfo2.cDisplayName);
			}

			//Combine strings
			deviceIdentifier = deviceManufacturerId + L" " + deviceDisplayName;
		}
		catch (...) {}
		//AVDebugWriteLine("Got display identifier: " << deviceIdentifier);
		return deviceIdentifier;
	}
}