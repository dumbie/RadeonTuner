#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::button_Tuning_Keep_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Toggle keep active on or off
			KeepActive_Toggle();
		}
		catch (...) {}
	}
}