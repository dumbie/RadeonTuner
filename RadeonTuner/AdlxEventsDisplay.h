#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::button_Display_Import_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Import settings from file
			AdlxValuesImportDisplay();
		}
		catch (...) {}
	}

	void MainPage::button_Display_Export_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Export current settings to file
			AdlxValuesExportDisplay();
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_FreeSync_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get settings
			IADLXDisplayFreeSyncPtr ppFreeSync;
			adlx_Res0 = ppDispServices->GetFreeSync(ppDisplayInfo, &ppFreeSync);

			IADLXDisplayFreeSyncColorAccuracyPtr ppFSCA;
			adlx_Res0 = ppDispServices->GetFreeSyncColorAccuracy(ppDisplayInfo, &ppFSCA);

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				adlx_Res0 = ppFreeSync->SetEnabled(true);
				if (ADLX_FAILED(adlx_Res0))
				{
					ShowNotification(L"Failed enabling AMD FreeSync");
					AVDebugWriteLine(L"Failed enabling AMD FreeSync");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					//Enable or disable interface
					adlx_Res0 = ppFSCA->IsSupported(&adlx_Bool);
					{
						toggleswitch_FreeSyncColorAccuracy().IsEnabled(true);

						//Reload settings to get current value
						disable_saving = true;
						adlx_Res0 = ppFSCA->IsEnabled(&adlx_Bool);
						toggleswitch_FreeSyncColorAccuracy().IsOn(adlx_Bool);
						disable_saving = false;
					}

					ShowNotification(L"AMD FreeSync enabled");
					AVDebugWriteLine(L"AMD FreeSync enabled");
				}
			}
			else
			{
				//Enable or disable interface
				toggleswitch_FreeSyncColorAccuracy().IsEnabled(false);

				adlx_Res0 = ppFreeSync->SetEnabled(false);
				ShowNotification(L"AMD FreeSync disabled");
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
					ShowNotification(L"Failed enabling AMD FreeSync Color Accuracy");
					AVDebugWriteLine(L"Failed enabling AMD FreeSync Color Accuracy");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					ShowNotification(L"AMD FreeSync Color Accuracy enabled");
					AVDebugWriteLine(L"AMD FreeSync Color Accuracy enabled");
				}
			}
			else
			{
				adlx_Res0 = ppFSCA->SetEnabled(false);
				ShowNotification(L"AMD FreeSync Color Accuracy disabled");
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
					ShowNotification(L"Failed enabling AMD VSR");
					AVDebugWriteLine(L"Failed enabling AMD VSR");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					ShowNotification(L"AMD VSR enabled");
					AVDebugWriteLine(L"AMD VSR enabled");
				}
			}
			else
			{
				adlx_Res0 = ppVSR->SetEnabled(false);
				ShowNotification(L"AMD VSR disabled");
				AVDebugWriteLine(L"AMD VSR disabled");
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_DynamicRefreshRateControl_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get settings
			IADLXDisplayDynamicRefreshRateControlPtr ppDRRC;
			adlx_Res0 = ppDispServices->GetDynamicRefreshRateControl(ppDisplayInfo, &ppDRRC);

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				adlx_Res0 = ppDRRC->SetEnabled(true);
				if (ADLX_FAILED(adlx_Res0))
				{
					ShowNotification(L"Failed enabling Dynamic Refresh Rate");
					AVDebugWriteLine(L"Failed enabling Dynamic Refresh Rate");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					ShowNotification(L"Dynamic Refresh Rate enabled");
					AVDebugWriteLine(L"Dynamic Refresh Rate enabled");
				}
			}
			else
			{
				adlx_Res0 = ppDRRC->SetEnabled(false);
				ShowNotification(L"Dynamic Refresh Rate disabled");
				AVDebugWriteLine(L"Dynamic Refresh Rate disabled");
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
				ShowNotification(L"Failed setting color depth");
				AVDebugWriteLine(L"Failed setting color depth");
			}
			else
			{
				//Set result
				ShowNotification(L"Color depth set to " + ADLX_COLOR_DEPTH_STRING[newValue]);
				AVDebugWriteLine(L"Color depth set to " << ADLX_COLOR_DEPTH_STRING[newValue]);
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
				ShowNotification(L"Failed setting pixel format");
				AVDebugWriteLine(L"Failed setting pixel format");
			}
			else
			{
				//Set result
				ShowNotification(L"Pixel format set to " + ADLX_PIXEL_FORMAT_STRING[newValue]);
				AVDebugWriteLine(L"Pixel format set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_Display_DisplayColorEnhancement_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get color enhancement value
			auto newValue = sender.as<ComboBox>().SelectedIndex();

			//Get display color enhancement
			IADLXDisplay3DLUTPtr pp3DLUT;
			adlx_Res0 = ppDispServices->Get3DLUT(ppDisplayInfo, &pp3DLUT);

			//Set display color enhancement
			if (newValue == 0)
			{
				adlx_Res0 = pp3DLUT->SetSCEDisabled();
			}
			else if (newValue == 1)
			{
				adlx_Res0 = pp3DLUT->SetSCEVividGaming();
			}
			else
			{
				//Get dynamic contrast intensity value
				auto newValue = slider_DynamicContrastIntensity().Value();
				adlx_Res0 = pp3DLUT->SetSCEDynamicContrast(newValue);
			}

			//Show result
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				ShowNotification(L"Failed setting color enhancement");
				AVDebugWriteLine(L"Failed setting color enhancement");
			}
			else
			{
				//Set result
				ShowNotification(L"Color enhancement set to " + ADLX_SCE_PROFILE_STRING[newValue]);
				AVDebugWriteLine(L"Color enhancement set to " << newValue);
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
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_Display_ColorTemperature().Foreground(colorInvalid);
				ShowNotification(L"Failed setting color temperature");
				AVDebugWriteLine(L"Failed setting color temperature");
			}
			else
			{
				//Set result
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_Display_ColorTemperature().Foreground(colorValid);
				ShowNotification(L"Color temperature set to " + number_to_wstring((int)newValue));
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
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_Display_Brightness().Foreground(colorInvalid);
				ShowNotification(L"Failed setting brightness");
				AVDebugWriteLine(L"Failed setting brightness");
			}
			else
			{
				//Set result
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_Display_Brightness().Foreground(colorValid);
				ShowNotification(L"Brightness set to " + number_to_wstring((int)newValue));
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
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_Display_Contrast().Foreground(colorInvalid);
				ShowNotification(L"Failed setting contrast");
				AVDebugWriteLine(L"Failed setting contrast");
			}
			else
			{
				//Set result
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_Display_Contrast().Foreground(colorValid);
				ShowNotification(L"Contrast set to " + number_to_wstring((int)newValue));
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
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_Display_Saturation().Foreground(colorInvalid);
				ShowNotification(L"Failed setting saturation");
				AVDebugWriteLine(L"Failed setting saturation");
			}
			else
			{
				//Set result
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_Display_Saturation().Foreground(colorValid);
				ShowNotification(L"Saturation set to " + number_to_wstring((int)newValue));
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
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_Display_Hue().Foreground(colorInvalid);
				ShowNotification(L"Failed setting hue");
				AVDebugWriteLine(L"Failed setting hue");
			}
			else
			{
				//Set result
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_Display_Hue().Foreground(colorValid);
				ShowNotification(L"Hue set to " + number_to_wstring((int)newValue));
				AVDebugWriteLine(L"Hue set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::slider_Display_Protanopia_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		AVDebugWriteLine("Wait for ADLX v1.5 release, support has been added to driver 25.12.1");
	}

	void MainPage::slider_Display_Deuteranopia_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		AVDebugWriteLine("Wait for ADLX v1.5 release, support has been added to driver 25.12.1");
	}

	void MainPage::slider_Display_Tritanopia_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		AVDebugWriteLine("Wait for ADLX v1.5 release, support has been added to driver 25.12.1");
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
					ShowNotification(L"Failed enabling GPU Scaling");
					AVDebugWriteLine(L"Failed enabling GPU Scaling");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					//Enable or disable interface
					adlx_Res0 = ppIntegerScaling->IsSupported(&adlx_Bool);
					if (adlx_Bool)
					{
						toggleswitch_IntegerScaling().IsEnabled(true);

						//Reload settings to get current value
						disable_saving = true;
						adlx_Res0 = ppIntegerScaling->IsEnabled(&adlx_Bool);
						toggleswitch_IntegerScaling().IsOn(adlx_Bool);
						disable_saving = false;
					}

					ShowNotification(L"GPU Scaling enabled");
					AVDebugWriteLine(L"GPU Scaling enabled");
				}
			}
			else
			{
				//Enable or disable interface
				toggleswitch_IntegerScaling().IsEnabled(false);

				adlx_Res0 = ppGPUScaling->SetEnabled(false);
				ShowNotification(L"GPU Scaling disabled");
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
					ShowNotification(L"Failed enabling Integer Scaling");
					AVDebugWriteLine(L"Failed enabling Integer Scaling");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					ShowNotification(L"Integer Scaling enabled");
					AVDebugWriteLine(L"Integer Scaling enabled");
				}
			}
			else
			{
				adlx_Res0 = ppIntegerScaling->SetEnabled(false);
				ShowNotification(L"Integer Scaling disabled");
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
				ShowNotification(L"Failed setting scaling mode");
				AVDebugWriteLine(L"Failed setting scaling mode");
			}
			else
			{
				//Set result
				ShowNotification(L"Scaling mode set to " + ADLX_SCALE_MODE_STRING[newValue]);
				AVDebugWriteLine(L"Scaling mode set to " << ADLX_SCALE_MODE_STRING[newValue]);
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
					ShowNotification(L"Failed enabling HDCP Support");
					AVDebugWriteLine(L"Failed enabling HDCP Support");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					ShowNotification(L"HDCP Support enabled");
					AVDebugWriteLine(L"HDCP Support enabled");
				}
			}
			else
			{
				adlx_Res0 = ppHDCP->SetEnabled(false);
				ShowNotification(L"HDCP Support disabled");
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
					ShowNotification(L"Failed enabling Vari-Bright");
					AVDebugWriteLine(L"Failed enabling Vari-Bright");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					//Enable or disable interface
					combobox_Display_VariBright_Level().IsEnabled(true);

					//Reload settings to get current value
					disable_saving = true;
					adlx_Res0 = ppVariBright->IsCurrentMaximizeBrightness(&adlx_Bool);
					if (adlx_Bool)
					{
						combobox_Display_VariBright_Level().SelectedIndex(0);
					}
					adlx_Res0 = ppVariBright->IsCurrentOptimizeBrightness(&adlx_Bool);
					if (adlx_Bool)
					{
						combobox_Display_VariBright_Level().SelectedIndex(1);
					}
					adlx_Res0 = ppVariBright->IsCurrentBalanced(&adlx_Bool);
					if (adlx_Bool)
					{
						combobox_Display_VariBright_Level().SelectedIndex(2);
					}
					adlx_Res0 = ppVariBright->IsCurrentOptimizeBattery(&adlx_Bool);
					if (adlx_Bool)
					{
						combobox_Display_VariBright_Level().SelectedIndex(3);
					}
					adlx_Res0 = ppVariBright->IsCurrentMaximizeBattery(&adlx_Bool);
					if (adlx_Bool)
					{
						combobox_Display_VariBright_Level().SelectedIndex(4);
					}
					disable_saving = false;

					ShowNotification(L"Vari-Bright enabled");
					AVDebugWriteLine(L"Vari-Bright enabled");
				}
			}
			else
			{
				//Enable or disable interface
				combobox_Display_VariBright_Level().IsEnabled(false);

				adlx_Res0 = ppVariBright->SetEnabled(false);
				ShowNotification(L"Vari-Bright disabled");
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
				ShowNotification(L"Vari-Bright set to maximize brightness");
				AVDebugWriteLine(L"Vari-Bright set to maximize brightness");
			}
			else if (newValue == 1)
			{
				adlx_Res0 = ppVariBright->SetOptimizeBrightness();
				ShowNotification(L"Vari-Bright set to optimize brightness");
				AVDebugWriteLine(L"Vari-Bright set to optimize brightness");
			}
			else if (newValue == 2)
			{
				adlx_Res0 = ppVariBright->SetBalanced();
				ShowNotification(L"Vari-Bright set to balanced");
				AVDebugWriteLine(L"Vari-Bright set to balanced");
			}
			else if (newValue == 3)
			{
				adlx_Res0 = ppVariBright->SetOptimizeBattery();
				ShowNotification(L"Vari-Bright set to optimize battery");
				AVDebugWriteLine(L"Vari-Bright set to optimize battery");
			}
			else if (newValue == 4)
			{
				adlx_Res0 = ppVariBright->SetMaximizeBattery();
				ShowNotification(L"Vari-Bright set to maximize battery");
				AVDebugWriteLine(L"Vari-Bright set to maximize battery");
			}
		}
		catch (...) {}
	}

	void MainPage::slider_Display_RelativeVoltageSwing_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get value
			auto newValue = sender.as<Slider>().Value();

			//Get display connectivity experience
			IADLXDisplayConnectivityExperiencePtr ppDisplayConnectivityExperience;
			adlx_Res0 = ppDispServices->GetDisplayConnectivityExperience(ppDisplayInfo, &ppDisplayConnectivityExperience);

			//Set display relative voltage swing
			ppDisplayConnectivityExperience->SetRelativeVoltageSwing(newValue);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_Display_RelativeVoltageSwing().Foreground(colorInvalid);
				ShowNotification(L"Failed setting voltage swing");
				AVDebugWriteLine(L"Failed setting voltage swing");
			}
			else
			{
				//Set result
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_Display_RelativeVoltageSwing().Foreground(colorValid);
				ShowNotification(L"Voltage swing set to " + number_to_wstring((int)newValue));
				AVDebugWriteLine(L"Voltage swing set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::slider_Display_RelativePreEmphasis_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get value
			auto newValue = sender.as<Slider>().Value();

			//Get display connectivity experience
			IADLXDisplayConnectivityExperiencePtr ppDisplayConnectivityExperience;
			adlx_Res0 = ppDispServices->GetDisplayConnectivityExperience(ppDisplayInfo, &ppDisplayConnectivityExperience);

			//Set display relative preset emphasis
			ppDisplayConnectivityExperience->SetRelativePreEmphasis(newValue);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_Display_RelativePreEmphasis().Foreground(colorInvalid);
				ShowNotification(L"Failed setting preset emphasis");
				AVDebugWriteLine(L"Failed setting preset emphasis");
			}
			else
			{
				//Set result
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_Display_RelativePreEmphasis().Foreground(colorValid);
				ShowNotification(L"Preset emphasis set to " + number_to_wstring((int)newValue));
				AVDebugWriteLine(L"Preset emphasis set to " << newValue);
			}
		}
		catch (...) {}
	}
}