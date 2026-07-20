#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	std::wstring MainPage::AdlxValuesLoadDisplayList(bool selectFirst)
	{
		try
		{
			//Get combobox items
			auto itemCollectionSelect = combobox_DisplaySelect().Items();
			auto itemCollectionEyefinity = winrt::single_threaded_observable_vector<RadeonTuner::DisplayDetailsIdl>();

			//Clear combobox items
			itemCollectionSelect.Clear();

			//Get all displays
			adl_List_Displays = AdlGetDisplayAll();
			int displayCount = adl_List_Displays.size();

			//Add all displays
			for (const ADLDisplayInfo& displayInfo : adl_List_Displays)
			{
				//Get display name
				std::wstring displayNameString = char_to_wstring(displayInfo.strDisplayName);

				//Add display to combobox
				itemCollectionSelect.Append(box_value(displayNameString));

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
			listview_EyefinityMonitorIndex().ItemsSource(itemCollectionEyefinity);

			//Select first index
			if (selectFirst)
			{
				combobox_DisplaySelect().SelectedIndex(0);
			}

			//Set result
			AVDebugWriteLine("Listed all displays: " << displayCount);
			if (displayCount == 0)
			{
				return L"Failed to find any displays.";
			}
			else
			{
				return L"";
			}
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading display list.");
			return L"Failed loading display list.";
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
}