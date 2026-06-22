#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesLoadDisplay()
	{
		try
		{
			//Set interface limits
			slider_Display_Protanopia().Minimum(0);
			slider_Display_Protanopia().Maximum(20);
			slider_Display_Protanopia().StepFrequency(1);
			slider_Display_Protanopia().SmallChange(1);

			slider_Display_Deuteranopia().Minimum(0);
			slider_Display_Deuteranopia().Maximum(20);
			slider_Display_Deuteranopia().StepFrequency(1);
			slider_Display_Deuteranopia().SmallChange(1);

			slider_Display_Tritanopia().Minimum(0);
			slider_Display_Tritanopia().Maximum(20);
			slider_Display_Tritanopia().StepFrequency(1);
			slider_Display_Tritanopia().SmallChange(1);

			//FixPort Check if display is active
			bool displayActive = true;
			//ADL2_Display_DisplayInfo_Get ADL_DISPLAY_DISPLAYINFO_DISPLAYCONNECTED

			//Get HDR State
			try
			{
				ADLDisplayID displayId{};
				displayId.iDisplayLogicalAdapterIndex = adl_Display_AdapterIndex;
				displayId.iDisplayLogicalIndex = adl_Display_DisplayIndex;

				int hdrSupported = -1;
				int hdrEnabled = -1;
				adl_Res0 = _ADL2_Display_HDRState_Get(adl_Context, adl_Display_AdapterIndex, displayId, &hdrSupported, &hdrEnabled);
				if (displayActive && adl_Res0 == ADL_OK)
				{
					//Set current
					toggleswitch_HdrEnable().IsOn(hdrEnabled);

					//Enable or disable interface
					toggleswitch_HdrEnable().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
					toggleswitch_HdrEnable().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_HdrEnable().IsEnabled(false);
			}

			//Get HDR Media Profile
			try
			{
				int hdrTypePreference = -1;
				adl_Res0 = _ADL2_Display_HdrTypePreference_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &hdrTypePreference);
				if (displayActive && adl_Res0 == ADL_OK)
				{
					//Set current
					combobox_Display_HdrTypePreference().SelectedIndex(hdrTypePreference);

					//Enable or disable interface
					combobox_Display_HdrTypePreference().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
					combobox_Display_HdrTypePreference().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				combobox_Display_HdrTypePreference().IsEnabled(false);
			}

			//Get FreeSync
			try
			{
				int freeSyncCurrent = -1;
				int freeSyncDefault = -1;
				int freeSyncMinRefreshRateInMicroHz = -1;
				int freeSyncMaxRefreshRateInMicroHz = -1;
				adl_Res0 = _ADL2_Display_FreeSyncState_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &freeSyncCurrent, &freeSyncDefault, &freeSyncMinRefreshRateInMicroHz, &freeSyncMaxRefreshRateInMicroHz);
				if (displayActive && adl_Res0 == ADL_OK)
				{
					//Set current
					toggleswitch_FreeSync().IsOn(freeSyncCurrent > 0);

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

			//Get Virtual Super Resolution
			try
			{
				ADLDisplayProperty displayProperty{};
				displayProperty.iSize = sizeof(displayProperty);
				displayProperty.iPropertyType = ADL_DL_DISPLAYPROPERTY_TYPE_DOWNSCALE;
				adl_Res0 = _ADL2_Display_Property_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &displayProperty);
				if (displayActive && adl_Res0 == ADL_OK)
				{
					toggleswitch_VSR().IsOn(displayProperty.iCurrent == 1);

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

			//Get GPU Scaling
			try
			{
				int gpuScalingSupported = -1;
				int gpuScalingCurrent = -1;
				int gpuScalingDefault = -1;
				adl_Res0 = _ADL2_DFP_GPUScalingEnable_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &gpuScalingSupported, &gpuScalingCurrent, &gpuScalingDefault);
				if (displayActive && adl_Res0 == ADL_OK)
				{
					toggleswitch_GPUScaling().IsOn(gpuScalingCurrent == 1);

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

			//Get Integer Scaling
			try
			{
				ADLDisplayProperty displayProperty{};
				displayProperty.iSize = sizeof(displayProperty);
				displayProperty.iPropertyType = ADL_DL_DISPLAYPROPERTY_TYPE_INTEGER_SCALING;
				adl_Res0 = _ADL2_Display_Property_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &displayProperty);
				if (displayActive && adl_Res0 == ADL_OK)
				{
					toggleswitch_IntegerScaling().IsOn(displayProperty.iCurrent == 1);

					//Enable or disable interface
					toggleswitch_IntegerScaling().IsEnabled(true);
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

			//Get Scaling Mode
			try
			{
				//Note: Do not use ADL2_Display_Property_Get ADL_DL_DISPLAYPROPERTY_TYPE_EXPANSIONMODE iExpansionMode is always 1 and set fails

				//Get current mode
				int aspectRatioSupport = -1;
				int aspectRatioCurrent = -1;
				int aspectRatioDefault = -1;
				adl_Res0 = _ADL2_Display_PreservedAspectRatio_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &aspectRatioSupport, &aspectRatioCurrent, &aspectRatioDefault);

				int imageExpansionSupported = -1;
				int imageExpansionCurrent = -1;
				int imageExpansionDefault = -1;
				adl_Res0 = _ADL2_Display_ImageExpansion_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &imageExpansionSupported, &imageExpansionCurrent, &imageExpansionDefault);

				//Check current mode
				int currentMode = 0;
				if (aspectRatioCurrent == 1)
				{
					//Preserve Aspect Ratio
					currentMode = 0;
				}
				else if (imageExpansionCurrent == 1)
				{
					//Full Panel
					currentMode = 1;
				}
				else if (imageExpansionCurrent == 0)
				{
					//Center
					currentMode = 2;
				}

				//Update interface
				if (displayActive)
				{
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

			//Get Color Depth
			try
			{
				int colorDepth = -1;
				adl_Res0 = _ADL2_Display_ColorDepth_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &colorDepth);
				if (displayActive && adl_Res0 == ADL_OK)
				{
					combobox_Display_ColorDepth().SelectedIndex(colorDepth - 1);

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

			//Get Pixel Format
			try
			{
				int pixelFormat = -1;
				adl_Res0 = _ADL2_Display_PixelFormat_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &pixelFormat);
				if (displayActive && adl_Res0 == ADL_OK)
				{
					//Enumeration index correction
					if (pixelFormat == ADL_DISPLAY_PIXELFORMAT_RGB_FULL_RANGE)
					{
						combobox_Display_PixelFormat().SelectedIndex(0);
					}
					else if (pixelFormat == ADL_DISPLAY_PIXELFORMAT_YCRCB444)
					{
						combobox_Display_PixelFormat().SelectedIndex(1);
					}
					else if (pixelFormat == ADL_DISPLAY_PIXELFORMAT_YCRCB422)
					{
						combobox_Display_PixelFormat().SelectedIndex(2);
					}
					else if (pixelFormat == ADL_DISPLAY_PIXELFORMAT_RGB_LIMITED_RANGE)
					{
						combobox_Display_PixelFormat().SelectedIndex(3);
					}
					else if (pixelFormat == ADL_DISPLAY_PIXELFORMAT_YCRCB420)
					{
						combobox_Display_PixelFormat().SelectedIndex(4);
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

			//Get Color Enhancement
			try
			{
				int sceType = -1;
				int sceStatus = -1;
				adl_Res0 = _ADL2_Display_SCE_State_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &sceType, &sceStatus);
				if (displayActive && adl_Res0 == ADL_OK)
				{
					//Enumeration index correction
					if (sceType == ADLColorEnhancementType::SCE_Disabled)
					{
						combobox_Display_DisplayColorEnhancement().SelectedIndex(0);
					}
					else if (sceType == ADLColorEnhancementType::SCE_VividGaming)
					{
						combobox_Display_DisplayColorEnhancement().SelectedIndex(1);
					}
					else if (sceType == ADLColorEnhancementType::SCE_DynamicContrast)
					{
						combobox_Display_DisplayColorEnhancement().SelectedIndex(2);
					}

					//Enable or disable interface
					combobox_Display_DisplayColorEnhancement().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
					combobox_Display_DisplayColorEnhancement().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				combobox_Display_DisplayColorEnhancement().IsEnabled(false);
			}

			//Get Color Temperature Control
			try
			{
				int lpTempSource;
				adl_Res0 = _ADL2_Display_ColorTemperatureSource_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &lpTempSource);
				if (displayActive && adl_Res0 == ADL_OK)
				{
					bool userControlEnabled = lpTempSource == ADL_DISPLAY_COLOR_TEMPERATURE_SOURCE_USER;
					toggleswitch_Display_ColorTemperature_Control().IsOn(userControlEnabled);

					//Enable or disable interface
					toggleswitch_Display_ColorTemperature_Control().IsEnabled(true);
					if (userControlEnabled)
					{
						slider_Display_ColorTemperature_Kelvin().IsEnabled(true);
					}
					else
					{
						slider_Display_ColorTemperature_Kelvin().IsEnabled(false);
					}
				}
				else
				{
					//Enable or disable interface
					toggleswitch_Display_ColorTemperature_Control().IsEnabled(false);
					slider_Display_ColorTemperature_Kelvin().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_Display_ColorTemperature_Control().IsEnabled(false);
				slider_Display_ColorTemperature_Kelvin().IsEnabled(false);
			}

			//Get Color Temperature
			try
			{
				int colorCurrent = -1;
				int colorDefault = -1;
				int colorMin = -1;
				int colorMax = -1;
				int colorStep = -1;
				adl_Res0 = _ADL2_Display_Color_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, ADL_DISPLAY_COLOR_TEMPERATURE, &colorCurrent, &colorDefault, &colorMin, &colorMax, &colorStep);
				if (displayActive && adl_Res0 == ADL_OK)
				{
					slider_Display_ColorTemperature_Kelvin().Minimum(colorMin);
					slider_Display_ColorTemperature_Kelvin().Maximum(colorMax);
					slider_Display_ColorTemperature_Kelvin().StepFrequency(colorStep);
					slider_Display_ColorTemperature_Kelvin().SmallChange(colorStep);
					slider_Display_ColorTemperature_Kelvin().Value(colorCurrent);
				}
				else
				{
					//Enable or disable interface
					slider_Display_ColorTemperature_Kelvin().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				slider_Display_ColorTemperature_Kelvin().IsEnabled(false);
			}

			//Get Color Brightness
			try
			{
				int colorCurrent = -1;
				int colorDefault = -1;
				int colorMin = -1;
				int colorMax = -1;
				int colorStep = -1;
				adl_Res0 = _ADL2_Display_Color_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, ADL_DISPLAY_COLOR_BRIGHTNESS, &colorCurrent, &colorDefault, &colorMin, &colorMax, &colorStep);
				if (displayActive && adl_Res0 == ADL_OK)
				{
					slider_Display_Brightness().Minimum(colorMin);
					slider_Display_Brightness().Maximum(colorMax);
					slider_Display_Brightness().StepFrequency(colorStep);
					slider_Display_Brightness().SmallChange(colorStep);
					slider_Display_Brightness().Value(colorCurrent);
				}
				else
				{
					//Enable or disable interface
					slider_Display_Brightness().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				slider_Display_Brightness().IsEnabled(false);
			}

			//Get Color Contrast
			try
			{
				int colorCurrent = -1;
				int colorDefault = -1;
				int colorMin = -1;
				int colorMax = -1;
				int colorStep = -1;
				adl_Res0 = _ADL2_Display_Color_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, ADL_DISPLAY_COLOR_CONTRAST, &colorCurrent, &colorDefault, &colorMin, &colorMax, &colorStep);
				if (displayActive && adl_Res0 == ADL_OK)
				{
					slider_Display_Contrast().Minimum(colorMin);
					slider_Display_Contrast().Maximum(colorMax);
					slider_Display_Contrast().StepFrequency(colorStep);
					slider_Display_Contrast().SmallChange(colorStep);
					slider_Display_Contrast().Value(colorCurrent);
				}
				else
				{
					//Enable or disable interface
					slider_Display_Contrast().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				slider_Display_Contrast().IsEnabled(false);
			}

			//Get Color Saturation
			try
			{
				int colorCurrent = -1;
				int colorDefault = -1;
				int colorMin = -1;
				int colorMax = -1;
				int colorStep = -1;
				adl_Res0 = _ADL2_Display_Color_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, ADL_DISPLAY_COLOR_SATURATION, &colorCurrent, &colorDefault, &colorMin, &colorMax, &colorStep);
				if (displayActive && adl_Res0 == ADL_OK)
				{
					slider_Display_Saturation().Minimum(colorMin);
					slider_Display_Saturation().Maximum(colorMax);
					slider_Display_Saturation().StepFrequency(colorStep);
					slider_Display_Saturation().SmallChange(colorStep);
					slider_Display_Saturation().Value(colorCurrent);
				}
				else
				{
					//Enable or disable interface
					slider_Display_Saturation().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				slider_Display_Saturation().IsEnabled(false);
			}

			//Get Color Hue
			try
			{
				int colorCurrent = -1;
				int colorDefault = -1;
				int colorMin = -1;
				int colorMax = -1;
				int colorStep = -1;
				adl_Res0 = _ADL2_Display_Color_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, ADL_DISPLAY_COLOR_HUE, &colorCurrent, &colorDefault, &colorMin, &colorMax, &colorStep);
				if (displayActive && adl_Res0 == ADL_OK)
				{
					slider_Display_Hue().Minimum(colorMin);
					slider_Display_Hue().Maximum(colorMax);
					slider_Display_Hue().StepFrequency(colorStep);
					slider_Display_Hue().SmallChange(colorStep);
					slider_Display_Hue().Value(colorCurrent);
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
				slider_Display_Hue().IsEnabled(false);
			}

			//Get Color Vision Deficiency
			try
			{
				if (displayActive)
				{
					//Get Enabled
					int cvdcEnabled;
					adl_Res0 = _ADL2_Display_CVDC_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, CVDC_ENABLED, &cvdcEnabled);
					toggleswitch_Display_CVDC_Control().IsOn(cvdcEnabled);

					//Get Protanopia
					int cvdcProtanopia;
					adl_Res0 = _ADL2_Display_CVDC_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, CVDC_PROTANOPIA, &cvdcProtanopia);
					slider_Display_Protanopia().Value(cvdcProtanopia);

					//Get Deuteranopia
					int cvdcDeuteranopia;
					adl_Res0 = _ADL2_Display_CVDC_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, CVDC_DEUTERANOPIA, &cvdcDeuteranopia);
					slider_Display_Deuteranopia().Value(cvdcDeuteranopia);

					//Get Tritanopia
					int cvdcTritanopia;
					adl_Res0 = _ADL2_Display_CVDC_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, CVDC_TRITANOPIA, &cvdcTritanopia);
					slider_Display_Tritanopia().Value(cvdcTritanopia);

					//Enable or disable interface
					toggleswitch_Display_CVDC_Control().IsEnabled(true);
					slider_Display_Protanopia().IsEnabled(cvdcEnabled);
					slider_Display_Deuteranopia().IsEnabled(cvdcEnabled);
					slider_Display_Tritanopia().IsEnabled(cvdcEnabled);
				}
				else
				{
					//Enable or disable interface
					toggleswitch_Display_CVDC_Control().IsEnabled(false);
					slider_Display_Protanopia().IsEnabled(false);
					slider_Display_Deuteranopia().IsEnabled(false);
					slider_Display_Tritanopia().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_Display_CVDC_Control().IsEnabled(false);
				slider_Display_Protanopia().IsEnabled(false);
				slider_Display_Deuteranopia().IsEnabled(false);
				slider_Display_Tritanopia().IsEnabled(false);
			}

			//Get Vari-Bright
			try
			{
				int variSupported = -1;
				int variEnabled = -1;
				int variVersion = -1;
				adl_Res0 = _ADL2_Adapter_VariBright_Caps(adl_Context, adl_Gpu_AdapterIndex, &variSupported, &variEnabled, &variVersion);
				if (displayActive && adl_Res0 == ADL_OK)
				{
					toggleswitch_VariBright().IsOn(variEnabled);

					//Enable or disable interface
					toggleswitch_VariBright().IsEnabled(true);
					if (variEnabled)
					{
						combobox_Display_VariBright_Level().IsEnabled(true);
					}
					else
					{
						combobox_Display_VariBright_Level().IsEnabled(false);
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

			//Get Vari-Bright Level
			try
			{
				int variDefaultLevel = -1;
				int variNumberOfLevels = -1;
				int variStep = -1;
				int variCurrentLevel = -1;
				adl_Res0 = _ADL2_Adapter_VariBrightLevel_Get(adl_Context, adl_Gpu_AdapterIndex, &variDefaultLevel, &variNumberOfLevels, &variStep, &variCurrentLevel);
				if (displayActive && adl_Res0 == ADL_OK)
				{
					combobox_Display_VariBright_Level().SelectedIndex(variCurrentLevel);
				}
				else
				{
					//Enable or disable interface
					combobox_Display_VariBright_Level().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				combobox_Display_VariBright_Level().IsEnabled(false);
			}

			//Get HDCP Support
			try
			{
				ADLHDCPSettings lpHDCPSettings{};
				adl_Res0 = _ADL2_Display_HDCP_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &lpHDCPSettings);
				if (displayActive && adl_Res0 == ADL_OK)
				{
					toggleswitch_HDCPSupport().IsOn(lpHDCPSettings.iAllowAll);

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

			//Eyefinity
			try
			{
				//Enable or disable interface
				if (displayActive)
				{
					button_Eyefinity_CreateCustom().IsEnabled(true);
					button_Eyefinity_DeleteAll().IsEnabled(true);
					button_Eyefinity_Enable().IsEnabled(true);
					button_Eyefinity_Disable().IsEnabled(true);
					slider_Eyefinity_Columns().IsEnabled(true);
					slider_Eyefinity_Rows().IsEnabled(true);
					listview_EyefinityMonitorIndex().IsEnabled(true);
					combobox_EyefinityMonitorOrientation().IsEnabled(true);

					bool eyefinityAutomatic = toggleswitch_Eyefinity_Automatic().IsOn();
					toggleswitch_Eyefinity_Automatic().IsEnabled(true);
					combobox_Eyefinity_Applications().IsEnabled(eyefinityAutomatic);
					button_Eyefinity_AddExe().IsEnabled(eyefinityAutomatic);
					button_Eyefinity_Remove().IsEnabled(eyefinityAutomatic);
				}
				else
				{
					button_Eyefinity_CreateCustom().IsEnabled(false);
					button_Eyefinity_DeleteAll().IsEnabled(false);
					button_Eyefinity_Enable().IsEnabled(false);
					button_Eyefinity_Disable().IsEnabled(false);
					slider_Eyefinity_Columns().IsEnabled(false);
					slider_Eyefinity_Rows().IsEnabled(false);
					listview_EyefinityMonitorIndex().IsEnabled(false);
					combobox_EyefinityMonitorOrientation().IsEnabled(false);
					toggleswitch_Eyefinity_Automatic().IsEnabled(false);
					combobox_Eyefinity_Applications().IsEnabled(false);
					button_Eyefinity_AddExe().IsEnabled(false);
					button_Eyefinity_Remove().IsEnabled(false);
				}
			}
			catch (...) {}

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