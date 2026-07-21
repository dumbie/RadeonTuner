#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::DisplaySettings_Resolution_Revert()
	{
		try
		{
			std::wstring resolutionString = number_to_wstring(displayResolutionRevertWidth) + L"x" + number_to_wstring(displayResolutionRevertHeight) + L" @ " + float_to_wstring(displayResolutionRevertRefreshRate, 2) + L" Hz";
			AVDebugWriteLine(L"Display reverting to " << resolutionString);

			//Get current display mode
			int numModes = -1;
			ADLMode* adlModeCurrent{};
			adl_Res0 = _ADL2_Display_Modes_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &numModes, &adlModeCurrent);
			if (adl_Res0 != ADL_OK)
			{
				AVDebugWriteLine(L"Failed getting current display mode.");
				return;
			}

			//Update display mode
			adlModeCurrent->iXRes = displayResolutionRevertWidth;
			adlModeCurrent->iYRes = displayResolutionRevertHeight;
			adlModeCurrent->fRefreshRate = displayResolutionRevertRefreshRate;
			adlModeCurrent->iOrientation = displayResolutionRevertOrientation;

			//Set setting
			adl_Res0 = _ADL2_Display_Modes_Set(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, 1, adlModeCurrent);

			//Set result
			bool newFailed = adl_Res0 != ADL_OK;

			//Show result
			if (newFailed)
			{
				ShowNotification(L"Failed reverting display");
				AVDebugWriteLine(L"Failed reverting display");
			}
			else
			{
				ShowNotification(L"Display reverted to " + resolutionString);
				AVDebugWriteLine(L"Display reverted to " << resolutionString);

				disable_saving = true;
				//Select current display values
				DisplayList_SelectCurrent_Values();
				disable_saving = false;
			}
		}
		catch (...) {}
	}

	void MainPage::DisplaySettings_Confirm_Resolution_Start()
	{
		try
		{
			//Reset switch time
			displayResolutionSwitchTimeSec = 15;

			//Show overlay
			grid_Main().IsHitTestVisible(false);
			grid_Overlay_ConfirmResolution().Visibility(Visibility::Visible);
			textblock_Overlay_ConfirmResolution_SubText().Text(L"Reverting in " + number_to_wstring(displayResolutionSwitchTimeSec) + L" seconds...");

			//Resolution switch timer tick
			std::function<void(IInspectable const& sender, IInspectable const& e)> tickFunction = [&](auto, auto)
				{
					try
					{
						//Update countdown time
						displayResolutionSwitchTimeSec -= 1;

						//Update countdown text
						textblock_Overlay_ConfirmResolution_SubText().Text(L"Reverting in " + number_to_wstring(displayResolutionSwitchTimeSec) + L" seconds...");

						//Check if time is up and revert resolution
						if (displayResolutionSwitchTimeSec <= 0)
						{
							DisplaySettings_Confirm_Resolution_Stop(true);
						}
					}
					catch (...) {}
				};

			//Start resolution switch timer
			if (TimerResolutionSwitch == NULL)
			{
				TimerResolutionSwitch = winrt::Windows::UI::Xaml::DispatcherTimer();
				TimerResolutionSwitch.Interval(TimeSpan(10000000));
				TimerResolutionSwitch.Tick(tickFunction);
			}
			TimerResolutionSwitch.Start();
		}
		catch (...) {}
	}

	void MainPage::DisplaySettings_Confirm_Resolution_Stop(bool revertResolution)
	{
		try
		{
			AVDebugWriteLine(L"Confirmed resolution switch, reverting: " << revertResolution);

			//Stop resolution switch timer
			TimerResolutionSwitch.Stop();

			//Hide overlay
			grid_Main().IsHitTestVisible(true);
			grid_Overlay_ConfirmResolution().Visibility(Visibility::Collapsed);

			//Revert resolution
			if (revertResolution)
			{
				//Revert resolution and refresh rate
				DisplaySettings_Resolution_Revert();

				//Fix select resolution and refresh rate
			}
		}
		catch (...) {}
	}

	void MainPage::button_Overlay_ConfirmResolution_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			DisplaySettings_Confirm_Resolution_Stop(false);
		}
		catch (...) {}
	}

	void MainPage::button_Overlay_RevertResolution_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			DisplaySettings_Confirm_Resolution_Stop(true);
		}
		catch (...) {}
	}
}