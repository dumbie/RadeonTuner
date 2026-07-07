#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::button_Graphics_AddExe_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Show file dialog
			AdlAppInterfaceAddFile();
		}
		catch (...) {}
	}

	void MainPage::button_Graphics_AddProcess_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Show process dialog
			AdlAppInterfaceAddProcess();
		}
		catch (...) {}
	}

	void MainPage::button_Graphics_Remove_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Remove application and profile
			std::wstring removeResult = AdlAppRemove(AdlAppSelectedGet().value());

			//Show notification
			ShowNotification(removeResult);
			AVDebugWriteLine(removeResult);

			//Check result
			if (removeResult == L"Application removed")
			{
				//Reload applications
				AdlAppInterfaceListLoad();

				//Select application
				combobox_AppSelect().SelectedIndex(0);
			}
		}
		catch (...) {}
	}

	void MainPage::button_Graphics_Reset_Settings_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get current and default settings
			GraphicsSettings graphicsSettings;

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				graphicsSettings = GraphicsSettings_Generate_FromADLRegistry(adl_Gpu_AdapterIndex).value();
			}
			else
			{
				graphicsSettings = GraphicsSettings_Generate_FromADLApp(AdlAppSelectedGet().value()).value();
			}

			//Convert settings to interface
			bool resetResult = GraphicsSettings_Convert_ToUI_Default(graphicsSettings);

			//Check result
			if (resetResult)
			{
				//Show notification
				ShowNotification(L"Graphics settings reset");
				AVDebugWriteLine(L"Graphics settings reset");
			}
			else
			{
				//Show notification
				ShowNotification(L"Graphics settings not reset");
				AVDebugWriteLine(L"Graphics settings not reset");
			}
		}
		catch (...) {}
	}

	void MainPage::button_Graphics_Import_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Import settings from file
			AdlxValuesImportGraphics();
		}
		catch (...) {}
	}

	void MainPage::button_Graphics_Export_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Export current settings to file
			AdlxValuesExportGraphics();
		}
		catch (...) {}
	}

	void MainPage::button_Graphics_Clear_ShaderCache_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Reset shader cache
			bool resetResult = AdlxResetShaderCache();

			//Set result
			if (!resetResult)
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

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "FsrOverride", number_to_wstring(newValue));
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"FsrOverride", number_to_wstring(newValue));
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling FSR Upscaling override");
					AVDebugWriteLine(L"Failed enabling FSR Upscaling override");
				}
				else
				{
					ShowNotification(L"Failed disabling FSR Upscaling override");
					AVDebugWriteLine(L"Failed disabling FSR Upscaling override");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"FSR Upscaling override enabled");
					AVDebugWriteLine(L"FSR Upscaling override enabled");
				}
				else
				{
					ShowNotification(L"FSR Upscaling override disabled");
					AVDebugWriteLine(L"FSR Upscaling override disabled");
				}

				//Update current value
				graphicsSettingsCurrent.FsrOverride.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_FsrOverrideFrameGeneration_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "MlfiOverride", number_to_wstring(newValue));
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"MlfiOverride", number_to_wstring(newValue));
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling FSR Frame Generation override");
					AVDebugWriteLine(L"Failed enabling FSR Frame Generation override");
				}
				else
				{
					ShowNotification(L"Failed disabling FSR Frame Generation override");
					AVDebugWriteLine(L"Failed disabling FSR Frame Generation override");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"FSR Frame Generation override enabled");
					AVDebugWriteLine(L"FSR Frame Generation override enabled");
				}
				else
				{
					ShowNotification(L"FSR Frame Generation override disabled");
					AVDebugWriteLine(L"FSR Frame Generation override disabled");
				}

				//Update current value
				graphicsSettingsCurrent.MlfiOverride.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_FsrOverrideMultiFrameGeneration_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "MfgOverride", number_to_wstring(newValue));
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"MfgOverride", number_to_wstring(newValue));
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling FSR Frame Generation override");
					AVDebugWriteLine(L"Failed enabling FSR Frame Generation override");
				}
				else
				{
					ShowNotification(L"Failed disabling FSR Frame Generation override");
					AVDebugWriteLine(L"Failed disabling FSR Frame Generation override");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"FSR Frame Generation override enabled");
					AVDebugWriteLine(L"FSR Frame Generation override enabled");
				}
				else
				{
					ShowNotification(L"FSR Frame Generation override disabled");
					AVDebugWriteLine(L"FSR Frame Generation override disabled");
				}

				//Update current value
				graphicsSettingsCurrent.MfgOverride.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_FsrOverrideRayRegeneration_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "MldOverride", number_to_wstring(newValue));
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"MldOverride", number_to_wstring(newValue));
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling FSR Ray Regeneration override");
					AVDebugWriteLine(L"Failed enabling FSR Ray Regeneration override");
				}
				else
				{
					ShowNotification(L"Failed disabling FSR Ray Regeneration override");
					AVDebugWriteLine(L"Failed disabling FSR Ray Regeneration override");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"FSR Ray Regeneration override enabled");
					AVDebugWriteLine(L"FSR Ray Regeneration override enabled");
				}
				else
				{
					ShowNotification(L"FSR Ray Regeneration override disabled");
					AVDebugWriteLine(L"FSR Ray Regeneration override disabled");
				}

				//Update current value
				graphicsSettingsCurrent.MldOverride.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_FsrOverrideNeuralRadianceCaching_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "NrcOverride", number_to_wstring(newValue));
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"NrcOverride", number_to_wstring(newValue));
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling FSR Neural Radiance Caching override");
					AVDebugWriteLine(L"Failed enabling FSR Neural Radiance Caching override");
				}
				else
				{
					ShowNotification(L"Failed disabling FSR Neural Radiance Caching override");
					AVDebugWriteLine(L"Failed disabling FSR Neural Radiance Caching override");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"FSR Neural Radiance Caching override enabled");
					AVDebugWriteLine(L"FSR Neural Radiance Caching override enabled");
				}
				else
				{
					ShowNotification(L"FSR Neural Radiance Caching override disabled");
					AVDebugWriteLine(L"FSR Neural Radiance Caching override disabled");
				}

				//Update current value
				graphicsSettingsCurrent.NrcOverride.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_MultiFrameGenerationRatio_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "MfgRatio", number_to_wstring(newValue));
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"MfgRatio", number_to_wstring(newValue));
			}

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting FSR Frame Generation Ratio");
				AVDebugWriteLine(L"Failed setting FSR Frame Generation Ratio");
			}
			else
			{
				ShowNotification(L"FSR Frame Generation Ratio set to " + ADL_FSR_MULTIFRAMEGEN_RATIO[newValue]);
				AVDebugWriteLine(L"FSR Frame Generation Ratio set to " << newValue);

				//Update current value
				graphicsSettingsCurrent.MfgRatio.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::textbox_FsrDllLoadPath_TextChanged(IInspectable const& sender, TextChangedEventArgs const& e)
	{
		try
		{
			//Get setting value
			auto newValueHstring = sender.as<TextBox>().Text();
			auto newValue = hstring_to_wstring(newValueHstring);
			bool newFailed = true;

			//Set FSR library version information
			FsrOverrideDllUpdateTextPathInfo(newValue);
			FsrOverrideDllUpdateTextVersion(newValue);

			//Check if saving is disabled
			if (disable_saving) { return; }

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "FsrOvrDLLPath", newValue);
			}
			else
			{
				//Set setting
				//newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"FfxDllPath", newValue);
			}

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting FSR Override Library");
				AVDebugWriteLine(L"Failed setting FSR Override Library");
			}
			else
			{
				ShowNotification(L"FSR Override Library set");
				AVDebugWriteLine(L"FSR Override Library set");

				//Update current value
				graphicsSettingsCurrent.FsrOvrDLLPath.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::button_FsrDllLoadPath_Set_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Show file dialog
			std::wstring newValue = filepicker_open(L"Select FSR library file...", { { L"FSR DLL", L"amdxcff*.dll" } });

			//Check file path
			if (newValue.empty())
			{
				ShowNotification(L"FSR library not changed, no path set");
				AVDebugWriteLine(L"FSR library not changed, no path set");
				return;
			}

			//Set text and trigger event
			textbox_FsrDllLoadPath().Text(newValue);
		}
		catch (...) {}
	}

	void MainPage::button_FsrDllLoadPath_Default_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get default FSR Override Library
			std::wstring newValue = FsrOverrideDllGetPathDefault();

			//Set text and trigger event
			textbox_FsrDllLoadPath().Text(newValue);
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_FsrLatencyReduction_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//DriverBug#5

			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				ADL_DELAG_SETTINGS adlSettings{};
				adlSettings.GlobalEnable = newValue;

				ADL_DELAG_NOTFICATION_REASON adlNotificationReason{};
				adlNotificationReason.GlobalEnableChanged = true;

				ADL_ERROR_REASON2 adlErrorReason;
				adl_Res0 = _ADL2_DELAG_SettingsX2_Set(adl_Context, adl_Gpu_AdapterIndex, adlSettings, adlNotificationReason, &adlErrorReason);

				//Set result
				newFailed = adl_Res0 != ADL_OK;

				//Notify change
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_DELAG_PROFILE, ADL_TRUE);
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"Dlg_PFEnable", number_to_wstring(newValue));
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling FSR Latency Reduction");
					AVDebugWriteLine(L"Failed enabling FSR Latency Reduction");
				}
				else
				{
					ShowNotification(L"Failed disabling FSR Latency Reduction");
					AVDebugWriteLine(L"Failed disabling FSR Latency Reduction");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"FSR Latency Reduction enabled");
					AVDebugWriteLine(L"FSR Latency Reduction enabled");
				}
				else
				{
					ShowNotification(L"FSR Latency Reduction disabled");
					AVDebugWriteLine(L"FSR Latency Reduction disabled");
				}

				//Update current value
				graphicsSettingsCurrent.DeLagEnabled.Current = newValue;
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

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "TurboSync", number_to_wstring(newValue));

				//Notify change
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_ENHANCEDSYNC, ADL_TRUE);
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"TurboSync", number_to_wstring(newValue));
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

				//Update current value
				graphicsSettingsCurrent.EnhancedSync.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_VerticalSync_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "VSyncControl", number_to_wstring(newValue));
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"VSyncControl", number_to_wstring(newValue));
			}

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting Vertical Sync");
				AVDebugWriteLine(L"Failed setting Vertical Sync");
			}
			else
			{
				ShowNotification(L"Vertical Sync set to " + ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE_STRING[newValue]);
				AVDebugWriteLine(L"Vertical Sync set to " << newValue);

				//Update current value
				graphicsSettingsCurrent.VerticalSync.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_FrameGenEnabled_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//DriverBug#6
			//Software\AMD\DVR FrameGenTestEnv

			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "", "DrvFrameGenEnabled", newValue);
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
					combobox_FrameGenAlgorithm().IsEnabled(true);
					ShowNotification(L"Fluid Motion Frames enabled");
					AVDebugWriteLine(L"Fluid Motion Frames enabled");
				}
				else
				{
					combobox_FrameGenSearchMode().IsEnabled(false);
					combobox_FrameGenPerfMode().IsEnabled(false);
					combobox_FrameGenResponseMode().IsEnabled(false);
					combobox_FrameGenAlgorithm().IsEnabled(false);
					ShowNotification(L"Fluid Motion Frames disabled");
					AVDebugWriteLine(L"Fluid Motion Frames disabled");
				}

				//Update current value
				graphicsSettingsCurrent.FrameGenEnabled.Current = newValue;
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

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !RegistrySet(HKEY_ENUM::CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenSearchMode", newValue);
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

				//Update current value
				graphicsSettingsCurrent.FrameGenSearchMode.Current = newValue;
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

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !RegistrySet(HKEY_ENUM::CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenPerfMode", newValue);
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

				//Update current value
				graphicsSettingsCurrent.FrameGenPerfMode.Current = newValue;
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

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !RegistrySet(HKEY_ENUM::CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenFallbackMode", newValue);
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

				//Update current value
				graphicsSettingsCurrent.FrameGenResponseMode.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_FrameGenAlgorithm_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !RegistrySet(HKEY_ENUM::CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenAlgorithm", newValue);
			}

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting Algorithm mode");
				AVDebugWriteLine(L"Failed setting Algorithm mode");
			}
			else
			{
				ShowNotification(L"Algorithm mode set to " + REGISTRY_FRAMEGEN_ALGORITHM_MODE_STRING[newValue]);
				AVDebugWriteLine(L"Algorithm mode set to " << newValue);

				//Update current value
				graphicsSettingsCurrent.FrameGenAlgorithm.Current = newValue;
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

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				ADL_CHILL_SETTINGS adlSettings{};
				adlSettings.GlobalEnable = newValue;

				ADL_CHILL_NOTFICATION_REASON adlNotificationReason{};
				adlNotificationReason.GlobalEnableChanged = true;

				ADL_ERROR_REASON adlErrorReason;
				adl_Res0 = _ADL2_CHILL_SettingsX2_Set(adl_Context, adl_Gpu_AdapterIndex, adlSettings, adlNotificationReason, &adlErrorReason);

				//Set result
				newFailed = adl_Res0 != ADL_OK;

				//Notify change
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_CHILL_PROFILE, ADL_TRUE);
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"Chil_PFEnable", number_to_wstring(newValue));
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
					//Check Radeon Chill Link
					if (radeon_Chill_Linked)
					{
						button_RadeonChill_Link().Opacity(1.00);
						slider_RadeonChill_Min().IsEnabled(false);
					}
					else
					{
						button_RadeonChill_Link().Opacity(0.50);
						slider_RadeonChill_Min().IsEnabled(true);
					}
					slider_RadeonChill_Max().IsEnabled(true);
					button_RadeonChill_Link().IsEnabled(true);
					ShowNotification(L"Radeon Chill enabled");
					AVDebugWriteLine(L"Radeon Chill enabled");
				}
				else
				{
					slider_RadeonChill_Min().IsEnabled(false);
					slider_RadeonChill_Max().IsEnabled(false);
					button_RadeonChill_Link().Opacity(0.50);
					button_RadeonChill_Link().IsEnabled(false);
					ShowNotification(L"Radeon Chill disabled");
					AVDebugWriteLine(L"Radeon Chill disabled");
				}

				//Update current value
				graphicsSettingsCurrent.ChillEnabled.Current = newValue;
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

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				ADL_CHILL_SETTINGS adlSettings{};
				adlSettings.GlobalMinFPS = newValue;

				ADL_CHILL_NOTFICATION_REASON adlNotificationReason{};
				adlNotificationReason.GlobalMinFPSChanged = true;

				ADL_ERROR_REASON adlErrorReason;
				adl_Res0 = _ADL2_CHILL_SettingsX2_Set(adl_Context, adl_Gpu_AdapterIndex, adlSettings, adlNotificationReason, &adlErrorReason);

				//Set result
				newFailed = adl_Res0 != ADL_OK;

				//Notify change
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_CHILL_PROFILE, ADL_TRUE);
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"Chil_MinFRate", number_to_wstring(newValue));
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

				//Update current value
				graphicsSettingsCurrent.ChillMinFps.Current = newValue;
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

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				ADL_CHILL_SETTINGS adlSettings{};
				adlSettings.GlobalMaxFPS = newValue;

				ADL_CHILL_NOTFICATION_REASON adlNotificationReason{};
				adlNotificationReason.GlobalMaxFPSChanged = true;

				ADL_ERROR_REASON adlErrorReason;
				adl_Res0 = _ADL2_CHILL_SettingsX2_Set(adl_Context, adl_Gpu_AdapterIndex, adlSettings, adlNotificationReason, &adlErrorReason);

				//Set result
				newFailed = adl_Res0 != ADL_OK;

				//Notify change
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_CHILL_PROFILE, ADL_TRUE);
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"Chil_MaxFRate", number_to_wstring(newValue));
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
				if (radeon_Chill_Linked || newValue < slider_RadeonChill_Min().Value())
				{
					slider_RadeonChill_Min().Value(newValue);
				}

				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_RadeonChill_Max().Foreground(colorValid);
				ShowNotification(L"Chill maximum fps set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Chill maximum fps set to " << newValue);

				//Update current value
				graphicsSettingsCurrent.ChillMaxFps.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::button_RadeonChill_Link_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Check Radeon Chill Link
			if (!radeon_Chill_Linked)
			{
				AVDebugWriteLine("Link Radeon Chill.");
				button_RadeonChill_Link().Opacity(1.00);
				slider_RadeonChill_Min().IsEnabled(false);
				radeon_Chill_Linked = true;
			}
			else
			{
				AVDebugWriteLine("Unlink Radeon Chill.");
				button_RadeonChill_Link().Opacity(0.50);
				slider_RadeonChill_Min().IsEnabled(true);
				radeon_Chill_Linked = false;
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

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				ADL_BOOST_SETTINGS adlSettings{};
				adlSettings.GlobalEnable = newValue;

				ADL_BOOST_NOTFICATION_REASON adlNotificationReason{};
				adlNotificationReason.GlobalEnableChanged = true;

				ADL_ERROR_REASON2 adlErrorReason;
				adl_Res0 = _ADL2_BOOST_SettingsX2_Set(adl_Context, adl_Gpu_AdapterIndex, adlSettings, adlNotificationReason, &adlErrorReason);

				//Set result
				newFailed = adl_Res0 != ADL_OK;

				//Notify change
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_BOOST_PROFILE, ADL_TRUE);
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"Bst_PFEnable", number_to_wstring(newValue));
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
					slider_RadeonBoost_MinResolution().IsEnabled(true);
					ShowNotification(L"Radeon Boost enabled");
					AVDebugWriteLine(L"Radeon Boost enabled");
				}
				else
				{
					slider_RadeonBoost_MinResolution().IsEnabled(false);
					ShowNotification(L"Radeon Boost disabled");
					AVDebugWriteLine(L"Radeon Boost disabled");
				}

				//Update current value
				graphicsSettingsCurrent.BoostEnabled.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::slider_RadeonBoost_MinResolution_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				ADL_BOOST_SETTINGS adlSettings{};
				adlSettings.GlobalMinRes = newValue;

				ADL_BOOST_NOTFICATION_REASON adlNotificationReason{};
				adlNotificationReason.GlobalMinResChanged = true;

				ADL_ERROR_REASON2 adlErrorReason;
				adl_Res0 = _ADL2_BOOST_SettingsX2_Set(adl_Context, adl_Gpu_AdapterIndex, adlSettings, adlNotificationReason, &adlErrorReason);

				//Set result
				newFailed = adl_Res0 != ADL_OK;

				//Notify change
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_BOOST_PROFILE, ADL_TRUE);
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"Bst_MaxScale", number_to_wstring(newValue));
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

				//Update current value
				graphicsSettingsCurrent.BoostMinResolution.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_RadeonImageSharpening1_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				ADL_RIS_SETTINGS adlSettings{};
				adlSettings.GlobalEnable = newValue;

				ADL_RIS_NOTFICATION_REASON adlNotificationReason{};
				adlNotificationReason.GlobalEnableChanged = true;

				adl_Res0 = _ADL2_RIS_Settings_Set(adl_Context, adl_Gpu_AdapterIndex, adlSettings, adlNotificationReason);

				//Set result
				newFailed = adl_Res0 != ADL_OK;

				//Notify change
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_USU_PROFILE, ADL_TRUE);
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"Ris_PFEnable", number_to_wstring(newValue));
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
					slider_RadeonImageSharpening1_Sharpening().IsEnabled(true);
					ShowNotification(L"Image Sharpening enabled");
					AVDebugWriteLine(L"Image Sharpening enabled");
				}
				else
				{
					slider_RadeonImageSharpening1_Sharpening().IsEnabled(false);
					ShowNotification(L"Image Sharpening disabled");
					AVDebugWriteLine(L"Image Sharpening disabled");
				}

				//Update current value
				graphicsSettingsCurrent.RisEnabled.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::slider_RadeonImageSharpening1_Sharpening_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValueInt = (int)e.NewValue();
			float newValueFloat = (float)e.NewValue();
			bool newFailed = true;

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				ADL_RIS_SETTINGS adlSettings{};
				adlSettings.GlobalSharpeningDegree = newValueInt;

				ADL_RIS_NOTFICATION_REASON adlNotificationReason{};
				adlNotificationReason.GlobalSharpeningDegreeChanged = true;

				adl_Res0 = _ADL2_RIS_Settings_Set(adl_Context, adl_Gpu_AdapterIndex, adlSettings, adlNotificationReason);

				//Set result
				newFailed = adl_Res0 != ADL_OK;

				//Notify change
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_USU_PROFILE, ADL_TRUE);
			}
			else
			{
				//Set setting
				float convertedValue = newValueFloat / 100;
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"Ris_SHDegree", float_to_wstring(convertedValue, 1));
			}

			//Show result
			if (newFailed)
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_RadeonImageSharpening1_Sharpening().Foreground(colorInvalid);
				ShowNotification(L"Failed setting Sharpening");
				AVDebugWriteLine(L"Failed setting Sharpening");
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_RadeonImageSharpening1_Sharpening().Foreground(colorValid);
				ShowNotification(L"Sharpening set to " + number_to_wstring(newValueInt));
				AVDebugWriteLine(L"Sharpening set to " << newValueInt);

				//Update current value
				graphicsSettingsCurrent.RisSharpeningDegree.Current = newValueInt;
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_RadeonImageSharpening2_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				ADL_RIS2_SETTINGS adlSettings{};
				adlSettings.GlobalEnable = newValue;

				ADL_RIS2_NOTIFICATION_REASON adlNotificationReason{};
				adlNotificationReason.GlobalEnableChanged = true;

				adl_Res0 = _ADL2_RIS_SettingsX2_Set(adl_Context, adl_Gpu_AdapterIndex, adlSettings, adlNotificationReason);

				//Set result
				newFailed = adl_Res0 != ADL_OK;

				//Notify change
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_USU2_PROFILE, ADL_TRUE);
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
					toggleswitch_RadeonImageSharpening2_Desktop().IsEnabled(true);
					slider_RadeonImageSharpening2_Sharpening().IsEnabled(true);
					ShowNotification(L"Image Sharpening enabled");
					AVDebugWriteLine(L"Image Sharpening enabled");
				}
				else
				{
					toggleswitch_RadeonImageSharpening2_Desktop().IsEnabled(false);
					slider_RadeonImageSharpening2_Sharpening().IsEnabled(false);
					ShowNotification(L"Image Sharpening disabled");
					AVDebugWriteLine(L"Image Sharpening disabled");
				}

				//Update current value
				graphicsSettingsCurrent.Ris2Enabled.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_RadeonImageSharpening2_Desktop_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Note: RIS2 registry states 0 = off / 1 = on / 2 = off + desktop / 3 = on + desktop

				//Set setting
				ADL_RIS2_SETTINGS adlSettings{};
				adlSettings.GlobalEnable = true;
				adlSettings.GlobalDesktop = newValue;

				ADL_RIS2_NOTIFICATION_REASON adlNotificationReason{};
				adlNotificationReason.GlobalEnableChanged = true;
				adlNotificationReason.GlobalDesktopChanged = true;

				adl_Res0 = _ADL2_RIS_SettingsX2_Set(adl_Context, adl_Gpu_AdapterIndex, adlSettings, adlNotificationReason);

				//Set result
				newFailed = adl_Res0 != ADL_OK;

				//Notify change
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_USU2_PROFILE, ADL_TRUE);
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

				//Update current value
				graphicsSettingsCurrent.Ris2DesktopEnabled.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::slider_RadeonImageSharpening2_Sharpening_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				ADL_RIS2_SETTINGS adlSettings{};
				adlSettings.GlobalSharpeningDegree = newValue;

				ADL_RIS2_NOTIFICATION_REASON adlNotificationReason{};
				adlNotificationReason.GlobalSharpeningDegreeChanged = true;

				adl_Res0 = _ADL2_RIS_SettingsX2_Set(adl_Context, adl_Gpu_AdapterIndex, adlSettings, adlNotificationReason);

				//Set result
				newFailed = adl_Res0 != ADL_OK;

				//Notify change
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_USU2_PROFILE, ADL_TRUE);
			}

			//Show result
			if (newFailed)
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_RadeonImageSharpening2_Sharpening().Foreground(colorInvalid);
				ShowNotification(L"Failed setting Sharpening");
				AVDebugWriteLine(L"Failed setting Sharpening");
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_RadeonImageSharpening2_Sharpening().Foreground(colorValid);
				ShowNotification(L"Sharpening set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Sharpening set to " << newValue);

				//Update current value
				graphicsSettingsCurrent.Ris2SharpeningDegree.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_AntiAliasingOverride_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check application type
			std::wstring convertedValue = newValue ? L"2" : L"1";
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "AntiAlias", convertedValue);
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"AntiAlias", convertedValue);
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling AA Override");
					AVDebugWriteLine(L"Failed enabling AA Override");
				}
				else
				{
					ShowNotification(L"Failed disabling AA Override");
					AVDebugWriteLine(L"Failed disabling AA Override");
				}
			}
			else
			{
				if (newValue)
				{
					combobox_AntiAliasingMethod().IsEnabled(true);
					combobox_AntiAliasingLevel().IsEnabled(true);
					toggleswitch_AntiAliasingEnhancedQuality().IsEnabled(true);
					ShowNotification(L"AA Override enabled");
					AVDebugWriteLine(L"AA Override enabled");
				}
				else
				{
					combobox_AntiAliasingMethod().IsEnabled(false);
					combobox_AntiAliasingLevel().IsEnabled(false);
					toggleswitch_AntiAliasingEnhancedQuality().IsEnabled(false);
					ShowNotification(L"AA Override disabled");
					AVDebugWriteLine(L"AA Override disabled");
				}

				//Update current value
				graphicsSettingsCurrent.AntiAliasingOverride.Current = newValue;
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
			int newValue = sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Enumeration index correction
			std::wstring setValueAsd = L"-1";
			std::wstring setValueAse = L"0";
			std::wstring setValueAstt = L"0";
			if (newValue == 0)
			{
				//Multisampling
				setValueAsd = L"-1";
				setValueAse = L"0";
				setValueAstt = L"0";
			}
			else if (newValue == 1)
			{
				//Adaptive Multisampling
				setValueAsd = L"1";
				setValueAse = L"0";
				setValueAstt = L"1";
			}
			else if (newValue == 2)
			{
				//Supersampling
				setValueAsd = L"1";
				setValueAse = L"1";
				setValueAstt = L"1";
			}

			//Set setting
			if (AdlAppSelectedGet().value().get().Global)
			{
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "ASD", setValueAsd);
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "ASE", setValueAse);
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "ASTT", setValueAstt);
			}
			else
			{
				std::vector<AdlAppProperty> adlAppProperties{};

				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"ASD";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = setValueAsd;
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);

				AdlAppProperty adlAppProperty1{};
				adlAppProperty1.Name = L"ASE";
				AdlAppPropertyValue adlAppPropertyValue1{};
				adlAppPropertyValue1.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue1.Value = setValueAse;
				adlAppProperty1.Values = { adlAppPropertyValue1 };
				adlAppProperties.push_back(adlAppProperty1);

				AdlAppProperty adlAppProperty2{};
				adlAppProperty2.Name = L"ASTT";
				AdlAppPropertyValue adlAppPropertyValue2{};
				adlAppPropertyValue2.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue2.Value = setValueAstt;
				adlAppProperty2.Values = { adlAppPropertyValue2 };
				adlAppProperties.push_back(adlAppProperty2);

				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), adlAppProperties, false);
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

				//Update current value
				graphicsSettingsCurrent.AntiAliasingMethod.Current = newValue;
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
			auto newValue = sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Enumeration index correction
			std::wstring setValue = L"2";
			if (newValue == 0)
			{
				setValue = L"2";
			}
			else if (newValue == 1)
			{
				setValue = L"4";
			}
			else if (newValue == 2)
			{
				setValue = L"8";
			}

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "AntiAliasSamples", setValue);
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"AntiAliasSmpls", setValue);
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

				//Update current value
				graphicsSettingsCurrent.AntiAliasingLevel.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_AntiAliasingEnhancedQuality_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//DriverBug#3

			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "EQAA", number_to_wstring(newValue));
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"EQAA", number_to_wstring(newValue));
			}

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling EQAA");
					AVDebugWriteLine(L"Failed enabling EQAA");
				}
				else
				{
					ShowNotification(L"Failed disabling EQAA");
					AVDebugWriteLine(L"Failed disabling EQAA");
				}
			}
			else
			{
				if (newValue)
				{
					ShowNotification(L"EQAA enabled");
					AVDebugWriteLine(L"EQAA enabled");
				}
				else
				{
					ShowNotification(L"EQAA disabled");
					AVDebugWriteLine(L"EQAA disabled");
				}

				//Update current value
				graphicsSettingsCurrent.AntiAliasingEnhancedQuality.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_MorphologicalAntiAliasing_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "MLF", number_to_wstring(newValue));
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"MLF", number_to_wstring(newValue));
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

				//Update current value
				graphicsSettingsCurrent.AntiAliasingMorphological.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_AnisotropicTextureFiltering_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//DriverBug#4

			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Enumeration index correction
			std::wstring setValue = L"0";
			if (newValue == 0)
			{
				setValue = L"0";
			}
			else if (newValue == 1)
			{
				setValue = L"2";
			}
			else if (newValue == 2)
			{
				setValue = L"4";
			}
			else if (newValue == 3)
			{
				setValue = L"8";
			}
			else if (newValue == 4)
			{
				setValue = L"16";
			}

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "AnisoDegree", setValue);
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"AnisoDegree", setValue);
			}

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting Anisotropic");
				AVDebugWriteLine(L"Failed setting Anisotropic");
			}
			else
			{
				ShowNotification(L"Anisotropic set to " + ADLX_ANISOTROPIC_FILTERING_LEVEL_STRING[newValue]);
				AVDebugWriteLine(L"Anisotropic set to " << newValue);

				//Update current value
				graphicsSettingsCurrent.AnisotropicOverride.Current = newValue;
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
			int newValue = sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "Tessellation_OPTION", number_to_wstring(newValue));
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"Tessellation_OP", number_to_wstring(newValue));
			}

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting Tessellation mode");
				AVDebugWriteLine(L"Failed setting Tessellation mode");
			}
			else
			{
				//Check if setting is enabled
				if (newValue != 2)
				{
					combobox_Tessellation_Level().IsEnabled(false);
				}
				else
				{
					combobox_Tessellation_Level().IsEnabled(true);
				}

				ShowNotification(L"Tessellation mode set to " + ADLX_TESSELLATION_MODE_STRING[newValue]);
				AVDebugWriteLine(L"Tessellation mode set to " << newValue);

				//Update current value
				graphicsSettingsCurrent.TessellationMode.Current = newValue;
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
			std::wstring setValue = L"1";
			if (newValue == 0)
			{
				setValue = L"1";
			}
			else if (newValue == 1)
			{
				setValue = L"2";
			}
			else if (newValue == 2)
			{
				setValue = L"4";
			}
			else if (newValue == 3)
			{
				setValue = L"6";
			}
			else if (newValue == 4)
			{
				setValue = L"8";
			}
			else if (newValue == 5)
			{
				setValue = L"16";
			}
			else if (newValue == 6)
			{
				setValue = L"32";
			}
			else if (newValue == 7)
			{
				setValue = L"64";
			}

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "Tessellation", setValue);
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"Tessellation", setValue);
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

				//Update current value
				graphicsSettingsCurrent.TessellationLevel.Current = newValue;
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

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "EnableTripleBuffering", number_to_wstring(newValue));
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"EnableTrplBffr", number_to_wstring(newValue));
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

				//Update current value
				graphicsSettingsCurrent.OpenGLTripleBuffering.Current = newValue;
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

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "TFQ", number_to_wstring(newValue));
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"TFQ", number_to_wstring(newValue));
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

				//Update current value
				graphicsSettingsCurrent.TextureFilteringQuality.Current = newValue;
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

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "SurfaceFormatReplacements", number_to_wstring(newValue));
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"SrfcFrmtRplcmnt", number_to_wstring(newValue));
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

				//Update current value
				graphicsSettingsCurrent.SurfaceFormatOptimization.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_Frtc_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Note: FRTC Pro works in windowed mode when using workstation drivers but not with gaming drivers.

			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				if (newValue)
				{
					//Get current slider value
					auto sliderValue = slider_Frtc_FrameRateTarget().Value();

					ADLFPSSettingsInput adlSettings{};
					adlSettings.bGlobalSettings = true;
					adlSettings.ulACFPSCurrent = sliderValue;
					adlSettings.ulDCFPSCurrent = sliderValue;
					adl_Res0 = _ADL2_FPS_Settings_Set(adl_Context, adl_Gpu_AdapterIndex, adlSettings);
				}
				else
				{
					ADLFPSSettingsInput adlSettings{};
					adlSettings.bGlobalSettings = true;
					adlSettings.ulACFPSCurrent = 0;
					adlSettings.ulDCFPSCurrent = 0;
					adl_Res0 = _ADL2_FPS_Settings_Set(adl_Context, adl_Gpu_AdapterIndex, adlSettings);
				}

				//Set result
				newFailed = adl_Res0 != ADL_OK;
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
					slider_Frtc_FrameRateTarget().IsEnabled(true);
					ShowNotification(L"FRTC enabled");
					AVDebugWriteLine(L"FRTC enabled");
				}
				else
				{
					slider_Frtc_FrameRateTarget().IsEnabled(false);
					ShowNotification(L"FRTC disabled");
					AVDebugWriteLine(L"FRTC disabled");
				}

				//Update current value
				graphicsSettingsCurrent.FrtcEnabled.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::slider_Frtc_FrameRateTarget_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				ADLFPSSettingsInput input{};
				input.bGlobalSettings = true;
				input.ulACFPSCurrent = newValue;
				input.ulDCFPSCurrent = newValue;
				adl_Res0 = _ADL2_FPS_Settings_Set(adl_Context, adl_Gpu_AdapterIndex, input);

				//Set result
				newFailed = adl_Res0 != ADL_OK;
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

				//Update current value
				graphicsSettingsCurrent.FrtcFrameRateTarget.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_OpenGL10BitPixelFormat_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Enumeration index correction
				int setValue = 1;
				if (newValue)
				{
					setValue = 1;
				}
				else
				{
					setValue = 2;
				}

				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "", "KMD_10BitMode", setValue);
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "", "Gmx_Enable10BitMode", setValue);
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

				//Update current value
				graphicsSettingsCurrent.OpenGL10BitPixelFormat.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_FsrOtaUpdates_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Fix check if ADL2_CloudProfile_DLL_Get is used to trigger update or get dll path.

			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Note: AMD Adrenalin also changes the FsrOvrDLLPath to the selected value.

			//Check application type
			if (AdlAppSelectedGet().value().get().Global)
			{
				//Set setting
				newFailed = !AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "FsrOtaIndex", number_to_wstring(newValue));
			}
			else
			{
				//Set setting
				newFailed = !AdlAppPropertyUpdate(AdlAppSelectedGet().value(), gpuUniqueIdentifierHex, L"FsrOtaIndex", number_to_wstring(newValue));
			}

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed setting FSR OTA Updates");
				AVDebugWriteLine(L"Failed setting FSR OTA Updates");
			}
			else
			{
				//Set result
				ShowNotification(L"FSR OTA Updates set to " + REGISTRY_FSR_OTA_CONTROL_STRING[newValue]);
				AVDebugWriteLine(L"FSR OTA Updates set to " << newValue);

				//Update current value
				graphicsSettingsCurrent.FsrOtaIndex.Current = newValue;
			}
		}
		catch (...) {}
	}
}