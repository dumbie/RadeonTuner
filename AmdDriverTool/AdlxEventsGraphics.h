#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::toggleswitch_RadeonSuperResolution_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get super resolution
			IADLX3DRadeonSuperResolutionPtr pp3DRadeonSuperResolution;
			adlx_Res0 = pp3DSettingsServices->GetRadeonSuperResolution(&pp3DRadeonSuperResolution);

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				adlx_Res0 = pp3DRadeonSuperResolution->SetEnabled(true);
				if (ADLX_FAILED(adlx_Res0))
				{
					textblock_Status().Text(L"Failed enabling Super Resolution");
					AVDebugWriteLine(L"Failed enabling Super Resolution");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					//Enable or disable interface
					slider_RadeonSuperResolution_Sharpening().IsEnabled(true);

					//Reload settings to get current value
					disable_saving = true;
					adlx_Res0 = pp3DRadeonSuperResolution->GetSharpness(&adlx_Int0);
					slider_RadeonSuperResolution_Sharpening().Value(adlx_Int0);
					disable_saving = false;

					textblock_Status().Text(L"Super Resolution enabled");
					AVDebugWriteLine(L"Super Resolution enabled");
				}
			}
			else
			{
				//Enable or disable interface
				slider_RadeonSuperResolution_Sharpening().IsEnabled(false);

				adlx_Res0 = pp3DRadeonSuperResolution->SetEnabled(false);
				textblock_Status().Text(L"Super Resolution disabled");
				AVDebugWriteLine(L"Super Resolution disabled");
			}
		}
		catch (...) {}
	}

	void MainPage::slider_RadeonSuperResolution_Sharpening_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
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
				textbox_RadeonSuperResolution_Sharpening().Foreground(SolidColorBrush(Windows::UI::Colors::Red()));
				textblock_Status().Text(L"Failed setting sharpening");
				AVDebugWriteLine(L"Failed setting sharpening");
			}
			else
			{
				//Set result
				textbox_RadeonSuperResolution_Sharpening().Foreground(SolidColorBrush(Windows::UI::Colors::Green()));
				textblock_Status().Text(L"Sharpening set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Sharpening set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_RadeonFluidMotionFrames_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
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
		catch (...) {}
	}

	void MainPage::toggleswitch_RadeonAntiLag_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get settings
			IADLX3DAntiLagPtr pp3DAntiLag;
			adlx_Res0 = pp3DSettingsServices->GetAntiLag(ppGpuInfo, &pp3DAntiLag);

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				adlx_Res0 = pp3DAntiLag->SetEnabled(true);
				if (ADLX_FAILED(adlx_Res0))
				{
					textblock_Status().Text(L"Failed enabling Anti-Lag");
					AVDebugWriteLine(L"Failed enabling Anti-Lag");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					textblock_Status().Text(L"Anti-Lag enabled");
					AVDebugWriteLine(L"Anti-Lag enabled");
				}
			}
			else
			{
				adlx_Res0 = pp3DAntiLag->SetEnabled(false);
				textblock_Status().Text(L"Anti-Lag disabled");
				AVDebugWriteLine(L"Anti-Lag disabled");
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_RadeonEnhancedSync_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get enhanced sync settings
			IADLX3DEnhancedSyncPtr pp3DEnhancedSync;
			adlx_Res0 = pp3DSettingsServices->GetEnhancedSync(ppGpuInfo, &pp3DEnhancedSync);

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				adlx_Res0 = pp3DEnhancedSync->SetEnabled(true);
				if (ADLX_FAILED(adlx_Res0))
				{
					textblock_Status().Text(L"Failed enabling Enhanced Sync");
					AVDebugWriteLine(L"Failed enabling Enhanced Sync");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					textblock_Status().Text(L"Enhanced Sync enabled");
					AVDebugWriteLine(L"Enhanced Sync enabled");
				}
			}
			else
			{
				adlx_Res0 = pp3DEnhancedSync->SetEnabled(false);
				textblock_Status().Text(L"Enhanced Sync disabled");
				AVDebugWriteLine(L"Enhanced Sync disabled");
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_VerticalRefresh_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Set setting
			IADLX3DWaitForVerticalRefreshPtr pp3DWaitForVerticalRefresh;
			adlx_Res0 = pp3DSettingsServices->GetWaitForVerticalRefresh(ppGpuInfo, &pp3DWaitForVerticalRefresh);

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();
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
		catch (...) {}
	}

	void MainPage::toggleswitch_RadeonChill_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get chill settings
			IADLX3DChillPtr pp3DChill;
			adlx_Res0 = pp3DSettingsServices->GetChill(ppGpuInfo, &pp3DChill);

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				adlx_Res0 = pp3DChill->SetEnabled(true);
				if (ADLX_FAILED(adlx_Res0))
				{
					textblock_Status().Text(L"Failed enabling Radeon Chill");
					AVDebugWriteLine(L"Failed enabling Radeon Chill");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					//Enable or disable interface
					slider_RadeonChill_Min().IsEnabled(true);
					slider_RadeonChill_Max().IsEnabled(true);

					//Reload settings to get current value
					disable_saving = true;
					adlx_Res0 = pp3DChill->GetMinFPS(&adlx_Int0);
					adlx_Res0 = pp3DChill->GetMaxFPS(&adlx_Int1);
					slider_RadeonChill_Min().Value(adlx_Int0);
					slider_RadeonChill_Max().Value(adlx_Int1);
					disable_saving = false;

					textblock_Status().Text(L"Radeon Chill enabled");
					AVDebugWriteLine(L"Radeon Chill enabled");
				}
			}
			else
			{
				//Enable or disable interface
				slider_RadeonChill_Min().IsEnabled(false);
				slider_RadeonChill_Max().IsEnabled(false);

				adlx_Res0 = pp3DChill->SetEnabled(false);
				textblock_Status().Text(L"Radeon Chill disabled");
				AVDebugWriteLine(L"Radeon Chill disabled");
			}
		}
		catch (...) {}
	}

	void MainPage::slider_RadeonChill_Min_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
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
				textbox_RadeonChill_Min().Foreground(SolidColorBrush(Windows::UI::Colors::Red()));
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
				textbox_RadeonChill_Min().Foreground(SolidColorBrush(Windows::UI::Colors::Green()));
				textblock_Status().Text(L"Chill minimum set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Chill minimum set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::slider_RadeonChill_Max_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
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
				textbox_RadeonChill_Max().Foreground(SolidColorBrush(Windows::UI::Colors::Red()));
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
				textbox_RadeonChill_Max().Foreground(SolidColorBrush(Windows::UI::Colors::Green()));
				textblock_Status().Text(L"Chill maximum set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Chill maximum set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_RadeonBoost_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get settings
			IADLX3DBoostPtr pp3DBoost;
			adlx_Res0 = pp3DSettingsServices->GetBoost(ppGpuInfo, &pp3DBoost);

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				adlx_Res0 = pp3DBoost->SetEnabled(true);
				if (ADLX_FAILED(adlx_Res0))
				{
					textblock_Status().Text(L"Failed enabling Radeon Boost");
					AVDebugWriteLine(L"Failed enabling Radeon Boost");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					//Enable or disable interface
					slider_RadeonBoost_MinRes().IsEnabled(true);

					//Reload settings to get current value
					disable_saving = true;
					adlx_Res0 = pp3DBoost->GetResolution(&adlx_Int0);
					slider_RadeonBoost_MinRes().Value(adlx_Int0);
					disable_saving = false;

					textblock_Status().Text(L"Radeon Boost enabled");
					AVDebugWriteLine(L"Radeon Boost enabled");
				}
			}
			else
			{
				//Enable or disable interface
				slider_RadeonBoost_MinRes().IsEnabled(false);

				adlx_Res0 = pp3DBoost->SetEnabled(false);
				textblock_Status().Text(L"Radeon Boost disabled");
				AVDebugWriteLine(L"Radeon Boost disabled");
			}
		}
		catch (...) {}
	}

	void MainPage::slider_RadeonBoost_MinRes_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
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
				textbox_RadeonBoost_MinRes().Foreground(SolidColorBrush(Windows::UI::Colors::Red()));
				textblock_Status().Text(L"Failed setting min. resolution");
				AVDebugWriteLine(L"Failed setting min. resolution");
			}
			else
			{
				//Set result
				textbox_RadeonBoost_MinRes().Foreground(SolidColorBrush(Windows::UI::Colors::Green()));
				textblock_Status().Text(L"Min. resolution set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Min. resolution set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_RadeonImageSharpening_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting
			IADLX3DImageSharpeningPtr pp3DImageSharpening;
			adlx_Res0 = pp3DSettingsServices->GetImageSharpening(ppGpuInfo, &pp3DImageSharpening);

			IADLX3DImageSharpenDesktopPtr pp3DImageSharpenDesktop;
			adlx_Res0 = pp3DSettingsServices->GetImageSharpenDesktop(ppGpuInfo, &pp3DImageSharpenDesktop);

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				adlx_Res0 = pp3DImageSharpening->SetEnabled(true);
				if (ADLX_FAILED(adlx_Res0))
				{
					textblock_Status().Text(L"Failed enabling Image Sharpening");
					AVDebugWriteLine(L"Failed enabling Image Sharpening");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					//Enable or disable interface
					adlx_Res0 = pp3DImageSharpenDesktop->IsSupported(&adlx_Bool);
					if (adlx_Bool)
					{
						toggleswitch_RadeonSharpenDesktop().IsEnabled(true);
					}
					slider_RadeonImageSharpening_Sharpening().IsEnabled(true);

					//Reload settings to get current value
					disable_saving = true;
					adlx_Res0 = pp3DImageSharpening->GetSharpness(&adlx_Int0);
					slider_RadeonImageSharpening_Sharpening().Value(adlx_Int0);
					disable_saving = false;

					textblock_Status().Text(L"Image Sharpening enabled");
					AVDebugWriteLine(L"Image Sharpening enabled");
				}
			}
			else
			{
				//Enable or disable interface
				toggleswitch_RadeonSharpenDesktop().IsEnabled(false);
				slider_RadeonImageSharpening_Sharpening().IsEnabled(false);

				adlx_Res0 = pp3DImageSharpening->SetEnabled(false);
				textblock_Status().Text(L"Image Sharpening disabled");
				AVDebugWriteLine(L"Image Sharpening disabled");
			}
		}
		catch (...) {}
	}

	void MainPage::slider_RadeonImageSharpening_Sharpening_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
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
				textbox_RadeonImageSharpening_Sharpening().Foreground(SolidColorBrush(Windows::UI::Colors::Red()));
				textblock_Status().Text(L"Failed setting sharpening");
				AVDebugWriteLine(L"Failed setting sharpening");
			}
			else
			{
				//Set result
				textbox_RadeonImageSharpening_Sharpening().Foreground(SolidColorBrush(Windows::UI::Colors::Green()));
				textblock_Status().Text(L"Sharpening set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Sharpening set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_RadeonSharpenDesktop_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting
			IADLX3DImageSharpenDesktopPtr pp3DImageSharpenDesktop;
			adlx_Res0 = pp3DSettingsServices->GetImageSharpenDesktop(ppGpuInfo, &pp3DImageSharpenDesktop);

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				adlx_Res0 = pp3DImageSharpenDesktop->SetEnabled(true);
				if (ADLX_FAILED(adlx_Res0))
				{
					textblock_Status().Text(L"Failed enabling Desktop Sharpening");
					AVDebugWriteLine(L"Failed enabling Desktop Sharpening");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					textblock_Status().Text(L"Desktop Sharpening enabled");
					AVDebugWriteLine(L"Desktop Sharpening enabled");
				}
			}
			else
			{
				adlx_Res0 = pp3DImageSharpenDesktop->SetEnabled(false);
				textblock_Status().Text(L"Desktop Sharpening disabled");
				AVDebugWriteLine(L"Desktop Sharpening disabled");
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_Frtc_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting
			IADLX3DFrameRateTargetControlPtr pp3DFrameRateTargetControl;
			adlx_Res0 = pp3DSettingsServices->GetFrameRateTargetControl(ppGpuInfo, &pp3DFrameRateTargetControl);

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				adlx_Res0 = pp3DFrameRateTargetControl->SetEnabled(true);
				if (ADLX_FAILED(adlx_Res0))
				{
					textblock_Status().Text(L"Failed enabling FRTC");
					AVDebugWriteLine(L"Failed enabling FRTC");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					//Enable or disable interface
					slider_Frtc_Max().IsEnabled(true);

					//Reload settings to get current value
					disable_saving = true;
					adlx_Res0 = pp3DFrameRateTargetControl->GetFPS(&adlx_Int0);
					slider_Frtc_Max().Value(adlx_Int0);
					disable_saving = false;

					textblock_Status().Text(L"FRTC enabled");
					AVDebugWriteLine(L"FRTC enabled");
				}
			}
			else
			{
				//Enable or disable interface
				slider_Frtc_Max().IsEnabled(false);

				adlx_Res0 = pp3DFrameRateTargetControl->SetEnabled(false);
				textblock_Status().Text(L"FRTC disabled");
				AVDebugWriteLine(L"FRTC disabled");
			}
		}
		catch (...) {}
	}

	void MainPage::slider_Frtc_Max_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
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
				textbox_Frtc_Max().Foreground(SolidColorBrush(Windows::UI::Colors::Red()));
				textblock_Status().Text(L"Failed setting FRTC");
				AVDebugWriteLine(L"Failed setting FRTC");
			}
			else
			{
				//Set result
				textbox_Frtc_Max().Foreground(SolidColorBrush(Windows::UI::Colors::Green()));
				textblock_Status().Text(L"FRTC set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"FRTC set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_AntiAliasingMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting
			IADLX3DAntiAliasingPtr pp3DAntiAliasing;
			adlx_Res0 = pp3DSettingsServices->GetAntiAliasing(ppGpuInfo, &pp3DAntiAliasing);

			//Get setting value
			ADLX_ANTI_ALIASING_MODE newValue = (ADLX_ANTI_ALIASING_MODE)sender.as<ComboBox>().SelectedIndex();
			adlx_Res0 = pp3DAntiAliasing->SetMode(newValue);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				textblock_Status().Text(L"Failed setting AA mode");
				AVDebugWriteLine(L"Failed setting AA mode");
			}
			else
			{
				//Enable or disable interface
				if (newValue != ADLX_ANTI_ALIASING_MODE::AA_MODE_OVERRIDE_APP_SETTINGS)
				{
					combobox_AntiAliasingLevel().IsEnabled(false);
				}
				else
				{
					combobox_AntiAliasingLevel().IsEnabled(true);

					//Reload settings to get current value
					disable_saving = true;
					ADLX_ANTI_ALIASING_LEVEL currentLevel;
					adlx_Res0 = pp3DAntiAliasing->GetLevel(&currentLevel);
					if (currentLevel == ADLX_ANTI_ALIASING_LEVEL::AA_LEVEL_2X)
					{
						combobox_AntiAliasingLevel().SelectedIndex(0);
					}
					else if (currentLevel == ADLX_ANTI_ALIASING_LEVEL::AA_LEVEL_2XEQ)
					{
						combobox_AntiAliasingLevel().SelectedIndex(1);
					}
					else if (currentLevel == ADLX_ANTI_ALIASING_LEVEL::AA_LEVEL_4X)
					{
						combobox_AntiAliasingLevel().SelectedIndex(2);
					}
					else if (currentLevel == ADLX_ANTI_ALIASING_LEVEL::AA_LEVEL_4XEQ)
					{
						combobox_AntiAliasingLevel().SelectedIndex(3);
					}
					else if (currentLevel == ADLX_ANTI_ALIASING_LEVEL::AA_LEVEL_8X)
					{
						combobox_AntiAliasingLevel().SelectedIndex(4);
					}
					else if (currentLevel == ADLX_ANTI_ALIASING_LEVEL::AA_LEVEL_8XEQ)
					{
						combobox_AntiAliasingLevel().SelectedIndex(5);
					}
					disable_saving = false;
				}

				//Set result
				textblock_Status().Text(L"AA mode set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"AA mode set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_AntiAliasingMethod_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting
			IADLX3DAntiAliasingPtr pp3DAntiAliasing;
			adlx_Res0 = pp3DSettingsServices->GetAntiAliasing(ppGpuInfo, &pp3DAntiAliasing);

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();
			adlx_Res0 = pp3DAntiAliasing->SetMethod((ADLX_ANTI_ALIASING_METHOD)newValue);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				textblock_Status().Text(L"Failed setting AA method");
				AVDebugWriteLine(L"Failed setting AA method");
			}
			else
			{
				//Set result
				textblock_Status().Text(L"AA method set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"AA method set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_AntiAliasingLevel_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting
			IADLX3DAntiAliasingPtr pp3DAntiAliasing;
			adlx_Res0 = pp3DSettingsServices->GetAntiAliasing(ppGpuInfo, &pp3DAntiAliasing);

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();

			//Enumeration index correction
			if (newValue == 0)
			{
				newValue = 2;
			}
			else if (newValue == 1)
			{
				newValue = 3;
			}
			else if (newValue == 2)
			{
				newValue = 4;
			}
			else if (newValue == 3)
			{
				newValue = 5;
			}
			else if (newValue == 4)
			{
				newValue = 8;
			}
			else if (newValue == 5)
			{
				newValue = 9;
			}

			adlx_Res0 = pp3DAntiAliasing->SetLevel((ADLX_ANTI_ALIASING_LEVEL)newValue);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				textblock_Status().Text(L"Failed setting AA level");
				AVDebugWriteLine(L"Failed setting AA level");
			}
			else
			{
				//Set result
				textblock_Status().Text(L"AA level set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"AA level set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_MorphologicAntiAliasing_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting
			IADLX3DMorphologicalAntiAliasingPtr pp3DMorphologicalAntiAliasing;
			adlx_Res0 = pp3DSettingsServices->GetMorphologicalAntiAliasing(ppGpuInfo, &pp3DMorphologicalAntiAliasing);

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				adlx_Res0 = pp3DMorphologicalAntiAliasing->SetEnabled(true);
				if (ADLX_FAILED(adlx_Res0))
				{
					textblock_Status().Text(L"Failed enabling Morphological AA");
					AVDebugWriteLine(L"Failed enabling Morphological AA");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					textblock_Status().Text(L"Morphological AA enabled");
					AVDebugWriteLine(L"Morphological AA enabled");
				}
			}
			else
			{
				adlx_Res0 = pp3DMorphologicalAntiAliasing->SetEnabled(false);
				textblock_Status().Text(L"Morphological AA disabled");
				AVDebugWriteLine(L"Morphological AA disabled");
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_AnisotropicTextureFiltering_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting
			IADLX3DAnisotropicFilteringPtr pp3DAnisotropicFiltering;
			adlx_Res0 = pp3DSettingsServices->GetAnisotropicFiltering(ppGpuInfo, &pp3DAnisotropicFiltering);

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				adlx_Res0 = pp3DAnisotropicFiltering->SetEnabled(true);
				if (ADLX_FAILED(adlx_Res0))
				{
					textblock_Status().Text(L"Failed enabling Anisotropic");
					AVDebugWriteLine(L"Failed enabling Anisotropic");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					//Enable or disable interface
					combobox_AnisotropicTextureFilteringQuality().IsEnabled(true);

					//Reload settings to get current value
					disable_saving = true;
					ADLX_ANISOTROPIC_FILTERING_LEVEL currentLevel;
					adlx_Res0 = pp3DAnisotropicFiltering->GetLevel(&currentLevel);
					if (currentLevel == ADLX_ANISOTROPIC_FILTERING_LEVEL::AF_LEVEL_X2)
					{
						combobox_AnisotropicTextureFilteringQuality().SelectedIndex(0);
					}
					else if (currentLevel == ADLX_ANISOTROPIC_FILTERING_LEVEL::AF_LEVEL_X4)
					{
						combobox_AnisotropicTextureFilteringQuality().SelectedIndex(1);
					}
					else if (currentLevel == ADLX_ANISOTROPIC_FILTERING_LEVEL::AF_LEVEL_X8)
					{
						combobox_AnisotropicTextureFilteringQuality().SelectedIndex(2);
					}
					else if (currentLevel == ADLX_ANISOTROPIC_FILTERING_LEVEL::AF_LEVEL_X16)
					{
						combobox_AnisotropicTextureFilteringQuality().SelectedIndex(3);
					}
					disable_saving = false;

					textblock_Status().Text(L"Anisotropic enabled");
					AVDebugWriteLine(L"Anisotropic enabled");
				}
			}
			else
			{
				//Enable or disable interface
				combobox_AnisotropicTextureFilteringQuality().IsEnabled(false);

				adlx_Res0 = pp3DAnisotropicFiltering->SetEnabled(false);
				textblock_Status().Text(L"Anisotropic disabled");
				AVDebugWriteLine(L"Anisotropic disabled");
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_AnisotropicTextureFilteringQuality_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting
			IADLX3DAnisotropicFilteringPtr pp3DAnisotropicFiltering;
			adlx_Res0 = pp3DSettingsServices->GetAnisotropicFiltering(ppGpuInfo, &pp3DAnisotropicFiltering);

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();

			//Enumeration index correction
			if (newValue == 0)
			{
				newValue = 2;
			}
			else if (newValue == 1)
			{
				newValue = 4;
			}
			else if (newValue == 2)
			{
				newValue = 8;
			}
			else if (newValue == 3)
			{
				newValue = 16;
			}

			adlx_Res0 = pp3DAnisotropicFiltering->SetLevel((ADLX_ANISOTROPIC_FILTERING_LEVEL)newValue);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				textblock_Status().Text(L"Failed setting Anisotropic level");
				AVDebugWriteLine(L"Failed setting Anisotropic level");
			}
			else
			{
				//Set result
				textblock_Status().Text(L"Anisotropic level set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Anisotropic level set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_Tessellation_Mode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting
			IADLX3DTessellationPtr pp3DTessellation;
			adlx_Res0 = pp3DSettingsServices->GetTessellation(ppGpuInfo, &pp3DTessellation);

			//Get setting value
			ADLX_TESSELLATION_MODE newValue = (ADLX_TESSELLATION_MODE)sender.as<ComboBox>().SelectedIndex();
			adlx_Res0 = pp3DTessellation->SetMode(newValue);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				textblock_Status().Text(L"Failed setting Tessellation mode");
				AVDebugWriteLine(L"Failed setting Tessellation mode");
			}
			else
			{
				//Enable or disable interface
				if (newValue != ADLX_TESSELLATION_MODE::T_MODE_OVERRIDE_APP_SETTINGS)
				{
					combobox_Tessellation_Level().IsEnabled(false);
				}
				else
				{
					combobox_Tessellation_Level().IsEnabled(true);

					//Reload settings to get current value
					disable_saving = true;
					ADLX_TESSELLATION_LEVEL currentLevel;
					adlx_Res0 = pp3DTessellation->GetLevel(&currentLevel);
					if (currentLevel == ADLX_TESSELLATION_LEVEL::T_LEVEL_OFF)
					{
						combobox_Tessellation_Level().SelectedIndex(0);
					}
					else if (currentLevel == ADLX_TESSELLATION_LEVEL::T_LEVEL_2X)
					{
						combobox_Tessellation_Level().SelectedIndex(1);
					}
					else if (currentLevel == ADLX_TESSELLATION_LEVEL::T_LEVEL_4X)
					{
						combobox_Tessellation_Level().SelectedIndex(2);
					}
					else if (currentLevel == ADLX_TESSELLATION_LEVEL::T_LEVEL_6X)
					{
						combobox_Tessellation_Level().SelectedIndex(3);
					}
					else if (currentLevel == ADLX_TESSELLATION_LEVEL::T_LEVEL_8X)
					{
						combobox_Tessellation_Level().SelectedIndex(4);
					}
					else if (currentLevel == ADLX_TESSELLATION_LEVEL::T_LEVEL_16X)
					{
						combobox_Tessellation_Level().SelectedIndex(5);
					}
					else if (currentLevel == ADLX_TESSELLATION_LEVEL::T_LEVEL_32X)
					{
						combobox_Tessellation_Level().SelectedIndex(6);
					}
					else if (currentLevel == ADLX_TESSELLATION_LEVEL::T_LEVEL_64X)
					{
						combobox_Tessellation_Level().SelectedIndex(7);
					}
					disable_saving = false;
				}

				//Set result
				textblock_Status().Text(L"Tessellation mode set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Tessellation mode set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_Tessellation_Level_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting
			IADLX3DTessellationPtr pp3DTessellation;
			adlx_Res0 = pp3DSettingsServices->GetTessellation(ppGpuInfo, &pp3DTessellation);

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();

			//Enumeration index correction
			if (newValue == 0)
			{
				newValue = 1;
			}
			else if (newValue == 1)
			{
				newValue = 2;
			}
			else if (newValue == 2)
			{
				newValue = 4;
			}
			else if (newValue == 3)
			{
				newValue = 6;
			}
			else if (newValue == 4)
			{
				newValue = 8;
			}
			else if (newValue == 5)
			{
				newValue = 16;
			}
			else if (newValue == 6)
			{
				newValue = 32;
			}
			else if (newValue == 7)
			{
				newValue = 64;
			}

			adlx_Res0 = pp3DTessellation->SetLevel((ADLX_TESSELLATION_LEVEL)newValue);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				textblock_Status().Text(L"Failed setting Tessellation level");
				AVDebugWriteLine(L"Failed setting Tessellation level");
			}
			else
			{
				//Set result
				textblock_Status().Text(L"Tessellation level set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Tessellation level set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::button_Reset_Shader_Cache_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
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
		catch (...)
		{
			textblock_Status().Text(L"Failed resetting shader cache");
			AVDebugWriteLine(L"Failed resetting shader cache");
		}
	}
}