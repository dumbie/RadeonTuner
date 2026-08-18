#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AppVariables.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	//Fix: Change display and tuning check to event that triggers on process launch and close or check foreground window switch.
	//Fix: Add support to manually enable RIS2 desktop when it used in an application profile.
	//Fix: Make sure Gamma RGB is set to currently used value, changing resolution etc resets it.

	void MainPage::AdlxLoopKeepActive()
	{
		while (true)
		{
			try
			{
				//Delay next loop
				if (!AppVariables::LaunchKeepActive)
				{
					Sleep(10000);
				}
				else
				{
					Sleep(2000);
					AppVariables::LaunchKeepActive = false;
				}

				//Check if loop is allowed
				if (AppVariables::ApplicationExiting)
				{
					return;
				}

				//Get running processes
				std::vector<std::wstring> processExeRunning{};
				std::vector<AVProcess> processAll = Get_ProcessAll();
				for (AVProcess& process : processAll)
				{
					//Lower case executable name
					std::wstring exeNameLower = wstring_to_lower(process.ExeName());

					//Add to list of running processes
					processExeRunning.push_back(exeNameLower);
				}

				//Check display automatic eyefinity
				AdlxCheckDisplayEyefinityAutomatic(processExeRunning);

				//Check display application profile
				AdlxCheckDisplayApplicationProfile(processExeRunning);

				//Check tuning application profile
				AdlxCheckTuningApplicationProfile(processExeRunning);
			}
			catch (...) {}
		}
	}
}