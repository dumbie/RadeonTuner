#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AppVariables.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxLoopDisplayApplyGamma(int adapterIndex, DisplaySettings displaySettingsRunning)
	{
		try
		{
			//Check if gamma control is enabled
			if (displaySettingsRunning.GammaControl.Current.has_value() && !displaySettingsRunning.GammaControl.Current.value())
			{
				//AVDebugWriteLine(L"Display gamma control is disabled.");
				return;
			}

			//Get current gamma ramp
			AdlGammaRamp gammaRampCurrent{};
			adl_Res0 = _ADL2_Adapter_Gamma_Get(adl_Context, adapterIndex, &gammaRampCurrent);
			if (adl_Res0 == ADL_OK)
			{
				//Get setting gamma values
				float baseGammaSetting = displaySettingsRunning.GammaBase.Current.value();
				float redGammaSetting = displaySettingsRunning.GammaRed.Current.value();
				float greenGammaSetting = displaySettingsRunning.GammaGreen.Current.value();
				float blueGammaSetting = displaySettingsRunning.GammaBlue.Current.value();

				//Build setting gamma ramp
				AdlGammaRamp gammaRampTarget = AdlGammaRampBuild(baseGammaSetting, redGammaSetting, greenGammaSetting, blueGammaSetting);

				//Check if gamma ramp matches
				if (!AdlGammaRampMatch(gammaRampCurrent, gammaRampTarget))
				{
					//Apply gamma values
					AVDebugWriteLine(L"Display gamma does not match target profile.");
					AdlGammaApply(adapterIndex, baseGammaSetting, redGammaSetting, greenGammaSetting, blueGammaSetting);
				}
			}
		}
		catch (...) {}
	}
}