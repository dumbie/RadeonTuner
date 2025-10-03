#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	TuningFanSettings MainPage::Generate_TuningFanSettings()
	{
		TuningFanSettings tuningFanSettings{};
		try
		{
			tuningFanSettings.CoreMin = (int)slider_Core_Min().Value();
			tuningFanSettings.CoreMax = (int)slider_Core_Max().Value();
			tuningFanSettings.MemoryMax = (int)slider_Memory_Max().Value();
			tuningFanSettings.MemoryTiming = (int)combobox_Memory_Timing().SelectedIndex();
			tuningFanSettings.PowerLimit = (int)slider_Power_Limit().Value();
			tuningFanSettings.PowerVoltage = (int)slider_Power_Voltage().Value();
			tuningFanSettings.PowerTDC = (int)slider_Power_TDC().Value();
			tuningFanSettings.FanZeroRpm = (bool)toggleswitch_Fan_Zero_Rpm().IsOn();
			tuningFanSettings.FanSpeed0 = (int)slider_Fan_Speed_0().Value();
			tuningFanSettings.FanTemp0 = (int)slider_Fan_Temp_0().Value();
			tuningFanSettings.FanSpeed1 = (int)slider_Fan_Speed_1().Value();
			tuningFanSettings.FanTemp1 = (int)slider_Fan_Temp_1().Value();
			tuningFanSettings.FanSpeed2 = (int)slider_Fan_Speed_2().Value();
			tuningFanSettings.FanTemp2 = (int)slider_Fan_Temp_2().Value();
			tuningFanSettings.FanSpeed3 = (int)slider_Fan_Speed_3().Value();
			tuningFanSettings.FanTemp3 = (int)slider_Fan_Temp_3().Value();
			tuningFanSettings.FanSpeed4 = (int)slider_Fan_Speed_4().Value();
			tuningFanSettings.FanTemp4 = (int)slider_Fan_Temp_4().Value();

			//Device identifier
			std::wstring device_id_w = AdlxGetDeviceIdentifier(ppGpuInfo);
			if (!device_id_w.empty())
			{
				tuningFanSettings.DeviceId = wstring_to_string(device_id_w);
			}
		}
		catch (...) {}
		return tuningFanSettings;
	}

	TuningFanSettings MainPage::Generate_TuningFanSettings(nlohmann::json jsonData)
	{
		TuningFanSettings tuningFanSettings{};
		try
		{
			//Set settings values
			if (jsonData.contains("CoreMin"))
			{
				tuningFanSettings.CoreMin = (int)jsonData["CoreMin"];
			}
			if (jsonData.contains("CoreMax"))
			{
				tuningFanSettings.CoreMax = (int)jsonData["CoreMax"];
			}
			if (jsonData.contains("MemoryMax"))
			{
				tuningFanSettings.MemoryMax = (int)jsonData["MemoryMax"];
			}
			if (jsonData.contains("MemoryTiming"))
			{
				tuningFanSettings.MemoryTiming = (int)jsonData["MemoryTiming"];
			}
			if (jsonData.contains("PowerLimit"))
			{
				tuningFanSettings.PowerLimit = (int)jsonData["PowerLimit"];
			}
			if (jsonData.contains("PowerVoltage"))
			{
				tuningFanSettings.PowerVoltage = (int)jsonData["PowerVoltage"];
			}
			if (jsonData.contains("PowerTDC"))
			{
				tuningFanSettings.PowerTDC = (int)jsonData["PowerTDC"];
			}
			if (jsonData.contains("FanZeroRpm"))
			{
				tuningFanSettings.FanZeroRpm = (bool)jsonData["FanZeroRpm"];
			}
			if (jsonData.contains("FanSpeed0"))
			{
				tuningFanSettings.FanSpeed0 = (int)jsonData["FanSpeed0"];
			}
			if (jsonData.contains("FanTemp0"))
			{
				tuningFanSettings.FanTemp0 = (int)jsonData["FanTemp0"];
			}
			if (jsonData.contains("FanSpeed1"))
			{
				tuningFanSettings.FanSpeed1 = (int)jsonData["FanSpeed1"];
			}
			if (jsonData.contains("FanTemp1"))
			{
				tuningFanSettings.FanTemp1 = (int)jsonData["FanTemp1"];
			}
			if (jsonData.contains("FanSpeed2"))
			{
				tuningFanSettings.FanSpeed2 = (int)jsonData["FanSpeed2"];
			}
			if (jsonData.contains("FanTemp2"))
			{
				tuningFanSettings.FanTemp2 = (int)jsonData["FanTemp2"];
			}
			if (jsonData.contains("FanSpeed3"))
			{
				tuningFanSettings.FanSpeed3 = (int)jsonData["FanSpeed3"];
			}
			if (jsonData.contains("FanTemp3"))
			{
				tuningFanSettings.FanTemp3 = (int)jsonData["FanTemp3"];
			}
			if (jsonData.contains("FanSpeed4"))
			{
				tuningFanSettings.FanSpeed4 = (int)jsonData["FanSpeed4"];
			}
			if (jsonData.contains("FanTemp4"))
			{
				tuningFanSettings.FanTemp4 = (int)jsonData["FanTemp4"];
			}

			//Device identifier
			if (jsonData.contains("DeviceId"))
			{
				std::string device_id_importa = jsonData["DeviceId"].get<std::string>();
				if (!device_id_importa.empty())
				{
					tuningFanSettings.DeviceId = device_id_importa;
				}
			}
		}
		catch (...) {}
		return tuningFanSettings;
	}

	nlohmann::json MainPage::Generate_TuningFanSettings(TuningFanSettings tuningFanSettings)
	{
		nlohmann::json jsonData{};
		try
		{
			//Set settings values
			jsonData["DeviceId"] = tuningFanSettings.DeviceId;
			jsonData["CoreMin"] = tuningFanSettings.CoreMin;
			jsonData["CoreMax"] = tuningFanSettings.CoreMax;
			jsonData["MemoryTiming"] = tuningFanSettings.MemoryTiming;
			jsonData["MemoryMax"] = tuningFanSettings.MemoryMax;
			jsonData["PowerLimit"] = tuningFanSettings.PowerLimit;
			jsonData["PowerVoltage"] = tuningFanSettings.PowerVoltage;
			jsonData["PowerTDC"] = tuningFanSettings.PowerTDC;
			jsonData["FanZeroRpm"] = tuningFanSettings.FanZeroRpm;
			jsonData["FanSpeed0"] = tuningFanSettings.FanSpeed0;
			jsonData["FanTemp0"] = tuningFanSettings.FanTemp0;
			jsonData["FanSpeed1"] = tuningFanSettings.FanSpeed1;
			jsonData["FanTemp1"] = tuningFanSettings.FanTemp1;
			jsonData["FanSpeed2"] = tuningFanSettings.FanSpeed2;
			jsonData["FanTemp2"] = tuningFanSettings.FanTemp2;
			jsonData["FanSpeed3"] = tuningFanSettings.FanSpeed3;
			jsonData["FanTemp3"] = tuningFanSettings.FanTemp3;
			jsonData["FanSpeed4"] = tuningFanSettings.FanSpeed4;
			jsonData["FanTemp4"] = tuningFanSettings.FanTemp4;
		}
		catch (...) {}
		return jsonData;
	}

	void MainPage::button_Tuning_Apply_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Generate tuning and fans settings
			TuningFanSettings tuningFanSettings = Generate_TuningFanSettings();

			//Apply tuning and fans settings
			adlx_Bool = AdlxApplyTuning(tuningFanSettings);
			if (adlx_Bool)
			{
				AdlxValuesLoadSelectGpu();
			}
		}
		catch (...) {}
	}

	void MainPage::button_Tuning_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			adlx_Bool = AdlxResetTuning();
			if (adlx_Bool)
			{
				AdlxValuesLoadSelectGpu();
			}
		}
		catch (...) {}
	}

	void MainPage::button_Tuning_Import_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Import settings from file
			AdlxValuesImport();
		}
		catch (...) {}
	}

	void MainPage::button_Tuning_Export_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Export current settings to file
			AdlxValuesExport();
		}
		catch (...) {}
	}

	void MainPage::button_Tuning_Keep_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Get active overclock file path
			std::wstring pathSettingFileW = PathMerge(PathGetExecutableDirectory(), L"ActiveOverclock.json");
			std::string pathSettingFileA = wstring_to_string(pathSettingFileW);

			//Export current settings to file
			AdlxValuesExport(pathSettingFileA);
		}
		catch (...) {}
	}

	bool MainPage::AdlxApplyTuning(TuningFanSettings tuningFanSettings)
	{
		try
		{
			//Get fan manual tuning
			adlx_Res0 = ppGPUTuningServices->IsSupportedManualFanTuning(ppGpuInfo, &adlx_Bool);
			if (adlx_Bool)
			{
				IADLXManualFanTuningPtr ppManualFanTuning;
				adlx_Res0 = ppGPUTuningServices->GetManualFanTuning(ppGpuInfo, (IADLXInterface**)&ppManualFanTuning);

				//Set fan zero rpm setting
				adlx_Res0 = ppManualFanTuning->IsSupportedZeroRPM(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = ppManualFanTuning->SetZeroRPMState(tuningFanSettings.FanZeroRpm);
				}

				//Get empty fan curve
				IADLXManualFanTuningStatePtr ppFanState;
				IADLXManualFanTuningStateListPtr ppFanStates;
				adlx_Res0 = ppManualFanTuning->GetEmptyFanTuningStates(&ppFanStates);
				for (UINT i = 0; i < ppFanStates->Size(); i++)
				{
					ppFanStates->At(i, &ppFanState);
					if (i == 0)
					{
						ppFanState->SetFanSpeed(tuningFanSettings.FanSpeed0);
						ppFanState->SetTemperature(tuningFanSettings.FanTemp0);
					}
					else if (i == 1)
					{
						ppFanState->SetFanSpeed(tuningFanSettings.FanSpeed1);
						ppFanState->SetTemperature(tuningFanSettings.FanTemp1);
					}
					else if (i == 2)
					{
						ppFanState->SetFanSpeed(tuningFanSettings.FanSpeed2);
						ppFanState->SetTemperature(tuningFanSettings.FanTemp2);
					}
					else if (i == 3)
					{
						ppFanState->SetFanSpeed(tuningFanSettings.FanSpeed3);
						ppFanState->SetTemperature(tuningFanSettings.FanTemp3);
					}
					else if (i == 4)
					{
						ppFanState->SetFanSpeed(tuningFanSettings.FanSpeed4);
						ppFanState->SetTemperature(tuningFanSettings.FanTemp4);
					}
				}

				//Validate fan curve
				adlx_Res0 = ppManualFanTuning->IsValidFanTuningStates(ppFanStates, &adlx_Int0);
				if (ADLX_FAILED(adlx_Res0))
				{
					//Set result
					textblock_Status().Text(L"Invalid fan curve");
					AVDebugWriteLine(L"Invalid fan curve");
					return false;
				}

				//Set fan curve
				adlx_Res0 = ppManualFanTuning->SetFanTuningStates(ppFanStates);
			}

			//Get gpu manual tuning
			adlx_Res0 = ppGPUTuningServices->IsSupportedManualGFXTuning(ppGpuInfo, &adlx_Bool);
			if (adlx_Bool)
			{
				IADLXManualGraphicsTuning2Ptr ppManualGFXTuning;
				adlx_Res0 = ppGPUTuningServices->GetManualGFXTuning(ppGpuInfo, (IADLXInterface**)&ppManualGFXTuning);
				adlx_Res0 = ppManualGFXTuning->SetGPUMinFrequency(tuningFanSettings.CoreMin);
				adlx_Res0 = ppManualGFXTuning->SetGPUMaxFrequency(tuningFanSettings.CoreMax);
				adlx_Res0 = ppManualGFXTuning->SetGPUVoltage(tuningFanSettings.PowerVoltage);
			}

			//Get memory manual tuning
			adlx_Res0 = ppGPUTuningServices->IsSupportedManualVRAMTuning(ppGpuInfo, &adlx_Bool);
			if (adlx_Bool)
			{
				IADLXManualVRAMTuning2Ptr ppManualVRAMTuning;
				adlx_Res0 = ppGPUTuningServices->GetManualVRAMTuning(ppGpuInfo, (IADLXInterface**)&ppManualVRAMTuning);
				adlx_Res0 = ppManualVRAMTuning->SetMaxVRAMFrequency(tuningFanSettings.MemoryMax);

				adlx_Res0 = ppManualVRAMTuning->IsSupportedMemoryTiming(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = ppManualVRAMTuning->SetMemoryTimingDescription((ADLX_MEMORYTIMING_DESCRIPTION)tuningFanSettings.MemoryTiming);
				}
			}

			//Get power manual tuning
			adlx_Res0 = ppGPUTuningServices->IsSupportedManualPowerTuning(ppGpuInfo, &adlx_Bool);
			if (adlx_Bool)
			{
				IADLXManualPowerTuning1Ptr ppManualPowerTuning;
				adlx_Res0 = ppGPUTuningServices->GetManualPowerTuning(ppGpuInfo, (IADLXInterface**)&ppManualPowerTuning);
				adlx_Res0 = ppManualPowerTuning->SetPowerLimit(tuningFanSettings.PowerLimit);

				adlx_Res0 = ppManualPowerTuning->IsSupportedTDCLimit(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = ppManualPowerTuning->SetTDCLimit(tuningFanSettings.PowerTDC);
				}
			}

			//Set result
			textblock_Status().Text(L"Tuning and fans applied");
			AVDebugWriteLine(L"Tuning and fans applied");
			return true;
		}
		catch (...)
		{
			//Set result
			textblock_Status().Text(L"Failed applying tuning and fans");
			AVDebugWriteLine(L"Failed applying tuning and fans");
			return false;
		}
	}
}