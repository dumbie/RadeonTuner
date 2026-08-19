#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::fire_and_forget MainPage::AdlxValuesLoadSelectGraphicsApp(int gpuAdapterIndex, std::wstring application)
	{
		try
		{
			//Check application
			if (application.empty())
			{
				co_return;
			}

			//Disable saving
			disable_saving = true;

			//Get current and default settings
			GraphicsSettings graphicsSettingsAdl{};
			if (application == L"Global")
			{
				graphicsSettingsAdl = GraphicsSettings_Generate_FromADLRegistry(gpuAdapterIndex, application).value();
			}
			else
			{
				//Get adl application
				AdlApplication adlApplication = AdlAppLoadSearch(L"3D_User", application, L"*\\*").value();

				//Update current and default settings
				graphicsSettingsAdl = GraphicsSettings_Generate_FromADLApp(gpuAdapterIndex, adlApplication).value();
			}

			//Add settings profile
			if (GraphicsSettings_Profile_Add(graphicsSettingsAdl))
			{
				//Save settings profile
				GraphicsSettings_Profiles_SaveToFile();
			}

			//Device identifier
			std::wstring deviceId = graphicsSettingsAdl.DeviceId.value();

			//Get and set settings
			graphicsSettingsCurrent = GraphicsSettings_Profile_Get(deviceId, application).value();

			//Convert settings values to interface
			GraphicsSettings_Convert_ToUI_Adl(graphicsSettingsAdl);
			GraphicsSettings_Convert_ToUI_Profile(graphicsSettingsCurrent.get(), AdlSettingGet::Current);

			//Update button text
			textblock_AppSelect_Graphics().Text(application);

			//Update button colors
			//Fix check if current settings match profile and set button color accordingly
			SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
			button_Graphics_Apply().Background(colorValid);

			//Enable saving
			co_await AsyncTaskDelay(300, AppVariables::App.GetDispatcher());
			disable_saving = false;

			//Set result
			AVDebugWriteLine(L"ADLX loaded graphics values: " << deviceId << L" / " << application);
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed loading selected app values (Exception)");
		}
	}
}