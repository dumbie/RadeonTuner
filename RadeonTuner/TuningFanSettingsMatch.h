#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::TuningFanSettings_Match(TuningFanSettings tuningFanSettingsProfile, TuningFanSettings tuningFanSettingsGpu)
	{
		try
		{
			//Gpu Core Minimum
			if (tuningFanSettingsProfile.CoreMin.Current.has_value() && tuningFanSettingsGpu.CoreMin.Current.has_value())
			{
				if (tuningFanSettingsProfile.CoreMin.Current.value() != tuningFanSettingsGpu.CoreMin.Current.value()) { return false; }
			}

			//Gpu Core Maximum
			if (tuningFanSettingsProfile.CoreMax.Current.has_value() && tuningFanSettingsGpu.CoreMax.Current.has_value())
			{
				if (tuningFanSettingsProfile.CoreMax.Current.value() != tuningFanSettingsGpu.CoreMax.Current.value()) { return false; }
			}

			//Memory Timing
			if (tuningFanSettingsProfile.MemoryTiming.Current.has_value() && tuningFanSettingsGpu.MemoryTiming.Current.has_value())
			{
				if (tuningFanSettingsProfile.MemoryTiming.Current.value() != tuningFanSettingsGpu.MemoryTiming.Current.value()) { return false; }
			}

			//Memory Frequency
			if (tuningFanSettingsProfile.MemoryMax.Current.has_value() && tuningFanSettingsGpu.MemoryMax.Current.has_value())
			{
				if (tuningFanSettingsProfile.MemoryMax.Current.value() != tuningFanSettingsGpu.MemoryMax.Current.value()) { return false; }
			}

			//Power Boost
			if (tuningFanSettingsProfile.PowerBoostUse)
			{
				//Power Limit (Power Boost)
				if (tuningFanSettingsProfile.PowerLimitPB.Current.has_value() && tuningFanSettingsGpu.PowerLimit.Current.has_value())
				{
					if (tuningFanSettingsProfile.PowerLimitPB.Current.value() != tuningFanSettingsGpu.PowerLimit.Current.value()) { return false; }
				}

				//Power Voltage (Power Boost)
				if (tuningFanSettingsProfile.PowerVoltagePB.Current.has_value() && tuningFanSettingsGpu.PowerVoltage.Current.has_value())
				{
					if (tuningFanSettingsProfile.PowerVoltagePB.Current.value() != tuningFanSettingsGpu.PowerVoltage.Current.value()) { return false; }
				}

				//Power TDC (Power Boost)
				if (tuningFanSettingsProfile.PowerTDCPB.Current.has_value() && tuningFanSettingsGpu.PowerTDC.Current.has_value())
				{
					if (tuningFanSettingsProfile.PowerTDCPB.Current.value() != tuningFanSettingsGpu.PowerTDC.Current.value()) { return false; }
				}
			}
			else
			{
				//Power Limit
				if (tuningFanSettingsProfile.PowerLimit.Current.has_value() && tuningFanSettingsGpu.PowerLimit.Current.has_value())
				{
					if (tuningFanSettingsProfile.PowerLimit.Current.value() != tuningFanSettingsGpu.PowerLimit.Current.value()) { return false; }
				}

				//Power Voltage
				if (tuningFanSettingsProfile.PowerVoltage.Current.has_value() && tuningFanSettingsGpu.PowerVoltage.Current.has_value())
				{
					if (tuningFanSettingsProfile.PowerVoltage.Current.value() != tuningFanSettingsGpu.PowerVoltage.Current.value()) { return false; }
				}

				//Power TDC
				if (tuningFanSettingsProfile.PowerTDC.Current.has_value() && tuningFanSettingsGpu.PowerTDC.Current.has_value())
				{
					if (tuningFanSettingsProfile.PowerTDC.Current.value() != tuningFanSettingsGpu.PowerTDC.Current.value()) { return false; }
				}
			}

			//Fan Control
			if (tuningFanSettingsProfile.FanControl.Current.has_value() && tuningFanSettingsProfile.FanControl.Current.value())
			{
				//Fan Zero RPM
				if (tuningFanSettingsProfile.FanZeroRpm.Current.has_value() && tuningFanSettingsGpu.FanZeroRpm.Current.has_value())
				{
					if (tuningFanSettingsProfile.FanZeroRpm.Current.value() != tuningFanSettingsGpu.FanZeroRpm.Current.value()) { return false; }
				}

				//Fan Speed 0
				if (tuningFanSettingsProfile.FanSpeed0.Current.has_value() && tuningFanSettingsGpu.FanSpeed0.Current.has_value())
				{
					if (tuningFanSettingsProfile.FanSpeed0.Current.value() != tuningFanSettingsGpu.FanSpeed0.Current.value()) { return false; }
				}

				//Fan Temperature 0
				if (tuningFanSettingsProfile.FanTemp0.Current.has_value() && tuningFanSettingsGpu.FanTemp0.Current.has_value())
				{
					if (tuningFanSettingsProfile.FanTemp0.Current.value() != tuningFanSettingsGpu.FanTemp0.Current.value()) { return false; }
				}

				//Fan Speed 1
				if (tuningFanSettingsProfile.FanSpeed1.Current.has_value() && tuningFanSettingsGpu.FanSpeed1.Current.has_value())
				{
					if (tuningFanSettingsProfile.FanSpeed1.Current.value() != tuningFanSettingsGpu.FanSpeed1.Current.value()) { return false; }
				}

				//Fan Temperature 1
				if (tuningFanSettingsProfile.FanTemp1.Current.has_value() && tuningFanSettingsGpu.FanTemp1.Current.has_value())
				{
					if (tuningFanSettingsProfile.FanTemp1.Current.value() != tuningFanSettingsGpu.FanTemp1.Current.value()) { return false; }
				}

				//Fan Speed 2
				if (tuningFanSettingsProfile.FanSpeed2.Current.has_value() && tuningFanSettingsGpu.FanSpeed2.Current.has_value())
				{
					if (tuningFanSettingsProfile.FanSpeed2.Current.value() != tuningFanSettingsGpu.FanSpeed2.Current.value()) { return false; }
				}

				//Fan Temperature 2
				if (tuningFanSettingsProfile.FanTemp2.Current.has_value() && tuningFanSettingsGpu.FanTemp2.Current.has_value())
				{
					if (tuningFanSettingsProfile.FanTemp2.Current.value() != tuningFanSettingsGpu.FanTemp2.Current.value()) { return false; }
				}

				//Fan Speed 3
				if (tuningFanSettingsProfile.FanSpeed3.Current.has_value() && tuningFanSettingsGpu.FanSpeed3.Current.has_value())
				{
					if (tuningFanSettingsProfile.FanSpeed3.Current.value() != tuningFanSettingsGpu.FanSpeed3.Current.value()) { return false; }
				}

				//Fan Temperature 3
				if (tuningFanSettingsProfile.FanTemp3.Current.has_value() && tuningFanSettingsGpu.FanTemp3.Current.has_value())
				{
					if (tuningFanSettingsProfile.FanTemp3.Current.value() != tuningFanSettingsGpu.FanTemp3.Current.value()) { return false; }
				}

				//Fan Speed 4
				if (tuningFanSettingsProfile.FanSpeed4.Current.has_value() && tuningFanSettingsGpu.FanSpeed4.Current.has_value())
				{
					if (tuningFanSettingsProfile.FanSpeed4.Current.value() != tuningFanSettingsGpu.FanSpeed4.Current.value()) { return false; }
				}

				//Fan Temperature 4
				if (tuningFanSettingsProfile.FanTemp4.Current.has_value() && tuningFanSettingsGpu.FanTemp4.Current.has_value())
				{
					if (tuningFanSettingsProfile.FanTemp4.Current.value() != tuningFanSettingsGpu.FanTemp4.Current.value()) { return false; }
				}
			}
		}
		catch (...) {}
		return true;
	}
}