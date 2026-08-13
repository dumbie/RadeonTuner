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
			//Get current display settings
			DisplaySettings currentSettings = DisplaySettings_Generate_FromADL(displayAdapterIndex, displayDisplayIndex, targetSettings.Application.value()).value();

			//Pixel Format
			try
			{
				//Get and match values
				auto newValue = targetSettings.PixelFormat.Get(settingGet).value();
				auto currentValue = currentSettings.PixelFormat.Current.value();
				if (!appProfileOnly && newValue != currentValue)
				{
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
					Sleep(200);
				}
			}
			catch (...) {}

			//HDR Enabled
			//Note: HDR requires a 4:4:4 pixel format so set pixel format before HDR.
			try
			{
				//Get and match values
				auto newValue = targetSettings.HdrEnabled.Get(settingGet).value();
				auto currentValue = currentSettings.HdrEnabled.Current.value();
				if (!appProfileOnly && newValue != currentValue)
				{
					//Set setting
					ADLDisplayID displayId{};
					displayId.iDisplayLogicalAdapterIndex = displayAdapterIndex;
					displayId.iDisplayLogicalIndex = displayDisplayIndex;
					adl_Res0 = _ADL2_Display_HDRState_Set(adl_Context, displayAdapterIndex, displayId, newValue);

					//Delay to prevent no display issue
					Sleep(200);
				}
			}
			catch (...) {}

			//FreeSync Mode
			//Note: you can manually set the FreeSync Rate by using static usecase and providing microhertz for example: 50000000 (50Hz)
			try
			{
				//Get and match values
				auto newValue = targetSettings.FreeSyncMode.Get(settingGet).value();
				auto currentValue = currentSettings.FreeSyncMode.Current.value();
				if (newValue != currentValue)
				{
					//Enumeration index correction
					int freeSyncFlag = 0;
					if (newValue == 0)
					{
						//Disabled
						freeSyncFlag = 0;
					}
					else if (newValue == 1)
					{
						//Variable or combined
						freeSyncFlag = ADL_FREESYNC_USECASE_STATIC | ADL_FREESYNC_USECASE_VIDEO | ADL_FREESYNC_USECASE_GAMING;
					}
					else if (newValue == 2)
					{
						//Static
						freeSyncFlag = ADL_FREESYNC_USECASE_STATIC;
					}

					//Set setting
					adl_Res0 = _ADL2_Display_FreeSyncState_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, freeSyncFlag, 0);
				}
			}
			catch (...) {}

			//Virtual Super Resolution
			try
			{
				//Get and match values
				auto newValue = targetSettings.VsrEnabled.Get(settingGet).value();
				auto currentValue = currentSettings.VsrEnabled.Current.value();
				if (!appProfileOnly && newValue != currentValue)
				{
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
				//Get and match values
				auto newValue = targetSettings.ColorDepth.Get(settingGet).value();
				auto currentValue = currentSettings.ColorDepth.Current.value();
				if (!appProfileOnly && newValue != currentValue)
				{
					//Enumeration index correction
					int setValue = newValue + 1;

					//Set setting
					adl_Res0 = _ADL2_Display_ColorDepth_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, setValue);

					//Delay to prevent no display issue
					Sleep(200);
				}
			}
			catch (...) {}

			//Color Enhancement
			try
			{
				//Get and match values
				auto newValue = targetSettings.ColorEnhancement.Get(settingGet).value();
				auto currentValue = currentSettings.ColorEnhancement.Current.value();
				if (newValue != currentValue)
				{
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
			}
			catch (...) {}

			//Color Temperature Control
			try
			{
				//Get and match values
				auto newValue = targetSettings.ColorTemperatureControl.Get(settingGet).value();
				auto currentValue = currentSettings.ColorTemperatureControl.Current.value();
				if (newValue != currentValue)
				{
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
			}
			catch (...) {}

			//Color Temperature Kelvin
			try
			{
				//Get and match values
				auto newValue = targetSettings.ColorTemperatureKelvin.Get(settingGet).value();
				auto currentValue = currentSettings.ColorTemperatureKelvin.Current.value();
				if (newValue != currentValue)
				{
					//Set setting
					adl_Res0 = _ADL2_Display_Color_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, ADL_DISPLAY_COLOR_TEMPERATURE, newValue);
				}
			}
			catch (...) {}

			//Color Brightness
			try
			{
				//Get and match values
				auto newValue = targetSettings.Brightness.Get(settingGet).value();
				auto currentValue = currentSettings.Brightness.Current.value();
				if (newValue != currentValue)
				{
					//Set setting
					adl_Res0 = _ADL2_Display_Color_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, ADL_DISPLAY_COLOR_BRIGHTNESS, newValue);
				}
			}
			catch (...) {}

			//Color Contrast
			try
			{
				//Get and match values
				auto newValue = targetSettings.Contrast.Get(settingGet).value();
				auto currentValue = currentSettings.Contrast.Current.value();
				if (newValue != currentValue)
				{
					//Set setting
					adl_Res0 = _ADL2_Display_Color_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, ADL_DISPLAY_COLOR_CONTRAST, newValue);
				}
			}
			catch (...) {}

			//Color Saturation
			try
			{
				//Get and match values
				auto newValue = targetSettings.Saturation.Get(settingGet).value();
				auto currentValue = currentSettings.Saturation.Current.value();
				if (newValue != currentValue)
				{
					//Set setting
					adl_Res0 = _ADL2_Display_Color_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, ADL_DISPLAY_COLOR_SATURATION, newValue);
				}
			}
			catch (...) {}

			//Color Hue
			try
			{
				//Get and match values
				auto newValue = targetSettings.Hue.Get(settingGet).value();
				auto currentValue = currentSettings.Hue.Current.value();
				if (newValue != currentValue)
				{
					//Set setting
					adl_Res0 = _ADL2_Display_Color_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, ADL_DISPLAY_COLOR_HUE, newValue);
				}
			}
			catch (...) {}

			//Color Deficiency Correction Control
			try
			{
				//Get and match values
				auto newValue = targetSettings.CVDCControl.Get(settingGet).value();
				auto currentValue = currentSettings.CVDCControl.Current.value();
				if (newValue != currentValue)
				{
					//Set setting
					adl_Res0 = _ADL2_Display_CVDC_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, ADLCvdcType::CVDC_ENABLED, newValue);
				}
			}
			catch (...) {}

			//Color Deficiency Correction Protanopia
			try
			{
				//Get and match values
				auto newValue = targetSettings.CVDCProtanopia.Get(settingGet).value();
				auto currentValue = currentSettings.CVDCProtanopia.Current.value();
				if (newValue != currentValue)
				{
					//Set setting
					adl_Res0 = _ADL2_Display_CVDC_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, ADLCvdcType::CVDC_PROTANOPIA, newValue);
				}
			}
			catch (...) {}

			//Color Deficiency Correction Deuteranopia
			try
			{
				//Get and match values
				auto newValue = targetSettings.CVDCDeuteranopia.Get(settingGet).value();
				auto currentValue = currentSettings.CVDCDeuteranopia.Current.value();
				if (newValue != currentValue)
				{
					//Set setting
					adl_Res0 = _ADL2_Display_CVDC_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, ADLCvdcType::CVDC_DEUTERANOPIA, newValue);
				}
			}
			catch (...) {}

			//Color Deficiency Correction Tritanopia
			try
			{
				//Get and match values
				auto newValue = targetSettings.CVDCTritanopia.Get(settingGet).value();
				auto currentValue = currentSettings.CVDCTritanopia.Current.value();
				if (newValue != currentValue)
				{
					//Set setting
					adl_Res0 = _ADL2_Display_CVDC_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, ADLCvdcType::CVDC_TRITANOPIA, newValue);
				}
			}
			catch (...) {}

			//Gpu Scaling
			try
			{
				//Get and match values
				auto newValue = targetSettings.GpuScalingEnabled.Get(settingGet).value();
				auto currentValue = currentSettings.GpuScalingEnabled.Current.value();
				if (!appProfileOnly && newValue != currentValue)
				{
					//Set setting
					adl_Res0 = _ADL2_DFP_GPUScalingEnable_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, newValue);
				}
			}
			catch (...) {}

			//Integer Scaling
			try
			{
				//Get and match values
				auto newValue = targetSettings.IntegerScalingEnabled.Get(settingGet).value();
				auto currentValue = currentSettings.IntegerScalingEnabled.Current.value();
				if (!appProfileOnly && newValue != currentValue)
				{
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
				//Get and match values
				auto newValue = targetSettings.ScalingMode.Get(settingGet).value();
				auto currentValue = currentSettings.ScalingMode.Current.value();
				if (!appProfileOnly && newValue != currentValue)
				{
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
				//Get and match values
				auto newValue = targetSettings.HDCPEnabled.Get(settingGet).value();
				auto currentValue = currentSettings.HDCPEnabled.Current.value();
				if (!appProfileOnly && newValue != currentValue)
				{
					//Set setting
					adl_Res0 = _ADL2_Display_HDCP_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, false, newValue);
				}
			}
			catch (...) {}

			//Vari-Bright Enabled
			try
			{
				//Get and match values
				auto newValue = targetSettings.VariBrightEnabled.Get(settingGet).value();
				auto currentValue = currentSettings.VariBrightEnabled.Current.value();
				if (!appProfileOnly && newValue != currentValue)
				{
					//Set setting
					adl_Res0 = _ADL2_Adapter_VariBrightEnable_Set(adl_Context, displayAdapterIndex, newValue);
				}
			}
			catch (...) {}

			//Vari-Bright Level
			try
			{
				//Get and match values
				auto newValue = targetSettings.VariBrightLevel.Get(settingGet).value();
				auto currentValue = currentSettings.VariBrightLevel.Current.value();
				if (!appProfileOnly && newValue != currentValue)
				{
					//Set setting
					adl_Res0 = _ADL2_Adapter_VariBrightLevel_Set(adl_Context, displayAdapterIndex, newValue, true);
				}
			}
			catch (...) {}

			//Color Gamma Red Green Blue
			//Fix some applications and resolution changes seem to block or reset set gamma (ADL2 wraps around SetDeviceGammaRamp) find better alternative that always works.
			//Fix Applying other settings at the same time breaks applying gamma, wait before others are set before applying gamma.
			try
			{
				//Get and match values
				auto newValueRed = targetSettings.GammaRed.Get(settingGet).value();
				auto newValueGreen = targetSettings.GammaGreen.Get(settingGet).value();
				auto newValueBlue = targetSettings.GammaBlue.Get(settingGet).value();
				auto currentValueRed = currentSettings.GammaRed.Current.value();
				auto currentValueGreen = currentSettings.GammaGreen.Current.value();
				auto currentValueBlue = currentSettings.GammaBlue.Current.value();
				if (newValueRed != currentValueRed || newValueGreen != currentValueGreen || newValueBlue != currentValueBlue)
				{
					//Set setting
					AdlGammaRamp gammaRamp = AdlGammaRampBuild(newValueRed, newValueGreen, newValueBlue);
					adl_Res0 = _ADL2_Adapter_Gamma_Set(adl_Context, displayAdapterIndex, gammaRamp);
				}
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