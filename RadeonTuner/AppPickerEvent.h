#pragma once
#include "pch.h"
#include "MainPage.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::button_Overlay_AppPicker_Confirm_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Update variables
			appPickerCompleted = true;
		}
		catch (...) {}
	}

	void MainPage::button_Overlay_AppPicker_Cancel_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Update variables
			appPickerCancel = true;
		}
		catch (...) {}
	}

	void MainPage::listview_Overlay_AppPicker_ItemClick(IInspectable const& sender, ItemClickEventArgs const& e)
	{
		try
		{
			//Update variables
			appPickerSelected = true;
		}
		catch (...) {}
	}
}