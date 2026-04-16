#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesLoadTuning()
	{
		try
		{
			//Check services
			if (ppGPUTuningServices == NULL)
			{
				stackpanel_Tuning().Opacity(0.20);
				stackpanel_Tuning().IsHitTestVisible(false);
				stackpanel_Fans().Opacity(0.20);
				stackpanel_Fans().IsHitTestVisible(false);
				AVDebugWriteLine("ADLX tuning service is not available.");
				return;
			}

			//Load tuning and fan settings
			TuningFanSettings tuningFanSettingsGpu = TuningFanSettings_Generate_FromAdlxGpuPtr(ppGpuInfo).value();

			//Add gpu tuning and fans settings profile
			TuningFanSettings_Profile_Add(tuningFanSettingsGpu);

			//Device identifier
			std::wstring device_id_w = string_to_wstring(tuningFanSettingsGpu.DeviceId.value());

			//Get tuning fan settings
			TuningFanSettings& tuningFanSettingsProfile = TuningFanSettings_Profile_Get(device_id_w).value();

			//Set settings values to interface
			TuningFanSettings_GPU_Convert_ToUI(tuningFanSettingsGpu);
			TuningFanSettings_Profile_Convert_ToUI(tuningFanSettingsProfile);

			//Set result
			AVDebugWriteLine("ADLX loaded tuning and fans values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading tuning and fans values.");
		}
	}
}