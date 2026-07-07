#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesLoadMultimedia()
	{
		try
		{
			//Get current and default settings
			multimediaSettingsCurrent = MultimediaSettings_Generate_FromADL(adl_Gpu_AdapterIndex).value();

			//Convert settings values to interface
			MultimediaSettings_Convert_ToUI_ADL(multimediaSettingsCurrent);

			//Set result
			AVDebugWriteLine("ADLX loaded multimedia values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading multimedia values.");
		}
	}
}