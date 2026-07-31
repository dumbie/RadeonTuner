#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::fire_and_forget MainPage::AdlxValuesLoadSelectDisplay(ADLDisplayInfo displayInfo)
	{
		try
		{
			//Disable saving
			disable_saving = true;

			//Get adapter and display index
			adl_Display_AdapterIndex = displayInfo.displayID.iDisplayLogicalAdapterIndex;
			adl_Display_DisplayIndex = displayInfo.displayID.iDisplayLogicalIndex;
			AVDebugWriteLine("Selected display index: A" << adl_Display_AdapterIndex << " / D" << adl_Display_DisplayIndex);

			//Update button text
			textblock_DisplaySelect().Text(char_to_wstring(displayInfo.strDisplayName));

			//Load display settings
			AdlxValuesLoadDisplay();

			//Load eyefinity settings
			AdlxValuesLoadEyefinity();

			//Load information
			AdlxInfoLoad();

			//Enable saving
			co_await AsyncTaskDelay(300, AppVariables::App.GetDispatcher());
			disable_saving = false;

			//Set result
			AVDebugWriteLine("Loaded selected display values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed loading selected display values (Exception)");
		}
	}

	void MainPage::AdlxValuesLoadDisplay()
	{
		try
		{
			//Get current and default settings
			displaySettingsCurrent = DisplaySettings_Generate_FromADL(adl_Display_AdapterIndex, adl_Display_DisplayIndex).value();

			//Convert settings values to interface
			DisplaySettings_Convert_ToUI_Adl(displaySettingsCurrent);

			//Load display resolution values
			DisplayList_Resolution(false);

			//Load display refresh rate values
			DisplayList_RefreshRate();

			//Select current display values
			DisplayList_SelectCurrent_Values();

			//Set result
			AVDebugWriteLine("ADLX loaded display values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading display values.");
		}
	}

	void MainPage::AdlxValuesLoadEyefinity()
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