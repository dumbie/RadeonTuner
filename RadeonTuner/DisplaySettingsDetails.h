#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::DisplayList_SelectCurrent()
	{
		try
		{
			//Get current display mode
			int numModes = -1;
			ADLMode* adlModeCurrent{};
			adl_Res0 = _ADL2_Display_Modes_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &numModes, &adlModeCurrent);
			if (adl_Res0 != ADL_OK)
			{
				AVDebugWriteLine(L"Failed getting current display mode.");
				return;
			}

			//Select display resolution
			for (int i = 0; i < combobox_Display_Resolution().Items().Size(); i++)
			{
				auto item = combobox_Display_Resolution().Items().GetAt(i).as<RadeonTuner::DisplayDetailsIdl>();
				if (item.ResolutionWidth() == adlModeCurrent->iXRes && item.ResolutionHeight() == adlModeCurrent->iYRes)
				{
					combobox_Display_Resolution().SelectedIndex(i);
					break;
				}
			}

			//Select display refresh rate
			for (int i = 0; i < combobox_Display_RefreshRate().Items().Size(); i++)
			{
				auto item = combobox_Display_RefreshRate().Items().GetAt(i).as<RadeonTuner::DisplayDetailsIdl>();
				if (item.RefreshRate() == adlModeCurrent->fRefreshRate)
				{
					combobox_Display_RefreshRate().SelectedIndex(i);
					break;
				}
			}

			//Select display orientation
			//Enumeration index correction
			switch (adlModeCurrent->iOrientation)
			{
			case 0:
				combobox_Display_Orientation().SelectedIndex(0);
				break;
			case 90:
				combobox_Display_Orientation().SelectedIndex(1);
				break;
			case 180:
				combobox_Display_Orientation().SelectedIndex(2);
				break;
			case 270:
				combobox_Display_Orientation().SelectedIndex(3);
				break;
			}
		}
		catch (...) {}
	}

	void MainPage::DisplayList_Resolution()
	{
		try
		{
			//Fix reload list when virtual super resolution is enabled or disabled

			//Create item collection
			auto itemCollection = winrt::single_threaded_observable_vector<RadeonTuner::DisplayDetailsIdl>();

			//Add resolutions to item collection
			ADLMode* lppModes;
			int lpNumModes = -1;
			adl_Res0 = _ADL2_Display_PossibleMode_Get(adl_Context, adl_Display_AdapterIndex, &lpNumModes, &lppModes);
			for (int i = 0; i < lpNumModes; i++)
			{
				ADLMode adlMode = lppModes[i];
				RadeonTuner::DisplayDetailsIdl displayDetails;
				displayDetails.Name(number_to_wstring(adlMode.iXRes) + L"x" + number_to_wstring(adlMode.iYRes));
				displayDetails.ResolutionWidth(adlMode.iXRes);
				displayDetails.ResolutionHeight(adlMode.iYRes);

				//Check if value already exists in item collection
				bool alreadyExists = std::ranges::any_of(itemCollection,
					[&](const auto& item)
					{
						return item.ResolutionWidth() == displayDetails.ResolutionWidth() && item.ResolutionHeight() == displayDetails.ResolutionHeight();
					});
				if (!alreadyExists)
				{
					itemCollection.Append(displayDetails);
				}
			}

			//Set combobox items source
			combobox_Display_Resolution().ItemsSource(itemCollection);
		}
		catch (...) {}
	}

	void MainPage::DisplayList_RefreshRate()
	{
		try
		{
			//Fix refresh rates returned by ADL2 are rounded down for example 59.94 is returned as 59.00

			//Create item collection
			auto itemCollection = winrt::single_threaded_observable_vector<RadeonTuner::DisplayDetailsIdl>();

			//Add resolutions to item collection
			ADLMode* lppModes;
			int lpNumModes = -1;
			adl_Res0 = _ADL2_Display_PossibleMode_Get(adl_Context, adl_Display_AdapterIndex, &lpNumModes, &lppModes);
			for (int i = 0; i < lpNumModes; i++)
			{
				ADLMode adlMode = lppModes[i];
				RadeonTuner::DisplayDetailsIdl displayDetails;
				displayDetails.Name(float_to_wstring(adlMode.fRefreshRate, 2) + L" Hz");
				displayDetails.RefreshRate(adlMode.fRefreshRate);

				//Check if value already exists in item collection
				bool alreadyExists = std::ranges::any_of(itemCollection,
					[&](const auto& item)
					{
						return item.RefreshRate() == displayDetails.RefreshRate();
					});
				if (!alreadyExists)
				{
					itemCollection.Append(displayDetails);
				}
			}

			//Fix Sort refresh rates

			//Set combobox items source
			combobox_Display_RefreshRate().ItemsSource(itemCollection);
		}
		catch (...) {}
	}
}