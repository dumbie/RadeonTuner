#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::AdlxValuesLoadDisplay()
	{
		try
		{
			//Check services
			if (ppDispServices == NULL)
			{
				stackpanel_Display().Opacity(0.20);
				stackpanel_Display().IsHitTestVisible(false);
				AVDebugWriteLine("ADLX display service is not available.");
				return;
			}

			//Get display freesync setting
			try
			{
				IADLXDisplayFreeSyncPtr ppFreeSync;
				adlx_Res0 = ppDispServices->GetFreeSync(ppDisplayInfo, &ppFreeSync);
				adlx_Res0 = ppFreeSync->IsSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = ppFreeSync->IsEnabled(&adlx_Bool);
					toggleswitch_FreeSync().IsOn(adlx_Bool);

					//Enable or disable interface
					toggleswitch_FreeSync().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
					toggleswitch_FreeSync().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_FreeSync().IsEnabled(false);
			}

			//Get display freesync color accuracy setting
			try
			{
				IADLXDisplayFreeSyncColorAccuracyPtr ppFSCA;
				adlx_Res0 = ppDispServices->GetFreeSyncColorAccuracy(ppDisplayInfo, &ppFSCA);
				adlx_Res0 = ppFSCA->IsSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = ppFSCA->IsEnabled(&adlx_Bool);
					toggleswitch_FreeSyncColorAccuracy().IsOn(adlx_Bool);

					//Enable or disable interface
					if (toggleswitch_FreeSync().IsOn())
					{
						toggleswitch_FreeSyncColorAccuracy().IsEnabled(true);
					}
					else
					{
						toggleswitch_FreeSyncColorAccuracy().IsEnabled(false);
					}
				}
				else
				{
					//Enable or disable interface
					toggleswitch_FreeSyncColorAccuracy().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_FreeSyncColorAccuracy().IsEnabled(false);
			}

			//Get display VSR setting
			try
			{
				IADLXDisplayVSRPtr ppVSR;
				adlx_Res0 = ppDispServices->GetVirtualSuperResolution(ppDisplayInfo, &ppVSR);
				adlx_Res0 = ppVSR->IsSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = ppVSR->IsEnabled(&adlx_Bool);
					toggleswitch_VSR().IsOn(adlx_Bool);

					//Enable or disable interface
					toggleswitch_VSR().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
					toggleswitch_VSR().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_VSR().IsEnabled(false);
			}

			//Get display Dynamic Refresh Rate Control setting
			try
			{
				IADLXDisplayDynamicRefreshRateControlPtr ppDRRC;
				adlx_Res0 = ppDispServices->GetDynamicRefreshRateControl(ppDisplayInfo, &ppDRRC);
				adlx_Res0 = ppDRRC->IsSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = ppDRRC->IsEnabled(&adlx_Bool);
					toggleswitch_DynamicRefreshRateControl().IsOn(adlx_Bool);

					//Enable or disable interface
					toggleswitch_DynamicRefreshRateControl().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
					toggleswitch_DynamicRefreshRateControl().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_DynamicRefreshRateControl().IsEnabled(false);
			}

			//Get display GPU Scaling setting
			try
			{
				IADLXDisplayGPUScalingPtr ppGPUScaling;
				adlx_Res0 = ppDispServices->GetGPUScaling(ppDisplayInfo, &ppGPUScaling);
				adlx_Res0 = ppGPUScaling->IsSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = ppGPUScaling->IsEnabled(&adlx_Bool);
					toggleswitch_GPUScaling().IsOn(adlx_Bool);

					//Enable or disable interface
					toggleswitch_GPUScaling().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
					toggleswitch_GPUScaling().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_GPUScaling().IsEnabled(false);
			}

			//Get display Integer Scaling setting
			try
			{
				IADLXDisplayIntegerScalingPtr ppIntegerScaling;
				adlx_Res0 = ppDispServices->GetIntegerScaling(ppDisplayInfo, &ppIntegerScaling);
				adlx_Res0 = ppIntegerScaling->IsSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = ppIntegerScaling->IsEnabled(&adlx_Bool);
					toggleswitch_IntegerScaling().IsOn(adlx_Bool);

					//Enable or disable interface
					if (toggleswitch_GPUScaling().IsOn())
					{
						toggleswitch_IntegerScaling().IsEnabled(true);
					}
					else
					{
						toggleswitch_IntegerScaling().IsEnabled(false);
					}
				}
				else
				{
					//Enable or disable interface
					toggleswitch_IntegerScaling().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_IntegerScaling().IsEnabled(false);
			}

			//Get display scaling mode
			try
			{
				IADLXDisplayScalingModePtr ppScalingMode;
				adlx_Res0 = ppDispServices->GetScalingMode(ppDisplayInfo, &ppScalingMode);
				adlx_Res0 = ppScalingMode->IsSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					ADLX_SCALE_MODE currentMode;
					adlx_Res0 = ppScalingMode->GetMode(&currentMode);
					combobox_Display_ScalingMode().SelectedIndex(currentMode);

					//Enable or disable interface
					combobox_Display_ScalingMode().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
					combobox_Display_ScalingMode().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				combobox_Display_ScalingMode().IsEnabled(false);
			}

			//Get display color depth
			try
			{
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

					//Enable or disable interface
					combobox_Display_ColorDepth().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
					combobox_Display_ColorDepth().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				combobox_Display_ColorDepth().IsEnabled(false);
			}

			//Get display pixel format
			try
			{
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

					//Enable or disable interface
					combobox_Display_PixelFormat().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
					combobox_Display_PixelFormat().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				combobox_Display_PixelFormat().IsEnabled(false);
			}

			//Get display custom color profile
			try
			{
				IADLXDisplayCustomColorPtr ppCustomColor;
				adlx_Res0 = ppDispServices->GetCustomColor(ppDisplayInfo, &ppCustomColor);

				//Get display color temperature
				adlx_Res0 = ppCustomColor->IsTemperatureSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = ppCustomColor->GetTemperature(&adlx_Int0);
					adlx_Res0 = ppCustomColor->GetTemperatureRange(&adlx_IntRange0);
					slider_Display_ColorTemperature().Value(adlx_Int0);
					slider_Display_ColorTemperature().Minimum(adlx_IntRange0.minValue);
					slider_Display_ColorTemperature().Maximum(adlx_IntRange0.maxValue);
					slider_Display_ColorTemperature().StepFrequency(adlx_IntRange0.step);

					//Enable or disable interface
					slider_Display_ColorTemperature().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
					slider_Display_ColorTemperature().IsEnabled(false);
				}

				//Get display brightness
				adlx_Res0 = ppCustomColor->IsBrightnessSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = ppCustomColor->GetBrightness(&adlx_Int0);
					adlx_Res0 = ppCustomColor->GetBrightnessRange(&adlx_IntRange0);
					slider_Display_Brightness().Value(adlx_Int0);
					slider_Display_Brightness().Minimum(adlx_IntRange0.minValue);
					slider_Display_Brightness().Maximum(adlx_IntRange0.maxValue);
					slider_Display_Brightness().StepFrequency(adlx_IntRange0.step);

					//Enable or disable interface
					slider_Display_Brightness().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
					slider_Display_Brightness().IsEnabled(false);
				}

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

					//Enable or disable interface
					slider_Display_Contrast().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
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

					//Enable or disable interface
					slider_Display_Saturation().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
					slider_Display_Saturation().IsEnabled(false);
				}

				//Get display hue
				adlx_Res0 = ppCustomColor->IsHueSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = ppCustomColor->GetHue(&adlx_Int0);
					adlx_Res0 = ppCustomColor->GetHueRange(&adlx_IntRange0);
					slider_Display_Hue().Value(adlx_Int0);
					slider_Display_Hue().Minimum(adlx_IntRange0.minValue);
					slider_Display_Hue().Maximum(adlx_IntRange0.maxValue);
					slider_Display_Hue().StepFrequency(adlx_IntRange0.step);

					//Enable or disable interface
					slider_Display_Hue().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
					slider_Display_Hue().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				slider_Display_ColorTemperature().IsEnabled(false);
				slider_Display_Brightness().IsEnabled(false);
				slider_Display_Contrast().IsEnabled(false);
				slider_Display_Saturation().IsEnabled(false);
				slider_Display_Hue().IsEnabled(false);
			}

			//Get display vari-bright
			try
			{
				IADLXDisplayVariBrightPtr ppVariBright;
				adlx_Res0 = ppDispServices->GetVariBright(ppDisplayInfo, &ppVariBright);
				adlx_Res0 = ppVariBright->IsSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					//Set Vari-Bright
					adlx_Res0 = ppVariBright->IsEnabled(&adlx_Bool);
					toggleswitch_VariBright().IsOn(adlx_Bool);

					//Enable or disable interface
					toggleswitch_VariBright().IsEnabled(true);
					if (adlx_Bool)
					{
						combobox_Display_VariBright_Level().IsEnabled(true);
					}
					else
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
					//Enable or disable interface
					combobox_Display_VariBright_Level().IsEnabled(false);
					toggleswitch_VariBright().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				combobox_Display_VariBright_Level().IsEnabled(false);
				toggleswitch_VariBright().IsEnabled(false);
			}

			//Get display hdcp support
			try
			{
				IADLXDisplayHDCPPtr ppHDCP;
				adlx_Res0 = ppDispServices->GetHDCP(ppDisplayInfo, &ppHDCP);
				adlx_Res0 = ppHDCP->IsSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = ppHDCP->IsEnabled(&adlx_Bool);
					toggleswitch_HDCPSupport().IsOn(adlx_Bool);

					//Enable or disable interface
					toggleswitch_HDCPSupport().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
					toggleswitch_HDCPSupport().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_HDCPSupport().IsEnabled(false);
			}

			//Get display relative voltage swing
			try
			{
				IADLXDisplayConnectivityExperiencePtr ppDisplayConnectivityExperience;
				adlx_Res0 = ppDispServices->GetDisplayConnectivityExperience(ppDisplayInfo, &ppDisplayConnectivityExperience);
				adlx_Res0 = ppDisplayConnectivityExperience->GetRelativeVoltageSwing(&adlx_Int0);
				if (ADLX_FAILED(adlx_Res0))
				{
					//Enable or disable interface
					slider_Display_RelativeVoltageSwing().IsEnabled(false);
				}
				else
				{
					slider_Display_RelativeVoltageSwing().Value(adlx_Int0);
					slider_Display_RelativeVoltageSwing().Minimum(-2);
					slider_Display_RelativeVoltageSwing().Maximum(2);
					slider_Display_RelativeVoltageSwing().StepFrequency(1);
					//Fix find way to check support and get ranges

					//Enable or disable interface
					slider_Display_RelativeVoltageSwing().IsEnabled(true);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				slider_Display_RelativeVoltageSwing().IsEnabled(false);
			}

			//Get display relative preset emphasis
			try
			{
				IADLXDisplayConnectivityExperiencePtr ppDisplayConnectivityExperience;
				adlx_Res0 = ppDispServices->GetDisplayConnectivityExperience(ppDisplayInfo, &ppDisplayConnectivityExperience);
				adlx_Res0 = ppDisplayConnectivityExperience->GetRelativePreEmphasis(&adlx_Int0);
				if (ADLX_FAILED(adlx_Res0))
				{
					//Enable or disable interface
					slider_Display_RelativePreEmphasis().IsEnabled(false);
				}
				else
				{
					slider_Display_RelativePreEmphasis().Value(adlx_Int0);
					slider_Display_RelativePreEmphasis().Minimum(-2);
					slider_Display_RelativePreEmphasis().Maximum(2);
					slider_Display_RelativePreEmphasis().StepFrequency(1);
					//Fix find way to check support and get ranges

					//Enable or disable interface
					slider_Display_RelativePreEmphasis().IsEnabled(true);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				slider_Display_RelativePreEmphasis().IsEnabled(false);
			}

			//Set result
			AVDebugWriteLine("ADLX loaded display values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading display values.");
		}
	}
}