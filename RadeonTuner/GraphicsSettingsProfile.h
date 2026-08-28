#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::GraphicsSettings_Profile_Add(GraphicsSettings graphicsSettingsAdd)
	{
		try
		{
			//Device identifier
			std::wstring deviceIdW = graphicsSettingsAdd.DeviceId.value();

			//Device application
			std::wstring applicationW = graphicsSettingsAdd.Application.value();

			//Get settings
			auto graphicsSettingsGet = GraphicsSettings_Profile_Get(deviceIdW, applicationW);

			//Check settings profile
			bool profileAdded = false;
			if (!graphicsSettingsGet.has_value())
			{
				//Add settings profile
				graphicsSettingsCache.push_back(graphicsSettingsAdd);
				profileAdded = true;

				AVDebugWriteLine(L"Added graphics settings profile: " << deviceIdW << L" / " << applicationW);
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

	bool MainPage::GraphicsSettings_Profile_Replace(GraphicsSettings graphicsSettingsReplace)
	{
		try
		{
			for (GraphicsSettings& graphicsSettings : graphicsSettingsCache)
			{
				try
				{
					if (graphicsSettings.DeviceId.value() == graphicsSettingsReplace.DeviceId.value() && graphicsSettings.Application.value() == graphicsSettingsReplace.Application.value())
					{
						graphicsSettings = graphicsSettingsReplace;
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

	bool MainPage::GraphicsSettings_Profile_Remove(std::wstring deviceId, std::wstring application)
	{
		try
		{
			//Remove settings profile
			auto iterator = std::remove_if(graphicsSettingsCache.begin(), graphicsSettingsCache.end(), [&](GraphicsSettings& x) { return x.DeviceId == deviceId && x.Application == application; });
			graphicsSettingsCache.erase(iterator, graphicsSettingsCache.end());

			AVDebugWriteLine(L"Removed graphics settings profile: " << deviceId << L" / " << application);

			//Return result
			return true;
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	std::optional<std::reference_wrapper<GraphicsSettings>> MainPage::GraphicsSettings_Profile_Get(std::wstring deviceId, std::wstring application)
	{
		try
		{
			for (GraphicsSettings& graphicsSettings : graphicsSettingsCache)
			{
				try
				{
					//DriverBug#1 if (graphicsSettings.DeviceId.value() == deviceId && graphicsSettings.Application.value() == application)
					if (graphicsSettings.Application.value() == application)
					{
						if (graphicsSettings.Global())
						{
							if (graphicsSettings.DeviceId.value() == deviceId)
							{
								return graphicsSettings;
							}
						}
						else
						{
							return graphicsSettings;
						}
					}
				}
				catch (...) {}
			}
		}
		catch (...) {}
		return std::nullopt;
	}

	std::vector<std::wstring> MainPage::GraphicsSettings_Profile_GetAllApps(std::wstring deviceId)
	{
		std::vector<std::wstring> apps{};
		try
		{
			for (GraphicsSettings& graphicsSettings : graphicsSettingsCache)
			{
				try
				{
					//DriverBug#1 if (graphicsSettings.DeviceId.value() == deviceId)
					{
						if (graphicsSettings.Application.has_value())
						{
							std::wstring appName = graphicsSettings.Application.value();
							if (appName != L"Global")
							{
								apps.push_back(appName);
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

	std::optional<GraphicsSettings> MainPage::GraphicsSettings_Profile_LoadFromFile(std::wstring loadPath)
	{
		try
		{
			//Open settings file
			std::wstring jsonStringW = file_to_string(loadPath);

			//Convert json to struct
			return jsonstring_to_struct<GraphicsSettings>(jsonStringW);
		}
		catch (...) {}
		return std::nullopt;
	}

	bool MainPage::GraphicsSettings_Profile_SaveToFile(GraphicsSettings graphicsSettings, std::wstring savePath)
	{
		try
		{
			//Convert json to string
			std::wstring jsonStringW = struct_to_jsonstring(graphicsSettings, true);

			//Save settings file
			return string_to_file(savePath, jsonStringW);
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	bool MainPage::GraphicsSettings_Profiles_SaveToFile()
	{
		try
		{
			//Convert json to string
			std::wstring jsonStringW = struct_to_jsonstring(graphicsSettingsCache, true);

			//Get profiles file path
			std::wstring pathSettingFileW = PathMerge(AppVariables::SaveDataPath, L"Profiles\\GraphicsProfiles.json");

			//Save profiles json file
			string_to_file(pathSettingFileW, jsonStringW);

			AVDebugWriteLine("Saved graphics profiles: " << graphicsSettingsCache.size());
			return true;
		}
		catch (...)
		{
			AVDebugWriteLine("Failed saving graphics profiles (Exception)");
			return false;
		}
	}

	bool MainPage::GraphicsSettings_Profiles_LoadFromFile()
	{
		try
		{
			//Get profiles file path
			std::wstring pathSettingFileW = PathMerge(AppVariables::SaveDataPath, L"Profiles\\GraphicsProfiles.json");

			//Open profiles file
			std::wstring jsonStringW = file_to_string(pathSettingFileW);

			//Deserialize profiles
			graphicsSettingsCache = jsonstring_to_struct<std::deque<GraphicsSettings>>(jsonStringW);

			AVDebugWriteLine("Loaded graphics profiles: " << graphicsSettingsCache.size());
			return true;
		}
		catch (...)
		{
			AVDebugWriteLine("Failed loading graphics profiles (Exception)");
			return false;
		}
	}
}