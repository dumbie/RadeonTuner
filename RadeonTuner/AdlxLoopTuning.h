#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AppVariables.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxLoopTuningApplicationProfile(std::vector<std::wstring> processExeRunning)
	{
		try
		{
			//Get all available GPU's
			std::vector<AdapterInfo> listGpus = AdlGetGpuAll(false);

			//Loop all gpu's
			for (AdapterInfo& adapterInfo : listGpus)
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
					//AVDebugWriteLine("Found running tuning and fans profile application: " << tuningFanSettingsRunning.DeviceId.value() << L" / " << tuningFanSettingsRunning.Application.value());

					//Check if tuning and fans profile needs to be applied
					AdlxLoopTuningApplyProfile(adapterIndex, tuningFanSettingsRunning);
				}
			}
		}
		catch (...) {}
	}
}