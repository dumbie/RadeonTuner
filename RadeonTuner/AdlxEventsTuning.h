#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::button_Tuning_Apply_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Generate tuning and fans settings
			TuningFanSettings tuningFanSettings = TuningFanSettings_Generate_FromUI().value();

			//Apply tuning and fans settings
			if (AdlTuningApply(adl_Gpu_AdapterIndex, tuningFanSettings))
			{
				//Replace tuning and fans settings
				TuningFanSettings_Profile_Replace(tuningFanSettings);

				//Save tuning and fans settings
				TuningFanSettings_Profiles_SaveToFile();

				//Load tuning values to interface
				AdlxValuesLoadTuning();
			}
		}
		catch (...) {}
	}

	void MainPage::button_Tuning_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Reset tuning and fans settings
			if (AdlTuningReset())
			{
				//Device identifier
				std::wstring device_id_w = AdlxGetGpuIdentifier(ppGpuInfo);

				//Remove tuning and fans settings
				TuningFanSettings_Profile_Remove(device_id_w);

				//Save tuning and fans settings
				TuningFanSettings_Profiles_SaveToFile();

				//Load tuning values to interface
				AdlxValuesLoadTuning();
			}
		}
		catch (...) {}
	}

	void MainPage::button_Tuning_Import_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Import settings from file
			AdlxValuesImportTuning();
		}
		catch (...) {}
	}

	void MainPage::button_Tuning_Export_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Export current settings to file
			AdlxValuesExportTuning();
		}
		catch (...) {}
	}

	void MainPage::slider_Core_Min_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int maxCurrent = (int)slider_Core_Max().Value();
			int minLimits = maxCurrent - 100;
			int minCurrent = (int)slider_Core_Min().Value();
			int maxLimits = minCurrent + 100;

			//Adjust values
			if (minCurrent > minLimits)
			{
				slider_Core_Min().Value(minLimits);
				slider_Core_Max().Value(maxLimits);
			}
		}
		catch (...) {}
	}

	void MainPage::slider_Core_Max_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			if (slider_Core_Min().IsEnabled())
			{
				//Get setting value
				int maxCurrent = (int)slider_Core_Max().Value();
				int minLimits = maxCurrent - 100;
				int minCurrent = (int)slider_Core_Min().Value();
				int maxLimits = minCurrent + 100;

				//Adjust values
				if (minCurrent > minLimits)
				{
					slider_Core_Min().Value(minLimits);
					slider_Core_Max().Value(maxLimits);
				}
			}
		}
		catch (...) {}
	}
}