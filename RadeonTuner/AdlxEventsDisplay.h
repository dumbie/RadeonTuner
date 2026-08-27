#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::fire_and_forget MainPage::button_AppAdd_Display_Click(IInspectable const& sender, RoutedEventArgs const& e)
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
				DisplaySettings displaySettingsAdl = DisplaySettings_Generate_FromADL(adl_Display_AdapterIndex, adl_Display_DisplayIndex, executableName, true).value();

				//Add display settings profile
				if (DisplaySettings_Profile_Add(displaySettingsAdl))
				{
					addCount++;
				}
			}

			//Check add count
			if (addCount > 0)
			{
				//Save display settings
				DisplaySettings_Profiles_SaveToFile();
			}

			//Show notification
			//Fix show fail and duplicate count
			ShowNotification(L"Applications added: " + number_to_wstring(addCount) + L" / " + number_to_wstring(selectedAppsCount));
			AVDebugWriteLine(L"Applications added: " << addCount << L" / " << selectedAppsCount);
		}
		catch (...) {}
	}

	winrt::fire_and_forget MainPage::button_AppRemove_Display_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { co_return; }

			//Show remove dialog
			auto selectedApps = co_await AdlAppPickerRemoveAppDisplay();
			int selectedAppsCount = selectedApps.Size();

			//Check selected items
			if (selectedAppsCount == 0)
			{
				ShowNotification(L"No applications selected");
				AVDebugWriteLine(L"No applications selected.");
				co_return;
			}

			//Device identifier
			std::wstring deviceIdW = displaySettingsProfile.DeviceId.value();

			//Device application
			std::wstring applicationW = displaySettingsProfile.Application.value();

			//Remove selected items
			int removeCount = 0;
			bool currentAppRemoved = false;
			for (auto const& app : selectedApps)
			{
				//Get executable name
				std::wstring executableName = hstring_to_wstring(app.ExeName());

				//Remove application and profile
				if (DisplaySettings_Profile_Remove(deviceIdW, executableName))
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
				//Save display settings
				DisplaySettings_Profiles_SaveToFile();
			}

			//Show notification
			//Fix show fail and duplicate count
			ShowNotification(L"Applications removed: " + number_to_wstring(removeCount) + L" / " + number_to_wstring(selectedAppsCount));
			AVDebugWriteLine(L"Applications removed: " << removeCount << L" / " << selectedAppsCount);

			//Check selected application and reload
			if (currentAppRemoved)
			{
				AVDebugWriteLine(L"Current application removed, selecting Global.");

				//Load display settings
				AdlxValuesLoadSelectDisplayApp(adl_Display_AdapterIndex, adl_Display_DisplayIndex, L"Global");
			}
		}
		catch (...) {}
	}

	void MainPage::button_Display_Apply_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Profile is used
			bool usingProfile = displaySettingsProfile.UsingProfile;

			//Profile global
			bool globalProfile = displaySettingsProfile.Global();

			//Device identifier
			std::wstring deviceIdW = displaySettingsProfile.DeviceId.value();

			//Device application
			std::wstring applicationW = displaySettingsProfile.Application.value();

			//Update display settings
			DisplaySettings_Profile_Replace(displaySettingsProfile);

			//Save display settings
			DisplaySettings_Profiles_SaveToFile();

			//Check if profile is used
			if (usingProfile)
			{
				//Get current settings
				DisplaySettings displaySettingsAdl = DisplaySettings_Generate_FromADL(adl_Display_AdapterIndex, adl_Display_DisplayIndex, applicationW, false).value();

				//Apply display settings
				bool applyResult = AdlDisplaySettingsApply(adl_Display_AdapterIndex, adl_Display_DisplayIndex, displaySettingsProfile, displaySettingsAdl, AdlSettingGet::Current, !globalProfile);

				//Check result
				if (applyResult)
				{
					//Show notification
					ShowNotification(L"Display settings applied");
					AVDebugWriteLine(L"Display settings applied: " << deviceIdW << L" / " << applicationW);

					//Load display settings
					AdlxValuesLoadSelectDisplayApp(adl_Display_AdapterIndex, adl_Display_DisplayIndex, applicationW);
				}
				else
				{
					//Update button colors
					SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
					button_Display_Apply().Background(colorInvalid);

					//Show notification
					ShowNotification(L"Failed applying display settings");
					AVDebugWriteLine(L"Failed applying display settings: " << deviceIdW << L" / " << applicationW);
				}
			}
			else
			{
				//Update button colors
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				button_Display_Apply().Background(colorValid);

				//Show notification
				ShowNotification(L"Display settings adjusted");
				AVDebugWriteLine(L"Display settings adjusted: " << deviceIdW << L" / " << applicationW);
			}
		}
		catch (...) {}
	}

	winrt::fire_and_forget MainPage::button_Display_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { co_return; }

			//Confirm reset
			std::vector<std::wstring> messageAnswers{ L"Yes", L"No" };
			int messageResult = co_await ShowMessageBox(L"Reset display settings?", L"", messageAnswers);
			if (messageResult == 1)
			{
				co_return;
			}

			//Profile is used
			bool usingProfile = displaySettingsProfile.UsingProfile;

			//Profile global
			bool globalProfile = displaySettingsProfile.Global();

			//Device identifier
			std::wstring deviceIdW = displaySettingsProfile.DeviceId.value();

			//Device application
			std::wstring applicationW = displaySettingsProfile.Application.value();

			//Remove display settings
			if (DisplaySettings_Profile_Remove(deviceIdW, applicationW))
			{
				//Save display settings
				DisplaySettings_Profiles_SaveToFile();
			}

			//Check if profile is used
			if (usingProfile)
			{
				//Get current settings
				DisplaySettings displaySettingsAdl = DisplaySettings_Generate_FromADL(adl_Display_AdapterIndex, adl_Display_DisplayIndex, applicationW, false).value();

				//Get default settings
				DisplaySettings displaySettingsDefault = DisplaySettings_Generate_FromADL(adl_Display_AdapterIndex, adl_Display_DisplayIndex, applicationW, true).value();

				//Apply display settings
				AdlDisplaySettingsApply(adl_Display_AdapterIndex, adl_Display_DisplayIndex, displaySettingsDefault, displaySettingsAdl, AdlSettingGet::Default, !globalProfile);
			}

			//Show notification
			ShowNotification(L"Display settings reset");
			AVDebugWriteLine(L"Display settings reset: " << deviceIdW << L" / " << applicationW);

			//Load display settings
			AdlxValuesLoadSelectDisplayApp(adl_Display_AdapterIndex, adl_Display_DisplayIndex, applicationW);
		}
		catch (...) {}
	}

	void MainPage::button_Display_Import_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Import settings from file
			AdlxValuesImportDisplay();
		}
		catch (...) {}
	}

	void MainPage::button_Display_Export_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Export current settings to file
			AdlxValuesExportDisplay();
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_Display_HdrEnabled_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.HdrEnabled.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::combobox_Display_FreeSyncMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ComboBox>();
			int newValue = newSender.SelectedIndex();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.FreeSyncMode.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_Display_VSR_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.VsrEnabled.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::combobox_Display_ColorDepth_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.ColorDepth.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::combobox_Display_PixelFormat_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.PixelFormat.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::combobox_Display_DisplayColorEnhancement_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.ColorEnhancement.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_Display_ColorTemperature_Control_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();

			//Update interface
			if (newValue)
			{
				slider_Display_ColorTemperature_Kelvin().IsEnabled(true);
			}
			else
			{
				slider_Display_ColorTemperature_Kelvin().IsEnabled(false);
			}

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.ColorTemperatureControl.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_Display_ColorTemperature_Kelvin_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.ColorTemperatureKelvin.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_Display_Brightness_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.Brightness.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_Display_Contrast_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.Contrast.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_Display_Saturation_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.Saturation.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_Display_Hue_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.Hue.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_Display_GammaRGB_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting values
			float redGain = slider_Display_GammaRed().Value();
			float greenGain = slider_Display_GammaGreen().Value();
			float blueGain = slider_Display_GammaBlue().Value();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.GammaRed.Current = redGain;
			displaySettingsProfile.GammaGreen.Current = greenGain;
			displaySettingsProfile.GammaBlue.Current = blueGain;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_Display_CVDC_Control_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();

			//Update interface
			if (newValue)
			{
				slider_Display_Protanopia().IsEnabled(true);
				slider_Display_Deuteranopia().IsEnabled(true);
				slider_Display_Tritanopia().IsEnabled(true);
			}
			else
			{
				slider_Display_Protanopia().IsEnabled(false);
				slider_Display_Deuteranopia().IsEnabled(false);
				slider_Display_Tritanopia().IsEnabled(false);
			}

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.CVDCControl.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_Display_Protanopia_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.CVDCProtanopia.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_Display_Deuteranopia_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.CVDCDeuteranopia.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_Display_Tritanopia_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.CVDCTritanopia.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_Display_GpuScaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.GpuScalingEnabled.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_Display_IntegerScaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.IntegerScalingEnabled.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::combobox_Display_ScalingMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.ScalingMode.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_Display_HDCPSupport_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.HDCPEnabled.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_Display_VariBright_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();

			//Update interface
			if (newValue)
			{
				combobox_Display_VariBright_Level().IsEnabled(true);
			}
			else
			{
				combobox_Display_VariBright_Level().IsEnabled(false);
			}

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.VariBrightEnabled.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::combobox_Display_VariBright_Level_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.VariBrightLevel.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_Eyefinity_Automatic_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			button_Display_Apply().Background(colorIgnored);

			//Update current value
			displaySettingsProfile.EyefinityAutomatic.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::combobox_Display_Resolution_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newIndex = sender.as<ComboBox>().SelectedIndex();
			auto newValue = sender.as<ComboBox>().SelectedItem().as<RadeonTuner::DisplayDetailsIdl>();
			bool newFailed = true;

			//Get current display mode
			int numModes = -1;
			ADLMode* adlModeCurrent{};
			adl_Res0 = _ADL2_Display_Modes_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &numModes, &adlModeCurrent);
			if (adl_Res0 != ADL_OK)
			{
				AVDebugWriteLine(L"Failed getting current display mode.");
				return;
			}

			//Update revert values
			displayResolutionRevertWidth = adlModeCurrent->iXRes;
			displayResolutionRevertHeight = adlModeCurrent->iYRes;
			displayResolutionRevertRefreshRate = adlModeCurrent->fRefreshRate;
			displayResolutionRevertOrientation = adlModeCurrent->iOrientation;

			//Update display mode
			adlModeCurrent->iXRes = newValue.ResolutionWidth();
			adlModeCurrent->iYRes = newValue.ResolutionHeight();

			//Set setting
			adl_Res0 = _ADL2_Display_Modes_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, 1, adlModeCurrent);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting display resolution");
				AVDebugWriteLine(L"Failed setting display resolution");
			}
			else
			{
				std::wstring valueString = number_to_wstring(newValue.ResolutionWidth()) + L"x" + number_to_wstring(newValue.ResolutionHeight());
				ShowNotification(L"Display resolution set to " + valueString);
				AVDebugWriteLine(L"Display resolution set to " << newIndex);

				//Show confirm overlay
				DisplaySettings_Confirm_Resolution_Start();
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_Display_RefreshRate_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newIndex = sender.as<ComboBox>().SelectedIndex();
			auto newValue = sender.as<ComboBox>().SelectedItem().as<RadeonTuner::DisplayDetailsIdl>();
			bool newFailed = true;

			//Get current display mode
			int numModes = -1;
			ADLMode* adlModeCurrent{};
			adl_Res0 = _ADL2_Display_Modes_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &numModes, &adlModeCurrent);
			if (adl_Res0 != ADL_OK)
			{
				AVDebugWriteLine(L"Failed getting current display mode.");
				return;
			}

			//Update revert values
			displayResolutionRevertWidth = adlModeCurrent->iXRes;
			displayResolutionRevertHeight = adlModeCurrent->iYRes;
			displayResolutionRevertRefreshRate = adlModeCurrent->fRefreshRate;
			displayResolutionRevertOrientation = adlModeCurrent->iOrientation;

			//Update display mode
			adlModeCurrent->fRefreshRate = newValue.RefreshRate();

			//Set setting
			adl_Res0 = _ADL2_Display_Modes_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, 1, adlModeCurrent);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting display refresh rate");
				AVDebugWriteLine(L"Failed setting display refresh rate");
			}
			else
			{
				std::wstring valueString = float_to_wstring(newValue.RefreshRate(), 2) + L" Hz";
				ShowNotification(L"Display refresh rate set to " + valueString);
				AVDebugWriteLine(L"Display refresh rate set to " << newIndex);

				//Show confirm overlay
				DisplaySettings_Confirm_Resolution_Start();
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_Display_Orientation_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Get current display mode
			int numModes = -1;
			ADLMode* adlModeCurrent{};
			adl_Res0 = _ADL2_Display_Modes_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &numModes, &adlModeCurrent);
			if (adl_Res0 != ADL_OK)
			{
				AVDebugWriteLine(L"Failed getting current display mode.");
				return;
			}

			//Enumeration index correction
			int displayOrientationDegree = 0;
			switch (newValue)
			{
			case 0:
				displayOrientationDegree = 0;
				break;
			case 1:
				displayOrientationDegree = 90;
				break;
			case 2:
				displayOrientationDegree = 180;
				break;
			case 3:
				displayOrientationDegree = 270;
				break;
			}

			//Update display mode
			adlModeCurrent->iOrientation = displayOrientationDegree;

			//Set setting
			adl_Res0 = _ADL2_Display_Modes_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, 1, adlModeCurrent);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting display orientation");
				AVDebugWriteLine(L"Failed setting display orientation");
			}
			else
			{
				ShowNotification(L"Display orientation set to " + ADL_DISPLAY_ORIENTATIONS[newValue]);
				AVDebugWriteLine(L"Display orientation set to " << newValue);
			}
		}
		catch (...) {}
	}
}