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
				std::optional<std::reference_wrapper<TuningFanSettings>> tuningFanSettingsProfileOpt;
				for (TuningFanSettings& tuningFanSettings : tuningFanSettingsCache)
				{
					try
					{
						//Check and match device id
						if (tuningFanSettings.DeviceId.value() == deviceIdentifier)
						{
							//Check if profile keep active is enabled
							if (tuningFanSettings.KeepActive.Current.has_value())
							{
								if (tuningFanSettings.KeepActive.Current.value())
								{
									tuningFanSettingsProfileOpt = tuningFanSettings;
								}
							}

							//Check if profile application is running
							if (tuningFanSettings.Application.has_value())
							{
								//Lower case application name
								std::wstring appNameLower = wstring_to_lower(tuningFanSettings.Application.value());

								//Check and set global profile
								if (appNameLower == L"global")
								{
									tuningFanSettingsProfileOpt = tuningFanSettings;
								}

								//Check and set application profile
								if (array_contains(processExeRunning, appNameLower))
								{
									//AVDebugWriteLine("Application profile application running: " << appNameLower);
									tuningFanSettingsProfileOpt = tuningFanSettings;
									break;
								}
							}
						}
					}
					catch (...) {}
				}

				//Compare settings
				if (tuningFanSettingsProfileOpt.has_value())
				{
					//Get profile value
					TuningFanSettings& tuningFanSettingsProfile = tuningFanSettingsProfileOpt.value();
					//AVDebugWriteLine("Comparing tuning and fans settings: " << tuningFanSettingsProfile.DeviceId.value() << L" / " << tuningFanSettingsProfile.Application.value());

					//Check if keep active is enabled
					bool keepActiveEnabled = false;
					if (tuningFanSettingsProfile.KeepActive.Current.has_value())
					{
						keepActiveEnabled = tuningFanSettingsProfile.KeepActive.Current.value();
					}

					//Check if apply is required
					if (tuningFanSettingsProfile.UsingProfile && !keepActiveEnabled)
					{
						//AVDebugWriteLine(L"Profile is currently in use: " << tuningFanSettingsProfile.Application.value());
						continue;
					}

					//Get current and default settings
					TuningFanSettings tuningFanSettingsAdl = TuningFanSettings_Generate_FromADL(adapterIndex, L"", false).value();

					//Check if settings match
					if (!TuningFanSettings_Match(tuningFanSettingsProfile, tuningFanSettingsAdl))
					{
						AVDebugWriteLine("Tuning and fans settings do not match, applying settings.");

						//Apply tuning and fans settings
						bool applyResult = AdlTuningFanSettingsApply(adapterIndex, tuningFanSettingsProfile, AdlSettingGet::Current);

						//Check result
						if (applyResult)
						{
							//Update application using status
							TuningFanSettings_Profile_Set_Using(tuningFanSettingsProfile.DeviceId.value(), tuningFanSettingsProfile.Application.value());
						}

						std::function<void()> updateFunction = [=]
							{
								if (applyResult)
								{
									//Load tuning and fans settings
									AdlxValuesLoadSelectTuningApp(adapterIndex, tuningFanSettingsCurrent.get().Application.value());

									//Show notification
									ShowNotification(L"Tuning and fans settings applied: " + tuningFanSettingsProfile.Application.value());
									AVDebugWriteLine(L"Tuning and fans settings applied: " << tuningFanSettingsProfile.Application.value());
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