#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::DisplaySettings_Match(DisplaySettings settingsProfile, DisplaySettings settingsAdl, bool appProfileOnly)
	{
		try
		{
			if (settingsProfile.Brightness.Current.has_value() && settingsAdl.Brightness.Current.has_value() && settingsAdl.Brightness.Support)
			{
				if (settingsProfile.Brightness.Current.value() != settingsAdl.Brightness.Current.value()) { return false; }
			}

			if (!appProfileOnly)
			{
				if (settingsProfile.ColorDepth.Current.has_value() && settingsAdl.ColorDepth.Current.has_value() && settingsAdl.ColorDepth.Support)
				{
					if (settingsProfile.ColorDepth.Current.value() != settingsAdl.ColorDepth.Current.value()) { return false; }
				}
			}

			if (settingsProfile.ColorEnhancement.Current.has_value() && settingsAdl.ColorEnhancement.Current.has_value() && settingsAdl.ColorEnhancement.Support)
			{
				if (settingsProfile.ColorEnhancement.Current.value() != settingsAdl.ColorEnhancement.Current.value()) { return false; }
			}

			if (settingsProfile.ColorTemperatureControl.Current.has_value() && settingsAdl.ColorTemperatureControl.Current.has_value() && settingsAdl.ColorTemperatureControl.Support)
			{
				if (settingsProfile.ColorTemperatureControl.Current.value() != settingsAdl.ColorTemperatureControl.Current.value()) { return false; }
			}

			if (settingsProfile.ColorTemperatureKelvin.Current.has_value() && settingsAdl.ColorTemperatureKelvin.Current.has_value() && settingsAdl.ColorTemperatureKelvin.Support)
			{
				if (settingsProfile.ColorTemperatureKelvin.Current.value() != settingsAdl.ColorTemperatureKelvin.Current.value()) { return false; }
			}

			if (settingsProfile.Contrast.Current.has_value() && settingsAdl.Contrast.Current.has_value() && settingsAdl.Contrast.Support)
			{
				if (settingsProfile.Contrast.Current.value() != settingsAdl.Contrast.Current.value()) { return false; }
			}

			if (settingsProfile.CVDCControl.Current.has_value() && settingsAdl.CVDCControl.Current.has_value() && settingsAdl.CVDCControl.Support)
			{
				if (settingsProfile.CVDCControl.Current.value() != settingsAdl.CVDCControl.Current.value()) { return false; }
			}

			if (settingsProfile.CVDCProtanopia.Current.has_value() && settingsAdl.CVDCProtanopia.Current.has_value() && settingsAdl.CVDCProtanopia.Support)
			{
				if (settingsProfile.CVDCProtanopia.Current.value() != settingsAdl.CVDCProtanopia.Current.value()) { return false; }
			}

			if (settingsProfile.CVDCDeuteranopia.Current.has_value() && settingsAdl.CVDCDeuteranopia.Current.has_value() && settingsAdl.CVDCDeuteranopia.Support)
			{
				if (settingsProfile.CVDCDeuteranopia.Current.value() != settingsAdl.CVDCDeuteranopia.Current.value()) { return false; }
			}

			if (settingsProfile.CVDCTritanopia.Current.has_value() && settingsAdl.CVDCTritanopia.Current.has_value() && settingsAdl.CVDCTritanopia.Support)
			{
				if (settingsProfile.CVDCTritanopia.Current.value() != settingsAdl.CVDCTritanopia.Current.value()) { return false; }
			}

			if (settingsProfile.FreeSyncMode.Current.has_value() && settingsAdl.FreeSyncMode.Current.has_value() && settingsAdl.FreeSyncMode.Support)
			{
				if (settingsProfile.FreeSyncMode.Current.value() != settingsAdl.FreeSyncMode.Current.value()) { return false; }
			}

			if (!appProfileOnly)
			{
				if (settingsProfile.GpuScalingEnabled.Current.has_value() && settingsAdl.GpuScalingEnabled.Current.has_value() && settingsAdl.GpuScalingEnabled.Support)
				{
					if (settingsProfile.GpuScalingEnabled.Current.value() != settingsAdl.GpuScalingEnabled.Current.value()) { return false; }
				}
			}

			if (!appProfileOnly)
			{
				if (settingsProfile.HDCPEnabled.Current.has_value() && settingsAdl.HDCPEnabled.Current.has_value() && settingsAdl.HDCPEnabled.Support)
				{
					if (settingsProfile.HDCPEnabled.Current.value() != settingsAdl.HDCPEnabled.Current.value()) { return false; }
				}
			}

			if (!appProfileOnly)
			{
				if (settingsProfile.HdrEnabled.Current.has_value() && settingsAdl.HdrEnabled.Current.has_value() && settingsAdl.HdrEnabled.Support)
				{
					if (settingsProfile.HdrEnabled.Current.value() != settingsAdl.HdrEnabled.Current.value()) { return false; }
				}
			}

			if (settingsProfile.Hue.Current.has_value() && settingsAdl.Hue.Current.has_value() && settingsAdl.Hue.Support)
			{
				if (settingsProfile.Hue.Current.value() != settingsAdl.Hue.Current.value()) { return false; }
			}

			if (!appProfileOnly)
			{
				if (settingsProfile.IntegerScalingEnabled.Current.has_value() && settingsAdl.IntegerScalingEnabled.Current.has_value() && settingsAdl.IntegerScalingEnabled.Support)
				{
					if (settingsProfile.IntegerScalingEnabled.Current.value() != settingsAdl.IntegerScalingEnabled.Current.value()) { return false; }
				}
			}

			if (!appProfileOnly)
			{
				if (settingsProfile.PixelFormat.Current.has_value() && settingsAdl.PixelFormat.Current.has_value() && settingsAdl.PixelFormat.Support)
				{
					if (settingsProfile.PixelFormat.Current.value() != settingsAdl.PixelFormat.Current.value()) { return false; }
				}
			}

			if (settingsProfile.Saturation.Current.has_value() && settingsAdl.Saturation.Current.has_value() && settingsAdl.Saturation.Support)
			{
				if (settingsProfile.Saturation.Current.value() != settingsAdl.Saturation.Current.value()) { return false; }
			}

			if (!appProfileOnly)
			{
				if (settingsProfile.ScalingMode.Current.has_value() && settingsAdl.ScalingMode.Current.has_value() && settingsAdl.ScalingMode.Support)
				{
					if (settingsProfile.ScalingMode.Current.value() != settingsAdl.ScalingMode.Current.value()) { return false; }
				}
			}

			if (!appProfileOnly)
			{
				if (settingsProfile.VariBrightEnabled.Current.has_value() && settingsAdl.VariBrightEnabled.Current.has_value() && settingsAdl.VariBrightEnabled.Support)
				{
					if (settingsProfile.VariBrightEnabled.Current.value() != settingsAdl.VariBrightEnabled.Current.value()) { return false; }
				}
			}

			if (!appProfileOnly)
			{
				if (settingsProfile.VariBrightLevel.Current.has_value() && settingsAdl.VariBrightLevel.Current.has_value() && settingsAdl.VariBrightLevel.Support)
				{
					if (settingsProfile.VariBrightLevel.Current.value() != settingsAdl.VariBrightLevel.Current.value()) { return false; }
				}
			}

			if (!appProfileOnly)
			{
				if (settingsProfile.VsrEnabled.Current.has_value() && settingsAdl.VsrEnabled.Current.has_value() && settingsAdl.VsrEnabled.Support)
				{
					if (settingsProfile.VsrEnabled.Current.value() != settingsAdl.VsrEnabled.Current.value()) { return false; }
				}
			}
		}
		catch (...) {}
		return true;
	}
}