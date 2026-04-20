#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::Adl_Overdrive_Reset()
	{
		try
		{
			//Set defaults
			ADLOD8SetSetting odSetSetting{};
			odSetSetting.count = OD8_COUNT;
			for (int i = 0; i < odSetSetting.count; i++)
			{
				odSetSetting.od8SettingTable[i].reset = true;
				odSetSetting.od8SettingTable[i].requested = true;
				odSetSetting.od8SettingTable[i].value = 0;
			}

			//Set OD8Settings flag
			int od8SettingsFlag = OD8SettingsRegistryFlags::Default;

			//Set OD8Settings in registry
			AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "", "OD8Settings", od8SettingsFlag);

			//Set settings
			ADLOD8CurrentSetting odCurrentSetting{};
			odCurrentSetting.count = OD8_COUNT;
			adl_Res0 = _ADL2_Overdrive8_Setting_Set(adl_Context, adl_Gpu_AdapterIndex, &odSetSetting, &odCurrentSetting);

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

	bool MainPage::Adl_Overdrive_Save(std::vector<std::tuple<ADLOD8SettingId, int, bool>> saveSettings)
	{
		try
		{
			//Set defaults
			ADLOD8SetSetting odSetSetting{};
			odSetSetting.count = OD8_COUNT;
			for (int i = 0; i < odSetSetting.count; i++)
			{
				odSetSetting.od8SettingTable[i].reset = false;
				odSetSetting.od8SettingTable[i].requested = false;
				odSetSetting.od8SettingTable[i].value = 0;
			}

			//Set values
			bool fanControl = false;
			for (std::tuple<ADLOD8SettingId, int, bool> setting : saveSettings)
			{
				ADLOD8SettingId settingId = std::get<0>(setting);
				int settingValue = std::get<1>(setting);
				bool settingReset = std::get<2>(setting);
				odSetSetting.od8SettingTable[settingId].reset = settingReset;
				odSetSetting.od8SettingTable[settingId].requested = true;
				odSetSetting.od8SettingTable[settingId].value = settingValue;

				//Check if fan control is needed
				if (settingId == ADLOD8SettingId::OD8_FAN_CURVE_SPEED_1)
				{
					fanControl = true;
				}
			}

			//Set OD8Settings flag
			int od8SettingsFlag = OD8SettingsRegistryFlags::GpuTuning | OD8SettingsRegistryFlags::MemoryTuning | OD8SettingsRegistryFlags::PowerTuning;

			//Check Fan Control flag
			if (fanControl)
			{
				od8SettingsFlag |= OD8SettingsRegistryFlags::FanTuningOn;
				od8SettingsFlag &= ~OD8SettingsRegistryFlags::FanTuningOff;
			}
			else
			{
				od8SettingsFlag |= OD8SettingsRegistryFlags::FanTuningOff;
				od8SettingsFlag &= ~OD8SettingsRegistryFlags::FanTuningOn;
			}

			//Set OD8Settings in registry
			AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "", "OD8Settings", od8SettingsFlag);

			//Set settings
			ADLOD8CurrentSetting odCurrentSetting{};
			odCurrentSetting.count = OD8_COUNT;
			adl_Res0 = _ADL2_Overdrive8_Setting_Set(adl_Context, adl_Gpu_AdapterIndex, &odSetSetting, &odCurrentSetting);

			//Return result
			AVDebugWriteLine("Saved overdrive settings: " << adl_Res0);
			return adl_Res0 == ADL_OK;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to save overdrive settings (Exception)");
			return false;
		}
	}

	bool MainPage::Adl_Overdrive_Feature_Supported(ADLOD8FeatureControl featureId)
	{
		try
		{
			int od8Capabilities;
			int numberOfFeatures = OD8_COUNT;
			auto initSettingList = AVFin<ADLOD8SingleInitSettingWrap*>(AVFinMethod::FreeMarshal);
			adl_Res0 = _ADL2_Overdrive8_Init_SettingX2_Get(adl_Context, adl_Gpu_AdapterIndex, &od8Capabilities, &numberOfFeatures, &initSettingList.Get());
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

	std::optional<ADLOD8SingleInitSettingWrap> MainPage::Adl_Overdrive_Load_Default(ADLOD8SettingId settingId)
	{
		try
		{
			int od8Capabilities;
			int numberOfFeatures = OD8_COUNT;
			auto initSettingList = AVFin<ADLOD8SingleInitSettingWrap*>(AVFinMethod::FreeMarshal);
			adl_Res0 = _ADL2_Overdrive8_Init_SettingX2_Get(adl_Context, adl_Gpu_AdapterIndex, &od8Capabilities, &numberOfFeatures, &initSettingList.Get());
			if (adl_Res0 == ADL_OK)
			{
				//Return result
				return initSettingList.Get()[settingId];
			}
			else
			{
				//Return result
				AVDebugWriteLine("Failed to load overdrive setting default: " << settingId);
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

	std::optional<int> MainPage::Adl_Overdrive_Load_Value(ADLOD8SettingId settingId)
	{
		try
		{
			int numberOfFeatures = OD8_COUNT;
			auto currentSettingList = AVFin<int*>(AVFinMethod::FreeMarshal);
			adl_Res0 = _ADL2_Overdrive8_Current_SettingX2_Get(adl_Context, adl_Gpu_AdapterIndex, &numberOfFeatures, &currentSettingList.Get());
			if (adl_Res0 == ADL_OK)
			{
				//Return result
				return currentSettingList.Get()[settingId];
			}
			else
			{
				//Return result
				AVDebugWriteLine("Failed to load overdrive setting value: " << settingId);
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