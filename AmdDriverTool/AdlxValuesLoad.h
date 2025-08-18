#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::AdlxValuesLoad()
	{
		//Fix ADLX missing Surface Format Optimization
		//Fix ADLX missing OpenGL Triple Buffering
		//Fix ADLX missing 10-Bit Pixel Format
		//Fix ADLX missing AMD Privacy View
		//Fix IADLXEyefinityDesktop support
		//Fix Get3DLUT support (Missing IADLXDisplay3DLUTPtr)
		//Fix GetGamut support (Missing IADLXDisplayGamutPtr)
		//Fix GetGamma support (Missing IADLXDisplayGammaPtr)
		//Fix GetCustomResolution support (Custom Resolution Utility)

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

		//Get super resolution
		IADLX3DRadeonSuperResolutionPtr pp3DRadeonSuperResolution;
		adlx_Res0 = pp3DSettingsServices->GetRadeonSuperResolution(&pp3DRadeonSuperResolution);
		adlx_Res0 = pp3DRadeonSuperResolution->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			adlx_Res0 = pp3DRadeonSuperResolution->IsEnabled(&adlx_Bool);
			adlx_Res0 = pp3DRadeonSuperResolution->GetSharpness(&adlx_Int0);
			adlx_Res0 = pp3DRadeonSuperResolution->GetSharpnessRange(&adlx_IntRange0);

			toggleswitch_RadeonSuperResolution().IsOn(adlx_Bool);
			slider_RadeonSuperResolution_Sharpening().Value(adlx_Int0);
			slider_RadeonSuperResolution_Sharpening().Minimum(adlx_IntRange0.minValue);
			slider_RadeonSuperResolution_Sharpening().Maximum(adlx_IntRange0.maxValue);
			slider_RadeonSuperResolution_Sharpening().StepFrequency(adlx_IntRange0.step);

			if (!adlx_Bool)
			{
				slider_RadeonSuperResolution_Sharpening().IsEnabled(false);
			}
		}
		else
		{
			toggleswitch_RadeonSuperResolution().IsEnabled(false);
			slider_RadeonSuperResolution_Sharpening().IsEnabled(false);
		}

		//Get Radeon Fluid Motion Frames setting
		IADLX3DAMDFluidMotionFramesPtr pp3DAMDFluidMotionFrames;
		adlx_Res0 = pp3DSettingsServices->GetAMDFluidMotionFrames(&pp3DAMDFluidMotionFrames);
		adlx_Res0 = pp3DAMDFluidMotionFrames->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			adlx_Res0 = pp3DAMDFluidMotionFrames->IsEnabled(&adlx_Bool);
			toggleswitch_RadeonFluidMotionFrames().IsOn(adlx_Bool);
		}
		else
		{
			toggleswitch_RadeonFluidMotionFrames().IsEnabled(false);
		}

		//Get Radeon Anti-Lag setting
		IADLX3DAntiLagPtr pp3DAntiLag;
		adlx_Res0 = pp3DSettingsServices->GetAntiLag(ppGpuInfo, &pp3DAntiLag);
		adlx_Res0 = pp3DAntiLag->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			adlx_Res0 = pp3DAntiLag->IsEnabled(&adlx_Bool);
			toggleswitch_RadeonAntiLag().IsOn(adlx_Bool);
		}
		else
		{
			toggleswitch_RadeonAntiLag().IsEnabled(false);
		}

		//Get Radeon Boost setting
		IADLX3DBoostPtr pp3DBoost;
		adlx_Res0 = pp3DSettingsServices->GetBoost(ppGpuInfo, &pp3DBoost);
		adlx_Res0 = pp3DBoost->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			adlx_Res0 = pp3DBoost->IsEnabled(&adlx_Bool);
			adlx_Res0 = pp3DBoost->GetResolution(&adlx_Int0);
			adlx_Res0 = pp3DBoost->GetResolutionRange(&adlx_IntRange0);

			toggleswitch_RadeonBoost().IsOn(adlx_Bool);
			slider_RadeonBoost_MinRes().Value(adlx_Int0);
			slider_RadeonBoost_MinRes().Minimum(adlx_IntRange0.minValue);
			slider_RadeonBoost_MinRes().Maximum(adlx_IntRange0.maxValue);
			slider_RadeonBoost_MinRes().StepFrequency(adlx_IntRange0.step);

			if (!adlx_Bool)
			{
				slider_RadeonBoost_MinRes().IsEnabled(false);
			}
		}
		else
		{
			toggleswitch_RadeonBoost().IsEnabled(false);
			slider_RadeonBoost_MinRes().IsEnabled(false);
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

		//Get image sharpening
		IADLX3DImageSharpeningPtr pp3DImageSharpening;
		adlx_Res0 = pp3DSettingsServices->GetImageSharpening(ppGpuInfo, &pp3DImageSharpening);
		adlx_Res0 = pp3DImageSharpening->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			adlx_Res0 = pp3DImageSharpening->IsEnabled(&adlx_Bool);
			adlx_Res0 = pp3DImageSharpening->GetSharpness(&adlx_Int0);
			adlx_Res0 = pp3DImageSharpening->GetSharpnessRange(&adlx_IntRange0);

			toggleswitch_RadeonImageSharpening().IsOn(adlx_Bool);
			slider_RadeonImageSharpening_Sharpening().Value(adlx_Int0);
			slider_RadeonImageSharpening_Sharpening().Minimum(adlx_IntRange0.minValue);
			slider_RadeonImageSharpening_Sharpening().Maximum(adlx_IntRange0.maxValue);
			slider_RadeonImageSharpening_Sharpening().StepFrequency(adlx_IntRange0.step);

			if (!adlx_Bool)
			{
				slider_RadeonImageSharpening_Sharpening().IsEnabled(false);
			}
		}
		else
		{
			toggleswitch_RadeonImageSharpening().IsEnabled(false);
			slider_RadeonImageSharpening_Sharpening().IsEnabled(false);
		}

		//Get desktop sharpening setting
		IADLX3DImageSharpenDesktopPtr pp3DImageSharpenDesktop;
		adlx_Res0 = pp3DSettingsServices->GetImageSharpenDesktop(ppGpuInfo, &pp3DImageSharpenDesktop);
		adlx_Res0 = pp3DImageSharpenDesktop->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			adlx_Res0 = pp3DImageSharpenDesktop->IsEnabled(&adlx_Bool);
			toggleswitch_RadeonSharpenDesktop().IsOn(adlx_Bool);
		}
		else
		{
			toggleswitch_RadeonSharpenDesktop().IsEnabled(false);
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
			toggleswitch_RadeonEnhancedSync().IsOn(adlx_Bool);
		}
		else
		{
			toggleswitch_RadeonEnhancedSync().IsEnabled(false);
		}

		//Get frtc
		IADLX3DFrameRateTargetControlPtr pp3DFrameRateTargetControl;
		adlx_Res0 = pp3DSettingsServices->GetFrameRateTargetControl(ppGpuInfo, &pp3DFrameRateTargetControl);
		adlx_Res0 = pp3DFrameRateTargetControl->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			adlx_Res0 = pp3DFrameRateTargetControl->IsEnabled(&adlx_Bool);
			adlx_Res0 = pp3DFrameRateTargetControl->GetFPS(&adlx_Int0);
			adlx_Res0 = pp3DFrameRateTargetControl->GetFPSRange(&adlx_IntRange0);

			toggleswitch_Frtc().IsOn(adlx_Bool);
			slider_Frtc_Max().Value(adlx_Int0);
			slider_Frtc_Max().Minimum(adlx_IntRange0.minValue);
			slider_Frtc_Max().Maximum(adlx_IntRange0.maxValue);
			slider_Frtc_Max().StepFrequency(adlx_IntRange0.step);

			if (!adlx_Bool)
			{
				slider_Frtc_Max().IsEnabled(false);
			}
		}
		else
		{
			toggleswitch_Frtc().IsEnabled(false);
			slider_Frtc_Max().IsEnabled(false);
		}

		//Get Anti-Aliasing
		IADLX3DAntiAliasingPtr pp3DAntiAliasing;
		adlx_Res0 = pp3DSettingsServices->GetAntiAliasing(ppGpuInfo, &pp3DAntiAliasing);
		adlx_Res0 = pp3DAntiAliasing->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			ADLX_ANTI_ALIASING_MODE currentMode;
			adlx_Res0 = pp3DAntiAliasing->GetMode(&currentMode);
			combobox_AntiAliasingMode().SelectedIndex(currentMode);

			ADLX_ANTI_ALIASING_METHOD currentMethod;
			adlx_Res0 = pp3DAntiAliasing->GetMethod(&currentMethod);
			combobox_AntiAliasingMethod().SelectedIndex(currentMethod);

			ADLX_ANTI_ALIASING_LEVEL currentLevel;
			adlx_Res0 = pp3DAntiAliasing->GetLevel(&currentLevel);

			//Enumeration index correction
			if (currentLevel == ADLX_ANTI_ALIASING_LEVEL::AA_LEVEL_2X)
			{
				combobox_AntiAliasingLevel().SelectedIndex(0);
			}
			else if (currentLevel == ADLX_ANTI_ALIASING_LEVEL::AA_LEVEL_2XEQ)
			{
				combobox_AntiAliasingLevel().SelectedIndex(1);
			}
			else if (currentLevel == ADLX_ANTI_ALIASING_LEVEL::AA_LEVEL_4X)
			{
				combobox_AntiAliasingLevel().SelectedIndex(2);
			}
			else if (currentLevel == ADLX_ANTI_ALIASING_LEVEL::AA_LEVEL_4XEQ)
			{
				combobox_AntiAliasingLevel().SelectedIndex(3);
			}
			else if (currentLevel == ADLX_ANTI_ALIASING_LEVEL::AA_LEVEL_8X)
			{
				combobox_AntiAliasingLevel().SelectedIndex(4);
			}
			else if (currentLevel == ADLX_ANTI_ALIASING_LEVEL::AA_LEVEL_8XEQ)
			{
				combobox_AntiAliasingLevel().SelectedIndex(5);
			}
			else
			{
				AVDebugWriteLine("No Anti-Aliasing level set.");
			}
		}
		else
		{
			combobox_AntiAliasingMode().IsEnabled(false);
			combobox_AntiAliasingMethod().IsEnabled(false);
			combobox_AntiAliasingLevel().IsEnabled(false);
		}

		//Get Morphological Anti-Aliasing
		IADLX3DMorphologicalAntiAliasingPtr pp3DMorphologicalAntiAliasing;
		adlx_Res0 = pp3DSettingsServices->GetMorphologicalAntiAliasing(ppGpuInfo, &pp3DMorphologicalAntiAliasing);
		adlx_Res0 = pp3DMorphologicalAntiAliasing->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			adlx_Res0 = pp3DMorphologicalAntiAliasing->IsEnabled(&adlx_Bool);
			toggleswitch_MorphologicAntiAliasing().IsOn(adlx_Bool);
		}
		else
		{
			toggleswitch_MorphologicAntiAliasing().IsEnabled(false);
		}

		//Get Anisotropic texture filtering
		IADLX3DAnisotropicFilteringPtr pp3DAnisotropicFiltering;
		adlx_Res0 = pp3DSettingsServices->GetAnisotropicFiltering(ppGpuInfo, &pp3DAnisotropicFiltering);
		adlx_Res0 = pp3DAnisotropicFiltering->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			adlx_Res0 = pp3DAnisotropicFiltering->IsEnabled(&adlx_Bool);
			toggleswitch_AnisotropicTextureFiltering().IsOn(adlx_Bool);

			ADLX_ANISOTROPIC_FILTERING_LEVEL currentLevel;
			adlx_Res0 = pp3DAnisotropicFiltering->GetLevel(&currentLevel);

			//Enumeration index correction
			if (currentLevel == ADLX_ANISOTROPIC_FILTERING_LEVEL::AF_LEVEL_X2)
			{
				combobox_AnisotropicTextureFilteringQuality().SelectedIndex(0);
			}
			else if (currentLevel == ADLX_ANISOTROPIC_FILTERING_LEVEL::AF_LEVEL_X4)
			{
				combobox_AnisotropicTextureFilteringQuality().SelectedIndex(1);
			}
			else if (currentLevel == ADLX_ANISOTROPIC_FILTERING_LEVEL::AF_LEVEL_X8)
			{
				combobox_AnisotropicTextureFilteringQuality().SelectedIndex(2);
			}
			else if (currentLevel == ADLX_ANISOTROPIC_FILTERING_LEVEL::AF_LEVEL_X16)
			{
				combobox_AnisotropicTextureFilteringQuality().SelectedIndex(3);
			}
			else
			{
				AVDebugWriteLine("No Anisotropic level set.");
			}
		}
		else
		{
			toggleswitch_AnisotropicTextureFiltering().IsEnabled(false);
			combobox_AnisotropicTextureFilteringQuality().IsEnabled(false);
		}

		//Get Tesselation
		IADLX3DTessellationPtr pp3DTessellation;
		adlx_Res0 = pp3DSettingsServices->GetTessellation(ppGpuInfo, &pp3DTessellation);
		adlx_Res0 = pp3DTessellation->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			ADLX_TESSELLATION_MODE currentMode;
			adlx_Res0 = pp3DTessellation->GetMode(&currentMode);
			combobox_Tessellation_Mode().SelectedIndex(currentMode);

			ADLX_TESSELLATION_LEVEL currentLevel;
			adlx_Res0 = pp3DTessellation->GetLevel(&currentLevel);

			//Enumeration index correction
			if (currentLevel == ADLX_TESSELLATION_LEVEL::T_LEVEL_OFF)
			{
				combobox_Tessellation_Level().SelectedIndex(0);
			}
			else if (currentLevel == ADLX_TESSELLATION_LEVEL::T_LEVEL_2X)
			{
				combobox_Tessellation_Level().SelectedIndex(1);
			}
			else if (currentLevel == ADLX_TESSELLATION_LEVEL::T_LEVEL_4X)
			{
				combobox_Tessellation_Level().SelectedIndex(2);
			}
			else if (currentLevel == ADLX_TESSELLATION_LEVEL::T_LEVEL_6X)
			{
				combobox_Tessellation_Level().SelectedIndex(3);
			}
			else if (currentLevel == ADLX_TESSELLATION_LEVEL::T_LEVEL_8X)
			{
				combobox_Tessellation_Level().SelectedIndex(4);
			}
			else if (currentLevel == ADLX_TESSELLATION_LEVEL::T_LEVEL_16X)
			{
				combobox_Tessellation_Level().SelectedIndex(5);
			}
			else if (currentLevel == ADLX_TESSELLATION_LEVEL::T_LEVEL_32X)
			{
				combobox_Tessellation_Level().SelectedIndex(6);
			}
			else if (currentLevel == ADLX_TESSELLATION_LEVEL::T_LEVEL_64X)
			{
				combobox_Tessellation_Level().SelectedIndex(7);
			}
		}
		else
		{
			combobox_Tessellation_Mode().IsEnabled(false);
			combobox_Tessellation_Level().IsEnabled(false);
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

		//Get display VSR setting
		IADLXDisplayVSRPtr ppVSR;
		adlx_Res0 = ppDispServices->GetVirtualSuperResolution(ppDisplayInfo, &ppVSR);
		adlx_Res0 = ppVSR->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			adlx_Res0 = ppVSR->IsEnabled(&adlx_Bool);
			toggleswitch_VSR().IsOn(adlx_Bool);
		}
		else
		{
			toggleswitch_VSR().IsEnabled(false);
		}

		//Get display GPU Scaling setting
		IADLXDisplayGPUScalingPtr ppGPUScaling;
		adlx_Res0 = ppDispServices->GetGPUScaling(ppDisplayInfo, &ppGPUScaling);
		adlx_Res0 = ppGPUScaling->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			adlx_Res0 = ppGPUScaling->IsEnabled(&adlx_Bool);
			toggleswitch_GPUScaling().IsOn(adlx_Bool);
		}
		else
		{
			toggleswitch_GPUScaling().IsEnabled(false);
		}

		//Get display Integer Scaling setting
		IADLXDisplayIntegerScalingPtr ppIntegerScaling;
		adlx_Res0 = ppDispServices->GetIntegerScaling(ppDisplayInfo, &ppIntegerScaling);
		adlx_Res0 = ppIntegerScaling->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			adlx_Res0 = ppIntegerScaling->IsEnabled(&adlx_Bool);
			toggleswitch_IntegerScaling().IsOn(adlx_Bool);
		}
		else
		{
			toggleswitch_IntegerScaling().IsEnabled(false);
		}

		//Get display scaling mode
		IADLXDisplayScalingModePtr ppScalingMode;
		adlx_Res0 = ppDispServices->GetScalingMode(ppDisplayInfo, &ppScalingMode);
		adlx_Res0 = ppScalingMode->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			ADLX_SCALE_MODE currentMode;
			adlx_Res0 = ppScalingMode->GetMode(&currentMode);
			combobox_Display_ScalingMode().SelectedIndex(currentMode);
		}
		else
		{
			combobox_Display_ScalingMode().IsEnabled(false);
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

		//Get display vari-bright
		IADLXDisplayVariBrightPtr ppVariBright;
		adlx_Res0 = ppDispServices->GetVariBright(ppDisplayInfo, &ppVariBright);
		adlx_Res0 = ppVariBright->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			//Set Vari-Bright
			adlx_Res0 = ppVariBright->IsEnabled(&adlx_Bool);
			toggleswitch_VariBright().IsOn(adlx_Bool);

			//Check Vari-Bright
			if (!adlx_Bool)
			{
				combobox_Display_VariBright_Level().IsEnabled(false);
			}

			//Set Vari-Bright Level
			adlx_Res0 = ppVariBright->IsCurrentMaximizeBrightness(&adlx_Bool);
			if (adlx_Bool)
			{
				combobox_Display_VariBright_Level().SelectedIndex(0);
			}
			adlx_Res0 = ppVariBright->IsCurrentOptimizeBrightness(&adlx_Bool);
			if (adlx_Bool)
			{
				combobox_Display_VariBright_Level().SelectedIndex(1);
			}
			adlx_Res0 = ppVariBright->IsCurrentBalanced(&adlx_Bool);
			if (adlx_Bool)
			{
				combobox_Display_VariBright_Level().SelectedIndex(2);
			}
			adlx_Res0 = ppVariBright->IsCurrentOptimizeBattery(&adlx_Bool);
			if (adlx_Bool)
			{
				combobox_Display_VariBright_Level().SelectedIndex(3);
			}
			adlx_Res0 = ppVariBright->IsCurrentMaximizeBattery(&adlx_Bool);
			if (adlx_Bool)
			{
				combobox_Display_VariBright_Level().SelectedIndex(4);
			}
		}
		else
		{
			combobox_Display_VariBright_Level().IsEnabled(false);
			toggleswitch_VariBright().IsEnabled(false);
		}

		//Get display hdcp support
		IADLXDisplayHDCPPtr ppHDCP;
		adlx_Res0 = ppDispServices->GetHDCP(ppDisplayInfo, &ppHDCP);
		adlx_Res0 = ppHDCP->IsSupported(&adlx_Bool);
		if (adlx_Bool)
		{
			adlx_Res0 = ppHDCP->IsEnabled(&adlx_Bool);
			toggleswitch_HDCPSupport().IsOn(adlx_Bool);
		}
		else
		{
			toggleswitch_HDCPSupport().IsEnabled(false);
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