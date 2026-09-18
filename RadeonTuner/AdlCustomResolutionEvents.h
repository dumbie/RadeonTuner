#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::fire_and_forget MainPage::button_CustomResolution_Create_Click(IInspectable const& sender, RoutedEventArgs const& e)
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
				co_await AsyncTaskDelay(300, AppVariables::App.GetDispatcher());
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

	void MainPage::textbox_CustomResolution_Height_TextChanged(IInspectable const& sender, TextChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving_customresolution) { return; }

			//Calculate and update timing variable
			DisplayModeInfo_Calculate_Timings();
		}
		catch (...) {}
	}

	void MainPage::textbox_CustomResolution_Width_TextChanged(IInspectable const& sender, TextChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving_customresolution) { return; }

			//Calculate and update timing variable
			DisplayModeInfo_Calculate_Timings();
		}
		catch (...) {}
	}

	void MainPage::textbox_CustomResolution_RefreshRate_TextChanged(IInspectable const& sender, TextChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving_customresolution) { return; }

			//Calculate and update timing variable
			DisplayModeInfo_Calculate_Timings();
		}
		catch (...) {}
	}

	void MainPage::combobox_CustomResolution_Presentation_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving_customresolution) { return; }

			//Calculate and update timing variable
			DisplayModeInfo_Calculate_Timings();
		}
		catch (...) {}
	}

	void MainPage::combobox_CustomResolution_TimingStandard_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving_customresolution) { return; }

			//Calculate and update timing variable
			DisplayModeInfo_Calculate_Timings();
		}
		catch (...) {}
	}

	winrt::fire_and_forget MainPage::button_CustomResolution_Remove_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
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
				ADLDisplayModeInfoX2 modeInfo = modeInfoList.Get()[i];
				std::wstring resolutionString = number_to_wstring(modeInfo.iPelsWidth) + L"x" + number_to_wstring(modeInfo.iPelsHeight) + L" @ " + number_to_wstring(modeInfo.iRefreshRate) + L"Hz";
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
			CustomResolution_Delete(adl_Display_AdapterIndex, adl_Display_DisplayIndex, infoMode);
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
}