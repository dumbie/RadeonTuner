#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::TuningFanSettings_Convert_ToUI_Adl(TuningFanSettings tuningFanSettings)
	{
		try
		{
			//Gpu Core Minimum
			if (tuningFanSettings.CoreMin.Support)
			{
				//Get setting
				int valueInt = 0;
				if (tuningFanSettings.CoreMin.Current.has_value())
				{
					valueInt = tuningFanSettings.CoreMin.Current.value();
				}
				else if (tuningFanSettings.CoreMin.Default.has_value())
				{
					valueInt = tuningFanSettings.CoreMin.Default.value();
				}

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt) + L"MHz";
				textblock_Core_Min_Value().Text(valueHint);

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
				//Set hint value
				textblock_Core_Min_Value().Text(L"");

				//Enable or disable interface
				slider_Core_Min().IsEnabled(false);
			}

			//Gpu Core Maximum
			if (tuningFanSettings.CoreMax.Support)
			{
				//Get setting
				int valueInt = 0;
				if (tuningFanSettings.CoreMax.Current.has_value())
				{
					valueInt = tuningFanSettings.CoreMax.Current.value();
				}
				else if (tuningFanSettings.CoreMax.Default.has_value())
				{
					valueInt = tuningFanSettings.CoreMax.Default.value();
				}

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt) + L"MHz";
				textblock_Core_Max_Value().Text(valueHint);

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
				//Set hint value
				textblock_Core_Max_Value().Text(L"");

				//Enable or disable interface
				slider_Core_Max().IsEnabled(false);
			}

			//Memory Timing
			if (tuningFanSettings.MemoryTiming.Support)
			{
				//Get setting
				int valueInt = 0;
				if (tuningFanSettings.MemoryTiming.Current.has_value())
				{
					valueInt = tuningFanSettings.MemoryTiming.Current.value();
				}
				else if (tuningFanSettings.MemoryTiming.Default.has_value())
				{
					valueInt = tuningFanSettings.MemoryTiming.Default.value();
				}

				//Set hint value
				std::wstring valueHint = ADLX_MEMORYTIMING_DESCRIPTION_STRING[valueInt];
				textblock_Memory_Timing_Value().Text(valueHint);

				//Enable or disable interface
				combobox_Memory_Timing().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Memory_Timing_Value().Text(L"");

				//Enable or disable interface
				combobox_Memory_Timing().IsEnabled(false);
			}

			//Memory ECC / EDC
			if (tuningFanSettings.MemoryEcc.Support)
			{
				//Get setting
				int valueInt = 0;
				if (tuningFanSettings.MemoryEcc.Current.has_value())
				{
					valueInt = tuningFanSettings.MemoryEcc.Current.value();
				}
				else if (tuningFanSettings.MemoryEcc.Default.has_value())
				{
					valueInt = tuningFanSettings.MemoryEcc.Default.value();
				}

				//Set hint value
				std::wstring valueHint = ADLX_MEMORYECC_STRING[valueInt];
				textblock_Memory_Ecc_Value().Text(valueHint);

				//Enable or disable interface
				combobox_Memory_Ecc().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Memory_Ecc_Value().Text(L"");

				//Enable or disable interface
				combobox_Memory_Ecc().IsEnabled(false);
			}

			//Memory Frequency
			if (tuningFanSettings.MemoryMax.Support)
			{
				//Get setting
				int valueInt = 0;
				if (tuningFanSettings.MemoryMax.Current.has_value())
				{
					valueInt = tuningFanSettings.MemoryMax.Current.value();
				}
				else if (tuningFanSettings.MemoryMax.Default.has_value())
				{
					valueInt = tuningFanSettings.MemoryMax.Default.value();
				}

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt) + L"MTs";
				textblock_Memory_Max_Value().Text(valueHint);

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
				//Set hint value
				textblock_Memory_Max_Value().Text(L"");

				//Enable or disable interface
				slider_Memory_Max().IsEnabled(false);
			}

			//Power Limit
			if (tuningFanSettings.PowerLimit.Support)
			{
				//Get setting
				int valueInt = 0;
				if (tuningFanSettings.PowerLimit.Current.has_value())
				{
					valueInt = tuningFanSettings.PowerLimit.Current.value();
				}
				else if (tuningFanSettings.PowerLimit.Default.has_value())
				{
					valueInt = tuningFanSettings.PowerLimit.Default.value();
				}

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt) + L"%";
				textblock_Power_Limit_Value().Text(valueHint);

				//Set interface
				if (tuningFanSettings.PowerLimit.Minimum.has_value())
				{
					slider_Power_Limit().Minimum(tuningFanSettings.PowerLimit.Minimum.value());
					slider_Power_Limit().Maximum(tuningFanSettings.PowerLimit.Maximum.value());
					slider_Power_Limit().StepFrequency(tuningFanSettings.PowerLimit.Step.value());
					slider_Power_Limit().SmallChange(tuningFanSettings.PowerLimit.Step.value());
				}

				//Enable or disable interface
				slider_Power_Limit().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Power_Limit_Value().Text(L"");

				//Enable or disable interface
				slider_Power_Limit().IsEnabled(false);
			}

			//Power Voltage
			if (tuningFanSettings.PowerVoltage.Support)
			{
				//Get setting
				int valueInt = 0;
				if (tuningFanSettings.PowerVoltage.Current.has_value())
				{
					valueInt = tuningFanSettings.PowerVoltage.Current.value();
				}
				else if (tuningFanSettings.PowerVoltage.Default.has_value())
				{
					valueInt = tuningFanSettings.PowerVoltage.Default.value();
				}

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt) + L"mV";
				textblock_Power_Voltage_Value().Text(valueHint);

				//Set interface
				if (tuningFanSettings.PowerVoltage.Minimum.has_value())
				{
					slider_Power_Voltage().Minimum(tuningFanSettings.PowerVoltage.Minimum.value());
					slider_Power_Voltage().Maximum(tuningFanSettings.PowerVoltage.Maximum.value());
					slider_Power_Voltage().StepFrequency(tuningFanSettings.PowerVoltage.Step.value());
					slider_Power_Voltage().SmallChange(tuningFanSettings.PowerVoltage.Step.value());

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
			}
			else
			{
				//Set hint value
				textblock_Power_Voltage_Value().Text(L"");

				//Enable or disable interface
				slider_Power_Voltage().IsEnabled(false);
			}

			//Power TDC
			if (tuningFanSettings.PowerTDC.Support)
			{
				//Get setting
				int valueInt = 0;
				if (tuningFanSettings.PowerTDC.Current.has_value())
				{
					valueInt = tuningFanSettings.PowerTDC.Current.value();
				}
				else if (tuningFanSettings.PowerTDC.Default.has_value())
				{
					valueInt = tuningFanSettings.PowerTDC.Default.value();
				}

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt) + L"%";
				textblock_Power_TDC_Value().Text(valueHint);

				//Set interface
				if (tuningFanSettings.PowerTDC.Minimum.has_value())
				{
					slider_Power_TDC().Minimum(tuningFanSettings.PowerTDC.Minimum.value());
					slider_Power_TDC().Maximum(tuningFanSettings.PowerTDC.Maximum.value());
					slider_Power_TDC().StepFrequency(tuningFanSettings.PowerTDC.Step.value());
					slider_Power_TDC().SmallChange(tuningFanSettings.PowerTDC.Step.value());
				}

				//Enable or disable interface
				slider_Power_TDC().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Power_TDC_Value().Text(L"");

				//Enable or disable interface
				slider_Power_TDC().IsEnabled(false);
			}

			//Update fan graph
			UpdateFanGraphGpu(tuningFanSettings);

			//Fan Control
			if (tuningFanSettings.FanControl.Support)
			{
				//Get setting
				bool valueBool = false;
				if (tuningFanSettings.FanControl.Current.has_value())
				{
					valueBool = tuningFanSettings.FanControl.Current.value();
				}
				else if (tuningFanSettings.FanControl.Default.has_value())
				{
					valueBool = tuningFanSettings.FanControl.Default.value();
				}

				//Set hint value
				textblock_Fan_Control_Value().Text(valueBool ? L"Enabled" : L"Disabled");

				//Enable or disable interface
				toggleswitch_Fan_Control().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_Fan_Control().IsEnabled(false);
			}

			//Fan Zero RPM
			if (tuningFanSettings.FanZeroRpm.Support)
			{
				//Get setting
				bool valueBool = false;
				if (tuningFanSettings.FanZeroRpm.Current.has_value())
				{
					valueBool = tuningFanSettings.FanZeroRpm.Current.value();
				}
				else if (tuningFanSettings.FanZeroRpm.Default.has_value())
				{
					valueBool = tuningFanSettings.FanZeroRpm.Default.value();
				}

				//Set hint value
				textblock_Fan_Zero_Rpm_Value().Text(valueBool ? L"Enabled" : L"Disabled");

				//Show or hide Zero RPM line
				grid_Fan_Zero_Rpm_Line_Gpu().Visibility(valueBool ? Visibility::Visible : Visibility::Collapsed);

				//Enable or disable interface
				toggleswitch_Fan_Zero_Rpm().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_Fan_Zero_Rpm().IsEnabled(false);
			}

			//Fan Speed 0
			if (tuningFanSettings.FanSpeed0.Support)
			{
				//Get setting
				int valueInt = 0;
				if (tuningFanSettings.FanSpeed0.Current.has_value())
				{
					valueInt = tuningFanSettings.FanSpeed0.Current.value();
				}
				else if (tuningFanSettings.FanSpeed0.Default.has_value())
				{
					valueInt = tuningFanSettings.FanSpeed0.Default.value();
				}

				//Set hint value
				textblock_Fan_Curve_0_Speed_Value().Text(number_to_wstring(valueInt) + L"%");

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
			if (tuningFanSettings.FanTemp0.Support)
			{
				//Get setting
				int valueInt = 0;
				if (tuningFanSettings.FanTemp0.Current.has_value())
				{
					valueInt = tuningFanSettings.FanTemp0.Current.value();
				}
				else if (tuningFanSettings.FanTemp0.Default.has_value())
				{
					valueInt = tuningFanSettings.FanTemp0.Default.value();
				}

				//Set hint value
				textblock_Fan_Curve_0_Temp_Value().Text(number_to_wstring(valueInt) + L"°C");

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
			if (tuningFanSettings.FanSpeed1.Support)
			{
				//Get setting
				int valueInt = 0;
				if (tuningFanSettings.FanSpeed1.Current.has_value())
				{
					valueInt = tuningFanSettings.FanSpeed1.Current.value();
				}
				else if (tuningFanSettings.FanSpeed1.Default.has_value())
				{
					valueInt = tuningFanSettings.FanSpeed1.Default.value();
				}

				//Set hint value
				textblock_Fan_Curve_1_Speed_Value().Text(number_to_wstring(valueInt) + L"%");

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
			if (tuningFanSettings.FanTemp1.Support)
			{
				//Get setting
				int valueInt = 0;
				if (tuningFanSettings.FanTemp1.Current.has_value())
				{
					valueInt = tuningFanSettings.FanTemp1.Current.value();
				}
				else if (tuningFanSettings.FanTemp1.Default.has_value())
				{
					valueInt = tuningFanSettings.FanTemp1.Default.value();
				}

				//Set hint value
				textblock_Fan_Curve_1_Temp_Value().Text(number_to_wstring(valueInt) + L"°C");

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
			if (tuningFanSettings.FanSpeed2.Support)
			{
				//Get setting
				int valueInt = 0;
				if (tuningFanSettings.FanSpeed2.Current.has_value())
				{
					valueInt = tuningFanSettings.FanSpeed2.Current.value();
				}
				else if (tuningFanSettings.FanSpeed2.Default.has_value())
				{
					valueInt = tuningFanSettings.FanSpeed2.Default.value();
				}

				//Set hint value
				textblock_Fan_Curve_2_Speed_Value().Text(number_to_wstring(valueInt) + L"%");

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
			if (tuningFanSettings.FanTemp2.Support)
			{
				//Get setting
				int valueInt = 0;
				if (tuningFanSettings.FanTemp2.Current.has_value())
				{
					valueInt = tuningFanSettings.FanTemp2.Current.value();
				}
				else if (tuningFanSettings.FanTemp2.Default.has_value())
				{
					valueInt = tuningFanSettings.FanTemp2.Default.value();
				}

				//Set hint value
				textblock_Fan_Curve_2_Temp_Value().Text(number_to_wstring(valueInt) + L"°C");

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
			if (tuningFanSettings.FanSpeed3.Support)
			{
				//Get setting
				int valueInt = 0;
				if (tuningFanSettings.FanSpeed3.Current.has_value())
				{
					valueInt = tuningFanSettings.FanSpeed3.Current.value();
				}
				else if (tuningFanSettings.FanSpeed3.Default.has_value())
				{
					valueInt = tuningFanSettings.FanSpeed3.Default.value();
				}

				//Set hint value
				textblock_Fan_Curve_3_Speed_Value().Text(number_to_wstring(valueInt) + L"%");

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
			if (tuningFanSettings.FanTemp3.Support)
			{
				//Get setting
				int valueInt = 0;
				if (tuningFanSettings.FanTemp3.Current.has_value())
				{
					valueInt = tuningFanSettings.FanTemp3.Current.value();
				}
				else if (tuningFanSettings.FanTemp3.Default.has_value())
				{
					valueInt = tuningFanSettings.FanTemp3.Default.value();
				}

				//Set hint value
				textblock_Fan_Curve_3_Temp_Value().Text(number_to_wstring(valueInt) + L"°C");

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
			if (tuningFanSettings.FanSpeed4.Support)
			{
				//Get setting
				int valueInt = 0;
				if (tuningFanSettings.FanSpeed4.Current.has_value())
				{
					valueInt = tuningFanSettings.FanSpeed4.Current.value();
				}
				else if (tuningFanSettings.FanSpeed4.Default.has_value())
				{
					valueInt = tuningFanSettings.FanSpeed4.Default.value();
				}

				//Set hint value
				textblock_Fan_Curve_4_Speed_Value().Text(number_to_wstring(valueInt) + L"%");

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
			if (tuningFanSettings.FanTemp4.Support)
			{
				//Get setting
				int valueInt = 0;
				if (tuningFanSettings.FanTemp4.Current.has_value())
				{
					valueInt = tuningFanSettings.FanTemp4.Current.value();
				}
				else if (tuningFanSettings.FanTemp4.Default.has_value())
				{
					valueInt = tuningFanSettings.FanTemp4.Default.value();
				}

				//Set hint value
				textblock_Fan_Curve_4_Temp_Value().Text(number_to_wstring(valueInt) + L"°C");

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
				button_AppSelect_Tuning().IsEnabled(false);
				button_AppAdd_Tuning().IsEnabled(false);
				button_AppRemove_Tuning().IsEnabled(false);
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
				button_AppSelect_Tuning().IsEnabled(true);
				button_AppAdd_Tuning().IsEnabled(true);
				button_AppRemove_Tuning().IsEnabled(true);
				button_Tuning_Apply().IsEnabled(true);
				button_Tuning_Reset().IsEnabled(true);
				button_Tuning_Import().IsEnabled(true);
				button_Tuning_Export().IsEnabled(true);

				//Custom settings
				toggleswitch_KeepActive().IsEnabled(true);
			}

			//Enable or disable fan interface
			if (!tuningFanSettings.FanSupport)
			{
				//Top buttons
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
				//Top buttons
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
			AVDebugWriteLine(L"Tuning and fans settings applied to interface (ADL)");
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine(L"Failed applying tuning and fans settings to interface (ADL)");
			return false;
		}
	}
}