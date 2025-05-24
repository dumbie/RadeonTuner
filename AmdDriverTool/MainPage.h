#pragma once
#include "MainPage.g.h"

namespace winrt::AmdDriverTool::implementation
{
	struct MainPage : MainPageT<MainPage>
	{
		MainPage() {}
		void AdlxInitialize();
		void AdlxLoadValues();
		void AdlxUpdateLoop();

		void Page_Loaded(IInspectable const& sender, RoutedEventArgs const& e);
		void ClickHandler(IInspectable const& sender, RoutedEventArgs const& args);
		void toggleswitch_Chill_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void textBox_Chill_Min_TextChanged(IInspectable const& sender, TextChangedEventArgs const& e);
		void textBox_Chill_Max_TextChanged(IInspectable const& sender, TextChangedEventArgs const& e);
		void combobox_VerticalRefresh_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void listbox_Main_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
	};
}

namespace winrt::AmdDriverTool::factory_implementation
{
	struct MainPage : MainPageT<MainPage, implementation::MainPage>
	{
	};
}