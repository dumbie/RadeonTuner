#pragma once
#include "pch.h"
#include "AppVariables.h"

#include "AdlAppsFunc.h"
#include "AdlAppsUnlock.h"
#include "AdlGraphicsStatus.h"
#include "AdlAppsSetDefaults.h"
#include "AdlAppsInterface.h"
#include "AdlAppsAdd.h"
#include "AdlAppsLoad.h"
#include "AdlAppsRemove.h"
#include "AdlAppsProperty.h"
#include "AdlOverdrive8.h"
#include "AdlEyefinity.h"
#include "AdlRegistry.h"
#include "AdlGetDevices.h"
#include "AdlGetIdentifier.h"
#include "AdlInitialize.h"
#include "AdlCheck.h"
#include "AdlFunctions.h"

#include "AdlxInfoLoad.h"
#include "AdlValuesPrepare.h"
#include "AdlxValuesLoadSelect.h"
#include "AdlxValuesPrepare.h"
#include "AdlxValuesExportDisplay.h"
#include "AdlxValuesImportDisplay.h"
#include "AdlxValuesExportGraphics.h"
#include "AdlxValuesImportGraphics.h"
#include "AdlxValuesExportTuning.h"
#include "AdlxValuesImportTuning.h"

#include "AdlxEventsDisplay.h"
#include "AdlxEventsFans.h"
#include "AdlxEventsGraphics.h"
#include "AdlxEventsMultimedia.h"
#include "AdlxEventsTuning.h"

#include "MultimediaSettingsFunc.h"
#include "MultimediaSettingsGenerateAdl.h"
#include "MultimediaSettingsConvertUIAdl.h"
#include "MultimediaSettingsConvertUICurrent.h"
#include "MultimediaSettingsConvertUIDefault.h"

#include "GraphicsFsrOverrideDll.h"
#include "GraphicsSettingsGenerateAdlApp.h"
#include "GraphicsSettingsGenerateAdlRegistry.h"
#include "GraphicsSettingsConvertUIAdl.h"
#include "GraphicsSettingsConvertUICurrent.h"
#include "GraphicsSettingsConvertUIDefault.h"
#include "GraphicsSettingsFunc.h"
#include "AdlxResetShaderCache.h"

#include "DisplaySettingsGenerateAdl.h"
#include "DisplaySettingsConvertUIAdl.h"
#include "DisplaySettingsConvertUICurrent.h"
#include "DisplaySettingsConvertUIDefault.h"
#include "DisplaySettingsResolution.h"
#include "DisplaySettingsDetails.h"
#include "DisplaySettingsFunc.h"

#include "TuningFanSettingsGenerateAdl.h"
#include "TuningFanSettingsConvertUIAdl.h"
#include "TuningFanSettingsConvertUICurrent.h"
#include "TuningFanSettingsCache.h"
#include "TuningFanSettingsMatch.h"
#include "TuningFanSettingsApply.h"
#include "AdlTuningMetrics.h"

#include "EyefinityFunc.h"
#include "EyefinityEvents.h"
#include "PowerBoostFunc.h"
#include "PowerBoostEvents.h"

#include "SettingFunc.h"
#include "SettingAdmin.h"
#include "SettingSave.h"
#include "SettingLoad.h"

#include "AdlxLoopDevice.h"
#include "AdlxLoopMetrics.h"
#include "AdlxLoopKeepActive.h"

#include "MainPage.h"
#if __has_include("MainPage.g.cpp")
#include "MainPage.g.cpp"
#endif

