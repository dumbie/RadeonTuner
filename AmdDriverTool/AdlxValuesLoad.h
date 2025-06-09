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
		adlx_Res0 = ppGpuList->At(selectedGpuIndex, (IADLXGPU**)&ppGpuInfo);
		if (ADLX_FAILED(adlx_Res0))
		{
			AVDebugWriteLine("Failed getting selected gpu.");
			return;
		}

		//Get selected display
		int selectedDisplayIndex = combobox_DisplaySelect().SelectedIndex();
		adlx_Res0 = ppDisplayList->At(selectedDisplayIndex, &ppDisplayInfo);
		if (ADLX_FAILED(adlx_Res0))
		{
			AVDebugWriteLine("Failed getting selected display.");
			return;
		}

		//Get chill setting
		IADLX3DChillPtr pp3DChill;
		adlx_Res0 = pp3DSettingsServices->GetChill(ppGpuInfo, &pp3DChill);
		adlx_Res0 = pp3DChill->IsEnabled(&adlx_Bool);
		adlx_Res0 = pp3DChill->GetMinFPS(&adlx_Int0);
		adlx_Res0 = pp3DChill->GetMaxFPS(&adlx_Int1);
		adlx_Res0 = pp3DChill->GetFPSRange(&adlx_IntRange0);
		toggleswitch_RadeonChill().IsOn(adlx_Bool);
		slider_RadeonChill_Min().Value(adlx_Int0);
		slider_RadeonChill_Min().Minimum(adlx_IntRange0.minValue);
		slider_RadeonChill_Min().Maximum(adlx_IntRange0.maxValue);
		slider_RadeonChill_Max().Value(adlx_Int1);
		slider_RadeonChill_Max().Minimum(adlx_IntRange0.minValue);
		slider_RadeonChill_Max().Maximum(adlx_IntRange0.maxValue);
		if (!adlx_Bool)
		{
			slider_RadeonChill_Min().IsEnabled(false);
			slider_RadeonChill_Max().IsEnabled(false);
		}

		//Get vertical refresh setting
		IADLX3DWaitForVerticalRefreshPtr pp3DWaitForVerticalRefresh;
		adlx_Res0 = pp3DSettingsServices->GetWaitForVerticalRefresh(ppGpuInfo, &pp3DWaitForVerticalRefresh);
		ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE verticalRefreshMode;
		pp3DWaitForVerticalRefresh->GetMode(&verticalRefreshMode);
		combobox_VerticalRefresh().SelectedIndex(verticalRefreshMode);

		//Get enhanced sync
		IADLX3DEnhancedSyncPtr pp3DEnhancedSync;
		adlx_Res0 = pp3DSettingsServices->GetEnhancedSync(ppGpuInfo, &pp3DEnhancedSync);
		pp3DEnhancedSync->IsEnabled(&adlx_Bool);
		toggleswitch_EnhancedSync().IsOn(adlx_Bool);

		//Get fan manual tuning
		IADLXManualFanTuningPtr ppManualFanTuning;
		ppGPUTuningServices->GetManualFanTuning(ppGpuInfo, (IADLXInterface**)&ppManualFanTuning);

		//Get fan zero rpm setting
		ppManualFanTuning->GetZeroRPMState(&adlx_Bool);
		toggleswitch_Fan_Zero_Rpm().IsOn(adlx_Bool);

		//Get fan curve setting
		IADLXManualFanTuningStatePtr ppFanState;
		IADLXManualFanTuningStateListPtr ppFanStates;
		ppManualFanTuning->GetFanTuningStates(&ppFanStates);
		ppManualFanTuning->GetFanTuningRanges(&adlx_IntRange0, &adlx_IntRange1);

		ppFanStates->At(0, &ppFanState);
		ppFanState->GetFanSpeed(&adlx_Int0);
		ppFanState->GetTemperature(&adlx_Int1);
		slider_Fan_Speed_0().Value(adlx_Int0);
		slider_Fan_Speed_0().Minimum(adlx_IntRange0.minValue);
		slider_Fan_Speed_0().Maximum(adlx_IntRange0.maxValue);
		slider_Fan_Temp_0().Value(adlx_Int1);
		slider_Fan_Temp_0().Minimum(adlx_IntRange0.minValue);
		slider_Fan_Temp_0().Maximum(adlx_IntRange0.maxValue);

		ppFanStates->At(1, &ppFanState);
		ppFanState->GetFanSpeed(&adlx_Int0);
		ppFanState->GetTemperature(&adlx_Int1);
		slider_Fan_Speed_1().Value(adlx_Int0);
		slider_Fan_Speed_1().Minimum(adlx_IntRange0.minValue);
		slider_Fan_Speed_1().Maximum(adlx_IntRange0.maxValue);
		slider_Fan_Temp_1().Value(adlx_Int1);
		slider_Fan_Temp_1().Minimum(adlx_IntRange0.minValue);
		slider_Fan_Temp_1().Maximum(adlx_IntRange0.maxValue);

		ppFanStates->At(2, &ppFanState);
		ppFanState->GetFanSpeed(&adlx_Int0);
		ppFanState->GetTemperature(&adlx_Int1);
		slider_Fan_Speed_2().Value(adlx_Int0);
		slider_Fan_Speed_2().Minimum(adlx_IntRange0.minValue);
		slider_Fan_Speed_2().Maximum(adlx_IntRange0.maxValue);
		slider_Fan_Temp_2().Value(adlx_Int1);
		slider_Fan_Temp_2().Minimum(adlx_IntRange0.minValue);
		slider_Fan_Temp_2().Maximum(adlx_IntRange0.maxValue);

		ppFanStates->At(3, &ppFanState);
		ppFanState->GetFanSpeed(&adlx_Int0);
		ppFanState->GetTemperature(&adlx_Int1);
		slider_Fan_Speed_3().Value(adlx_Int0);
		slider_Fan_Speed_3().Minimum(adlx_IntRange0.minValue);
		slider_Fan_Speed_3().Maximum(adlx_IntRange0.maxValue);
		slider_Fan_Temp_3().Value(adlx_Int1);
		slider_Fan_Temp_3().Minimum(adlx_IntRange0.minValue);
		slider_Fan_Temp_3().Maximum(adlx_IntRange0.maxValue);

		ppFanStates->At(4, &ppFanState);
		ppFanState->GetFanSpeed(&adlx_Int0);
		ppFanState->GetTemperature(&adlx_Int1);
		slider_Fan_Speed_4().Value(adlx_Int0);
		slider_Fan_Speed_4().Minimum(adlx_IntRange0.minValue);
		slider_Fan_Speed_4().Maximum(adlx_IntRange0.maxValue);
		slider_Fan_Temp_4().Value(adlx_Int1);
		slider_Fan_Temp_4().Minimum(adlx_IntRange0.minValue);
		slider_Fan_Temp_4().Maximum(adlx_IntRange0.maxValue);

		//Update fan graph
		UpdateFanGraph();

		//Get freesync setting
		IADLXDisplayFreeSyncPtr ppFreeSync;
		adlx_Res0 = ppDispServices->GetFreeSync(ppDisplayInfo, &ppFreeSync);
		adlx_Res0 = ppFreeSync->IsEnabled(&adlx_Bool);
		toggleswitch_FreeSync().IsOn(adlx_Bool);

		//Get gpu clock setting
		IADLXManualGraphicsTuning2Ptr ppManualGFXTuning;
		adlx_Res0 = ppGPUTuningServices->GetManualGFXTuning(ppGpuInfo, (IADLXInterface**)&ppManualGFXTuning);

		adlx_Res0 = ppManualGFXTuning->GetGPUMinFrequencyRange(&adlx_IntRange0);
		slider_Core_Min().Minimum(adlx_IntRange0.minValue);
		slider_Core_Min().Maximum(adlx_IntRange0.maxValue);

		adlx_Res0 = ppManualGFXTuning->GetGPUMinFrequency(&adlx_Int0);
		slider_Core_Min().Value(adlx_Int0);

		adlx_Res0 = ppManualGFXTuning->GetGPUMaxFrequencyRange(&adlx_IntRange0);
		slider_Core_Max().Minimum(adlx_IntRange0.minValue);
		slider_Core_Max().Maximum(adlx_IntRange0.maxValue);

		adlx_Res0 = ppManualGFXTuning->GetGPUMaxFrequency(&adlx_Int0);
		slider_Core_Max().Value(adlx_Int0);

		adlx_Res0 = ppManualGFXTuning->GetGPUVoltageRange(&adlx_IntRange0);
		slider_Power_Voltage().Minimum(adlx_IntRange0.minValue);
		slider_Power_Voltage().Maximum(adlx_IntRange0.maxValue);

		adlx_Res0 = ppManualGFXTuning->GetGPUVoltage(&adlx_Int0);
		slider_Power_Voltage().Value(adlx_Int0);

		//Get gpu memory setting
		IADLXManualVRAMTuning2Ptr ppManualVRAMTuning;
		adlx_Res0 = ppGPUTuningServices->GetManualVRAMTuning(ppGpuInfo, (IADLXInterface**)&ppManualVRAMTuning);

		adlx_Res0 = ppManualVRAMTuning->GetMaxVRAMFrequencyRange(&adlx_IntRange0);
		slider_Memory_Max().Minimum(adlx_IntRange0.minValue);
		slider_Memory_Max().Maximum(adlx_IntRange0.maxValue);
		slider_Memory_Max().StepFrequency(adlx_IntRange0.step);

		adlx_Res0 = ppManualVRAMTuning->GetMaxVRAMFrequency(&adlx_Int0);
		slider_Memory_Max().Value(adlx_Int0);

		ADLX_MEMORYTIMING_DESCRIPTION memoryTimingDescription;
		adlx_Res0 = ppManualVRAMTuning->GetMemoryTimingDescription(&memoryTimingDescription);
		combobox_Memory_Timing().SelectedIndex(memoryTimingDescription);

		//Get gpu power setting
		IADLXManualPowerTuningPtr ppManualPowerTuning;
		adlx_Res0 = ppGPUTuningServices->GetManualPowerTuning(ppGpuInfo, (IADLXInterface**)&ppManualPowerTuning);

		adlx_Res0 = ppManualPowerTuning->GetPowerLimitRange(&adlx_IntRange0);
		slider_Power_Limit().Minimum(adlx_IntRange0.minValue);
		slider_Power_Limit().Maximum(adlx_IntRange0.maxValue);

		adlx_Res0 = ppManualPowerTuning->GetPowerLimit(&adlx_Int0);
		slider_Power_Limit().Value(adlx_Int0);

		//Fix add tdc
		//adlx_Res0 = ppManualPowerTuning->IsSupportedTDCLimit(&adlx_Bool);
		//if (adlx_Bool) 
		//{
		//	//adlx_Res0 = ppManualPowerTuning->GetTDCLimitRange(&adlx_IntRange0);
		//	//adlx_Res0 = ppManualPowerTuning->GetTDCLimit(&adlx_Int0);
		//}

		//Get display color depth
		IADLXDisplayColorDepthPtr ppColorDepth;
		adlx_Res0 = ppDispServices->GetColorDepth(ppDisplayInfo, &ppColorDepth);
		ADLX_COLOR_DEPTH colorDepth;
		ppColorDepth->GetValue(&colorDepth);
		combobox_Display_ColorDepth().SelectedIndex(colorDepth - 1);

		//Get display pixel format
		IADLXDisplayPixelFormatPtr ppPixelFormat;
		adlx_Res0 = ppDispServices->GetPixelFormat(ppDisplayInfo, &ppPixelFormat);
		ADLX_PIXEL_FORMAT pixelFormat;
		ppPixelFormat->GetValue(&pixelFormat);
		combobox_Display_PixelFormat().SelectedIndex(pixelFormat - 1);

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