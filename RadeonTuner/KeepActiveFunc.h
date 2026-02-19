#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::KeepActive_Load_UI()
	{
		try
		{
			//Device identifier
			std::wstring device_id_w = AdlxGetGpuIdentifier(ppGpuInfo);

			//Get active overclock file path
			std::wstring pathSettingFileW = PathMerge(PathGetExecutableDirectory(), L"Active\\" + device_id_w + L".radt");
			std::string pathSettingFileA = wstring_to_string(pathSettingFileW);

			//Load tuning fan settings from file
			TuningFanSettings tuningFanSettings = TuningFanSettings_Load(pathSettingFileA);

			//Check keep active setting
			if (tuningFanSettings.KeepActive.has_value())
			{
				if (tuningFanSettings.KeepActive.value())
				{
					//Set button color
					SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
					button_Fan_Keep().Background(colorValid);
					button_Tuning_Keep().Background(colorValid);
				}
				else
				{
					//Set button color
					SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
					button_Fan_Keep().Background(colorInvalid);
					button_Tuning_Keep().Background(colorInvalid);
				}
			}
			else
			{
				//Set button color
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				button_Fan_Keep().Background(colorInvalid);
				button_Tuning_Keep().Background(colorInvalid);
			}

			//Set result
			AVDebugWriteLine("Loaded keep active setting.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed loading keep active setting.");
		}
	}

	bool MainPage::KeepActive_Export()
	{
		try
		{
			//Device identifier
			std::wstring device_id_w = AdlxGetGpuIdentifier(ppGpuInfo);

			//Get active overclock file path
			std::wstring pathSettingFileW = PathMerge(PathGetExecutableDirectory(), L"Active\\" + device_id_w + L".radt");
			std::string pathSettingFileA = wstring_to_string(pathSettingFileW);

			//Set button color
			SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
			button_Fan_Keep().Background(colorInvalid);
			button_Tuning_Keep().Background(colorInvalid);

			//Generate tuning fan settings
			TuningFanSettings tuningFanSettings = TuningFanSettings_Generate_FromUI(false);

			//Save tuning fan settings to file
			bool saveResult = TuningFanSettings_Save(tuningFanSettings, pathSettingFileA);

			//Return result
			if (saveResult)
			{
				//Update status variable
				keepactive_cache_loaded = false;

				ShowNotification(L"Keep active exported");
				AVDebugWriteLine(L"Keep active exported");
			}
			else
			{
				ShowNotification(L"Keep active export failed");
				AVDebugWriteLine(L"Keep active export failed");
			}
			return saveResult;
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	bool MainPage::KeepActive_Enable()
	{
		try
		{
			//Device identifier
			std::wstring device_id_w = AdlxGetGpuIdentifier(ppGpuInfo);

			//Get active overclock file path
			std::wstring pathSettingFileW = PathMerge(PathGetExecutableDirectory(), L"Active\\" + device_id_w + L".radt");
			std::string pathSettingFileA = wstring_to_string(pathSettingFileW);

			//Load tuning fan settings from file
			TuningFanSettings tuningFanSettings = TuningFanSettings_Load(pathSettingFileA);

			//Change keep active setting
			tuningFanSettings.KeepActive = true;

			//Save tuning fan settings to file
			bool saveResult = TuningFanSettings_Save(tuningFanSettings, pathSettingFileA);

			//Set button color
			SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
			button_Fan_Keep().Background(colorValid);
			button_Tuning_Keep().Background(colorValid);

			//Update status variable
			keepactive_cache_loaded = false;

			//Return result
			ShowNotification(L"Keep active enabled");
			AVDebugWriteLine(L"Keep active enabled");
			return true;
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	bool MainPage::KeepActive_Disable()
	{
		try
		{
			//Device identifier
			std::wstring device_id_w = AdlxGetGpuIdentifier(ppGpuInfo);

			//Get active overclock file path
			std::wstring pathSettingFileW = PathMerge(PathGetExecutableDirectory(), L"Active\\" + device_id_w + L".radt");
			std::string pathSettingFileA = wstring_to_string(pathSettingFileW);

			//Load tuning fan settings from file
			TuningFanSettings tuningFanSettings = TuningFanSettings_Load(pathSettingFileA);

			//Change keep active setting
			tuningFanSettings.KeepActive = false;

			//Save tuning fan settings to file
			bool saveResult = TuningFanSettings_Save(tuningFanSettings, pathSettingFileA);

			//Set button color
			SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
			button_Fan_Keep().Background(colorInvalid);
			button_Tuning_Keep().Background(colorInvalid);

			//Update status variable
			keepactive_cache_loaded = false;

			//Return result
			ShowNotification(L"Keep active disabled");
			AVDebugWriteLine(L"Keep active disabled");
			return true;
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	bool MainPage::KeepActive_Toggle()
	{
		try
		{
			//Device identifier
			std::wstring device_id_w = AdlxGetGpuIdentifier(ppGpuInfo);

			//Get active overclock file path
			std::wstring pathSettingFileW = PathMerge(PathGetExecutableDirectory(), L"Active\\" + device_id_w + L".radt");
			std::string pathSettingFileA = wstring_to_string(pathSettingFileW);

			//Load tuning fan settings from file
			TuningFanSettings tuningFanSettings = TuningFanSettings_Load(pathSettingFileA);

			//Toggle keep active setting
			if (tuningFanSettings.KeepActive.has_value() && tuningFanSettings.KeepActive.value())
			{
				return KeepActive_Disable();
			}
			else
			{
				return KeepActive_Enable();
			}
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}
}