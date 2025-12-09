#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesLoadPower()
	{
		try
		{
			//Check services
			if (ppPowerTuningServices == NULL)
			{
				stackpanel_Power().Opacity(0.20);
				stackpanel_Power().IsHitTestVisible(false);
				AVDebugWriteLine("ADLX power service is not available.");
				return;
			}

			//Get smartshift eco
			try
			{
				IADLXSmartShiftEcoPtr ppSmartShiftEco;
				adlx_Res0 = ppPowerTuningServices->GetSmartShiftEco(&ppSmartShiftEco);
				adlx_Res0 = ppSmartShiftEco->IsSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = ppSmartShiftEco->IsEnabled(&adlx_Bool);
					toggleswitch_SmartShiftEco().IsOn(adlx_Bool);

					//Enable or disable interface
					toggleswitch_SmartShiftEco().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
					toggleswitch_SmartShiftEco().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_SmartShiftEco().IsEnabled(false);
			}

			//Get smartshift max
			try
			{
				IADLXSmartShiftMaxPtr ppSmartShiftMax;
				adlx_Res0 = ppPowerTuningServices->GetSmartShiftMax(&ppSmartShiftMax);
				adlx_Res0 = ppSmartShiftMax->IsSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					//Set setting mode
					ADLX_SSM_BIAS_MODE currentMode;
					adlx_Res0 = ppSmartShiftMax->GetBiasMode(&currentMode);
					combobox_SmartShiftMaxMode().SelectedIndex(currentMode);

					//Set setting bias
					adlx_Res0 = ppSmartShiftMax->GetBias(&adlx_Int0);
					adlx_Res0 = ppSmartShiftMax->GetBiasRange(&adlx_IntRange0);
					slider_SmartShiftMaxBias().Value(adlx_Int0);
					slider_SmartShiftMaxBias().Minimum(adlx_IntRange0.minValue);
					slider_SmartShiftMaxBias().Maximum(adlx_IntRange0.maxValue);
					slider_SmartShiftMaxBias().StepFrequency(adlx_IntRange0.step);
					slider_SmartShiftMaxBias().SmallChange(adlx_IntRange0.step);

					//Enable or disable interface
					combobox_SmartShiftMaxMode().IsEnabled(true);
					if (currentMode == ADLX_SSM_BIAS_MODE::SSM_BIAS_AUTO)
					{
						slider_SmartShiftMaxBias().IsEnabled(false);
					}
					else
					{
						slider_SmartShiftMaxBias().IsEnabled(true);
					}
				}
				else
				{
					//Enable or disable interface
					combobox_SmartShiftMaxMode().IsEnabled(false);
					slider_SmartShiftMaxBias().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				combobox_SmartShiftMaxMode().IsEnabled(false);
				slider_SmartShiftMaxBias().IsEnabled(false);
			}

			//Set result
			AVDebugWriteLine("ADLX loaded power values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading power values.");
		}
	}
}