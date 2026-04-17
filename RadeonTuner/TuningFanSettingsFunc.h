#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::TuningFanSettings_Profile_Convert_ToUI(TuningFanSettings tuningFanSettings)
	{
		try
		{
			//Gpu Core Minimum
			if (tuningFanSettings.CoreMin.has_value())
			{
				slider_Core_Min().Value(tuningFanSettings.CoreMin.value());
			}

			//Gpu Core Maximum
			if (tuningFanSettings.CoreMax.has_value())
			{
				slider_Core_Max().Value(tuningFanSettings.CoreMax.value());
			}

			//Memory timing
			if (tuningFanSettings.MemoryTiming.has_value())
			{
				combobox_Memory_Timing().SelectedIndex(tuningFanSettings.MemoryTiming.value());
			}

			//Memory frequency
			if (tuningFanSettings.MemoryMax.has_value())
			{
				slider_Memory_Max().Value(tuningFanSettings.MemoryMax.value());
			}

			//Power limit
			if (tuningFanSettings.PowerLimit.has_value())
			{
				slider_Power_Limit().Value(tuningFanSettings.PowerLimit.value());
			}

			//Power voltage
			if (tuningFanSettings.PowerVoltage.has_value())
			{
				slider_Power_Voltage().Value(tuningFanSettings.PowerVoltage.value());
			}

			//Power TDC
			if (tuningFanSettings.PowerTDC.has_value())
			{
				slider_Power_TDC().Value(tuningFanSettings.PowerTDC.value());
			}

			//Fan Zero RPM
			if (tuningFanSettings.FanZeroRpm.has_value())
			{
				toggleswitch_Fan_Zero_Rpm().IsOn(tuningFanSettings.FanZeroRpm.value());
			}

			//Fan Speed 0
			if (tuningFanSettings.FanSpeed0.has_value())
			{
				slider_Fan_Speed_0().Value(tuningFanSettings.FanSpeed0.value());
			}

			//Fan Temperature 0
			if (tuningFanSettings.FanTemp0.has_value())
			{
				slider_Fan_Temp_0().Value(tuningFanSettings.FanTemp0.value());
			}

			//Fan Speed 1
			if (tuningFanSettings.FanSpeed1.has_value())
			{
				slider_Fan_Speed_1().Value(tuningFanSettings.FanSpeed1.value());
			}

			//Fan Temperature 1
			if (tuningFanSettings.FanTemp1.has_value())
			{
				slider_Fan_Temp_1().Value(tuningFanSettings.FanTemp1.value());
			}

			//Fan Speed 2
			if (tuningFanSettings.FanSpeed2.has_value())
			{
				slider_Fan_Speed_2().Value(tuningFanSettings.FanSpeed2.value());
			}

			//Fan Temperature 2
			if (tuningFanSettings.FanTemp2.has_value())
			{
				slider_Fan_Temp_2().Value(tuningFanSettings.FanTemp2.value());
			}

			//Fan Speed 3
			if (tuningFanSettings.FanSpeed3.has_value())
			{
				slider_Fan_Speed_3().Value(tuningFanSettings.FanSpeed3.value());
			}

			//Fan Temperature 3
			if (tuningFanSettings.FanTemp3.has_value())
			{
				slider_Fan_Temp_3().Value(tuningFanSettings.FanTemp3.value());
			}

			//Fan Speed 4
			if (tuningFanSettings.FanSpeed4.has_value())
			{
				slider_Fan_Speed_4().Value(tuningFanSettings.FanSpeed4.value());
			}

			//Fan Temperature 4
			if (tuningFanSettings.FanTemp4.has_value())
			{
				slider_Fan_Temp_4().Value(tuningFanSettings.FanTemp4.value());
			}

			//Load keep active setting
			if (tuningFanSettings.KeepActive.has_value())
			{
				toggleswitch_KeepActive().IsOn(tuningFanSettings.KeepActive.value());
			}
			else
			{
				toggleswitch_KeepActive().IsOn(false);
			}

			//Load power boost setting
			if (tuningFanSettings.PowerBoost.has_value())
			{
				bool powerBoost = tuningFanSettings.PowerBoost.value();
				toggleswitch_PowerBoost().IsOn(powerBoost);

				//Show or hide power boost settings
				if (powerBoost)
				{
					//Hide or show settings
					grid_Power_Limit_PB().Visibility(Visibility::Visible);
					grid_Power_Voltage_PB().Visibility(Visibility::Visible);
					grid_Power_TDC_PB().Visibility(Visibility::Visible);

					//Enable or disable settings
					combobox_PowerBoost_Applications().IsEnabled(true);
					button_PowerBoost_AddExe().IsEnabled(true);
					button_PowerBoost_Remove().IsEnabled(true);
				}
				else
				{
					//Hide or show settings
					grid_Power_Limit_PB().Visibility(Visibility::Collapsed);
					grid_Power_Voltage_PB().Visibility(Visibility::Collapsed);
					grid_Power_TDC_PB().Visibility(Visibility::Collapsed);

					//Enable or disable settings
					combobox_PowerBoost_Applications().IsEnabled(false);
					button_PowerBoost_AddExe().IsEnabled(false);
					button_PowerBoost_Remove().IsEnabled(false);
				}

				//Power limit (Power Boost)
				if (tuningFanSettings.PowerLimitPB.has_value())
				{
					slider_Power_Limit_PB().Value(tuningFanSettings.PowerLimitPB.value());
				}

				//Power voltage (Power Boost)
				if (tuningFanSettings.PowerVoltagePB.has_value())
				{
					slider_Power_Voltage_PB().Value(tuningFanSettings.PowerVoltagePB.value());
				}

				//Power TDC (Power Boost)
				if (tuningFanSettings.PowerTDCPB.has_value())
				{
					slider_Power_TDC_PB().Value(tuningFanSettings.PowerTDCPB.value());
				}
			}
			else
			{
				toggleswitch_PowerBoost().IsOn(false);
			}

			//Set result
			AVDebugWriteLine("Loaded profile tuning and fan settings.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed loading profile tuning and fan settings.");
		}
	}

	void MainPage::TuningFanSettings_GPU_Convert_ToUI(TuningFanSettings tuningFanSettings)
	{
		try
		{
			//Gpu Core Minimum
			if (tuningFanSettings.CoreMin.has_value())
			{
				//Set value text
				std::wstring valueText = number_to_wstring(tuningFanSettings.CoreMin.value()) + L"MHz";
				textblock_Core_Min_Value().Text(valueText);

				//Set setting limits
				if (tuningFanSettings.CoreMinMin.has_value())
				{
					slider_Core_Min().Minimum(tuningFanSettings.CoreMinMin.value());
					slider_Core_Min().Maximum(tuningFanSettings.CoreMinMax.value());
					slider_Core_Min().StepFrequency(tuningFanSettings.CoreMinStep.value());
					slider_Core_Min().SmallChange(tuningFanSettings.CoreMinStep.value());
				}

				//Enable or disable interface
				slider_Core_Min().IsEnabled(true);
			}
			else
			{
				//Set value text
				textblock_Core_Min_Value().Text(L"");

				//Enable or disable interface
				slider_Core_Min().IsEnabled(false);
			}

			//Gpu Core Maximum
			if (tuningFanSettings.CoreMax.has_value())
			{
				//Set value text
				std::wstring valueText = number_to_wstring(tuningFanSettings.CoreMax.value()) + L"MHz";
				textblock_Core_Max_Value().Text(valueText);

				//Set setting limits
				if (tuningFanSettings.CoreMaxMin.has_value())
				{
					slider_Core_Max().Minimum(tuningFanSettings.CoreMaxMin.value());
					slider_Core_Max().Maximum(tuningFanSettings.CoreMaxMax.value());
					slider_Core_Max().StepFrequency(tuningFanSettings.CoreMaxStep.value());
					slider_Core_Max().SmallChange(tuningFanSettings.CoreMaxStep.value());

					//Check if value is offset (RDNA4+)
					if (tuningFanSettings.CoreMaxMin.value() < 0)
					{
						textblock_Core_Max().Text(L"Maximum Frequency Offset");
					}
					else
					{
						textblock_Core_Max().Text(L"Maximum Frequency");
					}
				}

				//Enable or disable interface
				slider_Core_Max().IsEnabled(true);
			}
			else
			{
				//Set value text
				textblock_Core_Max_Value().Text(L"");

				//Enable or disable interface
				slider_Core_Max().IsEnabled(false);
			}

			//Memory timing
			if (tuningFanSettings.MemoryTiming.has_value())
			{
				//Set value text
				std::wstring valueText = ADLX_MEMORYTIMING_DESCRIPTION_STRING[tuningFanSettings.MemoryTiming.value()];
				textblock_Memory_Timing_Value().Text(valueText);

				//Enable or disable interface
				combobox_Memory_Timing().IsEnabled(true);
			}
			else
			{
				//Set value text
				textblock_Memory_Timing_Value().Text(L"");

				//Enable or disable interface
				combobox_Memory_Timing().IsEnabled(false);
			}

			//Memory frequency
			if (tuningFanSettings.MemoryMax.has_value())
			{
				//Set value text
				std::wstring valueText = number_to_wstring(tuningFanSettings.MemoryMax.value()) + L"MT/s";
				textblock_Memory_Max_Value().Text(valueText);

				//Set setting limits
				if (tuningFanSettings.MemoryMaxMin.has_value())
				{
					slider_Memory_Max().Minimum(tuningFanSettings.MemoryMaxMin.value());
					slider_Memory_Max().Maximum(tuningFanSettings.MemoryMaxMax.value());
					slider_Memory_Max().StepFrequency(tuningFanSettings.MemoryMaxStep.value());
					slider_Memory_Max().SmallChange(tuningFanSettings.MemoryMaxStep.value());
				}

				//Enable or disable interface
				slider_Memory_Max().IsEnabled(true);
			}
			else
			{
				//Set value text
				textblock_Memory_Max_Value().Text(L"");

				//Enable or disable interface
				slider_Memory_Max().IsEnabled(false);
			}

			//Power limit
			if (tuningFanSettings.PowerLimit.has_value())
			{
				//Set value text
				std::wstring valueText = number_to_wstring(tuningFanSettings.PowerLimit.value()) + L"%";
				textblock_Power_Limit_Value().Text(valueText);

				//Set setting limits
				if (tuningFanSettings.PowerLimitMin.has_value())
				{
					slider_Power_Limit().Minimum(tuningFanSettings.PowerLimitMin.value());
					slider_Power_Limit().Maximum(tuningFanSettings.PowerLimitMax.value());
					slider_Power_Limit().StepFrequency(tuningFanSettings.PowerLimitStep.value());
					slider_Power_Limit().SmallChange(tuningFanSettings.PowerLimitStep.value());
					slider_Power_Limit_PB().Minimum(tuningFanSettings.PowerLimitMin.value());
					slider_Power_Limit_PB().Maximum(tuningFanSettings.PowerLimitMax.value());
					slider_Power_Limit_PB().StepFrequency(tuningFanSettings.PowerLimitStep.value());
					slider_Power_Limit_PB().SmallChange(tuningFanSettings.PowerLimitStep.value());
				}

				//Enable or disable interface
				slider_Power_Limit().IsEnabled(true);
				slider_Power_Limit_PB().IsEnabled(true);
				toggleswitch_PowerBoost().IsEnabled(true);
				combobox_PowerBoost_Applications().IsEnabled(true);
				button_PowerBoost_AddExe().IsEnabled(true);
				button_PowerBoost_Remove().IsEnabled(true);
			}
			else
			{
				//Set value text
				textblock_Power_Limit_Value().Text(L"");

				//Enable or disable interface
				slider_Power_Limit().IsEnabled(false);
				slider_Power_Limit_PB().IsEnabled(false);
				toggleswitch_PowerBoost().IsEnabled(false);
				combobox_PowerBoost_Applications().IsEnabled(false);
				button_PowerBoost_AddExe().IsEnabled(false);
				button_PowerBoost_Remove().IsEnabled(false);
			}

			//Power voltage
			if (tuningFanSettings.PowerVoltage.has_value())
			{
				//Set value text
				std::wstring valueText = number_to_wstring(tuningFanSettings.PowerVoltage.value()) + L"mV";
				textblock_Power_Voltage_Value().Text(valueText);

				//Set setting limits
				if (tuningFanSettings.PowerVoltageMin.has_value())
				{
					slider_Power_Voltage().Minimum(tuningFanSettings.PowerVoltageMin.value());
					slider_Power_Voltage().Maximum(tuningFanSettings.PowerVoltageMax.value());
					slider_Power_Voltage().StepFrequency(tuningFanSettings.PowerVoltageStep.value());
					slider_Power_Voltage().SmallChange(tuningFanSettings.PowerVoltageStep.value());
					slider_Power_Voltage_PB().Minimum(tuningFanSettings.PowerVoltageMin.value());
					slider_Power_Voltage_PB().Maximum(tuningFanSettings.PowerVoltageMax.value());
					slider_Power_Voltage_PB().StepFrequency(tuningFanSettings.PowerVoltageStep.value());
					slider_Power_Voltage_PB().SmallChange(tuningFanSettings.PowerVoltageStep.value());

					//Check if value is offset (RDNA4+)
					if (tuningFanSettings.PowerVoltageMin.value() < 0)
					{
						textblock_Power_Voltage().Text(L"Voltage Offset");
					}
					else
					{
						textblock_Power_Voltage().Text(L"Voltage");
					}
				}

				//Enable or disable interface
				slider_Power_Voltage().IsEnabled(true);
				slider_Power_Voltage_PB().IsEnabled(true);
			}
			else
			{
				//Set value text
				textblock_Power_Voltage_Value().Text(L"");

				//Enable or disable interface
				slider_Power_Voltage().IsEnabled(false);
				slider_Power_Voltage_PB().IsEnabled(false);
			}

			//Power TDC
			if (tuningFanSettings.PowerTDC.has_value())
			{
				//Set value text
				std::wstring valueText = number_to_wstring(tuningFanSettings.PowerTDC.value()) + L"A";
				textblock_Power_TDC_Value().Text(valueText);

				//Set setting limits
				if (tuningFanSettings.PowerTDCMin.has_value())
				{
					slider_Power_TDC().Minimum(tuningFanSettings.PowerTDCMin.value());
					slider_Power_TDC().Maximum(tuningFanSettings.PowerTDCMax.value());
					slider_Power_TDC().StepFrequency(tuningFanSettings.PowerTDCStep.value());
					slider_Power_TDC().SmallChange(tuningFanSettings.PowerTDCStep.value());
					slider_Power_TDC_PB().Minimum(tuningFanSettings.PowerTDCMin.value());
					slider_Power_TDC_PB().Maximum(tuningFanSettings.PowerTDCMax.value());
					slider_Power_TDC_PB().StepFrequency(tuningFanSettings.PowerTDCStep.value());
					slider_Power_TDC_PB().SmallChange(tuningFanSettings.PowerTDCStep.value());
				}

				//Enable or disable interface
				slider_Power_TDC().IsEnabled(true);
				slider_Power_TDC_PB().IsEnabled(true);
			}
			else
			{
				//Set value text
				textblock_Power_TDC_Value().Text(L"");

				//Enable or disable interface
				slider_Power_TDC().IsEnabled(false);
				slider_Power_TDC_PB().IsEnabled(false);
			}

			//Fan Zero RPM
			if (tuningFanSettings.FanZeroRpm.has_value())
			{
				//Show or hide Zero RPM line
				if (tuningFanSettings.FanZeroRpm.value())
				{
					grid_Fan_Zero_Rpm_Line().Visibility(Visibility::Visible);
				}
				else
				{
					grid_Fan_Zero_Rpm_Line().Visibility(Visibility::Collapsed);
				}

				//Enable or disable interface
				toggleswitch_Fan_Zero_Rpm().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_Fan_Zero_Rpm().IsEnabled(false);
			}

			//Fan Speed 0
			if (tuningFanSettings.FanSpeed0.has_value())
			{
				//Set setting limits
				if (tuningFanSettings.FanSpeedMin0.has_value())
				{
					slider_Fan_Speed_0().Minimum(tuningFanSettings.FanSpeedMin0.value());
					slider_Fan_Speed_0().Maximum(tuningFanSettings.FanSpeedMax0.value());
					slider_Fan_Speed_0().StepFrequency(tuningFanSettings.FanSpeedStep0.value());
					slider_Fan_Speed_0().SmallChange(tuningFanSettings.FanSpeedStep0.value());
				}

				//Enable or disable interface
				slider_Fan_Speed_0().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				slider_Fan_Speed_0().IsEnabled(false);
			}

			//Fan Temperature 0
			if (tuningFanSettings.FanTemp0.has_value())
			{
				//Set setting limits
				if (tuningFanSettings.FanTempMin0.has_value())
				{
					slider_Fan_Temp_0().Minimum(tuningFanSettings.FanTempMin0.value());
					slider_Fan_Temp_0().Maximum(tuningFanSettings.FanTempMax0.value());
					slider_Fan_Temp_0().StepFrequency(tuningFanSettings.FanTempStep0.value());
					slider_Fan_Temp_0().SmallChange(tuningFanSettings.FanTempStep0.value());
				}

				//Enable or disable interface
				slider_Fan_Temp_0().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				slider_Fan_Temp_0().IsEnabled(false);
			}

			//Fan Speed 1
			if (tuningFanSettings.FanSpeed1.has_value())
			{
				//Set setting limits
				if (tuningFanSettings.FanSpeedMin1.has_value())
				{
					slider_Fan_Speed_1().Minimum(tuningFanSettings.FanSpeedMin1.value());
					slider_Fan_Speed_1().Maximum(tuningFanSettings.FanSpeedMax1.value());
					slider_Fan_Speed_1().StepFrequency(tuningFanSettings.FanSpeedStep1.value());
					slider_Fan_Speed_1().SmallChange(tuningFanSettings.FanSpeedStep1.value());
				}

				//Enable or disable interface
				slider_Fan_Speed_1().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				slider_Fan_Speed_1().IsEnabled(false);
			}

			//Fan Temperature 1
			if (tuningFanSettings.FanTemp1.has_value())
			{
				//Set setting limits
				if (tuningFanSettings.FanTempMin1.has_value())
				{
					slider_Fan_Temp_1().Minimum(tuningFanSettings.FanTempMin1.value());
					slider_Fan_Temp_1().Maximum(tuningFanSettings.FanTempMax1.value());
					slider_Fan_Temp_1().StepFrequency(tuningFanSettings.FanTempStep1.value());
					slider_Fan_Temp_1().SmallChange(tuningFanSettings.FanTempStep1.value());
				}

				//Enable or disable interface
				slider_Fan_Temp_1().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				slider_Fan_Temp_1().IsEnabled(false);
			}

			//Fan Speed 2
			if (tuningFanSettings.FanSpeed2.has_value())
			{
				//Set setting limits
				if (tuningFanSettings.FanSpeedMin2.has_value())
				{
					slider_Fan_Speed_2().Minimum(tuningFanSettings.FanSpeedMin2.value());
					slider_Fan_Speed_2().Maximum(tuningFanSettings.FanSpeedMax2.value());
					slider_Fan_Speed_2().StepFrequency(tuningFanSettings.FanSpeedStep2.value());
					slider_Fan_Speed_2().SmallChange(tuningFanSettings.FanSpeedStep2.value());
				}

				//Enable or disable interface
				slider_Fan_Speed_2().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				slider_Fan_Speed_2().IsEnabled(false);
			}

			//Fan Temperature 2
			if (tuningFanSettings.FanTemp2.has_value())
			{
				//Set setting limits
				if (tuningFanSettings.FanTempMin2.has_value())
				{
					slider_Fan_Temp_2().Minimum(tuningFanSettings.FanTempMin2.value());
					slider_Fan_Temp_2().Maximum(tuningFanSettings.FanTempMax2.value());
					slider_Fan_Temp_2().StepFrequency(tuningFanSettings.FanTempStep2.value());
					slider_Fan_Temp_2().SmallChange(tuningFanSettings.FanTempStep2.value());
				}

				//Enable or disable interface
				slider_Fan_Temp_2().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				slider_Fan_Temp_2().IsEnabled(false);
			}

			//Fan Speed 3
			if (tuningFanSettings.FanSpeed3.has_value())
			{
				//Set setting limits
				if (tuningFanSettings.FanSpeedMin3.has_value())
				{
					slider_Fan_Speed_3().Minimum(tuningFanSettings.FanSpeedMin3.value());
					slider_Fan_Speed_3().Maximum(tuningFanSettings.FanSpeedMax3.value());
					slider_Fan_Speed_3().StepFrequency(tuningFanSettings.FanSpeedStep3.value());
					slider_Fan_Speed_3().SmallChange(tuningFanSettings.FanSpeedStep3.value());
				}

				//Enable or disable interface
				slider_Fan_Speed_3().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				slider_Fan_Speed_3().IsEnabled(false);
			}

			//Fan Temperature 3
			if (tuningFanSettings.FanTemp3.has_value())
			{
				//Set setting limits
				if (tuningFanSettings.FanTempMin3.has_value())
				{
					slider_Fan_Temp_3().Minimum(tuningFanSettings.FanTempMin3.value());
					slider_Fan_Temp_3().Maximum(tuningFanSettings.FanTempMax3.value());
					slider_Fan_Temp_3().StepFrequency(tuningFanSettings.FanTempStep3.value());
					slider_Fan_Temp_3().SmallChange(tuningFanSettings.FanTempStep3.value());
				}

				//Enable or disable interface
				slider_Fan_Temp_3().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				slider_Fan_Temp_3().IsEnabled(false);
			}

			//Fan Speed 4
			if (tuningFanSettings.FanSpeed4.has_value())
			{
				//Set setting limits
				if (tuningFanSettings.FanSpeedMin4.has_value())
				{
					slider_Fan_Speed_4().Minimum(tuningFanSettings.FanSpeedMin4.value());
					slider_Fan_Speed_4().Maximum(tuningFanSettings.FanSpeedMax4.value());
					slider_Fan_Speed_4().StepFrequency(tuningFanSettings.FanSpeedStep4.value());
					slider_Fan_Speed_4().SmallChange(tuningFanSettings.FanSpeedStep4.value());
				}

				//Enable or disable interface
				slider_Fan_Speed_4().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				slider_Fan_Speed_4().IsEnabled(false);
			}

			//Fan Temperature 4
			if (tuningFanSettings.FanTemp4.has_value())
			{
				//Set setting limits
				if (tuningFanSettings.FanTempMin4.has_value())
				{
					slider_Fan_Temp_4().Minimum(tuningFanSettings.FanTempMin4.value());
					slider_Fan_Temp_4().Maximum(tuningFanSettings.FanTempMax4.value());
					slider_Fan_Temp_4().StepFrequency(tuningFanSettings.FanTempStep4.value());
					slider_Fan_Temp_4().SmallChange(tuningFanSettings.FanTempStep4.value());
				}

				//Enable or disable interface
				slider_Fan_Temp_4().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				slider_Fan_Temp_4().IsEnabled(false);
			}

			//Enable or disable tuning interface
			bool supportManualGPU = tuningFanSettings.SupportManualGPU.has_value() ? tuningFanSettings.SupportManualGPU.value() : false;
			bool supportManualVRAM = tuningFanSettings.SupportManualVRAM.has_value() ? tuningFanSettings.SupportManualVRAM.value() : false;
			bool supportManualPower = tuningFanSettings.SupportManualPower.has_value() ? tuningFanSettings.SupportManualPower.value() : false;
			if (!supportManualGPU && !supportManualVRAM && !supportManualPower)
			{
				//Top buttons
				button_Tuning_Apply().IsEnabled(false);
				button_Tuning_Reset().IsEnabled(false);
				button_Tuning_Import().IsEnabled(false);
				button_Tuning_Export().IsEnabled(false);

				//Custom settings
				toggleswitch_KeepActive().IsEnabled(false);
			}
			else
			{
				//Top buttons
				button_Tuning_Apply().IsEnabled(true);
				button_Tuning_Reset().IsEnabled(true);
				button_Tuning_Import().IsEnabled(true);
				button_Tuning_Export().IsEnabled(true);

				//Custom settings
				toggleswitch_KeepActive().IsEnabled(true);
			}

			//Enable or disable fan interface
			bool supportManualFAN = tuningFanSettings.SupportManualFAN.has_value() ? tuningFanSettings.SupportManualFAN.value() : false;
			if (!supportManualFAN)
			{
				button_Fan_Apply().IsEnabled(false);
				button_Fan_Reset().IsEnabled(false);
				button_Fan_Import().IsEnabled(false);
				button_Fan_Export().IsEnabled(false);
			}
			else
			{
				button_Fan_Apply().IsEnabled(true);
				button_Fan_Reset().IsEnabled(true);
				button_Fan_Import().IsEnabled(true);
				button_Fan_Export().IsEnabled(true);
			}

			//Return result
			AVDebugWriteLine(L"Tuning and fans settings applied to interface.");
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine(L"Failed applying tuning and fans settings to interface.");
		}
	}

	std::optional<TuningFanSettings> MainPage::TuningFanSettings_Generate_FromAdlxGpuPtr(IADLXGPU2Ptr ppGpuPtr)
	{
		try
		{
			TuningFanSettings tuningFanSettings{};

			//Device identifier
			std::wstring device_id_w = AdlxGetGpuIdentifier(ppGpuPtr);
			if (!device_id_w.empty())
			{
				tuningFanSettings.DeviceId = wstring_to_string(device_id_w);
			}

			//Check manual support
			try
			{
				adlx_Res0 = ppGPUTuningServices->IsSupportedManualGFXTuning(ppGpuPtr, &adlx_Bool);
				if (ADLX_SUCCEEDED(adlx_Res0) && adlx_Bool)
				{
					tuningFanSettings.SupportManualGPU = adlx_Bool;
				}
				else
				{
					tuningFanSettings.SupportManualGPU = false;
				}

				adlx_Res0 = ppGPUTuningServices->IsSupportedManualVRAMTuning(ppGpuPtr, &adlx_Bool);
				if (ADLX_SUCCEEDED(adlx_Res0) && adlx_Bool)
				{
					tuningFanSettings.SupportManualVRAM = adlx_Bool;
				}
				else
				{
					tuningFanSettings.SupportManualVRAM = false;
				}

				adlx_Res0 = ppGPUTuningServices->IsSupportedManualPowerTuning(ppGpuPtr, &adlx_Bool);
				if (ADLX_SUCCEEDED(adlx_Res0) && adlx_Bool)
				{
					tuningFanSettings.SupportManualPower = adlx_Bool;
				}
				else
				{
					tuningFanSettings.SupportManualPower = false;
				}

				adlx_Res0 = ppGPUTuningServices->IsSupportedManualFanTuning(ppGpuPtr, &adlx_Bool);
				if (ADLX_SUCCEEDED(adlx_Res0) && adlx_Bool)
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
				IADLXManualGraphicsTuning2_1Ptr ppManualGFXTuning;
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
				if (ADLX_SUCCEEDED(adlx_Res0))
				{
					//Fan 0
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

					//Fan 1
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

					//Fan 2
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

					//Fan 3
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

					//Fan 4
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
			}
			catch (...)
			{
				AVDebugWriteLine("Failed to generate tuning fan settings.");
			}

			//Return result
			return tuningFanSettings;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to generate tuning and fan settings from adlx GPU ptr.");
			return std::nullopt;
		}
	}

	std::optional<TuningFanSettings> MainPage::TuningFanSettings_Generate_FromUI()
	{
		try
		{
			TuningFanSettings tuningFanSettings{};

			//Identifier
			std::wstring device_id_w = AdlxGetGpuIdentifier(ppGpuInfo);
			if (!device_id_w.empty())
			{
				tuningFanSettings.DeviceId = wstring_to_string(device_id_w);
			}

			//Keep Active
			if (toggleswitch_KeepActive().IsEnabled())
			{
				tuningFanSettings.KeepActive = (bool)toggleswitch_KeepActive().IsOn();
			}

			//Core
			if (slider_Core_Min().IsEnabled())
			{
				tuningFanSettings.CoreMin = (int)slider_Core_Min().Value();
			}
			if (slider_Core_Max().IsEnabled())
			{
				tuningFanSettings.CoreMax = (int)slider_Core_Max().Value();
			}

			//Memory
			if (slider_Memory_Max().IsEnabled())
			{
				tuningFanSettings.MemoryMax = (int)slider_Memory_Max().Value();
			}
			if (combobox_Memory_Timing().IsEnabled())
			{
				tuningFanSettings.MemoryTiming = (int)combobox_Memory_Timing().SelectedIndex();
			}

			//Power
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

			//Power Boost
			if (toggleswitch_PowerBoost().IsEnabled())
			{
				tuningFanSettings.PowerBoost = (bool)toggleswitch_PowerBoost().IsOn();
			}
			if (slider_Power_Limit_PB().IsEnabled())
			{
				tuningFanSettings.PowerLimitPB = (int)slider_Power_Limit_PB().Value();
			}
			if (slider_Power_Voltage_PB().IsEnabled())
			{
				tuningFanSettings.PowerVoltagePB = (int)slider_Power_Voltage_PB().Value();
			}
			if (slider_Power_TDC_PB().IsEnabled())
			{
				tuningFanSettings.PowerTDCPB = (int)slider_Power_TDC_PB().Value();
			}

			//Fans
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

			//Return result
			return tuningFanSettings;
		}
		catch (...)
		{
			//Return result
			return std::nullopt;
		}
	}

	bool MainPage::TuningFanSettings_Match(TuningFanSettings tuningFanSettingsProfile, TuningFanSettings tuningFanSettingsGpu)
	{
		try
		{
			//Gpu Core Minimum
			if (tuningFanSettingsProfile.CoreMin.has_value() && tuningFanSettingsGpu.CoreMin.has_value())
			{
				if (tuningFanSettingsProfile.CoreMin.value() != tuningFanSettingsGpu.CoreMin.value()) { return false; }
			}

			//Gpu Core Maximum
			if (tuningFanSettingsProfile.CoreMax.has_value() && tuningFanSettingsGpu.CoreMax.has_value())
			{
				if (tuningFanSettingsProfile.CoreMax.value() != tuningFanSettingsGpu.CoreMax.value()) { return false; }
			}

			//Memory timing
			if (tuningFanSettingsProfile.MemoryTiming.has_value() && tuningFanSettingsGpu.MemoryTiming.has_value())
			{
				if (tuningFanSettingsProfile.MemoryTiming.value() != tuningFanSettingsGpu.MemoryTiming.value()) { return false; }
			}

			//Memory frequency
			if (tuningFanSettingsProfile.MemoryMax.has_value() && tuningFanSettingsGpu.MemoryMax.has_value())
			{
				if (tuningFanSettingsProfile.MemoryMax.value() != tuningFanSettingsGpu.MemoryMax.value()) { return false; }
			}

			//Power Boost
			if (tuningFanSettingsProfile.PowerBoostUse.has_value() && tuningFanSettingsProfile.PowerBoostUse.value())
			{
				//Power limit (Power Boost)
				if (tuningFanSettingsProfile.PowerLimitPB.has_value() && tuningFanSettingsGpu.PowerLimit.has_value())
				{
					if (tuningFanSettingsProfile.PowerLimitPB.value() != tuningFanSettingsGpu.PowerLimit.value()) { return false; }
				}

				//Power voltage (Power Boost)
				if (tuningFanSettingsProfile.PowerVoltagePB.has_value() && tuningFanSettingsGpu.PowerVoltage.has_value())
				{
					if (tuningFanSettingsProfile.PowerVoltagePB.value() != tuningFanSettingsGpu.PowerVoltage.value()) { return false; }
				}

				//Power TDC (Power Boost)
				if (tuningFanSettingsProfile.PowerTDCPB.has_value() && tuningFanSettingsGpu.PowerTDC.has_value())
				{
					if (tuningFanSettingsProfile.PowerTDCPB.value() != tuningFanSettingsGpu.PowerTDC.value()) { return false; }
				}
			}
			else
			{
				//Power limit
				if (tuningFanSettingsProfile.PowerLimit.has_value() && tuningFanSettingsGpu.PowerLimit.has_value())
				{
					if (tuningFanSettingsProfile.PowerLimit.value() != tuningFanSettingsGpu.PowerLimit.value()) { return false; }
				}

				//Power voltage
				if (tuningFanSettingsProfile.PowerVoltage.has_value() && tuningFanSettingsGpu.PowerVoltage.has_value())
				{
					if (tuningFanSettingsProfile.PowerVoltage.value() != tuningFanSettingsGpu.PowerVoltage.value()) { return false; }
				}

				//Power TDC
				if (tuningFanSettingsProfile.PowerTDC.has_value() && tuningFanSettingsGpu.PowerTDC.has_value())
				{
					if (tuningFanSettingsProfile.PowerTDC.value() != tuningFanSettingsGpu.PowerTDC.value()) { return false; }
				}
			}

			//Fan Zero RPM
			if (tuningFanSettingsProfile.FanZeroRpm.has_value() && tuningFanSettingsGpu.FanZeroRpm.has_value())
			{
				if (tuningFanSettingsProfile.FanZeroRpm.value() != tuningFanSettingsGpu.FanZeroRpm.value()) { return false; }
			}

			//Fan Speed 0
			if (tuningFanSettingsProfile.FanSpeed0.has_value() && tuningFanSettingsGpu.FanSpeed0.has_value())
			{
				if (tuningFanSettingsProfile.FanSpeed0.value() != tuningFanSettingsGpu.FanSpeed0.value()) { return false; }
			}

			//Fan Temperature 0
			if (tuningFanSettingsProfile.FanTemp0.has_value() && tuningFanSettingsGpu.FanTemp0.has_value())
			{
				if (tuningFanSettingsProfile.FanTemp0.value() != tuningFanSettingsGpu.FanTemp0.value()) { return false; }
			}

			//Fan Speed 1
			if (tuningFanSettingsProfile.FanSpeed1.has_value() && tuningFanSettingsGpu.FanSpeed1.has_value())
			{
				if (tuningFanSettingsProfile.FanSpeed1.value() != tuningFanSettingsGpu.FanSpeed1.value()) { return false; }
			}

			//Fan Temperature 1
			if (tuningFanSettingsProfile.FanTemp1.has_value() && tuningFanSettingsGpu.FanTemp1.has_value())
			{
				if (tuningFanSettingsProfile.FanTemp1.value() != tuningFanSettingsGpu.FanTemp1.value()) { return false; }
			}

			//Fan Speed 2
			if (tuningFanSettingsProfile.FanSpeed2.has_value() && tuningFanSettingsGpu.FanSpeed2.has_value())
			{
				if (tuningFanSettingsProfile.FanSpeed2.value() != tuningFanSettingsGpu.FanSpeed2.value()) { return false; }
			}

			//Fan Temperature 2
			if (tuningFanSettingsProfile.FanTemp2.has_value() && tuningFanSettingsGpu.FanTemp2.has_value())
			{
				if (tuningFanSettingsProfile.FanTemp2.value() != tuningFanSettingsGpu.FanTemp2.value()) { return false; }
			}

			//Fan Speed 3
			if (tuningFanSettingsProfile.FanSpeed3.has_value() && tuningFanSettingsGpu.FanSpeed3.has_value())
			{
				if (tuningFanSettingsProfile.FanSpeed3.value() != tuningFanSettingsGpu.FanSpeed3.value()) { return false; }
			}

			//Fan Temperature 3
			if (tuningFanSettingsProfile.FanTemp3.has_value() && tuningFanSettingsGpu.FanTemp3.has_value())
			{
				if (tuningFanSettingsProfile.FanTemp3.value() != tuningFanSettingsGpu.FanTemp3.value()) { return false; }
			}

			//Fan Speed 4
			if (tuningFanSettingsProfile.FanSpeed4.has_value() && tuningFanSettingsGpu.FanSpeed4.has_value())
			{
				if (tuningFanSettingsProfile.FanSpeed4.value() != tuningFanSettingsGpu.FanSpeed4.value()) { return false; }
			}

			//Fan Temperature 4
			if (tuningFanSettingsProfile.FanTemp4.has_value() && tuningFanSettingsGpu.FanTemp4.has_value())
			{
				if (tuningFanSettingsProfile.FanTemp4.value() != tuningFanSettingsGpu.FanTemp4.value()) { return false; }
			}
		}
		catch (...) {}
		return true;
	}
}