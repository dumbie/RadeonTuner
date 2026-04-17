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
					Sleep(15000);
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
				bool powerBoostProcessRunning = false;
				for (AVProcess process : Get_ProcessAll())
				{
					try
					{
						//Fix lower upper case matching

						//Check if Power Boost process is running
						std::wstring exeNameW = string_to_wstring(process.ExeName());
						if (array_contains(powerBoostAppsCache, exeNameW))
						{
							//AVDebugWriteLine("Power Boost process is running: " << exeNameW);
							powerBoostProcessRunning = true;
							break;
						}
					}
					catch (...) {}
				}

				//Check tuning fan settings
				for (TuningFanSettings& tuningFanSettingsProfile : tuningFanSettingsCache)
				{
					try
					{
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

						//Get GPU pointer
						IADLXGPU2Ptr gpuPointer = AdlxGetGpuPointer(tuningFanSettingsProfile.DeviceId.value());
						if (gpuPointer == nullptr)
						{
							continue;
						}

						//Get current gpu tuning and fans settings
						TuningFanSettings tuningFanSettingsGpu = TuningFanSettings_Generate_FromAdlxGpuPtr(gpuPointer).value();

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
						if (!TuningFanSettings_Match(tuningFanSettingsProfile, tuningFanSettingsGpu))
						{
							AVDebugWriteLine("Tuning and fans settings do not match, applying settings.");

							//Apply tuning and fans settings
							std::function<void()> updateFunction = [&]
								{
									//Apply tuning and fans settings
									if (AdlxApplyTuning(gpuPointer, tuningFanSettingsProfile))
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