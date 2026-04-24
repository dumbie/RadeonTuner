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

			//Memory Timing
			if (tuningFanSettings.MemoryTiming.has_value())
			{
				combobox_Memory_Timing().SelectedIndex(tuningFanSettings.MemoryTiming.value());
			}

			//Memory Frequency
			if (tuningFanSettings.MemoryMax.has_value())
			{
				slider_Memory_Max().Value(tuningFanSettings.MemoryMax.value());
			}

			//Power Limit
			if (tuningFanSettings.PowerLimit.has_value())
			{
				slider_Power_Limit().Value(tuningFanSettings.PowerLimit.value());
			}

			//Power Limit (Power Boost)
			if (tuningFanSettings.PowerLimitPB.has_value())
			{
				slider_Power_Limit_PB().Value(tuningFanSettings.PowerLimitPB.value());
			}

			//Power Voltage
			if (tuningFanSettings.PowerVoltage.has_value())
			{
				slider_Power_Voltage().Value(tuningFanSettings.PowerVoltage.value());
			}

			//Power Voltage (Power Boost)
			if (tuningFanSettings.PowerVoltagePB.has_value())
			{
				slider_Power_Voltage_PB().Value(tuningFanSettings.PowerVoltagePB.value());
			}

			//Power TDC
			if (tuningFanSettings.PowerTDC.has_value())
			{
				slider_Power_TDC().Value(tuningFanSettings.PowerTDC.value());
			}

			//Power TDC (Power Boost)
			if (tuningFanSettings.PowerTDCPB.has_value())
			{
				slider_Power_TDC_PB().Value(tuningFanSettings.PowerTDCPB.value());
			}

			//Fan Control
			bool fanControl = false;
			if (tuningFanSettings.FanControl.has_value())
			{
				fanControl = tuningFanSettings.FanControl.value();
				toggleswitch_Fan_Control().IsOn(fanControl);
				textblock_Fan_Control_Value().Text(fanControl ? L"Enabled" : L"Disabled");

				//Update fan graph opacity
				grid_Fan_Graph().Opacity(fanControl ? 1.0 : 0.4);
			}
			else
			{
				toggleswitch_Fan_Control().IsOn(false);
				textblock_Fan_Control_Value().Text(L"Disabled");

				//Update fan graph opacity
				grid_Fan_Graph().Opacity(0.4);
			}

			//Fan Zero RPM
			if (tuningFanSettings.FanZeroRpm.has_value())
			{
				bool zeroRpm = tuningFanSettings.FanZeroRpm.value();
				toggleswitch_Fan_Zero_Rpm().IsOn(zeroRpm);

				//Enable or disable interface
				toggleswitch_Fan_Zero_Rpm().IsEnabled(fanControl);

				//Show or hide Zero RPM line
				grid_Fan_Zero_Rpm_Line_Profile().Visibility(zeroRpm ? Visibility::Visible : Visibility::Collapsed);
			}

			//Fan Speed 0
			if (tuningFanSettings.FanSpeed0.has_value())
			{
				slider_Fan_Speed_0().Value(tuningFanSettings.FanSpeed0.value());

				//Enable or disable interface
				slider_Fan_Speed_0().IsEnabled(fanControl);
			}

			//Fan Temperature 0
			if (tuningFanSettings.FanTemp0.has_value())
			{
				slider_Fan_Temp_0().Value(tuningFanSettings.FanTemp0.value());

				//Enable or disable interface
				slider_Fan_Temp_0().IsEnabled(fanControl);
			}

			//Fan Speed 1
			if (tuningFanSettings.FanSpeed1.has_value())
			{
				slider_Fan_Speed_1().Value(tuningFanSettings.FanSpeed1.value());

				//Enable or disable interface
				slider_Fan_Speed_1().IsEnabled(fanControl);
			}

			//Fan Temperature 1
			if (tuningFanSettings.FanTemp1.has_value())
			{
				slider_Fan_Temp_1().Value(tuningFanSettings.FanTemp1.value());

				//Enable or disable interface
				slider_Fan_Temp_1().IsEnabled(fanControl);
			}

			//Fan Speed 2
			if (tuningFanSettings.FanSpeed2.has_value())
			{
				slider_Fan_Speed_2().Value(tuningFanSettings.FanSpeed2.value());

				//Enable or disable interface
				slider_Fan_Speed_2().IsEnabled(fanControl);
			}

			//Fan Temperature 2
			if (tuningFanSettings.FanTemp2.has_value())
			{
				slider_Fan_Temp_2().Value(tuningFanSettings.FanTemp2.value());

				//Enable or disable interface
				slider_Fan_Temp_2().IsEnabled(fanControl);
			}

			//Fan Speed 3
			if (tuningFanSettings.FanSpeed3.has_value())
			{
				slider_Fan_Speed_3().Value(tuningFanSettings.FanSpeed3.value());

				//Enable or disable interface
				slider_Fan_Speed_3().IsEnabled(fanControl);
			}

			//Fan Temperature 3
			if (tuningFanSettings.FanTemp3.has_value())
			{
				slider_Fan_Temp_3().Value(tuningFanSettings.FanTemp3.value());

				//Enable or disable interface
				slider_Fan_Temp_3().IsEnabled(fanControl);
			}

			//Fan Speed 4
			if (tuningFanSettings.FanSpeed4.has_value())
			{
				slider_Fan_Speed_4().Value(tuningFanSettings.FanSpeed4.value());

				//Enable or disable interface
				slider_Fan_Speed_4().IsEnabled(fanControl);
			}

			//Fan Temperature 4
			if (tuningFanSettings.FanTemp4.has_value())
			{
				slider_Fan_Temp_4().Value(tuningFanSettings.FanTemp4.value());

				//Enable or disable interface
				slider_Fan_Temp_4().IsEnabled(fanControl);
			}

			//Update fan graph
			UpdateFanGraphProfile();

			//Keep Active
			if (tuningFanSettings.KeepActive.has_value())
			{
				bool keepActive = tuningFanSettings.KeepActive.value();
				toggleswitch_KeepActive().IsOn(keepActive);
				textblock_KeepActive_Value().Text(keepActive ? L"Enabled" : L"Disabled");
			}
			else
			{
				toggleswitch_KeepActive().IsOn(false);
				textblock_KeepActive_Value().Text(L"Disabled");
			}

			//Power Boost
			if (tuningFanSettings.PowerBoost.has_value())
			{
				bool powerBoost = tuningFanSettings.PowerBoost.value();
				toggleswitch_PowerBoost().IsOn(powerBoost);

				//Show or hide power boost settings
				if (powerBoost)
				{
					//Current status
					textblock_PowerBoost_Value().Text(L"Enabled");

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
					//Current status
					textblock_PowerBoost_Value().Text(L"Disabled");

					//Hide or show settings
					grid_Power_Limit_PB().Visibility(Visibility::Collapsed);
					grid_Power_Voltage_PB().Visibility(Visibility::Collapsed);
					grid_Power_TDC_PB().Visibility(Visibility::Collapsed);

					//Enable or disable settings
					combobox_PowerBoost_Applications().IsEnabled(false);
					button_PowerBoost_AddExe().IsEnabled(false);
					button_PowerBoost_Remove().IsEnabled(false);
				}
			}
			else
			{
				toggleswitch_PowerBoost().IsOn(false);
				textblock_PowerBoost_Value().Text(L"Disabled");
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

			//Memory Timing
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

			//Memory Frequency
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

			//Power Limit
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
			}
			else
			{
				//Set value text
				textblock_Power_Limit_Value().Text(L"");

				//Enable or disable interface
				slider_Power_Limit().IsEnabled(false);
				slider_Power_Limit_PB().IsEnabled(false);
			}

			//Power Voltage
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
				std::wstring valueText = number_to_wstring(tuningFanSettings.PowerTDC.value()) + L"%";
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

			//Update fan graph
			UpdateFanGraphGpu(tuningFanSettings);

			//Fan Zero RPM
			if (tuningFanSettings.FanZeroRpm.has_value())
			{
				bool zeroRpm = tuningFanSettings.FanZeroRpm.value();
				textblock_Fan_Zero_Rpm_Value().Text(zeroRpm ? L"Enabled" : L"Disabled");

				//Show or hide Zero RPM line
				grid_Fan_Zero_Rpm_Line_Gpu().Visibility(zeroRpm ? Visibility::Visible : Visibility::Collapsed);

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
				textblock_Fan_Curve_0_Speed_Value().Text(number_to_wstring(tuningFanSettings.FanSpeed0.value()) + L"%");

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
				textblock_Fan_Curve_0_Temp_Value().Text(number_to_wstring(tuningFanSettings.FanTemp0.value()) + L"C");

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
				textblock_Fan_Curve_1_Speed_Value().Text(number_to_wstring(tuningFanSettings.FanSpeed1.value()) + L"%");

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
				textblock_Fan_Curve_1_Temp_Value().Text(number_to_wstring(tuningFanSettings.FanTemp1.value()) + L"C");

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
				textblock_Fan_Curve_2_Speed_Value().Text(number_to_wstring(tuningFanSettings.FanSpeed2.value()) + L"%");

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
				textblock_Fan_Curve_2_Temp_Value().Text(number_to_wstring(tuningFanSettings.FanTemp2.value()) + L"C");

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
				textblock_Fan_Curve_3_Speed_Value().Text(number_to_wstring(tuningFanSettings.FanSpeed3.value()) + L"%");

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
				textblock_Fan_Curve_3_Temp_Value().Text(number_to_wstring(tuningFanSettings.FanTemp3.value()) + L"C");

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
				textblock_Fan_Curve_4_Speed_Value().Text(number_to_wstring(tuningFanSettings.FanSpeed4.value()) + L"%");

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
				textblock_Fan_Curve_4_Temp_Value().Text(number_to_wstring(tuningFanSettings.FanTemp4.value()) + L"C");

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
			bool supportTuning = tuningFanSettings.SupportTuning.has_value() ? tuningFanSettings.SupportTuning.value() : false;
			if (!supportTuning)
			{
				//Top buttons
				button_Tuning_Apply().IsEnabled(false);
				button_Tuning_Reset().IsEnabled(false);
				button_Tuning_Import().IsEnabled(false);
				button_Tuning_Export().IsEnabled(false);

				//Custom settings
				toggleswitch_KeepActive().IsEnabled(false);
				toggleswitch_PowerBoost().IsEnabled(false);
				combobox_PowerBoost_Applications().IsEnabled(false);
				button_PowerBoost_AddExe().IsEnabled(false);
				button_PowerBoost_Remove().IsEnabled(false);
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
				toggleswitch_PowerBoost().IsEnabled(true);
				bool powerBoost = toggleswitch_PowerBoost().IsOn();
				combobox_PowerBoost_Applications().IsEnabled(powerBoost);
				button_PowerBoost_AddExe().IsEnabled(powerBoost);
				button_PowerBoost_Remove().IsEnabled(powerBoost);
			}

			//Enable or disable fan interface
			bool supportFans = tuningFanSettings.SupportFans.has_value() ? tuningFanSettings.SupportFans.value() : false;
			if (!supportFans)
			{
				button_Fan_Apply().IsEnabled(false);
				button_Fan_Reset().IsEnabled(false);
				button_Fan_Import().IsEnabled(false);
				button_Fan_Export().IsEnabled(false);

				//Custom settings
				toggleswitch_Fan_Control().IsEnabled(false);
				grid_Fan_Graph().Opacity(0.4);
			}
			else
			{
				button_Fan_Apply().IsEnabled(true);
				button_Fan_Reset().IsEnabled(true);
				button_Fan_Import().IsEnabled(true);
				button_Fan_Export().IsEnabled(true);

				//Custom settings
				toggleswitch_Fan_Control().IsEnabled(true);
				bool fanControl = toggleswitch_Fan_Control().IsOn();
				grid_Fan_Graph().Opacity(fanControl ? 1.0 : 0.4);
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

	std::optional<TuningFanSettings> MainPage::TuningFanSettings_Generate_FromGPU(IADLXGPU2Ptr gpuPointer, int gpuAdapterIndex)
	{
		try
		{
			TuningFanSettings tuningFanSettings{};

			//Device identifier
			{
				std::wstring device_id_w = AdlxGetGpuIdentifier(gpuPointer);
				tuningFanSettings.DeviceId = wstring_to_string(device_id_w);
			}

			//Gpu Core Minimum
			{
				auto defaultValue = Adl_Overdrive_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_GFXCLK_FMIN);
				auto settingValue = Adl_Overdrive_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_GFXCLK_FMIN);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						tuningFanSettings.CoreMin = settingValue.value();
						tuningFanSettings.CoreMinMin = defaultValue.value().minValue;
						tuningFanSettings.CoreMinMax = defaultValue.value().maxValue;
						tuningFanSettings.CoreMinStep = 1;
						tuningFanSettings.CoreMinSupport = true;
					}
				}
			}

			//Gpu Core Maximum
			{
				auto defaultValue = Adl_Overdrive_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_GFXCLK_FMAX);
				auto settingValue = Adl_Overdrive_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_GFXCLK_FMAX);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						tuningFanSettings.CoreMax = settingValue.value();
						tuningFanSettings.CoreMaxMin = defaultValue.value().minValue;
						tuningFanSettings.CoreMaxMax = defaultValue.value().maxValue;
						tuningFanSettings.CoreMaxStep = 1;
						tuningFanSettings.CoreMaxSupport = true;
					}
				}
			}

			//Memory Timing
			{
				auto defaultValue = Adl_Overdrive_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_AC_TIMING);
				auto settingValue = Adl_Overdrive_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_AC_TIMING);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						tuningFanSettings.MemoryTiming = settingValue.value();
						tuningFanSettings.MemoryTimingSupport = true;
					}
				}
			}

			//Memory Frequency
			{
				auto defaultValue = Adl_Overdrive_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_UCLK_FMAX);
				auto settingValue = Adl_Overdrive_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_UCLK_FMAX);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						tuningFanSettings.MemoryMax = settingValue.value();
						tuningFanSettings.MemoryMaxMin = defaultValue.value().minValue;
						tuningFanSettings.MemoryMaxMax = defaultValue.value().maxValue;
						tuningFanSettings.MemoryMaxStep = 2;
						tuningFanSettings.MemoryMaxSupport = true;
					}
				}
			}

			//Power Limit
			{
				auto defaultValue = Adl_Overdrive_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_POWER_PERCENTAGE);
				auto settingValue = Adl_Overdrive_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_POWER_PERCENTAGE);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						tuningFanSettings.PowerLimit = settingValue.value();
						tuningFanSettings.PowerLimitPB = defaultValue.value().defaultValue;
						tuningFanSettings.PowerLimitMin = defaultValue.value().minValue;
						tuningFanSettings.PowerLimitMax = defaultValue.value().maxValue;
						tuningFanSettings.PowerLimitStep = 1;
						tuningFanSettings.PowerLimitSupport = true;
					}
				}
			}

			//Power Voltage
			{
				auto defaultValue = Adl_Overdrive_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_OD_VOLTAGE);
				auto settingValue = Adl_Overdrive_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_OD_VOLTAGE);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						tuningFanSettings.PowerVoltage = settingValue.value();
						tuningFanSettings.PowerVoltagePB = defaultValue.value().defaultValue;
						tuningFanSettings.PowerVoltageMin = defaultValue.value().minValue;
						tuningFanSettings.PowerVoltageMax = defaultValue.value().maxValue;
						tuningFanSettings.PowerVoltageStep = 1;
						tuningFanSettings.PowerVoltageSupport = true;
					}
				}
			}

			//Power TDC
			{
				auto defaultValue = Adl_Overdrive_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_TDC_PERCENTAGE);
				auto settingValue = Adl_Overdrive_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_TDC_PERCENTAGE);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						tuningFanSettings.PowerTDC = settingValue.value();
						tuningFanSettings.PowerTDCPB = defaultValue.value().defaultValue;
						tuningFanSettings.PowerTDCMin = defaultValue.value().minValue;
						tuningFanSettings.PowerTDCMax = defaultValue.value().maxValue;
						tuningFanSettings.PowerTDCStep = 1;
						tuningFanSettings.PowerTDCSupport = true;
					}
				}
			}

			//Fan Zero RPM
			{
				auto defaultValue = Adl_Overdrive_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_ZERORPM_CONTROL);
				auto settingValue = Adl_Overdrive_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_ZERORPM_CONTROL);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						tuningFanSettings.FanZeroRpm = settingValue.value();
						tuningFanSettings.FanZeroRpmSupport = true;
					}
				}
			}

			//Fan Speed 0
			{
				auto defaultValue = Adl_Overdrive_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_SPEED_1);
				auto settingValue = Adl_Overdrive_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_SPEED_1);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						tuningFanSettings.FanSpeed0 = settingValue.value();
						tuningFanSettings.FanSpeedMin0 = defaultValue.value().minValue;
						tuningFanSettings.FanSpeedMax0 = defaultValue.value().maxValue;
						tuningFanSettings.FanSpeedStep0 = 1;
						tuningFanSettings.FanSpeedSupport0 = true;
					}
				}
			}

			//Fan Temperature 0
			{
				auto defaultValue = Adl_Overdrive_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_1);
				auto settingValue = Adl_Overdrive_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_1);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						tuningFanSettings.FanTemp0 = settingValue.value();
						tuningFanSettings.FanTempMin0 = defaultValue.value().minValue;
						tuningFanSettings.FanTempMax0 = defaultValue.value().maxValue;
						tuningFanSettings.FanTempStep0 = 1;
						tuningFanSettings.FanTempSupport0 = true;
					}
				}
			}

			//Fan Speed 1
			{
				auto defaultValue = Adl_Overdrive_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_SPEED_2);
				auto settingValue = Adl_Overdrive_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_SPEED_2);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						tuningFanSettings.FanSpeed1 = settingValue.value();
						tuningFanSettings.FanSpeedMin1 = defaultValue.value().minValue;
						tuningFanSettings.FanSpeedMax1 = defaultValue.value().maxValue;
						tuningFanSettings.FanSpeedStep1 = 1;
						tuningFanSettings.FanSpeedSupport1 = true;
					}
				}
			}

			//Fan Temperature 1
			{
				auto defaultValue = Adl_Overdrive_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_2);
				auto settingValue = Adl_Overdrive_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_2);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						tuningFanSettings.FanTemp1 = settingValue.value();
						tuningFanSettings.FanTempMin1 = defaultValue.value().minValue;
						tuningFanSettings.FanTempMax1 = defaultValue.value().maxValue;
						tuningFanSettings.FanTempStep1 = 1;
						tuningFanSettings.FanTempSupport1 = true;
					}
				}
			}

			//Fan Speed 2
			{
				auto defaultValue = Adl_Overdrive_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_SPEED_3);
				auto settingValue = Adl_Overdrive_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_SPEED_3);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						tuningFanSettings.FanSpeed2 = settingValue.value();
						tuningFanSettings.FanSpeedMin2 = defaultValue.value().minValue;
						tuningFanSettings.FanSpeedMax2 = defaultValue.value().maxValue;
						tuningFanSettings.FanSpeedStep2 = 1;
						tuningFanSettings.FanSpeedSupport2 = true;
					}
				}
			}

			//Fan Temperature 2
			{
				auto defaultValue = Adl_Overdrive_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_3);
				auto settingValue = Adl_Overdrive_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_3);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						tuningFanSettings.FanTemp2 = settingValue.value();
						tuningFanSettings.FanTempMin2 = defaultValue.value().minValue;
						tuningFanSettings.FanTempMax2 = defaultValue.value().maxValue;
						tuningFanSettings.FanTempStep2 = 1;
						tuningFanSettings.FanTempSupport2 = true;
					}
				}
			}

			//Fan Speed 3
			{
				auto defaultValue = Adl_Overdrive_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_SPEED_4);
				auto settingValue = Adl_Overdrive_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_SPEED_4);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						tuningFanSettings.FanSpeed3 = settingValue.value();
						tuningFanSettings.FanSpeedMin3 = defaultValue.value().minValue;
						tuningFanSettings.FanSpeedMax3 = defaultValue.value().maxValue;
						tuningFanSettings.FanSpeedStep3 = 1;
						tuningFanSettings.FanSpeedSupport3 = true;
					}
				}
			}

			//Fan Temperature 3
			{
				auto defaultValue = Adl_Overdrive_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_4);
				auto settingValue = Adl_Overdrive_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_4);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						tuningFanSettings.FanTemp3 = settingValue.value();
						tuningFanSettings.FanTempMin3 = defaultValue.value().minValue;
						tuningFanSettings.FanTempMax3 = defaultValue.value().maxValue;
						tuningFanSettings.FanTempStep3 = 1;
						tuningFanSettings.FanTempSupport3 = true;
					}
				}
			}

			//Fan Speed 4
			{
				auto defaultValue = Adl_Overdrive_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_SPEED_5);
				auto settingValue = Adl_Overdrive_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_SPEED_5);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						tuningFanSettings.FanSpeed4 = settingValue.value();
						tuningFanSettings.FanSpeedMin4 = defaultValue.value().minValue;
						tuningFanSettings.FanSpeedMax4 = defaultValue.value().maxValue;
						tuningFanSettings.FanSpeedStep4 = 1;
						tuningFanSettings.FanSpeedSupport4 = true;
					}
				}
			}

			//Fan Temperature 4
			{
				auto defaultValue = Adl_Overdrive_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_5);
				auto settingValue = Adl_Overdrive_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_5);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						tuningFanSettings.FanTemp4 = settingValue.value();
						tuningFanSettings.FanTempMin4 = defaultValue.value().minValue;
						tuningFanSettings.FanTempMax4 = defaultValue.value().maxValue;
						tuningFanSettings.FanTempStep4 = 1;
						tuningFanSettings.FanTempSupport4 = true;
					}
				}
			}

			//Feature support
			tuningFanSettings.SupportFans = Adl_Overdrive_Feature_Supported(gpuAdapterIndex, ADLOD8FeatureControl::ADL_OD8_FAN_CURVE);
			tuningFanSettings.SupportTuning = Adl_Overdrive_Feature_Supported(gpuAdapterIndex, ADLOD8FeatureControl::ADL_OD8_GFXCLK_LIMITS);

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
			TuningFanSettings tuningFanSettingsProfile{};
			TuningFanSettings tuningFanSettingsGpu = TuningFanSettings_Generate_FromGPU(ppGpuInfo, adl_Gpu_AdapterIndex).value();

			//Device identifier
			{
				tuningFanSettingsProfile.DeviceId = tuningFanSettingsGpu.DeviceId;
			}

			//Keep Active
			if (tuningFanSettingsGpu.SupportTuning.has_value() && tuningFanSettingsGpu.SupportTuning.value())
			{
				tuningFanSettingsProfile.KeepActive = (bool)toggleswitch_KeepActive().IsOn();
			}

			//Gpu Core Minimum
			if (tuningFanSettingsGpu.CoreMinSupport.has_value() && tuningFanSettingsGpu.CoreMinSupport.value())
			{
				tuningFanSettingsProfile.CoreMin = (int)slider_Core_Min().Value();
			}

			//Gpu Core Maximum
			if (tuningFanSettingsGpu.CoreMaxSupport.has_value() && tuningFanSettingsGpu.CoreMaxSupport.value())
			{
				tuningFanSettingsProfile.CoreMax = (int)slider_Core_Max().Value();
			}

			//Memory Timing
			if (tuningFanSettingsGpu.MemoryTimingSupport.has_value() && tuningFanSettingsGpu.MemoryTimingSupport.value())
			{
				tuningFanSettingsProfile.MemoryTiming = (int)combobox_Memory_Timing().SelectedIndex();
			}

			//Memory Frequency
			if (tuningFanSettingsGpu.MemoryMaxSupport.has_value() && tuningFanSettingsGpu.MemoryMaxSupport.value())
			{
				tuningFanSettingsProfile.MemoryMax = (int)slider_Memory_Max().Value();
			}

			//Power
			if (tuningFanSettingsGpu.PowerLimitSupport.has_value() && tuningFanSettingsGpu.PowerLimitSupport.value())
			{
				tuningFanSettingsProfile.PowerLimit = (int)slider_Power_Limit().Value();
			}
			if (tuningFanSettingsGpu.PowerVoltageSupport.has_value() && tuningFanSettingsGpu.PowerVoltageSupport.value())
			{
				tuningFanSettingsProfile.PowerVoltage = (int)slider_Power_Voltage().Value();
			}
			if (tuningFanSettingsGpu.PowerTDCSupport.has_value() && tuningFanSettingsGpu.PowerTDCSupport.value())
			{
				tuningFanSettingsProfile.PowerTDC = (int)slider_Power_TDC().Value();
			}

			//Power Boost
			if (tuningFanSettingsGpu.SupportTuning.has_value() && tuningFanSettingsGpu.SupportTuning.value())
			{
				tuningFanSettingsProfile.PowerBoost = (bool)toggleswitch_PowerBoost().IsOn();
			}
			if (tuningFanSettingsGpu.PowerLimitSupport.has_value() && tuningFanSettingsGpu.PowerLimitSupport.value())
			{
				tuningFanSettingsProfile.PowerLimitPB = (int)slider_Power_Limit_PB().Value();
			}
			if (tuningFanSettingsGpu.PowerVoltageSupport.has_value() && tuningFanSettingsGpu.PowerVoltageSupport.value())
			{
				tuningFanSettingsProfile.PowerVoltagePB = (int)slider_Power_Voltage_PB().Value();
			}
			if (tuningFanSettingsGpu.PowerTDCSupport.has_value() && tuningFanSettingsGpu.PowerTDCSupport.value())
			{
				tuningFanSettingsProfile.PowerTDCPB = (int)slider_Power_TDC_PB().Value();
			}

			//Fans
			if (tuningFanSettingsGpu.SupportFans.has_value() && tuningFanSettingsGpu.SupportFans.value())
			{
				tuningFanSettingsProfile.FanControl = (bool)toggleswitch_Fan_Control().IsOn();
			}
			if (tuningFanSettingsGpu.FanZeroRpmSupport.has_value() && tuningFanSettingsGpu.FanZeroRpmSupport.value())
			{
				tuningFanSettingsProfile.FanZeroRpm = (bool)toggleswitch_Fan_Zero_Rpm().IsOn();
			}
			if (tuningFanSettingsGpu.FanSpeedSupport0.has_value() && tuningFanSettingsGpu.FanSpeedSupport0.value())
			{
				tuningFanSettingsProfile.FanSpeed0 = (int)slider_Fan_Speed_0().Value();
			}
			if (tuningFanSettingsGpu.FanTempSupport0.has_value() && tuningFanSettingsGpu.FanTempSupport0.value())
			{
				tuningFanSettingsProfile.FanTemp0 = (int)slider_Fan_Temp_0().Value();
			}
			if (tuningFanSettingsGpu.FanSpeedSupport1.has_value() && tuningFanSettingsGpu.FanSpeedSupport1.value())
			{
				tuningFanSettingsProfile.FanSpeed1 = (int)slider_Fan_Speed_1().Value();
			}
			if (tuningFanSettingsGpu.FanTempSupport1.has_value() && tuningFanSettingsGpu.FanTempSupport1.value())
			{
				tuningFanSettingsProfile.FanTemp1 = (int)slider_Fan_Temp_1().Value();
			}
			if (tuningFanSettingsGpu.FanSpeedSupport2.has_value() && tuningFanSettingsGpu.FanSpeedSupport2.value())
			{
				tuningFanSettingsProfile.FanSpeed2 = (int)slider_Fan_Speed_2().Value();
			}
			if (tuningFanSettingsGpu.FanTempSupport2.has_value() && tuningFanSettingsGpu.FanTempSupport2.value())
			{
				tuningFanSettingsProfile.FanTemp2 = (int)slider_Fan_Temp_2().Value();
			}
			if (tuningFanSettingsGpu.FanSpeedSupport3.has_value() && tuningFanSettingsGpu.FanSpeedSupport3.value())
			{
				tuningFanSettingsProfile.FanSpeed3 = (int)slider_Fan_Speed_3().Value();
			}
			if (tuningFanSettingsGpu.FanTempSupport3.has_value() && tuningFanSettingsGpu.FanTempSupport3.value())
			{
				tuningFanSettingsProfile.FanTemp3 = (int)slider_Fan_Temp_3().Value();
			}
			if (tuningFanSettingsGpu.FanSpeedSupport4.has_value() && tuningFanSettingsGpu.FanSpeedSupport4.value())
			{
				tuningFanSettingsProfile.FanSpeed4 = (int)slider_Fan_Speed_4().Value();
			}
			if (tuningFanSettingsGpu.FanTempSupport4.has_value() && tuningFanSettingsGpu.FanTempSupport4.value())
			{
				tuningFanSettingsProfile.FanTemp4 = (int)slider_Fan_Temp_4().Value();
			}

			//Return result
			return tuningFanSettingsProfile;
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

			//Memory Timing
			if (tuningFanSettingsProfile.MemoryTiming.has_value() && tuningFanSettingsGpu.MemoryTiming.has_value())
			{
				if (tuningFanSettingsProfile.MemoryTiming.value() != tuningFanSettingsGpu.MemoryTiming.value()) { return false; }
			}

			//Memory Frequency
			if (tuningFanSettingsProfile.MemoryMax.has_value() && tuningFanSettingsGpu.MemoryMax.has_value())
			{
				if (tuningFanSettingsProfile.MemoryMax.value() != tuningFanSettingsGpu.MemoryMax.value()) { return false; }
			}

			//Power Boost
			if (tuningFanSettingsProfile.PowerBoostUse.has_value() && tuningFanSettingsProfile.PowerBoostUse.value())
			{
				//Power Limit (Power Boost)
				if (tuningFanSettingsProfile.PowerLimitPB.has_value() && tuningFanSettingsGpu.PowerLimit.has_value())
				{
					if (tuningFanSettingsProfile.PowerLimitPB.value() != tuningFanSettingsGpu.PowerLimit.value()) { return false; }
				}

				//Power Voltage (Power Boost)
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
				//Power Limit
				if (tuningFanSettingsProfile.PowerLimit.has_value() && tuningFanSettingsGpu.PowerLimit.has_value())
				{
					if (tuningFanSettingsProfile.PowerLimit.value() != tuningFanSettingsGpu.PowerLimit.value()) { return false; }
				}

				//Power Voltage
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

			//Fan Control
			if (tuningFanSettingsProfile.FanControl.has_value() && tuningFanSettingsProfile.FanControl.value())
			{
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
		}
		catch (...) {}
		return true;
	}
}