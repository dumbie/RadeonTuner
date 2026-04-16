#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::TuningFanSettings_Profile_Add(TuningFanSettings tuningFanSettings)
	{
		try
		{
			//Device identifier
			std::wstring deviceIdW = string_to_wstring(tuningFanSettings.DeviceId.value());

			//Get tuning fan settings
			auto tuningFanSettingsProfile = TuningFanSettings_Profile_Get(deviceIdW);

			//Add tuning fan settings profile
			if (!tuningFanSettingsProfile.has_value())
			{
				AVDebugWriteLine(L"Added tuning settings profile: " + deviceIdW);
				tuningFanSettingsCache.push_back(tuningFanSettings);
			}

			//Return result
			return true;
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	bool MainPage::TuningFanSettings_Profile_Replace(TuningFanSettings tuningFanSettingsReplace)
	{
		try
		{
			for (TuningFanSettings& tuningFanSettings : tuningFanSettingsCache)
			{
				try
				{
					//Check gpu identifier
					if (tuningFanSettings.DeviceId.value() == tuningFanSettingsReplace.DeviceId.value())
					{
						tuningFanSettings = tuningFanSettingsReplace;
					}
				}
				catch (...) {}
			}

			//Return result
			return true;
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	bool MainPage::TuningFanSettings_Profile_Remove(std::wstring gpuIdentifier)
	{
		try
		{
			//Device identifier
			std::string gpuIdentifierA = wstring_to_string(gpuIdentifier);

			//Remove tuning fan settings profile
			auto iterator = std::remove_if(tuningFanSettingsCache.begin(), tuningFanSettingsCache.end(), [&](TuningFanSettings& x) { return x.DeviceId == gpuIdentifierA; });
			tuningFanSettingsCache.erase(iterator, tuningFanSettingsCache.end());

			//Return result
			return true;
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	std::optional<std::reference_wrapper<TuningFanSettings>> MainPage::TuningFanSettings_Profile_Get(std::wstring gpuIdentifier)
	{
		try
		{
			std::string gpuIdentifierA = wstring_to_string(gpuIdentifier);
			for (TuningFanSettings& tuningFanSettings : tuningFanSettingsCache)
			{
				try
				{
					//Check gpu identifier
					if (tuningFanSettings.DeviceId.value() == gpuIdentifierA)
					{
						return tuningFanSettings;
					}
				}
				catch (...) {}
			}
		}
		catch (...) {}
		return std::nullopt;
	}

	TuningFanSettings MainPage::TuningFanSettings_Profile_LoadFromFile(std::string loadPath)
	{
		try
		{
			//Open settings file
			std::string jsonString = file_to_string(loadPath);

			//Convert json to struct
			return jsonstring_to_struct<TuningFanSettings>(jsonString);
		}
		catch (...) {}
		return TuningFanSettings{};
	}

	bool MainPage::TuningFanSettings_Profile_SaveToFile(TuningFanSettings tuningFanSettings, std::string savePath)
	{
		try
		{
			//Convert json to string
			std::string jsonString = struct_to_jsonstring(tuningFanSettings, true);

			//Save settings file
			return string_to_file(savePath, jsonString);
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	bool MainPage::TuningFanSettings_Profiles_SaveToFile()
	{
		try
		{
			//Convert json to string
			std::string jsonString = struct_to_jsonstring(tuningFanSettingsCache, true);

			//Get tuning profiles file path
			std::wstring pathSettingFileW = PathMerge(PathGetExecutableDirectory(), L"Profiles\\TuningProfiles.json");
			std::string pathSettingFileA = wstring_to_string(pathSettingFileW);

			//Save tuning profiles json file
			string_to_file(pathSettingFileA, jsonString);

			AVDebugWriteLine("Saved tuning profiles: " << tuningFanSettingsCache.size());
			return true;
		}
		catch (...)
		{
			AVDebugWriteLine("Failed saving tuning profiles (Exception)");
			return false;
		}
	}

	bool MainPage::TuningFanSettings_Profiles_LoadFromFile()
	{
		try
		{
			//Get tuning profiles file path
			std::wstring pathSettingFileW = PathMerge(PathGetExecutableDirectory(), L"Profiles\\TuningProfiles.json");
			std::string pathSettingFileA = wstring_to_string(pathSettingFileW);

			//Open tuning profiles file
			std::string jsonString = file_to_string(pathSettingFileA);

			//Deserialize tuning profiles
			tuningFanSettingsCache = jsonstring_to_struct<std::vector<TuningFanSettings>>(jsonString);

			AVDebugWriteLine("Loaded tuning profiles: " << tuningFanSettingsCache.size());
			return true;
		}
		catch (...)
		{
			AVDebugWriteLine("Failed loading tuning profiles (Exception)");
			return false;
		}
	}
}