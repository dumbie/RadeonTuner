#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlSetDefaultSettings()
	{
		try
		{
			for (AdapterInfo adapterInfo : adl_List_Gpus)
			{
				try
				{
					//Set gaming driver flag
					AdlRegistrySettingSet(adapterInfo.iAdapterIndex, "", "KMD_IsGamingDriver", 1);

					//Set enable desktop texture flag
					AdlRegistrySettingSet(adapterInfo.iAdapterIndex, "", "KMD_EnableDesktopTexture", 1);

					//Get gpu unique identifier
					//std::wstring identifierHex = number_to_hexwstring_littleendian(adapterInfo.iBusNumber, 4, true);

					//DriverBug#1
					//Set gpu application identifier
					AdlRegistrySettingSet(adapterInfo.iAdapterIndex, "UMD", "AppGpuId", L"0x0001");

					//Set multimedia video profile mode
					Adl_Multimedia_Set_Mode(adapterInfo.iAdapterIndex);

					//Set gpu tuning and fan overdrive mode
					std::vector<std::tuple<ADLOD8SettingId, int, bool>> overdriveSettings;
					overdriveSettings.push_back({ ADLOD8SettingId::OD8_OPTIMZED_POWER_MODE, OD8_OPTIMZED_POWER_MODES::Custom, false });
					Adl_Overdrive8_Set_Values(adapterInfo.iAdapterIndex, overdriveSettings);
				}
				catch (...) {}
			}
		}
		catch (...) {}
	}
}