#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::TuningFanSettings_ADL_Convert_ToUI(TuningFanSettings tuningFanSettings)
	{
		try
		{
			//Gpu Core Minimum
			if (tuningFanSettings.CoreMin.Current.has_value())
			{
				//Set value text
				std::wstring valueText = number_to_wstring(tuningFanSettings.CoreMin.Current.value()) + L"MHz";
				textblock_Core_Min_Value().Text(valueText);

				//Set interface
				if (tuningFanSettings.CoreMin.Minimum.has_value())
				{
					slider_Core_Min().Minimum(tuningFanSettings.CoreMin.Minimum.value());
					slider_Core_Min().Maximum(tuningFanSettings.CoreMin.Maximum.value());
					slider_Core_Min().StepFrequency(tuningFanSettings.CoreMin.Step.value());
					slider_Core_Min().SmallChange(tuningFanSettings.CoreMin.Step.value());
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
			if (tuningFanSettings.CoreMax.Current.has_value())
			{
				//Set value text
				std::wstring valueText = number_to_wstring(tuningFanSettings.CoreMax.Current.value()) + L"MHz";
				textblock_Core_Max_Value().Text(valueText);

				//Set interface
				if (tuningFanSettings.CoreMax.Minimum.has_value())
				{
					slider_Core_Max().Minimum(tuningFanSettings.CoreMax.Minimum.value());
					slider_Core_Max().Maximum(tuningFanSettings.CoreMax.Maximum.value());
					slider_Core_Max().StepFrequency(tuningFanSettings.CoreMax.Step.value());
					slider_Core_Max().SmallChange(tuningFanSettings.CoreMax.Step.value());

					//Check if value is offset (RDNA4+)
					if (tuningFanSettings.CoreMax.Minimum.value() < 0)
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
			if (tuningFanSettings.MemoryTiming.Current.has_value())
			{
				//Set value text
				std::wstring valueText = ADLX_MEMORYTIMING_DESCRIPTION_STRING[tuningFanSettings.MemoryTiming.Current.value()];
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
			if (tuningFanSettings.MemoryMax.Current.has_value())
			{
				//Set value text
				std::wstring valueText = number_to_wstring(tuningFanSettings.MemoryMax.Current.value()) + L"MTs";
				textblock_Memory_Max_Value().Text(valueText);

				//Set interface
				if (tuningFanSettings.MemoryMax.Minimum.has_value())
				{
					slider_Memory_Max().Minimum(tuningFanSettings.MemoryMax.Minimum.value());
					slider_Memory_Max().Maximum(tuningFanSettings.MemoryMax.Maximum.value());
					slider_Memory_Max().StepFrequency(tuningFanSettings.MemoryMax.Step.value());
					slider_Memory_Max().SmallChange(tuningFanSettings.MemoryMax.Step.value());
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
			if (tuningFanSettings.PowerLimit.Current.has_value())
			{
				//Set value text
				std::wstring valueText = number_to_wstring(tuningFanSettings.PowerLimit.Current.value()) + L"%";
				textblock_Power_Limit_Value().Text(valueText);

				//Set interface
				if (tuningFanSettings.PowerLimit.Minimum.has_value())
				{
					slider_Power_Limit().Minimum(tuningFanSettings.PowerLimit.Minimum.value());
					slider_Power_Limit().Maximum(tuningFanSettings.PowerLimit.Maximum.value());
					slider_Power_Limit().StepFrequency(tuningFanSettings.PowerLimit.Step.value());
					slider_Power_Limit().SmallChange(tuningFanSettings.PowerLimit.Step.value());
					slider_Power_Limit_PB().Minimum(tuningFanSettings.PowerLimit.Minimum.value());
					slider_Power_Limit_PB().Maximum(tuningFanSettings.PowerLimit.Maximum.value());
					slider_Power_Limit_PB().StepFrequency(tuningFanSettings.PowerLimit.Step.value());
					slider_Power_Limit_PB().SmallChange(tuningFanSettings.PowerLimit.Step.value());
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
			if (tuningFanSettings.PowerVoltage.Current.has_value())
			{
				//Set value text
				std::wstring valueText = number_to_wstring(tuningFanSettings.PowerVoltage.Current.value()) + L"mV";
				textblock_Power_Voltage_Value().Text(valueText);

				//Set interface
				if (tuningFanSettings.PowerVoltage.Minimum.has_value())
				{
					slider_Power_Voltage().Minimum(tuningFanSettings.PowerVoltage.Minimum.value());
					slider_Power_Voltage().Maximum(tuningFanSettings.PowerVoltage.Maximum.value());
					slider_Power_Voltage().StepFrequency(tuningFanSettings.PowerVoltage.Step.value());
					slider_Power_Voltage().SmallChange(tuningFanSettings.PowerVoltage.Step.value());
					slider_Power_Voltage_PB().Minimum(tuningFanSettings.PowerVoltage.Minimum.value());
					slider_Power_Voltage_PB().Maximum(tuningFanSettings.PowerVoltage.Maximum.value());
					slider_Power_Voltage_PB().StepFrequency(tuningFanSettings.PowerVoltage.Step.value());
					slider_Power_Voltage_PB().SmallChange(tuningFanSettings.PowerVoltage.Step.value());

					//Check if value is offset (RDNA4+)
					if (tuningFanSettings.PowerVoltage.Minimum.value() < 0)
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
			if (tuningFanSettings.PowerTDC.Current.has_value())
			{
				//Set value text
				std::wstring valueText = number_to_wstring(tuningFanSettings.PowerTDC.Current.value()) + L"%";
				textblock_Power_TDC_Value().Text(valueText);

				//Set interface
				if (tuningFanSettings.PowerTDC.Minimum.has_value())
				{
					slider_Power_TDC().Minimum(tuningFanSettings.PowerTDC.Minimum.value());
					slider_Power_TDC().Maximum(tuningFanSettings.PowerTDC.Maximum.value());
					slider_Power_TDC().StepFrequency(tuningFanSettings.PowerTDC.Step.value());
					slider_Power_TDC().SmallChange(tuningFanSettings.PowerTDC.Step.value());
					slider_Power_TDC_PB().Minimum(tuningFanSettings.PowerTDC.Minimum.value());
					slider_Power_TDC_PB().Maximum(tuningFanSettings.PowerTDC.Maximum.value());
					slider_Power_TDC_PB().StepFrequency(tuningFanSettings.PowerTDC.Step.value());
					slider_Power_TDC_PB().SmallChange(tuningFanSettings.PowerTDC.Step.value());
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
			if (tuningFanSettings.FanZeroRpm.Current.has_value())
			{
				//Set value text
				bool zeroRpm = tuningFanSettings.FanZeroRpm.Current.value();
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
			if (tuningFanSettings.FanSpeed0.Current.has_value())
			{
				//Set value text
				textblock_Fan_Curve_0_Speed_Value().Text(number_to_wstring(tuningFanSettings.FanSpeed0.Current.value()) + L"%");

				//Set interface
				if (tuningFanSettings.FanSpeed0.Minimum.has_value())
				{
					slider_Fan_Speed_0().Minimum(tuningFanSettings.FanSpeed0.Minimum.value());
					slider_Fan_Speed_0().Maximum(tuningFanSettings.FanSpeed0.Maximum.value());
					slider_Fan_Speed_0().StepFrequency(tuningFanSettings.FanSpeed0.Step.value());
					slider_Fan_Speed_0().SmallChange(tuningFanSettings.FanSpeed0.Step.value());
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
			if (tuningFanSettings.FanTemp0.Current.has_value())
			{
				//Set value text
				textblock_Fan_Curve_0_Temp_Value().Text(number_to_wstring(tuningFanSettings.FanTemp0.Current.value()) + L"C");

				//Set interface
				if (tuningFanSettings.FanTemp0.Minimum.has_value())
				{
					slider_Fan_Temp_0().Minimum(tuningFanSettings.FanTemp0.Minimum.value());
					slider_Fan_Temp_0().Maximum(tuningFanSettings.FanTemp0.Maximum.value());
					slider_Fan_Temp_0().StepFrequency(tuningFanSettings.FanTemp0.Step.value());
					slider_Fan_Temp_0().SmallChange(tuningFanSettings.FanTemp0.Step.value());
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
			if (tuningFanSettings.FanSpeed1.Current.has_value())
			{
				//Set value text
				textblock_Fan_Curve_1_Speed_Value().Text(number_to_wstring(tuningFanSettings.FanSpeed1.Current.value()) + L"%");

				//Set interface
				if (tuningFanSettings.FanSpeed1.Minimum.has_value())
				{
					slider_Fan_Speed_1().Minimum(tuningFanSettings.FanSpeed1.Minimum.value());
					slider_Fan_Speed_1().Maximum(tuningFanSettings.FanSpeed1.Maximum.value());
					slider_Fan_Speed_1().StepFrequency(tuningFanSettings.FanSpeed1.Step.value());
					slider_Fan_Speed_1().SmallChange(tuningFanSettings.FanSpeed1.Step.value());
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
			if (tuningFanSettings.FanTemp1.Current.has_value())
			{
				//Set value text
				textblock_Fan_Curve_1_Temp_Value().Text(number_to_wstring(tuningFanSettings.FanTemp1.Current.value()) + L"C");

				//Set interface
				if (tuningFanSettings.FanTemp1.Minimum.has_value())
				{
					slider_Fan_Temp_1().Minimum(tuningFanSettings.FanTemp1.Minimum.value());
					slider_Fan_Temp_1().Maximum(tuningFanSettings.FanTemp1.Maximum.value());
					slider_Fan_Temp_1().StepFrequency(tuningFanSettings.FanTemp1.Step.value());
					slider_Fan_Temp_1().SmallChange(tuningFanSettings.FanTemp1.Step.value());
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
			if (tuningFanSettings.FanSpeed2.Current.has_value())
			{
				//Set value text
				textblock_Fan_Curve_2_Speed_Value().Text(number_to_wstring(tuningFanSettings.FanSpeed2.Current.value()) + L"%");

				//Set interface
				if (tuningFanSettings.FanSpeed2.Minimum.has_value())
				{
					slider_Fan_Speed_2().Minimum(tuningFanSettings.FanSpeed2.Minimum.value());
					slider_Fan_Speed_2().Maximum(tuningFanSettings.FanSpeed2.Maximum.value());
					slider_Fan_Speed_2().StepFrequency(tuningFanSettings.FanSpeed2.Step.value());
					slider_Fan_Speed_2().SmallChange(tuningFanSettings.FanSpeed2.Step.value());
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
			if (tuningFanSettings.FanTemp2.Current.has_value())
			{
				//Set value text
				textblock_Fan_Curve_2_Temp_Value().Text(number_to_wstring(tuningFanSettings.FanTemp2.Current.value()) + L"C");

				//Set interface
				if (tuningFanSettings.FanTemp2.Minimum.has_value())
				{
					slider_Fan_Temp_2().Minimum(tuningFanSettings.FanTemp2.Minimum.value());
					slider_Fan_Temp_2().Maximum(tuningFanSettings.FanTemp2.Maximum.value());
					slider_Fan_Temp_2().StepFrequency(tuningFanSettings.FanTemp2.Step.value());
					slider_Fan_Temp_2().SmallChange(tuningFanSettings.FanTemp2.Step.value());
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
			if (tuningFanSettings.FanSpeed3.Current.has_value())
			{
				//Set value text
				textblock_Fan_Curve_3_Speed_Value().Text(number_to_wstring(tuningFanSettings.FanSpeed3.Current.value()) + L"%");

				//Set interface
				if (tuningFanSettings.FanSpeed3.Minimum.has_value())
				{
					slider_Fan_Speed_3().Minimum(tuningFanSettings.FanSpeed3.Minimum.value());
					slider_Fan_Speed_3().Maximum(tuningFanSettings.FanSpeed3.Maximum.value());
					slider_Fan_Speed_3().StepFrequency(tuningFanSettings.FanSpeed3.Step.value());
					slider_Fan_Speed_3().SmallChange(tuningFanSettings.FanSpeed3.Step.value());
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
			if (tuningFanSettings.FanTemp3.Current.has_value())
			{
				//Set value text
				textblock_Fan_Curve_3_Temp_Value().Text(number_to_wstring(tuningFanSettings.FanTemp3.Current.value()) + L"C");

				//Set interface
				if (tuningFanSettings.FanTemp3.Minimum.has_value())
				{
					slider_Fan_Temp_3().Minimum(tuningFanSettings.FanTemp3.Minimum.value());
					slider_Fan_Temp_3().Maximum(tuningFanSettings.FanTemp3.Maximum.value());
					slider_Fan_Temp_3().StepFrequency(tuningFanSettings.FanTemp3.Step.value());
					slider_Fan_Temp_3().SmallChange(tuningFanSettings.FanTemp3.Step.value());
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
			if (tuningFanSettings.FanSpeed4.Current.has_value())
			{
				//Set value text
				textblock_Fan_Curve_4_Speed_Value().Text(number_to_wstring(tuningFanSettings.FanSpeed4.Current.value()) + L"%");

				//Set interface
				if (tuningFanSettings.FanSpeed4.Minimum.has_value())
				{
					slider_Fan_Speed_4().Minimum(tuningFanSettings.FanSpeed4.Minimum.value());
					slider_Fan_Speed_4().Maximum(tuningFanSettings.FanSpeed4.Maximum.value());
					slider_Fan_Speed_4().StepFrequency(tuningFanSettings.FanSpeed4.Step.value());
					slider_Fan_Speed_4().SmallChange(tuningFanSettings.FanSpeed4.Step.value());
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
			if (tuningFanSettings.FanTemp4.Current.has_value())
			{
				//Set value text
				textblock_Fan_Curve_4_Temp_Value().Text(number_to_wstring(tuningFanSettings.FanTemp4.Current.value()) + L"C");

				//Set interface
				if (tuningFanSettings.FanTemp4.Minimum.has_value())
				{
					slider_Fan_Temp_4().Minimum(tuningFanSettings.FanTemp4.Minimum.value());
					slider_Fan_Temp_4().Maximum(tuningFanSettings.FanTemp4.Maximum.value());
					slider_Fan_Temp_4().StepFrequency(tuningFanSettings.FanTemp4.Step.value());
					slider_Fan_Temp_4().SmallChange(tuningFanSettings.FanTemp4.Step.value());
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
			if (!tuningFanSettings.TuningSupport)
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
			if (!tuningFanSettings.FanSupport)
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
			AVDebugWriteLine(L"ADL tuning and fans settings applied to interface.");
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine(L"Failed applying ADL tuning and fans settings to interface.");
			return false;
		}
	}

	bool MainPage::TuningFanSettings_Profile_Convert_ToUI(TuningFanSettings tuningFanSettings)
	{
		try
		{
			//Gpu Core Minimum
			if (tuningFanSettings.CoreMin.Current.has_value())
			{
				slider_Core_Min().Value(tuningFanSettings.CoreMin.Current.value());
			}

			//Gpu Core Maximum
			if (tuningFanSettings.CoreMax.Current.has_value())
			{
				slider_Core_Max().Value(tuningFanSettings.CoreMax.Current.value());
			}

			//Memory Timing
			if (tuningFanSettings.MemoryTiming.Current.has_value())
			{
				combobox_Memory_Timing().SelectedIndex(tuningFanSettings.MemoryTiming.Current.value());
			}

			//Memory Frequency
			if (tuningFanSettings.MemoryMax.Current.has_value())
			{
				slider_Memory_Max().Value(tuningFanSettings.MemoryMax.Current.value());
			}

			//Power Limit
			if (tuningFanSettings.PowerLimit.Current.has_value())
			{
				slider_Power_Limit().Value(tuningFanSettings.PowerLimit.Current.value());
			}

			//Power Limit (Power Boost)
			if (tuningFanSettings.PowerLimitPB.Current.has_value())
			{
				slider_Power_Limit_PB().Value(tuningFanSettings.PowerLimitPB.Current.value());
			}

			//Power Voltage
			if (tuningFanSettings.PowerVoltage.Current.has_value())
			{
				slider_Power_Voltage().Value(tuningFanSettings.PowerVoltage.Current.value());
			}

			//Power Voltage (Power Boost)
			if (tuningFanSettings.PowerVoltagePB.Current.has_value())
			{
				slider_Power_Voltage_PB().Value(tuningFanSettings.PowerVoltagePB.Current.value());
			}

			//Power TDC
			if (tuningFanSettings.PowerTDC.Current.has_value())
			{
				slider_Power_TDC().Value(tuningFanSettings.PowerTDC.Current.value());
			}

			//Power TDC (Power Boost)
			if (tuningFanSettings.PowerTDCPB.Current.has_value())
			{
				slider_Power_TDC_PB().Value(tuningFanSettings.PowerTDCPB.Current.value());
			}

			//Fan Control
			bool fanControl = false;
			if (tuningFanSettings.FanControl.Current.has_value())
			{
				fanControl = tuningFanSettings.FanControl.Current.value();
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
			if (tuningFanSettings.FanZeroRpm.Current.has_value())
			{
				bool zeroRpm = tuningFanSettings.FanZeroRpm.Current.value();
				toggleswitch_Fan_Zero_Rpm().IsOn(zeroRpm);

				//Enable or disable interface
				toggleswitch_Fan_Zero_Rpm().IsEnabled(fanControl);

				//Show or hide Zero RPM line
				grid_Fan_Zero_Rpm_Line_Profile().Visibility(zeroRpm ? Visibility::Visible : Visibility::Collapsed);
			}

			//Fan Speed 0
			if (tuningFanSettings.FanSpeed0.Current.has_value())
			{
				slider_Fan_Speed_0().Value(tuningFanSettings.FanSpeed0.Current.value());

				//Enable or disable interface
				slider_Fan_Speed_0().IsEnabled(fanControl);
			}

			//Fan Temperature 0
			if (tuningFanSettings.FanTemp0.Current.has_value())
			{
				slider_Fan_Temp_0().Value(tuningFanSettings.FanTemp0.Current.value());

				//Enable or disable interface
				slider_Fan_Temp_0().IsEnabled(fanControl);
			}

			//Fan Speed 1
			if (tuningFanSettings.FanSpeed1.Current.has_value())
			{
				slider_Fan_Speed_1().Value(tuningFanSettings.FanSpeed1.Current.value());

				//Enable or disable interface
				slider_Fan_Speed_1().IsEnabled(fanControl);
			}

			//Fan Temperature 1
			if (tuningFanSettings.FanTemp1.Current.has_value())
			{
				slider_Fan_Temp_1().Value(tuningFanSettings.FanTemp1.Current.value());

				//Enable or disable interface
				slider_Fan_Temp_1().IsEnabled(fanControl);
			}

			//Fan Speed 2
			if (tuningFanSettings.FanSpeed2.Current.has_value())
			{
				slider_Fan_Speed_2().Value(tuningFanSettings.FanSpeed2.Current.value());

				//Enable or disable interface
				slider_Fan_Speed_2().IsEnabled(fanControl);
			}

			//Fan Temperature 2
			if (tuningFanSettings.FanTemp2.Current.has_value())
			{
				slider_Fan_Temp_2().Value(tuningFanSettings.FanTemp2.Current.value());

				//Enable or disable interface
				slider_Fan_Temp_2().IsEnabled(fanControl);
			}

			//Fan Speed 3
			if (tuningFanSettings.FanSpeed3.Current.has_value())
			{
				slider_Fan_Speed_3().Value(tuningFanSettings.FanSpeed3.Current.value());

				//Enable or disable interface
				slider_Fan_Speed_3().IsEnabled(fanControl);
			}

			//Fan Temperature 3
			if (tuningFanSettings.FanTemp3.Current.has_value())
			{
				slider_Fan_Temp_3().Value(tuningFanSettings.FanTemp3.Current.value());

				//Enable or disable interface
				slider_Fan_Temp_3().IsEnabled(fanControl);
			}

			//Fan Speed 4
			if (tuningFanSettings.FanSpeed4.Current.has_value())
			{
				slider_Fan_Speed_4().Value(tuningFanSettings.FanSpeed4.Current.value());

				//Enable or disable interface
				slider_Fan_Speed_4().IsEnabled(fanControl);
			}

			//Fan Temperature 4
			if (tuningFanSettings.FanTemp4.Current.has_value())
			{
				slider_Fan_Temp_4().Value(tuningFanSettings.FanTemp4.Current.value());

				//Enable or disable interface
				slider_Fan_Temp_4().IsEnabled(fanControl);
			}

			//Update fan graph
			UpdateFanGraphProfile();

			//Keep Active
			if (tuningFanSettings.KeepActive.Current.has_value())
			{
				bool keepActive = tuningFanSettings.KeepActive.Current.value();
				toggleswitch_KeepActive().IsOn(keepActive);
				textblock_KeepActive_Value().Text(keepActive ? L"Enabled" : L"Disabled");
			}
			else
			{
				toggleswitch_KeepActive().IsOn(false);
				textblock_KeepActive_Value().Text(L"Disabled");
			}

			//Power Boost
			if (tuningFanSettings.PowerBoost.Current.has_value())
			{
				bool powerBoost = tuningFanSettings.PowerBoost.Current.value();
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
			AVDebugWriteLine(L"Profile tuning and fans settings applied to interface.");
			return true;
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine(L"Failed applying profile tuning and fans settings to interface.");
			return false;
		}
	}

	std::optional<TuningFanSettings> MainPage::TuningFanSettings_Generate_FromUI()
	{
		try
		{
			//Get current and default settings
			TuningFanSettings tuningFanSettingsAdl = TuningFanSettings_Generate_FromADL(adl_Gpu_AdapterIndex).value();
			TuningFanSettings tuningFanSettingsProfile{};

			//Device identifier
			{
				tuningFanSettingsProfile.DeviceId = tuningFanSettingsAdl.DeviceId;
			}

			//Keep Active
			if (tuningFanSettingsAdl.TuningSupport)
			{
				tuningFanSettingsProfile.KeepActive.Current = (bool)toggleswitch_KeepActive().IsOn();
			}

			//Gpu Core Minimum
			if (tuningFanSettingsAdl.CoreMin.Support.has_value() && tuningFanSettingsAdl.CoreMin.Support.value())
			{
				tuningFanSettingsProfile.CoreMin.Current = (int)slider_Core_Min().Value();
			}

			//Gpu Core Maximum
			if (tuningFanSettingsAdl.CoreMax.Support.has_value() && tuningFanSettingsAdl.CoreMax.Support.value())
			{
				tuningFanSettingsProfile.CoreMax.Current = (int)slider_Core_Max().Value();
			}

			//Memory Timing
			if (tuningFanSettingsAdl.MemoryTiming.Support.has_value() && tuningFanSettingsAdl.MemoryTiming.Support.value())
			{
				tuningFanSettingsProfile.MemoryTiming.Current = (int)combobox_Memory_Timing().SelectedIndex();
			}

			//Memory Frequency
			if (tuningFanSettingsAdl.MemoryMax.Support.has_value() && tuningFanSettingsAdl.MemoryMax.Support.value())
			{
				tuningFanSettingsProfile.MemoryMax.Current = (int)slider_Memory_Max().Value();
			}

			//Power
			if (tuningFanSettingsAdl.PowerLimit.Support.has_value() && tuningFanSettingsAdl.PowerLimit.Support.value())
			{
				tuningFanSettingsProfile.PowerLimit.Current = (int)slider_Power_Limit().Value();
			}
			if (tuningFanSettingsAdl.PowerVoltage.Support.has_value() && tuningFanSettingsAdl.PowerVoltage.Support.value())
			{
				tuningFanSettingsProfile.PowerVoltage.Current = (int)slider_Power_Voltage().Value();
			}
			if (tuningFanSettingsAdl.PowerTDC.Support.has_value() && tuningFanSettingsAdl.PowerTDC.Support.value())
			{
				tuningFanSettingsProfile.PowerTDC.Current = (int)slider_Power_TDC().Value();
			}

			//Power Boost
			if (tuningFanSettingsAdl.TuningSupport)
			{
				tuningFanSettingsProfile.PowerBoost.Current = (bool)toggleswitch_PowerBoost().IsOn();
			}
			if (tuningFanSettingsAdl.PowerLimit.Support.has_value() && tuningFanSettingsAdl.PowerLimit.Support.value())
			{
				tuningFanSettingsProfile.PowerLimitPB.Current = (int)slider_Power_Limit_PB().Value();
			}
			if (tuningFanSettingsAdl.PowerVoltage.Support.has_value() && tuningFanSettingsAdl.PowerVoltage.Support.value())
			{
				tuningFanSettingsProfile.PowerVoltagePB.Current = (int)slider_Power_Voltage_PB().Value();
			}
			if (tuningFanSettingsAdl.PowerTDC.Support.has_value() && tuningFanSettingsAdl.PowerTDC.Support.value())
			{
				tuningFanSettingsProfile.PowerTDCPB.Current = (int)slider_Power_TDC_PB().Value();
			}

			//Fans
			if (tuningFanSettingsAdl.FanSupport)
			{
				tuningFanSettingsProfile.FanControl.Current = (bool)toggleswitch_Fan_Control().IsOn();
			}
			if (tuningFanSettingsAdl.FanZeroRpm.Support.has_value() && tuningFanSettingsAdl.FanZeroRpm.Support.value())
			{
				tuningFanSettingsProfile.FanZeroRpm.Current = (bool)toggleswitch_Fan_Zero_Rpm().IsOn();
			}
			if (tuningFanSettingsAdl.FanSpeed0.Support.has_value() && tuningFanSettingsAdl.FanSpeed0.Support.value())
			{
				tuningFanSettingsProfile.FanSpeed0.Current = (int)slider_Fan_Speed_0().Value();
			}
			if (tuningFanSettingsAdl.FanTemp0.Support.has_value() && tuningFanSettingsAdl.FanTemp0.Support.value())
			{
				tuningFanSettingsProfile.FanTemp0.Current = (int)slider_Fan_Temp_0().Value();
			}
			if (tuningFanSettingsAdl.FanSpeed1.Support.has_value() && tuningFanSettingsAdl.FanSpeed1.Support.value())
			{
				tuningFanSettingsProfile.FanSpeed1.Current = (int)slider_Fan_Speed_1().Value();
			}
			if (tuningFanSettingsAdl.FanTemp1.Support.has_value() && tuningFanSettingsAdl.FanTemp1.Support.value())
			{
				tuningFanSettingsProfile.FanTemp1.Current = (int)slider_Fan_Temp_1().Value();
			}
			if (tuningFanSettingsAdl.FanSpeed2.Support.has_value() && tuningFanSettingsAdl.FanSpeed2.Support.value())
			{
				tuningFanSettingsProfile.FanSpeed2.Current = (int)slider_Fan_Speed_2().Value();
			}
			if (tuningFanSettingsAdl.FanTemp2.Support.has_value() && tuningFanSettingsAdl.FanTemp2.Support.value())
			{
				tuningFanSettingsProfile.FanTemp2.Current = (int)slider_Fan_Temp_2().Value();
			}
			if (tuningFanSettingsAdl.FanSpeed3.Support.has_value() && tuningFanSettingsAdl.FanSpeed3.Support.value())
			{
				tuningFanSettingsProfile.FanSpeed3.Current = (int)slider_Fan_Speed_3().Value();
			}
			if (tuningFanSettingsAdl.FanTemp3.Support.has_value() && tuningFanSettingsAdl.FanTemp3.Support.value())
			{
				tuningFanSettingsProfile.FanTemp3.Current = (int)slider_Fan_Temp_3().Value();
			}
			if (tuningFanSettingsAdl.FanSpeed4.Support.has_value() && tuningFanSettingsAdl.FanSpeed4.Support.value())
			{
				tuningFanSettingsProfile.FanSpeed4.Current = (int)slider_Fan_Speed_4().Value();
			}
			if (tuningFanSettingsAdl.FanTemp4.Support.has_value() && tuningFanSettingsAdl.FanTemp4.Support.value())
			{
				tuningFanSettingsProfile.FanTemp4.Current = (int)slider_Fan_Temp_4().Value();
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
}