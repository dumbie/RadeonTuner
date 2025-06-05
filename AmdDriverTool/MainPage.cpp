#pragma once
#include "pch.h"
#include "AppVariables.h"

#include "AdlxInitialize.h"
#include "AdlxInfoLoad.h"
#include "AdlxValuesLoad.h"
#include "AdlxValuesPrepare.h"
#include "AdlxValuesApply.h"
#include "AdlxValuesExport.h"
#include "AdlxValuesImport.h"
#include "AdlxValuesReset.h"
#include "AdlxUpdateLoop.h"

#include "AdlxEventsDisplay.h"
#include "AdlxEventsFans.h"
#include "AdlxEventsGraphics.h"

#include "MainPage.h"
#if __has_include("MainPage.g.cpp")
#include "MainPage.g.cpp"
#endif

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::page_Loaded(IInspectable const& sender, RoutedEventArgs const& e)
	{
		//Select default indexes
		listbox_Main().SelectedIndex(0);

		//Initialize adlx
		AdlxInitialize();

		//Prepare adlx values
		AdlxValuesPrepare();

		//Load adlx values
		AdlxValuesLoad();

		//Load adlx info
		AdlxInfoLoad();

		//Start adlx update loop
		std::thread threadUpdateLoop(&MainPage::AdlxUpdateLoop, this);
		threadUpdateLoop.detach();
	}

	void MainPage::listbox_Main_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		//Get selected index
		auto selectedIndex = sender.as<ListBox>().SelectedIndex();

		//Hide all pages
		stackpanel_Graphics().Visibility(Visibility::Collapsed);
		stackpanel_Tuning().Visibility(Visibility::Collapsed);
		stackpanel_Fans().Visibility(Visibility::Collapsed);
		stackpanel_Display().Visibility(Visibility::Collapsed);
		stackpanel_Info().Visibility(Visibility::Collapsed);

		//Make selected page visible
		if (selectedIndex == 0)
		{
			stackpanel_Tuning().Visibility(Visibility::Visible);
		}
		else if (selectedIndex == 1)
		{
			stackpanel_Fans().Visibility(Visibility::Visible);
		}
		else if (selectedIndex == 2)
		{
			stackpanel_Graphics().Visibility(Visibility::Visible);
		}
		else if (selectedIndex == 3)
		{
			stackpanel_Display().Visibility(Visibility::Visible);
		}
		else if (selectedIndex == 4)
		{
			stackpanel_Info().Visibility(Visibility::Visible);
		}
	}

	void MainPage::button_Apply_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		adlx_Bool = AdlxValuesApply();
		if (adlx_Bool)
		{
			AdlxValuesLoad();
		}
	}

	void MainPage::button_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		AdlxValuesReset();
		AdlxValuesLoad();
	}

	void MainPage::button_Import_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		AdlxValuesImport();
	}

	void MainPage::button_Export_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		AdlxValuesExport();
	}

	void MainPage::slider_Fan_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		ValidateFanSettings();
		UpdateFanGraph();
	}
}