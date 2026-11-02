#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AppVariables.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxLoopDisplayApplyProfile(int adapterIndex, int displayIndex, DisplaySettings displaySettingsRunning)
	{
		try
		{
			//Check if apply is required
			if (displaySettingsRunning.UsingProfile)
			{
				//AVDebugWriteLine(L"Profile is currently in use: " << displaySettingsRunning.Application.value());
				return;
			}

			//Get current and default settings
			DisplaySettings displaySettingsAdl = DisplaySettings_Generate_FromADL(adapterIndex, displayIndex, L"", false).value();

			//Apply display settings
			bool applyResult = AdlDisplaySettingsApply(adapterIndex, displayIndex, displaySettingsRunning, displaySettingsAdl, AdlSettingGet::Current, true);

			//Check result
			if (applyResult)
			{
				//Update application using status
				DisplaySettings_Profile_Set_Using(displaySettingsRunning.DeviceId.value(), displaySettingsRunning.Application.value());
			}

			std::function<winrt::IAsyncAction()> updateFunction = [=]() -> winrt::IAsyncAction
				{
					if (applyResult)
					{
						//Show notification
						ShowNotification(L"Display settings applied: " + displaySettingsRunning.Application.value());
						AVDebugWriteLine(L"Display settings applied: " << displaySettingsRunning.Application.value());

						//Load display settings
						co_await AdlxValuesLoadSelectDisplayApp(adl_Display_AdapterIndex, adl_Display_DisplayIndex, displaySettingsProfile.Application.value());
					}
				};
			AppVariables::App.DispatcherInvoke(updateFunction);
		}
		catch (...) {}
	}
}