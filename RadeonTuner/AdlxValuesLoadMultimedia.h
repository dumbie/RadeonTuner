#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::fire_and_forget MainPage::AdlxValuesLoadSelectMultimediaApp(int gpuAdapterIndex, std::wstring application)
	{
		try
		{
			//Disable saving
			disable_saving = true;

			//Get current and default settings
			MultimediaSettings multimediaSettingsAdl = MultimediaSettings_Generate_FromADL(gpuAdapterIndex, application, false).value();

			//Add settings profile
			if (MultimediaSettings_Profile_Add(multimediaSettingsAdl))
			{
				//Save settings profile
				MultimediaSettings_Profiles_SaveToFile();
			}

			//Device identifier
			std::wstring deviceId = multimediaSettingsAdl.DeviceId.value();

			//Get and set settings
			multimediaSettingsCurrent = MultimediaSettings_Profile_Get(deviceId, application).value();

			//Convert settings values to interface
			MultimediaSettings_Convert_ToUI_Adl(multimediaSettingsAdl);
			MultimediaSettings_Convert_ToUI_Profile(multimediaSettingsCurrent.get(), AdlSettingGet::Current);

			//Update button text
			textblock_AppSelect_Multimedia().Text(application);

			//Update button colors
			bool usingProfile = multimediaSettingsCurrent.get().UsingProfile;
			bool matchingProfile = MultimediaSettings_Match(multimediaSettingsCurrent.get(), multimediaSettingsAdl);
			if (usingProfile && !matchingProfile)
			{
				SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
				button_Multimedia_Apply().Background(colorIgnored);
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				button_Multimedia_Apply().Background(colorValid);
			}

			//Update status icon
			if (usingProfile)
			{
				image_Multimedia_Used().Visibility(Visibility::Visible);
			}
			else
			{
				image_Multimedia_Used().Visibility(Visibility::Collapsed);
			}

			//Enable saving
			co_await AsyncTaskDelay(300, AppVariables::App.GetDispatcher());
			disable_saving = false;

			//Set result
			AVDebugWriteLine(L"ADLX loaded multimedia values: " << deviceId << L" / " << application);
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading multimedia values.");
		}
	}
}