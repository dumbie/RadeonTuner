#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlxValuesResetMultimedia()
	{
		try
		{
			//Sharpening
			toggleswitch_Video_Sharpening().IsOn(false);
			slider_Video_Sharpening().Value(50);

			//Return result
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed resetting multimedia settings.");
			return false;
		}
	}
}