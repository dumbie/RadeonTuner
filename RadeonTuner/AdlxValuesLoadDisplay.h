#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::fire_and_forget MainPage::AdlxValuesLoadSelectDisplayApp(int dispAdapterIndex, int dispDisplayIndex, std::wstring application)
	{
		try
		{
			//Disable saving
			disable_saving = true;

			//Get current and default settings
			DisplaySettings displaySettingsAdl = DisplaySettings_Generate_FromADL(dispAdapterIndex, dispDisplayIndex, application).value();

			//Add settings profile
			DisplaySettings_Profile_Add(displaySettingsAdl);

			//Device identifier
			std::wstring deviceId = displaySettingsAdl.DeviceId.value();

			//Get and set settings
			displaySettingsCurrent = DisplaySettings_Profile_Get(deviceId, application).value();

			//Convert settings values to interface
			DisplaySettings_Convert_ToUI_Adl(displaySettingsAdl);
			DisplaySettings_Convert_ToUI_Profile(displaySettingsCurrent.get(), AdlSettingGet::Current);

			//Update button text
			textblock_AppSelect_Display().Text(application);

			//Disable or enable settings
			if (displaySettingsCurrent.get().Global())
			{
				//Enable settings
				combobox_Display_Resolution().IsEnabled(true);
				combobox_Display_RefreshRate().IsEnabled(true);
				combobox_Display_Orientation().IsEnabled(true);
				button_Eyefinity_Manage().IsEnabled(true);
				button_Eyefinity_Enable().IsEnabled(true);
				button_Eyefinity_Disable().IsEnabled(true);

				//Disable settings
				toggleswitch_Eyefinity_Automatic().IsEnabled(false);
			}
			else
			{
				//Enable settings
				toggleswitch_Eyefinity_Automatic().IsEnabled(true);

				//Disable settings
				combobox_Display_Resolution().IsEnabled(false);
				combobox_Display_RefreshRate().IsEnabled(false);
				combobox_Display_Orientation().IsEnabled(false);
				toggleswitch_Display_HdrEnabled().IsEnabled(false);
				toggleswitch_Display_VSR().IsEnabled(false);
				toggleswitch_Display_GpuScaling().IsEnabled(false);
				toggleswitch_Display_IntegerScaling().IsEnabled(false);
				combobox_Display_ScalingMode().IsEnabled(false);
				toggleswitch_Display_VariBright().IsEnabled(false);
				combobox_Display_VariBright_Level().IsEnabled(false);
				combobox_Display_ColorDepth().IsEnabled(false);
				combobox_Display_PixelFormat().IsEnabled(false);
				toggleswitch_Display_HDCPSupport().IsEnabled(false);
				button_Eyefinity_Manage().IsEnabled(false);
				button_Eyefinity_Enable().IsEnabled(false);
				button_Eyefinity_Disable().IsEnabled(false);
			}

			//Update button colors
			//Fix check if current settings match profile and set button color accordingly
			SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
			button_Display_Apply().Background(colorValid);

			//Enable saving
			co_await AsyncTaskDelay(300, AppVariables::App.GetDispatcher());
			disable_saving = false;

			//Set result
			AVDebugWriteLine(L"ADLX loaded display values: " << deviceId << L" / " << application);
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading display values.");
		}
	}

	void MainPage::AdlxValuesLoadEyefinityDisplays()
	{
		try
		{
			//Fix automatically reload eyefinity when a display is connected or disconnected

			//Get all displays
			std::vector<ADLDisplayInfo> displayList = AdlGetDisplayAll();
			int displayCount = displayList.size();

			//Create item collection
			auto itemCollectionEyefinity = winrt::single_threaded_observable_vector<RadeonTuner::DisplayDetailsIdl>();

			//Add all displays
			for (const ADLDisplayInfo& displayInfo : displayList)
			{
				//Get display name
				std::wstring displayNameString = char_to_wstring(displayInfo.strDisplayName);

				//Get adapter and display index
				int displayAdapterIndex = displayInfo.displayID.iDisplayLogicalAdapterIndex;
				int displayDisplayIndex = displayInfo.displayID.iDisplayLogicalIndex;

				//Eyefinity displays list
				RadeonTuner::DisplayDetailsIdl displayDetails;
				displayDetails.IndexAdapter(displayAdapterIndex);
				displayDetails.IndexDisplay(displayDisplayIndex);
				displayDetails.Name(displayNameString);
				itemCollectionEyefinity.Append(displayDetails);

				//Set min and max rows and columns based on display count
				slider_Eyefinity_Rows().Minimum(1);
				slider_Eyefinity_Rows().Maximum(displayCount);
				slider_Eyefinity_Columns().Minimum(1);
				slider_Eyefinity_Columns().Maximum(displayCount);
			}

			//Set listview items source
			listview_EyefinityMonitorIndex().ItemsSource(itemCollectionEyefinity);

			//Set result
			AVDebugWriteLine("ADLX loaded eyefinity values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading eyefinity values.");
		}
	}
}