#pragma once
#include "pch.h"

//Launchers
#include "SteamFuncLibraryFolders.h"
#include "SteamFuncAppInfo.h"
#include "SteamStructures.h"
#include "SteamFunctions.h"

#include "AppVariables.h"
#include "AdlAppsFunc.h"
#include "AdlAppsUnlock.h"
#include "AdlGraphicsStatus.h"
#include "AdlAppsSetDefaults.h"
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
#include "AdlxValuesPrepare.h"
#include "AdlxValuesExportDisplay.h"
#include "AdlxValuesImportDisplay.h"
#include "AdlxValuesExportGraphics.h"
#include "AdlxValuesImportGraphics.h"
#include "AdlxValuesExportTuning.h"
#include "AdlxValuesImportTuning.h"

#include "AdlxValuesLoadDisplay.h"
#include "AdlxValuesLoadGraphics.h"
#include "AdlxValuesLoadMultimedia.h"
#include "AdlxValuesLoadTuning.h"

#include "AdlxEventsDisplay.h"
#include "AdlxEventsFans.h"
#include "AdlxEventsGraphics.h"
#include "AdlxEventsMultimedia.h"
#include "AdlxEventsTuning.h"

#include "AdlxEventsSelect.h"

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

#include "SettingFunc.h"
#include "SettingAdmin.h"
#include "SettingSave.h"
#include "SettingLoad.h"

#include "AppPickerInterface.h"
#include "AppPickerEvent.h"

#include "AdlxLoopMetrics.h"
#include "AdlxLoopKeepActive.h"

#include "AdjustCursor.h"
#include "MessageBox.h"

#include "MainPage.h"
#if __has_include("MainPage.g.cpp")
#include "MainPage.g.cpp"
#endif

