#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	//Load settings from file
	AdlApplication MainPage::GraphicsSettings_Load(std::string loadPath)
	{
		try
		{
			//Open settings file
			std::string jsonString = file_to_string(loadPath);

			//Convert json to struct
			return jsonstring_to_struct<AdlApplication>(jsonString);
		}
		catch (...) {}
		return AdlApplication{};
	}

	//Save settings to file
	bool MainPage::GraphicsSettings_Save(AdlApplication graphicsSettings, std::string savePath)
	{
		try
		{
			//Convert json to string
			std::string jsonString = struct_to_jsonstring(graphicsSettings, true);

			//Save settings file
			return string_to_file(savePath, jsonString);
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}
}