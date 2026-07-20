#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	std::wstring MainPage::AdlxValuesLoadGpuList(bool selectFirst)
	{
		try
		{
			//Get combobox items
			auto itemCollection = combobox_GpuSelect().Items();

			//Clear combobox items
			itemCollection.Clear();

			//Get all GPU's
			adl_List_Gpus = AdlGetGpuAll();
			int adapterCount = adl_List_Gpus.size();

			//Add all GPU's
			for (const AdapterInfo& adapterInfo : adl_List_Gpus)
			{
				//Add gpu to combobox
				itemCollection.Append(box_value(char_to_wstring(adapterInfo.strAdapterName)));
			}

			//Select first index
			if (selectFirst)
			{
				combobox_GpuSelect().SelectedIndex(0);
			}

			//Set result
			AVDebugWriteLine("Listed all GPU's: " << adapterCount);
			if (adapterCount == 0)
			{
				return L"Failed to find any GPU's.";
			}
			else
			{
				return L"";
			}
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading gpu list.");
			return L"Failed loading gpu list.";
		}
	}

	void MainPage::AdlxValuesLoadTuning()
	{
		try
		{
			//Get current and default settings
			TuningFanSettings tuningFanSettingsAdl = TuningFanSettings_Generate_FromADL(adl_Gpu_AdapterIndex).value();

			//Add gpu tuning and fans settings profile
			TuningFanSettings_Profile_Add(tuningFanSettingsAdl);

			//Device identifier
			std::wstring device_id_w = string_to_wstring(tuningFanSettingsAdl.DeviceId.value());

			//Get tuning fan settings
			tuningFanSettingsCurrent = TuningFanSettings_Profile_Get(device_id_w).value();

			//Convert settings values to interface
			bool adlResult = TuningFanSettings_Convert_ToUI_Adl(tuningFanSettingsAdl);
			bool profileResult = TuningFanSettings_Convert_ToUI_Current(tuningFanSettingsCurrent);

			//Update button colors
			if (adlResult && profileResult)
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				button_Tuning_Apply().Background(colorValid);
				button_Fan_Apply().Background(colorValid);
			}
			else
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				button_Tuning_Apply().Background(colorInvalid);
				button_Fan_Apply().Background(colorInvalid);
			}

			//Set result
			AVDebugWriteLine("ADLX loaded tuning and fans values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading tuning and fans values.");
		}
	}
}