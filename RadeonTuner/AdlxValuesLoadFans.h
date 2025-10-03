#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesLoadFans()
	{
		try
		{
			//Check services
			if (ppGPUTuningServices == NULL)
			{
				stackpanel_Fans().Opacity(0.20);
				stackpanel_Fans().IsHitTestVisible(false);
				AVDebugWriteLine("ADLX fans service is not available.");
				return;
			}

			//Get fan manual tuning
			adlx_Res0 = ppGPUTuningServices->IsSupportedManualFanTuning(ppGpuInfo, &adlx_Bool);
			if (adlx_Bool)
			{
				IADLXManualFanTuningPtr ppManualFanTuning;
				adlx_Res0 = ppGPUTuningServices->GetManualFanTuning(ppGpuInfo, (IADLXInterface**)&ppManualFanTuning);

				//Get fan zero rpm setting
				adlx_Res0 = ppManualFanTuning->IsSupportedZeroRPM(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = ppManualFanTuning->GetZeroRPMState(&adlx_Bool);
					toggleswitch_Fan_Zero_Rpm().IsOn(adlx_Bool);

					//Enable or disable interface
					toggleswitch_Fan_Zero_Rpm().IsEnabled(true);

					//Show or hide Zero RPM line
					if (adlx_Bool)
					{
						grid_Fan_Zero_Rpm_Line().Visibility(Visibility::Visible);
					}
					else
					{
						grid_Fan_Zero_Rpm_Line().Visibility(Visibility::Collapsed);
					}
				}
				else
				{
					//Enable or disable interface
					toggleswitch_Fan_Zero_Rpm().IsEnabled(false);

					//Show or hide Zero RPM line
					grid_Fan_Zero_Rpm_Line().Visibility(Visibility::Collapsed);
				}

				//Get fan curve setting
				IADLXManualFanTuningStatePtr ppFanState;
				IADLXManualFanTuningStateListPtr ppFanStates;
				adlx_Res0 = ppManualFanTuning->GetFanTuningStates(&ppFanStates);
				adlx_Res0 = ppManualFanTuning->GetFanTuningRanges(&adlx_IntRange0, &adlx_IntRange1);

				ppFanStates->At(0, &ppFanState);
				adlx_Res0 = ppFanState->GetFanSpeed(&adlx_Int0);
				adlx_Res0 = ppFanState->GetTemperature(&adlx_Int1);
				slider_Fan_Speed_0().Value(adlx_Int0);
				slider_Fan_Speed_0().Minimum(adlx_IntRange0.minValue);
				slider_Fan_Speed_0().Maximum(adlx_IntRange0.maxValue);
				slider_Fan_Speed_0().StepFrequency(adlx_IntRange0.step);
				slider_Fan_Temp_0().Value(adlx_Int1);
				slider_Fan_Temp_0().Minimum(adlx_IntRange0.minValue);
				slider_Fan_Temp_0().Maximum(adlx_IntRange0.maxValue);
				slider_Fan_Temp_0().StepFrequency(adlx_IntRange0.step);

				ppFanStates->At(1, &ppFanState);
				adlx_Res0 = ppFanState->GetFanSpeed(&adlx_Int0);
				adlx_Res0 = ppFanState->GetTemperature(&adlx_Int1);
				slider_Fan_Speed_1().Value(adlx_Int0);
				slider_Fan_Speed_1().Minimum(adlx_IntRange0.minValue);
				slider_Fan_Speed_1().Maximum(adlx_IntRange0.maxValue);
				slider_Fan_Speed_1().StepFrequency(adlx_IntRange0.step);
				slider_Fan_Temp_1().Value(adlx_Int1);
				slider_Fan_Temp_1().Minimum(adlx_IntRange0.minValue);
				slider_Fan_Temp_1().Maximum(adlx_IntRange0.maxValue);
				slider_Fan_Temp_1().StepFrequency(adlx_IntRange0.step);

				ppFanStates->At(2, &ppFanState);
				adlx_Res0 = ppFanState->GetFanSpeed(&adlx_Int0);
				adlx_Res0 = ppFanState->GetTemperature(&adlx_Int1);
				slider_Fan_Speed_2().Value(adlx_Int0);
				slider_Fan_Speed_2().Minimum(adlx_IntRange0.minValue);
				slider_Fan_Speed_2().Maximum(adlx_IntRange0.maxValue);
				slider_Fan_Speed_2().StepFrequency(adlx_IntRange0.step);
				slider_Fan_Temp_2().Value(adlx_Int1);
				slider_Fan_Temp_2().Minimum(adlx_IntRange0.minValue);
				slider_Fan_Temp_2().Maximum(adlx_IntRange0.maxValue);
				slider_Fan_Temp_2().StepFrequency(adlx_IntRange0.step);

				ppFanStates->At(3, &ppFanState);
				adlx_Res0 = ppFanState->GetFanSpeed(&adlx_Int0);
				adlx_Res0 = ppFanState->GetTemperature(&adlx_Int1);
				slider_Fan_Speed_3().Value(adlx_Int0);
				slider_Fan_Speed_3().Minimum(adlx_IntRange0.minValue);
				slider_Fan_Speed_3().Maximum(adlx_IntRange0.maxValue);
				slider_Fan_Speed_3().StepFrequency(adlx_IntRange0.step);
				slider_Fan_Temp_3().Value(adlx_Int1);
				slider_Fan_Temp_3().Minimum(adlx_IntRange0.minValue);
				slider_Fan_Temp_3().Maximum(adlx_IntRange0.maxValue);
				slider_Fan_Temp_3().StepFrequency(adlx_IntRange0.step);

				ppFanStates->At(4, &ppFanState);
				adlx_Res0 = ppFanState->GetFanSpeed(&adlx_Int0);
				adlx_Res0 = ppFanState->GetTemperature(&adlx_Int1);
				slider_Fan_Speed_4().Value(adlx_Int0);
				slider_Fan_Speed_4().Minimum(adlx_IntRange0.minValue);
				slider_Fan_Speed_4().Maximum(adlx_IntRange0.maxValue);
				slider_Fan_Speed_4().StepFrequency(adlx_IntRange0.step);
				slider_Fan_Temp_4().Value(adlx_Int1);
				slider_Fan_Temp_4().Minimum(adlx_IntRange0.minValue);
				slider_Fan_Temp_4().Maximum(adlx_IntRange0.maxValue);
				slider_Fan_Temp_4().StepFrequency(adlx_IntRange0.step);

				//Enable or disable interface
				slider_Fan_Temp_0().IsEnabled(true);
				slider_Fan_Speed_0().IsEnabled(true);
				slider_Fan_Temp_1().IsEnabled(true);
				slider_Fan_Speed_1().IsEnabled(true);
				slider_Fan_Temp_2().IsEnabled(true);
				slider_Fan_Speed_2().IsEnabled(true);
				slider_Fan_Temp_3().IsEnabled(true);
				slider_Fan_Speed_3().IsEnabled(true);
				slider_Fan_Temp_4().IsEnabled(true);
				slider_Fan_Speed_4().IsEnabled(true);
				button_Fan_Apply().IsEnabled(true);
				button_Fan_Reset().IsEnabled(true);
				button_Fan_Import().IsEnabled(true);
				button_Fan_Export().IsEnabled(true);
				button_Fan_Keep().IsEnabled(true);

				//Update fan graph
				UpdateFanGraph();
			}
			else
			{
				//Enable or disable interface
				toggleswitch_Fan_Zero_Rpm().IsEnabled(false);
				slider_Fan_Temp_0().IsEnabled(false);
				slider_Fan_Speed_0().IsEnabled(false);
				slider_Fan_Temp_1().IsEnabled(false);
				slider_Fan_Speed_1().IsEnabled(false);
				slider_Fan_Temp_2().IsEnabled(false);
				slider_Fan_Speed_2().IsEnabled(false);
				slider_Fan_Temp_3().IsEnabled(false);
				slider_Fan_Speed_3().IsEnabled(false);
				slider_Fan_Temp_4().IsEnabled(false);
				slider_Fan_Speed_4().IsEnabled(false);
				button_Fan_Apply().IsEnabled(false);
				button_Fan_Reset().IsEnabled(false);
				button_Fan_Import().IsEnabled(false);
				button_Fan_Export().IsEnabled(false);
				button_Fan_Keep().IsEnabled(false);
			}

			//Set result
			AVDebugWriteLine("ADLX loaded fan values.");
		}
		catch (...)
		{
			//Enable or disable interface
			toggleswitch_Fan_Zero_Rpm().IsEnabled(false);
			slider_Fan_Temp_0().IsEnabled(false);
			slider_Fan_Speed_0().IsEnabled(false);
			slider_Fan_Temp_1().IsEnabled(false);
			slider_Fan_Speed_1().IsEnabled(false);
			slider_Fan_Temp_2().IsEnabled(false);
			slider_Fan_Speed_2().IsEnabled(false);
			slider_Fan_Temp_3().IsEnabled(false);
			slider_Fan_Speed_3().IsEnabled(false);
			slider_Fan_Temp_4().IsEnabled(false);
			slider_Fan_Speed_4().IsEnabled(false);
			button_Fan_Apply().IsEnabled(false);
			button_Fan_Reset().IsEnabled(false);
			button_Fan_Import().IsEnabled(false);
			button_Fan_Export().IsEnabled(false);
			button_Fan_Keep().IsEnabled(false);

			//Set result
			AVDebugWriteLine("ADLX failed loading fan values.");
		}
	}
}