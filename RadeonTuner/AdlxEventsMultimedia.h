#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::button_Multimedia_Apply_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Apply current settings
			bool applyResult = AdlMultimediaSettingsApply(adl_Gpu_AdapterIndex, multimediaSettingsCurrent, AdlSettingGet::Current);

			//Check result
			if (applyResult)
			{
				//Show notification
				ShowNotification(L"Multimedia settings applied");
				AVDebugWriteLine(L"Multimedia settings applied");

				//Load multimedia settings
				AdlxValuesLoadSelectMultimediaApp();
			}
			else
			{
				//Show notification
				ShowNotification(L"Multimedia settings not applied");
				AVDebugWriteLine(L"Multimedia settings not applied");

				//Update button colors
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				button_Multimedia_Apply().Background(colorInvalid);
			}
		}
		catch (...) {}
	}

	winrt::fire_and_forget MainPage::button_Multimedia_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { co_return; }

			//Confirm reset
			std::vector<std::wstring> messageAnswers{ L"Yes", L"No" };
			int messageResult = co_await ShowMessageBox(L"Reset settings?", L"", messageAnswers);
			if (messageResult == 1)
			{
				co_return;
			}

			//Get current and default settings
			MultimediaSettings multimediaSettings = MultimediaSettings_Generate_FromADL(adl_Gpu_AdapterIndex).value();

			//Apply default settings
			bool applyResult = AdlMultimediaSettingsApply(adl_Gpu_AdapterIndex, multimediaSettings, AdlSettingGet::Default);

			//Check result
			if (applyResult)
			{
				//Show notification
				ShowNotification(L"Multimedia settings reset");
				AVDebugWriteLine(L"Multimedia settings reset");

				//Load multimedia settings
				AdlxValuesLoadSelectMultimediaApp();
			}
			else
			{
				//Show notification
				ShowNotification(L"Multimedia settings not reset");
				AVDebugWriteLine(L"Multimedia settings not reset");

				//Update button colors
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				button_Multimedia_Apply().Background(colorInvalid);
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_Video_Upscaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();

			//Update interface
			if (newValue)
			{
				slider_Video_Sharpening().IsEnabled(true);
			}
			else
			{
				slider_Video_Sharpening().IsEnabled(false);
			}

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Multimedia_Apply().Background(colorIgnored);

			//Update current value
			multimediaSettingsCurrent.VideoUpscaling.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_Video_Sharpening_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Multimedia_Apply().Background(colorIgnored);

			//Update current value
			multimediaSettingsCurrent.VideoSharpening.Current = newValue;
		}
		catch (...) {}
	}

	void MainPage::slider_Video_Brightness_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();

			//Adjust button colors
			SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
			button_Multimedia_Apply().Background(colorIgnored);

			//Update current value
			multimediaSettingsCurrent.VideoBrightness.Current = newValue;
		}
		catch (...) {}
	}
}