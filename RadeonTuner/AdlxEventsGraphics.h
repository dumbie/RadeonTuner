#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::fire_and_forget MainPage::button_AppAdd_Graphics_Click(IInspectable const& sender, RoutedEventArgs const& e)
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

				//Create adl application
				AdlApplication adlApplication{};
				adlApplication.FileName = executableName;
				adlApplication.FilePath = L"*\\*";
				adlApplication.DriverArea = L"3D_User";

				//Get current and default settings
				GraphicsSettings graphicsSettingsAdl = GraphicsSettings_Generate_FromADLApp(adl_Gpu_AdapterIndex, adlApplication).value();

				//Add application to user.blb
				bool resultAddApp = AdlGraphicsSettingsApply(adl_Gpu_AdapterIndex, adl_Gpu_UniqueIdentifierHex, adlApplication, graphicsSettingsAdl, AdlSettingGet::Current);

				//Add application to profiles
				bool resultAddProfile = GraphicsSettings_Profile_Add(graphicsSettingsAdl);

				//Check result
				if (resultAddApp && resultAddProfile)
				{
					addCount++;
				}
			}

			//Check add count
			if (addCount > 0)
			{
				//Save tuning and fans settings
				GraphicsSettings_Profiles_SaveToFile();
			}

			//Show notification
			//Fix show fail and duplicate count
			ShowNotification(L"Applications added: " + number_to_wstring(addCount) + L" / " + number_to_wstring(selectedAppsCount));
			AVDebugWriteLine(L"Applications added: " << addCount << L" / " << selectedAppsCount);
		}
		catch (...) {}
	}

	winrt::fire_and_forget MainPage::button_AppRemove_Graphics_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { co_return; }

			//Show remove dialog
			auto selectedApps = co_await AdlAppPickerRemoveAppGraphics();
			int selectedAppsCount = selectedApps.Size();

			//Check selected items
			if (selectedAppsCount == 0)
			{
				ShowNotification(L"No applications selected");
				AVDebugWriteLine(L"No applications selected.");
				co_return;
			}

			//Get current device identifier
			std::wstring currentDeviceIdW = graphicsSettingsCurrent.get().DeviceId.value();

			//Get current application name
			std::wstring currentApplicationW = graphicsSettingsCurrent.get().Application.value();

			//Remove selected items
			int removeCount = 0;
			bool currentAppRemoved = false;
			for (auto const& app : selectedApps)
			{
				//Get executable name
				std::wstring executableName = hstring_to_wstring(app.ExeName());

				//Create adl application
				AdlApplication adlApplication{};
				adlApplication.FileName = executableName;
				adlApplication.FilePath = L"*\\*";
				adlApplication.DriverArea = L"3D_User";

				//Remove application from user.blb
				std::wstring removeResultApp = AdlAppRemove(adlApplication);

				//Remove application from profiles
				bool removeResultProfile = GraphicsSettings_Profile_Remove(currentDeviceIdW, executableName);

				//Check result
				if (removeResultProfile && removeResultApp == L"Application removed")
				{
					//Update remove count
					removeCount++;

					//Check if current application is removed
					if (executableName == currentApplicationW)
					{
						currentAppRemoved = true;
					}
				}
			}

			//Check remove count
			if (removeCount > 0)
			{
				//Save tuning and fans settings
				GraphicsSettings_Profiles_SaveToFile();
			}

			//Show notification
			//Fix show fail and duplicate count
			ShowNotification(L"Applications removed: " + number_to_wstring(removeCount) + L" / " + number_to_wstring(selectedAppsCount));
			AVDebugWriteLine(L"Applications removed: " << removeCount << L" / " << selectedAppsCount);

			//Check selected application and reload
			if (currentAppRemoved)
			{
				AVDebugWriteLine(L"Current application removed, selecting Global.");

				//Load graphics settings
				AdlxValuesLoadSelectGraphicsApp(adl_Gpu_AdapterIndex, L"Global");
			}
		}
		catch (...) {}
	}

	void MainPage::button_Graphics_Apply_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Device identifier
			std::wstring deviceIdW = graphicsSettingsCurrent.get().DeviceId.value();

			//Device application
			std::wstring applicationW = graphicsSettingsCurrent.get().Application.value();

			//Save graphics settings
			GraphicsSettings_Profiles_SaveToFile();

			//Create adl application
			AdlApplication adlApplication{};
			adlApplication.FileName = applicationW;
			adlApplication.FilePath = L"*\\*";
			adlApplication.DriverArea = L"3D_User";

			//Apply graphics settings
			bool applyResult = AdlGraphicsSettingsApply(adl_Gpu_AdapterIndex, adl_Gpu_UniqueIdentifierHex, adlApplication, graphicsSettingsCurrent.get(), AdlSettingGet::Current);

			//Check result
			if (applyResult)
			{
				//Show notification
				ShowNotification(L"Graphics settings applied");
				AVDebugWriteLine(L"Graphics settings applied: " << deviceIdW << L" / " << applicationW);

				//Load graphics settings
				AdlxValuesLoadSelectGraphicsApp(adl_Gpu_AdapterIndex, applicationW);
			}
			else
			{
				//Show notification
				ShowNotification(L"Graphics settings not applied");
				AVDebugWriteLine(L"Graphics settings not applied: " << deviceIdW << L" / " << applicationW);

				//Update button colors
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				button_Graphics_Apply().Background(colorInvalid);
			}
		}
		catch (...) {}
	}

	winrt::fire_and_forget MainPage::button_Graphics_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { co_return; }

			//Confirm reset
			std::vector<std::wstring> messageAnswers{ L"Yes", L"No" };
			int messageResult = co_await ShowMessageBox(L"Reset graphics settings?", L"", messageAnswers);
			if (messageResult == 1)
			{
				co_return;
			}

			//Device identifier
			std::wstring deviceIdW = graphicsSettingsCurrent.get().DeviceId.value();

			//Device application
			std::wstring applicationW = graphicsSettingsCurrent.get().Application.value();

			//Remove graphics settings
			if (GraphicsSettings_Profile_Remove(deviceIdW, applicationW))
			{
				//Save graphics settings
				GraphicsSettings_Profiles_SaveToFile();
			}

			//Create adl application
			AdlApplication adlApplication{};
			adlApplication.FileName = applicationW;
			adlApplication.FilePath = L"*\\*";
			adlApplication.DriverArea = L"3D_User";

			//Get current and default settings
			GraphicsSettings graphicsSettingsAdl{};
			if (applicationW == L"Global")
			{
				graphicsSettingsAdl = GraphicsSettings_Generate_FromADLRegistry(adl_Gpu_AdapterIndex, applicationW).value();
			}
			else
			{
				graphicsSettingsAdl = GraphicsSettings_Generate_FromADLApp(adl_Gpu_AdapterIndex, adlApplication).value();
			}

			//Apply current settings
			bool setResult = AdlGraphicsSettingsApply(adl_Gpu_AdapterIndex, adl_Gpu_UniqueIdentifierHex, adlApplication, graphicsSettingsAdl, AdlSettingGet::Default);

			//Check result
			if (setResult)
			{
				//Show notification
				ShowNotification(L"Graphics settings reset");
				AVDebugWriteLine(L"Graphics settings reset");

				//Load graphics settings
				AdlxValuesLoadSelectGraphicsApp(adl_Gpu_AdapterIndex, applicationW);
			}
			else
			{
				//Show notification
				ShowNotification(L"Graphics settings not reset");
				AVDebugWriteLine(L"Graphics settings not reset");

				//Update button colors
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				button_Graphics_Apply().Background(colorInvalid);
			}
		}
		catch (...) {}
	}

	void MainPage::button_Graphics_Import_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Import settings from file
			AdlxValuesImportGraphics();
		}
		catch (...) {}
	}

	void MainPage::button_Graphics_Export_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Export current settings to file
			AdlxValuesExportGraphics();
		}
		catch (...) {}
	}

	winrt::fire_and_forget MainPage::button_Graphics_Clear_ShaderCache_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { co_return; }

			//Confirm shader cache clear
			std::vector<std::wstring> messageAnswers{ L"Yes", L"No" };
			int messageResult = co_await ShowMessageBox(L"Clear shader cache?", L"", messageAnswers);
			if (messageResult == 1)
			{
				co_return;
			}

			//Reset shader cache
			bool resetResult = AdlxResetShaderCache();

			//Set result
			if (!resetResult)
			{
				ShowNotification(L"Failed resetting shader cache");
				AVDebugWriteLine(L"Failed resetting shader cache");
			}
			else
			{
				ShowNotification(L"Shader cache is reset");
				AVDebugWriteLine(L"Shader cache is reset");
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_FsrOverrideUpscaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().FsrOverride.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_FsrOverrideFrameGeneration_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().MlfiOverride.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_FsrOverrideMultiFrameGeneration_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().MfgOverride.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_FsrOverrideRayRegeneration_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().MldOverride.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_FsrOverrideNeuralRadianceCaching_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().NrcOverride.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::combobox_FsrMultiFrameGenerationRatio_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().MfgRatio.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::textbox_FsrDllLoadPath_TextChanged(IInspectable const& sender, TextBoxTextChangingEventArgs const& e)
	{
		try
		{
			//Get setting value
			auto newValueHstring = sender.as<TextBox>().Text();
			auto newValue = hstring_to_wstring(newValueHstring);

			//Set FSR library version information
			FsrOverrideDllUpdateTextPathInfo(newValue);
			FsrOverrideDllUpdateTextVersion(newValue);

			//Check if saving is disabled
			if (disable_saving) { return; }

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().FsrOvrDLLPath.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::button_FsrDllLoadPath_Set_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Show file dialog
			std::wstring newValue = filepicker_open(NULL, L"Select FSR library file...", { { L"FSR DLL", L"amdxcff*.dll" } });

			//Check file path
			if (newValue.empty())
			{
				ShowNotification(L"FSR library not changed, no path set");
				AVDebugWriteLine(L"FSR library not changed, no path set");
				return;
			}

			//Set text and trigger event
			textbox_FsrDllLoadPath().Text(newValue);
		}
		catch (...) {}
	}

	void MainPage::button_FsrDllLoadPath_Default_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get default FSR Override Library
			std::wstring newValue = FsrOverrideDllGetPathDefault();

			//Set text and trigger event
			textbox_FsrDllLoadPath().Text(newValue);
		}
		catch (...) {}
	}

	void MainPage::combobox_FsrOtaUpdates_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Fix check if ADL2_CloudProfile_DLL_Get is used to trigger update or get dll path.

			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().FsrOtaIndex.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_FsrLatencyReduction_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//DriverBug#5

			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().DeLagEnabled.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_RadeonEnhancedSync_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().EnhancedSync.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::combobox_VerticalSync_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().VerticalSync.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_FrameGenEnabled_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//DriverBug#6
			//Software\AMD\DVR FrameGenTestEnv

			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();

			//Update interface
			if (newValue)
			{
				combobox_FrameGenSearchMode().IsEnabled(true);
				combobox_FrameGenPerfMode().IsEnabled(true);
				combobox_FrameGenResponseMode().IsEnabled(true);
				combobox_FrameGenAlgorithm().IsEnabled(true);
			}
			else
			{
				combobox_FrameGenSearchMode().IsEnabled(false);
				combobox_FrameGenPerfMode().IsEnabled(false);
				combobox_FrameGenResponseMode().IsEnabled(false);
				combobox_FrameGenAlgorithm().IsEnabled(false);
			}

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().FrameGenEnabled.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::combobox_FrameGenSearchMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().FrameGenSearchMode.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::combobox_FrameGenPerfMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().FrameGenPerfMode.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::combobox_FrameGenResponseMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().FrameGenResponseMode.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::combobox_FrameGenAlgorithm_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().FrameGenAlgorithm.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_RadeonChill_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
				//Check Radeon Chill Link
				if (radeon_Chill_Linked)
				{
					slider_RadeonChill_Min().IsEnabled(false);
				}
				else
				{
					slider_RadeonChill_Min().IsEnabled(true);
				}
				slider_RadeonChill_Max().IsEnabled(true);
				button_RadeonChill_Link().IsEnabled(true);
			}
			else
			{
				slider_RadeonChill_Min().IsEnabled(false);
				slider_RadeonChill_Max().IsEnabled(false);
				button_RadeonChill_Link().IsEnabled(false);
			}

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().ChillEnabled.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_RadeonChill_Min_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();

			//Match values
			if (newValue > slider_RadeonChill_Max().Value())
			{
				slider_RadeonChill_Max().Value(newValue);
			}

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().ChillMinFps.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_RadeonChill_Max_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();

			//Match values
			if (radeon_Chill_Linked || newValue < slider_RadeonChill_Min().Value())
			{
				slider_RadeonChill_Min().Value(newValue);
			}

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().ChillMaxFps.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::button_RadeonChill_Link_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Check Radeon Chill Link
			if (!radeon_Chill_Linked)
			{
				AVDebugWriteLine("Link Radeon Chill.");
				auto bitmapImage = winrt::BitmapImage(winrt::Uri(L"ms-appx:///Assets/Link.png"));
				image_RadeonChill_Link().Source(bitmapImage);
				slider_RadeonChill_Min().IsEnabled(false);
				radeon_Chill_Linked = true;
			}
			else
			{
				AVDebugWriteLine("Unlink Radeon Chill.");
				auto bitmapImage = winrt::BitmapImage(winrt::Uri(L"ms-appx:///Assets/Unlink.png"));
				image_RadeonChill_Link().Source(bitmapImage);
				slider_RadeonChill_Min().IsEnabled(true);
				radeon_Chill_Linked = false;
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_RadeonBoost_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
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
			button_Graphics_Apply().Background(colorIgnored);

			//Update interface
			if (newValue)
			{
				slider_RadeonBoost_MinResolution().IsEnabled(true);
			}
			else
			{
				slider_RadeonBoost_MinResolution().IsEnabled(false);
			}

			//Update current value
			graphicsSettingsCurrent.get().BoostMode.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_RadeonBoost_MinResolution_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().BoostMinResolution.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_RadeonImageSharpening1_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			button_Graphics_Apply().Background(colorIgnored);

			//Update interface
			if (newValue)
			{
				slider_RadeonImageSharpening1_Sharpening().IsEnabled(true);
			}
			else
			{
				slider_RadeonImageSharpening1_Sharpening().IsEnabled(false);
			}

			//Update current value
			graphicsSettingsCurrent.get().RisEnabled.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_RadeonImageSharpening1_Sharpening_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValueInt = (int)e.NewValue();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().RisSharpeningDegree.Current = newValueInt;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_RadeonImageSharpening2_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			button_Graphics_Apply().Background(colorIgnored);

			//Update interface
			if (newValue)
			{
				toggleswitch_RadeonImageSharpening2_Desktop().IsEnabled(true);
				slider_RadeonImageSharpening2_Sharpening().IsEnabled(true);
			}
			else
			{
				toggleswitch_RadeonImageSharpening2_Desktop().IsEnabled(false);
				slider_RadeonImageSharpening2_Sharpening().IsEnabled(false);
			}

			//Update current value
			graphicsSettingsCurrent.get().Ris2Enabled.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_RadeonImageSharpening2_Desktop_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().Ris2DesktopEnabled.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_RadeonImageSharpening2_Sharpening_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().Ris2SharpeningDegree.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_AntiAliasingOverride_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			button_Graphics_Apply().Background(colorIgnored);

			//Update interface
			if (newValue)
			{
				combobox_AntiAliasingMethod().IsEnabled(true);
				combobox_AntiAliasingLevel().IsEnabled(true);
				toggleswitch_AntiAliasingEnhancedQuality().IsEnabled(true);
			}
			else
			{
				combobox_AntiAliasingMethod().IsEnabled(false);
				combobox_AntiAliasingLevel().IsEnabled(false);
				toggleswitch_AntiAliasingEnhancedQuality().IsEnabled(false);
			}

			//Update current value
			graphicsSettingsCurrent.get().AntiAliasingOverride.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::combobox_AntiAliasingMethod_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = sender.as<ComboBox>().SelectedIndex();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().AntiAliasingMethod.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::combobox_AntiAliasingLevel_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().AntiAliasingLevel.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_AntiAliasingEnhancedQuality_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//DriverBug#3

			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().AntiAliasingEnhancedQuality.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_MorphologicalAntiAliasing_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().AntiAliasingMorphological.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::combobox_AnisotropicTextureFiltering_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//DriverBug#4

			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().AnisotropicOverride.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::combobox_Tessellation_Mode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = sender.as<ComboBox>().SelectedIndex();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update interface
			if (newValue != 2)
			{
				combobox_Tessellation_Level().IsEnabled(false);
			}
			else
			{
				combobox_Tessellation_Level().IsEnabled(true);
			}

			//Update current value
			graphicsSettingsCurrent.get().TessellationMode.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::combobox_Tessellation_Level_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().TessellationLevel.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_OpenGLTripleBuffering_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().OpenGLTripleBuffering.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::combobox_TextureFilteringQuality_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().TextureFilteringQuality.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_SurfaceFormatOptimization_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().SurfaceFormatOptimization.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_Frtc_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Note: FRTC Pro works in windowed mode when using workstation drivers but not with gaming drivers.

			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update interface
			if (newValue)
			{
				slider_Frtc_FrameRateTarget().IsEnabled(true);
			}
			else
			{
				slider_Frtc_FrameRateTarget().IsEnabled(false);
			}

			//Update current value
			graphicsSettingsCurrent.get().FrtcEnabled.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_Frtc_FrameRateTarget_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().FrtcFrameRateTarget.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_OpenGL10BitPixelFormat_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			button_Graphics_Apply().Background(colorIgnored);

			//Update current value
			graphicsSettingsCurrent.get().OpenGL10BitPixelFormat.Current = newValue;
		}
		catch (...) {}
	}
}