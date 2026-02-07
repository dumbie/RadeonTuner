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

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Set setting
			IADLXSmartShiftEcoPtr ppSmartShiftEco;
			adlx_Res0 = ppPowerTuningServices->GetSmartShiftEco(&ppSmartShiftEco);
			adlx_Res0 = ppSmartShiftEco->SetEnabled(newValue);

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
					ShowNotification(L"Failed enabling SmartShift Eco");
					AVDebugWriteLine(L"Failed enabling SmartShift Eco");
				}
				else
				{
					ShowNotification(L"Failed disabling SmartShift Eco");
					AVDebugWriteLine(L"Failed disabling SmartShift Eco");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"SmartShift Eco enabled");
					AVDebugWriteLine(L"SmartShift Eco enabled");
				}
				else
				{
					ShowNotification(L"SmartShift Eco disabled");
					AVDebugWriteLine(L"SmartShift Eco disabled");
				}
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

			//Get setting value
			ADLX_SSM_BIAS_MODE newValue = (ADLX_SSM_BIAS_MODE)sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Set setting
			IADLXSmartShiftMaxPtr ppSmartShiftMax;
			adlx_Res0 = ppPowerTuningServices->GetSmartShiftMax(&ppSmartShiftMax);
			adlx_Res0 = ppSmartShiftMax->SetBiasMode(newValue);

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting SmartShift mode");
				AVDebugWriteLine(L"Failed setting SmartShift mode");
			}
			else
			{
				if (newValue == ADLX_SSM_BIAS_MODE::SSM_BIAS_AUTO)
				{
					slider_SmartShiftMaxBias().IsEnabled(false);
				}
				else
				{
					slider_SmartShiftMaxBias().IsEnabled(true);
				}

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

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Set setting
			IADLXSmartShiftMaxPtr ppSmartShiftMax;
			adlx_Res0 = ppPowerTuningServices->GetSmartShiftMax(&ppSmartShiftMax);
			adlx_Res0 = ppSmartShiftMax->SetBias(newValue);

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_SmartShiftMaxBias().Foreground(colorInvalid);
				ShowNotification(L"Failed setting SmartShift bias");
				AVDebugWriteLine(L"Failed setting SmartShift bias");
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_SmartShiftMaxBias().Foreground(colorValid);
				ShowNotification(L"SmartShift bias set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"SmartShift bias set to " << newValue);
			}
		}
		catch (...) {}
	}
}