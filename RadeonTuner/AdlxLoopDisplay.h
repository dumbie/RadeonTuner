#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AppVariables.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxLoopDisplayApplicationProfile(std::vector<std::wstring> processExeRunning)
	{
		try
		{
			//Get all displays
			std::vector<ADLDisplayInfo> displayList = AdlGetDisplayAll();

			//Loop all display's
			for (ADLDisplayInfo& displayInfo : displayList)
			{
				//Device index
				int adapterIndex = displayInfo.displayID.iDisplayLogicalAdapterIndex;
				int displayIndex = displayInfo.displayID.iDisplayLogicalIndex;

				//Device identifier
				std::wstring deviceIdentifier = AdlxGetDisplayIdentifier(adapterIndex, displayIndex);

				//Loop settings
				std::optional<std::reference_wrapper<DisplaySettings>> displaySettingsRunningOpt;
				for (DisplaySettings& displaySettings : displaySettingsCache)
				{
					try
					{
						//Check and match device id
						if (displaySettings.DeviceId.value() == deviceIdentifier)
						{
							//Check if profile application is running
							if (displaySettings.Application.has_value())
							{
								//Lower case application name
								std::wstring appNameLower = wstring_to_lower(displaySettings.Application.value());

								//Check and set global profile
								if (appNameLower == L"global")
								{
									displaySettingsRunningOpt = displaySettings;
								}

								//Check and set application profile
								if (array_contains(processExeRunning, appNameLower))
								{
									//AVDebugWriteLine("Application profile application running: " << appNameLower);
									displaySettingsRunningOpt = displaySettings;
									break;
								}
							}
						}
					}
					catch (...) {}
				}

				//Compare settings
				if (displaySettingsRunningOpt.has_value())
				{
					//Get profile value
					DisplaySettings& displaySettingsRunning = displaySettingsRunningOpt.value();
					//AVDebugWriteLine("Found running display profile application: " << displaySettingsRunning.DeviceId.value() << L" / " << displaySettingsRunning.Application.value());

					//Check if display profile needs to be applied
					AdlxLoopDisplayApplyProfile(adapterIndex, displayIndex, displaySettingsRunning);

					//Check if display gamma needs to be applied
					AdlxLoopDisplayApplyGamma(adapterIndex, displaySettingsRunning);
				}
			}
		}
		catch (...) {}
	}
}