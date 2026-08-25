#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlDisplaySettingsApply(int displayAdapterIndex, int displayDisplayIndex, DisplaySettings targetSettings, AdlSettingGet settingGet, bool appProfileOnly)
	{
		try
		{
			//Pixel Format
			try
			{
				if (!appProfileOnly)
				{
					//Get value
					auto newValue = targetSettings.PixelFormat.Get(settingGet).value();

					//Enumeration index correction
					int setValue = 0;
					if (newValue == 0)
					{
						setValue = ADL_DISPLAY_PIXELFORMAT_RGB_FULL_RANGE;
					}
					else if (newValue == 1)
					{
						setValue = ADL_DISPLAY_PIXELFORMAT_YCRCB444;
					}
					else if (newValue == 2)
					{
						setValue = ADL_DISPLAY_PIXELFORMAT_YCRCB422;
					}
					else if (newValue == 3)
					{
						setValue = ADL_DISPLAY_PIXELFORMAT_RGB_LIMITED_RANGE;
					}
					else if (newValue == 4)
					{
						setValue = ADL_DISPLAY_PIXELFORMAT_YCRCB420;
					}

					//Set setting
					adl_Res0 = _ADL2_Display_PixelFormat_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, setValue);

					//Delay to prevent no display issue
					Sleep(250);
				}
			}
			catch (...) {}

			//HDR Enabled
			//Note: HDR requires a 4:4:4 pixel format so set pixel format before HDR.
			try
			{
				if (!appProfileOnly)
				{
					//Get value
					auto newValue = targetSettings.HdrEnabled.Get(settingGet).value();

					//Set setting
					ADLDisplayID displayId{};
					displayId.iDisplayLogicalAdapterIndex = displayAdapterIndex;
					displayId.iDisplayLogicalIndex = displayDisplayIndex;
					adl_Res0 = _ADL2_Display_HDRState_Set(adl_Context, displayAdapterIndex, displayId, newValue);

					//Delay to prevent no display issue
					Sleep(250);
				}
			}
			catch (...) {}

			//FreeSync Mode and Frame Rate
			//Note: You can manually set the FreeSync Rate by using static usecase and providing microhertz for example: 50000000 (50Hz)
			//Note: You cannot get the currently set FreeSync Rate from the driver which makes the setting unreliable and seems to reset on reboot.
			try
			{
				//Get value
				auto newValueMode = targetSettings.FreeSyncMode.Get(settingGet).value();

				//Enumeration index correction
				int freeSyncMode = 0;
				int freeSyncFrameRate = 0;
				if (newValueMode == 0)
				{
					//Disabled
					freeSyncMode = 0;
					freeSyncFrameRate = 0;
				}
				else if (newValueMode == 1)
				{
					//Variable or combined
					freeSyncMode = ADL_FREESYNC_USECASE_STATIC | ADL_FREESYNC_USECASE_VIDEO | ADL_FREESYNC_USECASE_GAMING;
					freeSyncFrameRate = 0;
				}
				else if (newValueMode == 2)
				{
					//Static
					freeSyncMode = ADL_FREESYNC_USECASE_STATIC;
					freeSyncFrameRate = 0;
				}

				//Set setting
				adl_Res0 = _ADL2_Display_FreeSyncState_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, freeSyncMode, freeSyncFrameRate);
			}
			catch (...) {}

			//Virtual Super Resolution
			try
			{
				if (!appProfileOnly)
				{
					//Get value
					auto newValue = targetSettings.VsrEnabled.Get(settingGet).value();

					//Set setting
					ADLDisplayProperty displayProperty{};
					displayProperty.iSize = sizeof(displayProperty);
					displayProperty.iPropertyType = ADL_DL_DISPLAYPROPERTY_TYPE_DOWNSCALE;
					displayProperty.iCurrent = newValue;
					adl_Res0 = _ADL2_Display_Property_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, &displayProperty);
				}
			}
			catch (...) {}

			//Color Depth
			try
			{
				if (!appProfileOnly)
				{
					//Get value
					auto newValue = targetSettings.ColorDepth.Get(settingGet).value();

					//Enumeration index correction
					int setValue = newValue + 1;

					//Set setting
					adl_Res0 = _ADL2_Display_ColorDepth_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, setValue);

					//Delay to prevent no display issue
					Sleep(250);
				}
			}
			catch (...) {}

			//Color Enhancement
			try
			{
				//Get value
				auto newValue = targetSettings.ColorEnhancement.Get(settingGet).value();

				//Enumeration index correction
				int setValue = 0;
				if (newValue == 0)
				{
					setValue = (int)ADLColorEnhancementType::SCE_Disabled;
				}
				else if (newValue == 1)
				{
					setValue = (int)ADLColorEnhancementType::SCE_VividGaming;
				}
				else if (newValue == 2)
				{
					setValue = (int)ADLColorEnhancementType::SCE_DynamicContrast;
				}

				//Set Setting
				adl_Res0 = _ADL2_Display_SCE_State_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, setValue);
			}
			catch (...) {}

			//Color Temperature Control
			try
			{
				//Get value
				auto newValue = targetSettings.ColorTemperatureControl.Get(settingGet).value();

				//Set setting
				if (newValue)
				{
					adl_Res0 = _ADL2_Display_ColorTemperatureSource_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, ADL_DISPLAY_COLOR_TEMPERATURE_SOURCE_USER);
				}
				else
				{
					adl_Res0 = _ADL2_Display_ColorTemperatureSource_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, ADL_DISPLAY_COLOR_TEMPERATURE_SOURCE_EDID);
				}
			}
			catch (...) {}

			//Color Temperature Kelvin
			try
			{
				//Get value
				auto newValue = targetSettings.ColorTemperatureKelvin.Get(settingGet).value();

				//Set setting
				adl_Res0 = _ADL2_Display_Color_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, ADL_DISPLAY_COLOR_TEMPERATURE, newValue);
			}
			catch (...) {}

			//Color Brightness
			try
			{
				//Get value
				auto newValue = targetSettings.Brightness.Get(settingGet).value();

				//Set setting
				adl_Res0 = _ADL2_Display_Color_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, ADL_DISPLAY_COLOR_BRIGHTNESS, newValue);
			}
			catch (...) {}

			//Color Contrast
			try
			{
				//Get value
				auto newValue = targetSettings.Contrast.Get(settingGet).value();

				//Set setting
				adl_Res0 = _ADL2_Display_Color_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, ADL_DISPLAY_COLOR_CONTRAST, newValue);
			}
			catch (...) {}

			//Color Saturation
			try
			{
				//Get value
				auto newValue = targetSettings.Saturation.Get(settingGet).value();

				//Set setting
				adl_Res0 = _ADL2_Display_Color_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, ADL_DISPLAY_COLOR_SATURATION, newValue);
			}
			catch (...) {}

			//Color Hue
			try
			{
				//Get value
				auto newValue = targetSettings.Hue.Get(settingGet).value();

				//Set setting
				adl_Res0 = _ADL2_Display_Color_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, ADL_DISPLAY_COLOR_HUE, newValue);
			}
			catch (...) {}

			//Color Deficiency Correction Control
			try
			{
				//Get value
				auto newValue = targetSettings.CVDCControl.Get(settingGet).value();

				//Set setting
				adl_Res0 = _ADL2_Display_CVDC_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, ADLCvdcType::CVDC_ENABLED, newValue);
			}
			catch (...) {}

			//Color Deficiency Correction Protanopia
			try
			{
				//Get value
				auto newValue = targetSettings.CVDCProtanopia.Get(settingGet).value();

				//Set setting
				adl_Res0 = _ADL2_Display_CVDC_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, ADLCvdcType::CVDC_PROTANOPIA, newValue);
			}
			catch (...) {}

			//Color Deficiency Correction Deuteranopia
			try
			{
				//Get value
				auto newValue = targetSettings.CVDCDeuteranopia.Get(settingGet).value();

				//Set setting
				adl_Res0 = _ADL2_Display_CVDC_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, ADLCvdcType::CVDC_DEUTERANOPIA, newValue);
			}
			catch (...) {}

			//Color Deficiency Correction Tritanopia
			try
			{
				//Get value
				auto newValue = targetSettings.CVDCTritanopia.Get(settingGet).value();

				//Set setting
				adl_Res0 = _ADL2_Display_CVDC_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, ADLCvdcType::CVDC_TRITANOPIA, newValue);
			}
			catch (...) {}

			//Gpu Scaling
			try
			{
				if (!appProfileOnly)
				{
					//Get value
					auto newValue = targetSettings.GpuScalingEnabled.Get(settingGet).value();

					//Set setting
					adl_Res0 = _ADL2_DFP_GPUScalingEnable_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, newValue);
				}
			}
			catch (...) {}

			//Integer Scaling
			try
			{
				if (!appProfileOnly)
				{
					//Get value
					auto newValue = targetSettings.IntegerScalingEnabled.Get(settingGet).value();

					//Set setting
					ADLDisplayProperty displayProperty{};
					displayProperty.iSize = sizeof(displayProperty);
					displayProperty.iPropertyType = ADL_DL_DISPLAYPROPERTY_TYPE_INTEGER_SCALING;
					displayProperty.iCurrent = newValue;
					adl_Res0 = _ADL2_Display_Property_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, &displayProperty);
				}
			}
			catch (...) {}

			//Scaling Mode
			try
			{
				if (!appProfileOnly)
				{
					//Get value
					auto newValue = targetSettings.ScalingMode.Get(settingGet).value();

					//Set setting
					//Enumeration index correction
					if (newValue == 0)
					{
						//Preserve Aspect Ratio
						adl_Res0 = _ADL2_Display_PreservedAspectRatio_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, 1);
					}
					else if (newValue == 1)
					{
						//Full Panel
						adl_Res0 = _ADL2_Display_ImageExpansion_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, 1);
					}
					else if (newValue == 2)
					{
						//Centered
						adl_Res0 = _ADL2_Display_ImageExpansion_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, 0);
					}
				}
			}
			catch (...) {}

			//HDCP Support
			try
			{
				if (!appProfileOnly)
				{
					//Get value
					auto newValue = targetSettings.HDCPEnabled.Get(settingGet).value();

					//Set setting
					adl_Res0 = _ADL2_Display_HDCP_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, false, newValue);
				}
			}
			catch (...) {}

			//Vari-Bright Enabled
			try
			{
				if (!appProfileOnly)
				{
					//Get value
					auto newValue = targetSettings.VariBrightEnabled.Get(settingGet).value();

					//Set setting
					adl_Res0 = _ADL2_Adapter_VariBrightEnable_Set(adl_Context, displayAdapterIndex, newValue);
				}
			}
			catch (...) {}

			//Vari-Bright Level
			try
			{
				if (!appProfileOnly)
				{
					//Get value
					auto newValue = targetSettings.VariBrightLevel.Get(settingGet).value();

					//Set setting
					adl_Res0 = _ADL2_Adapter_VariBrightLevel_Set(adl_Context, displayAdapterIndex, newValue, true);
				}
			}
			catch (...) {}

			//Color Gamma Red Green Blue
			//Fix Some applications and resolution changes seem to block or reset set gamma (ADL2 wraps around SetDeviceGammaRamp) find better alternative that always works.
			//Fix Applying other settings at the same time breaks applying gamma, wait before others are set before applying gamma.
			try
			{
				//Get value
				auto newValueRed = targetSettings.GammaRed.Get(settingGet).value();
				auto newValueGreen = targetSettings.GammaGreen.Get(settingGet).value();
				auto newValueBlue = targetSettings.GammaBlue.Get(settingGet).value();

				//Note: Gamma sometimes gets stuck so resetting it to default first may help.

				//Set setting
				AdlGammaRamp gammaRampDefault = AdlGammaRampBuild(1.00, 1.00, 1.00);
				adl_Res0 = _ADL2_Adapter_Gamma_Set(adl_Context, displayAdapterIndex, gammaRampDefault);

				//Set setting
				AdlGammaRamp gammaRampTarget = AdlGammaRampBuild(newValueRed, newValueGreen, newValueBlue);
				adl_Res0 = _ADL2_Adapter_Gamma_Set(adl_Context, displayAdapterIndex, gammaRampTarget);
			}
			catch (...) {}

			//Return result
			return true;
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}
}