#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::button_Tuning_Apply_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Disable active overclock setting
			KeepActive_Disable(false);

			//Generate tuning and fans settings
			TuningFanSettings tuningFanSettings = TuningFanSettings_Generate_FromUI(false).value();

			//Apply tuning and fans settings
			if (AdlxApplyTuning(ppGpuInfo, tuningFanSettings))
			{
				//Replace tuning and fans settings
				TuningFanSettings_Profile_Replace(tuningFanSettings);

				//Save tuning and fans settings
				TuningFanSettings_Profiles_SaveToFile();

				//Load tuning values to interface
				AdlxValuesLoadTuning();
			}
		}
		catch (...) {}
	}

	void MainPage::button_Tuning_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Disable active overclock setting
			KeepActive_Disable(false);

			//Reset tuning and fans settings
			if (AdlxResetTuning())
			{
				//Device identifier
				std::wstring device_id_w = AdlxGetGpuIdentifier(ppGpuInfo);

				//Remove tuning and fans settings
				TuningFanSettings_Profile_Remove(device_id_w);

				//Save tuning and fans settings
				TuningFanSettings_Profiles_SaveToFile();

				//Load tuning values to interface
				AdlxValuesLoadTuning();
			}
		}
		catch (...) {}
	}

	void MainPage::button_Tuning_Import_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Import settings from file
			AdlxValuesImportTuning();
		}
		catch (...) {}
	}

	void MainPage::button_Tuning_Export_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Export current settings to file
			AdlxValuesExportTuning();
		}
		catch (...) {}
	}

	void MainPage::slider_Core_Min_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int maxCurrent = (int)slider_Core_Max().Value();
			int minLimits = maxCurrent - 100;
			int minCurrent = (int)slider_Core_Min().Value();
			int maxLimits = minCurrent + 100;

			//Adjust values
			if (minCurrent > minLimits)
			{
				slider_Core_Min().Value(minLimits);
				slider_Core_Max().Value(maxLimits);
			}
		}
		catch (...) {}
	}

	void MainPage::slider_Core_Max_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			if (slider_Core_Min().IsEnabled())
			{
				//Get setting value
				int maxCurrent = (int)slider_Core_Max().Value();
				int minLimits = maxCurrent - 100;
				int minCurrent = (int)slider_Core_Min().Value();
				int maxLimits = minCurrent + 100;

				//Adjust values
				if (minCurrent > minLimits)
				{
					slider_Core_Min().Value(minLimits);
					slider_Core_Max().Value(maxLimits);
				}
			}
		}
		catch (...) {}
	}

	bool MainPage::AdlxApplyTuning(IADLXGPU2Ptr ppGpuPtr, TuningFanSettings tuningFanSettings)
	{
		try
		{
			//Get fan manual tuning
			adlx_Res0 = ppGPUTuningServices->IsSupportedManualFanTuning(ppGpuPtr, &adlx_Bool);
			if (ADLX_SUCCEEDED(adlx_Res0) && adlx_Bool)
			{
				IADLXManualFanTuningPtr ppManualFanTuning;
				adlx_Res0 = ppGPUTuningServices->GetManualFanTuning(ppGpuPtr, (IADLXInterface**)&ppManualFanTuning);

				//Set fan zero rpm setting
				adlx_Res0 = ppManualFanTuning->IsSupportedZeroRPM(&adlx_Bool);
				if (ADLX_SUCCEEDED(adlx_Res0) && adlx_Bool)
				{
					if (tuningFanSettings.FanZeroRpm.has_value())
					{
						adlx_Res0 = ppManualFanTuning->SetZeroRPMState(tuningFanSettings.FanZeroRpm.value());
					}
				}

				//Get empty fan curve
				IADLXManualFanTuningStatePtr ppFanState;
				IADLXManualFanTuningStateListPtr ppFanStates;
				adlx_Res0 = ppManualFanTuning->GetEmptyFanTuningStates(&ppFanStates);
				for (UINT i = 0; i < ppFanStates->Size(); i++)
				{
					ppFanStates->At(i, &ppFanState);
					if (i == 0)
					{
						if (tuningFanSettings.FanSpeed0.has_value())
						{
							adlx_Res0 = ppFanState->SetFanSpeed(tuningFanSettings.FanSpeed0.value());
						}
						if (tuningFanSettings.FanTemp0.has_value())
						{
							adlx_Res0 = ppFanState->SetTemperature(tuningFanSettings.FanTemp0.value());
						}
					}
					else if (i == 1)
					{
						if (tuningFanSettings.FanSpeed1.has_value())
						{
							adlx_Res0 = ppFanState->SetFanSpeed(tuningFanSettings.FanSpeed1.value());
						}
						if (tuningFanSettings.FanTemp1.has_value())
						{
							adlx_Res0 = ppFanState->SetTemperature(tuningFanSettings.FanTemp1.value());
						}
					}
					else if (i == 2)
					{
						if (tuningFanSettings.FanSpeed2.has_value())
						{
							adlx_Res0 = ppFanState->SetFanSpeed(tuningFanSettings.FanSpeed2.value());
						}
						if (tuningFanSettings.FanTemp2.has_value())
						{
							adlx_Res0 = ppFanState->SetTemperature(tuningFanSettings.FanTemp2.value());
						}
					}
					else if (i == 3)
					{
						if (tuningFanSettings.FanSpeed3.has_value())
						{
							adlx_Res0 = ppFanState->SetFanSpeed(tuningFanSettings.FanSpeed3.value());
						}
						if (tuningFanSettings.FanTemp3.has_value())
						{
							adlx_Res0 = ppFanState->SetTemperature(tuningFanSettings.FanTemp3.value());
						}
					}
					else if (i == 4)
					{
						if (tuningFanSettings.FanSpeed4.has_value())
						{
							adlx_Res0 = ppFanState->SetFanSpeed(tuningFanSettings.FanSpeed4.value());
						}
						if (tuningFanSettings.FanTemp4.has_value())
						{
							adlx_Res0 = ppFanState->SetTemperature(tuningFanSettings.FanTemp4.value());
						}
					}
				}

				//Validate fan curve
				adlx_Res0 = ppManualFanTuning->IsValidFanTuningStates(ppFanStates, &adlx_Int0);
				if (ADLX_FAILED(adlx_Res0))
				{
					//Set result
					ShowNotification(L"Invalid fan curve");
					AVDebugWriteLine(L"Invalid fan curve");
					return false;
				}

				//Set fan curve
				adlx_Res0 = ppManualFanTuning->SetFanTuningStates(ppFanStates);
			}

			//Get gpu manual tuning
			adlx_Res0 = ppGPUTuningServices->IsSupportedManualGFXTuning(ppGpuPtr, &adlx_Bool);
			if (ADLX_SUCCEEDED(adlx_Res0) && adlx_Bool)
			{
				IADLXManualGraphicsTuning2_1Ptr ppManualGFXTuning;
				adlx_Res0 = ppGPUTuningServices->GetManualGFXTuning(ppGpuPtr, (IADLXInterface**)&ppManualGFXTuning);

				//Core Frequency Minimum
				if (tuningFanSettings.CoreMin.has_value())
				{
					adlx_Res0 = ppManualGFXTuning->SetGPUMinFrequency(tuningFanSettings.CoreMin.value());
				}

				//Core Frequency Maximum
				if (tuningFanSettings.CoreMax.has_value())
				{
					adlx_Res0 = ppManualGFXTuning->SetGPUMaxFrequency(tuningFanSettings.CoreMax.value());
				}

				//Power Voltage
				if (tuningFanSettings.PowerBoostActive.has_value() && tuningFanSettings.PowerBoostActive.value())
				{
					if (tuningFanSettings.PowerVoltagePB.has_value())
					{
						adlx_Res0 = ppManualGFXTuning->SetGPUVoltage(tuningFanSettings.PowerVoltagePB.value());
					}
				}
				else
				{
					if (tuningFanSettings.PowerVoltage.has_value())
					{
						adlx_Res0 = ppManualGFXTuning->SetGPUVoltage(tuningFanSettings.PowerVoltage.value());
					}
				}
			}

			//Get memory manual tuning
			adlx_Res0 = ppGPUTuningServices->IsSupportedManualVRAMTuning(ppGpuPtr, &adlx_Bool);
			if (ADLX_SUCCEEDED(adlx_Res0) && adlx_Bool)
			{
				IADLXManualVRAMTuning2Ptr ppManualVRAMTuning;
				adlx_Res0 = ppGPUTuningServices->GetManualVRAMTuning(ppGpuPtr, (IADLXInterface**)&ppManualVRAMTuning);

				//Memory Frequency
				if (tuningFanSettings.MemoryMax.has_value())
				{
					adlx_Res0 = ppManualVRAMTuning->SetMaxVRAMFrequency(tuningFanSettings.MemoryMax.value());
				}

				//Memory Timing
				adlx_Res0 = ppManualVRAMTuning->IsSupportedMemoryTiming(&adlx_Bool);
				if (ADLX_SUCCEEDED(adlx_Res0) && adlx_Bool)
				{
					if (tuningFanSettings.MemoryTiming.has_value())
					{
						adlx_Res0 = ppManualVRAMTuning->SetMemoryTimingDescription((ADLX_MEMORYTIMING_DESCRIPTION)tuningFanSettings.MemoryTiming.value());
					}
				}
			}

			//Get power manual tuning
			adlx_Res0 = ppGPUTuningServices->IsSupportedManualPowerTuning(ppGpuPtr, &adlx_Bool);
			if (ADLX_SUCCEEDED(adlx_Res0) && adlx_Bool)
			{
				IADLXManualPowerTuning1Ptr ppManualPowerTuning;
				adlx_Res0 = ppGPUTuningServices->GetManualPowerTuning(ppGpuPtr, (IADLXInterface**)&ppManualPowerTuning);

				//Power Limit
				if (tuningFanSettings.PowerBoostActive.has_value() && tuningFanSettings.PowerBoostActive.value())
				{
					if (tuningFanSettings.PowerLimitPB.has_value())
					{
						adlx_Res0 = ppManualPowerTuning->SetPowerLimit(tuningFanSettings.PowerLimitPB.value());
					}
				}
				else
				{
					if (tuningFanSettings.PowerLimit.has_value())
					{
						adlx_Res0 = ppManualPowerTuning->SetPowerLimit(tuningFanSettings.PowerLimit.value());
					}
				}

				//Power TDC
				adlx_Res0 = ppManualPowerTuning->IsSupportedTDCLimit(&adlx_Bool);
				if (ADLX_SUCCEEDED(adlx_Res0) && adlx_Bool)
				{
					if (tuningFanSettings.PowerBoostActive.has_value() && tuningFanSettings.PowerBoostActive.value())
					{
						if (tuningFanSettings.PowerTDCPB.has_value())
						{
							adlx_Res0 = ppManualPowerTuning->SetTDCLimit(tuningFanSettings.PowerTDCPB.value());
						}
					}
					else
					{
						if (tuningFanSettings.PowerTDC.has_value())
						{
							adlx_Res0 = ppManualPowerTuning->SetTDCLimit(tuningFanSettings.PowerTDC.value());
						}
					}
				}
			}

			//Set result
			ShowNotification(L"Tuning and fans settings applied");
			AVDebugWriteLine(L"Tuning and fans settings applied to gpu.");
			return true;
		}
		catch (...)
		{
			//Set result
			ShowNotification(L"Failed applying tuning and fans settings");
			AVDebugWriteLine(L"Failed applying tuning and fans settings to gpu.");
			return false;
		}
	}
}