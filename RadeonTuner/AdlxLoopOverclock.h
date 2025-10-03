#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AppVariables.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxLoopOverclock()
	{
		//Fix switch to IADLXGPUTuningChangedEvent?
		while (true)
		{
			try
			{
				//Delay next overclock
				Sleep(5000);

				//Check active overclock setting
				std::optional<bool> ActiveOverclock = AppVariables::Settings.Load<bool>("ActiveOverclock");
				if (ActiveOverclock.has_value() && ActiveOverclock.value())
				{
					//Get active overclock path
					std::wstring pathSettingFileW = PathMerge(PathGetExecutableDirectory(), L"ActiveOverclock.json");
					std::string pathSettingFileA = wstring_to_string(pathSettingFileW);

					//Open settings file
					std::string settings = file_to_string(pathSettingFileA);

					//Parse settings file
					nlohmann::json jsonData = nlohmann::json::parse(settings);

					//Convert json to struct
					TuningFanSettings targetSettings = Generate_TuningFanSettings(jsonData);

					//Loop through all gpus
					for (UINT i = 0; i < ppGpuList->Size(); i++)
					{
						//Get gpu pointer
						IADLXGPU2Ptr ppGpuPtr;
						ppGpuList->At(i, (IADLXGPU**)&ppGpuPtr);

						//Get gpu identifier
						std::wstring device_current_id_w = AdlxGetDeviceIdentifier(ppGpuPtr);
						std::string device_current_id_a = wstring_to_string(device_current_id_w);

						//Check gpu identifier
						if (targetSettings.DeviceId == device_current_id_a)
						{
							//Get current gpu clock speed
							IADLXManualGraphicsTuning2Ptr ppManualGFXTuning;
							adlx_Res0 = ppGPUTuningServices->GetManualGFXTuning(ppGpuPtr, (IADLXInterface**)&ppManualGFXTuning);

							int device_current_coremax = 0;
							adlx_Res0 = ppManualGFXTuning->GetGPUMaxFrequency(&device_current_coremax);

							//Check gpu clock speed
							if (device_current_coremax != targetSettings.CoreMax)
							{
								AVDebugWriteLine("Target overclock settings do not match, applying overclock.");
								std::function<void()> updateFunction = [&]
									{
										//Apply tuning and fans settings
										AdlxApplyTuning(targetSettings);

										//Load tuning settings
										AdlxValuesLoadTuning();

										//Load fans settings
										AdlxValuesLoadFans();
									};
								AppVariables::App.DispatcherInvoke(updateFunction);
							}
						}
					}

					AVDebugWriteLine("ADLX active overclock time");
				}
			}
			catch (...) {}
		}
	}
}