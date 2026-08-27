#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AppVariables.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxCheckDisplayApplicationProfile(std::vector<std::wstring> processExeRunning)
	{
		try
		{
			//Get all display's
			for (auto displayInfo : AdlGetDisplayAll())
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
					//AVDebugWriteLine("Comparing display settings: " << displaySettingsRunning.DeviceId.value() << L" / " << displaySettingsRunning.Application.value());

					//Check if apply is required
					if (displaySettingsRunning.UsingProfile)
					{
						//AVDebugWriteLine(L"Profile is currently in use: " << displaySettingsRunning.Application.value());
						continue;
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

					std::function<void()> updateFunction = [=]
						{
							if (applyResult)
							{
								//Show notification
								ShowNotification(L"Display settings applied: " + displaySettingsRunning.Application.value());
								AVDebugWriteLine(L"Display settings applied: " << displaySettingsRunning.Application.value());

								//Load display settings
								AdlxValuesLoadSelectDisplayApp(adl_Display_AdapterIndex, adl_Display_DisplayIndex, displaySettingsProfile.Application.value());
							}
						};
					AppVariables::App.DispatcherInvoke(updateFunction);
				}
			}
		}
		catch (...) {}
	}
}