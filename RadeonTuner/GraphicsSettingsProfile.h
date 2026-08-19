#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::GraphicsSettings_Profile_Add(GraphicsSettings graphicsSettings)
	{
		try
		{
			//Device identifier
			std::wstring deviceIdW = graphicsSettings.DeviceId.value();

			//Device application
			std::wstring applicationW = graphicsSettings.Application.value();

			//Get settings
			auto graphicsSettingsProfile = GraphicsSettings_Profile_Get(deviceIdW, applicationW);

			//Check settings profile
			if (!graphicsSettingsProfile.has_value())
			{
				//Check if any profile is used
				if (!GraphicsSettings_Profile_Any_Using(deviceIdW))
				{
					graphicsSettings.UsingProfile = true;
				}

				//Add settings profile
				graphicsSettingsCache.push_back(graphicsSettings);

				AVDebugWriteLine(L"Added graphics settings profile: " << deviceIdW << L" / " << applicationW << L" / Using " << graphicsSettings.UsingProfile);
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
					if (graphicsSettings.DeviceId.value() == deviceId && graphicsSettings.Application.value() == application)
					{
						return graphicsSettings;
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
					if (graphicsSettings.DeviceId.value() == deviceId)
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

	bool MainPage::GraphicsSettings_Profile_Set_UsingGlobal()
	{
		try
		{
			for (GraphicsSettings& graphicsSettings : graphicsSettingsCache)
			{
				try
				{
					if (graphicsSettings.Global())
					{
						graphicsSettings.UsingProfile = true;
					}
					else
					{
						graphicsSettings.UsingProfile = false;
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

	bool MainPage::GraphicsSettings_Profile_Set_Using(std::wstring deviceId, std::wstring application)
	{
		try
		{
			for (GraphicsSettings& graphicsSettings : graphicsSettingsCache)
			{
				try
				{
					if (graphicsSettings.DeviceId.value() == deviceId)
					{
						if (graphicsSettings.Application.value() == application)
						{
							graphicsSettings.UsingProfile = true;
						}
						else
						{
							graphicsSettings.UsingProfile = false;
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

	bool MainPage::GraphicsSettings_Profile_Any_Using(std::wstring deviceId)
	{
		bool anyUsing = false;
		try
		{
			for (GraphicsSettings& graphicsSettings : graphicsSettingsCache)
			{
				try
				{
					if (graphicsSettings.DeviceId.value() == deviceId)
					{
						if (graphicsSettings.UsingProfile)
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
			graphicsSettingsCache = jsonstring_to_struct<std::vector<GraphicsSettings>>(jsonStringW);

			//Set Global profile as using
			GraphicsSettings_Profile_Set_UsingGlobal();

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