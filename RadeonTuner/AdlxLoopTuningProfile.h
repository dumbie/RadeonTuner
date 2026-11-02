#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AppVariables.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxLoopTuningApplyProfile(int adapterIndex, TuningFanSettings tuningFanSettingsRunning)
	{
		try
		{
			//Check if keep active is enabled
			bool keepActiveEnabled = false;
			if (tuningFanSettingsRunning.KeepActive.Current.has_value())
			{
				keepActiveEnabled = tuningFanSettingsRunning.KeepActive.Current.value();
			}

			//Check if apply is required
			if (tuningFanSettingsRunning.UsingProfile && !keepActiveEnabled)
			{
				//AVDebugWriteLine(L"Profile is currently in use: " << tuningFanSettingsRunning.Application.value());
				return;
			}

			//Get current and default settings
			TuningFanSettings tuningFanSettingsAdl = TuningFanSettings_Generate_FromADL(adapterIndex, L"", false).value();

			//Check if settings match
			if (!TuningFanSettings_Match(tuningFanSettingsRunning, tuningFanSettingsAdl))
			{
				AVDebugWriteLine("Tuning and fans settings do not match, applying settings.");

				//Apply tuning and fans settings
				bool applyResult = AdlTuningFanSettingsApply(adapterIndex, tuningFanSettingsRunning, AdlSettingGet::Current);

				//Check result
				if (applyResult)
				{
					//Update application using status
					TuningFanSettings_Profile_Set_Using(tuningFanSettingsRunning.DeviceId.value(), tuningFanSettingsRunning.Application.value());
				}

				std::function<winrt::IAsyncAction()> updateFunction = [=]() -> winrt::IAsyncAction
					{
						if (applyResult)
						{
							//Show notification
							ShowNotification(L"Tuning and fans settings applied: " + tuningFanSettingsRunning.Application.value());
							AVDebugWriteLine(L"Tuning and fans settings applied: " << tuningFanSettingsRunning.Application.value());

							//Load tuning and fans settings
							co_await AdlxValuesLoadSelectTuningApp(adl_Gpu_AdapterIndex, tuningFanSettingsProfile.Application.value());
						}
					};
				AppVariables::App.DispatcherInvoke(updateFunction);
			}
		}
		catch (...) {}
	}
}