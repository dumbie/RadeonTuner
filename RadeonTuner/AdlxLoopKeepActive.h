#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AppVariables.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	//Note: IADLXGPUTuningChangedEvent does not get triggered when tuning is reset by system failure so manual polling is needed.
	//Fix: Change power boost and eyefinity to event that triggers on process launch and close or check foreground window.

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
				bool eyefinityProcessRunning = false;
				bool powerBoostProcessRunning = false;
				bool powerBoostAppsAny = powerBoostAppsCache.size() > 0;
				bool eyefinityAppsAny = eyefinityAppsCache.size() > 0;
				if (powerBoostAppsAny || eyefinityAppsAny)
				{
					for (AVProcess process : Get_ProcessAll())
					{
						try
						{
							//Fix lower upper case matching
							std::wstring exeNameW = string_to_wstring(process.ExeName());

							//Check if Power Boost process is running
							if (powerBoostAppsAny && array_contains(powerBoostAppsCache, exeNameW))
							{
								//AVDebugWriteLine("Power Boost process is running: " << exeNameW);
								powerBoostProcessRunning = true;
							}

							//Check if Eyefinity process is running
							if (eyefinityAppsAny && array_contains(eyefinityAppsCache, exeNameW))
							{
								//AVDebugWriteLine("Eyefinity process is running: " << exeNameW);
								eyefinityProcessRunning = true;
							}

							//Break from loop
							if (eyefinityProcessRunning && powerBoostProcessRunning)
							{
								break;
							}
						}
						catch (...) {}
					}
				}

				//Check Automatic Eyefinity setting
				bool eyefinityAutomatic = false;
				std::optional<bool> eyefinityAutomaticOpt = AppVariables::Settings.Load<bool>("EyefinityAutomatic");
				if (eyefinityAutomaticOpt.has_value())
				{
					eyefinityAutomatic = eyefinityAutomaticOpt.value();
				}

				//Enable or disable Eyefinity
				if (eyefinityAutomatic)
				{
					Adl_Eyefinity_Toggle(adl_Display_AdapterIndex, eyefinityProcessRunning);
				}

				//Check tuning fan settings
				for (TuningFanSettings& tuningFanSettingsProfile : tuningFanSettingsCache)
				{
					try
					{
						//AVDebugWriteLine("Checking tuning and fans settings for device: " << tuningFanSettingsProfile.DeviceId.value().c_str());

						//Check if Keep Active is enabled
						bool keepActiveEnabled = false;
						if (tuningFanSettingsProfile.KeepActive.has_value())
						{
							keepActiveEnabled = tuningFanSettingsProfile.KeepActive.value();
						}

						//Check if Power Boost is enabled
						bool powerBoostEnabled = false;
						if (tuningFanSettingsProfile.PowerBoost.has_value())
						{
							powerBoostEnabled = tuningFanSettingsProfile.PowerBoost.value();
						}

						//Check enabled settings
						if (!keepActiveEnabled && !powerBoostEnabled)
						{
							continue;
						}

						//Get GPU information
						std::string deviceId = tuningFanSettingsProfile.DeviceId.value();
						std::wstring deviceIdW = string_to_wstring(deviceId);
						std::optional<AdapterInfo> gpuInformation = AdlGetGpuByDeviceId(deviceIdW);
						if (!gpuInformation.has_value())
						{
							continue;
						}

						//Get GPU adapter index
						int gpuAdapterIndex = gpuInformation.value().iAdapterIndex;

						//Get current gpu tuning and fans settings
						std::optional<TuningFanSettings> tuningFanSettingsGpu = TuningFanSettings_Generate_FromGPU(gpuAdapterIndex);
						if (!tuningFanSettingsGpu.has_value())
						{
							continue;
						}

						//Check if Power Boost is enabled and used
						if (powerBoostEnabled)
						{
							tuningFanSettingsProfile.PowerBoostUse = powerBoostProcessRunning;
						}
						else
						{
							tuningFanSettingsProfile.PowerBoostUse = false;
						}

						//Check if tuning and fans settings match
						if (!TuningFanSettings_Match(tuningFanSettingsProfile, tuningFanSettingsGpu.value()))
						{
							AVDebugWriteLine("Tuning and fans settings do not match, applying settings.");

							//Apply tuning and fans settings
							std::function<void()> updateFunction = [=]
								{
									//Apply tuning and fans settings
									if (AdlTuningApply(gpuAdapterIndex, tuningFanSettingsProfile))
									{
										//Load tuning and fans settings
										AdlxValuesLoadTuning();
									}
								};
							AppVariables::App.DispatcherInvoke(updateFunction);
						}
					}
					catch (...) {}
				}
			}
			catch (...) {}
		}
	}
}