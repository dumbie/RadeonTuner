#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AppVariables.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	//Note: IADLXGPUTuningChangedEvent does not get triggered when tuning is reset by system failure so manual polling is needed.

	void MainPage::AdlxLoopKeepActive()
	{
		while (true)
		{
			try
			{
				//Delay next loop
				if (!AppVariables::LaunchKeepActive)
				{
					Sleep(20000);
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

				//Load and cache keep active setting files
				if (!keepactive_cache_loaded)
				{
					//Get keep active folder path
					std::wstring pathActiveFolderW = PathMerge(PathGetExecutableDirectory(), L"Active");

					//Clear keep active setting cache
					keepactive_cache.clear();

					//List keep active setting files
					auto fileList = FileList(pathActiveFolderW, false);
					for (auto file : fileList)
					{
						try
						{
							//Load tuning fans settings from file
							TuningFanSettings tuningFanSettingsKeepActive = TuningFanSettings_Load(file.path().string());

							//Add settings to keep active cache
							keepactive_cache.push_back(tuningFanSettingsKeepActive);
						}
						catch (...) {}
					}

					//Update status variable
					keepactive_cache_loaded = true;
					AVDebugWriteLine("Keep active setting cache updated.");
				}

				//Check keep active settings
				for (auto keepActiveSettings : keepactive_cache)
				{
					try
					{
						//Check if keep active is enabled
						if (keepActiveSettings.KeepActive.has_value())
						{
							if (!keepActiveSettings.KeepActive.value())
							{
								//AVDebugWriteLine("Keep active is disabled, skipped keep active.");
								continue;
							}
						}
						else
						{
							//AVDebugWriteLine("Keep active is missing, skipped keep active.");
							continue;
						}

						//Loop through all gpus
						for (UINT i = 0; i < ppGpuList->Size(); i++)
						{
							try
							{
								//Get gpu pointer
								IADLXGPU2Ptr ppGpuPtr;
								ppGpuList->At(i, (IADLXGPU**)&ppGpuPtr);

								//Get gpu identifier
								std::wstring device_current_id_w = AdlxGetGpuIdentifier(ppGpuPtr);
								std::string device_current_id_a = wstring_to_string(device_current_id_w);

								//Check gpu identifier
								if (keepActiveSettings.DeviceId.value() == device_current_id_a)
								{
									//Get current gpu tuning and fans settings
									TuningFanSettings tuningFanSettingsCurrent = TuningFanSettings_Generate_FromAdlxGpuPtr(ppGpuPtr);

									//Check if tuning and fans settings match
									if (!TuningFanSettings_Match(keepActiveSettings, tuningFanSettingsCurrent))
									{
										AVDebugWriteLine("Tuning and fans settings do not match, applying keep active settings.");

										//Apply tuning and fans settings
										std::function<void()> updateFunction = [&]
											{
												//Apply tuning and fans settings
												AdlxApplyTuning(ppGpuPtr, keepActiveSettings);

												//Load tuning and fans settings
												AdlxValuesLoadTuning();
											};
										AppVariables::App.DispatcherInvoke(updateFunction);
									}
								}
							}
							catch (...) {}
						}
					}
					catch (...) {}
				}
			}
			catch (...) {}
		}
	}
}