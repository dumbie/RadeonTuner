#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::Adl_Overdrive8_Values_Reset(int gpuAdapterIndex)
	{
		try
		{
			//Create empty settings
			ADLOD8SetSetting requestSettingList{};
			requestSettingList.count = OD8_COUNT - 1;
			for (UINT i = 0; i < requestSettingList.count; i++)
			{
				requestSettingList.od8SettingTable[i].reset = true;
				requestSettingList.od8SettingTable[i].requested = true;
				requestSettingList.od8SettingTable[i].value = 0;
			}

			//Apply settings
			ADLOD8CurrentSetting resultSettingList{};
			resultSettingList.count = OD8_COUNT - 1;
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

	bool MainPage::Adl_Overdrive8_Values_Set(int gpuAdapterIndex, std::vector<ADLOD8SaveSetting> saveSettings)
	{
		try
		{
			//Note: When tuning preset is not set to default or custom mode, tuning fails to apply.

			//Get default settings
			int od8Capabilities = -1;
			int numberOfFeatures = OD8_COUNT - 1;
			auto initSettingList = AVFin<ADLOD8SingleInitSettingWrap*>(AVFinMethod::FreeMarshal);
			adl_Res0 = _ADL2_Overdrive8_Init_SettingX2_Get(adl_Context, gpuAdapterIndex, &od8Capabilities, &numberOfFeatures, &initSettingList.Get());

			//Create empty settings
			ADLOD8SetSetting requestSettingList{};
			requestSettingList.count = OD8_COUNT - 1;
			for (UINT i = 0; i < requestSettingList.count; i++)
			{
				requestSettingList.od8SettingTable[i].reset = false;
				requestSettingList.od8SettingTable[i].requested = false;
				requestSettingList.od8SettingTable[i].value = 0;
			}

			//Set setting values
			for (const ADLOD8SaveSetting& setting : saveSettings)
			{
				requestSettingList.od8SettingTable[setting.Identifier].reset = setting.ResetValue;
				requestSettingList.od8SettingTable[setting.Identifier].requested = true;
				if (setting.UseDefaultValue)
				{
					requestSettingList.od8SettingTable[setting.Identifier].value = initSettingList.Get()[setting.Identifier].defaultValue;
				}
				else
				{
					requestSettingList.od8SettingTable[setting.Identifier].value = setting.TargetValue;
				}
			}

			//Apply settings
			ADLOD8CurrentSetting resultSettingList{};
			resultSettingList.count = OD8_COUNT - 1;
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
			//Get default settings
			int od8Capabilities = -1;
			int numberOfFeatures = OD8_COUNT - 1;
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
			//Get default settings
			int od8Capabilities = -1;
			int numberOfFeatures = OD8_COUNT - 1;
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
			int currentSettingCount = OD8_COUNT - 1;
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