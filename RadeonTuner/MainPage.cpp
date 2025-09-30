#pragma once
#include "pch.h"
#include "AppVariables.h"

#include "AdlInitialize.h"
#include "AdlValuesPrepare.h"

#include "AdlxInitialize.h"
#include "AdlxInfoLoad.h"
#include "AdlxUpdateLoop.h"

#include "AdlxValuesLoadSelect.h"
#include "AdlxValuesPrepare.h"
#include "AdlxValuesExport.h"
#include "AdlxValuesImport.h"

#include "AdlxResetDisplay.h"
#include "AdlxResetGraphics.h"
#include "AdlxResetTuning.h"

#include "AdlxEventsDisplay.h"
#include "AdlxEventsFans.h"
#include "AdlxEventsGraphics.h"
#include "AdlxEventsMultimedia.h"
#include "AdlxEventsPower.h"
#include "AdlxEventsTuning.h"

#include "SettingCheck.h"
#include "SettingSave.h"
#include "SettingLoad.h"

#include "MainPage.h"
#if __has_include("MainPage.g.cpp")
#include "MainPage.g.cpp"
#endif

namespace winrt::RadeonTuner::implementation
{
	void MainPage::page_Loaded(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			////Initialize adl
			//std::wstring initResult_Adl = AdlInitialize();
			//if (!initResult_Adl.empty())
			//{
			//	grid_Main().IsHitTestVisible(false);
			//	grid_Overlay().Visibility(Visibility::Visible);
			//	textblock_Overlay_Text().Text(L"Failed initializing ADL, please install or update your AMD drivers.");
			//	textblock_Overlay_Sub_Text().Text(L"If this message keeps appearing try using the AMD Cleanup Utility.\n\n" + initResult_Adl);
			//	return;
			//}

			//Initialize adlx
			std::wstring initResult_Adlx = AdlxInitialize();
			if (!initResult_Adlx.empty())
			{
				grid_Main().IsHitTestVisible(false);
				grid_Overlay().Visibility(Visibility::Visible);
				textblock_Overlay_Text().Text(L"Failed initializing ADLX, please install or update your AMD drivers.");
				textblock_Overlay_Sub_Text().Text(L"If this message keeps appearing try using the AMD Cleanup Utility.\n\n" + initResult_Adlx);
				return;
			}

			//Prepare adlx values
			AdlxValuesPrepare();

			//Prepare adl values
			//AdlValuesPrepare();

			//Check settings
			SettingCheck();

			//Load settings
			SettingLoad();

			//Load other values
			AdlxValuesLoadSelectOther();

			//Select default indexes
			listbox_Main().SelectedIndex(0);
			combobox_GpuSelect().SelectedIndex(0);
			combobox_DisplaySelect().SelectedIndex(0);
			combobox_AppSelect().SelectedIndex(0);

			//Start adlx update loop
			std::thread threadUpdateLoop(&MainPage::AdlxUpdateLoop, this);
			threadUpdateLoop.detach();
		}
		catch (...) {}
	}

	void MainPage::listbox_Main_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Get selected index
			auto selectedIndex = sender.as<ListBox>().SelectedIndex();

			//Hide all pages
			stackpanel_Graphics().Visibility(Visibility::Collapsed);
			stackpanel_Tuning().Visibility(Visibility::Collapsed);
			stackpanel_Fans().Visibility(Visibility::Collapsed);
			stackpanel_Power().Visibility(Visibility::Collapsed);
			stackpanel_Display().Visibility(Visibility::Collapsed);
			stackpanel_Multimedia().Visibility(Visibility::Collapsed);
			stackpanel_Settings().Visibility(Visibility::Collapsed);
			stackpanel_Information().Visibility(Visibility::Collapsed);

			//Disable selection boxes
			combobox_GpuSelect().IsEnabled(false);
			combobox_DisplaySelect().IsEnabled(false);
			combobox_AppSelect().IsEnabled(false);

			//Make selected page visible
			if (selectedIndex == 0)
			{
				combobox_GpuSelect().IsEnabled(true);
				stackpanel_Tuning().Visibility(Visibility::Visible);
			}
			else if (selectedIndex == 1)
			{
				combobox_GpuSelect().IsEnabled(true);
				stackpanel_Fans().Visibility(Visibility::Visible);
			}
			else if (selectedIndex == 2)
			{
				stackpanel_Power().Visibility(Visibility::Visible);
			}
			else if (selectedIndex == 3)
			{
				combobox_AppSelect().IsEnabled(true);
				combobox_GpuSelect().IsEnabled(true);
				stackpanel_Graphics().Visibility(Visibility::Visible);
			}
			else if (selectedIndex == 4)
			{
				combobox_DisplaySelect().IsEnabled(true);
				stackpanel_Display().Visibility(Visibility::Visible);
			}
			else if (selectedIndex == 5)
			{
				combobox_GpuSelect().IsEnabled(true);
				stackpanel_Multimedia().Visibility(Visibility::Visible);
			}
			else if (selectedIndex == 6)
			{
				stackpanel_Settings().Visibility(Visibility::Visible);
			}
			else if (selectedIndex == 7)
			{
				combobox_GpuSelect().IsEnabled(true);
				stackpanel_Information().Visibility(Visibility::Visible);
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_GpuSelect_SelectionChanged(IInspectable const& sender, Controls::SelectionChangedEventArgs const& e)
	{
		try
		{
			//Load adlx values
			AdlxValuesLoadSelectGpu();
		}
		catch (...) {}
	}

	void MainPage::combobox_DisplaySelect_SelectionChanged(IInspectable const& sender, Controls::SelectionChangedEventArgs const& e)
	{
		try
		{
			//Load adlx values
			AdlxValuesLoadSelectDisplay();
		}
		catch (...) {}
	}

	void MainPage::combobox_AppSelect_SelectionChanged(IInspectable const& sender, Controls::SelectionChangedEventArgs const& e)
	{
		try
		{
			//Load adlx values
			AdlxValuesLoadSelectApp();
		}
		catch (...) {}
	}
}