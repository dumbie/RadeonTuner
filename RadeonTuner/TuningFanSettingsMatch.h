#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::TuningFanSettings_Match(TuningFanSettings settingsProfile, TuningFanSettings settingsAdl)
	{
		try
		{
			if (settingsProfile.CoreMin.Current.has_value() && settingsAdl.CoreMin.Current.has_value() && settingsAdl.CoreMin.Support)
			{
				if (settingsProfile.CoreMin.Current.value() != settingsAdl.CoreMin.Current.value()) { return false; }
			}

			if (settingsProfile.CoreMax.Current.has_value() && settingsAdl.CoreMax.Current.has_value() && settingsAdl.CoreMax.Support)
			{
				if (settingsProfile.CoreMax.Current.value() != settingsAdl.CoreMax.Current.value()) { return false; }
			}

			if (settingsProfile.MemoryTiming.Current.has_value() && settingsAdl.MemoryTiming.Current.has_value() && settingsAdl.MemoryTiming.Support)
			{
				if (settingsProfile.MemoryTiming.Current.value() != settingsAdl.MemoryTiming.Current.value()) { return false; }
			}

			if (settingsProfile.MemoryMax.Current.has_value() && settingsAdl.MemoryMax.Current.has_value() && settingsAdl.MemoryMax.Support)
			{
				if (settingsProfile.MemoryMax.Current.value() != settingsAdl.MemoryMax.Current.value()) { return false; }
			}

			if (settingsProfile.PowerLimit.Current.has_value() && settingsAdl.PowerLimit.Current.has_value() && settingsAdl.PowerLimit.Support)
			{
				if (settingsProfile.PowerLimit.Current.value() != settingsAdl.PowerLimit.Current.value()) { return false; }
			}

			if (settingsProfile.PowerVoltage.Current.has_value() && settingsAdl.PowerVoltage.Current.has_value() && settingsAdl.PowerVoltage.Support)
			{
				if (settingsProfile.PowerVoltage.Current.value() != settingsAdl.PowerVoltage.Current.value()) { return false; }
			}

			if (settingsProfile.PowerTDC.Current.has_value() && settingsAdl.PowerTDC.Current.has_value() && settingsAdl.PowerTDC.Support)
			{
				if (settingsProfile.PowerTDC.Current.value() != settingsAdl.PowerTDC.Current.value()) { return false; }
			}

			if (settingsProfile.FanControl.Current.has_value() && settingsAdl.FanControl.Current.has_value() && settingsAdl.FanControl.Support)
			{
				if (settingsProfile.FanControl.Current.value() != settingsAdl.FanControl.Current.value()) { return false; }
			}

			if (settingsProfile.FanControl.Current.has_value() && settingsProfile.FanControl.Current.value())
			{
				if (settingsProfile.FanZeroRpm.Current.has_value() && settingsAdl.FanZeroRpm.Current.has_value() && settingsAdl.FanZeroRpm.Support)
				{
					if (settingsProfile.FanZeroRpm.Current.value() != settingsAdl.FanZeroRpm.Current.value()) { return false; }
				}

				if (settingsProfile.FanSpeed0.Current.has_value() && settingsAdl.FanSpeed0.Current.has_value() && settingsAdl.FanSpeed0.Support)
				{
					if (settingsProfile.FanSpeed0.Current.value() != settingsAdl.FanSpeed0.Current.value()) { return false; }
				}

				if (settingsProfile.FanTemp0.Current.has_value() && settingsAdl.FanTemp0.Current.has_value() && settingsAdl.FanTemp0.Support)
				{
					if (settingsProfile.FanTemp0.Current.value() != settingsAdl.FanTemp0.Current.value()) { return false; }
				}

				if (settingsProfile.FanSpeed1.Current.has_value() && settingsAdl.FanSpeed1.Current.has_value() && settingsAdl.FanSpeed1.Support)
				{
					if (settingsProfile.FanSpeed1.Current.value() != settingsAdl.FanSpeed1.Current.value()) { return false; }
				}

				if (settingsProfile.FanTemp1.Current.has_value() && settingsAdl.FanTemp1.Current.has_value() && settingsAdl.FanTemp1.Support)
				{
					if (settingsProfile.FanTemp1.Current.value() != settingsAdl.FanTemp1.Current.value()) { return false; }
				}

				if (settingsProfile.FanSpeed2.Current.has_value() && settingsAdl.FanSpeed2.Current.has_value() && settingsAdl.FanSpeed2.Support)
				{
					if (settingsProfile.FanSpeed2.Current.value() != settingsAdl.FanSpeed2.Current.value()) { return false; }
				}

				if (settingsProfile.FanTemp2.Current.has_value() && settingsAdl.FanTemp2.Current.has_value() && settingsAdl.FanTemp2.Support)
				{
					if (settingsProfile.FanTemp2.Current.value() != settingsAdl.FanTemp2.Current.value()) { return false; }
				}

				if (settingsProfile.FanSpeed3.Current.has_value() && settingsAdl.FanSpeed3.Current.has_value() && settingsAdl.FanSpeed3.Support)
				{
					if (settingsProfile.FanSpeed3.Current.value() != settingsAdl.FanSpeed3.Current.value()) { return false; }
				}

				if (settingsProfile.FanTemp3.Current.has_value() && settingsAdl.FanTemp3.Current.has_value() && settingsAdl.FanTemp3.Support)
				{
					if (settingsProfile.FanTemp3.Current.value() != settingsAdl.FanTemp3.Current.value()) { return false; }
				}

				if (settingsProfile.FanSpeed4.Current.has_value() && settingsAdl.FanSpeed4.Current.has_value() && settingsAdl.FanSpeed4.Support)
				{
					if (settingsProfile.FanSpeed4.Current.value() != settingsAdl.FanSpeed4.Current.value()) { return false; }
				}

				if (settingsProfile.FanTemp4.Current.has_value() && settingsAdl.FanTemp4.Current.has_value() && settingsAdl.FanTemp4.Support)
				{
					if (settingsProfile.FanTemp4.Current.value() != settingsAdl.FanTemp4.Current.value()) { return false; }
				}
			}
		}
		catch (...) {}
		return true;
	}
}