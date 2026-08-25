#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::MultimediaSettings_Profile_Add(MultimediaSettings multimediaSettings)
	{
		try
		{
			//Device identifier
			std::wstring deviceIdW = multimediaSettings.DeviceId.value();

			//Device application
			std::wstring applicationW = multimediaSettings.Application.value();

			//Get settings
			auto multimediaSettingsProfile = MultimediaSettings_Profile_Get(deviceIdW, applicationW);

			//Check settings profile
			bool profileAdded = false;
			if (!multimediaSettingsProfile.has_value())
			{
				//Check if any profile is used
				if (!MultimediaSettings_Profile_Any_Using(deviceIdW))
				{
					multimediaSettings.UsingProfile = true;
				}

				//Add settings profile
				multimediaSettingsCache.push_back(multimediaSettings);
				profileAdded = true;

				AVDebugWriteLine(L"Added multimedia settings profile: " << deviceIdW << L" / " << applicationW << L" / Using " << multimediaSettings.UsingProfile);
			}

			//Return result
			return profileAdded;
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	bool MainPage::MultimediaSettings_Profile_Remove(std::wstring deviceId, std::wstring application)
	{
		try
		{
			//Remove settings profile
			auto iterator = std::remove_if(multimediaSettingsCache.begin(), multimediaSettingsCache.end(), [&](MultimediaSettings& x) { return x.DeviceId == deviceId && x.Application == application; });
			multimediaSettingsCache.erase(iterator, multimediaSettingsCache.end());

			//Return result
			return true;
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	std::optional<std::reference_wrapper<MultimediaSettings>> MainPage::MultimediaSettings_Profile_Get(std::wstring deviceId, std::wstring application)
	{
		try
		{
			for (MultimediaSettings& multimediaSettings : multimediaSettingsCache)
			{
				try
				{
					if (multimediaSettings.DeviceId.value() == deviceId && multimediaSettings.Application.value() == application)
					{
						return multimediaSettings;
					}
				}
				catch (...) {}
			}
		}
		catch (...) {}
		return std::nullopt;
	}

	std::vector<std::wstring> MainPage::MultimediaSettings_Profile_GetAllApps(std::wstring deviceId)
	{
		std::vector<std::wstring> apps{};
		try
		{
			for (MultimediaSettings& multimediaSettings : multimediaSettingsCache)
			{
				try
				{
					if (multimediaSettings.DeviceId.value() == deviceId)
					{
						if (multimediaSettings.Application.has_value())
						{
							std::wstring appName = multimediaSettings.Application.value();
							if (appName != L"Global")
							{
								apps.push_back(multimediaSettings.Application.value());
							}
						}
					}
				}
				catch (...) {}
			}

			//Sort applications by name
			std::sort(apps.begin(), apps.end(), [](const std::wstring& a, const std::wstring& b) { return wstring_to_lower(a) < wstring_to_lower(b); });
		}
		catch (...) {}
		return apps;
	}

	bool MainPage::MultimediaSettings_Profile_Set_UsingGlobal()
	{
		try
		{
			for (MultimediaSettings& multimediaSettings : multimediaSettingsCache)
			{
				try
				{
					if (multimediaSettings.Global())
					{
						multimediaSettings.UsingProfile = true;
					}
					else
					{
						multimediaSettings.UsingProfile = false;
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

	bool MainPage::MultimediaSettings_Profile_Set_Using(std::wstring deviceId, std::wstring application)
	{
		try
		{
			for (MultimediaSettings& multimediaSettings : multimediaSettingsCache)
			{
				try
				{
					if (multimediaSettings.DeviceId.value() == deviceId)
					{
						if (multimediaSettings.Application.value() == application)
						{
							multimediaSettings.UsingProfile = true;
						}
						else
						{
							multimediaSettings.UsingProfile = false;
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

	bool MainPage::MultimediaSettings_Profile_Any_Using(std::wstring deviceId)
	{
		bool anyUsing = false;
		try
		{
			for (MultimediaSettings& multimediaSettings : multimediaSettingsCache)
			{
				try
				{
					if (multimediaSettings.DeviceId.value() == deviceId)
					{
						if (multimediaSettings.UsingProfile)
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

	std::optional<MultimediaSettings> MainPage::MultimediaSettings_Profile_LoadFromFile(std::wstring loadPath)
	{
		try
		{
			//Open settings file
			std::wstring jsonStringW = file_to_string(loadPath);

			//Convert json to struct
			return jsonstring_to_struct<MultimediaSettings>(jsonStringW);
		}
		catch (...) {}
		return std::nullopt;
	}

	bool MainPage::MultimediaSettings_Profile_SaveToFile(MultimediaSettings multimediaSettings, std::wstring savePath)
	{
		try
		{
			//Convert json to string
			std::wstring jsonStringW = struct_to_jsonstring(multimediaSettings, true);

			//Save settings file
			return string_to_file(savePath, jsonStringW);
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	bool MainPage::MultimediaSettings_Profiles_SaveToFile()
	{
		try
		{
			//Convert json to string
			std::wstring jsonStringW = struct_to_jsonstring(multimediaSettingsCache, true);

			//Get profiles file path
			std::wstring pathSettingFileW = PathMerge(AppVariables::SaveDataPath, L"Profiles\\MultimediaProfiles.json");

			//Save profiles json file
			string_to_file(pathSettingFileW, jsonStringW);

			AVDebugWriteLine("Saved multimedia profiles: " << multimediaSettingsCache.size());
			return true;
		}
		catch (...)
		{
			AVDebugWriteLine("Failed saving multimedia profiles (Exception)");
			return false;
		}
	}

	bool MainPage::MultimediaSettings_Profiles_LoadFromFile()
	{
		try
		{
			//Get profiles file path
			std::wstring pathSettingFileW = PathMerge(AppVariables::SaveDataPath, L"Profiles\\MultimediaProfiles.json");

			//Open profiles file
			std::wstring jsonStringW = file_to_string(pathSettingFileW);

			//Deserialize profiles
			multimediaSettingsCache = jsonstring_to_struct<std::deque<MultimediaSettings>>(jsonStringW);

			//Set Global profile as using
			MultimediaSettings_Profile_Set_UsingGlobal();

			AVDebugWriteLine("Loaded multimedia profiles: " << multimediaSettingsCache.size());
			return true;
		}
		catch (...)
		{
			AVDebugWriteLine("Failed loading multimedia profiles (Exception)");
			return false;
		}
	}
}