#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::DisplaySettings_Profile_Add(DisplaySettings displaySettings)
	{
		try
		{
			//Device identifier
			std::wstring deviceIdW = displaySettings.DeviceId.value();

			//Device application
			std::wstring applicationW = displaySettings.Application.value();

			//Get display settings
			auto displaySettingsProfile = DisplaySettings_Profile_Get(deviceIdW, applicationW);

			//Check display settings profile
			if (!displaySettingsProfile.has_value())
			{
				//Check if any profile is used
				if (!DisplaySettings_Profile_Any_Using(deviceIdW))
				{
					displaySettings.UsingProfile = true;
				}

				//Add display settings profile
				displaySettingsCache.push_back(displaySettings);

				//Save display settings profile
				DisplaySettings_Profiles_SaveToFile();

				AVDebugWriteLine(L"Added display settings profile: " << deviceIdW << L" / " << applicationW << L" / Using " << displaySettings.UsingProfile);
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

	bool MainPage::DisplaySettings_Profile_Replace(DisplaySettings displaySettingsReplace)
	{
		try
		{
			for (DisplaySettings& displaySettings : displaySettingsCache)
			{
				try
				{
					if (displaySettings.DeviceId.value() == displaySettingsReplace.DeviceId.value() && displaySettings.Application.value() == displaySettingsReplace.Application.value())
					{
						displaySettings = displaySettingsReplace;
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

	bool MainPage::DisplaySettings_Profile_Remove(std::wstring deviceId, std::wstring application)
	{
		try
		{
			//Remove display settings profile
			auto iterator = std::remove_if(displaySettingsCache.begin(), displaySettingsCache.end(), [&](DisplaySettings& x) { return x.DeviceId == deviceId && x.Application == application; });
			displaySettingsCache.erase(iterator, displaySettingsCache.end());

			//Return result
			return true;
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	std::optional<std::reference_wrapper<DisplaySettings>> MainPage::DisplaySettings_Profile_Get(std::wstring deviceId, std::wstring application)
	{
		try
		{
			for (DisplaySettings& displaySettings : displaySettingsCache)
			{
				try
				{
					if (displaySettings.DeviceId.value() == deviceId && displaySettings.Application.value() == application)
					{
						return displaySettings;
					}
				}
				catch (...) {}
			}
		}
		catch (...) {}
		return std::nullopt;
	}

	std::vector<std::wstring> MainPage::DisplaySettings_Profile_GetAllApps(std::wstring deviceId)
	{
		std::vector<std::wstring> apps{};
		try
		{
			for (DisplaySettings& displaySettings : displaySettingsCache)
			{
				try
				{
					if (displaySettings.DeviceId.value() == deviceId)
					{
						if (displaySettings.Application.has_value())
						{
							std::wstring appName = displaySettings.Application.value();
							if (appName != L"Global")
							{
								apps.push_back(displaySettings.Application.value());
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

	bool MainPage::DisplaySettings_Profile_Set_UsingGlobal()
	{
		try
		{
			for (DisplaySettings& displaySettings : displaySettingsCache)
			{
				try
				{
					if (displaySettings.Global())
					{
						displaySettings.UsingProfile = true;
					}
					else
					{
						displaySettings.UsingProfile = false;
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

	bool MainPage::DisplaySettings_Profile_Set_Using(std::wstring deviceId, std::wstring application)
	{
		try
		{
			for (DisplaySettings& displaySettings : displaySettingsCache)
			{
				try
				{
					if (displaySettings.DeviceId.value() == deviceId)
					{
						if (displaySettings.Application.value() == application)
						{
							displaySettings.UsingProfile = true;
						}
						else
						{
							displaySettings.UsingProfile = false;
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

	bool MainPage::DisplaySettings_Profile_Any_Using(std::wstring deviceId)
	{
		bool anyUsing = false;
		try
		{
			for (DisplaySettings& displaySettings : displaySettingsCache)
			{
				try
				{
					if (displaySettings.DeviceId.value() == deviceId)
					{
						if (displaySettings.UsingProfile)
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

	std::optional<DisplaySettings> MainPage::DisplaySettings_Profile_LoadFromFile(std::wstring loadPath)
	{
		try
		{
			//Open settings file
			std::wstring jsonStringW = file_to_string(loadPath);

			//Convert json to struct
			return jsonstring_to_struct<DisplaySettings>(jsonStringW);
		}
		catch (...) {}
		return std::nullopt;
	}

	bool MainPage::DisplaySettings_Profile_SaveToFile(DisplaySettings displaySettings, std::wstring savePath)
	{
		try
		{
			//Convert json to string
			std::wstring jsonStringW = struct_to_jsonstring(displaySettings, true);

			//Save settings file
			return string_to_file(savePath, jsonStringW);
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	bool MainPage::DisplaySettings_Profiles_SaveToFile()
	{
		try
		{
			//Convert json to string
			std::wstring jsonStringW = struct_to_jsonstring(displaySettingsCache, true);

			//Get display profiles file path	
			std::wstring pathSettingFileW = PathMerge(AppVariables::SaveDataPath, L"Profiles\\DisplayProfiles.json");

			//Save display profiles json file
			string_to_file(pathSettingFileW, jsonStringW);

			AVDebugWriteLine("Saved display profiles: " << displaySettingsCache.size());
			return true;
		}
		catch (...)
		{
			AVDebugWriteLine("Failed saving display profiles (Exception)");
			return false;
		}
	}

	bool MainPage::DisplaySettings_Profiles_LoadFromFile()
	{
		try
		{
			//Get display profiles file path
			std::wstring pathSettingFileW = PathMerge(AppVariables::SaveDataPath, L"Profiles\\DisplayProfiles.json");

			//Open display profiles file
			std::wstring jsonStringW = file_to_string(pathSettingFileW);

			//Deserialize display profiles
			displaySettingsCache = jsonstring_to_struct<std::vector<DisplaySettings>>(jsonStringW);

			//Set Global profile as using
			DisplaySettings_Profile_Set_UsingGlobal();

			AVDebugWriteLine("Loaded display profiles: " << displaySettingsCache.size());
			return true;
		}
		catch (...)
		{
			AVDebugWriteLine("Failed loading display profiles (Exception)");
			return false;
		}
	}
}