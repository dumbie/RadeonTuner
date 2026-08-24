#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::MultimediaSettings_Match(MultimediaSettings settingsProfile, MultimediaSettings settingsAdl)
	{
		try
		{
			if (settingsProfile.VideoUpscaling.Current.has_value() && settingsAdl.VideoUpscaling.Current.has_value())
			{
				if (settingsProfile.VideoUpscaling.Current.value() != settingsAdl.VideoUpscaling.Current.value()) { return false; }
			}

			if (settingsProfile.VideoSharpening.Current.has_value() && settingsAdl.VideoSharpening.Current.has_value())
			{
				if (settingsProfile.VideoSharpening.Current.value() != settingsAdl.VideoSharpening.Current.value()) { return false; }
			}

			if (settingsProfile.VideoBrightness.Current.has_value() && settingsAdl.VideoBrightness.Current.has_value())
			{
				if (settingsProfile.VideoBrightness.Current.value() != settingsAdl.VideoBrightness.Current.value()) { return false; }
			}
		}
		catch (...) {}
		return true;
	}
}