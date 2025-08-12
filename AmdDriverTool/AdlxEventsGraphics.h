#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::toggleswitch_RadeonSuperResolution_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Get super resolution
		IADLX3DRadeonSuperResolutionPtr pp3DRadeonSuperResolution;
		adlx_Res0 = pp3DSettingsServices->GetRadeonSuperResolution(&pp3DRadeonSuperResolution);

		if (sender.as<ToggleSwitch>().IsOn())
		{
			adlx_Res0 = pp3DRadeonSuperResolution->SetEnabled(true);
			slider_RadeonSuperResolution_Sharpening().IsEnabled(true);
			textblock_Status().Text(L"Radeon Super Resolution enabled");
			AVDebugWriteLine(L"Radeon Super Resolution enabled");
		}
		else
		{
			adlx_Res0 = pp3DRadeonSuperResolution->SetEnabled(false);
			slider_RadeonSuperResolution_Sharpening().IsEnabled(false);
			textblock_Status().Text(L"Radeon Super Resolution disabled");
			AVDebugWriteLine(L"Radeon Super Resolution disabled");
		}
	}

	void MainPage::slider_RadeonSuperResolution_Sharpening_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Convert new value
		int newValue = (int)e.NewValue();

		//Get super resolution
		IADLX3DRadeonSuperResolutionPtr pp3DRadeonSuperResolution;
		adlx_Res0 = pp3DSettingsServices->GetRadeonSuperResolution(&pp3DRadeonSuperResolution);

		adlx_Res0 = pp3DRadeonSuperResolution->SetSharpness(newValue);
		if (ADLX_FAILED(adlx_Res0))
		{
			//Set result
			textblock_RadeonSuperResolution_Sharpening().Foreground(SolidColorBrush(Windows::UI::Colors::Red()));
			textblock_Status().Text(L"Failed setting sharpening");
			AVDebugWriteLine(L"Failed setting sharpening");
		}
		else
		{
			//Set result
			textblock_RadeonSuperResolution_Sharpening().Foreground(SolidColorBrush(Windows::UI::Colors::Green()));
			textblock_Status().Text(L"Sharpening set to " + number_to_wstring(newValue));
			AVDebugWriteLine(L"Sharpening set to " << newValue);
		}
	}

	void MainPage::toggleswitch_RadeonFluidMotionFrames_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Get settings
		IADLX3DAMDFluidMotionFramesPtr pp3DAMDFluidMotionFrames;
		adlx_Res0 = pp3DSettingsServices->GetAMDFluidMotionFrames(&pp3DAMDFluidMotionFrames);

		ToggleSwitch senderElement = sender.as<ToggleSwitch>();
		if (senderElement.IsOn())
		{
			adlx_Res0 = pp3DAMDFluidMotionFrames->SetEnabled(true);
			if (ADLX_FAILED(adlx_Res0))
			{
				textblock_Status().Text(L"Failed enabling Fluid Motion Frames");
				AVDebugWriteLine(L"Failed enabling Fluid Motion Frames");
				disable_saving = true;
				senderElement.IsOn(false);
				disable_saving = false;
			}
			else
			{
				textblock_Status().Text(L"Fluid Motion Frames enabled");
				AVDebugWriteLine(L"Fluid Motion Frames enabled");
			}
		}
		else
		{
			adlx_Res0 = pp3DAMDFluidMotionFrames->SetEnabled(false);
			textblock_Status().Text(L"Fluid Motion Frames disabled");
			AVDebugWriteLine(L"Fluid Motion Frames disabled");
		}
	}

	void MainPage::toggleswitch_RadeonAntiLag_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Get settings
		IADLX3DAntiLagPtr pp3DAntiLag;
		adlx_Res0 = pp3DSettingsServices->GetAntiLag(ppGpuInfo, &pp3DAntiLag);

		if (sender.as<ToggleSwitch>().IsOn())
		{
			adlx_Res0 = pp3DAntiLag->SetEnabled(true);
			textblock_Status().Text(L"Anti-Lag enabled");
			AVDebugWriteLine(L"Anti-Lag enabled");
		}
		else
		{
			adlx_Res0 = pp3DAntiLag->SetEnabled(false);
			textblock_Status().Text(L"Anti-Lag disabled");
			AVDebugWriteLine(L"Anti-Lag disabled");
		}
	}

	void MainPage::toggleswitch_RadeonEnhancedSync_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Get enhanced sync settings
		IADLX3DEnhancedSyncPtr pp3DEnhancedSync;
		adlx_Res0 = pp3DSettingsServices->GetEnhancedSync(ppGpuInfo, &pp3DEnhancedSync);

		if (sender.as<ToggleSwitch>().IsOn())
		{
			adlx_Res0 = pp3DEnhancedSync->SetEnabled(true);
			textblock_Status().Text(L"Enhanced Sync enabled");
			AVDebugWriteLine(L"Enhanced Sync enabled");
		}
		else
		{
			adlx_Res0 = pp3DEnhancedSync->SetEnabled(false);
			textblock_Status().Text(L"Enhanced Sync disabled");
			AVDebugWriteLine(L"Enhanced Sync disabled");
		}
	}

	void MainPage::combobox_VerticalRefresh_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Get vertical refresh value
		auto newValue = sender.as<ComboBox>().SelectedIndex();

		//Set vertical refresh setting
		IADLX3DWaitForVerticalRefreshPtr pp3DWaitForVerticalRefresh;
		adlx_Res0 = pp3DSettingsServices->GetWaitForVerticalRefresh(ppGpuInfo, &pp3DWaitForVerticalRefresh);
		adlx_Res0 = pp3DWaitForVerticalRefresh->SetMode((ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE)newValue);
		if (ADLX_FAILED(adlx_Res0))
		{
			//Set result
			textblock_Status().Text(L"Failed setting vertical refresh");
			AVDebugWriteLine(L"Failed setting vertical refresh");
		}
		else
		{
			//Set result
			textblock_Status().Text(L"Vertical refresh set to " + number_to_wstring(newValue));
			AVDebugWriteLine(L"Vertical refresh set to " << newValue);
		}
	}

	void MainPage::toggleswitch_RadeonChill_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Get chill settings
		IADLX3DChillPtr pp3DChill;
		adlx_Res0 = pp3DSettingsServices->GetChill(ppGpuInfo, &pp3DChill);

		if (sender.as<ToggleSwitch>().IsOn())
		{
			adlx_Res0 = pp3DChill->SetEnabled(true);
			slider_RadeonChill_Min().IsEnabled(true);
			slider_RadeonChill_Max().IsEnabled(true);
			textblock_Status().Text(L"Radeon Chill enabled");
			AVDebugWriteLine(L"Radeon Chill enabled");
		}
		else
		{
			adlx_Res0 = pp3DChill->SetEnabled(false);
			slider_RadeonChill_Min().IsEnabled(false);
			slider_RadeonChill_Max().IsEnabled(false);
			textblock_Status().Text(L"Radeon Chill disabled");
			AVDebugWriteLine(L"Radeon Chill disabled");
		}
	}

	void MainPage::slider_RadeonChill_Min_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Convert new value
		int newValue = (int)e.NewValue();

		//Set chill settings
		IADLX3DChillPtr pp3DChill;
		adlx_Res0 = pp3DSettingsServices->GetChill(ppGpuInfo, &pp3DChill);
		adlx_Res0 = pp3DChill->SetMinFPS(newValue);
		if (ADLX_FAILED(adlx_Res0))
		{
			//Set result
			textblock_RadeonChill_Min().Foreground(SolidColorBrush(Windows::UI::Colors::Red()));
			textblock_Status().Text(L"Failed setting chill fps");
			AVDebugWriteLine(L"Failed setting chill fps");
		}
		else
		{
			//Match values
			if (newValue > slider_RadeonChill_Max().Value())
			{
				slider_RadeonChill_Max().Value(newValue);
			}

			//Set result
			textblock_RadeonChill_Min().Foreground(SolidColorBrush(Windows::UI::Colors::Green()));
			textblock_Status().Text(L"Chill minimum set to " + number_to_wstring(newValue));
			AVDebugWriteLine(L"Chill minimum set to " << newValue);
		}
	}

	void MainPage::slider_RadeonChill_Max_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Convert new value
		int newValue = (int)e.NewValue();

		//Set chill setting
		IADLX3DChillPtr pp3DChill;
		adlx_Res0 = pp3DSettingsServices->GetChill(ppGpuInfo, &pp3DChill);
		adlx_Res0 = pp3DChill->SetMaxFPS(newValue);
		if (ADLX_FAILED(adlx_Res0))
		{
			//Set result
			textblock_RadeonChill_Max().Foreground(SolidColorBrush(Windows::UI::Colors::Red()));
			textblock_Status().Text(L"Failed setting chill fps");
			AVDebugWriteLine(L"Failed setting chill fps");
		}
		else
		{
			//Match values
			if (newValue < slider_RadeonChill_Min().Value())
			{
				slider_RadeonChill_Min().Value(newValue);
			}

			//Set result
			textblock_RadeonChill_Max().Foreground(SolidColorBrush(Windows::UI::Colors::Green()));
			textblock_Status().Text(L"Chill maximum set to " + number_to_wstring(newValue));
			AVDebugWriteLine(L"Chill maximum set to " << newValue);
		}
	}

	void MainPage::toggleswitch_RadeonBoost_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Get settings
		IADLX3DBoostPtr pp3DBoost;
		adlx_Res0 = pp3DSettingsServices->GetBoost(ppGpuInfo, &pp3DBoost);

		if (sender.as<ToggleSwitch>().IsOn())
		{
			adlx_Res0 = pp3DBoost->SetEnabled(true);
			slider_RadeonBoost_MinRes().IsEnabled(true);
			textblock_Status().Text(L"Radeon Boost enabled");
			AVDebugWriteLine(L"Radeon Boost enabled");
		}
		else
		{
			adlx_Res0 = pp3DBoost->SetEnabled(false);
			slider_RadeonBoost_MinRes().IsEnabled(false);
			textblock_Status().Text(L"Radeon Boost disabled");
			AVDebugWriteLine(L"Radeon Boost disabled");
		}
	}

	void MainPage::slider_RadeonBoost_MinRes_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Convert new value
		int newValue = (int)e.NewValue();

		//Get settings
		IADLX3DBoostPtr pp3DBoost;
		adlx_Res0 = pp3DSettingsServices->GetBoost(ppGpuInfo, &pp3DBoost);
		adlx_Res0 = pp3DBoost->SetResolution(newValue);
		if (ADLX_FAILED(adlx_Res0))
		{
			//Set result
			textblock_RadeonBoost_MinRes().Foreground(SolidColorBrush(Windows::UI::Colors::Red()));
			textblock_Status().Text(L"Failed setting min. resolution");
			AVDebugWriteLine(L"Failed setting min. resolution");
		}
		else
		{
			//Set result
			textblock_RadeonBoost_MinRes().Foreground(SolidColorBrush(Windows::UI::Colors::Green()));
			textblock_Status().Text(L"Min. resolution set to " + number_to_wstring(newValue));
			AVDebugWriteLine(L"Min. resolution set to " << newValue);
		}
	}

	void MainPage::toggleswitch_RadeonImageSharpening_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Get setting
		IADLX3DImageSharpeningPtr pp3DImageSharpening;
		adlx_Res0 = pp3DSettingsServices->GetImageSharpening(ppGpuInfo, &pp3DImageSharpening);

		if (sender.as<ToggleSwitch>().IsOn())
		{
			adlx_Res0 = pp3DImageSharpening->SetEnabled(true);
			slider_RadeonImageSharpening_Sharpening().IsEnabled(true);
			textblock_Status().Text(L"Radeon Image Sharpening enabled");
			AVDebugWriteLine(L"Radeon Image Sharpening enabled");
		}
		else
		{
			adlx_Res0 = pp3DImageSharpening->SetEnabled(false);
			slider_RadeonImageSharpening_Sharpening().IsEnabled(false);
			textblock_Status().Text(L"Radeon Image Sharpening disabled");
			AVDebugWriteLine(L"Radeon Image Sharpening disabled");
		}
	}

	void MainPage::slider_RadeonImageSharpening_Sharpening_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Convert new value
		int newValue = (int)e.NewValue();

		//Get setting
		IADLX3DImageSharpeningPtr pp3DImageSharpening;
		adlx_Res0 = pp3DSettingsServices->GetImageSharpening(ppGpuInfo, &pp3DImageSharpening);

		adlx_Res0 = pp3DImageSharpening->SetSharpness(newValue);
		if (ADLX_FAILED(adlx_Res0))
		{
			//Set result
			textblock_RadeonImageSharpening_Sharpening().Foreground(SolidColorBrush(Windows::UI::Colors::Red()));
			textblock_Status().Text(L"Failed setting sharpening");
			AVDebugWriteLine(L"Failed setting sharpening");
		}
		else
		{
			//Set result
			textblock_RadeonImageSharpening_Sharpening().Foreground(SolidColorBrush(Windows::UI::Colors::Green()));
			textblock_Status().Text(L"Sharpening set to " + number_to_wstring(newValue));
			AVDebugWriteLine(L"Sharpening set to " << newValue);
		}
	}

	void MainPage::toggleswitch_Frtc_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Get setting
		IADLX3DFrameRateTargetControlPtr pp3DFrameRateTargetControl;
		adlx_Res0 = pp3DSettingsServices->GetFrameRateTargetControl(ppGpuInfo, &pp3DFrameRateTargetControl);

		if (sender.as<ToggleSwitch>().IsOn())
		{
			adlx_Res0 = pp3DFrameRateTargetControl->SetEnabled(true);
			slider_Frtc_Max().IsEnabled(true);
			textblock_Status().Text(L"FRTC enabled");
			AVDebugWriteLine(L"FRTC enabled");
		}
		else
		{
			adlx_Res0 = pp3DFrameRateTargetControl->SetEnabled(false);
			slider_Frtc_Max().IsEnabled(false);
			textblock_Status().Text(L"FRTC disabled");
			AVDebugWriteLine(L"FRTC disabled");
		}
	}

	void MainPage::slider_Frtc_Max_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Convert new value
		int newValue = (int)e.NewValue();

		//Get setting
		IADLX3DFrameRateTargetControlPtr pp3DFrameRateTargetControl;
		adlx_Res0 = pp3DSettingsServices->GetFrameRateTargetControl(ppGpuInfo, &pp3DFrameRateTargetControl);

		adlx_Res0 = pp3DFrameRateTargetControl->SetFPS(newValue);
		if (ADLX_FAILED(adlx_Res0))
		{
			//Set result
			textblock_Frtc_Max().Foreground(SolidColorBrush(Windows::UI::Colors::Red()));
			textblock_Status().Text(L"Failed setting FRTC");
			AVDebugWriteLine(L"Failed setting FRTC");
		}
		else
		{
			//Set result
			textblock_Frtc_Max().Foreground(SolidColorBrush(Windows::UI::Colors::Green()));
			textblock_Status().Text(L"FRTC set to " + number_to_wstring(newValue));
			AVDebugWriteLine(L"FRTC set to " << newValue);
		}
	}

	void MainPage::button_Reset_Shader_Cache_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Get setting
		IADLX3DResetShaderCachePtr pp3DResetShaderCache;
		adlx_Res0 = pp3DSettingsServices->GetResetShaderCache(ppGpuInfo, &pp3DResetShaderCache);

		//Reset shader cache
		adlx_Res0 = pp3DResetShaderCache->ResetShaderCache();

		//Set result
		if (ADLX_FAILED(adlx_Res0))
		{
			textblock_Status().Text(L"Failed resetting shader cache");
			AVDebugWriteLine(L"Failed resetting shader cache");
		}
		else
		{
			textblock_Status().Text(L"Shader cache is reset");
			AVDebugWriteLine(L"Shader cache is reset");
		}
	}
}