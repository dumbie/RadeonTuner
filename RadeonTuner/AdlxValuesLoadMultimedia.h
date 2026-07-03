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
			MultimediaSettings multimediaSettings = MultimediaSettings_Generate_FromADL(adl_Gpu_AdapterIndex).value();

			//Convert settings values to interface
			MultimediaSettings_ADL_Convert_ToUI(multimediaSettings);

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