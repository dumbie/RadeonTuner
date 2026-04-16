#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	//Load settings from file
	std::optional<AdlApplication> MainPage::GraphicsSettings_FileLoad(std::string loadPath)
	{
		try
		{
			//Open settings file
			std::string jsonString = file_to_string(loadPath);

			//Convert json to struct
			return jsonstring_to_struct<AdlApplication>(jsonString);
		}
		catch (...) {}
		return std::nullopt;
	}

	//Save settings to file
	bool MainPage::GraphicsSettings_FileSave(AdlApplication graphicsSettings, std::string savePath)
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