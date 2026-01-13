#pragma once
#include "pch.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::button_Website_Project_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			ShellExecuteW(0, 0, L"https://projects.arnoldvink.com", 0, 0, 0);
		}
		catch (...) {}
	}

	void MainPage::button_Website_Donation_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			ShellExecuteW(0, 0, L"https://donation.arnoldvink.com", 0, 0, 0);
		}
		catch (...) {}
	}

	void MainPage::button_Fps_Overlayer_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			ShellExecuteW(0, 0, L"https://github.com/dumbie/FpsOverlayer", 0, 0, 0);
		}
		catch (...) {}
	}

	void MainPage::button_Check_Update_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			AVDebugWriteLine("Checking for application update.");

			//Get available version
			std::string availableVersion = GitHub::GetLatestVersion("dumbie", "RadeonTuner");

			//Get current version
			std::string currentVersion = "v" + GetVersionFromResource(AppVariables::hInstance);

			//Check if version matches
			if (!availableVersion.empty() && currentVersion != availableVersion)
			{
				int messageResult = MessageBoxW(NULL, L"Newer version has been found, would you like to update the application to the newest version available?", L"RadeonTuner", MB_YESNO);
				if (messageResult == IDYES)
				{
					//ShellExecuteW(0, 0, L"https://github.com/dumbie/RadeonTuner/releases", 0, 0, 0);
					std::wstring pathUpdaterExeW = PathMerge(PathGetExecutableDirectory(), L"Updater.exe");
					Launch_ShellExecute(pathUpdaterExeW, L"", L"", true);
				}
			}
			else
			{
				MessageBoxW(NULL, L"No new application update has been found.", L"RadeonTuner", MB_OK);
			}
		}
		catch (...)
		{
			MessageBoxW(NULL, L"Failed checking for application update.", L"RadeonTuner", MB_OK);
		}
	}
}