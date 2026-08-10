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
			std::wstring deviceIdW = tuningFanSettings.DeviceId.value();

			//Device application
			std::wstring applicationW = tuningFanSettings.Application.value();

			//Get tuning fan settings
			auto tuningFanSettingsProfile = TuningFanSettings_Profile_Get(deviceIdW, applicationW);

			//Check tuning fan settings profile
			if (!tuningFanSettingsProfile.has_value())
			{
				//Check if any profile is used
				if (!TuningFanSettings_Profile_Any_Using(deviceIdW))
				{
					tuningFanSettings.UsingProfile = true;
				}

				//Add tuning fan settings profile
				tuningFanSettingsCache.push_back(tuningFanSettings);

				//Save tuning fan settings profile
				TuningFanSettings_Profiles_SaveToFile();

				AVDebugWriteLine(L"Added tuning settings profile: " << deviceIdW << L" / " << applicationW << L" / Using " << tuningFanSettings.UsingProfile);
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
					if (tuningFanSettings.DeviceId.value() == tuningFanSettingsReplace.DeviceId.value() && tuningFanSettings.Application.value() == tuningFanSettingsReplace.Application.value())
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

	bool MainPage::TuningFanSettings_Profile_Remove(std::wstring deviceId, std::wstring application)
	{
		try
		{
			//Remove tuning fan settings profile
			auto iterator = std::remove_if(tuningFanSettingsCache.begin(), tuningFanSettingsCache.end(), [&](TuningFanSettings& x) { return x.DeviceId == deviceId && x.Application == application; });
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

	std::optional<std::reference_wrapper<TuningFanSettings>> MainPage::TuningFanSettings_Profile_Get(std::wstring deviceId, std::wstring application)
	{
		try
		{
			for (TuningFanSettings& tuningFanSettings : tuningFanSettingsCache)
			{
				try
				{
					if (tuningFanSettings.DeviceId.value() == deviceId && tuningFanSettings.Application.value() == application)
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

	std::vector<std::wstring> MainPage::TuningFanSettings_Profile_GetAllApps(std::wstring deviceId)
	{
		std::vector<std::wstring> apps{};
		try
		{
			for (TuningFanSettings& tuningFanSettings : tuningFanSettingsCache)
			{
				try
				{
					if (tuningFanSettings.DeviceId.value() == deviceId)
					{
						if (tuningFanSettings.Application.has_value())
						{
							std::wstring appName = tuningFanSettings.Application.value();
							if (appName != L"Global")
							{
								apps.push_back(tuningFanSettings.Application.value());
							}
						}
					}
				}
				catch (...) {}
			}

			//Sort applications by name
			std::sort(apps.begin(), apps.end());
		}
		catch (...) {}
		return apps;
	}

	bool MainPage::TuningFanSettings_Profile_Set_UsingGlobal()
	{
		try
		{
			for (TuningFanSettings& tuningFanSettings : tuningFanSettingsCache)
			{
				try
				{
					if (tuningFanSettings.Application.value() == L"Global")
					{
						tuningFanSettings.UsingProfile = true;
					}
					else
					{
						tuningFanSettings.UsingProfile = false;
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

	bool MainPage::TuningFanSettings_Profile_Set_Using(std::wstring deviceId, std::wstring application)
	{
		try
		{
			for (TuningFanSettings& tuningFanSettings : tuningFanSettingsCache)
			{
				try
				{
					if (tuningFanSettings.DeviceId.value() == deviceId)
					{
						if (tuningFanSettings.Application.value() == application)
						{
							tuningFanSettings.UsingProfile = true;
						}
						else
						{
							tuningFanSettings.UsingProfile = false;
						}
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

	bool MainPage::TuningFanSettings_Profile_Any_Using(std::wstring deviceId)
	{
		bool anyUsing = false;
		try
		{
			for (TuningFanSettings& tuningFanSettings : tuningFanSettingsCache)
			{
				try
				{
					if (tuningFanSettings.DeviceId.value() == deviceId)
					{
						if (tuningFanSettings.UsingProfile)
						{
							anyUsing = true;
						}
					}
				}
				catch (...) {}
			}
		}
		catch (...) {}
		//Return result
		return anyUsing;
	}

	std::optional<TuningFanSettings> MainPage::TuningFanSettings_Profile_LoadFromFile(std::wstring loadPath)
	{
		try
		{
			//Open settings file
			std::wstring jsonStringW = file_to_string(loadPath);

			//Convert json to struct
			return jsonstring_to_struct<TuningFanSettings>(jsonStringW);
		}
		catch (...) {}
		return std::nullopt;
	}

	bool MainPage::TuningFanSettings_Profile_SaveToFile(TuningFanSettings tuningFanSettings, std::wstring savePath)
	{
		try
		{
			//Convert json to string
			std::wstring jsonStringW = struct_to_jsonstring(tuningFanSettings, true);

			//Save settings file
			return string_to_file(savePath, jsonStringW);
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
			std::wstring jsonStringW = struct_to_jsonstring(tuningFanSettingsCache, true);

			//Get tuning profiles file path	
			std::wstring pathSettingFileW = PathMerge(AppVariables::SaveDataPath, L"Profiles\\TuningProfiles.json");

			//Save tuning profiles json file
			string_to_file(pathSettingFileW, jsonStringW);

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
			std::wstring pathSettingFileW = PathMerge(AppVariables::SaveDataPath, L"Profiles\\TuningProfiles.json");

			//Open tuning profiles file
			std::wstring jsonStringW = file_to_string(pathSettingFileW);

			//Deserialize tuning profiles
			tuningFanSettingsCache = jsonstring_to_struct<std::vector<TuningFanSettings>>(jsonStringW);

			//Set Global profile as using
			TuningFanSettings_Profile_Set_UsingGlobal();

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