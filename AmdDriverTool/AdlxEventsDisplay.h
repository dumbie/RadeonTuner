#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::toggleswitch_FreeSync_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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
			adlx_Res0 = ppFreeSync->SetEnabled(false);
			textblock_Status().Text(L"AMD FreeSync disabled");
			AVDebugWriteLine(L"AMD FreeSync disabled");
		}
	}

	void MainPage::toggleswitch_VSR_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
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

	void MainPage::combobox_Display_ColorDepth_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
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

	void MainPage::combobox_Display_PixelFormat_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
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

	void MainPage::slider_Display_Contrast_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Get contrast value
		auto newValue = sender.as<Slider>().Value();

		//Get display custom color profile
		IADLXDisplayCustomColorPtr ppCustomColor;
		adlx_Res0 = ppDispServices->GetCustomColor(ppDisplayInfo, &ppCustomColor);

		//Set display contrast
		ppCustomColor->SetContrast(newValue);
	}

	void MainPage::slider_Display_Saturation_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Get saturation value
		auto newValue = sender.as<Slider>().Value();

		//Get display custom color profile
		IADLXDisplayCustomColorPtr ppCustomColor;
		adlx_Res0 = ppDispServices->GetCustomColor(ppDisplayInfo, &ppCustomColor);

		//Set display saturation
		ppCustomColor->SetSaturation(newValue);
	}

	void MainPage::toggleswitch_GPUScaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Get settings
		IADLXDisplayGPUScalingPtr ppGPUScaling;
		adlx_Res0 = ppDispServices->GetGPUScaling(ppDisplayInfo, &ppGPUScaling);

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
				textblock_Status().Text(L"GPU Scaling enabled");
				AVDebugWriteLine(L"GPU Scaling enabled");
			}
		}
		else
		{
			adlx_Res0 = ppGPUScaling->SetEnabled(false);
			textblock_Status().Text(L"GPU Scaling disabled");
			AVDebugWriteLine(L"GPU Scaling disabled");
		}
	}
}