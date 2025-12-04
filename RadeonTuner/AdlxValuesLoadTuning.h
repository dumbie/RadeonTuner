#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesLoadTuning()
	{
		try
		{
			//Check services
			if (ppGPUTuningServices == NULL)
			{
				stackpanel_Tuning().Opacity(0.20);
				stackpanel_Tuning().IsHitTestVisible(false);
				AVDebugWriteLine("ADLX tuning service is not available.");
				return;
			}

			//Variables
			BOOL supportedManualGFXTuning = false;
			BOOL supportedManualVRAMTuning = false;
			BOOL supportedManualPowerTuning = false;

			//Get gpu manual tuning
			try
			{
				adlx_Res0 = ppGPUTuningServices->IsSupportedManualGFXTuning(ppGpuInfo, &adlx_Bool);
				supportedManualGFXTuning = adlx_Bool;
				if (adlx_Bool)
				{
					IADLXManualGraphicsTuning2Ptr ppManualGFXTuning;
					adlx_Res0 = ppGPUTuningServices->GetManualGFXTuning(ppGpuInfo, (IADLXInterface**)&ppManualGFXTuning);

					//Note: some gpus seem to return ADLX_NOT_SUPPORTED when reading frequency returning 0 or 1 values
					adlx_Res0 = ppManualGFXTuning->GetGPUMinFrequencyRange(&adlx_IntRange0);
					if (ADLX_SUCCEEDED(adlx_Res0))
					{
						slider_Core_Min().Minimum(adlx_IntRange0.minValue);
						slider_Core_Min().Maximum(adlx_IntRange0.maxValue);
						slider_Core_Min().StepFrequency(adlx_IntRange0.step);

						adlx_Res0 = ppManualGFXTuning->GetGPUMinFrequency(&adlx_Int0);
						slider_Core_Min().Value(adlx_Int0);

						//Enable or disable interface
						slider_Core_Min().IsEnabled(true);
					}
					else
					{
						//Enable or disable interface
						slider_Core_Min().IsEnabled(false);
					}

					adlx_Res0 = ppManualGFXTuning->GetGPUMaxFrequencyRange(&adlx_IntRange0);
					if (ADLX_SUCCEEDED(adlx_Res0))
					{
						slider_Core_Max().Minimum(adlx_IntRange0.minValue);
						slider_Core_Max().Maximum(adlx_IntRange0.maxValue);
						slider_Core_Max().StepFrequency(adlx_IntRange0.step);

						adlx_Res0 = ppManualGFXTuning->GetGPUMaxFrequency(&adlx_Int0);
						slider_Core_Max().Value(adlx_Int0);

						//Enable or disable interface
						slider_Core_Max().IsEnabled(true);
					}
					else
					{
						//Enable or disable interface
						slider_Core_Max().IsEnabled(false);
					}

					adlx_Res0 = ppManualGFXTuning->GetGPUVoltageRange(&adlx_IntRange0);
					if (ADLX_SUCCEEDED(adlx_Res0))
					{
						slider_Power_Voltage().Minimum(adlx_IntRange0.minValue);
						slider_Power_Voltage().Maximum(adlx_IntRange0.maxValue);
						slider_Power_Voltage().StepFrequency(adlx_IntRange0.step);

						adlx_Res0 = ppManualGFXTuning->GetGPUVoltage(&adlx_Int0);
						slider_Power_Voltage().Value(adlx_Int0);

						//Enable or disable interface
						slider_Power_Voltage().IsEnabled(true);
					}
					else
					{
						//Enable or disable interface
						slider_Power_Voltage().IsEnabled(false);
					}
				}
				else
				{
					//Enable or disable interface
					slider_Core_Min().IsEnabled(false);
					slider_Core_Max().IsEnabled(false);
					slider_Power_Voltage().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				slider_Core_Min().IsEnabled(false);
				slider_Core_Max().IsEnabled(false);
				slider_Power_Voltage().IsEnabled(false);
			}

			//Get memory manual tuning
			try
			{
				adlx_Res0 = ppGPUTuningServices->IsSupportedManualVRAMTuning(ppGpuInfo, &adlx_Bool);
				supportedManualVRAMTuning = adlx_Bool;
				if (adlx_Bool)
				{
					IADLXManualVRAMTuning2Ptr ppManualVRAMTuning;
					adlx_Res0 = ppGPUTuningServices->GetManualVRAMTuning(ppGpuInfo, (IADLXInterface**)&ppManualVRAMTuning);

					adlx_Res0 = ppManualVRAMTuning->GetMaxVRAMFrequencyRange(&adlx_IntRange0);
					if (ADLX_SUCCEEDED(adlx_Res0))
					{
						slider_Memory_Max().Minimum(adlx_IntRange0.minValue);
						slider_Memory_Max().Maximum(adlx_IntRange0.maxValue);
						slider_Memory_Max().StepFrequency(adlx_IntRange0.step);

						adlx_Res0 = ppManualVRAMTuning->GetMaxVRAMFrequency(&adlx_Int0);
						slider_Memory_Max().Value(adlx_Int0);

						//Enable or disable interface
						slider_Memory_Max().IsEnabled(true);
					}
					else
					{
						//Enable or disable interface
						slider_Memory_Max().IsEnabled(false);
					}

					//Get memory timing settting
					adlx_Res0 = ppManualVRAMTuning->IsSupportedMemoryTiming(&adlx_Bool);
					if (adlx_Bool)
					{
						ADLX_MEMORYTIMING_DESCRIPTION memoryTimingDescription;
						adlx_Res0 = ppManualVRAMTuning->GetMemoryTimingDescription(&memoryTimingDescription);
						if (ADLX_SUCCEEDED(adlx_Res0))
						{
							combobox_Memory_Timing().SelectedIndex(memoryTimingDescription);

							//Enable or disable interface
							combobox_Memory_Timing().IsEnabled(true);
						}
						else
						{
							//Enable or disable interface
							combobox_Memory_Timing().IsEnabled(false);
						}
					}
					else
					{
						//Enable or disable interface
						combobox_Memory_Timing().IsEnabled(false);
					}
				}
				else
				{
					//Enable or disable interface
					slider_Memory_Max().IsEnabled(false);
					combobox_Memory_Timing().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				slider_Memory_Max().IsEnabled(false);
				combobox_Memory_Timing().IsEnabled(false);
			}

			//Get power manual tuning
			try
			{
				adlx_Res0 = ppGPUTuningServices->IsSupportedManualPowerTuning(ppGpuInfo, &adlx_Bool);
				supportedManualPowerTuning = adlx_Bool;
				if (adlx_Bool)
				{
					IADLXManualPowerTuning1Ptr ppManualPowerTuning;
					adlx_Res0 = ppGPUTuningServices->GetManualPowerTuning(ppGpuInfo, (IADLXInterface**)&ppManualPowerTuning);

					adlx_Res0 = ppManualPowerTuning->GetPowerLimitRange(&adlx_IntRange0);
					if (ADLX_SUCCEEDED(adlx_Res0))
					{
						slider_Power_Limit().Minimum(adlx_IntRange0.minValue);
						slider_Power_Limit().Maximum(adlx_IntRange0.maxValue);
						slider_Power_Limit().StepFrequency(adlx_IntRange0.step);

						adlx_Res0 = ppManualPowerTuning->GetPowerLimit(&adlx_Int0);
						slider_Power_Limit().Value(adlx_Int0);

						//Enable or disable interface
						slider_Power_Limit().IsEnabled(true);
					}
					else
					{
						//Enable or disable interface
						slider_Power_Limit().IsEnabled(false);
					}

					//Get power tdc settting
					adlx_Res0 = ppManualPowerTuning->IsSupportedTDCLimit(&adlx_Bool);
					if (adlx_Bool)
					{
						adlx_Res0 = ppManualPowerTuning->GetTDCLimitRange(&adlx_IntRange0);
						if (ADLX_SUCCEEDED(adlx_Res0))
						{
							slider_Power_TDC().Minimum(adlx_IntRange0.minValue);
							slider_Power_TDC().Maximum(adlx_IntRange0.maxValue);
							slider_Power_TDC().StepFrequency(adlx_IntRange0.step);

							adlx_Res0 = ppManualPowerTuning->GetTDCLimit(&adlx_Int0);
							slider_Power_TDC().Value(adlx_Int0);

							//Enable or disable interface
							slider_Power_TDC().IsEnabled(true);
						}
						else
						{
							//Enable or disable interface
							slider_Power_TDC().IsEnabled(false);
						}
					}
					else
					{
						//Enable or disable interface
						slider_Power_TDC().IsEnabled(false);
					}
				}
				else
				{
					//Enable or disable interface
					slider_Power_Limit().IsEnabled(false);
					slider_Power_TDC().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				slider_Power_Limit().IsEnabled(false);
				slider_Power_TDC().IsEnabled(false);
			}

			//Enable or disable interface
			if (!supportedManualGFXTuning && !supportedManualVRAMTuning && !supportedManualPowerTuning)
			{
				button_Tuning_Apply().IsEnabled(false);
				button_Tuning_Reset().IsEnabled(false);
				button_Tuning_Import().IsEnabled(false);
				button_Tuning_Export().IsEnabled(false);
				button_Tuning_Keep().IsEnabled(false);
			}
			else
			{
				button_Tuning_Apply().IsEnabled(true);
				button_Tuning_Reset().IsEnabled(true);
				button_Tuning_Import().IsEnabled(true);
				button_Tuning_Export().IsEnabled(true);
				button_Tuning_Keep().IsEnabled(true);
			}

			//Set result
			AVDebugWriteLine("ADLX loaded tuning values.");
		}
		catch (...)
		{
			//Enable or disable interface
			slider_Core_Min().IsEnabled(false);
			slider_Core_Max().IsEnabled(false);
			slider_Power_Voltage().IsEnabled(false);
			slider_Memory_Max().IsEnabled(false);
			combobox_Memory_Timing().IsEnabled(false);
			slider_Power_Limit().IsEnabled(false);
			slider_Power_TDC().IsEnabled(false);
			button_Tuning_Apply().IsEnabled(false);
			button_Tuning_Reset().IsEnabled(false);
			button_Tuning_Import().IsEnabled(false);
			button_Tuning_Export().IsEnabled(false);
			button_Tuning_Keep().IsEnabled(false);

			//Set result
			AVDebugWriteLine("ADLX failed loading tuning values.");
		}
	}
}