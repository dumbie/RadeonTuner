#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::toggleswitch_SmartShiftEco_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get settings
			IADLXSmartShiftEcoPtr ppSmartShiftEco;
			adlx_Res0 = ppPowerTuningServices->GetSmartShiftEco(&ppSmartShiftEco);

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				adlx_Res0 = ppSmartShiftEco->SetEnabled(true);
				if (ADLX_FAILED(adlx_Res0))
				{
					ShowNotification(L"Failed enabling SmartShift Eco");
					AVDebugWriteLine(L"Failed enabling SmartShift Eco");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					ShowNotification(L"SmartShift Eco enabled");
					AVDebugWriteLine(L"SmartShift Eco enabled");
				}
			}
			else
			{
				adlx_Res0 = ppSmartShiftEco->SetEnabled(false);
				ShowNotification(L"SmartShift Eco disabled");
				AVDebugWriteLine(L"SmartShift Eco disabled");
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_SmartShiftMaxMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get value
			ADLX_SSM_BIAS_MODE newValue = (ADLX_SSM_BIAS_MODE)sender.as<ComboBox>().SelectedIndex();

			//Get settings
			IADLXSmartShiftMaxPtr ppSmartShiftMax;
			adlx_Res0 = ppPowerTuningServices->GetSmartShiftMax(&ppSmartShiftMax);

			//Set settings
			adlx_Res0 = ppSmartShiftMax->SetBiasMode(newValue);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				ShowNotification(L"Failed setting SmartShift mode");
				AVDebugWriteLine(L"Failed setting SmartShift mode");
			}
			else
			{
				//Enable or disable interface
				if (newValue == ADLX_SSM_BIAS_MODE::SSM_BIAS_AUTO)
				{
					slider_SmartShiftMaxBias().IsEnabled(false);
				}
				else
				{
					slider_SmartShiftMaxBias().IsEnabled(true);

					//Reload settings to get current value
					disable_saving = true;
					adlx_Res0 = ppSmartShiftMax->GetBias(&adlx_Int0);
					slider_SmartShiftMaxBias().Value(adlx_Int0);
					disable_saving = false;
				}

				//Set result
				ShowNotification(L"SmartShift mode set to " + ADLX_SSM_BIAS_MODE_STRING[newValue]);
				AVDebugWriteLine(L"SmartShift mode set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::slider_SmartShiftMaxBias_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get value
			auto newValue = sender.as<Slider>().Value();

			//Get settings
			IADLXSmartShiftMaxPtr ppSmartShiftMax;
			adlx_Res0 = ppPowerTuningServices->GetSmartShiftMax(&ppSmartShiftMax);

			//Set settings
			adlx_Res0 = ppSmartShiftMax->SetBias(newValue);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_SmartShiftMaxBias().Foreground(colorInvalid);
				ShowNotification(L"Failed setting SmartShift bias");
				AVDebugWriteLine(L"Failed setting SmartShift bias");
			}
			else
			{
				//Set result
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_SmartShiftMaxBias().Foreground(colorValid);
				ShowNotification(L"SmartShift bias set to " + number_to_wstring((int)newValue));
				AVDebugWriteLine(L"SmartShift bias set to " << newValue);
			}
		}
		catch (...) {}
	}
}