#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	std::optional<DisplaySettings> MainPage::DisplaySettings_Generate_FromADL(int adapterIndex, int displayIndex, std::wstring application, bool loadDefault)
	{
		try
		{
			DisplaySettings displaySettings{};

			//Device identifier
			displaySettings.DeviceId = AdlxGetDisplayIdentifier(adapterIndex, displayIndex);

			//Device application
			displaySettings.Application = application;

			//HDR Enabled
			try
			{
				ADLDisplayID displayId{};
				displayId.iDisplayLogicalAdapterIndex = adapterIndex;
				displayId.iDisplayLogicalIndex = displayIndex;

				int hdrSupported = -1;
				int hdrEnabled = -1;
				adl_Res0 = _ADL2_Display_HDRState_Get(adl_Context, adapterIndex, displayId, &hdrSupported, &hdrEnabled);
				if (adl_Res0 == ADL_OK)
				{
					//Set default
					displaySettings.HdrEnabled.Default = 0;

					//Set current
					displaySettings.HdrEnabled.Current = hdrEnabled;

					//Set support
					displaySettings.HdrEnabled.Support = hdrSupported;
				}
			}
			catch (...) {}

			//FreeSync Mode
			try
			{
				int freeSyncCurrent = -1;
				int freeSyncDefault = -1;
				int freeSyncMinRefreshRateInMicroHz = -1;
				int freeSyncMaxRefreshRateInMicroHz = -1;
				adl_Res0 = _ADL2_Display_FreeSyncState_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &freeSyncCurrent, &freeSyncDefault, &freeSyncMinRefreshRateInMicroHz, &freeSyncMaxRefreshRateInMicroHz);
				if (adl_Res0 == ADL_OK)
				{
					//Set default
					displaySettings.FreeSyncMode.Default = 1;

					//Set current
					//Enumeration index correction
					if (freeSyncCurrent == 0)
					{
						//Disabled
						displaySettings.FreeSyncMode.Current = 0;
					}
					else if (freeSyncCurrent == 1)
					{
						//Static
						displaySettings.FreeSyncMode.Current = 2;
					}
					else
					{
						//Variable or combined
						displaySettings.FreeSyncMode.Current = 1;
					}

					//Set support
					displaySettings.FreeSyncMode.Support = true;
				}
			}
			catch (...) {}

			//Virtual Super Resolution
			try
			{
				ADLDisplayProperty displayProperty{};
				displayProperty.iSize = sizeof(displayProperty);
				displayProperty.iPropertyType = ADL_DL_DISPLAYPROPERTY_TYPE_DOWNSCALE;
				adl_Res0 = _ADL2_Display_Property_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &displayProperty);
				if (adl_Res0 == ADL_OK)
				{
					//Set default
					displaySettings.VsrEnabled.Default = 0;

					//Set current
					displaySettings.VsrEnabled.Current = displayProperty.iCurrent;

					//Set support
					displaySettings.VsrEnabled.Support = displayProperty.iSupport;
				}
			}
			catch (...) {}

			//Gpu Scaling
			try
			{
				int gpuScalingSupported = -1;
				int gpuScalingCurrent = -1;
				int gpuScalingDefault = -1;
				adl_Res0 = _ADL2_DFP_GPUScalingEnable_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &gpuScalingSupported, &gpuScalingCurrent, &gpuScalingDefault);
				if (adl_Res0 == ADL_OK)
				{
					//Set default
					displaySettings.GpuScalingEnabled.Default = gpuScalingDefault;

					//Set current
					displaySettings.GpuScalingEnabled.Current = gpuScalingCurrent;

					//Set support
					displaySettings.GpuScalingEnabled.Support = gpuScalingSupported;
				}
			}
			catch (...) {}

			//Integer Scaling
			try
			{
				ADLDisplayProperty displayProperty{};
				displayProperty.iSize = sizeof(displayProperty);
				displayProperty.iPropertyType = ADL_DL_DISPLAYPROPERTY_TYPE_INTEGER_SCALING;
				adl_Res0 = _ADL2_Display_Property_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &displayProperty);
				if (adl_Res0 == ADL_OK)
				{
					//Set default
					displaySettings.IntegerScalingEnabled.Default = displayProperty.iDefault;

					//Set current
					displaySettings.IntegerScalingEnabled.Current = displayProperty.iCurrent;

					//Set support
					displaySettings.IntegerScalingEnabled.Support = displayProperty.iSupport;
				}
			}
			catch (...) {}

			//Scaling Mode
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
				adl_Res1 = _ADL2_Display_ImageExpansion_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &imageExpansionSupported, &imageExpansionCurrent, &imageExpansionDefault);

				//Check results
				if (adl_Res0 == ADL_OK && adl_Res1 == ADL_OK)
				{
					//Set default
					displaySettings.ScalingMode.Default = 0;

					//Set current
					//Enumeration index correction
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

					displaySettings.ScalingMode.Current = currentMode;

					//Set support
					displaySettings.ScalingMode.Support = true;
				}
			}
			catch (...) {}

			//Color Depth
			try
			{
				int colorDepth = -1;
				adl_Res0 = _ADL2_Display_ColorDepth_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &colorDepth);
				if (adl_Res0 == ADL_OK)
				{
					//Set default
					displaySettings.ColorDepth.Default = 1;

					//Set current
					displaySettings.ColorDepth.Current = colorDepth - 1;

					//Set support
					displaySettings.ColorDepth.Support = true;
				}
			}
			catch (...) {}

			//Pixel Format
			try
			{
				int pixelFormat = -1;
				adl_Res0 = _ADL2_Display_PixelFormat_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &pixelFormat);
				if (adl_Res0 == ADL_OK)
				{
					//Set default
					displaySettings.PixelFormat.Default = 2;

					//Set current
					//Enumeration index correction
					if (pixelFormat == ADL_DISPLAY_PIXELFORMAT_RGB_FULL_RANGE)
					{
						displaySettings.PixelFormat.Current = 0;
					}
					else if (pixelFormat == ADL_DISPLAY_PIXELFORMAT_YCRCB444)
					{
						displaySettings.PixelFormat.Current = 1;
					}
					else if (pixelFormat == ADL_DISPLAY_PIXELFORMAT_YCRCB422)
					{
						displaySettings.PixelFormat.Current = 2;
					}
					else if (pixelFormat == ADL_DISPLAY_PIXELFORMAT_RGB_LIMITED_RANGE)
					{
						displaySettings.PixelFormat.Current = 3;
					}
					else if (pixelFormat == ADL_DISPLAY_PIXELFORMAT_YCRCB420)
					{
						displaySettings.PixelFormat.Current = 4;
					}

					//Set support
					displaySettings.PixelFormat.Support = true;
				}
			}
			catch (...) {}

			//Color Enhancement
			try
			{
				int sceType = -1;
				int sceStatus = -1;
				adl_Res0 = _ADL2_Display_SCE_State_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &sceType, &sceStatus);
				if (adl_Res0 == ADL_OK)
				{
					//Set default
					displaySettings.ColorEnhancement.Default = 0;

					//Set current
					//Enumeration index correction
					if (sceType == (int)ADLColorEnhancementType::SCE_Disabled)
					{
						displaySettings.ColorEnhancement.Current = 0;
					}
					else if (sceType == (int)ADLColorEnhancementType::SCE_VividGaming)
					{
						displaySettings.ColorEnhancement.Current = 1;
					}
					else if (sceType == (int)ADLColorEnhancementType::SCE_DynamicContrast)
					{
						displaySettings.ColorEnhancement.Current = 2;
					}

					//Set support
					displaySettings.ColorEnhancement.Support = true;
				}
			}
			catch (...) {}

			//Color Temperature Control
			try
			{
				int lpTempSource;
				adl_Res0 = _ADL2_Display_ColorTemperatureSource_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &lpTempSource);
				if (adl_Res0 == ADL_OK)
				{
					//Set default
					displaySettings.ColorTemperatureControl.Default = 1;

					//Set current
					displaySettings.ColorTemperatureControl.Current = lpTempSource == ADL_DISPLAY_COLOR_TEMPERATURE_SOURCE_USER;

					//Set support
					displaySettings.ColorTemperatureControl.Support = true;
				}
			}
			catch (...) {}

			//Color Temperature Kelvin
			try
			{
				int colorCurrent = -1;
				int colorDefault = -1;
				int colorMin = -1;
				int colorMax = -1;
				int colorStep = -1;
				adl_Res0 = _ADL2_Display_Color_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, ADL_DISPLAY_COLOR_TEMPERATURE, &colorCurrent, &colorDefault, &colorMin, &colorMax, &colorStep);
				if (adl_Res0 == ADL_OK)
				{
					//Set default
					displaySettings.ColorTemperatureKelvin.Default = colorDefault;

					//Set current
					displaySettings.ColorTemperatureKelvin.Current = colorCurrent;

					//Set interface
					displaySettings.ColorTemperatureKelvin.Minimum = colorMin;
					displaySettings.ColorTemperatureKelvin.Maximum = colorMax;
					displaySettings.ColorTemperatureKelvin.Step = colorStep;

					//Set support
					displaySettings.ColorTemperatureKelvin.Support = true;
				}
			}
			catch (...) {}

			//Color Brightness
			try
			{
				int colorCurrent = -1;
				int colorDefault = -1;
				int colorMin = -1;
				int colorMax = -1;
				int colorStep = -1;
				adl_Res0 = _ADL2_Display_Color_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, ADL_DISPLAY_COLOR_BRIGHTNESS, &colorCurrent, &colorDefault, &colorMin, &colorMax, &colorStep);
				if (adl_Res0 == ADL_OK)
				{
					//Set default
					displaySettings.Brightness.Default = colorDefault;

					//Set current
					displaySettings.Brightness.Current = colorCurrent;

					//Set interface
					displaySettings.Brightness.Minimum = colorMin;
					displaySettings.Brightness.Maximum = colorMax;
					displaySettings.Brightness.Step = colorStep;

					//Set support
					displaySettings.Brightness.Support = true;
				}
			}
			catch (...) {}

			//Color Contrast
			try
			{
				int colorCurrent = -1;
				int colorDefault = -1;
				int colorMin = -1;
				int colorMax = -1;
				int colorStep = -1;
				adl_Res0 = _ADL2_Display_Color_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, ADL_DISPLAY_COLOR_CONTRAST, &colorCurrent, &colorDefault, &colorMin, &colorMax, &colorStep);
				if (adl_Res0 == ADL_OK)
				{
					//Set default
					displaySettings.Contrast.Default = colorDefault;

					//Set current
					displaySettings.Contrast.Current = colorCurrent;

					//Set interface
					displaySettings.Contrast.Minimum = colorMin;
					displaySettings.Contrast.Maximum = colorMax;
					displaySettings.Contrast.Step = colorStep;

					//Set support
					displaySettings.Contrast.Support = true;
				}
			}
			catch (...) {}

			//Color Saturation
			try
			{
				int colorCurrent = -1;
				int colorDefault = -1;
				int colorMin = -1;
				int colorMax = -1;
				int colorStep = -1;
				adl_Res0 = _ADL2_Display_Color_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, ADL_DISPLAY_COLOR_SATURATION, &colorCurrent, &colorDefault, &colorMin, &colorMax, &colorStep);
				if (adl_Res0 == ADL_OK)
				{
					//Set default
					displaySettings.Saturation.Default = colorDefault;

					//Set current
					displaySettings.Saturation.Current = colorCurrent;

					//Set interface
					displaySettings.Saturation.Minimum = colorMin;
					displaySettings.Saturation.Maximum = colorMax;
					displaySettings.Saturation.Step = colorStep;

					//Set support
					displaySettings.Saturation.Support = true;
				}
			}
			catch (...) {}

			//Color Hue
			try
			{
				int colorCurrent = -1;
				int colorDefault = -1;
				int colorMin = -1;
				int colorMax = -1;
				int colorStep = -1;
				adl_Res0 = _ADL2_Display_Color_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, ADL_DISPLAY_COLOR_HUE, &colorCurrent, &colorDefault, &colorMin, &colorMax, &colorStep);
				if (adl_Res0 == ADL_OK)
				{
					//Set default
					displaySettings.Hue.Default = colorDefault;

					//Set current
					displaySettings.Hue.Current = colorCurrent;

					//Set interface
					displaySettings.Hue.Minimum = colorMin;
					displaySettings.Hue.Maximum = colorMax;
					displaySettings.Hue.Step = colorStep;

					//Set support
					displaySettings.Hue.Support = true;
				}
			}
			catch (...) {}

			//Color Gamma Red, Green, Blue
			try
			{
				AdlGammaRamp gammaRamp{};
				adl_Res0 = _ADL2_Adapter_Gamma_Get(adl_Context, adl_Display_AdapterIndex, &gammaRamp);
				if (adl_Res0 == ADL_OK)
				{
					//Set default
					displaySettings.GammaRed.Default = 1.0F;
					displaySettings.GammaGreen.Default = 1.0F;
					displaySettings.GammaBlue.Default = 1.0F;

					//Set current
					float redGain = 1.0F;
					float greenGain = 1.0F;
					float blueGain = 1.0F;
					AdlGammaRampGet(gammaRamp, redGain, greenGain, blueGain);
					displaySettings.GammaRed.Current = redGain;
					displaySettings.GammaGreen.Current = greenGain;
					displaySettings.GammaBlue.Current = blueGain;

					//Set support
					displaySettings.GammaRed.Support = true;
					displaySettings.GammaGreen.Support = true;
					displaySettings.GammaBlue.Support = true;

					//Set interface
					displaySettings.GammaRed.Minimum = 0.5F;
					displaySettings.GammaRed.Maximum = 2.0F;
					displaySettings.GammaRed.Step = 0.01F;
					displaySettings.GammaGreen.Minimum = 0.5F;
					displaySettings.GammaGreen.Maximum = 2.0F;
					displaySettings.GammaGreen.Step = 0.01F;
					displaySettings.GammaBlue.Minimum = 0.5F;
					displaySettings.GammaBlue.Maximum = 2.0F;
					displaySettings.GammaBlue.Step = 0.01F;
				}
			}
			catch (...) {}

			//Color Deficiency Correction Control
			try
			{
				int cvdcEnabled;
				adl_Res0 = _ADL2_Display_CVDC_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, ADLCvdcType::CVDC_ENABLED, &cvdcEnabled);
				if (adl_Res0 == ADL_OK)
				{
					//Set default
					displaySettings.CVDCControl.Default = 0;

					//Set current
					displaySettings.CVDCControl.Current = cvdcEnabled;

					//Set support
					displaySettings.CVDCControl.Support = true;
				}
			}
			catch (...) {}

			//Color Deficiency Correction Protanopia
			try
			{
				int cvdcProtanopia;
				adl_Res0 = _ADL2_Display_CVDC_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, ADLCvdcType::CVDC_PROTANOPIA, &cvdcProtanopia);
				if (adl_Res0 == ADL_OK)
				{
					//Set default
					displaySettings.CVDCProtanopia.Default = 10;

					//Set setting
					displaySettings.CVDCProtanopia.Current = cvdcProtanopia;

					//Set support
					displaySettings.CVDCProtanopia.Support = true;

					//Set interface
					displaySettings.CVDCProtanopia.Minimum = 0;
					displaySettings.CVDCProtanopia.Maximum = 20;
					displaySettings.CVDCProtanopia.Step = 1;
				}
			}
			catch (...) {}

			//Color Deficiency Correction Deuteranopia
			try
			{
				int cvdcDeuteranopia;
				adl_Res0 = _ADL2_Display_CVDC_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, ADLCvdcType::CVDC_DEUTERANOPIA, &cvdcDeuteranopia);
				if (adl_Res0 == ADL_OK)
				{
					//Set default
					displaySettings.CVDCDeuteranopia.Default = 0;

					//Set setting
					displaySettings.CVDCDeuteranopia.Current = cvdcDeuteranopia;

					//Set support
					displaySettings.CVDCDeuteranopia.Support = true;

					//Set interface
					displaySettings.CVDCDeuteranopia.Minimum = 0;
					displaySettings.CVDCDeuteranopia.Maximum = 20;
					displaySettings.CVDCDeuteranopia.Step = 1;
				}
			}
			catch (...) {}

			//Color Deficiency Correction Tritanopia
			try
			{
				int cvdcTritanopia;
				adl_Res0 = _ADL2_Display_CVDC_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, ADLCvdcType::CVDC_TRITANOPIA, &cvdcTritanopia);
				if (adl_Res0 == ADL_OK)
				{
					//Set default
					displaySettings.CVDCTritanopia.Default = 0;

					//Set setting
					displaySettings.CVDCTritanopia.Current = cvdcTritanopia;

					//Set support
					displaySettings.CVDCTritanopia.Support = true;

					//Set interface
					displaySettings.CVDCTritanopia.Minimum = 0;
					displaySettings.CVDCTritanopia.Maximum = 20;
					displaySettings.CVDCTritanopia.Step = 1;
				}
			}
			catch (...) {}

			//Vari-Bright
			try
			{
				int variSupported = -1;
				int variEnabled = -1;
				int variVersion = -1;
				adl_Res0 = _ADL2_Adapter_VariBright_Caps(adl_Context, adl_Gpu_AdapterIndex, &variSupported, &variEnabled, &variVersion);
				if (adl_Res0 == ADL_OK)
				{
					//Set default
					displaySettings.VariBrightEnabled.Default = 1;

					//Set setting
					displaySettings.VariBrightEnabled.Current = variEnabled;

					//Set support
					displaySettings.VariBrightEnabled.Support = variSupported;
				}
			}
			catch (...) {}

			//Vari-Bright Level
			try
			{
				int variDefaultLevel = -1;
				int variNumberOfLevels = -1;
				int variStep = -1;
				int variCurrentLevel = -1;
				adl_Res0 = _ADL2_Adapter_VariBrightLevel_Get(adl_Context, adl_Gpu_AdapterIndex, &variDefaultLevel, &variNumberOfLevels, &variStep, &variCurrentLevel);
				if (adl_Res0 == ADL_OK)
				{
					//Set default
					displaySettings.VariBrightLevel.Default = 2;

					//Set setting
					displaySettings.VariBrightLevel.Current = variCurrentLevel;

					//Set support
					displaySettings.VariBrightLevel.Support = true;
				}
			}
			catch (...) {}

			//HDCP Support
			try
			{
				ADLHDCPSettings lpHDCPSettings{};
				adl_Res0 = _ADL2_Display_HDCP_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &lpHDCPSettings);
				if (adl_Res0 == ADL_OK)
				{
					//Set default
					displaySettings.HDCPEnabled.Default = 1;

					//Set setting
					displaySettings.HDCPEnabled.Current = lpHDCPSettings.iAllowAll;

					//Set support
					displaySettings.HDCPEnabled.Support = true;
				}
			}
			catch (...) {}

			//Set current value to default value
			if (loadDefault)
			{
				displaySettings.SetCurrentToDefault();
			}

			//Return result
			return displaySettings;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to generate display settings from ADL.");
			return std::nullopt;
		}
	}
}