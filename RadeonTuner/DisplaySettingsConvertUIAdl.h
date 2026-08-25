#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::DisplaySettings_Convert_ToUI_Adl(DisplaySettings displaySettings)
	{
		try
		{
			//HDR Enabled
			if (displaySettings.HdrEnabled.Support)
			{
				//Get setting
				int valueInt = 0;
				if (displaySettings.HdrEnabled.Current.has_value())
				{
					valueInt = displaySettings.HdrEnabled.Current.value();
				}
				else if (displaySettings.HdrEnabled.Default.has_value())
				{
					valueInt = displaySettings.HdrEnabled.Default.value();
				}

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
			if (displaySettings.FreeSyncMode.Support)
			{
				//Get setting
				int valueInt = 0;
				if (displaySettings.FreeSyncMode.Current.has_value())
				{
					valueInt = displaySettings.FreeSyncMode.Current.value();
				}
				else if (displaySettings.FreeSyncMode.Default.has_value())
				{
					valueInt = displaySettings.FreeSyncMode.Default.value();
				}

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
			if (displaySettings.VsrEnabled.Support)
			{
				//Get setting
				int valueInt = 0;
				if (displaySettings.VsrEnabled.Current.has_value())
				{
					valueInt = displaySettings.VsrEnabled.Current.value();
				}
				else if (displaySettings.VsrEnabled.Default.has_value())
				{
					valueInt = displaySettings.VsrEnabled.Default.value();
				}

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
			if (displaySettings.GpuScalingEnabled.Support)
			{
				//Get setting
				int valueInt = 0;
				if (displaySettings.GpuScalingEnabled.Current.has_value())
				{
					valueInt = displaySettings.GpuScalingEnabled.Current.value();
				}
				else if (displaySettings.GpuScalingEnabled.Default.has_value())
				{
					valueInt = displaySettings.GpuScalingEnabled.Default.value();
				}

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
			if (displaySettings.IntegerScalingEnabled.Support)
			{
				//Get setting
				int valueInt = 0;
				if (displaySettings.IntegerScalingEnabled.Current.has_value())
				{
					valueInt = displaySettings.IntegerScalingEnabled.Current.value();
				}
				else if (displaySettings.IntegerScalingEnabled.Default.has_value())
				{
					valueInt = displaySettings.IntegerScalingEnabled.Default.value();
				}

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
			if (displaySettings.ScalingMode.Support)
			{
				//Get setting
				int valueInt = 0;
				if (displaySettings.ScalingMode.Current.has_value())
				{
					valueInt = displaySettings.ScalingMode.Current.value();
				}
				else if (displaySettings.ScalingMode.Default.has_value())
				{
					valueInt = displaySettings.ScalingMode.Default.value();
				}

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
			if (displaySettings.ColorDepth.Support)
			{
				//Get setting
				int valueInt = 0;
				if (displaySettings.ColorDepth.Current.has_value())
				{
					valueInt = displaySettings.ColorDepth.Current.value();
				}
				else if (displaySettings.ColorDepth.Default.has_value())
				{
					valueInt = displaySettings.ColorDepth.Default.value();
				}

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
			if (displaySettings.PixelFormat.Support)
			{
				//Get setting
				int valueInt = 0;
				if (displaySettings.PixelFormat.Current.has_value())
				{
					valueInt = displaySettings.PixelFormat.Current.value();
				}
				else if (displaySettings.PixelFormat.Default.has_value())
				{
					valueInt = displaySettings.PixelFormat.Default.value();
				}

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
			if (displaySettings.ColorEnhancement.Support)
			{
				//Get setting
				int valueInt = 0;
				if (displaySettings.ColorEnhancement.Current.has_value())
				{
					valueInt = displaySettings.ColorEnhancement.Current.value();
				}
				else if (displaySettings.ColorEnhancement.Default.has_value())
				{
					valueInt = displaySettings.ColorEnhancement.Default.value();
				}

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
			if (displaySettings.ColorTemperatureControl.Support)
			{
				//Get setting
				int valueInt = 0;
				if (displaySettings.ColorTemperatureControl.Current.has_value())
				{
					valueInt = displaySettings.ColorTemperatureControl.Current.value();
				}
				else if (displaySettings.ColorTemperatureControl.Default.has_value())
				{
					valueInt = displaySettings.ColorTemperatureControl.Default.value();
				}

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
			if (displaySettings.ColorTemperatureKelvin.Support)
			{
				//Get setting
				int valueInt = 0;
				if (displaySettings.ColorTemperatureKelvin.Current.has_value())
				{
					valueInt = displaySettings.ColorTemperatureKelvin.Current.value();
				}
				else if (displaySettings.ColorTemperatureKelvin.Default.has_value())
				{
					valueInt = displaySettings.ColorTemperatureKelvin.Default.value();
				}

				//Set setting value
				slider_Display_ColorTemperature_Kelvin().Value(valueInt);

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt) + L"K";
				textblock_Display_ColorTemperature_Kelvin_Value().Text(valueHint);

				//Set interface
				if (displaySettings.ColorTemperatureKelvin.Minimum.has_value())
				{
					slider_Display_ColorTemperature_Kelvin().Minimum(displaySettings.ColorTemperatureKelvin.Minimum.value());
					slider_Display_ColorTemperature_Kelvin().Maximum(displaySettings.ColorTemperatureKelvin.Maximum.value());
					slider_Display_ColorTemperature_Kelvin().StepFrequency(displaySettings.ColorTemperatureKelvin.Step.value());
					slider_Display_ColorTemperature_Kelvin().SmallChange(displaySettings.ColorTemperatureKelvin.Step.value());
				}
			}
			else
			{
				//Set hint value
				textblock_Display_ColorTemperature_Kelvin_Value().Text(L"");

				//Enable or disable interface
				slider_Display_ColorTemperature_Kelvin().IsEnabled(false);
			}

			//Color Brightness
			if (displaySettings.Brightness.Support)
			{
				//Get setting
				int valueInt = 0;
				if (displaySettings.Brightness.Current.has_value())
				{
					valueInt = displaySettings.Brightness.Current.value();
				}
				else if (displaySettings.Brightness.Default.has_value())
				{
					valueInt = displaySettings.Brightness.Default.value();
				}

				//Set setting value
				slider_Display_Brightness().Value(valueInt);

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt);
				textblock_Display_Brightness_Value().Text(valueHint);

				//Set interface
				if (displaySettings.Brightness.Minimum.has_value())
				{
					slider_Display_Brightness().Minimum(displaySettings.Brightness.Minimum.value());
					slider_Display_Brightness().Maximum(displaySettings.Brightness.Maximum.value());
					slider_Display_Brightness().StepFrequency(displaySettings.Brightness.Step.value());
					slider_Display_Brightness().SmallChange(displaySettings.Brightness.Step.value());
				}

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
			if (displaySettings.Contrast.Support)
			{
				//Get setting
				int valueInt = 0;
				if (displaySettings.Contrast.Current.has_value())
				{
					valueInt = displaySettings.Contrast.Current.value();
				}
				else if (displaySettings.Contrast.Default.has_value())
				{
					valueInt = displaySettings.Contrast.Default.value();
				}

				//Set setting value
				slider_Display_Contrast().Value(valueInt);

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt);
				textblock_Display_Contrast_Value().Text(valueHint);

				//Set interface
				if (displaySettings.Contrast.Minimum.has_value())
				{
					slider_Display_Contrast().Minimum(displaySettings.Contrast.Minimum.value());
					slider_Display_Contrast().Maximum(displaySettings.Contrast.Maximum.value());
					slider_Display_Contrast().StepFrequency(displaySettings.Contrast.Step.value());
					slider_Display_Contrast().SmallChange(displaySettings.Contrast.Step.value());
				}

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
			if (displaySettings.Saturation.Support)
			{
				//Get setting
				int valueInt = 0;
				if (displaySettings.Saturation.Current.has_value())
				{
					valueInt = displaySettings.Saturation.Current.value();
				}
				else if (displaySettings.Saturation.Default.has_value())
				{
					valueInt = displaySettings.Saturation.Default.value();
				}

				//Set setting value
				slider_Display_Saturation().Value(valueInt);

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt);
				textblock_Display_Saturation_Value().Text(valueHint);

				//Set interface
				if (displaySettings.Saturation.Minimum.has_value())
				{
					slider_Display_Saturation().Minimum(displaySettings.Saturation.Minimum.value());
					slider_Display_Saturation().Maximum(displaySettings.Saturation.Maximum.value());
					slider_Display_Saturation().StepFrequency(displaySettings.Saturation.Step.value());
					slider_Display_Saturation().SmallChange(displaySettings.Saturation.Step.value());
				}

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
			if (displaySettings.Hue.Support)
			{
				//Get setting
				int valueInt = 0;
				if (displaySettings.Hue.Current.has_value())
				{
					valueInt = displaySettings.Hue.Current.value();
				}
				else if (displaySettings.Hue.Default.has_value())
				{
					valueInt = displaySettings.Hue.Default.value();
				}

				//Set setting value
				slider_Display_Hue().Value(valueInt);

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt);
				textblock_Display_Hue_Value().Text(valueHint);

				//Set interface
				if (displaySettings.Hue.Minimum.has_value())
				{
					slider_Display_Hue().Minimum(displaySettings.Hue.Minimum.value());
					slider_Display_Hue().Maximum(displaySettings.Hue.Maximum.value());
					slider_Display_Hue().StepFrequency(displaySettings.Hue.Step.value());
					slider_Display_Hue().SmallChange(displaySettings.Hue.Step.value());
				}

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

			//Color Gamma Red
			if (displaySettings.GammaRed.Support)
			{
				//Get setting
				float valueFloat = 0.0f;
				if (displaySettings.GammaRed.Current.has_value())
				{
					valueFloat = displaySettings.GammaRed.Current.value();
				}
				else if (displaySettings.GammaRed.Default.has_value())
				{
					valueFloat = displaySettings.GammaRed.Default.value();
				}

				//Set setting value
				slider_Display_GammaRed().Value(valueFloat);

				//Set hint value
				std::wstring valueHint = float_to_wstring(valueFloat, 2);
				textblock_Display_GammaRed_Value().Text(valueHint);

				//Set interface
				if (displaySettings.GammaRed.Minimum.has_value())
				{
					slider_Display_GammaRed().Minimum(displaySettings.GammaRed.Minimum.value());
					slider_Display_GammaRed().Maximum(displaySettings.GammaRed.Maximum.value());
					slider_Display_GammaRed().StepFrequency(displaySettings.GammaRed.Step.value());
					slider_Display_GammaRed().SmallChange(displaySettings.GammaRed.Step.value());
				}

				//Enable or disable interface
				slider_Display_GammaRed().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Display_GammaRed_Value().Text(L"");

				//Enable or disable interface
				slider_Display_GammaRed().IsEnabled(false);
			}

			//Color Gamma Green
			if (displaySettings.GammaGreen.Support)
			{
				//Get setting
				float valueFloat = 0.0f;
				if (displaySettings.GammaGreen.Current.has_value())
				{
					valueFloat = displaySettings.GammaGreen.Current.value();
				}
				else if (displaySettings.GammaGreen.Default.has_value())
				{
					valueFloat = displaySettings.GammaGreen.Default.value();
				}

				//Set setting value
				slider_Display_GammaGreen().Value(valueFloat);

				//Set hint value
				std::wstring valueHint = float_to_wstring(valueFloat, 2);
				textblock_Display_GammaGreen_Value().Text(valueHint);

				//Set interface
				if (displaySettings.GammaGreen.Minimum.has_value())
				{
					slider_Display_GammaGreen().Minimum(displaySettings.GammaGreen.Minimum.value());
					slider_Display_GammaGreen().Maximum(displaySettings.GammaGreen.Maximum.value());
					slider_Display_GammaGreen().StepFrequency(displaySettings.GammaGreen.Step.value());
					slider_Display_GammaGreen().SmallChange(displaySettings.GammaGreen.Step.value());
				}

				//Enable or disable interface
				slider_Display_GammaGreen().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Display_GammaGreen_Value().Text(L"");

				//Enable or disable interface
				slider_Display_GammaGreen().IsEnabled(false);
			}

			//Color Gamma Blue
			if (displaySettings.GammaBlue.Support)
			{
				//Get setting
				float valueFloat = 0.0f;
				if (displaySettings.GammaBlue.Current.has_value())
				{
					valueFloat = displaySettings.GammaBlue.Current.value();
				}
				else if (displaySettings.GammaBlue.Default.has_value())
				{
					valueFloat = displaySettings.GammaBlue.Default.value();
				}

				//Set setting value
				slider_Display_GammaBlue().Value(valueFloat);

				//Set hint value
				std::wstring valueHint = float_to_wstring(valueFloat, 2);
				textblock_Display_GammaBlue_Value().Text(valueHint);

				//Set interface
				if (displaySettings.GammaBlue.Minimum.has_value())
				{
					slider_Display_GammaBlue().Minimum(displaySettings.GammaBlue.Minimum.value());
					slider_Display_GammaBlue().Maximum(displaySettings.GammaBlue.Maximum.value());
					slider_Display_GammaBlue().StepFrequency(displaySettings.GammaBlue.Step.value());
					slider_Display_GammaBlue().SmallChange(displaySettings.GammaBlue.Step.value());
				}

				//Enable or disable interface
				slider_Display_GammaBlue().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Display_GammaBlue_Value().Text(L"");

				//Enable or disable interface
				slider_Display_GammaBlue().IsEnabled(false);
			}

			//Color Deficiency Correction Control
			if (displaySettings.CVDCControl.Support)
			{
				//Get setting
				int valueInt = 0;
				if (displaySettings.CVDCControl.Current.has_value())
				{
					valueInt = displaySettings.CVDCControl.Current.value();
				}
				else if (displaySettings.CVDCControl.Default.has_value())
				{
					valueInt = displaySettings.CVDCControl.Default.value();
				}

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
			if (displaySettings.CVDCProtanopia.Support)
			{
				//Get setting
				int valueInt = 0;
				if (displaySettings.CVDCProtanopia.Current.has_value())
				{
					valueInt = displaySettings.CVDCProtanopia.Current.value();
				}
				else if (displaySettings.CVDCProtanopia.Default.has_value())
				{
					valueInt = displaySettings.CVDCProtanopia.Default.value();
				}

				//Set setting value
				slider_Display_Protanopia().Value(valueInt);

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt);
				textblock_Display_Protanopia_Value().Text(valueHint);

				//Set interface
				if (displaySettings.CVDCProtanopia.Minimum.has_value())
				{
					slider_Display_Protanopia().Minimum(displaySettings.CVDCProtanopia.Minimum.value());
					slider_Display_Protanopia().Maximum(displaySettings.CVDCProtanopia.Maximum.value());
					slider_Display_Protanopia().StepFrequency(displaySettings.CVDCProtanopia.Step.value());
					slider_Display_Protanopia().SmallChange(displaySettings.CVDCProtanopia.Step.value());
				}
			}
			else
			{
				//Set hint value
				textblock_Display_Protanopia_Value().Text(L"");

				//Enable or disable interface
				slider_Display_Protanopia().IsEnabled(false);
			}

			//Color Deficiency Correction Deuteranopia
			if (displaySettings.CVDCDeuteranopia.Support)
			{
				//Get setting
				int valueInt = 0;
				if (displaySettings.CVDCDeuteranopia.Current.has_value())
				{
					valueInt = displaySettings.CVDCDeuteranopia.Current.value();
				}
				else if (displaySettings.CVDCDeuteranopia.Default.has_value())
				{
					valueInt = displaySettings.CVDCDeuteranopia.Default.value();
				}

				//Set setting value
				slider_Display_Deuteranopia().Value(valueInt);

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt);
				textblock_Display_Deuteranopia_Value().Text(valueHint);

				//Set interface
				if (displaySettings.CVDCDeuteranopia.Minimum.has_value())
				{
					slider_Display_Deuteranopia().Minimum(displaySettings.CVDCDeuteranopia.Minimum.value());
					slider_Display_Deuteranopia().Maximum(displaySettings.CVDCDeuteranopia.Maximum.value());
					slider_Display_Deuteranopia().StepFrequency(displaySettings.CVDCDeuteranopia.Step.value());
					slider_Display_Deuteranopia().SmallChange(displaySettings.CVDCDeuteranopia.Step.value());
				}
			}
			else
			{
				//Set hint value
				textblock_Display_Deuteranopia_Value().Text(L"");

				//Enable or disable interface
				slider_Display_Deuteranopia().IsEnabled(false);
			}

			//Color Deficiency Correction Tritanopia
			if (displaySettings.CVDCTritanopia.Support)
			{
				//Get setting
				int valueInt = 0;
				if (displaySettings.CVDCTritanopia.Current.has_value())
				{
					valueInt = displaySettings.CVDCTritanopia.Current.value();
				}
				else if (displaySettings.CVDCTritanopia.Default.has_value())
				{
					valueInt = displaySettings.CVDCTritanopia.Default.value();
				}

				//Set setting value
				slider_Display_Tritanopia().Value(valueInt);

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt);
				textblock_Display_Tritanopia_Value().Text(valueHint);

				//Set interface
				if (displaySettings.CVDCTritanopia.Minimum.has_value())
				{
					slider_Display_Tritanopia().Minimum(displaySettings.CVDCTritanopia.Minimum.value());
					slider_Display_Tritanopia().Maximum(displaySettings.CVDCTritanopia.Maximum.value());
					slider_Display_Tritanopia().StepFrequency(displaySettings.CVDCTritanopia.Step.value());
					slider_Display_Tritanopia().SmallChange(displaySettings.CVDCTritanopia.Step.value());
				}
			}
			else
			{
				//Set hint value
				textblock_Display_Tritanopia_Value().Text(L"");

				//Enable or disable interface
				slider_Display_Tritanopia().IsEnabled(false);
			}

			//Vari-Bright Enabled
			if (displaySettings.VariBrightEnabled.Support)
			{
				//Get setting
				int valueInt = 0;
				if (displaySettings.VariBrightEnabled.Current.has_value())
				{
					valueInt = displaySettings.VariBrightEnabled.Current.value();
				}
				else if (displaySettings.VariBrightEnabled.Default.has_value())
				{
					valueInt = displaySettings.VariBrightEnabled.Default.value();
				}

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
			if (displaySettings.VariBrightLevel.Support)
			{
				//Get setting
				int valueInt = 0;
				if (displaySettings.VariBrightLevel.Current.has_value())
				{
					valueInt = displaySettings.VariBrightLevel.Current.value();
				}
				else if (displaySettings.VariBrightLevel.Default.has_value())
				{
					valueInt = displaySettings.VariBrightLevel.Default.value();
				}

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
			if (displaySettings.HDCPEnabled.Support)
			{
				//Get setting
				int valueInt = 0;
				if (displaySettings.HDCPEnabled.Current.has_value())
				{
					valueInt = displaySettings.HDCPEnabled.Current.value();
				}
				else if (displaySettings.HDCPEnabled.Default.has_value())
				{
					valueInt = displaySettings.HDCPEnabled.Default.value();
				}

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