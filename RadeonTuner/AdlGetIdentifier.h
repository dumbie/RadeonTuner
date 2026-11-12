#pragma once
#include "pch.h"

namespace winrt::RadeonTuner::implementation
{
	std::wstring MainPage::AdlxGetGpuIdentifier(int adapterIndex)
	{
		//Example: VEN_1002&DEV_7550&SUBSYS_2435148C&REV_C0
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

				//Serial number
				//Fix find way to get unique serial number to identify identical GPU's
				//int uniqueIdentifier = -1;
				//adl_Res0 = _ADL2_Adapter_ID_Get(adl_Context, adapterIndex, &uniqueIdentifier);
			}
		}
		catch (...) {}
		//AVDebugWriteLine("Got gpu identifier: " << device_id);
		return device_id;
	}

	std::wstring MainPage::AdlxGetDisplayIdentifier(int adapterIndex, int displayIndex)
	{
		//Example: 27934 LG TV SSCR2 16843009
		std::wstring deviceIdentifier = L"";
		try
		{
			//Device strings
			std::wstring deviceManufacturerId = L"";
			std::wstring deviceDisplayName = L"";
			std::wstring deviceSerialNumber = L"";

			//Get display DDC information
			ADLDDCInfo2 ADLDDCInfo2;
			adl_Res0 = _ADL2_Display_DDCInfo2_Get(adl_Context, adapterIndex, displayIndex, &ADLDDCInfo2);
			if (adl_Res0 == ADL_OK)
			{
				//Manufacturer identifier
				deviceManufacturerId = number_to_wstring(ADLDDCInfo2.ulManufacturerID);

				//Display name
				deviceDisplayName = char_to_wstring(ADLDDCInfo2.cDisplayName);

				//Serial number
				//Note: 16843009 is a generic serial number used on lots of displays, can't be used to identify identical displays.
				deviceSerialNumber = number_to_wstring(ADLDDCInfo2.ulSerialID);
			}

			//Combine strings
			deviceIdentifier = deviceManufacturerId + L" " + deviceDisplayName + L" " + deviceSerialNumber;
		}
		catch (...) {}
		//AVDebugWriteLine("Got display identifier: " << deviceIdentifier);
		return deviceIdentifier;
	}
}