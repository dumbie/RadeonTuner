#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::fire_and_forget MainPage::AdlxValuesLoadSelectMultimediaApp()
	{
		try
		{
			//Disable saving
			disable_saving = true;

			//Get current and default settings
			multimediaSettingsCurrent = MultimediaSettings_Generate_FromADL(adl_Gpu_AdapterIndex).value();

			//Convert settings values to interface
			MultimediaSettings_Convert_ToUI_Adl(multimediaSettingsCurrent);

			//Update button colors
			SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
			button_Multimedia_Apply().Background(colorValid);

			//Enable saving
			co_await AsyncTaskDelay(300, AppVariables::App.GetDispatcher());
			disable_saving = false;

			//Set result
			AVDebugWriteLine("ADLX loaded multimedia values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading multimedia values.");
		}
	}
}