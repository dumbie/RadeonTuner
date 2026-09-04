#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AppVariables.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxCheckTuningApplicationProfile(std::vector<std::wstring> processExeRunning)
	{
		try
		{
			//Get all GPU's
			for (auto adapterInfo : AdlGetGpuAll())
			{
				//Device index
				int adapterIndex = adapterInfo.iAdapterIndex;

				//Device identifier
				std::wstring deviceIdentifier = char_to_wstring(adapterInfo.strPNPString);
				deviceIdentifier = wstring_get_between(deviceIdentifier, L"\\", L"\\");

				//Loop settings
				std::optional<std::reference_wrapper<TuningFanSettings>> tuningFanSettingsRunningOpt;
				for (TuningFanSettings& tuningFanSettings : tuningFanSettingsCache)
				{
					try
					{
						//Check and match device id
						if (tuningFanSettings.DeviceId.value() == deviceIdentifier)
						{
							//Check if profile application is running
							if (tuningFanSettings.Application.has_value())
							{
								//Lower case application name
								std::wstring appNameLower = wstring_to_lower(tuningFanSettings.Application.value());

								//Check and set global profile
								if (appNameLower == L"global")
								{
									tuningFanSettingsRunningOpt = tuningFanSettings;
								}

								//Check and set application profile
								if (array_contains(processExeRunning, appNameLower))
								{
									//AVDebugWriteLine("Application profile application running: " << appNameLower);
									tuningFanSettingsRunningOpt = tuningFanSettings;
									break;
								}
							}
						}
					}
					catch (...) {}
				}

				//Compare settings
				if (tuningFanSettingsRunningOpt.has_value())
				{
					//Get profile value
					TuningFanSettings& tuningFanSettingsRunning = tuningFanSettingsRunningOpt.value();
					//AVDebugWriteLine("Comparing tuning and fans settings: " << tuningFanSettingsRunning.DeviceId.value() << L" / " << tuningFanSettingsRunning.Application.value());

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
						continue;
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

						std::function<void()> updateFunction = [=]
							{
								if (applyResult)
								{
									//Show notification
									ShowNotification(L"Tuning and fans settings applied: " + tuningFanSettingsRunning.Application.value());
									AVDebugWriteLine(L"Tuning and fans settings applied: " << tuningFanSettingsRunning.Application.value());

									//Load tuning and fans settings
									AdlxValuesLoadSelectTuningApp(adl_Gpu_AdapterIndex, tuningFanSettingsProfile.Application.value());
								}
							};
						AppVariables::App.DispatcherInvoke(updateFunction);
					}
				}
			}
		}
		catch (...) {}
	}
}