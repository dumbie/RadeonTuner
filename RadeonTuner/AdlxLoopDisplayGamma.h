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
			//Get current gamma ramp
			AdlGammaRamp gammaRamp{};
			adl_Res0 = _ADL2_Adapter_Gamma_Get(adl_Context, adapterIndex, &gammaRamp);
			if (adl_Res0 == ADL_OK)
			{
				//Get setting gamma values
				float redGammaSetting = displaySettingsRunning.GammaRed.Current.value();
				float greenGammaSetting = displaySettingsRunning.GammaGreen.Current.value();
				float blueGammaSetting = displaySettingsRunning.GammaBlue.Current.value();

				//Get current gamma values
				float redGammaCurrent = 1.0F;
				float greenGammaCurrent = 1.0F;
				float blueGammaCurrent = 1.0F;
				AdlGammaRampConvertToFloat(gammaRamp, redGammaCurrent, greenGammaCurrent, blueGammaCurrent);

				//Check if gamma matches
				if (!float_equal(redGammaCurrent, redGammaSetting) || !float_equal(greenGammaCurrent, greenGammaSetting) || !float_equal(blueGammaCurrent, blueGammaSetting))
				{
					//Apply gamma values
					AVDebugWriteLine(L"Display gamma does not match target profile.");
					AdlGammaApply(adapterIndex, redGammaSetting, greenGammaSetting, blueGammaSetting);

					//Fix update current gamma string on display tab
				}
			}
		}
		catch (...) {}
	}
}