namespace winrt::RadeonTuner::implementation
{
	winrt::fire_and_forget MainPage::page_Loaded(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Fix check if DCH / UWP or downgraded driver is installed and warn not supported
			//Fix check if other overclock applications are running and warn user

			//Check driver software type
			if (AdlCheckDriverOnlySoftware())
			{
				grid_Main().IsHitTestVisible(false);
				std::vector<std::wstring> messageAnswers{ L"Continue anyways", L"Exit application" };
				int messageResult = co_await ShowMessageBox(L"Incompatible driver software type", L"It is highly recommended that you install your drivers using the 'Driver Only' software type to prevent possible issues with RadeonTuner.\n\nPlease reinstall your drivers using the 'Driver Only' software type and 'Factory Reset' option, you can find those options by clicking on 'Additional Options' in the Radeon driver setup.", messageAnswers);
				if (messageResult == 0)
				{
					//Enable interface
					grid_Main().IsHitTestVisible(true);
				}
				else
				{
					//Exit application
					AppVariables::App.Exit(true);
					co_return;
				}
			}

			//Initialize adl api
			std::wstring initResult_Adl = AdlInitialize();
			if (!initResult_Adl.empty())
			{
				grid_Main().IsHitTestVisible(false);
				std::vector<std::wstring> messageAnswers{ L"Run AMD Cleanup Utility", L"Exit application" };
				int messageResult = co_await ShowMessageBox(L"Failed initializing ADL", L"Please (re)install or update your AMD drivers, if this message keeps appearing try using the AMD Cleanup Utility. (" + initResult_Adl + L")", messageAnswers);
				if (messageResult == 0)
				{
					//Launch driver cleanup utility
					LaunchDriverCleanup();

					//Exit application
					AppVariables::App.Exit(true);
					co_return;
				}
				else
				{
					//Exit application
					AppVariables::App.Exit(true);
					co_return;
				}
			}

			//Prepare adlx values
			AdlxValuesPrepare();

			//Load tuning profiles
			TuningFanSettings_Profiles_LoadFromFile();

			//Get all GPU's
			std::vector<AdapterInfo> listGpus = AdlGetGpuAll();
			if (listGpus.size() == 0)
			{
				grid_Main().IsHitTestVisible(false);
				std::vector<std::wstring> messageAnswers{ L"Run AMD Cleanup Utility", L"Exit application" };
				int messageResult = co_await ShowMessageBox(L"Failed to find any GPU's", L"Please (re)install or update your AMD drivers, if this message keeps appearing try using the AMD Cleanup Utility.", messageAnswers);
				if (messageResult == 0)
				{
					//Launch driver cleanup utility
					LaunchDriverCleanup();

					//Exit application
					AppVariables::App.Exit(true);
					co_return;
				}
				else
				{
					//Exit application
					AppVariables::App.Exit(true);
					co_return;
				}
			}
			else
			{
				//Select defaults
				AdlxValuesLoadSelectGpu(listGpus[0]);
			}

			//Get all displays
			std::vector<ADLDisplayInfo> displayList = AdlGetDisplayAll();
			if (displayList.size() == 0)
			{
				grid_Main().IsHitTestVisible(false);
				std::vector<std::wstring> messageAnswers{ L"Run AMD Cleanup Utility", L"Exit application" };
				int messageResult = co_await ShowMessageBox(L"Failed to find any displays", L"Please (re)install or update your AMD drivers, if this message keeps appearing try using the AMD Cleanup Utility.", messageAnswers);
				if (messageResult == 0)
				{
					//Launch driver cleanup utility
					LaunchDriverCleanup();

					//Exit application
					AppVariables::App.Exit(true);
					co_return;
				}
				else
				{
					//Exit application
					AppVariables::App.Exit(true);
					co_return;
				}
			}
			else
			{
				//Select defaults
				AdlxValuesLoadSelectDisplay(displayList[0]);
			}

			//Remove global user application
			AdlApplication globalApp{};
			globalApp.FileName = L"*.*";
			globalApp.FilePath = L"*\\*";
			AdlAppRemove(globalApp);

			//Load graphics settings
			AdlxValuesLoadSelectGraphics(adl_App_Global);

			//Load and list Automatic Eyefinity applications
			Eyefinity_Applications_LoadFromFile();
			Eyefinity_Applications_List(true);

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

			//Start adlx loop metrics
			std::thread threadLoopMetrics(&MainPage::AdlxLoopMetrics, this);
			threadLoopMetrics.detach();

			//Start adlx loop keep active
			std::thread threadLoopKeepActive(&MainPage::AdlxLoopKeepActive, this);
			threadLoopKeepActive.detach();

			//Check for application update
			std::optional<bool> setStartCheckUpdate = AppVariables::Settings.Load<bool>("StartCheckUpdate");
			if (setStartCheckUpdate.has_value() && setStartCheckUpdate.value())
			{
				UpdateCheckResult updateCheckResult = UpdateCheck(AppVariables::hInstance, "dumbie", "RadeonTuner");
				if (updateCheckResult.UpdateFound)
				{
					//Show update button
					button_Update_Launch().Visibility(Visibility::Visible);

					//Show notification
					AVDebugWriteLine(L"New application update found");
					ShowNotification(L"New application update found");
				}
			}

			//Update first launch setting
			AppVariables::Settings.Set("FirstLaunch", false);
		}
		catch (...) {}
	}

	void MainPage::SelectDefaultIndexes()
	{
		try
		{
			//Select Eyefinity orientation
			combobox_EyefinityMonitorOrientation().SelectedIndex(0);

			//Select previous menu index
			int mainSelectIndex = 0;
			std::optional<int> prevMenuIndex = AppVariables::Settings.Load<int>("MenuIndex");
			if (prevMenuIndex.has_value())
			{
				mainSelectIndex = prevMenuIndex.value();
				//Check if selected index is exit button
				int exitButtonIndex = listview_Main().Items().Size() - 1;
				if (mainSelectIndex >= exitButtonIndex) { mainSelectIndex = 0; }
			}
			try
			{
				listview_Main().SelectedIndex(mainSelectIndex);
			}
			catch (...)
			{
				listview_Main().SelectedIndex(0);
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

	void MainPage::listview_Main_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Get selected index
			int selectedIndex = sender.as<ListView>().SelectedIndex();

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

			//Hide selection boxes
			button_GpuSelect().Visibility(Visibility::Collapsed);
			button_DisplaySelect().Visibility(Visibility::Collapsed);
			stackpanel_AppSelect_Graphics().Visibility(Visibility::Collapsed);
			stackpanel_AppSelect_Tuning().Visibility(Visibility::Collapsed);

			//Make selected page visible
			if (selectedIndex == 0)
			{
				button_GpuSelect().Visibility(Visibility::Visible);
				stackpanel_AppSelect_Tuning().Visibility(Visibility::Visible);
				stackpanel_Tuning().Visibility(Visibility::Visible);
				stackpanel_Tuning_Buttons().Visibility(Visibility::Visible);
			}
			else if (selectedIndex == 1)
			{
				button_GpuSelect().Visibility(Visibility::Visible);
				stackpanel_AppSelect_Tuning().Visibility(Visibility::Visible);
				stackpanel_Fans().Visibility(Visibility::Visible);
				stackpanel_Fan_Buttons().Visibility(Visibility::Visible);
			}
			else if (selectedIndex == 2)
			{
				button_GpuSelect().Visibility(Visibility::Visible);
				stackpanel_AppSelect_Graphics().Visibility(Visibility::Visible);
				stackpanel_Graphics().Visibility(Visibility::Visible);
				stackpanel_Graphics_Buttons().Visibility(Visibility::Visible);
			}
			else if (selectedIndex == 3)
			{
				button_DisplaySelect().Visibility(Visibility::Visible);
				stackpanel_Display().Visibility(Visibility::Visible);
				stackpanel_Display_Buttons().Visibility(Visibility::Visible);
			}
			else if (selectedIndex == 4)
			{
				button_GpuSelect().Visibility(Visibility::Visible);
				stackpanel_Multimedia().Visibility(Visibility::Visible);
				stackpanel_Multimedia_Buttons().Visibility(Visibility::Visible);
			}
			else if (selectedIndex == 5)
			{
				stackpanel_Settings().Visibility(Visibility::Visible);
			}
			else if (selectedIndex == 6)
			{
				button_GpuSelect().Visibility(Visibility::Visible);
				stackpanel_Information().Visibility(Visibility::Visible);
				stackpanel_Information_Buttons().Visibility(Visibility::Visible);
			}
		}
		catch (...) {}
	}

	void MainPage::ShowNotification(std::wstring text)
	{
		try
		{
			//Set notification text
			grid_Overlay_Notification().Visibility(Visibility::Visible);
			textblock_Notification_Text().Text(text);

			//Notification timer tick
			std::function<void(IInspectable const& sender, IInspectable const& e)> tickFunction = [&](auto, auto)
				{
					try
					{
						//Hide notification text
						grid_Overlay_Notification().Visibility(Visibility::Collapsed);

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