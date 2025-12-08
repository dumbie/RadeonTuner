#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	//Load TuningFanSettings from file
	TuningFanSettings MainPage::TuningFanSettings_Load(std::string loadPath)
	{
		try
		{
			//Open settings file
			std::string jsonString = file_to_string(loadPath);

			//Parse settings file
			nlohmann::json jsonData = nlohmann::json::parse(jsonString);

			//Convert json to tuning fan settings
			return TuningFanSettings_Generate_FromJson(jsonData);
		}
		catch (...) {}
		return TuningFanSettings{};
	}

	//Save TuningFanSettings to file
	bool MainPage::TuningFanSettings_Save(TuningFanSettings tuningFanSettings, std::string savePath)
	{
		try
		{
			//Convert tuning fan settings
			nlohmann::json jsonData = TuningFanSettings_Convert_ToJson(tuningFanSettings);

			//Convert json to string
			std::string jsonString = jsonData.dump();

			//Save settings file
			return string_to_file(savePath, jsonString);
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	bool MainPage::TuningFanSettings_Convert_ToUI(TuningFanSettings tuningFanSettings, bool ignoreKeepActive)
	{
		try
		{
			if (!ignoreKeepActive && tuningFanSettings.KeepActive.has_value())
			{
				if (tuningFanSettings.KeepActive.value())
				{
					//Set button color
					SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
					button_Fan_Keep().Background(colorValid);
					button_Tuning_Keep().Background(colorValid);
				}
				else
				{
					//Set button color
					SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
					button_Fan_Keep().Background(colorInvalid);
					button_Tuning_Keep().Background(colorInvalid);
				}
			}
			if (tuningFanSettings.CoreMin.has_value())
			{
				slider_Core_Min().Value(tuningFanSettings.CoreMin.value());
			}
			if (tuningFanSettings.CoreMax.has_value())
			{
				slider_Core_Max().Value(tuningFanSettings.CoreMax.value());
			}
			if (tuningFanSettings.MemoryMax.has_value())
			{
				slider_Memory_Max().Value(tuningFanSettings.MemoryMax.value());
			}
			if (tuningFanSettings.MemoryTiming.has_value())
			{
				combobox_Memory_Timing().SelectedIndex(tuningFanSettings.MemoryTiming.value());
			}
			if (tuningFanSettings.PowerLimit.has_value())
			{
				slider_Power_Limit().Value(tuningFanSettings.PowerLimit.value());
			}
			if (tuningFanSettings.PowerVoltage.has_value())
			{
				slider_Power_Voltage().Value(tuningFanSettings.PowerVoltage.value());
			}
			if (tuningFanSettings.PowerTDC.has_value())
			{
				slider_Power_TDC().Value(tuningFanSettings.PowerTDC.value());
			}
			if (tuningFanSettings.FanZeroRpm.has_value())
			{
				toggleswitch_Fan_Zero_Rpm().IsOn(tuningFanSettings.FanZeroRpm.value());
			}
			if (tuningFanSettings.FanSpeed0.has_value())
			{
				slider_Fan_Speed_0().Value(tuningFanSettings.FanSpeed0.value());
			}
			if (tuningFanSettings.FanTemp0.has_value())
			{
				slider_Fan_Temp_0().Value(tuningFanSettings.FanTemp0.value());
			}
			if (tuningFanSettings.FanSpeed1.has_value())
			{
				slider_Fan_Speed_1().Value(tuningFanSettings.FanSpeed1.value());
			}
			if (tuningFanSettings.FanTemp1.has_value())
			{
				slider_Fan_Temp_1().Value(tuningFanSettings.FanTemp1.value());
			}
			if (tuningFanSettings.FanSpeed2.has_value())
			{
				slider_Fan_Speed_2().Value(tuningFanSettings.FanSpeed2.value());
			}
			if (tuningFanSettings.FanTemp2.has_value())
			{
				slider_Fan_Temp_2().Value(tuningFanSettings.FanTemp2.value());
			}
			if (tuningFanSettings.FanSpeed3.has_value())
			{
				slider_Fan_Speed_3().Value(tuningFanSettings.FanSpeed3.value());
			}
			if (tuningFanSettings.FanTemp3.has_value())
			{
				slider_Fan_Temp_3().Value(tuningFanSettings.FanTemp3.value());
			}
			if (tuningFanSettings.FanSpeed4.has_value())
			{
				slider_Fan_Speed_4().Value(tuningFanSettings.FanSpeed4.value());
			}
			if (tuningFanSettings.FanTemp4.has_value())
			{
				slider_Fan_Temp_4().Value(tuningFanSettings.FanTemp4.value());
			}

			//Return result
			return true;
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	TuningFanSettings MainPage::TuningFanSettings_Generate_FromAdlxGpuPtr(IADLXGPU2Ptr ppGpuPtr)
	{
		TuningFanSettings tuningFanSettings{};
		try
		{
			//Device identifier
			std::wstring device_id_w = AdlxGetDeviceIdentifier(ppGpuPtr);
			if (!device_id_w.empty())
			{
				tuningFanSettings.DeviceId = wstring_to_string(device_id_w);
			}

			//Check manual support
			try
			{
				adlx_Res0 = ppGPUTuningServices->IsSupportedManualGFXTuning(ppGpuPtr, &adlx_Bool);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.SupportManualGPU = adlx_Bool;
				}
				else
				{
					tuningFanSettings.SupportManualGPU = false;
				}

				adlx_Res0 = ppGPUTuningServices->IsSupportedManualVRAMTuning(ppGpuPtr, &adlx_Bool);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.SupportManualVRAM = adlx_Bool;
				}
				else
				{
					tuningFanSettings.SupportManualVRAM = false;
				}

				adlx_Res0 = ppGPUTuningServices->IsSupportedManualPowerTuning(ppGpuPtr, &adlx_Bool);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.SupportManualPower = adlx_Bool;
				}
				else
				{
					tuningFanSettings.SupportManualPower = false;
				}

				adlx_Res0 = ppGPUTuningServices->IsSupportedManualFanTuning(ppGpuPtr, &adlx_Bool);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.SupportManualFAN = adlx_Bool;
				}
				else
				{
					tuningFanSettings.SupportManualFAN = false;
				}
			}
			catch (...)
			{
				AVDebugWriteLine("Failed to generate tuning support settings.");
			}

			//Note: some gpus seem to return ADLX_NOT_SUPPORTED when reading returning invalid 0 or 1 values

			//Get gpu manual tuning
			try
			{
				IADLXManualGraphicsTuning2Ptr ppManualGFXTuning;
				adlx_Res0 = ppGPUTuningServices->GetManualGFXTuning(ppGpuPtr, (IADLXInterface**)&ppManualGFXTuning);

				//Get gpu frequency setting
				adlx_Res0 = ppManualGFXTuning->GetGPUMinFrequencyRange(&adlx_IntRange0);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.CoreMinMin = adlx_IntRange0.minValue;
					tuningFanSettings.CoreMinMax = adlx_IntRange0.maxValue;
					tuningFanSettings.CoreMinStep = adlx_IntRange0.step;
				}

				adlx_Res0 = ppManualGFXTuning->GetGPUMinFrequency(&adlx_Int0);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.CoreMin = adlx_Int0;
				}

				adlx_Res0 = ppManualGFXTuning->GetGPUMaxFrequencyRange(&adlx_IntRange0);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.CoreMaxMin = adlx_IntRange0.minValue;
					tuningFanSettings.CoreMaxMax = adlx_IntRange0.maxValue;
					tuningFanSettings.CoreMaxStep = adlx_IntRange0.step;
				}

				adlx_Res0 = ppManualGFXTuning->GetGPUMaxFrequency(&adlx_Int0);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.CoreMax = adlx_Int0;
				}

				//Get gpu voltage setting
				adlx_Res0 = ppManualGFXTuning->GetGPUVoltageRange(&adlx_IntRange0);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.PowerVoltageMin = adlx_IntRange0.minValue;
					tuningFanSettings.PowerVoltageMax = adlx_IntRange0.maxValue;
					tuningFanSettings.PowerVoltageStep = adlx_IntRange0.step;
				}

				adlx_Res0 = ppManualGFXTuning->GetGPUVoltage(&adlx_Int0);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.PowerVoltage = adlx_Int0;
				}
			}
			catch (...)
			{
				AVDebugWriteLine("Failed to generate tuning gpu settings.");
			}

			//Get memory manual tuning
			try
			{
				IADLXManualVRAMTuning2Ptr ppManualVRAMTuning;
				adlx_Res0 = ppGPUTuningServices->GetManualVRAMTuning(ppGpuPtr, (IADLXInterface**)&ppManualVRAMTuning);

				//Get memory frequency setting
				adlx_Res0 = ppManualVRAMTuning->GetMaxVRAMFrequencyRange(&adlx_IntRange0);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.MemoryMaxMin = adlx_IntRange0.minValue;
					tuningFanSettings.MemoryMaxMax = adlx_IntRange0.maxValue;
					tuningFanSettings.MemoryMaxStep = adlx_IntRange0.step;
				}

				adlx_Res0 = ppManualVRAMTuning->GetMaxVRAMFrequency(&adlx_Int0);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.MemoryMax = adlx_Int0;
				}

				//Get memory timing settting
				adlx_Res0 = ppManualVRAMTuning->IsSupportedMemoryTiming(&adlx_Bool);
				if (ADLX_SUCCEEDED(adlx_Res0) && adlx_Bool)
				{
					ADLX_MEMORYTIMING_DESCRIPTION memoryTimingDescription;
					adlx_Res0 = ppManualVRAMTuning->GetMemoryTimingDescription(&memoryTimingDescription);
					if (ADLX_SUCCEEDED(adlx_Res0))
					{
						tuningFanSettings.MemoryTiming = memoryTimingDescription;
					}
				}
			}
			catch (...)
			{
				AVDebugWriteLine("Failed to generate tuning memory settings.");
			}

			//Get power manual tuning
			try
			{
				IADLXManualPowerTuning1Ptr ppManualPowerTuning;
				adlx_Res0 = ppGPUTuningServices->GetManualPowerTuning(ppGpuPtr, (IADLXInterface**)&ppManualPowerTuning);

				//Get power limit setting
				adlx_Res0 = ppManualPowerTuning->GetPowerLimitRange(&adlx_IntRange0);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.PowerLimitMin = adlx_IntRange0.minValue;
					tuningFanSettings.PowerLimitMax = adlx_IntRange0.maxValue;
					tuningFanSettings.PowerLimitStep = adlx_IntRange0.step;
				}

				adlx_Res0 = ppManualPowerTuning->GetPowerLimit(&adlx_Int0);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.PowerLimit = adlx_Int0;
				}

				//Get power tdc setting
				adlx_Res0 = ppManualPowerTuning->IsSupportedTDCLimit(&adlx_Bool);
				if (ADLX_SUCCEEDED(adlx_Res0) && adlx_Bool)
				{
					adlx_Res0 = ppManualPowerTuning->GetTDCLimitRange(&adlx_IntRange0);
					if (ADLX_SUCCEEDED(adlx_Res0))
					{
						tuningFanSettings.PowerTDCMin = adlx_IntRange0.minValue;
						tuningFanSettings.PowerTDCMax = adlx_IntRange0.maxValue;
						tuningFanSettings.PowerTDCStep = adlx_IntRange0.step;
					}

					adlx_Res0 = ppManualPowerTuning->GetTDCLimit(&adlx_Int0);
					if (ADLX_SUCCEEDED(adlx_Res0))
					{
						tuningFanSettings.PowerTDC = adlx_Int0;
					}
				}
			}
			catch (...)
			{
				AVDebugWriteLine("Failed to generate tuning power settings.");
			}

			//Get fan manual tuning
			try
			{
				IADLXManualFanTuningPtr ppManualFanTuning;
				adlx_Res0 = ppGPUTuningServices->GetManualFanTuning(ppGpuPtr, (IADLXInterface**)&ppManualFanTuning);

				//Get fan zero rpm setting
				adlx_Res0 = ppManualFanTuning->IsSupportedZeroRPM(&adlx_Bool);
				if (ADLX_SUCCEEDED(adlx_Res0) && adlx_Bool)
				{
					adlx_Res0 = ppManualFanTuning->GetZeroRPMState(&adlx_Bool);
					if (ADLX_SUCCEEDED(adlx_Res0))
					{
						tuningFanSettings.FanZeroRpm = adlx_Bool;
					}
				}

				//Get fan range setting
				adlx_Res0 = ppManualFanTuning->GetFanTuningRanges(&adlx_IntRange0, &adlx_IntRange1);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.FanSpeedMin0 = adlx_IntRange0.minValue;
					tuningFanSettings.FanSpeedMax0 = adlx_IntRange0.maxValue;
					tuningFanSettings.FanSpeedStep0 = adlx_IntRange0.step;
					tuningFanSettings.FanTempMin0 = adlx_IntRange1.minValue;
					tuningFanSettings.FanTempMax0 = adlx_IntRange1.maxValue;
					tuningFanSettings.FanTempStep0 = adlx_IntRange1.step;

					tuningFanSettings.FanSpeedMin1 = adlx_IntRange0.minValue;
					tuningFanSettings.FanSpeedMax1 = adlx_IntRange0.maxValue;
					tuningFanSettings.FanSpeedStep1 = adlx_IntRange0.step;
					tuningFanSettings.FanTempMin1 = adlx_IntRange1.minValue;
					tuningFanSettings.FanTempMax1 = adlx_IntRange1.maxValue;
					tuningFanSettings.FanTempStep1 = adlx_IntRange1.step;

					tuningFanSettings.FanSpeedMin2 = adlx_IntRange0.minValue;
					tuningFanSettings.FanSpeedMax2 = adlx_IntRange0.maxValue;
					tuningFanSettings.FanSpeedStep2 = adlx_IntRange0.step;
					tuningFanSettings.FanTempMin2 = adlx_IntRange1.minValue;
					tuningFanSettings.FanTempMax2 = adlx_IntRange1.maxValue;
					tuningFanSettings.FanTempStep2 = adlx_IntRange1.step;

					tuningFanSettings.FanSpeedMin3 = adlx_IntRange0.minValue;
					tuningFanSettings.FanSpeedMax3 = adlx_IntRange0.maxValue;
					tuningFanSettings.FanSpeedStep3 = adlx_IntRange0.step;
					tuningFanSettings.FanTempMin3 = adlx_IntRange1.minValue;
					tuningFanSettings.FanTempMax3 = adlx_IntRange1.maxValue;
					tuningFanSettings.FanTempStep3 = adlx_IntRange1.step;

					tuningFanSettings.FanSpeedMin4 = adlx_IntRange0.minValue;
					tuningFanSettings.FanSpeedMax4 = adlx_IntRange0.maxValue;
					tuningFanSettings.FanSpeedStep4 = adlx_IntRange0.step;
					tuningFanSettings.FanTempMin4 = adlx_IntRange1.minValue;
					tuningFanSettings.FanTempMax4 = adlx_IntRange1.maxValue;
					tuningFanSettings.FanTempStep4 = adlx_IntRange1.step;
				}

				//Get fan curve setting
				IADLXManualFanTuningStatePtr ppFanState;
				IADLXManualFanTuningStateListPtr ppFanStates;
				adlx_Res0 = ppManualFanTuning->GetFanTuningStates(&ppFanStates);

				//Fan Zero
				ppFanStates->At(0, &ppFanState);
				adlx_Res0 = ppFanState->GetFanSpeed(&adlx_Int0);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.FanSpeed0 = adlx_Int0;
				}
				adlx_Res0 = ppFanState->GetTemperature(&adlx_Int0);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.FanTemp0 = adlx_Int0;
				}

				ppFanStates->At(1, &ppFanState);
				adlx_Res0 = ppFanState->GetFanSpeed(&adlx_Int0);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.FanSpeed1 = adlx_Int0;
				}
				adlx_Res0 = ppFanState->GetTemperature(&adlx_Int0);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.FanTemp1 = adlx_Int0;
				}

				ppFanStates->At(2, &ppFanState);
				adlx_Res0 = ppFanState->GetFanSpeed(&adlx_Int0);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.FanSpeed2 = adlx_Int0;
				}
				adlx_Res0 = ppFanState->GetTemperature(&adlx_Int0);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.FanTemp2 = adlx_Int0;
				}

				ppFanStates->At(3, &ppFanState);
				adlx_Res0 = ppFanState->GetFanSpeed(&adlx_Int0);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.FanSpeed3 = adlx_Int0;
				}
				adlx_Res0 = ppFanState->GetTemperature(&adlx_Int0);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.FanTemp3 = adlx_Int0;
				}

				ppFanStates->At(4, &ppFanState);
				adlx_Res0 = ppFanState->GetFanSpeed(&adlx_Int0);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.FanSpeed4 = adlx_Int0;
				}
				adlx_Res0 = ppFanState->GetTemperature(&adlx_Int0);
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					tuningFanSettings.FanTemp4 = adlx_Int0;
				}
			}
			catch (...)
			{
				AVDebugWriteLine("Failed to generate tuning fan settings.");
			}
		}
		catch (...)
		{
			AVDebugWriteLine("Failed to generate tuning and fan settings from adlx GPU ptr.");
		}
		return tuningFanSettings;
	}

	TuningFanSettings MainPage::TuningFanSettings_Generate_FromUI(bool keepActive)
	{
		TuningFanSettings tuningFanSettings{};
		try
		{
			//Device identifier
			std::wstring device_id_w = AdlxGetDeviceIdentifier(ppGpuInfo);
			if (!device_id_w.empty())
			{
				tuningFanSettings.DeviceId = wstring_to_string(device_id_w);
			}

			//Keep active
			tuningFanSettings.KeepActive = keepActive;

			if (slider_Core_Min().IsEnabled())
			{
				tuningFanSettings.CoreMin = (int)slider_Core_Min().Value();
			}
			if (slider_Core_Max().IsEnabled())
			{
				tuningFanSettings.CoreMax = (int)slider_Core_Max().Value();
			}
			if (slider_Memory_Max().IsEnabled())
			{
				tuningFanSettings.MemoryMax = (int)slider_Memory_Max().Value();
			}
			if (combobox_Memory_Timing().IsEnabled())
			{
				tuningFanSettings.MemoryTiming = (int)combobox_Memory_Timing().SelectedIndex();
			}
			if (slider_Power_Limit().IsEnabled())
			{
				tuningFanSettings.PowerLimit = (int)slider_Power_Limit().Value();
			}
			if (slider_Power_Voltage().IsEnabled())
			{
				tuningFanSettings.PowerVoltage = (int)slider_Power_Voltage().Value();
			}
			if (slider_Power_TDC().IsEnabled())
			{
				tuningFanSettings.PowerTDC = (int)slider_Power_TDC().Value();
			}
			if (toggleswitch_Fan_Zero_Rpm().IsEnabled())
			{
				tuningFanSettings.FanZeroRpm = (bool)toggleswitch_Fan_Zero_Rpm().IsOn();
			}
			if (slider_Fan_Speed_0().IsEnabled())
			{
				tuningFanSettings.FanSpeed0 = (int)slider_Fan_Speed_0().Value();
			}
			if (slider_Fan_Temp_0().IsEnabled())
			{
				tuningFanSettings.FanTemp0 = (int)slider_Fan_Temp_0().Value();
			}
			if (slider_Fan_Speed_1().IsEnabled())
			{
				tuningFanSettings.FanSpeed1 = (int)slider_Fan_Speed_1().Value();
			}
			if (slider_Fan_Temp_1().IsEnabled())
			{
				tuningFanSettings.FanTemp1 = (int)slider_Fan_Temp_1().Value();
			}
			if (slider_Fan_Speed_2().IsEnabled())
			{
				tuningFanSettings.FanSpeed2 = (int)slider_Fan_Speed_2().Value();
			}
			if (slider_Fan_Temp_2().IsEnabled())
			{
				tuningFanSettings.FanTemp2 = (int)slider_Fan_Temp_2().Value();
			}
			if (slider_Fan_Speed_3().IsEnabled())
			{
				tuningFanSettings.FanSpeed3 = (int)slider_Fan_Speed_3().Value();
			}
			if (slider_Fan_Temp_3().IsEnabled())
			{
				tuningFanSettings.FanTemp3 = (int)slider_Fan_Temp_3().Value();
			}
			if (slider_Fan_Speed_4().IsEnabled())
			{
				tuningFanSettings.FanSpeed4 = (int)slider_Fan_Speed_4().Value();
			}
			if (slider_Fan_Temp_4().IsEnabled())
			{
				tuningFanSettings.FanTemp4 = (int)slider_Fan_Temp_4().Value();
			}
		}
		catch (...) {}
		return tuningFanSettings;
	}

	TuningFanSettings MainPage::TuningFanSettings_Generate_FromJson(nlohmann::json jsonData)
	{
		TuningFanSettings tuningFanSettings{};
		try
		{
			if (jsonData.contains("DeviceId"))
			{
				std::string device_id_importa = jsonData["DeviceId"].get<std::string>();
				if (!device_id_importa.empty())
				{
					tuningFanSettings.DeviceId = device_id_importa;
				}
			}
			if (jsonData.contains("KeepActive"))
			{
				tuningFanSettings.KeepActive = (bool)jsonData["KeepActive"];
			}
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
		}
		catch (...) {}
		return tuningFanSettings;
	}

	nlohmann::json MainPage::TuningFanSettings_Convert_ToJson(TuningFanSettings tuningFanSettings)
	{
		nlohmann::json jsonData{};
		try
		{
			if (tuningFanSettings.DeviceId.has_value())
			{
				jsonData["DeviceId"] = tuningFanSettings.DeviceId.value();
			}
			if (tuningFanSettings.KeepActive.has_value())
			{
				jsonData["KeepActive"] = tuningFanSettings.KeepActive.value();
			}
			if (tuningFanSettings.CoreMin.has_value())
			{
				jsonData["CoreMin"] = tuningFanSettings.CoreMin.value();
			}
			if (tuningFanSettings.CoreMax.has_value())
			{
				jsonData["CoreMax"] = tuningFanSettings.CoreMax.value();
			}
			if (tuningFanSettings.MemoryTiming.has_value())
			{
				jsonData["MemoryTiming"] = tuningFanSettings.MemoryTiming.value();
			}
			if (tuningFanSettings.MemoryMax.has_value())
			{
				jsonData["MemoryMax"] = tuningFanSettings.MemoryMax.value();
			}
			if (tuningFanSettings.PowerLimit.has_value())
			{
				jsonData["PowerLimit"] = tuningFanSettings.PowerLimit.value();
			}
			if (tuningFanSettings.PowerVoltage.has_value())
			{
				jsonData["PowerVoltage"] = tuningFanSettings.PowerVoltage.value();
			}
			if (tuningFanSettings.PowerTDC.has_value())
			{
				jsonData["PowerTDC"] = tuningFanSettings.PowerTDC.value();
			}
			if (tuningFanSettings.FanZeroRpm.has_value())
			{
				jsonData["FanZeroRpm"] = tuningFanSettings.FanZeroRpm.value();
			}
			if (tuningFanSettings.FanSpeed0.has_value())
			{
				jsonData["FanSpeed0"] = tuningFanSettings.FanSpeed0.value();
			}
			if (tuningFanSettings.FanTemp0.has_value())
			{
				jsonData["FanTemp0"] = tuningFanSettings.FanTemp0.value();
			}
			if (tuningFanSettings.FanSpeed1.has_value())
			{
				jsonData["FanSpeed1"] = tuningFanSettings.FanSpeed1.value();
			}
			if (tuningFanSettings.FanTemp1.has_value())
			{
				jsonData["FanTemp1"] = tuningFanSettings.FanTemp1.value();
			}
			if (tuningFanSettings.FanSpeed2.has_value())
			{
				jsonData["FanSpeed2"] = tuningFanSettings.FanSpeed2.value();
			}
			if (tuningFanSettings.FanTemp2.has_value())
			{
				jsonData["FanTemp2"] = tuningFanSettings.FanTemp2.value();
			}
			if (tuningFanSettings.FanSpeed3.has_value())
			{
				jsonData["FanSpeed3"] = tuningFanSettings.FanSpeed3.value();
			}
			if (tuningFanSettings.FanTemp3.has_value())
			{
				jsonData["FanTemp3"] = tuningFanSettings.FanTemp3.value();
			}
			if (tuningFanSettings.FanSpeed4.has_value())
			{
				jsonData["FanSpeed4"] = tuningFanSettings.FanSpeed4.value();
			}
			if (tuningFanSettings.FanTemp4.has_value())
			{
				jsonData["FanTemp4"] = tuningFanSettings.FanTemp4.value();
			}
		}
		catch (...) {}
		return jsonData;
	}
}