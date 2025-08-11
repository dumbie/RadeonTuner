#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::AdlxValuesLoad()
	{
		//Disable saving
		disable_saving = true;

		//Get selected GPU
		int selectedGpuIndex = combobox_GpuSelect().SelectedIndex();
		ppGpuList->At(selectedGpuIndex, (IADLXGPU**)&ppGpuInfo);
		if (ppGpuInfo == nullptr)
		{
			AVDebugWriteLine("Failed getting selected gpu.");
			return;
		}

		//Get selected display
		int selectedDisplayIndex = combobox_DisplaySelect().SelectedIndex();
		ppDisplayList->At(selectedDisplayIndex, &ppDisplayInfo);
		if (ppDisplayInfo == nullptr)
		{
			AVDebugWriteLine("Failed getting selected display.");
			return;
		}

		//Get chill setting
		IADLX3DChillPtr pp3DChill;
		adlx_Res0 = pp3DSettingsServices->GetChill(ppGpuInfo, &pp3DChill);
		adlx_Res0 = pp3DChill->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			adlx_Res0 = pp3DChill->IsEnabled(&adlx_Bool);
			adlx_Res0 = pp3DChill->GetMinFPS(&adlx_Int0);
			adlx_Res0 = pp3DChill->GetMaxFPS(&adlx_Int1);
			adlx_Res0 = pp3DChill->GetFPSRange(&adlx_IntRange0);

			toggleswitch_RadeonChill().IsOn(adlx_Bool);
			slider_RadeonChill_Min().Value(adlx_Int0);
			slider_RadeonChill_Min().Minimum(adlx_IntRange0.minValue);
			slider_RadeonChill_Min().Maximum(adlx_IntRange0.maxValue);
			slider_RadeonChill_Min().StepFrequency(adlx_IntRange0.step);
			slider_RadeonChill_Max().Value(adlx_Int1);
			slider_RadeonChill_Max().Minimum(adlx_IntRange0.minValue);
			slider_RadeonChill_Max().Maximum(adlx_IntRange0.maxValue);
			slider_RadeonChill_Max().StepFrequency(adlx_IntRange0.step);

			if (!adlx_Bool)
			{
				slider_RadeonChill_Min().IsEnabled(false);
				slider_RadeonChill_Max().IsEnabled(false);
			}
		}
		else
		{
			toggleswitch_RadeonChill().IsEnabled(false);
			slider_RadeonChill_Min().IsEnabled(false);
			slider_RadeonChill_Max().IsEnabled(false);
		}

		//Get vertical refresh setting
		IADLX3DWaitForVerticalRefreshPtr pp3DWaitForVerticalRefresh;
		adlx_Res0 = pp3DSettingsServices->GetWaitForVerticalRefresh(ppGpuInfo, &pp3DWaitForVerticalRefresh);
		adlx_Res0 = pp3DWaitForVerticalRefresh->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE verticalRefreshMode;
			adlx_Res0 = pp3DWaitForVerticalRefresh->GetMode(&verticalRefreshMode);
			combobox_VerticalRefresh().SelectedIndex(verticalRefreshMode);
		}
		else
		{
			combobox_VerticalRefresh().IsEnabled(false);
		}

		//Get enhanced sync setting
		IADLX3DEnhancedSyncPtr pp3DEnhancedSync;
		adlx_Res0 = pp3DSettingsServices->GetEnhancedSync(ppGpuInfo, &pp3DEnhancedSync);
		adlx_Res0 = pp3DEnhancedSync->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			adlx_Res0 = pp3DEnhancedSync->IsEnabled(&adlx_Bool);
			toggleswitch_EnhancedSync().IsOn(adlx_Bool);
		}
		else
		{
			toggleswitch_EnhancedSync().IsEnabled(false);
		}

		//Get display freesync setting
		IADLXDisplayFreeSyncPtr ppFreeSync;
		adlx_Res0 = ppDispServices->GetFreeSync(ppDisplayInfo, &ppFreeSync);
		adlx_Res0 = ppFreeSync->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			adlx_Res0 = ppFreeSync->IsEnabled(&adlx_Bool);
			toggleswitch_FreeSync().IsOn(adlx_Bool);
		}
		else
		{
			toggleswitch_FreeSync().IsEnabled(false);
		}

		//Get display color depth
		IADLXDisplayColorDepthPtr ppColorDepth;
		adlx_Res0 = ppDispServices->GetColorDepth(ppDisplayInfo, &ppColorDepth);
		adlx_Res0 = ppColorDepth->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			ADLX_COLOR_DEPTH colorDepth;
			adlx_Res0 = ppColorDepth->GetValue(&colorDepth);
			if (colorDepth != ADLX_COLOR_DEPTH::BPC_UNKNOWN)
			{
				combobox_Display_ColorDepth().SelectedIndex(colorDepth - 1);
			}
		}
		else
		{
			combobox_Display_ColorDepth().IsEnabled(false);
		}

		//Get display pixel format
		IADLXDisplayPixelFormatPtr ppPixelFormat;
		adlx_Res0 = ppDispServices->GetPixelFormat(ppDisplayInfo, &ppPixelFormat);
		adlx_Res0 = ppPixelFormat->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			ADLX_PIXEL_FORMAT pixelFormat;
			adlx_Res0 = ppPixelFormat->GetValue(&pixelFormat);
			if (pixelFormat != ADLX_PIXEL_FORMAT::FORMAT_UNKNOWN)
			{
				combobox_Display_PixelFormat().SelectedIndex(pixelFormat - 1);
			}
		}
		else
		{
			combobox_Display_PixelFormat().IsEnabled(false);
		}

		//Get display custom color profile
		IADLXDisplayCustomColorPtr ppCustomColor;
		adlx_Res0 = ppDispServices->GetCustomColor(ppDisplayInfo, &ppCustomColor);

		//Get display contrast
		adlx_Res0 = ppCustomColor->IsContrastSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			adlx_Res0 = ppCustomColor->GetContrast(&adlx_Int0);
			adlx_Res0 = ppCustomColor->GetContrastRange(&adlx_IntRange0);
			slider_Display_Contrast().Value(adlx_Int0);
			slider_Display_Contrast().Minimum(adlx_IntRange0.minValue);
			slider_Display_Contrast().Maximum(adlx_IntRange0.maxValue);
			slider_Display_Contrast().StepFrequency(adlx_IntRange0.step);
		}
		else
		{
			slider_Display_Contrast().IsEnabled(false);
		}

		//Get display saturation
		adlx_Res0 = ppCustomColor->IsSaturationSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			adlx_Res0 = ppCustomColor->GetSaturation(&adlx_Int0);
			adlx_Res0 = ppCustomColor->GetSaturationRange(&adlx_IntRange0);
			slider_Display_Saturation().Value(adlx_Int0);
			slider_Display_Saturation().Minimum(adlx_IntRange0.minValue);
			slider_Display_Saturation().Maximum(adlx_IntRange0.maxValue);
			slider_Display_Saturation().StepFrequency(adlx_IntRange0.step);
		}
		else
		{
			slider_Display_Saturation().IsEnabled(false);
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
			}
			else
			{
				toggleswitch_Fan_Zero_Rpm().IsEnabled(false);
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

			//Update fan graph
			UpdateFanGraph();
		}
		else
		{
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
			toggleswitch_Fan_Zero_Rpm().IsEnabled(false);
		}

		//Get gpu manual tuning
		adlx_Res0 = ppGPUTuningServices->IsSupportedManualGFXTuning(ppGpuInfo, &adlx_Bool);
		if (adlx_Bool)
		{
			IADLXManualGraphicsTuning2Ptr ppManualGFXTuning;
			adlx_Res0 = ppGPUTuningServices->GetManualGFXTuning(ppGpuInfo, (IADLXInterface**)&ppManualGFXTuning);

			adlx_Res0 = ppManualGFXTuning->GetGPUMinFrequencyRange(&adlx_IntRange0);
			slider_Core_Min().Minimum(adlx_IntRange0.minValue);
			slider_Core_Min().Maximum(adlx_IntRange0.maxValue);
			slider_Core_Min().StepFrequency(adlx_IntRange0.step);

			adlx_Res0 = ppManualGFXTuning->GetGPUMinFrequency(&adlx_Int0);
			slider_Core_Min().Value(adlx_Int0);

			adlx_Res0 = ppManualGFXTuning->GetGPUMaxFrequencyRange(&adlx_IntRange0);
			slider_Core_Max().Minimum(adlx_IntRange0.minValue);
			slider_Core_Max().Maximum(adlx_IntRange0.maxValue);
			slider_Core_Max().StepFrequency(adlx_IntRange0.step);

			adlx_Res0 = ppManualGFXTuning->GetGPUMaxFrequency(&adlx_Int0);
			slider_Core_Max().Value(adlx_Int0);

			adlx_Res0 = ppManualGFXTuning->GetGPUVoltageRange(&adlx_IntRange0);
			slider_Power_Voltage().Minimum(adlx_IntRange0.minValue);
			slider_Power_Voltage().Maximum(adlx_IntRange0.maxValue);
			slider_Power_Voltage().StepFrequency(adlx_IntRange0.step);

			adlx_Res0 = ppManualGFXTuning->GetGPUVoltage(&adlx_Int0);
			slider_Power_Voltage().Value(adlx_Int0);
		}
		else
		{
			slider_Core_Min().IsEnabled(false);
			slider_Core_Max().IsEnabled(false);
			slider_Power_Voltage().IsEnabled(false);
		}

		//Get memory manual tuning
		adlx_Res0 = ppGPUTuningServices->IsSupportedManualVRAMTuning(ppGpuInfo, &adlx_Bool);
		if (adlx_Bool)
		{
			IADLXManualVRAMTuning2Ptr ppManualVRAMTuning;
			adlx_Res0 = ppGPUTuningServices->GetManualVRAMTuning(ppGpuInfo, (IADLXInterface**)&ppManualVRAMTuning);

			adlx_Res0 = ppManualVRAMTuning->GetMaxVRAMFrequencyRange(&adlx_IntRange0);
			slider_Memory_Max().Minimum(adlx_IntRange0.minValue);
			slider_Memory_Max().Maximum(adlx_IntRange0.maxValue);
			slider_Memory_Max().StepFrequency(adlx_IntRange0.step);

			adlx_Res0 = ppManualVRAMTuning->GetMaxVRAMFrequency(&adlx_Int0);
			slider_Memory_Max().Value(adlx_Int0);

			//Get memory timing settting
			adlx_Res0 = ppManualVRAMTuning->IsSupportedMemoryTiming(&adlx_Bool);
			if (adlx_Bool)
			{
				ADLX_MEMORYTIMING_DESCRIPTION memoryTimingDescription;
				adlx_Res0 = ppManualVRAMTuning->GetMemoryTimingDescription(&memoryTimingDescription);
				combobox_Memory_Timing().SelectedIndex(memoryTimingDescription);
			}
			else
			{
				combobox_Memory_Timing().IsEnabled(false);
			}
		}
		else
		{
			slider_Memory_Max().IsEnabled(false);
			combobox_Memory_Timing().IsEnabled(false);
		}

		//Get power manual tuning
		adlx_Res0 = ppGPUTuningServices->IsSupportedManualPowerTuning(ppGpuInfo, &adlx_Bool);
		if (adlx_Bool)
		{
			IADLXManualPowerTuning1Ptr ppManualPowerTuning;
			adlx_Res0 = ppGPUTuningServices->GetManualPowerTuning(ppGpuInfo, (IADLXInterface**)&ppManualPowerTuning);

			adlx_Res0 = ppManualPowerTuning->GetPowerLimitRange(&adlx_IntRange0);
			slider_Power_Limit().Minimum(adlx_IntRange0.minValue);
			slider_Power_Limit().Maximum(adlx_IntRange0.maxValue);
			slider_Power_Limit().StepFrequency(adlx_IntRange0.step);

			adlx_Res0 = ppManualPowerTuning->GetPowerLimit(&adlx_Int0);
			slider_Power_Limit().Value(adlx_Int0);

			//Get power tdc settting
			adlx_Res0 = ppManualPowerTuning->IsSupportedTDCLimit(&adlx_Bool);
			if (adlx_Bool)
			{
				adlx_Res0 = ppManualPowerTuning->GetTDCLimitRange(&adlx_IntRange0);
				slider_Power_TDC().Minimum(adlx_IntRange0.minValue);
				slider_Power_TDC().Maximum(adlx_IntRange0.maxValue);
				slider_Power_TDC().StepFrequency(adlx_IntRange0.step);

				adlx_Res0 = ppManualPowerTuning->GetTDCLimit(&adlx_Int0);
				slider_Power_TDC().Value(adlx_Int0);
			}
			else
			{
				slider_Power_TDC().IsEnabled(false);
			}
		}
		else
		{
			slider_Power_Limit().IsEnabled(false);
			slider_Power_TDC().IsEnabled(false);
		}

		//Enable saving
		std::thread threadEnableSaving([]()
			{
				Sleep(1000);
				disable_saving = false;
			});
		threadEnableSaving.detach();

		//Set result
		AVDebugWriteLine("ADLX loaded values.");
	}
}