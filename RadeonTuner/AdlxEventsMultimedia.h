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

			//Profile is used
			bool usingProfile = multimediaSettingsCurrent.get().UsingProfile;

			//Device identifier
			std::wstring deviceIdW = multimediaSettingsCurrent.get().DeviceId.value();

			//Device application
			std::wstring applicationW = multimediaSettingsCurrent.get().Application.value();

			//Save multimedia settings
			MultimediaSettings_Profiles_SaveToFile();

			//Check if profile is used
			if (usingProfile)
			{
				//Apply current settings
				bool applyResult = AdlMultimediaSettingsApply(adl_Gpu_AdapterIndex, multimediaSettingsCurrent.get(), AdlSettingGet::Current);

				//Check result
				if (applyResult)
				{
					//Show notification
					ShowNotification(L"Multimedia settings applied");
					AVDebugWriteLine(L"Multimedia settings applied");

					//Load multimedia settings
					AdlxValuesLoadSelectMultimediaApp(adl_Gpu_AdapterIndex, applicationW);
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
			int messageResult = co_await ShowMessageBox(L"Reset multimedia settings?", L"", messageAnswers);
			if (messageResult == 1)
			{
				co_return;
			}

			//Profile is used
			bool usingProfile = multimediaSettingsCurrent.get().UsingProfile;

			//Device identifier
			std::wstring deviceIdW = multimediaSettingsCurrent.get().DeviceId.value();

			//Device application
			std::wstring applicationW = multimediaSettingsCurrent.get().Application.value();

			//Remove multimedia settings
			if (MultimediaSettings_Profile_Remove(deviceIdW, applicationW))
			{
				//Save multimedia settings
				MultimediaSettings_Profiles_SaveToFile();
			}

			//Check if profile is used
			if (usingProfile)
			{
				//Get current and default settings
				MultimediaSettings multimediaSettings = MultimediaSettings_Generate_FromADL(adl_Gpu_AdapterIndex, L"").value();

				//Apply default settings
				AdlMultimediaSettingsApply(adl_Gpu_AdapterIndex, multimediaSettings, AdlSettingGet::Default);
			}

			//Show notification
			ShowNotification(L"Multimedia settings reset");
			AVDebugWriteLine(L"Multimedia settings reset: " << deviceIdW << L" / " << applicationW);

			//Load multimedia settings
			AdlxValuesLoadSelectMultimediaApp(adl_Gpu_AdapterIndex, applicationW);
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
			multimediaSettingsCurrent.get().VideoUpscaling.Current = newValue;
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
			multimediaSettingsCurrent.get().VideoSharpening.Current = newValue;
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
			multimediaSettingsCurrent.get().VideoBrightness.Current = newValue;
		}
		catch (...) {}
	}
}