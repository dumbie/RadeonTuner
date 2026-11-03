#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::DisplaySettings_Convert_ToUI_Adl(DisplaySettings displaySettings, AdlSettingGet settingType)
	{
		try
		{
			//HDR Enabled
			if (displaySettings.HdrEnabled.Support && displaySettings.HdrEnabled.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = displaySettings.HdrEnabled.Get(settingType, true).value();

				//Set setting value
				toggleswitch_Display_HdrEnabled().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_Display_HdrEnabled_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_Display_HdrEnabled().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Display_HdrEnabled_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_Display_HdrEnabled().IsEnabled(false);
			}

			//FreeSync Mode
			if (displaySettings.FreeSyncMode.Support && displaySettings.FreeSyncMode.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = displaySettings.FreeSyncMode.Get(settingType, true).value();

				//Set setting value
				combobox_Display_FreeSyncMode().SelectedIndex(valueInt);

				//Set hint value
				std::wstring valueHint = ADL_FREESYNC_MODE[valueInt];
				textblock_Display_FreeSyncMode_Value().Text(valueHint);

				//Enable or disable interface
				combobox_Display_FreeSyncMode().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Display_FreeSyncMode_Value().Text(L"");

				//Enable or disable interface
				combobox_Display_FreeSyncMode().IsEnabled(false);
			}

			//Virtual Super Resolution
			if (displaySettings.VsrEnabled.Support && displaySettings.VsrEnabled.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = displaySettings.VsrEnabled.Get(settingType, true).value();

				//Set setting value
				toggleswitch_Display_VSR().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_Display_VSR_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_Display_VSR().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Display_VSR_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_Display_VSR().IsEnabled(false);
			}

			//Gpu Scaling
			if (displaySettings.GpuScalingEnabled.Support && displaySettings.GpuScalingEnabled.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = displaySettings.GpuScalingEnabled.Get(settingType, true).value();

				//Set setting value
				toggleswitch_Display_GpuScaling().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_Display_GpuScaling_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_Display_GpuScaling().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Display_GpuScaling_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_Display_GpuScaling().IsEnabled(false);
			}

			//Integer Scaling
			if (displaySettings.IntegerScalingEnabled.Support && displaySettings.IntegerScalingEnabled.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = displaySettings.IntegerScalingEnabled.Get(settingType, true).value();

				//Set setting value
				toggleswitch_Display_IntegerScaling().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_Display_IntegerScaling_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_Display_IntegerScaling().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Display_IntegerScaling_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_Display_IntegerScaling().IsEnabled(false);
			}

			//Scaling Mode
			if (displaySettings.ScalingMode.Support && displaySettings.ScalingMode.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = displaySettings.ScalingMode.Get(settingType, true).value();

				//Set setting value
				combobox_Display_ScalingMode().SelectedIndex(valueInt);

				//Set hint value
				std::wstring valueHint = ADLX_SCALE_MODE_STRING[valueInt];
				textblock_Display_ScalingMode_Value().Text(valueHint);

				//Enable or disable interface
				combobox_Display_ScalingMode().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Display_ScalingMode_Value().Text(L"");

				//Enable or disable interface
				combobox_Display_ScalingMode().IsEnabled(false);
			}

			//Color Depth
			if (displaySettings.ColorDepth.Support && displaySettings.ColorDepth.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = displaySettings.ColorDepth.Get(settingType, true).value();

				//Set setting value
				combobox_Display_ColorDepth().SelectedIndex(valueInt);

				//Set hint value
				std::wstring valueHint = ADLX_COLOR_DEPTH_STRING[valueInt + 1];
				textblock_Display_ColorDepth_Value().Text(valueHint);

				//Enable or disable interface
				combobox_Display_ColorDepth().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Display_ColorDepth_Value().Text(L"");

				//Enable or disable interface
				combobox_Display_ColorDepth().IsEnabled(false);
			}

			//Pixel Format
			if (displaySettings.PixelFormat.Support && displaySettings.PixelFormat.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = displaySettings.PixelFormat.Get(settingType, true).value();

				//Set setting value
				combobox_Display_PixelFormat().SelectedIndex(valueInt);

				//Set hint value
				std::wstring valueHint = ADLX_PIXEL_FORMAT_STRING[valueInt + 1];
				textblock_Display_PixelFormat_Value().Text(valueHint);

				//Enable or disable interface
				combobox_Display_PixelFormat().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Display_PixelFormat_Value().Text(L"");

				//Enable or disable interface
				combobox_Display_PixelFormat().IsEnabled(false);
			}

			//Color Enhancement
			if (displaySettings.ColorEnhancement.Support && displaySettings.ColorEnhancement.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = displaySettings.ColorEnhancement.Get(settingType, true).value();

				//Set setting value
				combobox_Display_DisplayColorEnhancement().SelectedIndex(valueInt);

				//Set hint value
				std::wstring valueHint = ADLX_SCE_PROFILE_STRING[valueInt];
				textblock_Display_DisplayColorEnhancement_Value().Text(valueHint);

				//Enable or disable interface
				combobox_Display_DisplayColorEnhancement().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Display_DisplayColorEnhancement_Value().Text(L"");

				//Enable or disable interface
				combobox_Display_DisplayColorEnhancement().IsEnabled(false);
			}

			//Color Temperature Control
			if (displaySettings.ColorTemperatureControl.Support && displaySettings.ColorTemperatureControl.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = displaySettings.ColorTemperatureControl.Get(settingType, true).value();

				//Set setting value
				toggleswitch_Display_ColorTemperature_Control().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_Display_ColorTemperature_Control_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_Display_ColorTemperature_Control().IsEnabled(true);
				slider_Display_ColorTemperature_Kelvin().IsEnabled(valueInt);
			}
			else
			{
				//Set hint value
				textblock_Display_ColorTemperature_Control_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_Display_ColorTemperature_Control().IsEnabled(false);
				slider_Display_ColorTemperature_Kelvin().IsEnabled(false);
			}

			//Color Temperature Kelvin
			if (displaySettings.ColorTemperatureKelvin.Support && displaySettings.ColorTemperatureKelvin.Get(settingType, true).has_value())
			{
				//Set interface
				if (displaySettings.ColorTemperatureKelvin.Minimum.has_value())
				{
					slider_Display_ColorTemperature_Kelvin().Minimum(displaySettings.ColorTemperatureKelvin.Minimum.value());
					slider_Display_ColorTemperature_Kelvin().Maximum(displaySettings.ColorTemperatureKelvin.Maximum.value());
					slider_Display_ColorTemperature_Kelvin().StepFrequency(displaySettings.ColorTemperatureKelvin.Step.value());
					slider_Display_ColorTemperature_Kelvin().SmallChange(displaySettings.ColorTemperatureKelvin.Step.value());
				}

				//Get setting
				int valueInt = displaySettings.ColorTemperatureKelvin.Get(settingType, true).value();

				//Set setting value
				slider_Display_ColorTemperature_Kelvin().Value(valueInt);

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt) + L"K";
				textblock_Display_ColorTemperature_Kelvin_Value().Text(valueHint);
			}
			else
			{
				//Set hint value
				textblock_Display_ColorTemperature_Kelvin_Value().Text(L"");

				//Enable or disable interface
				slider_Display_ColorTemperature_Kelvin().IsEnabled(false);
			}

			//Color Brightness
			if (displaySettings.Brightness.Support && displaySettings.Brightness.Get(settingType, true).has_value())
			{
				//Set interface
				if (displaySettings.Brightness.Minimum.has_value())
				{
					slider_Display_Brightness().Minimum(displaySettings.Brightness.Minimum.value());
					slider_Display_Brightness().Maximum(displaySettings.Brightness.Maximum.value());
					slider_Display_Brightness().StepFrequency(displaySettings.Brightness.Step.value());
					slider_Display_Brightness().SmallChange(displaySettings.Brightness.Step.value());
				}

				//Get setting
				int valueInt = displaySettings.Brightness.Get(settingType, true).value();

				//Set setting value
				slider_Display_Brightness().Value(valueInt);

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt);
				textblock_Display_Brightness_Value().Text(valueHint);

				//Enable or disable interface
				slider_Display_Brightness().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Display_Brightness_Value().Text(L"");

				//Enable or disable interface
				slider_Display_Brightness().IsEnabled(false);
			}

			//Color Contrast
			if (displaySettings.Contrast.Support && displaySettings.Contrast.Get(settingType, true).has_value())
			{
				//Set interface
				if (displaySettings.Contrast.Minimum.has_value())
				{
					slider_Display_Contrast().Minimum(displaySettings.Contrast.Minimum.value());
					slider_Display_Contrast().Maximum(displaySettings.Contrast.Maximum.value());
					slider_Display_Contrast().StepFrequency(displaySettings.Contrast.Step.value());
					slider_Display_Contrast().SmallChange(displaySettings.Contrast.Step.value());
				}

				//Get setting
				int valueInt = displaySettings.Contrast.Get(settingType, true).value();

				//Set setting value
				slider_Display_Contrast().Value(valueInt);

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt);
				textblock_Display_Contrast_Value().Text(valueHint);

				//Enable or disable interface
				slider_Display_Contrast().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Display_Contrast_Value().Text(L"");

				//Enable or disable interface
				slider_Display_Contrast().IsEnabled(false);
			}

			//Color Saturation
			if (displaySettings.Saturation.Support && displaySettings.Saturation.Get(settingType, true).has_value())
			{
				//Set interface
				if (displaySettings.Saturation.Minimum.has_value())
				{
					slider_Display_Saturation().Minimum(displaySettings.Saturation.Minimum.value());
					slider_Display_Saturation().Maximum(displaySettings.Saturation.Maximum.value());
					slider_Display_Saturation().StepFrequency(displaySettings.Saturation.Step.value());
					slider_Display_Saturation().SmallChange(displaySettings.Saturation.Step.value());
				}

				//Get setting
				int valueInt = displaySettings.Saturation.Get(settingType, true).value();

				//Set setting value
				slider_Display_Saturation().Value(valueInt);

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt);
				textblock_Display_Saturation_Value().Text(valueHint);

				//Enable or disable interface
				slider_Display_Saturation().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Display_Saturation_Value().Text(L"");

				//Enable or disable interface
				slider_Display_Saturation().IsEnabled(false);
			}

			//Color Hue
			if (displaySettings.Hue.Support && displaySettings.Hue.Get(settingType, true).has_value())
			{
				//Set interface
				if (displaySettings.Hue.Minimum.has_value())
				{
					slider_Display_Hue().Minimum(displaySettings.Hue.Minimum.value());
					slider_Display_Hue().Maximum(displaySettings.Hue.Maximum.value());
					slider_Display_Hue().StepFrequency(displaySettings.Hue.Step.value());
					slider_Display_Hue().SmallChange(displaySettings.Hue.Step.value());
				}

				//Get setting
				int valueInt = displaySettings.Hue.Get(settingType, true).value();

				//Set setting value
				slider_Display_Hue().Value(valueInt);

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt);
				textblock_Display_Hue_Value().Text(valueHint);

				//Enable or disable interface
				slider_Display_Hue().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Display_Hue_Value().Text(L"");

				//Enable or disable interface
				slider_Display_Hue().IsEnabled(false);
			}

			//Color Deficiency Correction Control
			if (displaySettings.CVDCControl.Support && displaySettings.CVDCControl.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = displaySettings.CVDCControl.Get(settingType, true).value();

				//Set setting value
				toggleswitch_Display_CVDC_Control().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_Display_CVDC_Control_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_Display_CVDC_Control().IsEnabled(true);
				slider_Display_Protanopia().IsEnabled(valueInt);
				slider_Display_Deuteranopia().IsEnabled(valueInt);
				slider_Display_Tritanopia().IsEnabled(valueInt);
			}
			else
			{
				//Set hint value
				textblock_Display_CVDC_Control_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_Display_CVDC_Control().IsEnabled(false);
				slider_Display_Protanopia().IsEnabled(false);
				slider_Display_Deuteranopia().IsEnabled(false);
				slider_Display_Tritanopia().IsEnabled(false);
			}

			//Color Deficiency Correction Protanopia
			if (displaySettings.CVDCProtanopia.Support && displaySettings.CVDCProtanopia.Get(settingType, true).has_value())
			{
				//Set interface
				if (displaySettings.CVDCProtanopia.Minimum.has_value())
				{
					slider_Display_Protanopia().Minimum(displaySettings.CVDCProtanopia.Minimum.value());
					slider_Display_Protanopia().Maximum(displaySettings.CVDCProtanopia.Maximum.value());
					slider_Display_Protanopia().StepFrequency(displaySettings.CVDCProtanopia.Step.value());
					slider_Display_Protanopia().SmallChange(displaySettings.CVDCProtanopia.Step.value());
				}

				//Get setting
				int valueInt = displaySettings.CVDCProtanopia.Get(settingType, true).value();

				//Set setting value
				slider_Display_Protanopia().Value(valueInt);

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt);
				textblock_Display_Protanopia_Value().Text(valueHint);
			}
			else
			{
				//Set hint value
				textblock_Display_Protanopia_Value().Text(L"");

				//Enable or disable interface
				slider_Display_Protanopia().IsEnabled(false);
			}

			//Color Deficiency Correction Deuteranopia
			if (displaySettings.CVDCDeuteranopia.Support && displaySettings.CVDCDeuteranopia.Get(settingType, true).has_value())
			{
				//Set interface
				if (displaySettings.CVDCDeuteranopia.Minimum.has_value())
				{
					slider_Display_Deuteranopia().Minimum(displaySettings.CVDCDeuteranopia.Minimum.value());
					slider_Display_Deuteranopia().Maximum(displaySettings.CVDCDeuteranopia.Maximum.value());
					slider_Display_Deuteranopia().StepFrequency(displaySettings.CVDCDeuteranopia.Step.value());
					slider_Display_Deuteranopia().SmallChange(displaySettings.CVDCDeuteranopia.Step.value());
				}

				//Get setting
				int valueInt = displaySettings.CVDCDeuteranopia.Get(settingType, true).value();

				//Set setting value
				slider_Display_Deuteranopia().Value(valueInt);

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt);
				textblock_Display_Deuteranopia_Value().Text(valueHint);
			}
			else
			{
				//Set hint value
				textblock_Display_Deuteranopia_Value().Text(L"");

				//Enable or disable interface
				slider_Display_Deuteranopia().IsEnabled(false);
			}

			//Color Deficiency Correction Tritanopia
			if (displaySettings.CVDCTritanopia.Support && displaySettings.CVDCTritanopia.Get(settingType, true).has_value())
			{
				//Set interface
				if (displaySettings.CVDCTritanopia.Minimum.has_value())
				{
					slider_Display_Tritanopia().Minimum(displaySettings.CVDCTritanopia.Minimum.value());
					slider_Display_Tritanopia().Maximum(displaySettings.CVDCTritanopia.Maximum.value());
					slider_Display_Tritanopia().StepFrequency(displaySettings.CVDCTritanopia.Step.value());
					slider_Display_Tritanopia().SmallChange(displaySettings.CVDCTritanopia.Step.value());
				}

				//Get setting
				int valueInt = displaySettings.CVDCTritanopia.Get(settingType, true).value();

				//Set setting value
				slider_Display_Tritanopia().Value(valueInt);

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt);
				textblock_Display_Tritanopia_Value().Text(valueHint);
			}
			else
			{
				//Set hint value
				textblock_Display_Tritanopia_Value().Text(L"");

				//Enable or disable interface
				slider_Display_Tritanopia().IsEnabled(false);
			}

			//Vari-Bright Enabled
			if (displaySettings.VariBrightEnabled.Support && displaySettings.VariBrightEnabled.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = displaySettings.VariBrightEnabled.Get(settingType, true).value();

				//Set setting value
				toggleswitch_Display_VariBright().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_Display_VariBright_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_Display_VariBright().IsEnabled(true);
				combobox_Display_VariBright_Level().IsEnabled(valueInt);
			}
			else
			{
				//Set hint value
				textblock_Display_VariBright_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_Display_VariBright().IsEnabled(false);
				combobox_Display_VariBright_Level().IsEnabled(false);
			}

			//Vari-Bright Level
			if (displaySettings.VariBrightLevel.Support && displaySettings.VariBrightLevel.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = displaySettings.VariBrightLevel.Get(settingType, true).value();

				//Set setting value
				combobox_Display_VariBright_Level().SelectedIndex(valueInt);

				//Set hint value
				std::wstring valueHint = ADLX_VARIBRIGHT_LEVEL_STRING[valueInt];
				textblock_Display_VariBright_Level_Value().Text(valueHint);
			}
			else
			{
				//Set hint value
				textblock_Display_VariBright_Level_Value().Text(L"");

				//Enable or disable interface
				combobox_Display_VariBright_Level().IsEnabled(false);
			}

			//HDCP Support
			if (displaySettings.HDCPEnabled.Support && displaySettings.HDCPEnabled.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = displaySettings.HDCPEnabled.Get(settingType, true).value();

				//Set setting value
				toggleswitch_Display_HDCPSupport().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_Display_HDCPSupport_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_Display_HDCPSupport().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Display_HDCPSupport_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_Display_HDCPSupport().IsEnabled(false);
			}

			//Top buttons
			button_AppSelect_Display().IsEnabled(true);
			button_AppAdd_Display().IsEnabled(true);
			button_AppRemove_Display().IsEnabled(true);
			button_Display_Apply().IsEnabled(true);
			button_Display_Reset().IsEnabled(true);
			button_Display_Import().IsEnabled(true);
			button_Display_Export().IsEnabled(true);

			//Return result
			AVDebugWriteLine(L"Display settings applied to interface (ADL)");
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine(L"Failed applying display settings to interface (ADL)");
			return false;
		}
	}
}