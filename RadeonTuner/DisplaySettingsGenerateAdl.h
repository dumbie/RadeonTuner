#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	std::optional<DisplaySettings> MainPage::DisplaySettings_Generate_FromADL(int adapterIndex, int displayIndex)
	{
		try
		{
			//Fix find way to check if setting is supported and disable interface.

			DisplaySettings displaySettings{};

			//Device identifier
			try
			{
				std::wstring device_id_w = AdlxGetDisplayIdentifier(adapterIndex, displayIndex);
				displaySettings.DeviceId = wstring_to_string(device_id_w);
			}
			catch (...) {}

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
					//Set current
					displaySettings.HdrEnabled.Current = hdrEnabled;

					//Set default
					displaySettings.HdrEnabled.Default = 1;

					//Set support
					displaySettings.HdrEnabled.Support = hdrSupported;
				}
				else
				{
					//Set support
					displaySettings.HdrEnabled.Support = false;
				}
			}
			catch (...) {}

			//HDR Media Profile
			try
			{
				UINT hdrTypePreference = -1;
				adl_Res0 = _ADL2_Display_HdrTypePreference_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &hdrTypePreference);
				if (adl_Res0 == ADL_OK)
				{
					//Set current
					displaySettings.HdrMediaProfile.Current = hdrTypePreference;

					//Set default
					displaySettings.HdrMediaProfile.Default = 0;

					//Set support
					displaySettings.HdrMediaProfile.Support = true;
				}
				else
				{
					//Set support
					displaySettings.HdrMediaProfile.Support = false;
				}
			}
			catch (...) {}

			//FreeSync
			try
			{
				int freeSyncCurrent = -1;
				int freeSyncDefault = -1;
				int freeSyncMinRefreshRateInMicroHz = -1;
				int freeSyncMaxRefreshRateInMicroHz = -1;
				adl_Res0 = _ADL2_Display_FreeSyncState_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &freeSyncCurrent, &freeSyncDefault, &freeSyncMinRefreshRateInMicroHz, &freeSyncMaxRefreshRateInMicroHz);
				if (adl_Res0 == ADL_OK)
				{
					//Set current
					displaySettings.FreeSyncEnabled.Current = freeSyncCurrent > 0;

					//Set default
					displaySettings.FreeSyncEnabled.Default = 1;

					//Set support
					displaySettings.FreeSyncEnabled.Support = true;
				}
				else
				{
					//Set support
					displaySettings.FreeSyncEnabled.Support = false;
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
					//Set current
					displaySettings.VsrEnabled.Current = displayProperty.iCurrent;

					//Set default
					displaySettings.VsrEnabled.Default = 0;

					//Set support
					displaySettings.VsrEnabled.Support = displayProperty.iSupport;
				}
				else
				{
					//Set support
					displaySettings.VsrEnabled.Support = false;
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
					//Set current
					displaySettings.GpuScalingEnabled.Current = gpuScalingCurrent;

					//Set default
					displaySettings.GpuScalingEnabled.Default = gpuScalingDefault;

					//Set support
					displaySettings.GpuScalingEnabled.Support = gpuScalingSupported;
				}
				else
				{
					//Set support
					displaySettings.GpuScalingEnabled.Support = false;
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
					//Set setting
					displaySettings.IntegerScalingEnabled.Current = displayProperty.iCurrent;

					//Set default
					displaySettings.IntegerScalingEnabled.Default = displayProperty.iDefault;

					//Set support
					displaySettings.IntegerScalingEnabled.Support = displayProperty.iSupport;
				}
				else
				{
					//Set support
					displaySettings.IntegerScalingEnabled.Support = false;
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

					//Set setting
					displaySettings.ScalingMode.Current = currentMode;

					//Set default
					displaySettings.ScalingMode.Default = 0;

					//Set support
					displaySettings.ScalingMode.Support = true;
				}
				else
				{
					//Set support
					displaySettings.ScalingMode.Support = false;
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
					//Set setting
					displaySettings.ColorDepth.Current = colorDepth - 1;

					//Set default
					displaySettings.ColorDepth.Default = 0;

					//Set support
					displaySettings.ColorDepth.Support = true;
				}
				else
				{
					//Set support
					displaySettings.ColorDepth.Support = false;
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
					//Set setting
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

					//Set default
					displaySettings.PixelFormat.Default = 2;

					//Set support
					displaySettings.PixelFormat.Support = true;
				}
				else
				{
					//Set support
					displaySettings.PixelFormat.Support = false;
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
					//Set setting
					//Enumeration index correction
					if (sceType == ADLColorEnhancementType::SCE_Disabled)
					{
						displaySettings.ColorEnhancement.Current = 0;
					}
					else if (sceType == ADLColorEnhancementType::SCE_VividGaming)
					{
						displaySettings.ColorEnhancement.Current = 1;
					}
					else if (sceType == ADLColorEnhancementType::SCE_DynamicContrast)
					{
						displaySettings.ColorEnhancement.Current = 2;
					}

					//Set default
					displaySettings.ColorEnhancement.Default = 0;

					//Set support
					displaySettings.ColorEnhancement.Support = true;
				}
				else
				{
					//Set support
					displaySettings.ColorEnhancement.Support = false;
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
					//Set setting
					displaySettings.ColorTemperatureControl.Current = lpTempSource == ADL_DISPLAY_COLOR_TEMPERATURE_SOURCE_USER;

					//Set default
					displaySettings.ColorTemperatureControl.Default = 1;

					//Set support
					displaySettings.ColorTemperatureControl.Support = true;
				}
				else
				{
					//Set support
					displaySettings.ColorTemperatureControl.Support = false;
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
					//Set setting
					displaySettings.ColorTemperatureKelvin.Current = colorCurrent;

					//Set default
					displaySettings.ColorTemperatureKelvin.Default = colorDefault;

					//Set interface
					displaySettings.ColorTemperatureKelvin.Minimum = colorMin;
					displaySettings.ColorTemperatureKelvin.Maximum = colorMax;
					displaySettings.ColorTemperatureKelvin.Step = colorStep;

					//Set support
					displaySettings.ColorTemperatureKelvin.Support = true;
				}
				else
				{
					//Set support
					displaySettings.ColorTemperatureKelvin.Support = false;
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
					//Set setting
					displaySettings.Brightness.Current = colorCurrent;

					//Set default
					displaySettings.Brightness.Default = colorDefault;

					//Set interface
					displaySettings.Brightness.Minimum = colorMin;
					displaySettings.Brightness.Maximum = colorMax;
					displaySettings.Brightness.Step = colorStep;

					//Set support
					displaySettings.Brightness.Support = true;
				}
				else
				{
					//Set support
					displaySettings.Brightness.Support = false;
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
					//Set setting
					displaySettings.Contrast.Current = colorCurrent;

					//Set default
					displaySettings.Contrast.Default = colorDefault;

					//Set interface
					displaySettings.Contrast.Minimum = colorMin;
					displaySettings.Contrast.Maximum = colorMax;
					displaySettings.Contrast.Step = colorStep;

					//Set support
					displaySettings.Contrast.Support = true;
				}
				else
				{
					//Set support
					displaySettings.Contrast.Support = false;
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
					//Set setting
					displaySettings.Saturation.Current = colorCurrent;

					//Set default
					displaySettings.Saturation.Default = colorDefault;

					//Set interface
					displaySettings.Saturation.Minimum = colorMin;
					displaySettings.Saturation.Maximum = colorMax;
					displaySettings.Saturation.Step = colorStep;

					//Set support
					displaySettings.Saturation.Support = true;
				}
				else
				{
					//Set support
					displaySettings.Saturation.Support = false;
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
					//Set setting
					displaySettings.Hue.Current = colorCurrent;

					//Set default
					displaySettings.Hue.Default = colorDefault;

					//Set interface
					displaySettings.Hue.Minimum = colorMin;
					displaySettings.Hue.Maximum = colorMax;
					displaySettings.Hue.Step = colorStep;

					//Set support
					displaySettings.Hue.Support = true;
				}
				else
				{
					//Set support
					displaySettings.Hue.Support = false;
				}
			}
			catch (...) {}

			//Color Deficiency Correction Control
			try
			{
				int cvdcEnabled;
				adl_Res0 = _ADL2_Display_CVDC_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, CVDC_ENABLED, &cvdcEnabled);
				if (adl_Res0 == ADL_OK)
				{
					//Set setting
					displaySettings.CVDCControl.Current = cvdcEnabled;

					//Set default
					displaySettings.CVDCControl.Default = 0;

					//Set support
					displaySettings.CVDCControl.Support = true;
				}
				else
				{
					//Set support
					displaySettings.CVDCControl.Support = false;
				}
			}
			catch (...) {}

			//Color Deficiency Correction Protanopia
			try
			{
				int cvdcProtanopia;
				adl_Res0 = _ADL2_Display_CVDC_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, CVDC_PROTANOPIA, &cvdcProtanopia);
				if (adl_Res0 == ADL_OK)
				{
					//Set setting
					displaySettings.CVDCProtanopia.Current = cvdcProtanopia;

					//Set default
					displaySettings.CVDCProtanopia.Default = 10;

					//Set support
					displaySettings.CVDCProtanopia.Support = true;

					//Set interface
					displaySettings.CVDCProtanopia.Minimum = 0;
					displaySettings.CVDCProtanopia.Maximum = 20;
					displaySettings.CVDCProtanopia.Step = 1;
				}
				else
				{
					//Set support
					displaySettings.CVDCProtanopia.Support = false;
				}
			}
			catch (...) {}

			//Color Deficiency Correction Deuteranopia
			try
			{
				int cvdcDeuteranopia;
				adl_Res0 = _ADL2_Display_CVDC_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, CVDC_DEUTERANOPIA, &cvdcDeuteranopia);
				if (adl_Res0 == ADL_OK)
				{
					//Set setting
					displaySettings.CVDCDeuteranopia.Current = cvdcDeuteranopia;

					//Set default
					displaySettings.CVDCDeuteranopia.Default = 0;

					//Set support
					displaySettings.CVDCDeuteranopia.Support = true;

					//Set interface
					displaySettings.CVDCDeuteranopia.Minimum = 0;
					displaySettings.CVDCDeuteranopia.Maximum = 20;
					displaySettings.CVDCDeuteranopia.Step = 1;
				}
				else
				{
					//Set support
					displaySettings.CVDCDeuteranopia.Support = false;
				}
			}
			catch (...) {}

			//Color Deficiency Correction Tritanopia
			try
			{
				int cvdcTritanopia;
				adl_Res0 = _ADL2_Display_CVDC_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, CVDC_TRITANOPIA, &cvdcTritanopia);
				if (adl_Res0 == ADL_OK)
				{
					//Set setting
					displaySettings.CVDCTritanopia.Current = cvdcTritanopia;

					//Set default
					displaySettings.CVDCTritanopia.Default = 0;

					//Set support
					displaySettings.CVDCTritanopia.Support = true;

					//Set interface
					displaySettings.CVDCTritanopia.Minimum = 0;
					displaySettings.CVDCTritanopia.Maximum = 20;
					displaySettings.CVDCTritanopia.Step = 1;
				}
				else
				{
					//Set support
					displaySettings.CVDCTritanopia.Support = false;
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
					//Set setting
					displaySettings.VariBrightEnabled.Current = variEnabled;

					//Set default
					displaySettings.VariBrightEnabled.Default = 1;

					//Set support
					displaySettings.VariBrightEnabled.Support = variSupported;
				}
				else
				{
					//Set support
					displaySettings.VariBrightEnabled.Support = false;
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
					//Set setting
					displaySettings.VariBrightLevel.Current = variCurrentLevel;

					//Set default
					displaySettings.VariBrightLevel.Default = 2;

					//Set support
					displaySettings.VariBrightLevel.Support = true;
				}
				else
				{
					//Set support
					displaySettings.VariBrightLevel.Support = false;
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
					//Set setting
					displaySettings.HDCPEnabled.Current = lpHDCPSettings.iAllowAll;

					//Set default
					displaySettings.HDCPEnabled.Default = 1;

					//Set support
					displaySettings.HDCPEnabled.Support = true;
				}
				else
				{
					//Set support
					displaySettings.HDCPEnabled.Support = false;
				}
			}
			catch (...) {}

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