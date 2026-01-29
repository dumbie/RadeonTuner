#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	//Load settings from file
	DisplaySettings MainPage::DisplaySettings_Load(std::string loadPath)
	{
		try
		{
			//Open settings file
			std::string jsonString = file_to_string(loadPath);

			//Convert json to struct
			return jsonstring_to_struct<DisplaySettings>(jsonString);
		}
		catch (...) {}
		return DisplaySettings{};
	}

	//Save settings to file
	bool MainPage::DisplaySettings_Save(DisplaySettings displaySettings, std::string savePath)
	{
		try
		{
			//Convert json to string
			std::string jsonString = struct_to_jsonstring(displaySettings, true);

			//Save settings file
			return string_to_file(savePath, jsonString);
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	bool MainPage::DisplaySettings_Convert_ToUI(DisplaySettings displaySettings)
	{
		try
		{
			//FreeSync
			if (displaySettings.FreeSync.has_value())
			{
				toggleswitch_FreeSync().IsOn(displaySettings.FreeSync.value());
			}

			//Return result
			AVDebugWriteLine(L"Display settings applied to interface.");
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine(L"Failed applying display settings to interface.");
			return false;
		}
	}

	DisplaySettings MainPage::DisplaySettings_Generate_FromUI()
	{
		DisplaySettings displaySettings{};
		try
		{
			//Identifier
			std::wstring device_id_w = AdlxGetDisplayIdentifier(ppDisplayInfo);
			if (!device_id_w.empty())
			{
				displaySettings.DeviceId = wstring_to_string(device_id_w);
			}

			//Settings
			if (toggleswitch_FreeSync().IsEnabled())
			{
				displaySettings.FreeSync = (bool)toggleswitch_FreeSync().IsOn();
			}
		}
		catch (...) {}
		return displaySettings;
	}
}