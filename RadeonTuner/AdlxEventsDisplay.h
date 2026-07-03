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
			//Check if saving is disabled
			if (disable_saving) { return; }

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
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Import settings from file
			AdlxValuesImportDisplay();
		}
		catch (...) {}
	}

	void MainPage::button_Display_Export_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Export current settings to file
			AdlxValuesExportDisplay();
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_HdrEnabled_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			ADLDisplayID displayId{};
			displayId.iDisplayLogicalAdapterIndex = adl_Display_AdapterIndex;
			displayId.iDisplayLogicalIndex = adl_Display_DisplayIndex;
			adl_Res0 = _ADL2_Display_HDRState_Set(adl_Context, adl_Display_AdapterIndex, displayId, newValue);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling High Dynamic Range");
					AVDebugWriteLine(L"Failed enabling High Dynamic Range");
				}
				else
				{
					ShowNotification(L"Failed disabling High Dynamic Range");
					AVDebugWriteLine(L"Failed disabling High Dynamic Range");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"High Dynamic Range enabled");
					AVDebugWriteLine(L"High Dynamic Range enabled");
				}
				else
				{
					ShowNotification(L"High Dynamic Range disabled");
					AVDebugWriteLine(L"High Dynamic Range disabled");
				}
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_Display_HdrMediaProfile_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Set setting
			adl_Res0 = _ADL2_Display_HdrTypePreference_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, newValue);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting HDR Media Profile");
				AVDebugWriteLine(L"Failed setting HDR Media Profile");
			}
			else
			{
				ShowNotification(L"HDR Media Profile set to " + ADL_HDR_TYPE_PREFERENCE[newValue]);
				AVDebugWriteLine(L"HDR Media Profile set to " << newValue);
			}
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
			int freeSyncSetting = 0;
			if (newValue)
			{
				freeSyncSetting = ADL_FREESYNC_USECASE_STATIC | ADL_FREESYNC_USECASE_VIDEO | ADL_FREESYNC_USECASE_GAMING;
			}
			adl_Res0 = _ADL2_Display_FreeSyncState_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, freeSyncSetting, 0);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

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
					ShowNotification(L"FreeSync enabled");
					AVDebugWriteLine(L"FreeSync enabled");
				}
				else
				{
					ShowNotification(L"FreeSync disabled");
					AVDebugWriteLine(L"FreeSync disabled");
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
			ADLDisplayProperty displayProperty{};
			displayProperty.iSize = sizeof(displayProperty);
			displayProperty.iPropertyType = ADL_DL_DISPLAYPROPERTY_TYPE_DOWNSCALE;
			displayProperty.iCurrent = newValue;
			adl_Res0 = _ADL2_Display_Property_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &displayProperty);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

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
			adl_Res0 = _ADL2_Display_ColorDepth_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, newValue);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

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
			auto newValue = sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Enumeration index correction
			int convertedValue = 0;
			if (newValue == 0)
			{
				convertedValue = ADL_DISPLAY_PIXELFORMAT_RGB_FULL_RANGE;
			}
			else if (newValue == 1)
			{
				convertedValue = ADL_DISPLAY_PIXELFORMAT_YCRCB444;
			}
			else if (newValue == 2)
			{
				convertedValue = ADL_DISPLAY_PIXELFORMAT_YCRCB422;
			}
			else if (newValue == 3)
			{
				convertedValue = ADL_DISPLAY_PIXELFORMAT_RGB_LIMITED_RANGE;
			}
			else if (newValue == 4)
			{
				convertedValue = ADL_DISPLAY_PIXELFORMAT_YCRCB420;
			}

			//Set setting
			adl_Res0 = _ADL2_Display_PixelFormat_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, convertedValue);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting Pixel format");
				AVDebugWriteLine(L"Failed setting Pixel format");
			}
			else
			{
				ShowNotification(L"Pixel format set to " + ADLX_PIXEL_FORMAT_STRING[newValue + 1]);
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

			//Enumeration index correction
			int convertedValue = 0;
			if (newValue == 0)
			{
				convertedValue = ADLColorEnhancementType::SCE_Disabled;
			}
			else if (newValue == 1)
			{
				convertedValue = ADLColorEnhancementType::SCE_VividGaming;
			}
			else if (newValue == 2)
			{
				convertedValue = ADLColorEnhancementType::SCE_DynamicContrast;
			}

			//Set Setting
			adl_Res0 = _ADL2_Display_SCE_State_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, convertedValue);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

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

	void MainPage::toggleswitch_Display_ColorTemperature_Control_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			if (newValue)
			{
				adl_Res0 = _ADL2_Display_ColorTemperatureSource_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, ADL_DISPLAY_COLOR_TEMPERATURE_SOURCE_USER);
			}
			else
			{
				adl_Res0 = _ADL2_Display_ColorTemperatureSource_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, ADL_DISPLAY_COLOR_TEMPERATURE_SOURCE_EDID);
			}

			//Set result
			newFailed = adl_Res0 != ADL_OK;

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling Temperature Control");
					AVDebugWriteLine(L"Failed enabling Temperature Control");
				}
				else
				{
					ShowNotification(L"Failed disabling Temperature Control");
					AVDebugWriteLine(L"Failed disabling Temperature Control");
				}
			}
			else
			{
				if (newValue)
				{
					slider_Display_ColorTemperature_Kelvin().IsEnabled(true);
					ShowNotification(L"Temperature Control enabled");
					AVDebugWriteLine(L"Temperature Control enabled");
				}
				else
				{
					slider_Display_ColorTemperature_Kelvin().IsEnabled(false);
					ShowNotification(L"Temperature Control disabled");
					AVDebugWriteLine(L"Temperature Control disabled");
				}
			}
		}
		catch (...) {}
	}

	void MainPage::slider_Display_ColorTemperature_Kelvin_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Set setting
			adl_Res0 = _ADL2_Display_Color_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, ADL_DISPLAY_COLOR_TEMPERATURE, newValue);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

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
			adl_Res0 = _ADL2_Display_Color_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, ADL_DISPLAY_COLOR_BRIGHTNESS, newValue);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

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
			adl_Res0 = _ADL2_Display_Color_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, ADL_DISPLAY_COLOR_CONTRAST, newValue);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

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
			adl_Res0 = _ADL2_Display_Color_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, ADL_DISPLAY_COLOR_SATURATION, newValue);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

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
			adl_Res0 = _ADL2_Display_Color_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, ADL_DISPLAY_COLOR_HUE, newValue);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

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

	void MainPage::toggleswitch_Display_CVDC_Control_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			adl_Res0 = _ADL2_Display_CVDC_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, CVDC_ENABLED, newValue);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling CVDC Control");
					AVDebugWriteLine(L"Failed enabling CVDC Control");
				}
				else
				{
					ShowNotification(L"Failed disabling CVDC Control");
					AVDebugWriteLine(L"Failed disabling CVDC Control");
				}
			}
			else
			{
				if (newValue)
				{
					slider_Display_Protanopia().IsEnabled(true);
					slider_Display_Deuteranopia().IsEnabled(true);
					slider_Display_Tritanopia().IsEnabled(true);
					ShowNotification(L"CVDC Control enabled");
					AVDebugWriteLine(L"CVDC Control enabled");
				}
				else
				{
					slider_Display_Protanopia().IsEnabled(false);
					slider_Display_Deuteranopia().IsEnabled(false);
					slider_Display_Tritanopia().IsEnabled(false);
					ShowNotification(L"CVDC Control disabled");
					AVDebugWriteLine(L"CVDC Control disabled");
				}
			}
		}
		catch (...) {}
	}

	void MainPage::slider_Display_Protanopia_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Set setting
			adl_Res0 = _ADL2_Display_CVDC_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, CVDC_PROTANOPIA, newValue);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

			//Show result
			if (newFailed)
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_Display_Protanopia().Foreground(colorInvalid);
				ShowNotification(L"Failed setting Protanopia");
				AVDebugWriteLine(L"Failed setting Protanopia");
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_Display_Protanopia().Foreground(colorValid);
				ShowNotification(L"Protanopia set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Protanopia set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::slider_Display_Deuteranopia_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Set setting
			adl_Res0 = _ADL2_Display_CVDC_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, CVDC_DEUTERANOPIA, newValue);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

			//Show result
			if (newFailed)
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_Display_Deuteranopia().Foreground(colorInvalid);
				ShowNotification(L"Failed setting Deuteranopia");
				AVDebugWriteLine(L"Failed setting Deuteranopia");
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_Display_Deuteranopia().Foreground(colorValid);
				ShowNotification(L"Deuteranopia set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Deuteranopia set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::slider_Display_Tritanopia_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Set setting
			adl_Res0 = _ADL2_Display_CVDC_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, CVDC_TRITANOPIA, newValue);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

			//Show result
			if (newFailed)
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_Display_Tritanopia().Foreground(colorInvalid);
				ShowNotification(L"Failed setting Tritanopia");
				AVDebugWriteLine(L"Failed setting Tritanopia");
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_Display_Tritanopia().Foreground(colorValid);
				ShowNotification(L"Tritanopia set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Tritanopia set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_GpuScaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			adl_Res0 = _ADL2_DFP_GPUScalingEnable_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, newValue);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

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
					ShowNotification(L"GPU Scaling enabled");
					AVDebugWriteLine(L"GPU Scaling enabled");
				}
				else
				{
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
			ADLDisplayProperty displayProperty{};
			displayProperty.iSize = sizeof(displayProperty);
			displayProperty.iPropertyType = ADL_DL_DISPLAYPROPERTY_TYPE_INTEGER_SCALING;
			displayProperty.iCurrent = newValue;
			adl_Res0 = _ADL2_Display_Property_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &displayProperty);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

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
			if (newValue == 0)
			{
				//Preserve Aspect Ratio
				adl_Res0 = _ADL2_Display_PreservedAspectRatio_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, 1);
			}
			else if (newValue == 1)
			{
				//Full Panel
				adl_Res0 = _ADL2_Display_ImageExpansion_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, 1);
			}
			else if (newValue == 2)
			{
				//Centered
				adl_Res0 = _ADL2_Display_ImageExpansion_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, 0);
			}

			//Set result
			newFailed = adl_Res0 != ADL_OK;

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
			adl_Res0 = _ADL2_Display_HDCP_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, false, newValue);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

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
			adl_Res0 = _ADL2_Adapter_VariBrightEnable_Set(adl_Context, adl_Gpu_AdapterIndex, newValue);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

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
			adl_Res0 = _ADL2_Adapter_VariBrightLevel_Set(adl_Context, adl_Gpu_AdapterIndex, newValue, true);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

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
}