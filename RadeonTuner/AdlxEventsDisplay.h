#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::button_Display_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Reset display settings
			bool resetResult = AdlxValuesResetDisplay();

			//Check result
			if (resetResult)
			{
				//Show notification
				ShowNotification(L"Display settings reset");
				AVDebugWriteLine(L"Display settings reset");
			}
			else
			{
				//Show notification
				ShowNotification(L"Display settings not reset");
				AVDebugWriteLine(L"Display settings not reset");
			}
		}
		catch (...) {}
	}

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

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Set setting
			IADLXDisplayFreeSyncPtr ppFreeSync;
			adlx_Res0 = ppDispServices->GetFreeSync(ppDisplayInfo, &ppFreeSync);
			adlx_Res0 = ppFreeSync->SetEnabled(newValue);

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling FreeSync");
					AVDebugWriteLine(L"Failed enabling FreeSync");
				}
				else
				{
					ShowNotification(L"Failed disabling FreeSync");
					AVDebugWriteLine(L"Failed disabling FreeSync");
				}
			}
			else
			{
				if (newValue)
				{
					IADLXDisplayFreeSyncColorAccuracyPtr ppFSCA;
					adlx_Res0 = ppDispServices->GetFreeSyncColorAccuracy(ppDisplayInfo, &ppFSCA);
					adlx_Res0 = ppFSCA->IsSupported(&adlx_Bool);
					if (ADLX_SUCCEEDED(adlx_Res0) && adlx_Bool)
					{
						toggleswitch_FreeSyncColorAccuracy().IsEnabled(true);
					}

					ShowNotification(L"FreeSync enabled");
					AVDebugWriteLine(L"FreeSync enabled");
				}
				else
				{
					toggleswitch_FreeSyncColorAccuracy().IsEnabled(false);
					ShowNotification(L"FreeSync disabled");
					AVDebugWriteLine(L"FreeSync disabled");
				}
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

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Set setting
			IADLXDisplayFreeSyncColorAccuracyPtr ppFSCA;
			adlx_Res0 = ppDispServices->GetFreeSyncColorAccuracy(ppDisplayInfo, &ppFSCA);
			adlx_Res0 = ppFSCA->SetEnabled(newValue);

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling FreeSync Color Accuracy");
					AVDebugWriteLine(L"Failed enabling FreeSync Color Accuracy");
				}
				else
				{
					ShowNotification(L"Failed disabling FreeSync Color Accuracy");
					AVDebugWriteLine(L"Failed disabling FreeSync Color Accuracy");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"FreeSync Color Accuracy enabled");
					AVDebugWriteLine(L"FreeSync Color Accuracy enabled");
				}
				else
				{
					ShowNotification(L"FreeSync Color Accuracy disabled");
					AVDebugWriteLine(L"FreeSync Color Accuracy disabled");
				}
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

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Set setting
			IADLXDisplayVSRPtr ppVSR;
			adlx_Res0 = ppDispServices->GetVirtualSuperResolution(ppDisplayInfo, &ppVSR);
			adlx_Res0 = ppVSR->SetEnabled(newValue);

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling Virtual Super Resolution");
					AVDebugWriteLine(L"Failed enabling Virtual Super Resolution");
				}
				else
				{
					ShowNotification(L"Failed disabling Virtual Super Resolution");
					AVDebugWriteLine(L"Failed disabling Virtual Super Resolution");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"Virtual Super Resolution enabled");
					AVDebugWriteLine(L"Virtual Super Resolution enabled");
				}
				else
				{
					ShowNotification(L"Virtual Super Resolution disabled");
					AVDebugWriteLine(L"Virtual Super Resolution disabled");
				}
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

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Set setting
			IADLXDisplayDynamicRefreshRateControlPtr ppDRRC;
			adlx_Res0 = ppDispServices->GetDynamicRefreshRateControl(ppDisplayInfo, &ppDRRC);
			adlx_Res0 = ppDRRC->SetEnabled(newValue);

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling Dynamic Refresh Rate");
					AVDebugWriteLine(L"Failed enabling Dynamic Refresh Rate");
				}
				else
				{
					ShowNotification(L"Failed disabling Dynamic Refresh Rate");
					AVDebugWriteLine(L"Failed disabling Dynamic Refresh Rate");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"Dynamic Refresh Rate enabled");
					AVDebugWriteLine(L"Dynamic Refresh Rate enabled");
				}
				else
				{
					ShowNotification(L"Dynamic Refresh Rate disabled");
					AVDebugWriteLine(L"Dynamic Refresh Rate disabled");
				}
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

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex() + 1;
			bool newFailed = true;

			//Set setting
			IADLXDisplayColorDepthPtr ppColorDepth;
			adlx_Res0 = ppDispServices->GetColorDepth(ppDisplayInfo, &ppColorDepth);
			adlx_Res0 = ppColorDepth->SetValue((ADLX_COLOR_DEPTH)newValue);

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting Color depth");
				AVDebugWriteLine(L"Failed setting Color depth");
			}
			else
			{
				ShowNotification(L"Color depth set to " + ADLX_COLOR_DEPTH_STRING[newValue]);
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

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex() + 1;
			bool newFailed = true;

			//Set setting
			IADLXDisplayPixelFormatPtr ppPixelFormat;
			adlx_Res0 = ppDispServices->GetPixelFormat(ppDisplayInfo, &ppPixelFormat);
			adlx_Res0 = ppPixelFormat->SetValue((ADLX_PIXEL_FORMAT)newValue);

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting Pixel format");
				AVDebugWriteLine(L"Failed setting Pixel format");
			}
			else
			{
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

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Set setting
			IADLXDisplay3DLUTPtr pp3DLUT;
			adlx_Res0 = ppDispServices->Get3DLUT(ppDisplayInfo, &pp3DLUT);

			//Enumeration index correction
			if (newValue == 0)
			{
				adlx_Res0 = pp3DLUT->SetSCEDisabled();
			}
			else if (newValue == 1)
			{
				adlx_Res0 = pp3DLUT->SetSCEVividGaming();
			}
			else if (newValue == 2)
			{
				//Get dynamic contrast intensity value
				auto newValueIntensity = slider_DynamicContrastIntensity().Value();
				adlx_Res0 = pp3DLUT->SetSCEDynamicContrast(newValueIntensity);
			}

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting Color enhancement");
				AVDebugWriteLine(L"Failed setting Color enhancement");
			}
			else
			{
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

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Fix find way to enable color temperature control when disabled in AMD Adrenalin

			//Set setting
			IADLXDisplayCustomColorPtr ppCustomColor;
			adlx_Res0 = ppDispServices->GetCustomColor(ppDisplayInfo, &ppCustomColor);
			adlx_Res0 = ppCustomColor->SetTemperature(newValue);

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_Display_ColorTemperature().Foreground(colorInvalid);
				ShowNotification(L"Failed setting Color temperature");
				AVDebugWriteLine(L"Failed setting Color temperature");
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_Display_ColorTemperature().Foreground(colorValid);
				ShowNotification(L"Color temperature set to " + number_to_wstring(newValue));
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

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Set setting
			IADLXDisplayCustomColorPtr ppCustomColor;
			adlx_Res0 = ppDispServices->GetCustomColor(ppDisplayInfo, &ppCustomColor);
			adlx_Res0 = ppCustomColor->SetBrightness(newValue);

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_Display_Brightness().Foreground(colorInvalid);
				ShowNotification(L"Failed setting Brightness");
				AVDebugWriteLine(L"Failed setting Brightness");
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_Display_Brightness().Foreground(colorValid);
				ShowNotification(L"Brightness set to " + number_to_wstring(newValue));
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

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Set setting
			IADLXDisplayCustomColorPtr ppCustomColor;
			adlx_Res0 = ppDispServices->GetCustomColor(ppDisplayInfo, &ppCustomColor);
			adlx_Res0 = ppCustomColor->SetContrast(newValue);

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_Display_Contrast().Foreground(colorInvalid);
				ShowNotification(L"Failed setting Contrast");
				AVDebugWriteLine(L"Failed setting Contrast");
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_Display_Contrast().Foreground(colorValid);
				ShowNotification(L"Contrast set to " + number_to_wstring(newValue));
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

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Set setting
			IADLXDisplayCustomColorPtr ppCustomColor;
			adlx_Res0 = ppDispServices->GetCustomColor(ppDisplayInfo, &ppCustomColor);
			adlx_Res0 = ppCustomColor->SetSaturation(newValue);

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_Display_Saturation().Foreground(colorInvalid);
				ShowNotification(L"Failed setting Saturation");
				AVDebugWriteLine(L"Failed setting Saturation");
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_Display_Saturation().Foreground(colorValid);
				ShowNotification(L"Saturation set to " + number_to_wstring(newValue));
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

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Set setting
			IADLXDisplayCustomColorPtr ppCustomColor;
			adlx_Res0 = ppDispServices->GetCustomColor(ppDisplayInfo, &ppCustomColor);
			adlx_Res0 = ppCustomColor->SetHue(newValue);

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_Display_Hue().Foreground(colorInvalid);
				ShowNotification(L"Failed setting Hue");
				AVDebugWriteLine(L"Failed setting Hue");
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_Display_Hue().Foreground(colorValid);
				ShowNotification(L"Hue set to " + number_to_wstring(newValue));
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

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Set setting
			IADLXDisplayGPUScalingPtr ppGPUScaling;
			adlx_Res0 = ppDispServices->GetGPUScaling(ppDisplayInfo, &ppGPUScaling);
			adlx_Res0 = ppGPUScaling->SetEnabled(newValue);

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling GPU Scaling");
					AVDebugWriteLine(L"Failed enabling GPU Scaling");
				}
				else
				{
					ShowNotification(L"Failed disabling GPU Scaling");
					AVDebugWriteLine(L"Failed disabling GPU Scaling");
				}
			}
			else
			{
				if (newValue)
				{
					IADLXDisplayIntegerScalingPtr ppIntegerScaling;
					adlx_Res0 = ppDispServices->GetIntegerScaling(ppDisplayInfo, &ppIntegerScaling);
					adlx_Res0 = ppIntegerScaling->IsSupported(&adlx_Bool);
					if (ADLX_SUCCEEDED(adlx_Res0) && adlx_Bool)
					{
						toggleswitch_IntegerScaling().IsEnabled(true);
					}

					ShowNotification(L"GPU Scaling enabled");
					AVDebugWriteLine(L"GPU Scaling enabled");
				}
				else
				{
					toggleswitch_IntegerScaling().IsEnabled(false);
					ShowNotification(L"GPU Scaling disabled");
					AVDebugWriteLine(L"GPU Scaling disabled");
				}
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

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Set setting
			IADLXDisplayIntegerScalingPtr ppIntegerScaling;
			adlx_Res0 = ppDispServices->GetIntegerScaling(ppDisplayInfo, &ppIntegerScaling);
			adlx_Res0 = ppIntegerScaling->SetEnabled(newValue);

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling Integer Scaling");
					AVDebugWriteLine(L"Failed enabling Integer Scaling");
				}
				else
				{
					ShowNotification(L"Failed disabling Integer Scaling");
					AVDebugWriteLine(L"Failed disabling Integer Scaling");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"Integer Scaling enabled");
					AVDebugWriteLine(L"Integer Scaling enabled");
				}
				else
				{
					ShowNotification(L"Integer Scaling disabled");
					AVDebugWriteLine(L"Integer Scaling disabled");
				}
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

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Set setting
			IADLXDisplayScalingModePtr ppScalingMode;
			adlx_Res0 = ppDispServices->GetScalingMode(ppDisplayInfo, &ppScalingMode);
			adlx_Res0 = ppScalingMode->SetMode((ADLX_SCALE_MODE)newValue);

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting Scaling mode");
				AVDebugWriteLine(L"Failed setting Scaling mode");
			}
			else
			{
				ShowNotification(L"Scaling mode set to " + ADLX_SCALE_MODE_STRING[newValue]);
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

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Set setting
			IADLXDisplayHDCPPtr ppHDCP;
			adlx_Res0 = ppDispServices->GetHDCP(ppDisplayInfo, &ppHDCP);
			adlx_Res0 = ppHDCP->SetEnabled(newValue);

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling HDCP Support");
					AVDebugWriteLine(L"Failed enabling HDCP Support");
				}
				else
				{
					ShowNotification(L"Failed disabling HDCP Support");
					AVDebugWriteLine(L"Failed disabling HDCP Support");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"HDCP Support enabled");
					AVDebugWriteLine(L"HDCP Support enabled");
				}
				else
				{
					ShowNotification(L"HDCP Support disabled");
					AVDebugWriteLine(L"HDCP Support disabled");
				}
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

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Set setting
			IADLXDisplayVariBrightPtr ppVariBright;
			adlx_Res0 = ppDispServices->GetVariBright(ppDisplayInfo, &ppVariBright);
			adlx_Res0 = ppVariBright->SetEnabled(newValue);

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling Vari-Bright");
					AVDebugWriteLine(L"Failed enabling Vari-Bright");
				}
				else
				{
					ShowNotification(L"Failed disabling Vari-Bright");
					AVDebugWriteLine(L"Failed disabling Vari-Bright");
				}
			}
			else
			{
				if (newValue)
				{
					combobox_Display_VariBright_Level().IsEnabled(true);
					ShowNotification(L"Vari-Bright enabled");
					AVDebugWriteLine(L"Vari-Bright enabled");
				}
				else
				{
					combobox_Display_VariBright_Level().IsEnabled(false);
					ShowNotification(L"Vari-Bright disabled");
					AVDebugWriteLine(L"Vari-Bright disabled");
				}
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

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Set setting
			IADLXDisplayVariBrightPtr ppVariBright;
			adlx_Res0 = ppDispServices->GetVariBright(ppDisplayInfo, &ppVariBright);

			//Enumeration index correction
			if (newValue == 0)
			{
				adlx_Res0 = ppVariBright->SetMaximizeBrightness();
			}
			else if (newValue == 1)
			{
				adlx_Res0 = ppVariBright->SetOptimizeBrightness();
			}
			else if (newValue == 2)
			{
				adlx_Res0 = ppVariBright->SetBalanced();
			}
			else if (newValue == 3)
			{
				adlx_Res0 = ppVariBright->SetOptimizeBattery();
			}
			else if (newValue == 4)
			{
				adlx_Res0 = ppVariBright->SetMaximizeBattery();
			}

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting Vari-Bright level");
				AVDebugWriteLine(L"Failed setting Vari-Bright level");
			}
			else
			{
				ShowNotification(L"Vari-Bright set to " + ADLX_VARIBRIGHT_LEVEL_STRING[newValue]);
				AVDebugWriteLine(L"Vari-Bright set to " << newValue);
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

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Set setting
			IADLXDisplayConnectivityExperiencePtr ppDisplayConnectivityExperience;
			adlx_Res0 = ppDispServices->GetDisplayConnectivityExperience(ppDisplayInfo, &ppDisplayConnectivityExperience);
			adlx_Res0 = ppDisplayConnectivityExperience->SetRelativeVoltageSwing(newValue);

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_Display_RelativeVoltageSwing().Foreground(colorInvalid);
				ShowNotification(L"Failed setting Voltage swing");
				AVDebugWriteLine(L"Failed setting Voltage swing");
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_Display_RelativeVoltageSwing().Foreground(colorValid);
				ShowNotification(L"Voltage swing set to " + number_to_wstring(newValue));
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

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Set setting
			IADLXDisplayConnectivityExperiencePtr ppDisplayConnectivityExperience;
			adlx_Res0 = ppDispServices->GetDisplayConnectivityExperience(ppDisplayInfo, &ppDisplayConnectivityExperience);
			adlx_Res0 = ppDisplayConnectivityExperience->SetRelativePreEmphasis(newValue);

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_Display_RelativePreEmphasis().Foreground(colorInvalid);
				ShowNotification(L"Failed setting Preset emphasis");
				AVDebugWriteLine(L"Failed setting Preset emphasis");
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_Display_RelativePreEmphasis().Foreground(colorValid);
				ShowNotification(L"Preset emphasis set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Preset emphasis set to " << newValue);
			}
		}
		catch (...) {}
	}
}