namespace winrt::RadeonTuner::implementation
{
	void MainPage::page_Loaded(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			////Check driver software type
			//if (AdlCheckDriverOnlySoftware())
			//{
			//	grid_Main().IsHitTestVisible(false);
			//	grid_Overlay_Warning().Visibility(Visibility::Visible);
			//	textblock_Overlay_Text().Text(L"Incompatible driver software type.");
			//	textblock_Overlay_Sub_Text().Text(L"To prevent possible issues with RadeonTuner please (re)install your drivers using the 'Driver Only' software type.");
			//	return;
			//}

			//Initialize adl api
			std::wstring initResult_Adl = AdlInitialize();
			if (!initResult_Adl.empty())
			{
				grid_Main().IsHitTestVisible(false);
				grid_Overlay_Warning().Visibility(Visibility::Visible);
				textblock_Overlay_Text().Text(L"Failed initializing ADL, please (re)install or update your AMD drivers.");
				textblock_Overlay_Sub_Text().Text(L"If this message keeps appearing try using the AMD Cleanup Utility.\n\n" + initResult_Adl);
				return;
			}

			//Prepare adlx values
			std::wstring initResult_Values = AdlxValuesPrepare();
			if (!initResult_Values.empty())
			{
				grid_Main().IsHitTestVisible(false);
				grid_Overlay_Warning().Visibility(Visibility::Visible);
				textblock_Overlay_Text().Text(L"Failed preparing values, please (re)install or update your AMD drivers.");
				textblock_Overlay_Sub_Text().Text(L"If this message keeps appearing try using the AMD Cleanup Utility.\n\n" + initResult_Values);
				return;
			}

			//Prepare adl values
			AdlValuesPrepare();

			//Load tuning profiles file
			TuningFanSettings_Profiles_LoadFromFile();

			//Load and list Power Boost applications
			PowerBoost_Applications_LoadFromFile();
			PowerBoost_Applications_List();

			//Load and list Automatic Eyefinity applications
			Eyefinity_Applications_LoadFromFile();
			Eyefinity_Applications_List();

			//Set default registry values
			AdlSetDefaultSettings();

			//Check admin setttings
			SettingAdmin();

			//Load settings
			SettingLoad();

			//Show or hide experimental settings
			ShowExperimentalSettings(true);

			//Select default indexes
			SelectDefaultIndexes();

			//Start adlx loop device
			std::thread threadLoopDevice(&MainPage::AdlxLoopDevice, this);
			threadLoopDevice.detach();

			//Start adlx loop metrics
			std::thread threadLoopMetrics(&MainPage::AdlxLoopMetrics, this);
			threadLoopMetrics.detach();

			//Start adlx loop keep active
			std::thread threadLoopKeepActive(&MainPage::AdlxLoopKeepActive, this);
			threadLoopKeepActive.detach();
		}
		catch (...) {}
	}

	void MainPage::button_Overlay_Exit_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Exit application
			AppVariables::App.Exit(true);
		}
		catch (...) {}
	}

	void MainPage::SelectDefaultIndexes()
	{
		try
		{
			//Select gpu and display
			combobox_GpuSelect().SelectedIndex(0);
			combobox_DisplaySelect().SelectedIndex(0);

			//Select application
			combobox_AppSelect().SelectedIndex(0);

			//Select Eyefinity orientation
			combobox_EyefinityMonitorOrientation().SelectedIndex(0);

			//Select previous menu index
			int mainSelectIndex = 0;
			std::optional<int> prevMenuIndex = AppVariables::Settings.Load<int>("MenuIndex");
			if (prevMenuIndex.has_value())
			{
				mainSelectIndex = prevMenuIndex.value();
				//Check if selected index is exit button
				int exitButtonIndex = listbox_Main().Items().Size() - 1;
				if (mainSelectIndex >= exitButtonIndex) { mainSelectIndex = 0; }
			}
			try
			{
				listbox_Main().SelectedIndex(mainSelectIndex);
			}
			catch (...)
			{
				listbox_Main().SelectedIndex(0);
			}
		}
		catch (...) {}
	}

	void MainPage::ShowExperimentalSettings(BOOL silent)
	{
		try
		{
			std::optional<bool> ShowExperimental = AppVariables::Settings.Load<bool>("ShowExperimental");
			if (ShowExperimental.has_value())
			{
				if (ShowExperimental.value())
				{
					//Enable or disable graphics settings
					stackpanel_MultiFrameGenerationRatio().Visibility(Visibility::Visible);
					stackpanel_FsrOverrideMultiFrameGeneration().Visibility(Visibility::Visible);
					stackpanel_FsrOverrideRayRegeneration().Visibility(Visibility::Visible);
					stackpanel_FsrOverrideNeuralRadianceCaching().Visibility(Visibility::Visible);
					stackpanel_FsrOtaUpdates().Visibility(Visibility::Visible);
					stackpanel_Display_HdrTypePreference().Visibility(Visibility::Visible);
					stackpanel_FluidMotion_Options().Visibility(Visibility::Visible);
					textblock_GraphicsOptions_Details().Visibility(Visibility::Visible);
					textblock_FsrDllLoadPath().Visibility(Visibility::Collapsed);
					textbox_FsrDllLoadPath().Width(NAN);

					//Show notification
					if (!silent)
					{
						ShowNotification(L"Showing experimental settings");
						AVDebugWriteLine(L"Showing experimental settings");
					}
				}
				else
				{
					//Enable or disable graphics settings
					stackpanel_MultiFrameGenerationRatio().Visibility(Visibility::Collapsed);
					stackpanel_FsrOverrideMultiFrameGeneration().Visibility(Visibility::Collapsed);
					stackpanel_FsrOverrideRayRegeneration().Visibility(Visibility::Collapsed);
					stackpanel_FsrOverrideNeuralRadianceCaching().Visibility(Visibility::Collapsed);
					stackpanel_FsrOtaUpdates().Visibility(Visibility::Collapsed);
					stackpanel_Display_HdrTypePreference().Visibility(Visibility::Collapsed);
					stackpanel_FluidMotion_Options().Visibility(Visibility::Collapsed);
					textblock_GraphicsOptions_Details().Visibility(Visibility::Collapsed);
					textblock_FsrDllLoadPath().Visibility(Visibility::Visible);
					textbox_FsrDllLoadPath().Width(0);

					//Show notification
					if (!silent)
					{
						ShowNotification(L"Hiding experimental settings");
						AVDebugWriteLine(L"Hiding experimental settings");
					}
				}
			}
		}
		catch (...) {}
	}

	void MainPage::listbox_Main_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Get selected index
			int selectedIndex = sender.as<ListBox>().SelectedIndex();

			//Exit application
			if (selectedIndex == 7)
			{
				//Exit application
				AppVariables::App.Exit(true);
				return;
			}

			//Save selected index
			AppVariables::Settings.Set("MenuIndex", selectedIndex);

			//Hide all buttons
			stackpanel_Tuning_Buttons().Visibility(Visibility::Collapsed);
			stackpanel_Fan_Buttons().Visibility(Visibility::Collapsed);
			stackpanel_Graphics_Buttons().Visibility(Visibility::Collapsed);
			stackpanel_Display_Buttons().Visibility(Visibility::Collapsed);
			stackpanel_Multimedia_Buttons().Visibility(Visibility::Collapsed);
			stackpanel_Information_Buttons().Visibility(Visibility::Collapsed);

			//Hide all pages
			stackpanel_Graphics().Visibility(Visibility::Collapsed);
			stackpanel_Tuning().Visibility(Visibility::Collapsed);
			stackpanel_Fans().Visibility(Visibility::Collapsed);
			stackpanel_Display().Visibility(Visibility::Collapsed);
			stackpanel_Multimedia().Visibility(Visibility::Collapsed);
			stackpanel_Settings().Visibility(Visibility::Collapsed);
			stackpanel_Information().Visibility(Visibility::Collapsed);

			//Disable selection boxes
			combobox_GpuSelect().IsEnabled(false);
			combobox_DisplaySelect().IsEnabled(false);
			combobox_AppSelect().IsEnabled(false);

			//Make selected page visible
			if (selectedIndex == 0)
			{
				combobox_GpuSelect().IsEnabled(true);
				stackpanel_Tuning().Visibility(Visibility::Visible);
				stackpanel_Tuning_Buttons().Visibility(Visibility::Visible);
			}
			else if (selectedIndex == 1)
			{
				combobox_GpuSelect().IsEnabled(true);
				stackpanel_Fans().Visibility(Visibility::Visible);
				stackpanel_Fan_Buttons().Visibility(Visibility::Visible);
			}
			else if (selectedIndex == 2)
			{
				combobox_GpuSelect().IsEnabled(true);
				combobox_AppSelect().IsEnabled(true);
				stackpanel_Graphics().Visibility(Visibility::Visible);
				stackpanel_Graphics_Buttons().Visibility(Visibility::Visible);
			}
			else if (selectedIndex == 3)
			{
				combobox_DisplaySelect().IsEnabled(true);
				stackpanel_Display().Visibility(Visibility::Visible);
				stackpanel_Display_Buttons().Visibility(Visibility::Visible);
			}
			else if (selectedIndex == 4)
			{
				combobox_GpuSelect().IsEnabled(true);
				stackpanel_Multimedia().Visibility(Visibility::Visible);
				stackpanel_Multimedia_Buttons().Visibility(Visibility::Visible);
			}
			else if (selectedIndex == 5)
			{
				stackpanel_Settings().Visibility(Visibility::Visible);
			}
			else if (selectedIndex == 6)
			{
				combobox_GpuSelect().IsEnabled(true);
				stackpanel_Information().Visibility(Visibility::Visible);
				stackpanel_Information_Buttons().Visibility(Visibility::Visible);
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_GpuSelect_SelectionChanged(IInspectable const& sender, Controls::SelectionChangedEventArgs const& e)
	{
		try
		{
			//Reload tuning and fans settings
			AdlxValuesLoadSelectGpu();
		}
		catch (...) {}
	}

	void MainPage::combobox_DisplaySelect_SelectionChanged(IInspectable const& sender, Controls::SelectionChangedEventArgs const& e)
	{
		try
		{
			//Reload display settings
			AdlxValuesLoadSelectDisplay();
		}
		catch (...) {}
	}

	void MainPage::combobox_AppSelect_SelectionChanged(IInspectable const& sender, Controls::SelectionChangedEventArgs const& e)
	{
		try
		{
			//Reload application settings
			AdlxValuesLoadSelectApp();
		}
		catch (...) {}
	}

	void MainPage::ShowNotification(std::wstring text)
	{
		try
		{
			//Set notification text
			grid_Notification().Visibility(Visibility::Visible);
			textblock_Notification_Text().Text(text);

			//Notification timer tick
			std::function<void(IInspectable const& sender, IInspectable const& e)> tickFunction = [&](auto, auto)
				{
					try
					{
						//Hide notification text
						grid_Notification().Visibility(Visibility::Collapsed);

						//Stop notification timer
						TimerNotification.Stop();
					}
					catch (...) {}
				};

			//Start notification timer
			if (TimerNotification == NULL)
			{
				TimerNotification = winrt::Windows::UI::Xaml::DispatcherTimer();
				TimerNotification.Interval(TimeSpan(40000000));
				TimerNotification.Tick(tickFunction);
			}
			TimerNotification.Start();
		}
		catch (...) {}
	}
}