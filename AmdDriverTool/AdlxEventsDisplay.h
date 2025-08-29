#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::toggleswitch_FreeSync_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get settings
			IADLXDisplayFreeSyncPtr ppFreeSync;
			adlx_Res0 = ppDispServices->GetFreeSync(ppDisplayInfo, &ppFreeSync);

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				adlx_Res0 = ppFreeSync->SetEnabled(true);
				if (ADLX_FAILED(adlx_Res0))
				{
					textblock_Status().Text(L"Failed enabling AMD FreeSync");
					AVDebugWriteLine(L"Failed enabling AMD FreeSync");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					textblock_Status().Text(L"AMD FreeSync enabled");
					AVDebugWriteLine(L"AMD FreeSync enabled");
				}
			}
			else
			{
				//Check setting mode
				toggleswitch_FreeSyncColorAccuracy().IsEnabled(false);

				adlx_Res0 = ppFreeSync->SetEnabled(false);
				textblock_Status().Text(L"AMD FreeSync disabled");
				AVDebugWriteLine(L"AMD FreeSync disabled");
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_FreeSyncColorAccuracy_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get settings
			IADLXDisplayFreeSyncColorAccuracyPtr ppFSCA;
			adlx_Res0 = ppDispServices->GetFreeSyncColorAccuracy(ppDisplayInfo, &ppFSCA);

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				adlx_Res0 = ppFSCA->SetEnabled(true);
				if (ADLX_FAILED(adlx_Res0))
				{
					textblock_Status().Text(L"Failed enabling AMD FreeSync Color Accuracy");
					AVDebugWriteLine(L"Failed enabling AMD FreeSync Color Accuracy");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					textblock_Status().Text(L"AMD FreeSync Color Accuracy enabled");
					AVDebugWriteLine(L"AMD FreeSync Color Accuracy enabled");
				}
			}
			else
			{
				adlx_Res0 = ppFSCA->SetEnabled(false);
				textblock_Status().Text(L"AMD FreeSync Color Accuracy disabled");
				AVDebugWriteLine(L"AMD FreeSync Color Accuracy disabled");
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_VSR_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get settings
			IADLXDisplayVSRPtr ppVSR;
			adlx_Res0 = ppDispServices->GetVirtualSuperResolution(ppDisplayInfo, &ppVSR);

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				adlx_Res0 = ppVSR->SetEnabled(true);
				if (ADLX_FAILED(adlx_Res0))
				{
					textblock_Status().Text(L"Failed enabling AMD VSR");
					AVDebugWriteLine(L"Failed enabling AMD VSR");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					textblock_Status().Text(L"AMD VSR enabled");
					AVDebugWriteLine(L"AMD VSR enabled");
				}
			}
			else
			{
				adlx_Res0 = ppVSR->SetEnabled(false);
				textblock_Status().Text(L"AMD VSR disabled");
				AVDebugWriteLine(L"AMD VSR disabled");
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_Display_ColorDepth_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get color depth value
			auto newValue = sender.as<ComboBox>().SelectedIndex() + 1;

			//Get display color depth
			IADLXDisplayColorDepthPtr ppColorDepth;
			adlx_Res0 = ppDispServices->GetColorDepth(ppDisplayInfo, &ppColorDepth);
			adlx_Res0 = ppColorDepth->SetValue((ADLX_COLOR_DEPTH)newValue);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				textblock_Status().Text(L"Failed setting color depth");
				AVDebugWriteLine(L"Failed setting color depth");
			}
			else
			{
				//Set result
				textblock_Status().Text(L"Color depth set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Color depth set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_Display_PixelFormat_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get pixel format value
			auto newValue = sender.as<ComboBox>().SelectedIndex() + 1;

			//Get display pixel format
			IADLXDisplayPixelFormatPtr ppPixelFormat;
			adlx_Res0 = ppDispServices->GetPixelFormat(ppDisplayInfo, &ppPixelFormat);
			adlx_Res0 = ppPixelFormat->SetValue((ADLX_PIXEL_FORMAT)newValue);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				textblock_Status().Text(L"Failed setting pixel format");
				AVDebugWriteLine(L"Failed setting pixel format");
			}
			else
			{
				//Set result
				textblock_Status().Text(L"Pixel format set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Pixel format set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::slider_Display_ColorTemperature_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get value
			auto newValue = sender.as<Slider>().Value();

			//Get display custom color profile
			IADLXDisplayCustomColorPtr ppCustomColor;
			adlx_Res0 = ppDispServices->GetCustomColor(ppDisplayInfo, &ppCustomColor);

			//Enable color temperature control
			//Fix find way to enable color temperature control when disabled in AMD Adrenalin

			//Set display color temperature
			adlx_Res0 = ppCustomColor->SetTemperature(newValue);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				textbox_Display_ColorTemperature().Foreground(SolidColorBrush(Windows::UI::Colors::Red()));
				textblock_Status().Text(L"Failed setting color temperature");
				AVDebugWriteLine(L"Failed setting color temperature");
			}
			else
			{
				//Set result
				textbox_Display_ColorTemperature().Foreground(SolidColorBrush(Windows::UI::Colors::Green()));
				textblock_Status().Text(L"Color temperature set to " + number_to_wstring((int)newValue));
				AVDebugWriteLine(L"Color temperature set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::slider_Display_Brightness_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get value
			auto newValue = sender.as<Slider>().Value();

			//Get display custom color profile
			IADLXDisplayCustomColorPtr ppCustomColor;
			adlx_Res0 = ppDispServices->GetCustomColor(ppDisplayInfo, &ppCustomColor);

			//Set display brightness
			adlx_Res0 = ppCustomColor->SetBrightness(newValue);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				textbox_Display_Brightness().Foreground(SolidColorBrush(Windows::UI::Colors::Red()));
				textblock_Status().Text(L"Failed setting brightness");
				AVDebugWriteLine(L"Failed setting brightness");
			}
			else
			{
				//Set result
				textbox_Display_Brightness().Foreground(SolidColorBrush(Windows::UI::Colors::Green()));
				textblock_Status().Text(L"Brightness set to " + number_to_wstring((int)newValue));
				AVDebugWriteLine(L"Brightness set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::slider_Display_Contrast_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get value
			auto newValue = sender.as<Slider>().Value();

			//Get display custom color profile
			IADLXDisplayCustomColorPtr ppCustomColor;
			adlx_Res0 = ppDispServices->GetCustomColor(ppDisplayInfo, &ppCustomColor);

			//Set display contrast
			adlx_Res0 = ppCustomColor->SetContrast(newValue);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				textbox_Display_Contrast().Foreground(SolidColorBrush(Windows::UI::Colors::Red()));
				textblock_Status().Text(L"Failed setting contrast");
				AVDebugWriteLine(L"Failed setting contrast");
			}
			else
			{
				//Set result
				textbox_Display_Contrast().Foreground(SolidColorBrush(Windows::UI::Colors::Green()));
				textblock_Status().Text(L"Contrast set to " + number_to_wstring((int)newValue));
				AVDebugWriteLine(L"Contrast set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::slider_Display_Saturation_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get saturation value
			auto newValue = sender.as<Slider>().Value();

			//Get display custom color profile
			IADLXDisplayCustomColorPtr ppCustomColor;
			adlx_Res0 = ppDispServices->GetCustomColor(ppDisplayInfo, &ppCustomColor);

			//Set display saturation
			adlx_Res0 = ppCustomColor->SetSaturation(newValue);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				textbox_Display_Saturation().Foreground(SolidColorBrush(Windows::UI::Colors::Red()));
				textblock_Status().Text(L"Failed setting saturation");
				AVDebugWriteLine(L"Failed setting saturation");
			}
			else
			{
				//Set result
				textbox_Display_Saturation().Foreground(SolidColorBrush(Windows::UI::Colors::Green()));
				textblock_Status().Text(L"Saturation set to " + number_to_wstring((int)newValue));
				AVDebugWriteLine(L"Saturation set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::slider_Display_Hue_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get saturation value
			auto newValue = sender.as<Slider>().Value();

			//Get display custom color profile
			IADLXDisplayCustomColorPtr ppCustomColor;
			adlx_Res0 = ppDispServices->GetCustomColor(ppDisplayInfo, &ppCustomColor);

			//Set display hue
			adlx_Res0 = ppCustomColor->SetHue(newValue);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				textbox_Display_Hue().Foreground(SolidColorBrush(Windows::UI::Colors::Red()));
				textblock_Status().Text(L"Failed setting hue");
				AVDebugWriteLine(L"Failed setting hue");
			}
			else
			{
				//Set result
				textbox_Display_Hue().Foreground(SolidColorBrush(Windows::UI::Colors::Green()));
				textblock_Status().Text(L"Hue set to " + number_to_wstring((int)newValue));
				AVDebugWriteLine(L"Hue set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_GPUScaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get settings
			IADLXDisplayGPUScalingPtr ppGPUScaling;
			adlx_Res0 = ppDispServices->GetGPUScaling(ppDisplayInfo, &ppGPUScaling);

			IADLXDisplayIntegerScalingPtr ppIntegerScaling;
			adlx_Res0 = ppDispServices->GetIntegerScaling(ppDisplayInfo, &ppIntegerScaling);

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				adlx_Res0 = ppGPUScaling->SetEnabled(true);
				if (ADLX_FAILED(adlx_Res0))
				{
					textblock_Status().Text(L"Failed enabling GPU Scaling");
					AVDebugWriteLine(L"Failed enabling GPU Scaling");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					adlx_Res0 = ppIntegerScaling->IsSupported(&adlx_Bool);
					if (adlx_Bool)
					{
						toggleswitch_IntegerScaling().IsEnabled(true);
					}
					textblock_Status().Text(L"GPU Scaling enabled");
					AVDebugWriteLine(L"GPU Scaling enabled");
				}
			}
			else
			{
				//Check setting mode
				disable_saving = true;
				toggleswitch_IntegerScaling().IsOn(false);
				disable_saving = false;
				toggleswitch_IntegerScaling().IsEnabled(false);

				adlx_Res0 = ppGPUScaling->SetEnabled(false);
				textblock_Status().Text(L"GPU Scaling disabled");
				AVDebugWriteLine(L"GPU Scaling disabled");
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_IntegerScaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get settings
			IADLXDisplayIntegerScalingPtr ppIntegerScaling;
			adlx_Res0 = ppDispServices->GetIntegerScaling(ppDisplayInfo, &ppIntegerScaling);

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				adlx_Res0 = ppIntegerScaling->SetEnabled(true);
				if (ADLX_FAILED(adlx_Res0))
				{
					textblock_Status().Text(L"Failed enabling Integer Scaling");
					AVDebugWriteLine(L"Failed enabling Integer Scaling");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					textblock_Status().Text(L"Integer Scaling enabled");
					AVDebugWriteLine(L"Integer Scaling enabled");
				}
			}
			else
			{
				adlx_Res0 = ppIntegerScaling->SetEnabled(false);
				textblock_Status().Text(L"Integer Scaling disabled");
				AVDebugWriteLine(L"Integer Scaling disabled");
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_Display_ScalingMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get selection
			auto newValue = sender.as<ComboBox>().SelectedIndex();

			//Get settings
			IADLXDisplayScalingModePtr ppScalingMode;
			adlx_Res0 = ppDispServices->GetScalingMode(ppDisplayInfo, &ppScalingMode);

			adlx_Res0 = ppScalingMode->SetMode((ADLX_SCALE_MODE)newValue);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				textblock_Status().Text(L"Failed setting scaling mode");
				AVDebugWriteLine(L"Failed setting scaling mode");
			}
			else
			{
				//Set result
				textblock_Status().Text(L"Scaling mode set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Scaling mode set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_HDCPSupport_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get settings
			IADLXDisplayHDCPPtr ppHDCP;
			adlx_Res0 = ppDispServices->GetHDCP(ppDisplayInfo, &ppHDCP);

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				adlx_Res0 = ppHDCP->SetEnabled(true);
				if (ADLX_FAILED(adlx_Res0))
				{
					textblock_Status().Text(L"Failed enabling HDCP Support");
					AVDebugWriteLine(L"Failed enabling HDCP Support");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					textblock_Status().Text(L"HDCP Support enabled");
					AVDebugWriteLine(L"HDCP Support enabled");
				}
			}
			else
			{
				adlx_Res0 = ppHDCP->SetEnabled(false);
				textblock_Status().Text(L"HDCP Support disabled");
				AVDebugWriteLine(L"HDCP Support disabled");
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_VariBright_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get settings
			IADLXDisplayVariBrightPtr ppVariBright;
			adlx_Res0 = ppDispServices->GetVariBright(ppDisplayInfo, &ppVariBright);

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				adlx_Res0 = ppVariBright->SetEnabled(true);
				if (ADLX_FAILED(adlx_Res0))
				{
					textblock_Status().Text(L"Failed enabling Vari-Bright");
					AVDebugWriteLine(L"Failed enabling Vari-Bright");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					//Check setting mode
					combobox_Display_VariBright_Level().IsEnabled(true);
					//Fix reload settings to get correct mode

					textblock_Status().Text(L"Vari-Bright enabled");
					AVDebugWriteLine(L"Vari-Bright enabled");
				}
			}
			else
			{
				//Check setting mode
				combobox_Display_VariBright_Level().IsEnabled(false);

				adlx_Res0 = ppVariBright->SetEnabled(false);
				textblock_Status().Text(L"Vari-Bright disabled");
				AVDebugWriteLine(L"Vari-Bright disabled");
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_Display_VariBright_Level_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get selection
			auto newValue = sender.as<ComboBox>().SelectedIndex();

			//Get settings
			IADLXDisplayVariBrightPtr ppVariBright;
			adlx_Res0 = ppDispServices->GetVariBright(ppDisplayInfo, &ppVariBright);

			//Set Vari-Bright Level
			if (newValue == 0)
			{
				adlx_Res0 = ppVariBright->SetMaximizeBrightness();
				textblock_Status().Text(L"Vari-Bright set to maximize brightness");
				AVDebugWriteLine(L"Vari-Bright set to maximize brightness");
			}
			else if (newValue == 1)
			{
				adlx_Res0 = ppVariBright->SetOptimizeBrightness();
				textblock_Status().Text(L"Vari-Bright set to optimize brightness");
				AVDebugWriteLine(L"Vari-Bright set to optimize brightness");
			}
			else if (newValue == 2)
			{
				adlx_Res0 = ppVariBright->SetBalanced();
				textblock_Status().Text(L"Vari-Bright set to balanced");
				AVDebugWriteLine(L"Vari-Bright set to balanced");
			}
			else if (newValue == 3)
			{
				adlx_Res0 = ppVariBright->SetOptimizeBattery();
				textblock_Status().Text(L"Vari-Bright set to optimize battery");
				AVDebugWriteLine(L"Vari-Bright set to optimize battery");
			}
			else if (newValue == 4)
			{
				adlx_Res0 = ppVariBright->SetMaximizeBattery();
				textblock_Status().Text(L"Vari-Bright set to maximize battery");
				AVDebugWriteLine(L"Vari-Bright set to maximize battery");
			}
		}
		catch (...) {}
	}
}