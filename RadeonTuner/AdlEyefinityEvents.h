#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::button_Eyefinity_Manage_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			bool manageVisible = grid_Overlay_ManageEyefinity().Visibility() == Visibility::Visible;
			if (manageVisible)
			{
				//Hide Eyefinity manage overlay
				grid_Overlay_ManageEyefinity().Visibility(Visibility::Collapsed);
				AVDebugWriteLine(L"Closed Eyefinity manage overlay");
			}
			else
			{
				//Fix load current Eyefinity settings

				//Load Eyefinity displays
				AdlxValuesLoadEyefinityDisplays();

				//Show Eyefinity manage overlay
				grid_Overlay_ManageEyefinity().Visibility(Visibility::Visible);
				AVDebugWriteLine(L"Opened Eyefinity manage overlay");
			}
		}
		catch (...) {}
	}

	void MainPage::button_Eyefinity_Overlay_Remove_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Disable automatic eyefinity loop
			disable_eyefinity_automatic = true;

			//Delete all Eyefinity configurations
			if (Adl_Eyefinity_Delete_All(adl_Display_AdapterIndex))
			{
				ShowNotification(L"Removed Eyefinity");
				AVDebugWriteLine(L"Removed Eyefinity");

				//Fix Reload display resolution
				//disable_saving = true;
				//DisplayList_Combined(true);
				//disable_saving = false;
			}
			else
			{
				ShowNotification(L"Failed removing Eyefinity");
				AVDebugWriteLine(L"Failed removing Eyefinity");
			}

			//Enable automatic eyefinity loop
			disable_eyefinity_automatic = false;
		}
		catch (...) {}
	}

	void MainPage::button_Eyefinity_Overlay_Create_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Disable automatic eyefinity loop
			disable_eyefinity_automatic = true;

			//Create custom eyefinity
			if (Adl_Eyefinity_Create_Custom(adl_Display_AdapterIndex))
			{
				ShowNotification(L"Created Eyefinity");
				AVDebugWriteLine(L"Created Eyefinity");

				//Fix Reload display resolution
				//disable_saving = true;
				//DisplayList_Combined(true);
				//disable_saving = false;
			}
			else
			{
				ShowNotification(L"Failed creating Eyefinity");
				AVDebugWriteLine(L"Failed creating Eyefinity");
			}

			//Enable automatic eyefinity loop
			disable_eyefinity_automatic = false;
		}
		catch (...) {}
	}

	void MainPage::button_Eyefinity_Enable_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Disable automatic eyefinity loop
			disable_eyefinity_automatic = true;

			//Enable Eyefinity
			AdlCustomResult eyefinityResult = Adl_Eyefinity_Toggle(adl_Display_AdapterIndex, true);
			if (eyefinityResult == AdlCustomResult::CUSTOM_OK)
			{
				ShowNotification(L"Enabled Eyefinity");
				AVDebugWriteLine(L"Enabled Eyefinity");

				//Fix Reload display resolution
				//disable_saving = true;
				//DisplayList_Combined(true);
				//disable_saving = false;
			}
			else if (eyefinityResult == AdlCustomResult::CUSTOM_ALREADY)
			{
				ShowNotification(L"Eyefinity already enabled");
				AVDebugWriteLine(L"Eyefinity already enabled");
			}
			else
			{
				ShowNotification(L"Failed enabling Eyefinity");
				AVDebugWriteLine(L"Failed enabling Eyefinity");
			}

			//Enable automatic eyefinity loop
			disable_eyefinity_automatic = false;
		}
		catch (...) {}
	}

	void MainPage::button_Eyefinity_Disable_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Disable automatic eyefinity loop
			disable_eyefinity_automatic = true;

			//Disable Eyefinity
			AdlCustomResult eyefinityResult = Adl_Eyefinity_Toggle(adl_Display_AdapterIndex, false);
			if (eyefinityResult == AdlCustomResult::CUSTOM_OK)
			{
				ShowNotification(L"Disabled Eyefinity");
				AVDebugWriteLine(L"Disabled Eyefinity");

				//Fix Reload display resolution
				//disable_saving = true;
				//DisplayList_Combined(true);
				//disable_saving = false;
			}
			else if (eyefinityResult == AdlCustomResult::CUSTOM_ALREADY)
			{
				ShowNotification(L"Eyefinity already disabled");
				AVDebugWriteLine(L"Eyefinity already disabled");
			}
			else
			{
				ShowNotification(L"Failed disabling Eyefinity");
				AVDebugWriteLine(L"Failed disabling Eyefinity");
			}

			//Enable automatic eyefinity loop
			disable_eyefinity_automatic = false;
		}
		catch (...) {}
	}
}