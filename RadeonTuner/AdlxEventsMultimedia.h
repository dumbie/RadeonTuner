#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::toggleswitch_VideoSuperResolution_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			IADLXVideoSuperResolutionPtr ppVideoSuperResolution;
			adlx_Res0 = ppMultiMediaServices->GetVideoSuperResolution(ppGpuInfo, &ppVideoSuperResolution);
			adlx_Res0 = ppVideoSuperResolution->SetEnabled(newValue);

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
					ShowNotification(L"Failed enabling Video Super Resolution");
					AVDebugWriteLine(L"Failed enabling Video Super Resolution");
				}
				else
				{
					ShowNotification(L"Failed disabling Video Super Resolution");
					AVDebugWriteLine(L"Failed disabling Video Super Resolution");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"Video Super Resolution enabled");
					AVDebugWriteLine(L"Video Super Resolution enabled");
				}
				else
				{
					ShowNotification(L"Video Super Resolution disabled");
					AVDebugWriteLine(L"Video Super Resolution disabled");
				}
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_VideoUpscale_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			IADLXVideoUpscalePtr ppVideoupscale;
			adlx_Res0 = ppMultiMediaServices->GetVideoUpscale(ppGpuInfo, &ppVideoupscale);
			adlx_Res0 = ppVideoupscale->SetEnabled(newValue);

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
					ShowNotification(L"Failed enabling Video Upscale");
					AVDebugWriteLine(L"Failed enabling Video Upscale");
				}
				else
				{
					ShowNotification(L"Failed disabling Video Upscale");
					AVDebugWriteLine(L"Failed disabling Video Upscale");
				}
			}
			else
			{
				if (newValue)
				{
					slider_VideoUpscale_Sharpening().IsEnabled(true);
					ShowNotification(L"Video Upscale enabled");
					AVDebugWriteLine(L"Video Upscale enabled");
				}
				else
				{
					slider_VideoUpscale_Sharpening().IsEnabled(false);
					ShowNotification(L"Video Upscale disabled");
					AVDebugWriteLine(L"Video Upscale disabled");
				}
			}
		}
		catch (...) {}
	}

	void MainPage::slider_VideoUpscale_Sharpening_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Set setting
			IADLXVideoUpscalePtr ppVideoupscale;
			adlx_Res0 = ppMultiMediaServices->GetVideoUpscale(ppGpuInfo, &ppVideoupscale);
			adlx_Res0 = ppVideoupscale->SetSharpness(newValue);

			//Set result
			newFailed = adlx_Res0 != ADLX_OK;

			//Show result
			if (newFailed)
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_VideoUpscale_Sharpening().Foreground(colorInvalid);
				ShowNotification(L"Failed setting Video sharpening");
				AVDebugWriteLine(L"Failed setting Video sharpening");
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_VideoUpscale_Sharpening().Foreground(colorValid);
				ShowNotification(L"Video sharpening set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Video sharpening set to " << newValue);
			}
		}
		catch (...) {}
	}
}