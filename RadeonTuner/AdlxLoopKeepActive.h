#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AppVariables.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxLoopKeepActive()
	{
		while (true)
		{
			try
			{
				//Delay next keep active
				Sleep(10000);

				//Check if AMDSoftwareInstaller is running
				std::vector<ProcessMulti> processList = Get_ProcessesMultiByName("AMDSoftwareInstaller.exe");
				if (processList.size() > 0)
				{
					std::function<void()> updateFunction = [&]
						{
							//Set result
							textblock_Status().Text(L"Skipped keep active");
							AVDebugWriteLine("AMDSoftwareInstaller is running, skipped keep active.");
						};
					AppVariables::App.DispatcherInvoke(updateFunction);
					continue;
				}

				//Get keep active folder path
				std::wstring pathActiveFolderW = PathMerge(PathGetExecutableDirectory(), L"Active");

				//List active overlock setting files
				auto fileList = FileList(pathActiveFolderW, false);
				for (auto file : fileList)
				{
					try
					{
						//Load tuning fans settings from file
						TuningFanSettings tuningFanSettingsKeepActive = TuningFanSettings_Load(file.path().string());

						//Check keep active setting
						if (tuningFanSettingsKeepActive.KeepActive.has_value())
						{
							if (!tuningFanSettingsKeepActive.KeepActive.value())
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
								std::wstring device_current_id_w = AdlxGetDeviceIdentifier(ppGpuPtr);
								std::string device_current_id_a = wstring_to_string(device_current_id_w);

								//Check gpu identifier
								if (tuningFanSettingsKeepActive.DeviceId.value() == device_current_id_a)
								{
									//Get current gpu tuning and fans settings
									TuningFanSettings tuningFanSettingsCurrent = TuningFanSettings_Generate_FromAdlxGpuPtr(ppGpuPtr);

									//Check if tuning and fans settings match
									if (!TuningFanSettings_Match(tuningFanSettingsKeepActive, tuningFanSettingsCurrent))
									{
										AVDebugWriteLine("Tuning and fans settings do not match, applying keep active settings.");

										//Apply tuning and fans settings
										std::function<void()> updateFunction = [&]
											{
												//Apply tuning and fans settings
												AdlxApplyTuning(ppGpuPtr, tuningFanSettingsKeepActive);

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