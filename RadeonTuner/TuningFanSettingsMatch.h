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
			if (settingsProfile.CoreMin.Current.has_value() && settingsAdl.CoreMin.Current.has_value())
			{
				if (settingsProfile.CoreMin.Current.value() != settingsAdl.CoreMin.Current.value()) { return false; }
			}

			if (settingsProfile.CoreMax.Current.has_value() && settingsAdl.CoreMax.Current.has_value())
			{
				if (settingsProfile.CoreMax.Current.value() != settingsAdl.CoreMax.Current.value()) { return false; }
			}

			if (settingsProfile.MemoryTiming.Current.has_value() && settingsAdl.MemoryTiming.Current.has_value())
			{
				if (settingsProfile.MemoryTiming.Current.value() != settingsAdl.MemoryTiming.Current.value()) { return false; }
			}

			if (settingsProfile.MemoryMax.Current.has_value() && settingsAdl.MemoryMax.Current.has_value())
			{
				if (settingsProfile.MemoryMax.Current.value() != settingsAdl.MemoryMax.Current.value()) { return false; }
			}

			if (settingsProfile.PowerLimit.Current.has_value() && settingsAdl.PowerLimit.Current.has_value())
			{
				if (settingsProfile.PowerLimit.Current.value() != settingsAdl.PowerLimit.Current.value()) { return false; }
			}

			if (settingsProfile.PowerVoltage.Current.has_value() && settingsAdl.PowerVoltage.Current.has_value())
			{
				if (settingsProfile.PowerVoltage.Current.value() != settingsAdl.PowerVoltage.Current.value()) { return false; }
			}

			if (settingsProfile.PowerTDC.Current.has_value() && settingsAdl.PowerTDC.Current.has_value())
			{
				if (settingsProfile.PowerTDC.Current.value() != settingsAdl.PowerTDC.Current.value()) { return false; }
			}

			if (settingsProfile.FanControl.Current.has_value() && settingsProfile.FanControl.Current.value())
			{
				if (settingsProfile.FanZeroRpm.Current.has_value() && settingsAdl.FanZeroRpm.Current.has_value())
				{
					if (settingsProfile.FanZeroRpm.Current.value() != settingsAdl.FanZeroRpm.Current.value()) { return false; }
				}

				if (settingsProfile.FanSpeed0.Current.has_value() && settingsAdl.FanSpeed0.Current.has_value())
				{
					if (settingsProfile.FanSpeed0.Current.value() != settingsAdl.FanSpeed0.Current.value()) { return false; }
				}

				if (settingsProfile.FanTemp0.Current.has_value() && settingsAdl.FanTemp0.Current.has_value())
				{
					if (settingsProfile.FanTemp0.Current.value() != settingsAdl.FanTemp0.Current.value()) { return false; }
				}

				if (settingsProfile.FanSpeed1.Current.has_value() && settingsAdl.FanSpeed1.Current.has_value())
				{
					if (settingsProfile.FanSpeed1.Current.value() != settingsAdl.FanSpeed1.Current.value()) { return false; }
				}

				if (settingsProfile.FanTemp1.Current.has_value() && settingsAdl.FanTemp1.Current.has_value())
				{
					if (settingsProfile.FanTemp1.Current.value() != settingsAdl.FanTemp1.Current.value()) { return false; }
				}

				if (settingsProfile.FanSpeed2.Current.has_value() && settingsAdl.FanSpeed2.Current.has_value())
				{
					if (settingsProfile.FanSpeed2.Current.value() != settingsAdl.FanSpeed2.Current.value()) { return false; }
				}

				if (settingsProfile.FanTemp2.Current.has_value() && settingsAdl.FanTemp2.Current.has_value())
				{
					if (settingsProfile.FanTemp2.Current.value() != settingsAdl.FanTemp2.Current.value()) { return false; }
				}

				if (settingsProfile.FanSpeed3.Current.has_value() && settingsAdl.FanSpeed3.Current.has_value())
				{
					if (settingsProfile.FanSpeed3.Current.value() != settingsAdl.FanSpeed3.Current.value()) { return false; }
				}

				if (settingsProfile.FanTemp3.Current.has_value() && settingsAdl.FanTemp3.Current.has_value())
				{
					if (settingsProfile.FanTemp3.Current.value() != settingsAdl.FanTemp3.Current.value()) { return false; }
				}

				if (settingsProfile.FanSpeed4.Current.has_value() && settingsAdl.FanSpeed4.Current.has_value())
				{
					if (settingsProfile.FanSpeed4.Current.value() != settingsAdl.FanSpeed4.Current.value()) { return false; }
				}

				if (settingsProfile.FanTemp4.Current.has_value() && settingsAdl.FanTemp4.Current.has_value())
				{
					if (settingsProfile.FanTemp4.Current.value() != settingsAdl.FanTemp4.Current.value()) { return false; }
				}
			}
		}
		catch (...) {}
		return true;
	}
}