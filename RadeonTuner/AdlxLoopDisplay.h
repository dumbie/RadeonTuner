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
				std::optional<std::reference_wrapper<DisplaySettings>> displaySettingsProfileOpt;
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
									displaySettingsProfileOpt = displaySettings;
								}

								//Check and set application profile
								if (array_contains(processExeRunning, appNameLower))
								{
									//AVDebugWriteLine("Application profile application running: " << appNameLower);
									displaySettingsProfileOpt = displaySettings;
									break;
								}
							}
						}
					}
					catch (...) {}
				}

				//Compare settings
				if (displaySettingsProfileOpt.has_value())
				{
					//Get profile value
					DisplaySettings& displaySettingsProfile = displaySettingsProfileOpt.value();
					//AVDebugWriteLine("Comparing display settings: " << displaySettingsProfile.DeviceId.value() << L" / " << displaySettingsProfile.Application.value());

					//Check if apply is required
					if (displaySettingsProfile.UsingProfile)
					{
						//AVDebugWriteLine(L"Profile is currently in use: " << displaySettingsProfile.Application.value());
						continue;
					}

					//Get current and default settings
					DisplaySettings displaySettingsAdl = DisplaySettings_Generate_FromADL(adapterIndex, displayIndex, L"", false).value();

					//Check if settings match
					if (!DisplaySettings_Match(displaySettingsProfile, displaySettingsAdl, true))
					{
						AVDebugWriteLine("Display settings do not match, applying settings.");

						//Apply display settings
						bool applyResult = AdlDisplaySettingsApply(adapterIndex, displayIndex, displaySettingsProfile, AdlSettingGet::Current, true);

						//Check result
						if (applyResult)
						{
							//Update application using status
							DisplaySettings_Profile_Set_Using(displaySettingsProfile.DeviceId.value(), displaySettingsProfile.Application.value());
						}

						std::function<void()> updateFunction = [=]
							{
								if (applyResult)
								{
									//Show notification
									ShowNotification(L"Display settings applied: " + displaySettingsProfile.Application.value());
									AVDebugWriteLine(L"Display settings applied: " << displaySettingsProfile.Application.value());

									//Load display settings
									AdlxValuesLoadSelectDisplayApp(adapterIndex, displayIndex, displaySettingsCurrent.get().Application.value());
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