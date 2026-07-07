#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::TuningFanSettings_Convert_ToUI_Current(TuningFanSettings tuningFanSettings)
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
}