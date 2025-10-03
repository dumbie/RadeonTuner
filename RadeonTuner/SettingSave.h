#pragma once
#include "pch.h"
#include "MainPage.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::toggleswitch_ActiveOverclock_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				AppVariables::Settings.Set("ActiveOverclock", true);

				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				button_Fan_Keep().Background(colorValid);
				button_Tuning_Keep().Background(colorValid);
			}
			else
			{
				AppVariables::Settings.Set("ActiveOverclock", false);

				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				button_Fan_Keep().Background(colorInvalid);
				button_Tuning_Keep().Background(colorInvalid);
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_Window_Top_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				AppVariables::Settings.Set("SetTopMost", true);
				AppVariables::App.SetTopMost(true);
				textblock_Status().Text(L"Set window on top");
				AVDebugWriteLine(L"Set window on top");
			}
			else
			{
				AppVariables::Settings.Set("SetTopMost", false);
				AppVariables::App.SetTopMost(false);
				textblock_Status().Text(L"Set window not on top");
				AVDebugWriteLine(L"Set window not on top");
			}
		}
		catch (...) {}
	}
}