#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AppVariables.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxLoopKeepActive()
	{
		//Fix switch to IADLXGPUTuningChangedEvent?
		while (true)
		{
			try
			{
				//Delay next overclock
				Sleep(5000);

				//Get active overclock folder path
				std::wstring pathActiveFolderW = PathMerge(PathGetExecutableDirectory(), L"Active");

				//List active overlock setting files
				auto fileList = FileList(pathActiveFolderW, false);
				for (auto file : fileList)
				{
					try
					{
						//Load tuning fan settings from file
						TuningFanSettings tuningFanSettings = TuningFanSettings_Load(file.path().string());

						//Check keep active setting
						if (tuningFanSettings.KeepActive.has_value())
						{
							if (!tuningFanSettings.KeepActive.value())
							{
								//AVDebugWriteLine("Keep active is disabled, skipped overclock.");
								continue;
							}
						}
						else
						{
							//AVDebugWriteLine("Keep active is missing, skipped overclock.");
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
								if (tuningFanSettings.DeviceId.value() == device_current_id_a)
								{
									//Get current gpu tuning
									IADLXManualGraphicsTuning2Ptr ppManualGFXTuning;
									adlx_Res0 = ppGPUTuningServices->GetManualGFXTuning(ppGpuPtr, (IADLXInterface**)&ppManualGFXTuning);

									//Get gpu clock speed
									int device_current_coremax = 0;
									adlx_Res0 = ppManualGFXTuning->GetGPUMaxFrequency(&device_current_coremax);

									//Check gpu clock speed
									//Fix add more checks including fan speed
									//Fix some gpus don't support frequency always returning 0 or 1
									//Fix value CoreMax has_value
									if (device_current_coremax != tuningFanSettings.CoreMax.value())
									{
										AVDebugWriteLine("Target overclock settings do not match, applying overclock.");

										//Check if AMDSoftwareInstaller is running
										std::vector<ProcessMulti> processList = Get_ProcessesMultiByName("AMDSoftwareInstaller.exe");
										if (processList.size() > 0)
										{
											std::function<void()> updateFunction = [&]
												{
													//Set result
													textblock_Status().Text(L"Skipped overclock");
													AVDebugWriteLine("AMDSoftwareInstaller is running, skipped overclock.");
												};
											AppVariables::App.DispatcherInvoke(updateFunction);
											continue;
										}

										//Apply overclock
										std::function<void()> updateFunction = [&]
											{
												//Apply tuning and fans settings
												AdlxApplyTuning(ppGpuPtr, tuningFanSettings);

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