#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::button_Tuning_Apply_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Disable active overclock setting
			KeepActive_Disable();

			//Generate tuning and fans settings
			TuningFanSettings tuningFanSettings = TuningFanSettings_Generate_FromUI(false);

			//Apply tuning and fans settings
			adlx_Bool = AdlxApplyTuning(ppGpuInfo, tuningFanSettings);
			if (adlx_Bool)
			{
				AdlxValuesLoadSelectGpu();
			}
		}
		catch (...) {}
	}

	void MainPage::button_Tuning_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Disable active overclock setting
			KeepActive_Disable();

			//Reset tuning and fans settings
			adlx_Bool = AdlxResetTuning();
			if (adlx_Bool)
			{
				AdlxValuesLoadSelectGpu();
			}
		}
		catch (...) {}
	}

	void MainPage::button_Tuning_Import_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Import settings from file
			AdlxValuesImport();
		}
		catch (...) {}
	}

	void MainPage::button_Tuning_Export_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Export current settings to file
			AdlxValuesExport();
		}
		catch (...) {}
	}

	void MainPage::button_Tuning_Keep_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Export active overclock settings
			KeepActive_Export();
		}
		catch (...) {}
	}

	void MainPage::button_Tuning_Keep_PointerPressed(IInspectable const& sender, PointerRoutedEventArgs const& e)
	{
		try
		{
			if (e.Pointer().PointerDeviceType() == PointerDeviceType::Mouse)
			{
				//Get pointer properties
				PointerPointProperties pointerProps = e.GetCurrentPoint(NULL).Properties();

				//Check which mouse button is pressed
				if (pointerProps.IsRightButtonPressed())
				{
					//Toggle active overclock on or off
					KeepActive_Toggle();
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
			if (adlx_Bool)
			{
				IADLXManualFanTuningPtr ppManualFanTuning;
				adlx_Res0 = ppGPUTuningServices->GetManualFanTuning(ppGpuPtr, (IADLXInterface**)&ppManualFanTuning);

				//Set fan zero rpm setting
				adlx_Res0 = ppManualFanTuning->IsSupportedZeroRPM(&adlx_Bool);
				if (adlx_Bool)
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
							ppFanState->SetFanSpeed(tuningFanSettings.FanSpeed0.value());
						}
						if (tuningFanSettings.FanTemp0.has_value())
						{
							ppFanState->SetTemperature(tuningFanSettings.FanTemp0.value());
						}
					}
					else if (i == 1)
					{
						if (tuningFanSettings.FanSpeed1.has_value())
						{
							ppFanState->SetFanSpeed(tuningFanSettings.FanSpeed1.value());
						}
						if (tuningFanSettings.FanTemp1.has_value())
						{
							ppFanState->SetTemperature(tuningFanSettings.FanTemp1.value());
						}
					}
					else if (i == 2)
					{
						if (tuningFanSettings.FanSpeed2.has_value())
						{
							ppFanState->SetFanSpeed(tuningFanSettings.FanSpeed2.value());
						}
						if (tuningFanSettings.FanTemp2.has_value())
						{
							ppFanState->SetTemperature(tuningFanSettings.FanTemp2.value());
						}
					}
					else if (i == 3)
					{
						if (tuningFanSettings.FanSpeed3.has_value())
						{
							ppFanState->SetFanSpeed(tuningFanSettings.FanSpeed3.value());
						}
						if (tuningFanSettings.FanTemp3.has_value())
						{
							ppFanState->SetTemperature(tuningFanSettings.FanTemp3.value());
						}
					}
					else if (i == 4)
					{
						if (tuningFanSettings.FanSpeed4.has_value())
						{
							ppFanState->SetFanSpeed(tuningFanSettings.FanSpeed4.value());
						}
						if (tuningFanSettings.FanTemp4.has_value())
						{
							ppFanState->SetTemperature(tuningFanSettings.FanTemp4.value());
						}
					}
				}

				//Validate fan curve
				adlx_Res0 = ppManualFanTuning->IsValidFanTuningStates(ppFanStates, &adlx_Int0);
				if (ADLX_FAILED(adlx_Res0))
				{
					//Set result
					textblock_Status().Text(L"Invalid fan curve");
					AVDebugWriteLine(L"Invalid fan curve");
					return false;
				}

				//Set fan curve
				adlx_Res0 = ppManualFanTuning->SetFanTuningStates(ppFanStates);
			}

			//Get gpu manual tuning
			adlx_Res0 = ppGPUTuningServices->IsSupportedManualGFXTuning(ppGpuPtr, &adlx_Bool);
			if (adlx_Bool)
			{
				IADLXManualGraphicsTuning2Ptr ppManualGFXTuning;
				adlx_Res0 = ppGPUTuningServices->GetManualGFXTuning(ppGpuPtr, (IADLXInterface**)&ppManualGFXTuning);
				if (tuningFanSettings.CoreMin.has_value())
				{
					adlx_Res0 = ppManualGFXTuning->SetGPUMinFrequency(tuningFanSettings.CoreMin.value());
				}
				if (tuningFanSettings.CoreMax.has_value())
				{
					adlx_Res0 = ppManualGFXTuning->SetGPUMaxFrequency(tuningFanSettings.CoreMax.value());
				}
				if (tuningFanSettings.PowerVoltage.has_value())
				{
					adlx_Res0 = ppManualGFXTuning->SetGPUVoltage(tuningFanSettings.PowerVoltage.value());
				}
			}

			//Get memory manual tuning
			adlx_Res0 = ppGPUTuningServices->IsSupportedManualVRAMTuning(ppGpuPtr, &adlx_Bool);
			if (adlx_Bool)
			{
				IADLXManualVRAMTuning2Ptr ppManualVRAMTuning;
				adlx_Res0 = ppGPUTuningServices->GetManualVRAMTuning(ppGpuPtr, (IADLXInterface**)&ppManualVRAMTuning);
				if (tuningFanSettings.MemoryMax.has_value())
				{
					adlx_Res0 = ppManualVRAMTuning->SetMaxVRAMFrequency(tuningFanSettings.MemoryMax.value());
				}

				adlx_Res0 = ppManualVRAMTuning->IsSupportedMemoryTiming(&adlx_Bool);
				if (adlx_Bool)
				{
					if (tuningFanSettings.MemoryTiming.has_value())
					{
						adlx_Res0 = ppManualVRAMTuning->SetMemoryTimingDescription((ADLX_MEMORYTIMING_DESCRIPTION)tuningFanSettings.MemoryTiming.value());
					}
				}
			}

			//Get power manual tuning
			adlx_Res0 = ppGPUTuningServices->IsSupportedManualPowerTuning(ppGpuPtr, &adlx_Bool);
			if (adlx_Bool)
			{
				IADLXManualPowerTuning1Ptr ppManualPowerTuning;
				adlx_Res0 = ppGPUTuningServices->GetManualPowerTuning(ppGpuPtr, (IADLXInterface**)&ppManualPowerTuning);
				if (tuningFanSettings.PowerLimit.has_value())
				{
					adlx_Res0 = ppManualPowerTuning->SetPowerLimit(tuningFanSettings.PowerLimit.value());
				}

				adlx_Res0 = ppManualPowerTuning->IsSupportedTDCLimit(&adlx_Bool);
				if (adlx_Bool)
				{
					if (tuningFanSettings.PowerTDC.has_value())
					{
						adlx_Res0 = ppManualPowerTuning->SetTDCLimit(tuningFanSettings.PowerTDC.value());
					}
				}
			}

			//Set result
			textblock_Status().Text(L"Tuning and fans applied");
			AVDebugWriteLine(L"Tuning and fans applied");
			return true;
		}
		catch (...)
		{
			//Set result
			textblock_Status().Text(L"Failed applying tuning and fans");
			AVDebugWriteLine(L"Failed applying tuning and fans");
			return false;
		}
	}
}