#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::button_Tuning_Apply_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			adlx_Bool = AdlxApplyTuning();
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
			AdlxValuesImport();
		}
		catch (...) {}
	}

	void MainPage::button_Tuning_Export_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			AdlxValuesExport();
		}
		catch (...) {}
	}

	bool MainPage::AdlxApplyTuning()
	{
		try
		{
			//Get fan manual tuning
			adlx_Res0 = ppGPUTuningServices->IsSupportedManualFanTuning(ppGpuInfo, &adlx_Bool);
			if (adlx_Bool)
			{
				IADLXManualFanTuningPtr ppManualFanTuning;
				adlx_Res0 = ppGPUTuningServices->GetManualFanTuning(ppGpuInfo, (IADLXInterface**)&ppManualFanTuning);

				//Set fan zero rpm setting
				adlx_Res0 = ppManualFanTuning->IsSupportedZeroRPM(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = ppManualFanTuning->SetZeroRPMState(toggleswitch_Fan_Zero_Rpm().IsOn());
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
						ppFanState->SetFanSpeed((int)slider_Fan_Speed_0().Value());
						ppFanState->SetTemperature((int)slider_Fan_Temp_0().Value());
					}
					else if (i == 1)
					{
						ppFanState->SetFanSpeed((int)slider_Fan_Speed_1().Value());
						ppFanState->SetTemperature((int)slider_Fan_Temp_1().Value());
					}
					else if (i == 2)
					{
						ppFanState->SetFanSpeed((int)slider_Fan_Speed_2().Value());
						ppFanState->SetTemperature((int)slider_Fan_Temp_2().Value());
					}
					else if (i == 3)
					{
						ppFanState->SetFanSpeed((int)slider_Fan_Speed_3().Value());
						ppFanState->SetTemperature((int)slider_Fan_Temp_3().Value());
					}
					else if (i == 4)
					{
						ppFanState->SetFanSpeed((int)slider_Fan_Speed_4().Value());
						ppFanState->SetTemperature((int)slider_Fan_Temp_4().Value());
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
			adlx_Res0 = ppGPUTuningServices->IsSupportedManualGFXTuning(ppGpuInfo, &adlx_Bool);
			if (adlx_Bool)
			{
				IADLXManualGraphicsTuning2Ptr ppManualGFXTuning;
				adlx_Res0 = ppGPUTuningServices->GetManualGFXTuning(ppGpuInfo, (IADLXInterface**)&ppManualGFXTuning);
				adlx_Res0 = ppManualGFXTuning->SetGPUMinFrequency((int)slider_Core_Min().Value());
				adlx_Res0 = ppManualGFXTuning->SetGPUMaxFrequency((int)slider_Core_Max().Value());
				adlx_Res0 = ppManualGFXTuning->SetGPUVoltage((int)slider_Power_Voltage().Value());
			}

			//Get memory manual tuning
			adlx_Res0 = ppGPUTuningServices->IsSupportedManualVRAMTuning(ppGpuInfo, &adlx_Bool);
			if (adlx_Bool)
			{
				IADLXManualVRAMTuning2Ptr ppManualVRAMTuning;
				adlx_Res0 = ppGPUTuningServices->GetManualVRAMTuning(ppGpuInfo, (IADLXInterface**)&ppManualVRAMTuning);
				adlx_Res0 = ppManualVRAMTuning->SetMaxVRAMFrequency((int)slider_Memory_Max().Value());

				adlx_Res0 = ppManualVRAMTuning->IsSupportedMemoryTiming(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = ppManualVRAMTuning->SetMemoryTimingDescription((ADLX_MEMORYTIMING_DESCRIPTION)combobox_Memory_Timing().SelectedIndex());
				}
			}

			//Get power manual tuning
			adlx_Res0 = ppGPUTuningServices->IsSupportedManualPowerTuning(ppGpuInfo, &adlx_Bool);
			if (adlx_Bool)
			{
				IADLXManualPowerTuning1Ptr ppManualPowerTuning;
				adlx_Res0 = ppGPUTuningServices->GetManualPowerTuning(ppGpuInfo, (IADLXInterface**)&ppManualPowerTuning);
				adlx_Res0 = ppManualPowerTuning->SetPowerLimit((int)slider_Power_Limit().Value());

				adlx_Res0 = ppManualPowerTuning->IsSupportedTDCLimit(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = ppManualPowerTuning->SetTDCLimit((int)slider_Power_TDC().Value());
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