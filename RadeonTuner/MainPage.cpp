#pragma once
#include "pch.h"
#include "AppVariables.h"

#include "AdlAppsFunc.h"
#include "AdlAppsUnlock.h"
#include "AdlAppsReset.h"
#include "AdlAppsInterface.h"
#include "AdlAppsAdd.h"
#include "AdlAppsLoad.h"
#include "AdlAppsRemove.h"
#include "AdlAppsProperty.h"
#include "AdlRegistry.h"
#include "AdlInitialize.h"
#include "AdlxInitialize.h"
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

#include "AdlxResetDisplay.h"
#include "AdlxResetGraphics.h"
#include "AdlxResetTuning.h"

#include "AdlxEventsDisplay.h"
#include "AdlxEventsFans.h"
#include "AdlxEventsGraphics.h"
#include "AdlxEventsMultimedia.h"
#include "AdlxEventsPower.h"
#include "AdlxEventsTuning.h"

#include "GraphicsSettingsFunc.h"
#include "DisplaySettingsFunc.h"

#include "KeepActiveFunc.h"
#include "KeepActiveEvents.h"
#include "PowerBoostFunc.h"
#include "PowerBoostEvents.h"
#include "TuningFanSettingsCacheFunc.h"
#include "TuningFanSettingsFunc.h"

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
			//Initialize adl
			std::wstring initResult_Adl = AdlInitialize();
			if (!initResult_Adl.empty())
			{
				grid_Main().IsHitTestVisible(false);
				grid_Overlay().Visibility(Visibility::Visible);
				textblock_Overlay_Text().Text(L"Failed initializing ADL, please install or update your AMD drivers.");
				textblock_Overlay_Sub_Text().Text(L"If this message keeps appearing try using the AMD Cleanup Utility.\n\n" + initResult_Adl);
				return;
			}

			//Initialize adlx
			std::wstring initResult_Adlx = AdlxInitialize();
			if (!initResult_Adlx.empty())
			{
				grid_Main().IsHitTestVisible(false);
				grid_Overlay().Visibility(Visibility::Visible);
				textblock_Overlay_Text().Text(L"Failed initializing ADLX, please install or update your AMD drivers.");
				textblock_Overlay_Sub_Text().Text(L"If this message keeps appearing try using the AMD Cleanup Utility.\n\n" + initResult_Adlx);
				return;
			}

			//Load tuning profiles file
			TuningFanSettings_Profiles_LoadFromFile();

			//Load power boost applications
			PowerBoost_Applications_LoadFromFile();

			//List power boost applications
			PowerBoost_Applications_List();

			//Set adl app gpu identifier
			AdlAppSetUmdGpuId();

			//Prepare adlx values
			AdlxValuesPrepare();

			//Select default indexes
			SelectIndexesAdlx();

			//Prepare adl values
			AdlValuesPrepare();

			//Select default indexes
			SelectIndexesAdl();

			//Fix check driver installation software type Default / Minimal / Driver Only

			//Check admin setttings
			SettingAdmin();

			//Load settings
			SettingLoad();

			//Load power values
			AdlxValuesLoadSelectPower();

			//Select default indexes
			SelectIndexesMenu();

			//Show or hide experimental settings
			ShowExperimentalSettings(true);

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

	void MainPage::SelectIndexesAdl()
	{
		try
		{
			//Select default indexes
			combobox_AppSelect().SelectedIndex(0);
		}
		catch (...) {}
	}

	void MainPage::SelectIndexesAdlx()
	{
		try
		{
			//Select default indexes
			combobox_GpuSelect().SelectedIndex(0);
			combobox_DisplaySelect().SelectedIndex(0);
		}
		catch (...) {}
	}

	void MainPage::SelectIndexesMenu()
	{
		try
		{
			//Select previous menu index
			int mainSelectIndex = 0;
			std::optional<int> prevMenuIndex = AppVariables::Settings.Load<int>("MenuIndex");
			if (prevMenuIndex.has_value())
			{
				mainSelectIndex = prevMenuIndex.value();
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
					stackpanel_FsrDllLoadPath().Visibility(Visibility::Visible);

					stackpanel_FsrOverrideMultiFrameGeneration().Visibility(Visibility::Visible);
					stackpanel_FsrOverrideRayRegeneration().Visibility(Visibility::Visible);
					stackpanel_FsrOverrideNeuralRadianceCaching().Visibility(Visibility::Visible);

					//Enable or disable feature unlock button
					button_Graphics_Unlock().IsEnabled(true);

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
					stackpanel_FsrDllLoadPath().Visibility(Visibility::Collapsed);

					stackpanel_FsrOverrideMultiFrameGeneration().Visibility(Visibility::Collapsed);
					stackpanel_FsrOverrideRayRegeneration().Visibility(Visibility::Collapsed);
					stackpanel_FsrOverrideNeuralRadianceCaching().Visibility(Visibility::Collapsed);

					//Enable or disable feature unlock button
					button_Graphics_Unlock().IsEnabled(false);

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
			if (selectedIndex == 8)
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

			//Hide all pages
			stackpanel_Graphics().Visibility(Visibility::Collapsed);
			stackpanel_Tuning().Visibility(Visibility::Collapsed);
			stackpanel_Fans().Visibility(Visibility::Collapsed);
			stackpanel_Power().Visibility(Visibility::Collapsed);
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
				//DriverBug#1
				//combobox_GpuSelect().IsEnabled(true);
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
			}
			else if (selectedIndex == 5)
			{
				stackpanel_Power().Visibility(Visibility::Visible);
			}
			else if (selectedIndex == 6)
			{
				stackpanel_Settings().Visibility(Visibility::Visible);
			}
			else if (selectedIndex == 7)
			{
				combobox_GpuSelect().IsEnabled(true);
				combobox_DisplaySelect().IsEnabled(true);
				stackpanel_Information().Visibility(Visibility::Visible);
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
						AppVariables::TimerNotification.Stop();
					}
					catch (...) {}
				};

			//Start notification timer
			if (AppVariables::TimerNotification == NULL)
			{
				AppVariables::TimerNotification = winrt::Windows::UI::Xaml::DispatcherTimer();
			}
			AppVariables::TimerNotification.Interval(TimeSpan(40000000));
			AppVariables::TimerNotification.Tick(tickFunction);
			AppVariables::TimerNotification.Start();
		}
		catch (...) {}
	}
}