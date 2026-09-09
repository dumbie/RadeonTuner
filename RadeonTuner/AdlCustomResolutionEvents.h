#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::button_CustomResolution_Create_Click(IInspectable const& sender, RoutedEventArgs const& e)
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
					return;
				}

				//Set current values for custom resolution
				textbox_CustomResolution_Width().Text(number_to_wstring(adlModeCurrent->iXRes));
				textbox_CustomResolution_Height().Text(number_to_wstring(adlModeCurrent->iYRes));
				textbox_CustomResolution_RefreshRate().Text(float_to_wstring(adlModeCurrent->fRefreshRate, 0));
				combobox_CustomResolution_Presentation().SelectedIndex(0);
				combobox_CustomResolution_TimingStandard().SelectedIndex(1);
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

			//Convert custom resolution info to mode
			ADLDisplayModeX2 displayMode{};
			displayMode.iWidth = infoMode.iPelsWidth;
			displayMode.iHeight = infoMode.iPelsHeight;
			displayMode.iRefreshRate = infoMode.iRefreshRate;

			//Remove custom resolution
			adl_Res0 = _ADL2_Display_ModeTimingOverride_Delete(adl_Context, displayID.iDisplayLogicalAdapterIndex, displayID, &displayMode, true);
			if (adl_Res0 == ADL_OK)
			{
				//Show notification
				ShowNotification(L"Custom resolution removed");
				AVDebugWriteLine(L"Custom resolution removed: " << adl_Res0 << L" / " << infoMode.iPelsWidth << L"x" << infoMode.iPelsHeight << L" @ " << infoMode.iRefreshRate << L"Hz");

				//Reload display resolution
				disable_saving = true;
				DisplayList_Combined(false);
				disable_saving = false;
			}
			else
			{
				//Show notification
				ShowNotification(L"Failed removing custom resolution");
				AVDebugWriteLine(L"Failed removing custom resolution: " << adl_Res0);
			}
		}
		catch (...)
		{
			//Show notification
			ShowNotification(L"Failed removing custom resolution");
			AVDebugWriteLine(L"Failed removing custom resolution (Exception)");
		}
	}

	winrt::fire_and_forget MainPage::button_Overlay_CustomResolution_Create_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Set ADL display identifier
			ADLDisplayID displayID{};
			displayID.iDisplayLogicalAdapterIndex = adl_Display_AdapterIndex;
			displayID.iDisplayLogicalIndex = adl_Display_DisplayIndex;

			//Create custom resolution mode
			ADLDisplayModeX2 displayMode{};
			displayMode.iWidth = wstring_to_int(textbox_CustomResolution_Width().Text().c_str());
			displayMode.iHeight = wstring_to_int(textbox_CustomResolution_Height().Text().c_str());
			displayMode.iRefreshRate = wstring_to_int(textbox_CustomResolution_RefreshRate().Text().c_str());

			//Get current display mode
			int numModes = -1;
			ADLMode* adlModeCurrent{};
			adl_Res0 = _ADL2_Display_Modes_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &numModes, &adlModeCurrent);
			if (adl_Res0 != ADL_OK)
			{
				AVDebugWriteLine(L"Failed getting current display mode.");
				co_return;
			}

			//Check if refresh rate is currently used
			//Note: When you create a custom resolution with same refresh rate you are currently using but with incompatible timings you will end up with a black (no signal) screen even after rebooting requiring you to go into safe mode.
			if (displayMode.iWidth == adlModeCurrent->iXRes && displayMode.iHeight == adlModeCurrent->iYRes && displayMode.iRefreshRate == adlModeCurrent->fRefreshRate)
			{
				//Fix switch to timer with confirm popup like resolution switch, remove custom resolution when not confirmed after x seconds.

				//Show prompt
				ShowMessageBox(L"Refresh rate in use", L"The custom resolution refresh rate you are trying to create or edit is currently in use by your display, to prevent you from locking yourself out with an incompatible timing causing a black (no signal) screen, please switch your display to a different refresh rate first.", {});
				AVDebugWriteLine(L"Refresh rate in use.");
				co_return;
			}

			//Enumeration index correction
			if (combobox_CustomResolution_Presentation().SelectedIndex() == 0)
			{
				//Progressive
				displayMode.iScanType = 0;
			}
			else if (combobox_CustomResolution_Presentation().SelectedIndex() == 1)
			{
				//Interlaced
				displayMode.iScanType = ADL_DL_TIMINGFLAG_INTERLACED;
			}

			//Enumeration index correction
			if (combobox_CustomResolution_TimingStandard().SelectedIndex() == 0)
			{
				//CVT
				displayMode.iTimingStandard = ADL_DL_MODETIMING_STANDARD_CVT;
			}
			else if (combobox_CustomResolution_TimingStandard().SelectedIndex() == 1)
			{
				//CVT-RB
				displayMode.iTimingStandard = ADL_DL_MODETIMING_STANDARD_CVT_RB;
			}
			else if (combobox_CustomResolution_TimingStandard().SelectedIndex() == 2)
			{
				//GTF
				displayMode.iTimingStandard = ADL_DL_MODETIMING_STANDARD_GTF;
			}
			else if (combobox_CustomResolution_TimingStandard().SelectedIndex() == 3)
			{
				//DMT
				displayMode.iTimingStandard = ADL_DL_MODETIMING_STANDARD_DMT;
			}
			else if (combobox_CustomResolution_TimingStandard().SelectedIndex() == 4)
			{
				//Manual
				displayMode.iTimingStandard = ADL_DL_MODETIMING_STANDARD_CUSTOM;
			}

			//Generate custom resolution
			ADLDisplayModeInfoX2 infoMode{};
			adl_Res0 = _ADL2_Display_ModeTimingOverrideX3_Get(adl_Context, displayID.iDisplayLogicalAdapterIndex, displayID, &displayMode, &infoMode);
			if (adl_Res0 != ADL_OK)
			{
				//Show notification
				ShowNotification(L"Failed generating custom resolution");
				AVDebugWriteLine(L"Failed generating custom resolution");
				co_return;
			}
			else
			{
				//Fix find way to read default display timings (for example my monitor front porch defaults to 24 but CVT-RB is 48)
				AVDebugWriteLine(L"Generated custom basics: Width " << infoMode.iPelsWidth << L" / Height " << infoMode.iPelsHeight << L" / RefreshRate " << infoMode.iRefreshRate << L" / Timing " << infoMode.iTimingStandard);
				AVDebugWriteLine(L"Generated custom details (General): PixelClock " << infoMode.sDetailedTiming.sPixelClock << L" / TimingFlags " << infoMode.sDetailedTiming.sTimingFlags);
				AVDebugWriteLine(L"Generated custom details (Horizontal): Total " << infoMode.sDetailedTiming.sHTotal << L" / ActiveDisplay " << infoMode.sDetailedTiming.sHDisplay << L" / FrontPorch " << (infoMode.sDetailedTiming.sHSyncStart - infoMode.sDetailedTiming.sHDisplay) << L" / SyncWidth " << infoMode.sDetailedTiming.sHSyncWidth << L" / Polarity " << ((infoMode.sDetailedTiming.sTimingFlags & ADL_DL_TIMINGFLAG_H_SYNC_POLARITY) == ADL_DL_TIMINGFLAG_H_SYNC_POLARITY));
				AVDebugWriteLine(L"Generated custom details (Vertical): Total " << infoMode.sDetailedTiming.sVTotal << L" / ActiveDisplay " << infoMode.sDetailedTiming.sVDisplay << L" / FrontPorch " << (infoMode.sDetailedTiming.sVSyncStart - infoMode.sDetailedTiming.sVDisplay) << L" / SyncWidth " << infoMode.sDetailedTiming.sVSyncWidth << L" / Polarity " << ((infoMode.sDetailedTiming.sTimingFlags & ADL_DL_TIMINGFLAG_V_SYNC_POLARITY) == ADL_DL_TIMINGFLAG_V_SYNC_POLARITY));
			}

			//Set custom resolution
			adl_Res0 = _ADL2_Display_ModeTimingOverrideX2_Set(adl_Context, displayID.iDisplayLogicalAdapterIndex, displayID.iDisplayLogicalIndex, &infoMode, true);
			if (adl_Res0 == ADL_OK)
			{
				//Show notification
				ShowNotification(L"Custom resolution created");
				AVDebugWriteLine(L"Custom resolution created: " << adl_Res0 << L" / " << infoMode.iPelsWidth << L"x" << infoMode.iPelsHeight << L" @ " << infoMode.iRefreshRate << L"Hz");

				//Reload display resolution
				disable_saving = true;
				DisplayList_Combined(false);
				disable_saving = false;
			}
			else
			{
				//Show notification
				ShowNotification(L"Failed creating custom resolution");
				AVDebugWriteLine(L"Failed creating custom resolution: " << adl_Res0);
			}
		}
		catch (...)
		{
			//Show notification
			ShowNotification(L"Failed creating custom resolution");
			AVDebugWriteLine(L"Failed creating custom resolution (Exception)");
		}
	}
}