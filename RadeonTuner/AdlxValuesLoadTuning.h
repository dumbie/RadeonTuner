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
			TuningFanSettings tuningFanSettings = TuningFanSettings_Generate_FromAdlxGpuPtr(ppGpuInfo);
			TuningFanSettings_Convert_ToUI(tuningFanSettings, true);

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