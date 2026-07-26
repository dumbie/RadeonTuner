#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	//Load settings from file
	std::optional<DisplaySettings> MainPage::DisplaySettings_FileLoad(std::wstring loadPath)
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

	//Save settings to file
	bool MainPage::DisplaySettings_FileSave(DisplaySettings displaySettings, std::wstring savePath)
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
}