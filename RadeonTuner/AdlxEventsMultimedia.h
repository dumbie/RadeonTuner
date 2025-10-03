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

			//Get settings
			IADLXVideoSuperResolutionPtr ppVideoSuperResolution;
			ppMultiMediaServices->GetVideoSuperResolution(ppGpuInfo, &ppVideoSuperResolution);

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				adlx_Res0 = ppVideoSuperResolution->SetEnabled(true);
				if (ADLX_FAILED(adlx_Res0))
				{
					textblock_Status().Text(L"Failed enabling Video Super Resolution");
					AVDebugWriteLine(L"Failed enabling Video Super Resolution");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					textblock_Status().Text(L"Video Super Resolution enabled");
					AVDebugWriteLine(L"Video Super Resolution enabled");
				}
			}
			else
			{
				adlx_Res0 = ppVideoSuperResolution->SetEnabled(false);
				textblock_Status().Text(L"Video Super Resolution disabled");
				AVDebugWriteLine(L"Video Super Resolution disabled");
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

			//Get setting
			IADLXVideoUpscalePtr ppVideoupscale;
			ppMultiMediaServices->GetVideoUpscale(ppGpuInfo, &ppVideoupscale);

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				adlx_Res0 = ppVideoupscale->SetEnabled(true);
				if (ADLX_FAILED(adlx_Res0))
				{
					textblock_Status().Text(L"Failed enabling Video Upscale");
					AVDebugWriteLine(L"Failed enabling Video Upscale");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					//Enable or disable interface
					slider_VideoUpscale_Sharpening().IsEnabled(true);

					//Reload settings to get current value
					disable_saving = true;
					adlx_Res0 = ppVideoupscale->GetSharpness(&adlx_Int0);
					slider_VideoUpscale_Sharpening().Value(adlx_Int0);
					disable_saving = false;

					textblock_Status().Text(L"Video Upscale enabled");
					AVDebugWriteLine(L"Video Upscale enabled");
				}
			}
			else
			{
				//Enable or disable interface
				slider_VideoUpscale_Sharpening().IsEnabled(false);

				adlx_Res0 = ppVideoupscale->SetEnabled(false);
				textblock_Status().Text(L"Video Upscale disabled");
				AVDebugWriteLine(L"Video Upscale disabled");
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

			//Convert new value
			int newValue = (int)e.NewValue();

			//Get setting
			IADLXVideoUpscalePtr ppVideoupscale;
			ppMultiMediaServices->GetVideoUpscale(ppGpuInfo, &ppVideoupscale);

			adlx_Res0 = ppVideoupscale->SetSharpness(newValue);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				slider_VideoUpscale_Sharpening().Foreground(colorInvalid);
				textblock_Status().Text(L"Failed setting video sharpening");
				AVDebugWriteLine(L"Failed setting video sharpening");
			}
			else
			{
				//Set result
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				slider_VideoUpscale_Sharpening().Foreground(colorValid);
				textblock_Status().Text(L"Video sharpening set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Video sharpening set to " << newValue);
			}
		}
		catch (...) {}
	}
}