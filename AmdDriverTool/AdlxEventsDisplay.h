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

		//Get FreeSync settings
		IADLXDisplayFreeSyncPtr ppFreeSync;
		adlx_Res0 = ppDispServices->GetFreeSync(ppDisplayInfo, &ppFreeSync);

		if (sender.as<ToggleSwitch>().IsOn())
		{
			adlx_Res0 = ppFreeSync->SetEnabled(true);
			textblock_Status().Text(L"AMD FreeSync enabled");
			AVDebugWriteLine(L"AMD FreeSync enabled");
		}
		else
		{
			adlx_Res0 = ppFreeSync->SetEnabled(false);
			textblock_Status().Text(L"AMD FreeSync disabled");
			AVDebugWriteLine(L"AMD FreeSync disabled");
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
}