#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AppVariables.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	//Note: IADLXGPUTuningChangedEvent does not get triggered when tuning is reset by system failure so manual polling is needed.
	//Fix: Change power boost and eyefinity to event that triggers on process launch and close or check foreground window.

	void MainPage::AdlxCheckAutomaticEyefinity(std::vector<std::wstring> processExeRunning)
	{
		try
		{
			//Check Automatic Eyefinity setting
			bool eyefinityAutomatic = false;
			std::optional<bool> eyefinityAutomaticOpt = AppVariables::Settings.Load<bool>("EyefinityAutomatic");
			if (eyefinityAutomaticOpt.has_value())
			{
				eyefinityAutomatic = eyefinityAutomaticOpt.value();
			}

			//Check if Automatic Eyefinity is enabled and app is added
			bool eyefinityProcessFound = false;
			if (eyefinityAutomatic && eyefinityAppsCache.size() > 0)
			{
				//Check if Eyefinity process is running
				for (auto eyefinityApp : eyefinityAppsCache)
				{
					std::wstring eyefinityAppLower = wstring_to_lower(eyefinityApp);
					if (array_contains(processExeRunning, eyefinityAppLower))
					{
						//AVDebugWriteLine("Eyefinity process is running: " << exeNameW);
						eyefinityProcessFound = true;
						break;
					}
				}

				//Enable or disable Eyefinity
				Adl_Eyefinity_Toggle(adl_Display_AdapterIndex, eyefinityProcessFound);
			}
		}
		catch (...) {}
	}

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
				std::wstring adapterDeviceId = char_to_wstring(adapterInfo.strPNPString);
				adapterDeviceId = wstring_get_between(adapterDeviceId, L"\\", L"\\");

				//Loop tuning and fans settings
				std::optional<std::reference_wrapper<TuningFanSettings>> tuningFanSettingsProfileOpt;
				for (TuningFanSettings& tuningFanSettings : tuningFanSettingsCache)
				{
					try
					{
						//Check and match device id
						if (tuningFanSettings.DeviceId.value() == adapterDeviceId)
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

				//Compare tuning fan settings
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
						bool applyResult = AdlTuningApply(adapterIndex, tuningFanSettingsProfile);

						//Update application using status
						if (applyResult)
						{
							TuningFanSettings_Profile_Set_Using(tuningFanSettingsProfile.DeviceId.value(), tuningFanSettingsProfile.Application.value());
						}

						//Show notification
						std::function<void()> updateFunction = [=]
							{
								if (applyResult)
								{
									//Load tuning and fans settings
									AdlxValuesLoadSelectTuning(adapterIndex, tuningFanSettingsCurrent.Application.value());

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

				//Check display Automatic Eyefinity
				AdlxCheckAutomaticEyefinity(processExeRunning);

				//Check tuning Application Profile
				AdlxCheckTuningApplicationProfile(processExeRunning);
			}
			catch (...) {}
		}
	}
}