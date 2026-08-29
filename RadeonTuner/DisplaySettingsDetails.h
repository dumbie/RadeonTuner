#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::fire_and_forget MainPage::DisplayList_SelectCurrent_Values(bool waitUpdate)
	{
		try
		{
			//Wait for resolutions to have updated
			if (waitUpdate)
			{
				co_await AsyncTaskDelay(500, AppVariables::App.GetDispatcher());
			}

			//Get current display mode
			int numModes = -1;
			ADLMode* adlModeCurrent{};
			adl_Res0 = _ADL2_Display_Modes_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &numModes, &adlModeCurrent);
			if (adl_Res0 != ADL_OK)
			{
				AVDebugWriteLine(L"Failed getting current display mode.");
				co_return;
			}

			//AVDebugWriteLine(L"Selecting display modes: " << adlModeCurrent->iXRes << L"x" << adlModeCurrent->iYRes << L" / " << adlModeCurrent->fRefreshRate << L" Hz / Orientation: " << adlModeCurrent->iOrientation);

			//Update current modes text
			//Fix when changing resolution text is not updated because nothing triggers this
			//textblock_Display_Resolution_Value().Text(number_to_wstring(adlModeCurrent->iXRes) + L"x" + number_to_wstring(adlModeCurrent->iYRes));
			//textblock_Display_RefreshRate_Value().Text(float_to_wstring(adlModeCurrent->fRefreshRate, 2) + L" Hz");
			//textblock_Display_Orientation_Value().Text(number_to_wstring(adlModeCurrent->iOrientation) + L"°");

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

	winrt::fire_and_forget MainPage::DisplayList_Resolution(bool waitUpdate)
	{
		try
		{
			//Wait for resolutions to have updated
			if (waitUpdate)
			{
				co_await AsyncTaskDelay(500, AppVariables::App.GetDispatcher());
			}

			//Create item collection
			auto itemCollection = winrt::single_threaded_observable_vector<RadeonTuner::DisplayDetailsIdl>();

			//Add resolutions to item collection
			ADLMode* lppModes;
			int lpNumModes = -1;
			adl_Res0 = _ADL2_Display_PossibleMode_Get(adl_Context, adl_Display_AdapterIndex, &lpNumModes, &lppModes);

			//Sort resolutions
			std::sort(lppModes, lppModes + lpNumModes, [](const ADLMode& a, const ADLMode& b) { return a.iXRes > b.iXRes; });

			//Append resolutions
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

			//Show result
			AVDebugWriteLine(L"Loaded display resolution values");
		}
		catch (...) {}
	}

	winrt::fire_and_forget MainPage::DisplayList_RefreshRate(bool waitUpdate)
	{
		try
		{
			//Wait for refresh rates to have updated
			if (waitUpdate)
			{
				co_await AsyncTaskDelay(500, AppVariables::App.GetDispatcher());
			}

			//Create item collection
			auto itemCollection = winrt::single_threaded_observable_vector<RadeonTuner::DisplayDetailsIdl>();

			//Add resolutions to item collection
			ADLMode* lppModes;
			int lpNumModes = -1;
			adl_Res0 = _ADL2_Display_PossibleMode_Get(adl_Context, adl_Display_AdapterIndex, &lpNumModes, &lppModes);

			//Sort refresh rates
			std::sort(lppModes, lppModes + lpNumModes, [](const ADLMode& a, const ADLMode& b) { return a.fRefreshRate > b.fRefreshRate; });

			//Append refresh rates
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

			//Set combobox items source
			combobox_Display_RefreshRate().ItemsSource(itemCollection);

			//Show result
			AVDebugWriteLine(L"Loaded display refresh rate values");
		}
		catch (...) {}
	}
}