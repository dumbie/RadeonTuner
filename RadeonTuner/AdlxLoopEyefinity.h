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
								//Check if Eyefinity automatic is enabled
								if (displaySettings.EyefinityAutomatic.Current.has_value())
								{
									if (displaySettings.EyefinityAutomatic.Current.value())
									{
										//Lower case application name
										std::wstring appNameLower = wstring_to_lower(displaySettings.Application.value());

										//Check and set application profile
										if (array_contains(processExeRunning, appNameLower))
										{
											displaySettingsProfileOpt = displaySettings;
											break;
										}
									}
								}
							}
						}
					}
					catch (...) {}
				}

				//Check if Eyefinity needs to be enabled
				bool enableEyefinity = displaySettingsProfileOpt.has_value();

				//Enable or disable Eyefinity
				Adl_Eyefinity_Toggle(adapterIndex, enableEyefinity);

				//Ignore other displays when enabled
				if (enableEyefinity)
				{
					break;
				}
			}
		}
		catch (...) {}
	}
}