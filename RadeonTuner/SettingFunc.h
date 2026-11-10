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

	void MainPage::LaunchDriverCleanup()
	{
		try
		{
			//Get path to AMD Cleanup Utility
			std::wstring pathProgramFiles = PathGetFolderKnown(FOLDERID_ProgramFiles);
			std::wstring pathCleanUtility = PathMerge(pathProgramFiles, L"AMD\\CIM\\Bin64\\AMDCleanupUtility.exe");

			//Check if AMD Cleanup Utility exists
			if (FileExists(pathCleanUtility))
			{
				//Launch AMD Cleanup Utility
				AVProcesses::Launch_ApplicationDesktop(pathCleanUtility, L"", L"", false);
			}
			else
			{
				ShowNotification(L"AMD Cleanup Utility has not been found");
				AVDebugWriteLine("No soup for you! AMD Cleanup Utility has not been found.");
			}
		}
		catch (...) {}
	}

	void MainPage::ToggleRadeonServices(bool disableServices)
	{
		try
		{
			//Note: Disabling services when you still use RadeonSoftware can cause heavy stuttering, for example when AFMF is enabled because it keeps trying to enable the setting over and over but fails.
			//Note: Disabling services will break graphic features like AFMF and Radeon Boost.
			//Fix check if event service is disabled and set graphics settings effected support to false.

			//Ignore Chipset services 
			//AMD 3D V-Cache Performance Optimizer Service 
			//AMD Application Compatibility Database Service 
			//AMD Provisioning Packages Service 

			//Toggle Radeon services
			int disableCount = 0;
			if (WindowsServiceDisableEnable(L"AMD External Events Utility", disableServices)) { disableCount++; }
			if (WindowsServiceDisableEnable(L"AMD Crash Defender Service", disableServices)) { disableCount++; }

			//Stop Radeon services
			WindowsServiceStartStop(L"AMD External Events Utility", disableServices);
			WindowsServiceStartStop(L"AMD Crash Defender Service", disableServices);

			//Show result
			if (disableServices)
			{
				AVDebugWriteLine(L"Disabled Radeon services: " << disableCount);
				ShowNotification(L"Disabled Radeon services (" + number_to_wstring(disableCount) + L")");
			}
			else
			{
				AVDebugWriteLine(L"Enabled Radeon services: " << disableCount);
				ShowNotification(L"Enabled Radeon services (" + number_to_wstring(disableCount) + L")");
			}
		}
		catch (...) {}
	}

	winrt::IAsyncAction MainPage::button_Update_Check_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			AVDebugWriteLine("Checking for application update.");

			UpdateCheckResult updateCheckResult = UpdateCheck(AppVariables::hInstance, "dumbie", "RadeonTuner");
			if (updateCheckResult.UpdateFound)
			{
				//Set update version
				vUpdateVersion = updateCheckResult.UpdateVersion;

				//Show messagebox
				int messageResult = co_await ShowMessageBox(L"New update available", L"Would you like to update the application to " + vUpdateVersion + L"?", { L"Yes", L"No" });

				//Check messagebox result
				if (messageResult == 0)
				{
					//Launch updater and restart application
					UpdateRestart();
				}
			}
			else
			{
				co_await ShowMessageBox(L"Update check", L"No new application update has been found.", { L"Ok" });
			}
		}
		catch (...) {}
	}

	winrt::IAsyncAction MainPage::button_Update_Launch_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Show messagebox
			int messageResult = co_await ShowMessageBox(L"New update available", L"Would you like to update the application to " + vUpdateVersion + L"?", { L"Yes", L"No" });

			//Check messagebox result
			if (messageResult == 0)
			{
				//Launch updater and restart application
				UpdateRestart();
			}
		}
		catch (...) {}
	}
}