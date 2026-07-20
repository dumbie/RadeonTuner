#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::button_Tuning_Apply_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Apply tuning and fans settings
			if (AdlTuningApply(adl_Gpu_AdapterIndex, tuningFanSettingsCurrent))
			{
				//Replace tuning and fans settings
				TuningFanSettings_Profile_Replace(tuningFanSettingsCurrent);

				//Save tuning and fans settings
				TuningFanSettings_Profiles_SaveToFile();

				//Load tuning values to interface
				AdlxValuesLoadTuning();

				//Show notification
				ShowNotification(L"Tuning and fans settings applied");
				AVDebugWriteLine(L"Tuning and fans settings applied");
			}
			else
			{
				//Update button colors
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				button_Tuning_Apply().Background(colorInvalid);
				button_Fan_Apply().Background(colorInvalid);

				//Show notification
				ShowNotification(L"Failed applying tuning and fans settings");
				AVDebugWriteLine(L"Failed applying tuning and fans settings");
			}
		}
		catch (...) {}
	}

	void MainPage::button_Tuning_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Reset tuning and fans settings
			if (Adl_Overdrive8_Reset(adl_Gpu_AdapterIndex))
			{
				//Device identifier
				std::wstring device_id_w = AdlxGetGpuIdentifier(adl_Gpu_AdapterIndex);

				//Remove tuning and fans settings
				TuningFanSettings_Profile_Remove(device_id_w);

				//Save tuning and fans settings
				TuningFanSettings_Profiles_SaveToFile();

				//Load tuning values to interface
				AdlxValuesLoadTuning();

				//Show notification
				ShowNotification(L"Tuning and fans settings reset");
				AVDebugWriteLine(L"Tuning and fans settings reset");
			}
			else
			{
				//Update button colors
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				button_Tuning_Apply().Background(colorInvalid);
				button_Fan_Apply().Background(colorInvalid);

				//Show notification
				ShowNotification(L"Failed resetting tuning and fans settings");
				AVDebugWriteLine(L"Failed resetting tuning and fans settings");
			}
		}
		catch (...) {}
	}

	void MainPage::button_Tuning_Import_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Import settings from file
			AdlxValuesImportTuning();
		}
		catch (...) {}
	}

	void MainPage::button_Tuning_Export_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Export current settings to file
			AdlxValuesExportTuning();
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_KeepActive_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();

			//Update current value
			tuningFanSettingsCurrent.KeepActive.Current = newValue;

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Tuning_Apply().Background(colorIgnored);
			button_Fan_Apply().Background(colorIgnored);
		}
		catch (...) {}
	}

	void MainPage::slider_Core_Min_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int maxCurrent = (int)slider_Core_Max().Value();
			int minLimits = maxCurrent - 100;
			int minCurrent = (int)slider_Core_Min().Value();
			int maxLimits = minCurrent + 100;

			//Adjust values
			if (minCurrent > minLimits)
			{
				slider_Core_Min().Value(minLimits);
				slider_Core_Max().Value(maxLimits);
			}

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Tuning_Apply().Background(colorIgnored);
			button_Fan_Apply().Background(colorIgnored);

			//Get setting value
			auto newSender = sender.as<Slider>();
			int newValue = (int)newSender.Value();

			//Update current value
			tuningFanSettingsCurrent.CoreMin.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_Core_Max_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Check if minimum core is enabled
			if (slider_Core_Min().IsEnabled())
			{
				//Get setting value
				int maxCurrent = (int)slider_Core_Max().Value();
				int minLimits = maxCurrent - 100;
				int minCurrent = (int)slider_Core_Min().Value();
				int maxLimits = minCurrent + 100;

				//Adjust values
				if (minCurrent > minLimits)
				{
					slider_Core_Min().Value(minLimits);
					slider_Core_Max().Value(maxLimits);
				}
			}

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Tuning_Apply().Background(colorIgnored);
			button_Fan_Apply().Background(colorIgnored);

			//Get setting value
			auto newSender = sender.as<Slider>();
			int newValue = (int)newSender.Value();

			//Update current value
			tuningFanSettingsCurrent.CoreMax.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::combobox_Memory_Timing_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Tuning_Apply().Background(colorIgnored);
			button_Fan_Apply().Background(colorIgnored);

			//Get setting value
			auto newSender = sender.as<ComboBox>();
			int newValue = (int)newSender.SelectedIndex();

			//Update current value
			tuningFanSettingsCurrent.MemoryTiming.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_Memory_Max_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Tuning_Apply().Background(colorIgnored);
			button_Fan_Apply().Background(colorIgnored);

			//Get setting value
			auto newSender = sender.as<Slider>();
			int newValue = (int)newSender.Value();

			//Update current value
			tuningFanSettingsCurrent.MemoryMax.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_Power_Limit_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Tuning_Apply().Background(colorIgnored);
			button_Fan_Apply().Background(colorIgnored);

			//Get setting value
			auto newSender = sender.as<Slider>();
			int newValue = (int)newSender.Value();

			//Update current value
			tuningFanSettingsCurrent.PowerLimit.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_Power_Limit_PB_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Tuning_Apply().Background(colorIgnored);
			button_Fan_Apply().Background(colorIgnored);

			//Get setting value
			auto newSender = sender.as<Slider>();
			int newValue = (int)newSender.Value();

			//Update current value
			tuningFanSettingsCurrent.PowerLimitPB.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_Power_Voltage_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Tuning_Apply().Background(colorIgnored);
			button_Fan_Apply().Background(colorIgnored);

			//Get setting value
			auto newSender = sender.as<Slider>();
			int newValue = (int)newSender.Value();

			//Update current value
			tuningFanSettingsCurrent.PowerVoltage.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_Power_Voltage_PB_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Tuning_Apply().Background(colorIgnored);
			button_Fan_Apply().Background(colorIgnored);

			//Get setting value
			auto newSender = sender.as<Slider>();
			int newValue = (int)newSender.Value();

			//Update current value
			tuningFanSettingsCurrent.PowerVoltagePB.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_Power_TDC_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Tuning_Apply().Background(colorIgnored);
			button_Fan_Apply().Background(colorIgnored);

			//Get setting value
			auto newSender = sender.as<Slider>();
			int newValue = (int)newSender.Value();

			//Update current value
			tuningFanSettingsCurrent.PowerTDC.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_Power_TDC_PB_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Tuning_Apply().Background(colorIgnored);
			button_Fan_Apply().Background(colorIgnored);

			//Get setting value
			auto newSender = sender.as<Slider>();
			int newValue = (int)newSender.Value();

			//Update current value
			tuningFanSettingsCurrent.PowerTDCPB.Current = newValue;
		}
		catch (...) {}
	}
}