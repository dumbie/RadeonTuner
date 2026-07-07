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
			if (displaySettings.HdrEnabled.Support.has_value() && displaySettings.HdrEnabled.Support.value())
			{
				//Set setting
				if (displaySettings.HdrEnabled.Current.has_value())
				{
					toggleswitch_HdrEnabled().IsOn(displaySettings.HdrEnabled.Current.value());
				}
				else if (displaySettings.HdrEnabled.Default.has_value())
				{
					toggleswitch_HdrEnabled().IsOn(displaySettings.HdrEnabled.Default.value());
				}

				//Enable or disable interface
				toggleswitch_HdrEnabled().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_HdrEnabled().IsEnabled(false);
			}

			//HDR Media Profile
			if (displaySettings.HdrMediaProfile.Support.has_value() && displaySettings.HdrMediaProfile.Support.value())
			{
				//Set setting
				if (displaySettings.HdrMediaProfile.Current.has_value())
				{
					combobox_Display_HdrMediaProfile().SelectedIndex(displaySettings.HdrMediaProfile.Current.value());
				}
				else if (displaySettings.HdrMediaProfile.Default.has_value())
				{
					combobox_Display_HdrMediaProfile().SelectedIndex(displaySettings.HdrMediaProfile.Default.value());
				}

				//Enable or disable interface
				combobox_Display_HdrMediaProfile().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				combobox_Display_HdrMediaProfile().IsEnabled(false);
			}

			//FreeSync
			if (displaySettings.FreeSyncEnabled.Support.has_value() && displaySettings.FreeSyncEnabled.Support.value())
			{
				//Set setting
				if (displaySettings.FreeSyncEnabled.Current.has_value())
				{
					toggleswitch_FreeSync().IsOn(displaySettings.FreeSyncEnabled.Current.value());
				}
				else if (displaySettings.FreeSyncEnabled.Default.has_value())
				{
					toggleswitch_FreeSync().IsOn(displaySettings.FreeSyncEnabled.Default.value());
				}

				//Enable or disable interface
				toggleswitch_FreeSync().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_FreeSync().IsEnabled(false);
			}

			//Virtual Super Resolution
			if (displaySettings.VsrEnabled.Support.has_value() && displaySettings.VsrEnabled.Support.value())
			{
				//Set setting
				if (displaySettings.VsrEnabled.Current.has_value())
				{
					toggleswitch_VSR().IsOn(displaySettings.VsrEnabled.Current.value());
				}
				else if (displaySettings.VsrEnabled.Default.has_value())
				{
					toggleswitch_VSR().IsOn(displaySettings.VsrEnabled.Default.value());
				}

				//Enable or disable interface
				toggleswitch_VSR().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_VSR().IsEnabled(false);
			}

			//Gpu Scaling
			if (displaySettings.GpuScalingEnabled.Support.has_value() && displaySettings.GpuScalingEnabled.Support.value())
			{
				//Set setting
				if (displaySettings.GpuScalingEnabled.Current.has_value())
				{
					toggleswitch_GpuScaling().IsOn(displaySettings.GpuScalingEnabled.Current.value());
				}
				else if (displaySettings.GpuScalingEnabled.Default.has_value())
				{
					toggleswitch_GpuScaling().IsOn(displaySettings.GpuScalingEnabled.Default.value());
				}

				//Enable or disable interface
				toggleswitch_GpuScaling().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_GpuScaling().IsEnabled(false);
			}

			//Integer Scaling
			if (displaySettings.IntegerScalingEnabled.Support.has_value() && displaySettings.IntegerScalingEnabled.Support.value())
			{
				//Set setting
				if (displaySettings.IntegerScalingEnabled.Current.has_value())
				{
					toggleswitch_IntegerScaling().IsOn(displaySettings.IntegerScalingEnabled.Current.value());
				}
				else if (displaySettings.IntegerScalingEnabled.Default.has_value())
				{
					toggleswitch_IntegerScaling().IsOn(displaySettings.IntegerScalingEnabled.Default.value());
				}

				//Enable or disable interface
				toggleswitch_IntegerScaling().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_IntegerScaling().IsEnabled(false);
			}

			//Scaling Mode
			if (displaySettings.ScalingMode.Support.has_value() && displaySettings.ScalingMode.Support.value())
			{
				//Set setting
				if (displaySettings.ScalingMode.Current.has_value())
				{
					combobox_Display_ScalingMode().SelectedIndex(displaySettings.ScalingMode.Current.value());
				}
				else if (displaySettings.ScalingMode.Default.has_value())
				{
					combobox_Display_ScalingMode().SelectedIndex(displaySettings.ScalingMode.Default.value());
				}

				//Enable or disable interface
				combobox_Display_ScalingMode().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				combobox_Display_ScalingMode().IsEnabled(false);
			}

			//Color Depth
			if (displaySettings.ColorDepth.Support.has_value() && displaySettings.ColorDepth.Support.value())
			{
				//Set setting
				if (displaySettings.ColorDepth.Current.has_value())
				{
					combobox_Display_ColorDepth().SelectedIndex(displaySettings.ColorDepth.Current.value());
				}
				else if (displaySettings.ColorDepth.Default.has_value())
				{
					combobox_Display_ColorDepth().SelectedIndex(displaySettings.ColorDepth.Default.value());
				}

				//Enable or disable interface
				combobox_Display_ColorDepth().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				combobox_Display_ColorDepth().IsEnabled(false);
			}

			//Pixel Format
			if (displaySettings.PixelFormat.Support.has_value() && displaySettings.PixelFormat.Support.value())
			{
				//Set setting
				if (displaySettings.PixelFormat.Current.has_value())
				{
					combobox_Display_PixelFormat().SelectedIndex(displaySettings.PixelFormat.Current.value());
				}
				else if (displaySettings.PixelFormat.Default.has_value())
				{
					combobox_Display_PixelFormat().SelectedIndex(displaySettings.PixelFormat.Default.value());
				}

				//Enable or disable interface
				combobox_Display_PixelFormat().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				combobox_Display_PixelFormat().IsEnabled(false);
			}

			//Color Enhancement
			if (displaySettings.ColorEnhancement.Support.has_value() && displaySettings.ColorEnhancement.Support.value())
			{
				//Set setting
				if (displaySettings.ColorEnhancement.Current.has_value())
				{
					combobox_Display_DisplayColorEnhancement().SelectedIndex(displaySettings.ColorEnhancement.Current.value());
				}
				else if (displaySettings.ColorEnhancement.Default.has_value())
				{
					combobox_Display_DisplayColorEnhancement().SelectedIndex(displaySettings.ColorEnhancement.Default.value());
				}

				//Enable or disable interface
				combobox_Display_DisplayColorEnhancement().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				combobox_Display_DisplayColorEnhancement().IsEnabled(false);
			}

			//Color Temperature Control
			if (displaySettings.ColorTemperatureControl.Support.has_value() && displaySettings.ColorTemperatureControl.Support.value())
			{
				if (displaySettings.ColorTemperatureControl.Current.has_value())
				{
					toggleswitch_Display_ColorTemperature_Control().IsOn(displaySettings.ColorTemperatureControl.Current.value());
					slider_Display_ColorTemperature_Kelvin().IsEnabled(displaySettings.ColorTemperatureControl.Current.value());
				}
				else if (displaySettings.ColorTemperatureControl.Default.has_value())
				{
					toggleswitch_Display_ColorTemperature_Control().IsOn(displaySettings.ColorTemperatureControl.Default.value());
					slider_Display_ColorTemperature_Kelvin().IsEnabled(displaySettings.ColorTemperatureControl.Default.value());
				}

				//Enable or disable interface
				toggleswitch_Display_ColorTemperature_Control().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_Display_ColorTemperature_Control().IsEnabled(false);
				slider_Display_ColorTemperature_Kelvin().IsEnabled(false);
			}

			//Color Temperature Kelvin
			if (displaySettings.ColorTemperatureKelvin.Support.has_value() && displaySettings.ColorTemperatureKelvin.Support.value())
			{
				//Set setting
				if (displaySettings.ColorTemperatureKelvin.Current.has_value())
				{
					slider_Display_ColorTemperature_Kelvin().Value(displaySettings.ColorTemperatureKelvin.Current.value());
				}
				else if (displaySettings.ColorTemperatureKelvin.Default.has_value())
				{
					slider_Display_ColorTemperature_Kelvin().Value(displaySettings.ColorTemperatureKelvin.Default.value());
				}

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
				//Enable or disable interface
				slider_Display_ColorTemperature_Kelvin().IsEnabled(false);
			}

			//Color Brightness
			if (displaySettings.Brightness.Support.has_value() && displaySettings.Brightness.Support.value())
			{
				//Set setting
				if (displaySettings.Brightness.Current.has_value())
				{
					slider_Display_Brightness().Value(displaySettings.Brightness.Current.value());
				}
				else if (displaySettings.Brightness.Default.has_value())
				{
					slider_Display_Brightness().Value(displaySettings.Brightness.Default.value());
				}

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
				//Enable or disable interface
				slider_Display_Brightness().IsEnabled(false);
			}

			//Color Contrast
			if (displaySettings.Contrast.Support.has_value() && displaySettings.Contrast.Support.value())
			{
				//Set setting
				if (displaySettings.Contrast.Current.has_value())
				{
					slider_Display_Contrast().Value(displaySettings.Contrast.Current.value());
				}
				else if (displaySettings.Contrast.Default.has_value())
				{
					slider_Display_Contrast().Value(displaySettings.Contrast.Default.value());
				}

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
				//Enable or disable interface
				slider_Display_Contrast().IsEnabled(false);
			}

			//Color Saturation
			if (displaySettings.Saturation.Support.has_value() && displaySettings.Saturation.Support.value())
			{
				//Set setting
				if (displaySettings.Saturation.Current.has_value())
				{
					slider_Display_Saturation().Value(displaySettings.Saturation.Current.value());
				}
				else if (displaySettings.Saturation.Default.has_value())
				{
					slider_Display_Saturation().Value(displaySettings.Saturation.Default.value());
				}

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
				//Enable or disable interface
				slider_Display_Saturation().IsEnabled(false);
			}

			//Color Hue
			if (displaySettings.Hue.Support.has_value() && displaySettings.Hue.Support.value())
			{
				//Set setting
				if (displaySettings.Hue.Current.has_value())
				{
					slider_Display_Hue().Value(displaySettings.Hue.Current.value());
				}
				else if (displaySettings.Hue.Default.has_value())
				{
					slider_Display_Hue().Value(displaySettings.Hue.Default.value());
				}

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
				//Enable or disable interface
				slider_Display_Hue().IsEnabled(false);
			}

			//Color Deficiency Correction Control
			if (displaySettings.CVDCControl.Support.has_value() && displaySettings.CVDCControl.Support.value())
			{
				if (displaySettings.CVDCControl.Current.has_value())
				{
					toggleswitch_Display_CVDC_Control().IsOn(displaySettings.CVDCControl.Current.value());

					//Enable or disable interface
					slider_Display_Protanopia().IsEnabled(displaySettings.CVDCControl.Current.value());
					slider_Display_Deuteranopia().IsEnabled(displaySettings.CVDCControl.Current.value());
					slider_Display_Tritanopia().IsEnabled(displaySettings.CVDCControl.Current.value());
				}
				else if (displaySettings.CVDCControl.Default.has_value())
				{
					toggleswitch_Display_CVDC_Control().IsOn(displaySettings.CVDCControl.Default.value());

					//Enable or disable interface
					slider_Display_Protanopia().IsEnabled(displaySettings.CVDCControl.Default.value());
					slider_Display_Deuteranopia().IsEnabled(displaySettings.CVDCControl.Default.value());
					slider_Display_Tritanopia().IsEnabled(displaySettings.CVDCControl.Default.value());
				}

				//Enable or disable interface
				toggleswitch_Display_CVDC_Control().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_Display_CVDC_Control().IsEnabled(false);
				slider_Display_Protanopia().IsEnabled(false);
				slider_Display_Deuteranopia().IsEnabled(false);
				slider_Display_Tritanopia().IsEnabled(false);
			}

			//Color Deficiency Correction Protanopia
			if (displaySettings.CVDCProtanopia.Support.has_value() && displaySettings.CVDCProtanopia.Support.value())
			{
				//Set setting
				if (displaySettings.CVDCProtanopia.Current.has_value())
				{
					slider_Display_Protanopia().Value(displaySettings.CVDCProtanopia.Current.value());
				}
				else if (displaySettings.CVDCProtanopia.Default.has_value())
				{
					slider_Display_Protanopia().Value(displaySettings.CVDCProtanopia.Default.value());
				}

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
				//Enable or disable interface
				slider_Display_Protanopia().IsEnabled(false);
			}

			//Color Deficiency Correction Deuteranopia
			if (displaySettings.CVDCDeuteranopia.Support.has_value() && displaySettings.CVDCDeuteranopia.Support.value())
			{
				//Set setting
				if (displaySettings.CVDCDeuteranopia.Current.has_value())
				{
					slider_Display_Deuteranopia().Value(displaySettings.CVDCDeuteranopia.Current.value());
				}
				else if (displaySettings.CVDCDeuteranopia.Default.has_value())
				{
					slider_Display_Deuteranopia().Value(displaySettings.CVDCDeuteranopia.Default.value());
				}

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
				//Enable or disable interface
				slider_Display_Deuteranopia().IsEnabled(false);
			}

			//Color Deficiency Correction Tritanopia
			if (displaySettings.CVDCTritanopia.Support.has_value() && displaySettings.CVDCTritanopia.Support.value())
			{
				//Set setting
				if (displaySettings.CVDCTritanopia.Current.has_value())
				{
					slider_Display_Tritanopia().Value(displaySettings.CVDCTritanopia.Current.value());
				}
				else if (displaySettings.CVDCTritanopia.Default.has_value())
				{
					slider_Display_Tritanopia().Value(displaySettings.CVDCTritanopia.Default.value());
				}

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
				//Enable or disable interface
				slider_Display_Tritanopia().IsEnabled(false);
			}

			//Vari-Bright Enabled
			if (displaySettings.VariBrightEnabled.Support.has_value() && displaySettings.VariBrightEnabled.Support.value())
			{
				//Set setting
				if (displaySettings.VariBrightEnabled.Current.has_value())
				{
					toggleswitch_VariBright().IsOn(displaySettings.VariBrightEnabled.Current.value());
					combobox_Display_VariBright_Level().IsEnabled(displaySettings.VariBrightEnabled.Current.value());
				}
				else if (displaySettings.VariBrightEnabled.Default.has_value())
				{
					toggleswitch_VariBright().IsOn(displaySettings.VariBrightEnabled.Default.value());
					combobox_Display_VariBright_Level().IsEnabled(displaySettings.VariBrightEnabled.Default.value());
				}

				//Enable or disable interface
				toggleswitch_VariBright().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_VariBright().IsEnabled(false);
				combobox_Display_VariBright_Level().IsEnabled(false);
			}

			//Vari-Bright Level
			if (displaySettings.VariBrightLevel.Support.has_value() && displaySettings.VariBrightLevel.Support.value())
			{
				//Set setting
				if (displaySettings.VariBrightLevel.Current.has_value())
				{
					combobox_Display_VariBright_Level().SelectedIndex(displaySettings.VariBrightLevel.Current.value());
				}
				else if (displaySettings.VariBrightLevel.Default.has_value())
				{
					combobox_Display_VariBright_Level().SelectedIndex(displaySettings.VariBrightLevel.Default.value());
				}
			}
			else
			{
				//Enable or disable interface
				combobox_Display_VariBright_Level().IsEnabled(false);
			}

			//HDCP Support
			if (displaySettings.HDCPEnabled.Support.has_value() && displaySettings.HDCPEnabled.Support.value())
			{
				//Set setting
				if (displaySettings.HDCPEnabled.Current.has_value())
				{
					toggleswitch_HDCPSupport().IsOn(displaySettings.HDCPEnabled.Current.value());
				}
				else if (displaySettings.HDCPEnabled.Default.has_value())
				{
					toggleswitch_HDCPSupport().IsOn(displaySettings.HDCPEnabled.Default.value());
				}

				//Enable or disable interface
				toggleswitch_HDCPSupport().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_HDCPSupport().IsEnabled(false);
			}

			//Return result
			AVDebugWriteLine(L"Display settings applied to interface.");
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine(L"Failed applying display settings to interface.");
			return false;
		}
	}
}