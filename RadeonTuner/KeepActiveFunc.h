#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::KeepActive_Enable(bool saveProfile)
	{
		try
		{
			//Device identifier
			std::wstring device_id_w = AdlxGetGpuIdentifier(ppGpuInfo);

			//Get tuning fan settings
			TuningFanSettings& tuningFanSettings = TuningFanSettings_Profile_Get(device_id_w).value();

			//Change keep active setting
			tuningFanSettings.KeepActive = true;

			//Save tuning fan settings to file
			if (saveProfile)
			{
				TuningFanSettings_Profiles_SaveToFile();
			}

			//Set button color
			SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
			button_Fan_Keep().Background(colorValid);
			button_Tuning_Keep().Background(colorValid);

			//Return result
			ShowNotification(L"Keep active enabled");
			AVDebugWriteLine(L"Keep active enabled.");
			return true;
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	bool MainPage::KeepActive_Disable(bool saveProfile)
	{
		try
		{
			//Device identifier
			std::wstring device_id_w = AdlxGetGpuIdentifier(ppGpuInfo);

			//Get tuning fan settings
			TuningFanSettings& tuningFanSettings = TuningFanSettings_Profile_Get(device_id_w).value();

			//Change keep active setting
			tuningFanSettings.KeepActive = false;

			//Save tuning fan settings to file
			if (saveProfile)
			{
				TuningFanSettings_Profiles_SaveToFile();
			}

			//Set button color
			SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
			button_Fan_Keep().Background(colorInvalid);
			button_Tuning_Keep().Background(colorInvalid);

			//Return result
			ShowNotification(L"Keep active disabled");
			AVDebugWriteLine(L"Keep active disabled.");
			return true;
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	void MainPage::KeepActive_Toggle()
	{
		try
		{
			//Device identifier
			std::wstring device_id_w = AdlxGetGpuIdentifier(ppGpuInfo);

			//Get tuning fan settings
			TuningFanSettings& tuningFanSettings = TuningFanSettings_Profile_Get(device_id_w).value();

			//Toggle keep active setting
			if (tuningFanSettings.KeepActive.has_value())
			{
				if (tuningFanSettings.KeepActive.value())
				{
					KeepActive_Disable(true);
				}
				else
				{
					KeepActive_Enable(true);
				}
			}
			else
			{
				//Return result
				ShowNotification(L"Apply settings first");
				AVDebugWriteLine(L"Apply settings first.");
			}
		}
		catch (...) {}
	}
}