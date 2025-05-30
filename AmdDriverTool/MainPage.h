#pragma once
#include "MainPage.g.h"

namespace winrt::AmdDriverTool::implementation
{
	struct MainPage : MainPageT<MainPage>
	{
		MainPage() {}
		void AdlxInitialize();
		void AdlxLoadValues();
		void AdlxValuesApply();
		void AdlxValuesExport();
		void AdlxValuesImport();
		void AdlxValuesReset();
		void AdlxLoadInfo();
		void AdlxUpdateLoop();

		void page_Loaded(IInspectable const& sender, RoutedEventArgs const& e);
		void listbox_Main_SelectionChanged(IInspectable const& sender, Controls::SelectionChangedEventArgs const& e);
		void button_Apply_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Import_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Export_Click(IInspectable const& sender, RoutedEventArgs const& e);

		void combobox_VerticalRefresh_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void toggleswitch_RadeonChill_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void slider_RadeonChill_Min_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_RadeonChill_Max_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
	};
}

namespace winrt::AmdDriverTool::factory_implementation
{
	struct MainPage : MainPageT<MainPage, implementation::MainPage>
	{
	};
}