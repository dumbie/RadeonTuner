#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::fire_and_forget MainPage::button_CustomResolution_ShowHide_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			bool manageVisible = grid_Overlay_CustomResolution().Visibility() == Visibility::Visible;
			if (manageVisible)
			{
				//Hide Custom Resolution manage overlay
				grid_Overlay_CustomResolution().Visibility(Visibility::Collapsed);
				AVDebugWriteLine(L"Closed Custom Resolution manage overlay");
			}
			else
			{
				//Show Custom Resolution manage overlay
				grid_Overlay_CustomResolution().Visibility(Visibility::Visible);
				AVDebugWriteLine(L"Opened Custom Resolution manage overlay");

				//Get current display mode
				int numModes = -1;
				ADLMode* adlModeCurrent{};
				adl_Res0 = _ADL2_Display_Modes_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &numModes, &adlModeCurrent);
				if (adl_Res0 != ADL_OK)
				{
					AVDebugWriteLine(L"Failed getting current display mode.");
					co_return;
				}

				//Disable custom resolution events
				disable_saving_customresolution = true;

				//Set current values for custom resolution
				textbox_CustomResolution_Width().Text(number_to_wstring(adlModeCurrent->iXRes));
				textbox_CustomResolution_Height().Text(number_to_wstring(adlModeCurrent->iYRes));
				textbox_CustomResolution_RefreshRate().Text(float_to_wstring(adlModeCurrent->fRefreshRate, 0));
				combobox_CustomResolution_Presentation().SelectedIndex(0);
				combobox_CustomResolution_TimingStandard().SelectedIndex(2);

				//Calculate and update timing variable
				DisplayModeInfo_Calculate_Timings();

				//Enable custom resolution events
				co_await AsyncTaskDelay(100, AppVariables::App.GetDispatcher());
				disable_saving_customresolution = false;
			}
		}
		catch (...) {}
	}

	void MainPage::button_Overlay_CustomResolution_Close_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Hide Custom Resolution manage overlay
			grid_Overlay_CustomResolution().Visibility(Visibility::Collapsed);
			AVDebugWriteLine(L"Closed Custom Resolution manage overlay");
		}
		catch (...) {}
	}

	winrt::fire_and_forget MainPage::button_CustomResolution_Remove_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Fix when there are two custom resolutions and the one you don't remove is not compatible you may end up with a black (no signal) screen.
			//Example: When removing 110Hz that works and 140Hz stays but is incompatible, Windows switches to it when display default refresh rate is 120Hz.

			//Set ADL display identifier
			ADLDisplayID displayID{};
			displayID.iDisplayLogicalAdapterIndex = adl_Display_AdapterIndex;
			displayID.iDisplayLogicalIndex = adl_Display_DisplayIndex;

			//Get custom resolutions list
			int numInfoList = -1;
			AVFin<ADLDisplayModeInfoX2*> modeInfoList = AVFin<ADLDisplayModeInfoX2*>(AVFinMethod::FreeMarshal);
			adl_Res0 = _ADL2_Display_ModeTimingOverrideListX3_Get(adl_Context, displayID.iDisplayLogicalAdapterIndex, displayID, &numInfoList, &modeInfoList.Get());

			//Check custom resolutions list
			if (adl_Res0 != ADL_OK)
			{
				//Show notification
				ShowNotification(L"Failed getting custom resolutions");
				AVDebugWriteLine(L"Failed getting custom resolutions");
				co_return;
			}

			if (numInfoList <= 0)
			{
				//Show notification
				ShowNotification(L"No custom resolution set");
				AVDebugWriteLine(L"No custom resolution set");
				co_return;
			}

			//List all custom resolutions
			std::vector<std::wstring> messageAnswers{};
			for (int i = 0; i < numInfoList; i++)
			{
				ADLDisplayModeInfoX2 modeInfoX2 = modeInfoList.Get()[i];
				std::wstring resolutionString = number_to_wstring(modeInfoX2.iPelsWidth) + L"x" + number_to_wstring(modeInfoX2.iPelsHeight) + L" @ " + number_to_wstring(modeInfoX2.iRefreshRate) + L"Hz";
				messageAnswers.push_back(resolutionString);
			}

			//Add cancel option
			messageAnswers.push_back(L"Cancel");

			//Show selection prompt
			int messageResult = co_await ShowMessageBox(L"Select custom resolution", L"Select the custom resolution you want to remove.", messageAnswers);

			//Check if cancelled
			if (messageResult == (messageAnswers.size() - 1))
			{
				AVDebugWriteLine(L"Cancelled custom resolution removal.");
				co_return;
			}

			//Get selected custom resolution
			ADLDisplayModeInfoX2 infoMode = modeInfoList.Get()[messageResult];

			//Delete custom resolution
			CustomResolution_Remove(adl_Display_AdapterIndex, adl_Display_DisplayIndex, infoMode);
		}
		catch (...)
		{
			//Show notification
			ShowNotification(L"Failed removing custom resolution");
			AVDebugWriteLine(L"Failed removing custom resolution (Exception)");
		}
	}

	void MainPage::button_Overlay_CustomResolution_Create_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Create custom resolution
			CustomResolution_Create(adl_Display_AdapterIndex, adl_Display_DisplayIndex, displayCustomModeInfo);
		}
		catch (...)
		{
			//Show notification
			ShowNotification(L"Failed creating custom resolution");
			AVDebugWriteLine(L"Failed creating custom resolution (Exception)");
		}
	}

	winrt::fire_and_forget MainPage::combobox_CustomResolution_TimingStandard_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving_customresolution) { co_return; }

			//Disable custom resolution events
			disable_saving_customresolution = true;

			//Calculate and update timing variable
			DisplayModeInfo_Calculate_Timings();

			//Enable custom resolution events
			co_await AsyncTaskDelay(100, AppVariables::App.GetDispatcher());
			disable_saving_customresolution = false;
		}
		catch (...) {}
	}

	winrt::fire_and_forget MainPage::textbox_CustomResolution_Resolution_TextChanged(IInspectable const& sender, TextChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving_customresolution) { co_return; }

			//Disable custom resolution events
			disable_saving_customresolution = true;

			//Calculate and update timing variable
			DisplayModeInfo_Calculate_Timings();

			//Enable custom resolution events
			co_await AsyncTaskDelay(100, AppVariables::App.GetDispatcher());
			disable_saving_customresolution = false;
		}
		catch (...) {}
	}

	winrt::fire_and_forget MainPage::textbox_CustomResolution_RefreshRate_TextChanged(IInspectable const& sender, TextChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving_customresolution) { co_return; }

			//Disable custom resolution events
			disable_saving_customresolution = true;

			//Calculate and update timing variable
			DisplayModeInfo_Calculate_Timings();

			//Enable custom resolution events
			co_await AsyncTaskDelay(100, AppVariables::App.GetDispatcher());
			disable_saving_customresolution = false;

			//Get setting value
			std::wstring newValueString = textbox_CustomResolution_RefreshRate().Text().c_str();
			int newValueInt = wstring_to_int(newValueString);

			//Update custom mode values
			displayCustomModeInfo.iRefreshRate = newValueInt;

			AVDebugWriteLine(L"Custom resolution refresh rate updated: " << displayCustomModeInfo.iRefreshRate);
		}
		catch (...) {}
	}

	void MainPage::combobox_CustomResolution_Presentation_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving_customresolution) { return; }

			//Get setting value
			auto newSender = sender.as<ComboBox>();
			int newValue = newSender.SelectedIndex();

			//Update custom mode values
			if (newValue == 0)
			{
				//Progressive
				displayCustomModeInfo.sDetailedTiming.sTimingFlags &= ~ADL_DL_TIMINGFLAG_INTERLACED;
				displayCustomModeInfo.sDetailedTiming.sTimingFlags &= ~ADL_DL_TIMINGFLAG_DOUBLE_SCAN;
			}
			else if (newValue == 1)
			{
				//Interlaced
				displayCustomModeInfo.sDetailedTiming.sTimingFlags &= ~ADL_DL_TIMINGFLAG_DOUBLE_SCAN;
				displayCustomModeInfo.sDetailedTiming.sTimingFlags |= ADL_DL_TIMINGFLAG_INTERLACED;
			}
			else
			{
				//Double Scan
				displayCustomModeInfo.sDetailedTiming.sTimingFlags &= ~ADL_DL_TIMINGFLAG_INTERLACED;
				displayCustomModeInfo.sDetailedTiming.sTimingFlags |= ADL_DL_TIMINGFLAG_DOUBLE_SCAN;
			}

			AVDebugWriteLine(L"Custom resolution presentation updated: " << displayCustomModeInfo.sDetailedTiming.sTimingFlags);
		}
		catch (...) {}
	}

	void MainPage::textbox_CustomResolution_PixelClock_TextChanged(IInspectable const& sender, TextChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving_customresolution) { return; }

			//Get setting value
			auto newSender = sender.as<TextBox>();
			std::wstring newValueString = newSender.Text().c_str();
			int newValueInt = wstring_to_int(newValueString);

			//Update custom mode values
			displayCustomModeInfo.sDetailedTiming.sPixelClock = newValueInt;

			//Recalculate and update interface
			DisplayModeInfo_ToUI(displayCustomModeInfo, true);

			AVDebugWriteLine(L"Custom resolution pixel clock updated: " << displayCustomModeInfo.sDetailedTiming.sPixelClock);
		}
		catch (...) {}
	}

	void MainPage::textbox_TimingTotal_TextChanged(IInspectable const& sender, TextChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving_customresolution) { return; }

			//Get setting values
			std::wstring newValueStringHorizontal = textbox_TimingTotal_Horizontal().Text().c_str();
			std::wstring newValueStringVertical = textbox_TimingTotal_Vertical().Text().c_str();
			int newValueIntHorizontal = wstring_to_int(newValueStringHorizontal);
			int newValueIntVertical = wstring_to_int(newValueStringVertical);

			//Update custom mode values
			displayCustomModeInfo.sDetailedTiming.sHTotal = newValueIntHorizontal;
			displayCustomModeInfo.sDetailedTiming.sVTotal = newValueIntVertical;

			//Recalculate and update interface
			DisplayModeInfo_ToUI(displayCustomModeInfo, true);

			AVDebugWriteLine(L"Custom resolution total updated: " << displayCustomModeInfo.sDetailedTiming.sHTotal << L" / " << displayCustomModeInfo.sDetailedTiming.sVTotal);
		}
		catch (...) {}
	}

	void MainPage::textbox_TimingFrontPorch_TextChanged(IInspectable const& sender, TextChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving_customresolution) { return; }

			//Get setting values
			std::wstring newValueStringHorizontal = textbox_TimingFrontPorch_Horizontal().Text().c_str();
			std::wstring newValueStringVertical = textbox_TimingFrontPorch_Vertical().Text().c_str();
			int newValueIntHorizontal = wstring_to_int(newValueStringHorizontal);
			int newValueIntVertical = wstring_to_int(newValueStringVertical);

			//Update custom mode values
			displayCustomModeInfo.sDetailedTiming.sHSyncStart = displayCustomModeInfo.sDetailedTiming.sHDisplay + newValueIntHorizontal;
			displayCustomModeInfo.sDetailedTiming.sVSyncStart = displayCustomModeInfo.sDetailedTiming.sVDisplay + newValueIntVertical;

			AVDebugWriteLine(L"Custom resolution front porch updated: " << displayCustomModeInfo.sDetailedTiming.sHSyncStart << L" / " << displayCustomModeInfo.sDetailedTiming.sVSyncStart);
		}
		catch (...) {}
	}

	void MainPage::textbox_TimingSyncWidth_TextChanged(IInspectable const& sender, TextChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving_customresolution) { return; }

			//Get setting values
			std::wstring newValueStringHorizontal = textbox_TimingSyncWidth_Horizontal().Text().c_str();
			std::wstring newValueStringVertical = textbox_TimingSyncWidth_Vertical().Text().c_str();
			int newValueIntHorizontal = wstring_to_int(newValueStringHorizontal);
			int newValueIntVertical = wstring_to_int(newValueStringVertical);

			//Update custom mode values
			displayCustomModeInfo.sDetailedTiming.sHSyncWidth = newValueIntHorizontal;
			displayCustomModeInfo.sDetailedTiming.sVSyncWidth = newValueIntVertical;

			AVDebugWriteLine(L"Custom resolution sync width updated: " << displayCustomModeInfo.sDetailedTiming.sHSyncWidth << L" / " << displayCustomModeInfo.sDetailedTiming.sVSyncWidth);
		}
		catch (...) {}
	}

	void MainPage::combobox_TimingPolarity_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving_customresolution) { return; }

			//Get setting value
			int newValueHorizontal = combobox_TimingPolarity_Horizontal().SelectedIndex();
			int newValueVertical = combobox_TimingPolarity_Vertical().SelectedIndex();

			//Update custom mode values
			if (newValueHorizontal == 0)
			{
				//Positive
				displayCustomModeInfo.sDetailedTiming.sTimingFlags &= ~ADL_DL_TIMINGFLAG_H_SYNC_POLARITY;
			}
			else
			{
				//Negative
				displayCustomModeInfo.sDetailedTiming.sTimingFlags |= ADL_DL_TIMINGFLAG_H_SYNC_POLARITY;
			}

			if (newValueVertical == 0)
			{
				//Positive
				displayCustomModeInfo.sDetailedTiming.sTimingFlags &= ~ADL_DL_TIMINGFLAG_V_SYNC_POLARITY;
			}
			else
			{
				//Negative
				displayCustomModeInfo.sDetailedTiming.sTimingFlags |= ADL_DL_TIMINGFLAG_V_SYNC_POLARITY;
			}

			AVDebugWriteLine(L"Custom resolution polarity updated: " << displayCustomModeInfo.sDetailedTiming.sTimingFlags);
		}
		catch (...) {}
	}
}