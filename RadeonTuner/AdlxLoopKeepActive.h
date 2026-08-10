#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AppVariables.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	//Fix: Change display and tuning check to event that triggers on process launch and close or check foreground window switch.
	//Fix: Add support to manually enable RIS2 desktop when it used in an application profile.
	//Fix: Make sure Gamma RGB is set to currently used value, changing resolution etc resets it.

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

					//Apply display settings
					bool applyResult = AdlDisplaySettingsApply(adapterIndex, displayIndex, displaySettingsProfile, AdlSettingGet::Current, true);

					//Update application using status
					if (applyResult)
					{
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
								AdlxValuesLoadSelectDisplayApp(adl_Display_AdapterIndex, adl_Display_DisplayIndex, displaySettingsCurrent.Application.value());
							}
						};
					AppVariables::App.DispatcherInvoke(updateFunction);
				}
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

						//Update application using status
						if (applyResult)
						{
							TuningFanSettings_Profile_Set_Using(tuningFanSettingsProfile.DeviceId.value(), tuningFanSettingsProfile.Application.value());
						}

						std::function<void()> updateFunction = [=]
							{
								if (applyResult)
								{
									//Load tuning and fans settings
									AdlxValuesLoadSelectTuningApp(adapterIndex, tuningFanSettingsCurrent.Application.value());

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

				//Check display automatic eyefinity
				AdlxCheckDisplayEyefinityAutomatic(processExeRunning);

				//Check display application profile
				AdlxCheckDisplayApplicationProfile(processExeRunning);

				//Check tuning application profile
				AdlxCheckTuningApplicationProfile(processExeRunning);
			}
			catch (...) {}
		}
	}
}