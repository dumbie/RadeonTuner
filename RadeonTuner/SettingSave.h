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
			}
			else
			{
				AppVariables::Settings.Set("ActiveOverclock", false);
			}
		}
		catch (...) {}
	}

	void MainPage::button_ActiveOverclockFileSelect_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Select settings file
			wchar_t lpstrFileName[MAX_PATH] = {};
			OPENFILENAMEW openFileName = {};
			openFileName.lStructSize = sizeof(openFileName);
			openFileName.lpstrTitle = L"Select tuning and fans settings...";
			openFileName.lpstrFilter = L"Setting files (radt)\0*.radt\0";
			openFileName.lpstrFile = lpstrFileName;
			openFileName.nMaxFile = MAX_PATH;
			openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			if (!GetOpenFileNameW(&openFileName))
			{
				return;
			}

			//Save settings
			AppVariables::Settings.Set("ActiveOverclockFile", lpstrFileName);

			//Update text
			textblock_ActiveOverclockFile().Text(lpstrFileName);
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