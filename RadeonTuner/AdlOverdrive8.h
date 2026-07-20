#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::Adl_Overdrive8_Reset(int gpuAdapterIndex)
	{
		try
		{
			//Get default settings
			ADLOD8SetSetting requestSettingList{};
			requestSettingList.count = OD8_COUNT - 2;
			for (int i = 0; i < requestSettingList.count; i++)
			{
				requestSettingList.od8SettingTable[i].reset = true;
				requestSettingList.od8SettingTable[i].requested = true;
				requestSettingList.od8SettingTable[i].value = 0;
			}

			//Set settings
			ADLOD8CurrentSetting resultSettingList{};
			resultSettingList.count = OD8_COUNT - 2;
			adl_Res0 = _ADL2_Overdrive8_Setting_Set(adl_Context, gpuAdapterIndex, &requestSettingList, &resultSettingList);

			//Return result
			AVDebugWriteLine("Reset overdrive settings: " << adl_Res0);
			return adl_Res0 == ADL_OK;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to reset overdrive settings (Exception)");
			return false;
		}
	}

	bool MainPage::Adl_Overdrive8_Set_Values(int gpuAdapterIndex, std::vector<std::tuple<ADLOD8SettingId, int, bool>> saveSettings)
	{
		try
		{
			//Note: when tuning preset is not set to default or custom mode, tuning fails to apply.
			//Note: when you create an empty settings list with all reset and requested false some settings still reset to default.
			//Note: on some gpu's applying settings randomly returns false, even when the settings are applied correctly.

			//Get current settings
			int currentSettingCount = OD8_COUNT - 2;
			auto currentSettingList = AVFin<int*>(AVFinMethod::FreeMarshal);
			adl_Res0 = _ADL2_Overdrive8_Current_SettingX2_Get(adl_Context, gpuAdapterIndex, &currentSettingCount, &currentSettingList.Get());
			if (adl_Res0 != ADL_OK)
			{
				//Return result
				AVDebugWriteLine("Failed to get current overdrive settings: " << adl_Res0);
				return false;
			}

			//Convert current settings
			ADLOD8SetSetting requestSettingList{};
			requestSettingList.count = OD8_COUNT - 2;
			for (int i = 0; i < requestSettingList.count; i++)
			{
				requestSettingList.od8SettingTable[i].reset = false;
				requestSettingList.od8SettingTable[i].requested = true;
				requestSettingList.od8SettingTable[i].value = currentSettingList.Get()[i];
			}

			//Set values
			for (std::tuple<ADLOD8SettingId, int, bool> setting : saveSettings)
			{
				ADLOD8SettingId settingId = std::get<0>(setting);
				int settingValue = std::get<1>(setting);
				bool settingReset = std::get<2>(setting);
				requestSettingList.od8SettingTable[settingId].reset = settingReset;
				requestSettingList.od8SettingTable[settingId].requested = true;
				requestSettingList.od8SettingTable[settingId].value = settingValue;
			}

			//Set settings
			ADLOD8CurrentSetting resultSettingList{};
			resultSettingList.count = OD8_COUNT - 2;
			adl_Res0 = _ADL2_Overdrive8_Setting_Set(adl_Context, gpuAdapterIndex, &requestSettingList, &resultSettingList);

			//Return result
			AVDebugWriteLine("Set overdrive values: " << adl_Res0);
			return adl_Res0 == ADL_OK;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to set overdrive values (Exception)");
			return false;
		}
	}

	bool MainPage::Adl_Overdrive8_Feature_Supported(int gpuAdapterIndex, ADLOD8FeatureControl featureId)
	{
		try
		{
			int od8Capabilities;
			int numberOfFeatures = OD8_COUNT - 2;
			auto initSettingList = AVFin<ADLOD8SingleInitSettingWrap*>(AVFinMethod::FreeMarshal);
			adl_Res0 = _ADL2_Overdrive8_Init_SettingX2_Get(adl_Context, gpuAdapterIndex, &od8Capabilities, &numberOfFeatures, &initSettingList.Get());
			if (adl_Res0 == ADL_OK)
			{
				//Return result
				return (od8Capabilities & featureId) == featureId;
			}
			else
			{
				//Return result
				return false;
			}
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	std::optional<ADLOD8SingleInitSettingWrap> MainPage::Adl_Overdrive8_Load_Default(int gpuAdapterIndex, ADLOD8SettingId settingId)
	{
		try
		{
			int od8Capabilities;
			int numberOfFeatures = OD8_COUNT - 2;
			auto initSettingList = AVFin<ADLOD8SingleInitSettingWrap*>(AVFinMethod::FreeMarshal);
			adl_Res0 = _ADL2_Overdrive8_Init_SettingX2_Get(adl_Context, gpuAdapterIndex, &od8Capabilities, &numberOfFeatures, &initSettingList.Get());
			if (adl_Res0 == ADL_OK)
			{
				//Return result
				return initSettingList.Get()[settingId];
			}
			else
			{
				//Return result
				//AVDebugWriteLine("Failed to load overdrive setting default: " << settingId);
				return std::nullopt;
			}
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to load overdrive setting default: " << settingId << " (Exception)");
			return std::nullopt;
		}
	}

	std::optional<int> MainPage::Adl_Overdrive8_Load_Value(int gpuAdapterIndex, ADLOD8SettingId settingId)
	{
		try
		{
			int currentSettingCount = OD8_COUNT - 2;
			auto currentSettingList = AVFin<int*>(AVFinMethod::FreeMarshal);
			adl_Res0 = _ADL2_Overdrive8_Current_SettingX2_Get(adl_Context, gpuAdapterIndex, &currentSettingCount, &currentSettingList.Get());
			if (adl_Res0 == ADL_OK)
			{
				//Return result
				return currentSettingList.Get()[settingId];
			}
			else
			{
				//Return result
				//AVDebugWriteLine("Failed to load overdrive setting value: " << settingId);
				return std::nullopt;
			}
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to load overdrive setting value: " << settingId << " (Exception)");
			return std::nullopt;
		}
	}
}