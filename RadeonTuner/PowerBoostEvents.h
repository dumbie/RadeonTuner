#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::fire_and_forget MainPage::button_PowerBoost_AddExe_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { co_return; }

			//Show application picker
			auto selectedApps = co_await AdlAppPickerAdd();
			int selectedAppsCount = selectedApps.Size();

			//Check selected items
			if (selectedAppsCount == 0)
			{
				ShowNotification(L"No applications selected");
				AVDebugWriteLine(L"No applications selected.");
				co_return;
			}

			//Add selected items
			int addCount = 0;
			for (auto const& app : selectedApps)
			{
				//Extract file name from path
				std::wstring fileName = hstring_to_wstring(app.ExeName());

				//Check double application
				if (array_contains(powerBoostAppsCache, fileName))
				{
					continue;
				}

				//Add application to list
				powerBoostAppsCache.push_back(fileName);
				addCount++;
			}

			//Check if applications were added
			if (addCount > 0)
			{
				//Save applications
				PowerBoost_Applications_SaveToFile();

				//List applications
				PowerBoost_Applications_List(true);
			}

			//Show notification
			//Fix show fail and duplicate count
			ShowNotification(L"Applications added: " + number_to_wstring(addCount) + L" / " + number_to_wstring(selectedAppsCount));
			AVDebugWriteLine(L"Applications added: " << addCount << L" / " << selectedAppsCount);
		}
		catch (...) {}
	}

	void MainPage::button_PowerBoost_Remove_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get selected index
			int selectedIndex = combobox_PowerBoost_Applications().SelectedIndex();

			//Remove application from list
			powerBoostAppsCache.erase(powerBoostAppsCache.begin() + selectedIndex);

			//Save applications
			PowerBoost_Applications_SaveToFile();

			//List applications
			PowerBoost_Applications_List(true);

			//Show notification
			ShowNotification(L"Application removed");
			AVDebugWriteLine(L"Application removed");
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_PowerBoost_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();

			//Update current value
			tuningFanSettingsCurrent.PowerBoost.Current = newValue;

			//Check if Power Boost is enabled
			if (newValue)
			{
				//Hide or show settings
				grid_Power_Limit_PB().Visibility(Visibility::Visible);
				grid_Power_Voltage_PB().Visibility(Visibility::Visible);
				grid_Power_TDC_PB().Visibility(Visibility::Visible);

				//Enable or disable settings
				combobox_PowerBoost_Applications().IsEnabled(true);
				button_PowerBoost_AddExe().IsEnabled(true);
				button_PowerBoost_Remove().IsEnabled(true);
			}
			else
			{
				//Hide or show settings
				grid_Power_Limit_PB().Visibility(Visibility::Collapsed);
				grid_Power_Voltage_PB().Visibility(Visibility::Collapsed);
				grid_Power_TDC_PB().Visibility(Visibility::Collapsed);

				//Enable or disable settings
				combobox_PowerBoost_Applications().IsEnabled(false);
				button_PowerBoost_AddExe().IsEnabled(false);
				button_PowerBoost_Remove().IsEnabled(false);
			}

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Tuning_Apply().Background(colorIgnored);
			button_Fan_Apply().Background(colorIgnored);
		}
		catch (...) {}
	}
}