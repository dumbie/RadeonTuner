#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesLoadGraphics()
	{
		try
		{
			//Check services
			if (pp3DSettingsServices == NULL)
			{
				stackpanel_Graphics().Opacity(0.20);
				stackpanel_Graphics().IsHitTestVisible(false);
				AVDebugWriteLine("ADLX graphics service is not available.");
				return;
			}

			//Get super resolution
			try
			{
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

					//Enable or disable interface
					toggleswitch_RadeonSuperResolution().IsEnabled(true);
					if (adlx_Bool)
					{
						slider_RadeonSuperResolution_Sharpening().IsEnabled(true);
					}
					else
					{
						slider_RadeonSuperResolution_Sharpening().IsEnabled(false);
					}
				}
				else
				{
					//Enable or disable interface
					toggleswitch_RadeonSuperResolution().IsEnabled(false);
					slider_RadeonSuperResolution_Sharpening().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_RadeonSuperResolution().IsEnabled(false);
				slider_RadeonSuperResolution_Sharpening().IsEnabled(false);
			}

			//Get Radeon Fluid Motion Frames setting
			try
			{
				IADLX3DAMDFluidMotionFramesPtr pp3DAMDFluidMotionFrames;
				adlx_Res0 = pp3DSettingsServices->GetAMDFluidMotionFrames(&pp3DAMDFluidMotionFrames);
				adlx_Res0 = pp3DAMDFluidMotionFrames->IsSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = pp3DAMDFluidMotionFrames->IsEnabled(&adlx_Bool);
					toggleswitch_RadeonFluidMotionFrames().IsOn(adlx_Bool);

					//Enable or disable interface
					toggleswitch_RadeonFluidMotionFrames().IsEnabled(true);
					combobox_FrameGenSearchMode().IsEnabled(true);
					combobox_FrameGenPerfMode().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
					toggleswitch_RadeonFluidMotionFrames().IsEnabled(false);
					combobox_FrameGenSearchMode().IsEnabled(false);
					combobox_FrameGenPerfMode().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_RadeonFluidMotionFrames().IsEnabled(false);
				combobox_FrameGenSearchMode().IsEnabled(false);
				combobox_FrameGenPerfMode().IsEnabled(false);
			}

			//Get Radeon Anti-Lag setting
			try
			{
				IADLX3DAntiLagPtr pp3DAntiLag;
				adlx_Res0 = pp3DSettingsServices->GetAntiLag(ppGpuInfo, &pp3DAntiLag);
				adlx_Res0 = pp3DAntiLag->IsSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = pp3DAntiLag->IsEnabled(&adlx_Bool);
					toggleswitch_RadeonAntiLag().IsOn(adlx_Bool);

					//Enable or disable interface
					toggleswitch_RadeonAntiLag().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
					toggleswitch_RadeonAntiLag().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_RadeonAntiLag().IsEnabled(false);
			}

			//Get Radeon Boost setting
			try
			{
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

					//Enable or disable interface
					toggleswitch_RadeonBoost().IsEnabled(true);
					if (adlx_Bool)
					{
						slider_RadeonBoost_MinRes().IsEnabled(true);
					}
					else
					{
						slider_RadeonBoost_MinRes().IsEnabled(false);
					}
				}
				else
				{
					//Enable or disable interface
					toggleswitch_RadeonBoost().IsEnabled(false);
					slider_RadeonBoost_MinRes().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_RadeonBoost().IsEnabled(false);
				slider_RadeonBoost_MinRes().IsEnabled(false);
			}

			//Get chill setting
			try
			{
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

					//Enable or disable interface
					toggleswitch_RadeonChill().IsEnabled(true);
					if (adlx_Bool)
					{
						slider_RadeonChill_Min().IsEnabled(true);
						slider_RadeonChill_Max().IsEnabled(true);
					}
					else
					{
						slider_RadeonChill_Min().IsEnabled(false);
						slider_RadeonChill_Max().IsEnabled(false);
					}
				}
				else
				{
					//Enable or disable interface
					toggleswitch_RadeonChill().IsEnabled(false);
					slider_RadeonChill_Min().IsEnabled(false);
					slider_RadeonChill_Max().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_RadeonChill().IsEnabled(false);
				slider_RadeonChill_Min().IsEnabled(false);
				slider_RadeonChill_Max().IsEnabled(false);
			}

			//Get image sharpening
			try
			{
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

					//Enable or disable interface
					toggleswitch_RadeonImageSharpening().IsEnabled(true);
					if (adlx_Bool)
					{
						slider_RadeonImageSharpening_Sharpening().IsEnabled(true);
					}
					else
					{
						slider_RadeonImageSharpening_Sharpening().IsEnabled(false);
					}
				}
				else
				{
					//Enable or disable interface
					toggleswitch_RadeonImageSharpening().IsEnabled(false);
					slider_RadeonImageSharpening_Sharpening().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_RadeonImageSharpening().IsEnabled(false);
				slider_RadeonImageSharpening_Sharpening().IsEnabled(false);
			}

			//Get desktop sharpening setting
			try
			{
				IADLX3DImageSharpenDesktopPtr pp3DImageSharpenDesktop;
				adlx_Res0 = pp3DSettingsServices->GetImageSharpenDesktop(ppGpuInfo, &pp3DImageSharpenDesktop);
				adlx_Res0 = pp3DImageSharpenDesktop->IsSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = pp3DImageSharpenDesktop->IsEnabled(&adlx_Bool);
					toggleswitch_RadeonSharpenDesktop().IsOn(adlx_Bool);

					//Enable or disable interface
					if (toggleswitch_RadeonImageSharpening().IsOn())
					{
						toggleswitch_RadeonSharpenDesktop().IsEnabled(true);
					}
					else
					{
						toggleswitch_RadeonSharpenDesktop().IsEnabled(false);
					}
				}
				else
				{
					//Enable or disable interface
					toggleswitch_RadeonSharpenDesktop().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_RadeonSharpenDesktop().IsEnabled(false);
			}

			//Get vertical refresh setting
			try
			{
				IADLX3DWaitForVerticalRefreshPtr pp3DWaitForVerticalRefresh;
				adlx_Res0 = pp3DSettingsServices->GetWaitForVerticalRefresh(ppGpuInfo, &pp3DWaitForVerticalRefresh);
				adlx_Res0 = pp3DWaitForVerticalRefresh->IsSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE verticalRefreshMode;
					adlx_Res0 = pp3DWaitForVerticalRefresh->GetMode(&verticalRefreshMode);
					combobox_VerticalRefresh().SelectedIndex(verticalRefreshMode);

					//Enable or disable interface
					combobox_VerticalRefresh().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
					combobox_VerticalRefresh().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				combobox_VerticalRefresh().IsEnabled(false);
			}

			//Get enhanced sync setting
			try
			{
				IADLX3DEnhancedSyncPtr pp3DEnhancedSync;
				adlx_Res0 = pp3DSettingsServices->GetEnhancedSync(ppGpuInfo, &pp3DEnhancedSync);
				adlx_Res0 = pp3DEnhancedSync->IsSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = pp3DEnhancedSync->IsEnabled(&adlx_Bool);
					toggleswitch_RadeonEnhancedSync().IsOn(adlx_Bool);

					//Enable or disable interface
					toggleswitch_RadeonEnhancedSync().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
					toggleswitch_RadeonEnhancedSync().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_RadeonEnhancedSync().IsEnabled(false);
			}

			//Get frtc
			try
			{
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

					//Enable or disable interface
					toggleswitch_Frtc().IsEnabled(true);
					if (adlx_Bool)
					{
						slider_Frtc_Max().IsEnabled(true);
					}
					else
					{
						slider_Frtc_Max().IsEnabled(false);
					}
				}
				else
				{
					//Enable or disable interface
					toggleswitch_Frtc().IsEnabled(false);
					slider_Frtc_Max().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_Frtc().IsEnabled(false);
				slider_Frtc_Max().IsEnabled(false);
			}

			//Get Anti-Aliasing
			try
			{
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

					//Enable or disable interface
					combobox_AntiAliasingMode().IsEnabled(true);
					combobox_AntiAliasingMethod().IsEnabled(true);
					if (currentMode != ADLX_ANTI_ALIASING_MODE::AA_MODE_OVERRIDE_APP_SETTINGS)
					{
						combobox_AntiAliasingLevel().IsEnabled(false);
					}
					else
					{
						combobox_AntiAliasingLevel().IsEnabled(true);
					}
				}
				else
				{
					//Enable or disable interface
					combobox_AntiAliasingMode().IsEnabled(false);
					combobox_AntiAliasingMethod().IsEnabled(false);
					combobox_AntiAliasingLevel().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				combobox_AntiAliasingMode().IsEnabled(false);
				combobox_AntiAliasingMethod().IsEnabled(false);
				combobox_AntiAliasingLevel().IsEnabled(false);
			}

			//Get Morphological Anti-Aliasing
			try
			{
				IADLX3DMorphologicalAntiAliasingPtr pp3DMorphologicalAntiAliasing;
				adlx_Res0 = pp3DSettingsServices->GetMorphologicalAntiAliasing(ppGpuInfo, &pp3DMorphologicalAntiAliasing);
				adlx_Res0 = pp3DMorphologicalAntiAliasing->IsSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = pp3DMorphologicalAntiAliasing->IsEnabled(&adlx_Bool);
					toggleswitch_MorphologicAntiAliasing().IsOn(adlx_Bool);

					//Enable or disable interface
					toggleswitch_MorphologicAntiAliasing().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
					toggleswitch_MorphologicAntiAliasing().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_MorphologicAntiAliasing().IsEnabled(false);
			}

			//Get Anisotropic texture filtering
			try
			{
				IADLX3DAnisotropicFilteringPtr pp3DAnisotropicFiltering;
				adlx_Res0 = pp3DSettingsServices->GetAnisotropicFiltering(ppGpuInfo, &pp3DAnisotropicFiltering);
				adlx_Res0 = pp3DAnisotropicFiltering->IsSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					//Set Anisotropic
					adlx_Res0 = pp3DAnisotropicFiltering->IsEnabled(&adlx_Bool);
					toggleswitch_AnisotropicTextureFiltering().IsOn(adlx_Bool);

					//Enable or disable interface
					toggleswitch_AnisotropicTextureFiltering().IsEnabled(true);
					if (adlx_Bool)
					{
						combobox_AnisotropicTextureFilteringQuality().IsEnabled(true);
					}
					else
					{
						combobox_AnisotropicTextureFilteringQuality().IsEnabled(false);
					}

					//Set Anisotropic Level
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
					//Enable or disable interface
					toggleswitch_AnisotropicTextureFiltering().IsEnabled(false);
					combobox_AnisotropicTextureFilteringQuality().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_AnisotropicTextureFiltering().IsEnabled(false);
				combobox_AnisotropicTextureFilteringQuality().IsEnabled(false);
			}

			//Get Tesselation
			try
			{
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

					//Enable or disable interface
					combobox_Tessellation_Mode().IsEnabled(true);
					if (currentMode != ADLX_TESSELLATION_MODE::T_MODE_OVERRIDE_APP_SETTINGS)
					{
						combobox_Tessellation_Level().IsEnabled(false);
					}
					else
					{
						combobox_Tessellation_Level().IsEnabled(true);
					}
				}
				else
				{
					//Enable or disable interface
					combobox_Tessellation_Mode().IsEnabled(false);
					combobox_Tessellation_Level().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				combobox_Tessellation_Mode().IsEnabled(false);
				combobox_Tessellation_Level().IsEnabled(false);
			}

			//Set result
			AVDebugWriteLine("ADLX loaded graphics values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading graphics values.");
		}
	}
}