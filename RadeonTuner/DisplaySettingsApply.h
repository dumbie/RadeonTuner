#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlDisplaySettingsApply(int displayAdapterIndex, int displayDisplayIndex, DisplaySettings targetSettings, DisplaySettings adlSettings, AdlSettingGet settingGet, bool appProfileOnly)
	{
		try
		{
			//Note: Comparing settings to prevent display from flashing because the driver does not checking if settings are already the same.

			//Pixel Format
			try
			{
				//Get and match values
				auto newValue = targetSettings.PixelFormat.Get(settingGet).value();
				auto currentValue = adlSettings.PixelFormat.Current.value();
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
				auto currentValue = adlSettings.HdrEnabled.Current.value();
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

			//FreeSync Mode and Frame Rate
			//Note: You can manually set the FreeSync Rate by using static usecase and providing microhertz for example: 50000000 (50Hz)
			//Note: You cannot get the currently set FreeSync Rate from the driver which makes the setting unreliable and seems to reset on reboot.
			try
			{
				//Get and match values
				auto newValueMode = targetSettings.FreeSyncMode.Get(settingGet).value();
				auto currentValueMode = adlSettings.FreeSyncMode.Current.value();
				if (newValueMode != currentValueMode)
				{
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

					//Delay to prevent no display issue
					Sleep(200);
				}
			}
			catch (...) {}

			//Virtual Super Resolution
			try
			{
				//Get and match values
				auto newValue = targetSettings.VsrEnabled.Get(settingGet).value();
				auto currentValue = adlSettings.VsrEnabled.Current.value();
				if (!appProfileOnly && newValue != currentValue)
				{
					//Set setting
					ADLDisplayProperty displayProperty{};
					displayProperty.iSize = sizeof(displayProperty);
					displayProperty.iPropertyType = ADL_DL_DISPLAYPROPERTY_TYPE_DOWNSCALE;
					displayProperty.iCurrent = newValue;
					adl_Res0 = _ADL2_Display_Property_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, &displayProperty);

					//Delay to prevent no display issue
					Sleep(200);
				}
			}
			catch (...) {}

			//Color Depth
			try
			{
				//Get and match values
				auto newValue = targetSettings.ColorDepth.Get(settingGet).value();
				auto currentValue = adlSettings.ColorDepth.Current.value();
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
				auto currentValue = adlSettings.ColorEnhancement.Current.value();
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
				auto currentValue = adlSettings.ColorTemperatureControl.Current.value();
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
				auto currentValue = adlSettings.ColorTemperatureKelvin.Current.value();
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
				auto currentValue = adlSettings.Brightness.Current.value();
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
				auto currentValue = adlSettings.Contrast.Current.value();
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
				auto currentValue = adlSettings.Saturation.Current.value();
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
				auto currentValue = adlSettings.Hue.Current.value();
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
				auto currentValue = adlSettings.CVDCControl.Current.value();
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
				auto currentValue = adlSettings.CVDCProtanopia.Current.value();
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
				auto currentValue = adlSettings.CVDCDeuteranopia.Current.value();
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
				auto currentValue = adlSettings.CVDCTritanopia.Current.value();
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
				auto currentValue = adlSettings.GpuScalingEnabled.Current.value();
				if (!appProfileOnly && newValue != currentValue)
				{
					//Set setting
					adl_Res0 = _ADL2_DFP_GPUScalingEnable_Set(adl_Context, displayAdapterIndex, displayDisplayIndex, newValue);

					//Delay to prevent no display issue
					Sleep(200);
				}
			}
			catch (...) {}

			//Integer Scaling
			try
			{
				//Get and match values
				auto newValue = targetSettings.IntegerScalingEnabled.Get(settingGet).value();
				auto currentValue = adlSettings.IntegerScalingEnabled.Current.value();
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
				auto currentValue = adlSettings.ScalingMode.Current.value();
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
				auto currentValue = adlSettings.HDCPEnabled.Current.value();
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
				auto currentValue = adlSettings.VariBrightEnabled.Current.value();
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
				auto currentValue = adlSettings.VariBrightLevel.Current.value();
				if (!appProfileOnly && newValue != currentValue)
				{
					//Set setting
					adl_Res0 = _ADL2_Adapter_VariBrightLevel_Set(adl_Context, displayAdapterIndex, newValue, true);
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