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
			//Show file dialog
			bool addResult = AdlAppInterfaceAddFile();

			//Check result
			if (addResult)
			{
				//Reload applications
				AdlAppInterfaceListLoad();

				//Select application
				combobox_AppSelect().SelectedIndex(0);

				//Show notification
				ShowNotification(L"Application added");
				AVDebugWriteLine(L"Application added");
			}
			else
			{
				ShowNotification(L"Application not added");
				AVDebugWriteLine(L"Application not added");
			}
		}
		catch (...) {}
	}

	void MainPage::button_Graphics_AddProcess_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Show process dialog
			bool addResult = AdlAppInterfaceAddProcess();

			//Check result
			if (addResult)
			{
				//Reload applications
				AdlAppInterfaceListLoad();

				//Select application
				combobox_AppSelect().SelectedIndex(0);

				//Show notification
				ShowNotification(L"Application added");
				AVDebugWriteLine(L"Application added");
			}
			else
			{
				ShowNotification(L"Application not added");
				AVDebugWriteLine(L"Application not added");
			}
		}
		catch (...) {}
	}

	void MainPage::button_Graphics_Remove_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Remove application and profile
			bool removeResult = AdlAppRemove(adl_AppSelected());

			//Check result
			if (removeResult)
			{
				//Reload applications
				AdlAppInterfaceListLoad();

				//Select application
				combobox_AppSelect().SelectedIndex(0);

				//Show notification
				ShowNotification(L"Application removed");
				AVDebugWriteLine(L"Application removed");
			}
			else
			{
				//Show notification
				ShowNotification(L"Application not removed");
				AVDebugWriteLine(L"Application not removed");
			}
		}
		catch (...) {}
	}

	void MainPage::button_Graphics_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Reset graphics settings
			bool resetResult = AdlxValuesResetGraphics();

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

	void MainPage::button_Graphics_Unlock_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Unlock application features
			bool unlockResult = AdlAppUnlock(adl_AppSelected());

			//Check result
			if (unlockResult)
			{
				//Show notification
				ShowNotification(L"Application features unlocked");
				AVDebugWriteLine(L"Application features unlocked");
			}
			else
			{
				//Show notification
				ShowNotification(L"Application not unlocked");
				AVDebugWriteLine(L"Application not unlocked");
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

			//Set setting
			newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), gpuUniqueIdentifierHex, L"FsrOverride", number_to_wstring(newValue));

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

			//Set setting
			newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), gpuUniqueIdentifierHex, L"MlfiOverride", number_to_wstring(newValue));

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

			//Set setting
			newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), gpuUniqueIdentifierHex, L"Dlg_PFEnable", number_to_wstring(newValue));

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

			//Set setting
			newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), gpuUniqueIdentifierHex, L"TurboSync", number_to_wstring(newValue));

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
					//combobox_VerticalRefresh().IsEnabled(false);
					ShowNotification(L"Enhanced Sync enabled");
					AVDebugWriteLine(L"Enhanced Sync enabled");
				}
				else
				{
					//combobox_VerticalRefresh().IsEnabled(true);
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

			//Set setting
			newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), gpuUniqueIdentifierHex, L"VSyncControl", number_to_wstring(newValue));

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

			//Set setting
			newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), gpuUniqueIdentifierHex, L"Chil_PFEnable", number_to_wstring(newValue));

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

			//Set setting
			newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), gpuUniqueIdentifierHex, L"Chil_MinFRate", number_to_wstring(newValue));

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

			//Set setting
			newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), gpuUniqueIdentifierHex, L"Chil_MaxFRate", number_to_wstring(newValue));

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

			//Set setting
			newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), gpuUniqueIdentifierHex, L"Bst_PFEnable", number_to_wstring(newValue));

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

			//Set setting
			newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), gpuUniqueIdentifierHex, L"Bst_MaxScale", number_to_wstring(newValue));

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

			//Set setting
			newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), gpuUniqueIdentifierHex, L"Ris_PFEnable", number_to_wstring(newValue));

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
					slider_RadeonImageSharpening_Sharpening().IsEnabled(true);
					ShowNotification(L"Image Sharpening enabled");
					AVDebugWriteLine(L"Image Sharpening enabled");
				}
				else
				{
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

			//Set setting
			float convertedValue = (float)newValue / 100;
			newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), gpuUniqueIdentifierHex, L"Ris_SHDegree", float_to_wstring(convertedValue, 1));

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

			//Set setting
			std::wstring convertedValue = newValue ? L"2" : L"1";
			newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), gpuUniqueIdentifierHex, L"AntiAlias", convertedValue);

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
					toggleswitch_EQAA().IsEnabled(true);
					ShowNotification(L"AA Override enabled");
					AVDebugWriteLine(L"AA Override enabled");
				}
				else
				{
					combobox_AntiAliasingMethod().IsEnabled(false);
					combobox_AntiAliasingLevel().IsEnabled(false);
					toggleswitch_EQAA().IsEnabled(false);
					ShowNotification(L"AA Override disabled");
					AVDebugWriteLine(L"AA Override disabled");
				}
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

			//Set setting
			if (newValue == ADLX_ANTI_ALIASING_METHOD::AA_METHOD_MULTISAMPLING)
			{
				std::vector<AdlAppPropertyValue> adlAppPropertyValues{};
				AdlAppPropertyValue adlAppPropertyValue1{};
				adlAppPropertyValue1.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue1.Name = L"ASD";
				adlAppPropertyValue1.Value = L"-1";
				adlAppPropertyValues.push_back(adlAppPropertyValue1);

				AdlAppPropertyValue adlAppPropertyValue2{};
				adlAppPropertyValue2.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue2.Name = L"ASE";
				adlAppPropertyValue2.Value = L"0";
				adlAppPropertyValues.push_back(adlAppPropertyValue2);

				AdlAppPropertyValue adlAppPropertyValue3{};
				adlAppPropertyValue3.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue3.Name = L"ASTT";
				adlAppPropertyValue3.Value = L"0";
				adlAppPropertyValues.push_back(adlAppPropertyValue3);

				newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), adlAppPropertyValues);
			}
			else if (newValue == ADLX_ANTI_ALIASING_METHOD::AA_METHOD_ADAPTIVE_MULTISAMPLING)
			{
				std::vector<AdlAppPropertyValue> adlAppPropertyValues{};
				AdlAppPropertyValue adlAppPropertyValue1{};
				adlAppPropertyValue1.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue1.Name = L"ASD";
				adlAppPropertyValue1.Value = L"1";
				adlAppPropertyValues.push_back(adlAppPropertyValue1);

				AdlAppPropertyValue adlAppPropertyValue2{};
				adlAppPropertyValue2.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue2.Name = L"ASE";
				adlAppPropertyValue2.Value = L"0";
				adlAppPropertyValues.push_back(adlAppPropertyValue2);

				AdlAppPropertyValue adlAppPropertyValue3{};
				adlAppPropertyValue3.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue3.Name = L"ASTT";
				adlAppPropertyValue3.Value = L"1";
				adlAppPropertyValues.push_back(adlAppPropertyValue3);

				newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), adlAppPropertyValues);
			}
			else if (newValue == ADLX_ANTI_ALIASING_METHOD::AA_METHOD_SUPERSAMPLING)
			{
				std::vector<AdlAppPropertyValue> adlAppPropertyValues{};
				AdlAppPropertyValue adlAppPropertyValue1{};
				adlAppPropertyValue1.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue1.Name = L"ASD";
				adlAppPropertyValue1.Value = L"1";
				adlAppPropertyValues.push_back(adlAppPropertyValue1);

				AdlAppPropertyValue adlAppPropertyValue2{};
				adlAppPropertyValue2.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue2.Name = L"ASE";
				adlAppPropertyValue2.Value = L"1";
				adlAppPropertyValues.push_back(adlAppPropertyValue2);

				AdlAppPropertyValue adlAppPropertyValue3{};
				adlAppPropertyValue3.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue3.Name = L"ASTT";
				adlAppPropertyValue3.Value = L"1";
				adlAppPropertyValues.push_back(adlAppPropertyValue3);

				newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), adlAppPropertyValues);
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
			auto newValue = sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Enumeration index correction
			std::wstring setValue = L"";
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

			//Set setting
			newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), gpuUniqueIdentifierHex, L"AntiAliasSmpls", setValue);

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

	void MainPage::toggleswitch_EQAA_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Set setting
			newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), gpuUniqueIdentifierHex, L"EQAA", number_to_wstring(newValue));

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

			//Set setting
			newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), gpuUniqueIdentifierHex, L"MLF", number_to_wstring(newValue));

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

	void MainPage::combobox_AnisotropicTextureFiltering_Level_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
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
				setValue = 0;
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
				setValue = 8;
			}
			else if (newValue == 4)
			{
				setValue = 16;
			}

			//Set setting
			newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), gpuUniqueIdentifierHex, L"AnisoDegree", number_to_wstring(setValue));

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

			//Set setting
			newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), gpuUniqueIdentifierHex, L"Tessellation_OP", number_to_wstring(newValue));

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

			//Set setting
			newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), gpuUniqueIdentifierHex, L"Tessellation", number_to_wstring(setValue));

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

			//Set setting
			newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), gpuUniqueIdentifierHex, L"EnableTrplBffr", number_to_wstring(newValue));

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

	void MainPage::combobox_TextureFilteringQuality_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newValue = sender.as<ComboBox>().SelectedIndex();
			bool newFailed = true;

			//Set setting
			newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), gpuUniqueIdentifierHex, L"TFQ", number_to_wstring(newValue));

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

			//Set setting
			newFailed = !AdlAppPropertyUpdate(adl_AppSelected(), gpuUniqueIdentifierHex, L"SrfcFrmtRplcmnt", number_to_wstring(newValue));

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
}