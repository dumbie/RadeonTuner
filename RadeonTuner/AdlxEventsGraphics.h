#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::button_Graphics_AddExe_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Show file dialog
			bool addResult = AdlInterfaceAppsAddDialog();

			//Check result
			if (addResult)
			{
				//Fix Show notification

				//Reload applications
				AdlInterfaceAppsList();
			}
		}
		catch (...) {}
	}

	void MainPage::button_Graphics_Remove_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Remove application and profile
			bool removeResult = AdlAppsRemove(adl_AppSelected());

			//Check result
			if (removeResult)
			{
				//Fix Show notification

				//Reload applications
				AdlInterfaceAppsList();
			}
		}
		catch (...) {}
	}

	void MainPage::button_Graphics_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			if (adl_AppSelected().Initialized())
			{
				//Fix add code to reset settings
			}
			else
			{
				//Fix add code to reset settings
			}
		}
		catch (...) {}
	}

	void MainPage::button_Graphics_Import_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Import settings from file
			AdlxValuesImportGraphics();
		}
		catch (...) {}
	}

	void MainPage::button_Graphics_Export_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Export current settings to file
			AdlxValuesExportGraphics();
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_RadeonSuperResolution_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"???", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				IADLX3DRadeonSuperResolutionPtr pp3DRadeonSuperResolution;
				adlx_Res0 = pp3DSettingsServices->GetRadeonSuperResolution(&pp3DRadeonSuperResolution);
				adlx_Res0 = pp3DRadeonSuperResolution->SetEnabled(newValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling Super Resolution");
					AVDebugWriteLine(L"Failed enabling Super Resolution");
				}
				else
				{
					ShowNotification(L"Failed disabling Super Resolution");
					AVDebugWriteLine(L"Failed disabling Super Resolution");
				}
			}
			else
			{
				if (newValue)
				{
					slider_RadeonSuperResolution_Sharpening().IsEnabled(true);
					ShowNotification(L"Super Resolution enabled");
					AVDebugWriteLine(L"Super Resolution enabled");
				}
				else
				{
					slider_RadeonSuperResolution_Sharpening().IsEnabled(false);
					ShowNotification(L"Super Resolution disabled");
					AVDebugWriteLine(L"Super Resolution disabled");
				}
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

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"???", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				IADLX3DRadeonSuperResolutionPtr pp3DRadeonSuperResolution;
				adlx_Res0 = pp3DSettingsServices->GetRadeonSuperResolution(&pp3DRadeonSuperResolution);
				adlx_Res0 = pp3DRadeonSuperResolution->SetSharpness(newValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_RadeonSuperResolution_Sharpening().Foreground(colorInvalid);
				ShowNotification(L"Failed setting Sharpening");
				AVDebugWriteLine(L"Failed setting Sharpening");
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_RadeonSuperResolution_Sharpening().Foreground(colorValid);
				ShowNotification(L"Sharpening set to " + number_to_wstring(newValue));
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

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"???", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				IADLX3DAMDFluidMotionFramesPtr pp3DAMDFluidMotionFrames;
				adlx_Res0 = pp3DSettingsServices->GetAMDFluidMotionFrames(&pp3DAMDFluidMotionFrames);
				adlx_Res0 = pp3DAMDFluidMotionFrames->SetEnabled(newValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling Fluid Motion Frames");
					AVDebugWriteLine(L"Failed enabling Fluid Motion Frames");
				}
				else
				{
					ShowNotification(L"Failed disabling Fluid Motion Frames");
					AVDebugWriteLine(L"Failed disabling Fluid Motion Frames");
				}
			}
			else
			{
				if (newValue)
				{
					combobox_FrameGenSearchMode().IsEnabled(true);
					combobox_FrameGenPerfMode().IsEnabled(true);
					combobox_FrameGenResponseMode().IsEnabled(true);
					ShowNotification(L"Fluid Motion Frames enabled");
					AVDebugWriteLine(L"Fluid Motion Frames enabled");
				}
				else
				{
					combobox_FrameGenSearchMode().IsEnabled(false);
					combobox_FrameGenPerfMode().IsEnabled(false);
					combobox_FrameGenResponseMode().IsEnabled(false);
					ShowNotification(L"Fluid Motion Frames disabled");
					AVDebugWriteLine(L"Fluid Motion Frames disabled");
				}
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

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"Dlg_PFEnable", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				IADLX3DAntiLagPtr pp3DAntiLag;
				adlx_Res0 = pp3DSettingsServices->GetAntiLag(ppGpuInfo, &pp3DAntiLag);
				adlx_Res0 = pp3DAntiLag->SetEnabled(newValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling Anti-Lag");
					AVDebugWriteLine(L"Failed enabling Anti-Lag");
				}
				else
				{
					ShowNotification(L"Failed disabling Anti-Lag");
					AVDebugWriteLine(L"Failed disabling Anti-Lag");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"Anti-Lag enabled");
					AVDebugWriteLine(L"Anti-Lag enabled");
				}
				else
				{
					ShowNotification(L"Anti-Lag disabled");
					AVDebugWriteLine(L"Anti-Lag disabled");
				}
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

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"TurboSync", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				IADLX3DEnhancedSyncPtr pp3DEnhancedSync;
				adlx_Res0 = pp3DSettingsServices->GetEnhancedSync(ppGpuInfo, &pp3DEnhancedSync);
				adlx_Res0 = pp3DEnhancedSync->SetEnabled(newValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling Enhanced Sync");
					AVDebugWriteLine(L"Failed enabling Enhanced Sync");
				}
				else
				{
					ShowNotification(L"Failed disabling Enhanced Sync");
					AVDebugWriteLine(L"Failed disabling Enhanced Sync");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"Enhanced Sync enabled");
					AVDebugWriteLine(L"Enhanced Sync enabled");
				}
				else
				{
					ShowNotification(L"Enhanced Sync disabled");
					AVDebugWriteLine(L"Enhanced Sync disabled");
				}
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

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"VSyncControl", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				IADLX3DWaitForVerticalRefreshPtr pp3DWaitForVerticalRefresh;
				adlx_Res0 = pp3DSettingsServices->GetWaitForVerticalRefresh(ppGpuInfo, &pp3DWaitForVerticalRefresh);
				adlx_Res0 = pp3DWaitForVerticalRefresh->SetMode((ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE)newValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting Vertical refresh");
				AVDebugWriteLine(L"Failed setting Vertical refresh");
			}
			else
			{
				ShowNotification(L"Vertical refresh set to " + ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE_STRING[newValue]);
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

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"Chil_PFEnable", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				IADLX3DChillPtr pp3DChill;
				adlx_Res0 = pp3DSettingsServices->GetChill(ppGpuInfo, &pp3DChill);
				adlx_Res0 = pp3DChill->SetEnabled(newValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling Radeon Chill");
					AVDebugWriteLine(L"Failed enabling Radeon Chill");
				}
				else
				{
					ShowNotification(L"Failed disabling Radeon Chill");
					AVDebugWriteLine(L"Failed disabling Radeon Chill");
				}
			}
			else
			{
				if (newValue)
				{
					slider_RadeonChill_Min().IsEnabled(true);
					slider_RadeonChill_Max().IsEnabled(true);
					ShowNotification(L"Radeon Chill enabled");
					AVDebugWriteLine(L"Radeon Chill enabled");
				}
				else
				{
					slider_RadeonChill_Min().IsEnabled(false);
					slider_RadeonChill_Max().IsEnabled(false);
					ShowNotification(L"Radeon Chill disabled");
					AVDebugWriteLine(L"Radeon Chill disabled");
				}
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

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"Chil_MinFRate", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				IADLX3DChillPtr pp3DChill;
				adlx_Res0 = pp3DSettingsServices->GetChill(ppGpuInfo, &pp3DChill);
				adlx_Res0 = pp3DChill->SetMinFPS(newValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_RadeonChill_Min().Foreground(colorInvalid);
				ShowNotification(L"Failed setting Chill minimum fps");
				AVDebugWriteLine(L"Failed setting Chill minimum fps");
			}
			else
			{
				//Match values
				if (newValue > slider_RadeonChill_Max().Value())
				{
					slider_RadeonChill_Max().Value(newValue);
				}

				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_RadeonChill_Min().Foreground(colorValid);
				ShowNotification(L"Chill minimum fps set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Chill minimum fps set to " << newValue);
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

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"Chil_MaxFRate", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				IADLX3DChillPtr pp3DChill;
				adlx_Res0 = pp3DSettingsServices->GetChill(ppGpuInfo, &pp3DChill);
				adlx_Res0 = pp3DChill->SetMaxFPS(newValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_RadeonChill_Max().Foreground(colorInvalid);
				ShowNotification(L"Failed setting Chill maximum fps");
				AVDebugWriteLine(L"Failed setting Chill maximum fps");
			}
			else
			{
				//Match values
				if (newValue < slider_RadeonChill_Min().Value())
				{
					slider_RadeonChill_Min().Value(newValue);
				}

				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_RadeonChill_Max().Foreground(colorValid);
				ShowNotification(L"Chill maximum fps set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Chill maximum fps set to " << newValue);
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

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"Bst_PFEnable", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				IADLX3DBoostPtr pp3DBoost;
				adlx_Res0 = pp3DSettingsServices->GetBoost(ppGpuInfo, &pp3DBoost);
				adlx_Res0 = pp3DBoost->SetEnabled(newValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling Radeon Boost");
					AVDebugWriteLine(L"Failed enabling Radeon Boost");
				}
				else
				{
					ShowNotification(L"Failed disabling Radeon Boost");
					AVDebugWriteLine(L"Failed disabling Radeon Boost");
				}
			}
			else
			{
				if (newValue)
				{
					slider_RadeonBoost_MinRes().IsEnabled(true);
					ShowNotification(L"Radeon Boost enabled");
					AVDebugWriteLine(L"Radeon Boost enabled");
				}
				else
				{
					slider_RadeonBoost_MinRes().IsEnabled(false);
					ShowNotification(L"Radeon Boost disabled");
					AVDebugWriteLine(L"Radeon Boost disabled");
				}
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

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"Bst_MaxScale", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				IADLX3DBoostPtr pp3DBoost;
				adlx_Res0 = pp3DSettingsServices->GetBoost(ppGpuInfo, &pp3DBoost);
				adlx_Res0 = pp3DBoost->SetResolution(newValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_RadeonBoost_MinRes().Foreground(colorInvalid);
				ShowNotification(L"Failed setting Minimum resolution");
				AVDebugWriteLine(L"Failed setting Minimum resolution");
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_RadeonBoost_MinRes().Foreground(colorValid);
				ShowNotification(L"Minimum resolution set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Minimum resolution set to " << newValue);
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

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"Ris_PFEnable", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				IADLX3DImageSharpeningPtr pp3DImageSharpening;
				adlx_Res0 = pp3DSettingsServices->GetImageSharpening(ppGpuInfo, &pp3DImageSharpening);
				adlx_Res0 = pp3DImageSharpening->SetEnabled(newValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling Image Sharpening");
					AVDebugWriteLine(L"Failed enabling Image Sharpening");
				}
				else
				{
					ShowNotification(L"Failed disabling Image Sharpening");
					AVDebugWriteLine(L"Failed disabling Image Sharpening");
				}
			}
			else
			{
				if (newValue)
				{
					if (!adl_AppSelected().Initialized())
					{
						IADLX3DImageSharpenDesktopPtr pp3DImageSharpenDesktop;
						adlx_Res0 = pp3DSettingsServices->GetImageSharpenDesktop(ppGpuInfo, &pp3DImageSharpenDesktop);
						adlx_Res0 = pp3DImageSharpenDesktop->IsSupported(&adlx_Bool);
						if (ADLX_SUCCEEDED(adlx_Res0) && adlx_Bool)
						{
							toggleswitch_RadeonSharpenDesktop().IsEnabled(true);
						}
					}
					slider_RadeonImageSharpening_Sharpening().IsEnabled(true);
					ShowNotification(L"Image Sharpening enabled");
					AVDebugWriteLine(L"Image Sharpening enabled");
				}
				else
				{
					toggleswitch_RadeonSharpenDesktop().IsEnabled(false);
					slider_RadeonImageSharpening_Sharpening().IsEnabled(false);
					ShowNotification(L"Image Sharpening disabled");
					AVDebugWriteLine(L"Image Sharpening disabled");
				}
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

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				float convertedValue = (float)newValue / 100;
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"Ris_SHDegree", float_to_wstring(convertedValue, 1), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				IADLX3DImageSharpeningPtr pp3DImageSharpening;
				adlx_Res0 = pp3DSettingsServices->GetImageSharpening(ppGpuInfo, &pp3DImageSharpening);
				adlx_Res0 = pp3DImageSharpening->SetSharpness(newValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_RadeonImageSharpening_Sharpening().Foreground(colorInvalid);
				ShowNotification(L"Failed setting Sharpening");
				AVDebugWriteLine(L"Failed setting Sharpening");
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_RadeonImageSharpening_Sharpening().Foreground(colorValid);
				ShowNotification(L"Sharpening set to " + number_to_wstring(newValue));
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

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"???", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				IADLX3DImageSharpenDesktopPtr pp3DImageSharpenDesktop;
				adlx_Res0 = pp3DSettingsServices->GetImageSharpenDesktop(ppGpuInfo, &pp3DImageSharpenDesktop);
				adlx_Res0 = pp3DImageSharpenDesktop->SetEnabled(newValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling Desktop Sharpening");
					AVDebugWriteLine(L"Failed enabling Desktop Sharpening");
				}
				else
				{
					ShowNotification(L"Failed disabling Desktop Sharpening");
					AVDebugWriteLine(L"Failed disabling Desktop Sharpening");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"Desktop Sharpening enabled");
					AVDebugWriteLine(L"Desktop Sharpening enabled");
				}
				else
				{
					ShowNotification(L"Desktop Sharpening disabled");
					AVDebugWriteLine(L"Desktop Sharpening disabled");
				}
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

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"???", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				IADLX3DFrameRateTargetControlPtr pp3DFrameRateTargetControl;
				adlx_Res0 = pp3DSettingsServices->GetFrameRateTargetControl(ppGpuInfo, &pp3DFrameRateTargetControl);
				adlx_Res0 = pp3DFrameRateTargetControl->SetEnabled(newValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling FRTC");
					AVDebugWriteLine(L"Failed enabling FRTC");
				}
				else
				{
					ShowNotification(L"Failed disabling FRTC");
					AVDebugWriteLine(L"Failed disabling FRTC");
				}
			}
			else
			{
				if (newValue)
				{
					slider_Frtc_Fps().IsEnabled(true);
					ShowNotification(L"FRTC enabled");
					AVDebugWriteLine(L"FRTC enabled");
				}
				else
				{
					slider_Frtc_Fps().IsEnabled(false);
					ShowNotification(L"FRTC disabled");
					AVDebugWriteLine(L"FRTC disabled");
				}
			}
		}
		catch (...) {}
	}

	void MainPage::slider_Frtc_Fps_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"???", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				IADLX3DFrameRateTargetControlPtr pp3DFrameRateTargetControl;
				adlx_Res0 = pp3DSettingsServices->GetFrameRateTargetControl(ppGpuInfo, &pp3DFrameRateTargetControl);
				adlx_Res0 = pp3DFrameRateTargetControl->SetFPS(newValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_Frtc_Fps().Foreground(colorInvalid);
				ShowNotification(L"Failed setting FRTC fps");
				AVDebugWriteLine(L"Failed setting FRTC fps");
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_Frtc_Fps().Foreground(colorValid);
				ShowNotification(L"FRTC fps set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"FRTC fps set to " << newValue);
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

			//Get setting value
			ADLX_ANTI_ALIASING_MODE newValue = (ADLX_ANTI_ALIASING_MODE)sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				if (newValue == ADLX_ANTI_ALIASING_MODE::AA_MODE_USE_APP_SETTINGS)
				{
					newFailed = !AdlAppPropertySet(adl_AppSelected(), L"AntiAlias", L"1", gpuUniqueIdentifierHex);
					newFailed = !AdlAppPropertySet(adl_AppSelected(), L"EQAA", L"0", gpuUniqueIdentifierHex);
				}
				else if (newValue == ADLX_ANTI_ALIASING_MODE::AA_MODE_ENHANCE_APP_SETTINGS)
				{
					newFailed = !AdlAppPropertySet(adl_AppSelected(), L"AntiAlias", L"1", gpuUniqueIdentifierHex);
					newFailed = !AdlAppPropertySet(adl_AppSelected(), L"EQAA", L"1", gpuUniqueIdentifierHex);
				}
				else if (newValue == ADLX_ANTI_ALIASING_MODE::AA_MODE_OVERRIDE_APP_SETTINGS)
				{
					newFailed = !AdlAppPropertySet(adl_AppSelected(), L"AntiAlias", L"2", gpuUniqueIdentifierHex);
				}
			}
			else
			{
				//Set setting
				IADLX3DAntiAliasingPtr pp3DAntiAliasing;
				adlx_Res0 = pp3DSettingsServices->GetAntiAliasing(ppGpuInfo, &pp3DAntiAliasing);
				adlx_Res0 = pp3DAntiAliasing->SetMode(newValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting AA mode");
				AVDebugWriteLine(L"Failed setting AA mode");
			}
			else
			{
				if (newValue != ADLX_ANTI_ALIASING_MODE::AA_MODE_OVERRIDE_APP_SETTINGS)
				{
					combobox_AntiAliasingLevel().IsEnabled(false);
				}
				else
				{
					combobox_AntiAliasingLevel().IsEnabled(true);
				}

				ShowNotification(L"AA mode set to " + ADLX_ANTI_ALIASING_MODE_STRING[newValue]);
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

			//Get setting value
			ADLX_ANTI_ALIASING_METHOD newValue = (ADLX_ANTI_ALIASING_METHOD)sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				if (newValue == ADLX_ANTI_ALIASING_METHOD::AA_METHOD_MULTISAMPLING)
				{
					newFailed = !AdlAppPropertySet(adl_AppSelected(), L"ASD", L"-1", gpuUniqueIdentifierHex);
					newFailed = !AdlAppPropertySet(adl_AppSelected(), L"ASE", L"0", gpuUniqueIdentifierHex);
					newFailed = !AdlAppPropertySet(adl_AppSelected(), L"ASTT", L"0", gpuUniqueIdentifierHex);
				}
				else if (newValue == ADLX_ANTI_ALIASING_METHOD::AA_METHOD_ADAPTIVE_MULTISAMPLING)
				{
					newFailed = !AdlAppPropertySet(adl_AppSelected(), L"ASD", L"1", gpuUniqueIdentifierHex);
					newFailed = !AdlAppPropertySet(adl_AppSelected(), L"ASE", L"0", gpuUniqueIdentifierHex);
					newFailed = !AdlAppPropertySet(adl_AppSelected(), L"ASTT", L"1", gpuUniqueIdentifierHex);
				}
				else if (newValue == ADLX_ANTI_ALIASING_METHOD::AA_METHOD_SUPERSAMPLING)
				{
					newFailed = !AdlAppPropertySet(adl_AppSelected(), L"ASD", L"1", gpuUniqueIdentifierHex);
					newFailed = !AdlAppPropertySet(adl_AppSelected(), L"ASE", L"1", gpuUniqueIdentifierHex);
					newFailed = !AdlAppPropertySet(adl_AppSelected(), L"ASTT", L"1", gpuUniqueIdentifierHex);
				}
			}
			else
			{
				//Set setting
				IADLX3DAntiAliasingPtr pp3DAntiAliasing;
				adlx_Res0 = pp3DSettingsServices->GetAntiAliasing(ppGpuInfo, &pp3DAntiAliasing);
				adlx_Res0 = pp3DAntiAliasing->SetMethod(newValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting AA method");
				AVDebugWriteLine(L"Failed setting AA method");
			}
			else
			{
				ShowNotification(L"AA method set to " + ADLX_ANTI_ALIASING_METHOD_STRING[newValue]);
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

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex() + 1;
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Enumeration index correction
				std::wstring setValueEqaa = L"";
				std::wstring setValueSamples = L"";
				if (newValue == 1)
				{
					setValueEqaa = L"0";
					setValueSamples = L"2";
				}
				else if (newValue == 2)
				{
					setValueEqaa = L"1";
					setValueSamples = L"2";
				}
				else if (newValue == 3)
				{
					setValueEqaa = L"0";
					setValueSamples = L"4";
				}
				else if (newValue == 4)
				{
					setValueEqaa = L"1";
					setValueSamples = L"4";
				}
				else if (newValue == 5)
				{
					setValueEqaa = L"0";
					setValueSamples = L"8";
				}
				else if (newValue == 6)
				{
					setValueEqaa = L"1";
					setValueSamples = L"8";
				}

				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"EQAA", setValueEqaa, gpuUniqueIdentifierHex);
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"AntiAliasSmpls", setValueSamples, gpuUniqueIdentifierHex);
			}
			else
			{
				//Enumeration index correction
				int setValue = 0;
				if (newValue == 1)
				{
					setValue = 2;
				}
				else if (newValue == 2)
				{
					setValue = 3;
				}
				else if (newValue == 3)
				{
					setValue = 4;
				}
				else if (newValue == 4)
				{
					setValue = 5;
				}
				else if (newValue == 5)
				{
					setValue = 8;
				}
				else if (newValue == 6)
				{
					setValue = 9;
				}

				//Set setting
				IADLX3DAntiAliasingPtr pp3DAntiAliasing;
				adlx_Res0 = pp3DSettingsServices->GetAntiAliasing(ppGpuInfo, &pp3DAntiAliasing);
				adlx_Res0 = pp3DAntiAliasing->SetLevel((ADLX_ANTI_ALIASING_LEVEL)setValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting AA level");
				AVDebugWriteLine(L"Failed setting AA level");
			}
			else
			{
				ShowNotification(L"AA level set to " + ADLX_ANTI_ALIASING_LEVEL_STRING[newValue]);
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

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"MLF", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				IADLX3DMorphologicalAntiAliasingPtr pp3DMorphologicalAntiAliasing;
				adlx_Res0 = pp3DSettingsServices->GetMorphologicalAntiAliasing(ppGpuInfo, &pp3DMorphologicalAntiAliasing);
				adlx_Res0 = pp3DMorphologicalAntiAliasing->SetEnabled(newValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling Morphological AA");
					AVDebugWriteLine(L"Failed enabling Morphological AA");
				}
				else
				{
					ShowNotification(L"Failed disabling Morphological AA");
					AVDebugWriteLine(L"Failed disabling Morphological AA");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"Morphological AA enabled");
					AVDebugWriteLine(L"Morphological AA enabled");
				}
				else
				{
					ShowNotification(L"Morphological AA disabled");
					AVDebugWriteLine(L"Morphological AA disabled");
				}
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

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				std::wstring convertedValue = newValue ? L"2" : L"0";
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"AnisoDegree", convertedValue, gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				IADLX3DAnisotropicFilteringPtr pp3DAnisotropicFiltering;
				adlx_Res0 = pp3DSettingsServices->GetAnisotropicFiltering(ppGpuInfo, &pp3DAnisotropicFiltering);
				adlx_Res0 = pp3DAnisotropicFiltering->SetEnabled(newValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling Anisotropic");
					AVDebugWriteLine(L"Failed enabling Anisotropic");
				}
				else
				{
					ShowNotification(L"Failed disabling Anisotropic");
					AVDebugWriteLine(L"Failed disabling Anisotropic");
				}
			}
			else
			{
				if (newValue)
				{
					combobox_AnisotropicTextureFiltering_Level().IsEnabled(true);
					ShowNotification(L"Anisotropic enabled");
					AVDebugWriteLine(L"Anisotropic enabled");
				}
				else
				{
					combobox_AnisotropicTextureFiltering_Level().IsEnabled(false);
					ShowNotification(L"Anisotropic disabled");
					AVDebugWriteLine(L"Anisotropic disabled");
				}
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_AnisotropicTextureFiltering_Level_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex() + 1;
			bool newFailed = true;

			//Enumeration index correction
			int setValue = 0;
			if (newValue == 1)
			{
				setValue = 2;
			}
			else if (newValue == 2)
			{
				setValue = 4;
			}
			else if (newValue == 3)
			{
				setValue = 8;
			}
			else if (newValue == 4)
			{
				setValue = 16;
			}

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"AnisoDegree", number_to_wstring(setValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				IADLX3DAnisotropicFilteringPtr pp3DAnisotropicFiltering;
				adlx_Res0 = pp3DSettingsServices->GetAnisotropicFiltering(ppGpuInfo, &pp3DAnisotropicFiltering);
				adlx_Res0 = pp3DAnisotropicFiltering->SetLevel((ADLX_ANISOTROPIC_FILTERING_LEVEL)setValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting Anisotropic level");
				AVDebugWriteLine(L"Failed setting Anisotropic level");
			}
			else
			{
				ShowNotification(L"Anisotropic level set to " + ADLX_ANISOTROPIC_FILTERING_LEVEL_STRING[newValue]);
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

			//Get setting value
			ADLX_TESSELLATION_MODE newValue = (ADLX_TESSELLATION_MODE)sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"Tessellation_OP", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				IADLX3DTessellationPtr pp3DTessellation;
				adlx_Res0 = pp3DSettingsServices->GetTessellation(ppGpuInfo, &pp3DTessellation);
				adlx_Res0 = pp3DTessellation->SetMode(newValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting Tessellation mode");
				AVDebugWriteLine(L"Failed setting Tessellation mode");
			}
			else
			{
				if (newValue != ADLX_TESSELLATION_MODE::T_MODE_OVERRIDE_APP_SETTINGS)
				{
					combobox_Tessellation_Level().IsEnabled(false);
				}
				else
				{
					combobox_Tessellation_Level().IsEnabled(true);
				}

				ShowNotification(L"Tessellation mode set to " + ADLX_TESSELLATION_MODE_STRING[newValue]);
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

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Enumeration index correction
			int setValue = 0;
			if (newValue == 0)
			{
				setValue = 1;
			}
			else if (newValue == 1)
			{
				setValue = 2;
			}
			else if (newValue == 2)
			{
				setValue = 4;
			}
			else if (newValue == 3)
			{
				setValue = 6;
			}
			else if (newValue == 4)
			{
				setValue = 8;
			}
			else if (newValue == 5)
			{
				setValue = 16;
			}
			else if (newValue == 6)
			{
				setValue = 32;
			}
			else if (newValue == 7)
			{
				setValue = 64;
			}

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"Tessellation", number_to_wstring(setValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				IADLX3DTessellationPtr pp3DTessellation;
				adlx_Res0 = pp3DSettingsServices->GetTessellation(ppGpuInfo, &pp3DTessellation);
				adlx_Res0 = pp3DTessellation->SetLevel((ADLX_TESSELLATION_LEVEL)setValue);

				//Set result
				newFailed = adlx_Res0 != ADLX_OK;
			}

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting Tessellation level");
				AVDebugWriteLine(L"Failed setting Tessellation level");
			}
			else
			{
				ShowNotification(L"Tessellation level set to " + ADLX_TESSELLATION_LEVEL_STRING[newValue]);
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
				ShowNotification(L"Failed resetting shader cache");
				AVDebugWriteLine(L"Failed resetting shader cache");
			}
			else
			{
				ShowNotification(L"Shader cache is reset");
				AVDebugWriteLine(L"Shader cache is reset");
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_OpenGLTripleBuffering_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"EnableTrplBffr", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_AdapterIndex, "UMD", "EnableTripleBuffering", number_to_string(newValue));
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling Triple buffering");
					AVDebugWriteLine(L"Failed enabling Triple buffering");
				}
				else
				{
					ShowNotification(L"Failed disabling Triple buffering");
					AVDebugWriteLine(L"Failed disabling Triple buffering");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"Triple buffering enabled");
					AVDebugWriteLine(L"Triple buffering enabled");
				}
				else
				{
					ShowNotification(L"Triple buffering disabled");
					AVDebugWriteLine(L"Triple buffering disabled");
				}
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_OpenGL10Bit_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"???", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_AdapterIndex, "UMD", "KMD_10BitMode", number_to_string(newValue));
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling 10-Bit pixel format");
					AVDebugWriteLine(L"Failed enabling 10-Bit pixel format");
				}
				else
				{
					ShowNotification(L"Failed disabling 10-Bit pixel format");
					AVDebugWriteLine(L"Failed disabling 10-Bit pixel format");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"10-Bit pixel format enabled");
					AVDebugWriteLine(L"10-Bit pixel format enabled");
				}
				else
				{
					ShowNotification(L"10-Bit pixel format disabled");
					AVDebugWriteLine(L"10-Bit pixel format disabled");
				}
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_FrameGenSearchMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"???", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				newFailed = !RegistrySet(HKEY_CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenSearchMode", newValue);
			}

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting Motion search mode");
				AVDebugWriteLine(L"Failed setting Motion search mode");
			}
			else
			{
				ShowNotification(L"Motion search mode set to " + REGISTRY_FRAMEGEN_SEARCH_MODE_STRING[newValue]);
				AVDebugWriteLine(L"Motion search mode set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_FrameGenPerfMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"???", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				newFailed = !RegistrySet(HKEY_CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenPerfMode", newValue);
			}

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting Motion performance mode");
				AVDebugWriteLine(L"Failed setting Motion performance mode");
			}
			else
			{
				ShowNotification(L"Motion performance mode set to " + REGISTRY_FRAMEGEN_PERFORMANCE_MODE_STRING[newValue]);
				AVDebugWriteLine(L"Motion performance mode set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_FrameGenResponseMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"???", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				newFailed = !RegistrySet(HKEY_CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenFallbackMode", newValue);
			}

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting Motion response mode");
				AVDebugWriteLine(L"Failed setting Motion response mode");
			}
			else
			{
				ShowNotification(L"Motion response mode set to " + REGISTRY_FRAMEGEN_RESPONSE_MODE_STRING[newValue]);
				AVDebugWriteLine(L"Motion response mode set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_TextureFilteringQuality_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"TFQ", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_AdapterIndex, "UMD", "TFQ", number_to_string(newValue));
			}

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting Filtering quality");
				AVDebugWriteLine(L"Failed setting Filtering quality");
			}
			else
			{
				//Set result
				ShowNotification(L"Filtering quality set to " + REGISTRY_TEXTURE_FILTERING_QUALITY_STRING[newValue]);
				AVDebugWriteLine(L"Filtering quality set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_SurfaceFormatOptimization_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"SrfcFrmtRplcmnt", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_AdapterIndex, "UMD", "SurfaceFormatReplacements", number_to_string(newValue));
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling Format optimization");
					AVDebugWriteLine(L"Failed enabling Format optimization");
				}
				else
				{
					ShowNotification(L"Failed disabling Format optimization");
					AVDebugWriteLine(L"Failed disabling Format optimization");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"Format optimization enabled");
					AVDebugWriteLine(L"Format optimization enabled");
				}
				else
				{
					ShowNotification(L"Format optimization disabled");
					AVDebugWriteLine(L"Format optimization disabled");
				}
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_FsrOverrideUpscaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"FsrOverride", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_AdapterIndex, "UMD", "FsrOverride", number_to_string(newValue));
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling FSR upscaling override");
					AVDebugWriteLine(L"Failed enabling FSR upscaling override");
				}
				else
				{
					ShowNotification(L"Failed disabling FSR upscaling override");
					AVDebugWriteLine(L"Failed disabling FSR upscaling override");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"FSR upscaling override enabled");
					AVDebugWriteLine(L"FSR upscaling override enabled");
				}
				else
				{
					ShowNotification(L"FSR upscaling override disabled");
					AVDebugWriteLine(L"FSR upscaling override disabled");
				}
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_FsrOverrideFrameGen_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check used application
			if (adl_AppSelected().Initialized())
			{
				//Set setting
				newFailed = !AdlAppPropertySet(adl_AppSelected(), L"MlfiOverride", number_to_wstring(newValue), gpuUniqueIdentifierHex);
			}
			else
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_AdapterIndex, "UMD", "MlfiOverride", number_to_string(newValue));
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling FSR frame generation override");
					AVDebugWriteLine(L"Failed enabling FSR frame generation override");
				}
				else
				{
					ShowNotification(L"Failed disabling FSR frame generation override");
					AVDebugWriteLine(L"Failed disabling FSR frame generation override");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"FSR frame generation override enabled");
					AVDebugWriteLine(L"FSR frame generation override enabled");
				}
				else
				{
					ShowNotification(L"FSR frame generation override disabled");
					AVDebugWriteLine(L"FSR frame generation override disabled");
				}
			}
		}
		catch (...) {}
	}
}