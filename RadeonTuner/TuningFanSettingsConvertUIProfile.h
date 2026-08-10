#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::TuningFanSettings_Convert_ToUI_Profile(TuningFanSettings tuningFanSettings, AdlSettingGet settingType)
	{
		try
		{
			//Gpu Core Minimum
			if (tuningFanSettings.CoreMin.Get(settingType).has_value())
			{
				slider_Core_Min().Value(tuningFanSettings.CoreMin.Get(settingType).value());
			}

			//Gpu Core Maximum
			if (tuningFanSettings.CoreMax.Get(settingType).has_value())
			{
				slider_Core_Max().Value(tuningFanSettings.CoreMax.Get(settingType).value());
			}

			//Memory Timing
			if (tuningFanSettings.MemoryTiming.Get(settingType).has_value())
			{
				combobox_Memory_Timing().SelectedIndex(tuningFanSettings.MemoryTiming.Get(settingType).value());
			}

			//Memory Frequency
			if (tuningFanSettings.MemoryMax.Get(settingType).has_value())
			{
				slider_Memory_Max().Value(tuningFanSettings.MemoryMax.Get(settingType).value());
			}

			//Power Limit
			if (tuningFanSettings.PowerLimit.Get(settingType).has_value())
			{
				slider_Power_Limit().Value(tuningFanSettings.PowerLimit.Get(settingType).value());
			}

			//Power Voltage
			if (tuningFanSettings.PowerVoltage.Get(settingType).has_value())
			{
				slider_Power_Voltage().Value(tuningFanSettings.PowerVoltage.Get(settingType).value());
			}

			//Power TDC
			if (tuningFanSettings.PowerTDC.Get(settingType).has_value())
			{
				slider_Power_TDC().Value(tuningFanSettings.PowerTDC.Get(settingType).value());
			}

			//Fan Control
			bool fanControl = false;
			if (tuningFanSettings.FanControl.Get(settingType).has_value())
			{
				fanControl = tuningFanSettings.FanControl.Get(settingType).value();
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
			if (tuningFanSettings.FanZeroRpm.Get(settingType).has_value())
			{
				bool zeroRpm = tuningFanSettings.FanZeroRpm.Get(settingType).value();
				toggleswitch_Fan_Zero_Rpm().IsOn(zeroRpm);

				//Enable or disable interface
				toggleswitch_Fan_Zero_Rpm().IsEnabled(fanControl);

				//Show or hide Zero RPM line
				grid_Fan_Zero_Rpm_Line_Profile().Visibility(zeroRpm ? Visibility::Visible : Visibility::Collapsed);
				border_Fan_Zero_Rpm_Range().Visibility(zeroRpm ? Visibility::Visible : Visibility::Collapsed);
			}

			//Fan Speed 0
			if (tuningFanSettings.FanSpeed0.Get(settingType).has_value())
			{
				slider_Fan_Speed_0().Value(tuningFanSettings.FanSpeed0.Get(settingType).value());

				//Enable or disable interface
				slider_Fan_Speed_0().IsEnabled(fanControl);
			}

			//Fan Temperature 0
			if (tuningFanSettings.FanTemp0.Get(settingType).has_value())
			{
				slider_Fan_Temp_0().Value(tuningFanSettings.FanTemp0.Get(settingType).value());

				//Enable or disable interface
				slider_Fan_Temp_0().IsEnabled(fanControl);
			}

			//Fan Speed 1
			if (tuningFanSettings.FanSpeed1.Get(settingType).has_value())
			{
				slider_Fan_Speed_1().Value(tuningFanSettings.FanSpeed1.Get(settingType).value());

				//Enable or disable interface
				slider_Fan_Speed_1().IsEnabled(fanControl);
			}

			//Fan Temperature 1
			if (tuningFanSettings.FanTemp1.Get(settingType).has_value())
			{
				slider_Fan_Temp_1().Value(tuningFanSettings.FanTemp1.Get(settingType).value());

				//Enable or disable interface
				slider_Fan_Temp_1().IsEnabled(fanControl);
			}

			//Fan Speed 2
			if (tuningFanSettings.FanSpeed2.Get(settingType).has_value())
			{
				slider_Fan_Speed_2().Value(tuningFanSettings.FanSpeed2.Get(settingType).value());

				//Enable or disable interface
				slider_Fan_Speed_2().IsEnabled(fanControl);
			}

			//Fan Temperature 2
			if (tuningFanSettings.FanTemp2.Get(settingType).has_value())
			{
				slider_Fan_Temp_2().Value(tuningFanSettings.FanTemp2.Get(settingType).value());

				//Enable or disable interface
				slider_Fan_Temp_2().IsEnabled(fanControl);
			}

			//Fan Speed 3
			if (tuningFanSettings.FanSpeed3.Get(settingType).has_value())
			{
				slider_Fan_Speed_3().Value(tuningFanSettings.FanSpeed3.Get(settingType).value());

				//Enable or disable interface
				slider_Fan_Speed_3().IsEnabled(fanControl);
			}

			//Fan Temperature 3
			if (tuningFanSettings.FanTemp3.Get(settingType).has_value())
			{
				slider_Fan_Temp_3().Value(tuningFanSettings.FanTemp3.Get(settingType).value());

				//Enable or disable interface
				slider_Fan_Temp_3().IsEnabled(fanControl);
			}

			//Fan Speed 4
			if (tuningFanSettings.FanSpeed4.Get(settingType).has_value())
			{
				slider_Fan_Speed_4().Value(tuningFanSettings.FanSpeed4.Get(settingType).value());

				//Enable or disable interface
				slider_Fan_Speed_4().IsEnabled(fanControl);
			}

			//Fan Temperature 4
			if (tuningFanSettings.FanTemp4.Get(settingType).has_value())
			{
				slider_Fan_Temp_4().Value(tuningFanSettings.FanTemp4.Get(settingType).value());

				//Enable or disable interface
				slider_Fan_Temp_4().IsEnabled(fanControl);
			}

			//Update fan graph
			UpdateFanGraphProfile();

			//Keep Active
			if (tuningFanSettings.KeepActive.Get(settingType).has_value())
			{
				bool keepActive = tuningFanSettings.KeepActive.Get(settingType).value();
				toggleswitch_KeepActive().IsOn(keepActive);
				textblock_KeepActive_Value().Text(keepActive ? L"Enabled" : L"Disabled");
			}
			else
			{
				toggleswitch_KeepActive().IsOn(false);
				textblock_KeepActive_Value().Text(L"Disabled");
			}

			//Set result
			AVDebugWriteLine(L"Tuning and fans settings applied to interface (Profile)");
			return true;
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine(L"Failed applying tuning and fans settings to interface (Profile)");
			return false;
		}
	}
}