#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AppVariables.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxCheckDisplayEyefinityAutomatic(std::vector<std::wstring> processExeRunning)
	{
		try
		{
			//Check if Automatic Eyefinity is disabled
			if (disable_eyefinity_automatic) { return; }

			//Get all display's
			for (auto displayInfo : AdlGetDisplayAll())
			{
				//Device index
				int adapterIndex = displayInfo.displayID.iDisplayLogicalAdapterIndex;
				int displayIndex = displayInfo.displayID.iDisplayLogicalIndex;

				//Device identifier
				std::wstring deviceIdentifier = AdlxGetDisplayIdentifier(adapterIndex, displayIndex);

				//Loop settings
				int eyefinityAutomaticCount = 0;
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
								//Check if Automatic Eyefinity is enabled
								if (displaySettings.EyefinityAutomatic.Current.has_value() && displaySettings.EyefinityAutomatic.Current.value())
								{
									//Update Automatic Eyefinity count
									eyefinityAutomaticCount++;

									//Lower case application name
									std::wstring appNameLower = wstring_to_lower(displaySettings.Application.value());

									//Check and set application profile
									if (array_contains(processExeRunning, appNameLower))
									{
										displaySettingsRunningOpt = displaySettings;
										break;
									}
								}
							}
						}
					}
					catch (...) {}
				}

				//Check if Eyefinity needs to be toggled
				if (eyefinityAutomaticCount > 0)
				{
					bool enableEyefinity = displaySettingsRunningOpt.has_value();

					//Enable or disable Eyefinity
					Adl_Eyefinity_Toggle(adapterIndex, enableEyefinity);

					//Ignore other displays when enabled
					if (enableEyefinity)
					{
						break;
					}
				}
			}
		}
		catch (...) {}
	}
}