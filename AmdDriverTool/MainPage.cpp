#pragma once
#include "pch.h"
#include "AppVariables.h"

#include "AdlxInitialize.h"
#include "AdlxChill.h"
#include "AdlxVerticalRefresh.h"

#include "MainPage.h"
#if __has_include("MainPage.g.cpp")
#include "MainPage.g.cpp"
#endif

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::Page_Loaded(IInspectable const& sender, RoutedEventArgs const& e)
	{
		//Initialize adlx
		AdlxInitialize();

		//Load adlx values
		AdlxLoadValues();

		//Start adlx update loop
		std::thread threadUpdateLoop(&MainPage::AdlxUpdateLoop, this);
		threadUpdateLoop.detach();

		//Fix bool is currently ignored
		disable_saving = false;
	}

	void MainPage::AdlxUpdateLoop()
	{
		while (true)
		{
			Sleep(1000);

			std::function<void()> updateFunction = [&]
				{
					OutputDebugString(L"Live update\n");
					textblock_Status().Text(L"Failed setting vertical refresh");
				};
			AppVariables::App.DispatcherInvoke(updateFunction);
		}
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
			stackpanel_Graphics().Visibility(Visibility::Visible);
		}
		else if (selectedIndex == 1)
		{
			stackpanel_Tuning().Visibility(Visibility::Visible);
		}
		else if (selectedIndex == 2)
		{
			stackpanel_Fans().Visibility(Visibility::Visible);
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

	void MainPage::ClickHandler(IInspectable const& sender, RoutedEventArgs const& e)
	{
	}
}