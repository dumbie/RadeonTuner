#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

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
			//Color Temperature
			if (displaySettings.ColorTemperature.has_value())
			{
				slider_Display_ColorTemperature().Value(displaySettings.ColorTemperature.value());
			}

			//Brightness
			if (displaySettings.Brightness.has_value())
			{
				slider_Display_Brightness().Value(displaySettings.Brightness.value());
			}

			//Contrast
			if (displaySettings.Contrast.has_value())
			{
				slider_Display_Contrast().Value(displaySettings.Contrast.value());
			}

			//Saturation
			if (displaySettings.Saturation.has_value())
			{
				slider_Display_Saturation().Value(displaySettings.Saturation.value());
			}

			//Hue
			if (displaySettings.Hue.has_value())
			{
				slider_Display_Hue().Value(displaySettings.Hue.value());
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

			//Color Temperature
			if (slider_Display_ColorTemperature().IsEnabled())
			{
				displaySettings.ColorTemperature = slider_Display_ColorTemperature().Value();
			}

			//Brightness
			if (slider_Display_Brightness().IsEnabled())
			{
				displaySettings.Brightness = slider_Display_Brightness().Value();
			}

			//Contrast
			if (slider_Display_Contrast().IsEnabled())
			{
				displaySettings.Contrast = slider_Display_Contrast().Value();
			}

			//Saturation
			if (slider_Display_Saturation().IsEnabled())
			{
				displaySettings.Saturation = slider_Display_Saturation().Value();
			}

			//Hue
			if (slider_Display_Hue().IsEnabled())
			{
				displaySettings.Hue = slider_Display_Hue().Value();
			}
		}
		catch (...) {}
		return displaySettings;
	}
}