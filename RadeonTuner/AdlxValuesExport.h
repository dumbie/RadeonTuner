#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesExport(std::string exportPath="")
	{
		try
		{
			//Check export path
			std::string exportPathFinal;
			if (exportPath.empty())
			{
				//Select settings file
				wchar_t lpstrFileName[MAX_PATH] = {};
				OPENFILENAMEW openFileName = {};
				openFileName.lStructSize = sizeof(openFileName);
				openFileName.lpstrTitle = L"Export tuning and fans settings...";
				openFileName.lpstrFilter = L"Setting files (radt)\0*.radt\0";
				openFileName.lpstrDefExt = L"radt";
				openFileName.lpstrFile = lpstrFileName;
				openFileName.nMaxFile = MAX_PATH;
				openFileName.Flags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
				if (!GetSaveFileNameW(&openFileName))
				{
					return;
				}
				else
				{
					exportPathFinal = wchar_to_string(lpstrFileName);
				}
			}
			else
			{
				exportPathFinal = exportPath;
			}

			//Fix add option to export graphics and display settings

			//Generate tuning fan settings
			TuningFanSettings tuningFanSettings = Generate_TuningFanSettings();

			//Convert tuning fan settings
			nlohmann::json jsonData = Generate_TuningFanSettings(tuningFanSettings);

			//Convert json to string
			std::string jsonString = jsonData.dump();

			//Save settings file
			string_to_file(exportPathFinal, jsonString);

			//Set result
			textblock_Status().Text(L"Tuning and fans exported");
			AVDebugWriteLine(L"Tuning and fans exported");
		}
		catch (...)
		{
			//Set result
			textblock_Status().Text(L"Tuning and fans not exported");
			AVDebugWriteLine(L"Tuning and fans not exported");
		}
	}
}