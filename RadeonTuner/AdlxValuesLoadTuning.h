#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::fire_and_forget MainPage::AdlxValuesLoadSelectTuningApp(int gpuAdapterIndex, std::wstring application)
	{
		try
		{
			//Disable saving
			disable_saving = true;

			//Get current and default settings
			TuningFanSettings tuningFanSettingsAdl = TuningFanSettings_Generate_FromADL(gpuAdapterIndex, application, false).value();

			//Add settings profile
			if (TuningFanSettings_Profile_Add(tuningFanSettingsAdl))
			{
				//Save settings profile
				TuningFanSettings_Profiles_SaveToFile();
			}

			//Device identifier
			std::wstring deviceId = tuningFanSettingsAdl.DeviceId.value();

			//Get and set settings
			tuningFanSettingsProfile = TuningFanSettings_Profile_Get(deviceId, application).value();

			//Convert settings values to interface
			TuningFanSettings_Convert_ToUI_Adl(tuningFanSettingsAdl);
			TuningFanSettings_Convert_ToUI_Profile(tuningFanSettingsProfile, AdlSettingGet::Current);

			//Update button text
			textblock_AppSelect_Tuning().Text(application);

			//Disable or enable settings
			if (tuningFanSettingsAdl.TuningSupport && tuningFanSettingsAdl.Global())
			{
				toggleswitch_KeepActive().IsEnabled(true);
			}
			else
			{
				toggleswitch_KeepActive().IsEnabled(false);
			}

			//Update button colors
			bool usingProfile = tuningFanSettingsProfile.UsingProfile;
			bool matchingProfile = TuningFanSettings_Match(tuningFanSettingsProfile, tuningFanSettingsAdl);
			if (usingProfile && !matchingProfile)
			{
				SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
				button_Tuning_Apply().Background(colorIgnored);
				button_Fan_Apply().Background(colorIgnored);
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				button_Tuning_Apply().Background(colorValid);
				button_Fan_Apply().Background(colorValid);
			}

			//Update status icon
			if (usingProfile)
			{
				image_Tuning_Used().Visibility(Visibility::Visible);
				image_Fans_Used().Visibility(Visibility::Visible);
			}
			else
			{
				image_Tuning_Used().Visibility(Visibility::Collapsed);
				image_Fans_Used().Visibility(Visibility::Collapsed);
			}

			//Enable saving
			co_await AsyncTaskDelay(300, AppVariables::App.GetDispatcher());
			disable_saving = false;

			//Set result
			AVDebugWriteLine(L"ADLX loaded tuning and fans values: " << deviceId << L" / " << application);
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed loading selected app values (Exception)");
		}
	}
}