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
			//Get all gpu's
			std::vector<AdapterInfo> listGpus = AdlGetGpuAll();

			//Set default settings for all gpu's
			for (AdapterInfo adapterInfo : listGpus)
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
				}
				catch (...) {}
			}
		}
		catch (...) {}
	}
}