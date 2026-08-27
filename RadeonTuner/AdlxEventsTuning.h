#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::fire_and_forget MainPage::button_AppAdd_Tuning_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { co_return; }

			//Show application picker
			auto selectedApps = co_await AdlAppPickerAdd();
			int selectedAppsCount = selectedApps.Size();

			//Check selected items
			if (selectedAppsCount == 0)
			{
				ShowNotification(L"No applications selected");
				AVDebugWriteLine(L"No applications selected.");
				co_return;
			}

			//Add selected items
			int addCount = 0;
			for (auto const& app : selectedApps)
			{
				//Get executable name
				std::wstring executableName = hstring_to_wstring(app.ExeName());

				//Get current and default settings
				TuningFanSettings tuningFanSettingsAdl = TuningFanSettings_Generate_FromADL(adl_Gpu_AdapterIndex, executableName, true).value();

				//Add settings profile
				if (TuningFanSettings_Profile_Add(tuningFanSettingsAdl))
				{
					addCount++;
				}
			}

			//Check add count
			if (addCount > 0)
			{
				//Save tuning and fans settings
				TuningFanSettings_Profiles_SaveToFile();
			}

			//Show notification
			//Fix show fail and duplicate count
			ShowNotification(L"Applications added: " + number_to_wstring(addCount) + L" / " + number_to_wstring(selectedAppsCount));
			AVDebugWriteLine(L"Applications added: " << addCount << L" / " << selectedAppsCount);
		}
		catch (...) {}
	}

	winrt::fire_and_forget MainPage::button_AppRemove_Tuning_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { co_return; }

			//Show remove dialog
			auto selectedApps = co_await AdlAppPickerRemoveAppTuning();
			int selectedAppsCount = selectedApps.Size();

			//Check selected items
			if (selectedAppsCount == 0)
			{
				ShowNotification(L"No applications selected");
				AVDebugWriteLine(L"No applications selected.");
				co_return;
			}

			//Device identifier
			std::wstring deviceIdW = tuningFanSettingsProfile.DeviceId.value();

			//Device application
			std::wstring applicationW = tuningFanSettingsProfile.Application.value();

			//Remove selected items
			int removeCount = 0;
			bool currentAppRemoved = false;
			for (auto const& app : selectedApps)
			{
				//Get executable name
				std::wstring executableName = hstring_to_wstring(app.ExeName());

				//Remove application and profile
				if (TuningFanSettings_Profile_Remove(deviceIdW, executableName))
				{
					//Update remove count
					removeCount++;

					//Check if current application is removed
					if (executableName == applicationW)
					{
						currentAppRemoved = true;
					}
				}
			}

			//Check remove count
			if (removeCount > 0)
			{
				//Save tuning and fans settings
				TuningFanSettings_Profiles_SaveToFile();
			}

			//Show notification
			//Fix show fail and duplicate count
			ShowNotification(L"Applications removed: " + number_to_wstring(removeCount) + L" / " + number_to_wstring(selectedAppsCount));
			AVDebugWriteLine(L"Applications removed: " << removeCount << L" / " << selectedAppsCount);

			//Check selected application and reload
			if (currentAppRemoved)
			{
				AVDebugWriteLine(L"Current application removed, selecting Global.");

				//Load tuning and fans settings
				AdlxValuesLoadSelectTuningApp(adl_Gpu_AdapterIndex, L"Global");
			}
		}
		catch (...) {}
	}

	void MainPage::button_Tuning_Apply_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Profile is used
			bool usingProfile = tuningFanSettingsProfile.UsingProfile;

			//Device identifier
			std::wstring deviceIdW = tuningFanSettingsProfile.DeviceId.value();

			//Device application
			std::wstring applicationW = tuningFanSettingsProfile.Application.value();

			//Update tuning and fans settings
			TuningFanSettings_Profile_Replace(tuningFanSettingsProfile);

			//Save tuning and fans settings
			TuningFanSettings_Profiles_SaveToFile();

			//Apply settings when application profile is used
			if (usingProfile)
			{
				//Apply tuning and fans settings
				bool applyResult = AdlTuningFanSettingsApply(adl_Gpu_AdapterIndex, tuningFanSettingsProfile, AdlSettingGet::Current);

				//Check result
				if (applyResult)
				{
					//Show notification
					ShowNotification(L"Tuning and fans settings applied");
					AVDebugWriteLine(L"Tuning and fans settings applied: " << deviceIdW << L" / " << applicationW);

					//Load tuning and fans settings
					AdlxValuesLoadSelectTuningApp(adl_Gpu_AdapterIndex, applicationW);
				}
				else
				{
					//Update button colors
					SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
					button_Tuning_Apply().Background(colorInvalid);
					button_Fan_Apply().Background(colorInvalid);

					//Show notification
					ShowNotification(L"Failed applying tuning and fans settings");
					AVDebugWriteLine(L"Failed applying tuning and fans settings: " << deviceIdW << L" / " << applicationW);
				}
			}
			else
			{
				//Update button colors
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				button_Tuning_Apply().Background(colorValid);
				button_Fan_Apply().Background(colorValid);

				//Show notification
				ShowNotification(L"Tuning and fans settings adjusted");
				AVDebugWriteLine(L"Tuning and fans settings adjusted: " << deviceIdW << L" / " << applicationW);
			}
		}
		catch (...) {}
	}

	winrt::fire_and_forget MainPage::button_Tuning_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { co_return; }

			//Confirm reset
			std::vector<std::wstring> messageAnswers{ L"Yes", L"No" };
			int messageResult = co_await ShowMessageBox(L"Reset tuning and fans settings?", L"", messageAnswers);
			if (messageResult == 1)
			{
				co_return;
			}

			//Profile is used
			bool usingProfile = tuningFanSettingsProfile.UsingProfile;

			//Device identifier
			std::wstring deviceIdW = tuningFanSettingsProfile.DeviceId.value();

			//Device application
			std::wstring applicationW = tuningFanSettingsProfile.Application.value();

			//Remove tuning and fans settings
			if (TuningFanSettings_Profile_Remove(deviceIdW, applicationW))
			{
				//Save tuning and fans settings
				TuningFanSettings_Profiles_SaveToFile();
			}

			//Check if profile is used
			if (usingProfile)
			{
				//Reset tuning and fans settings
				Adl_Overdrive8_Values_Reset(adl_Gpu_AdapterIndex);
			}

			//Show notification
			ShowNotification(L"Tuning and fans settings reset");
			AVDebugWriteLine(L"Tuning and fans settings reset: " << deviceIdW << L" / " << applicationW);

			//Load tuning and fans settings
			AdlxValuesLoadSelectTuningApp(adl_Gpu_AdapterIndex, applicationW);
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

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Tuning_Apply().Background(colorIgnored);
			button_Fan_Apply().Background(colorIgnored);

			//Update current value
			tuningFanSettingsProfile.KeepActive.Current = newValue;
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
			tuningFanSettingsProfile.CoreMin.Current = newValue;
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
			tuningFanSettingsProfile.CoreMax.Current = newValue;
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
			tuningFanSettingsProfile.MemoryTiming.Current = newValue;
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
			tuningFanSettingsProfile.MemoryMax.Current = newValue;
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
			tuningFanSettingsProfile.PowerLimit.Current = newValue;
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
			tuningFanSettingsProfile.PowerVoltage.Current = newValue;
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
			tuningFanSettingsProfile.PowerTDC.Current = newValue;
		}
		catch (...) {}
	}
}