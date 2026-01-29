#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	//Load settings from file
	GraphicsSettings MainPage::GraphicsSettings_Load(std::string loadPath)
	{
		try
		{
			//Open settings file
			std::string jsonString = file_to_string(loadPath);

			//Convert json to struct
			return jsonstring_to_struct<GraphicsSettings>(jsonString);
		}
		catch (...) {}
		return GraphicsSettings{};
	}

	//Save settings to file
	bool MainPage::GraphicsSettings_Save(GraphicsSettings graphicsSettings, std::string savePath)
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

	bool MainPage::GraphicsSettings_Convert_ToUI(GraphicsSettings graphicsSettings)
	{
		try
		{
			//WaitForVerticalRefresh
			if (graphicsSettings.WaitForVerticalRefresh.has_value())
			{
				combobox_VerticalRefresh().SelectedIndex(graphicsSettings.WaitForVerticalRefresh.value());
			}

			//Return result
			AVDebugWriteLine(L"Graphics settings applied to interface.");
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine(L"Failed applying graphics settings to interface.");
			return false;
		}
	}

	GraphicsSettings MainPage::GraphicsSettings_Generate_FromUI()
	{
		GraphicsSettings tuningFanSettings{};
		try
		{
			//Fix add 'Export Select' checkboxes to select settings to export

			//Identifier
			tuningFanSettings.AppId = hstring_to_string(combobox_AppSelect().SelectedValue().as<hstring>());

			//Settings
			if (combobox_VerticalRefresh().IsEnabled())
			{
				tuningFanSettings.WaitForVerticalRefresh = (int)combobox_VerticalRefresh().SelectedIndex();
			}
		}
		catch (...) {}
		return tuningFanSettings;
	}
}