#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::CustomResolution_Create(int adapterIndex, int displayIndex, ADLDisplayModeInfoX2 modeInfoX2)
	{
		try
		{
			//Set timing standard to custom
			modeInfoX2.iTimingStandard = ADL_DL_MODETIMING_STANDARD_CUSTOM;

			//Custom timing xor bitmask correction
			//Note: Polarity needs to be inverted when using custom timings.
			if (modeInfoX2.iTimingStandard == ADL_DL_MODETIMING_STANDARD_CUSTOM)
			{
				modeInfoX2.sDetailedTiming.sTimingFlags ^= ADL_DL_TIMINGFLAG_H_SYNC_POLARITY;
				modeInfoX2.sDetailedTiming.sTimingFlags ^= ADL_DL_TIMINGFLAG_V_SYNC_POLARITY;
				AVDebugWriteLine(L"Custom timing detected, applying polarity correction.");
			}

			//Show debug information
			AVDebugWriteLine(L"Custom resolution creating:");
			AVDebugWriteLine(L"(Basic) " << modeInfoX2.iPelsWidth << L"x" << modeInfoX2.iPelsHeight << L" @ " << modeInfoX2.iRefreshRate << L"Hz");
			AVDebugWriteLine(L"(Detailed) PixelClock " << modeInfoX2.sDetailedTiming.sPixelClock << L" / TimingStandard " << modeInfoX2.iTimingStandard << L" / TimingFlags " << modeInfoX2.sDetailedTiming.sTimingFlags << L" / Overscan8B " << modeInfoX2.sDetailedTiming.sOverscan8B << L" / OverscanGR " << modeInfoX2.sDetailedTiming.sOverscanGR << L" / Size " << modeInfoX2.sDetailedTiming.iSize);
			AVDebugWriteLine(L"(Horizontal) Total " << modeInfoX2.sDetailedTiming.sHTotal << L" / ActiveDisplay " << modeInfoX2.sDetailedTiming.sHDisplay << L" / SyncStart " << modeInfoX2.sDetailedTiming.sHSyncStart << L" / SyncWidth " << modeInfoX2.sDetailedTiming.sHSyncWidth << L" / OverscanLeft " << modeInfoX2.sDetailedTiming.sHOverscanLeft << L" / OverscanRight " << modeInfoX2.sDetailedTiming.sHOverscanRight);
			AVDebugWriteLine(L"(Vertical) Total " << modeInfoX2.sDetailedTiming.sVTotal << L" / ActiveDisplay " << modeInfoX2.sDetailedTiming.sVDisplay << L" / SyncStart " << modeInfoX2.sDetailedTiming.sVSyncStart << L" / SyncWidth " << modeInfoX2.sDetailedTiming.sVSyncWidth << L" / OverscanTop " << modeInfoX2.sDetailedTiming.sVOverscanTop << L" / OverscanBottom " << modeInfoX2.sDetailedTiming.sVOverscanBottom);

			//Set custom resolution
			adl_Res0 = _ADL2_Display_ModeTimingOverrideX2_Set(adl_Context, adapterIndex, displayIndex, &modeInfoX2, true);
			if (adl_Res0 == ADL_OK)
			{
				//Show notification
				ShowNotification(L"Custom resolution created");
				AVDebugWriteLine(L"Custom resolution created");

				//Show confirm overlay
				//Note: When you create a custom resolution with same refresh rate you are currently using but with incompatible timings you will end up with a black (no signal) screen even after rebooting requiring you to go into safe mode.
				//Alternative: Match current and target refresh rate and request user to switch first "The custom resolution refresh rate you are trying to create or edit is currently in use by your display, to prevent you from locking yourself out with an incompatible timing causing a black (no signal) screen, please switch your display to a different refresh rate first."
				DisplaySettings_Confirm_CustomResolution_Start();

				//Reload display resolution
				disable_saving = true;
				DisplayList_Combined(false);
				disable_saving = false;

				//Return result
				return true;
			}
			else
			{
				//Show notification
				ShowNotification(L"Failed creating custom resolution");
				AVDebugWriteLine(L"Failed creating custom resolution: " << adl_Res0);

				//Return result
				return false;
			}
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	bool MainPage::CustomResolution_Remove(int adapterIndex, int displayIndex, ADLDisplayModeInfoX2 modeInfoX2)
	{
		try
		{
			//Show debug information
			AVDebugWriteLine(L"Custom resolution removing:");
			AVDebugWriteLine(L"(Basic) " << modeInfoX2.iPelsWidth << L"x" << modeInfoX2.iPelsHeight << L" @ " << modeInfoX2.iRefreshRate << L"Hz");
			AVDebugWriteLine(L"(Detailed) PixelClock " << modeInfoX2.sDetailedTiming.sPixelClock << L" / TimingStandard " << modeInfoX2.iTimingStandard << L" / TimingFlags " << modeInfoX2.sDetailedTiming.sTimingFlags << L" / Overscan8B " << modeInfoX2.sDetailedTiming.sOverscan8B << L" / OverscanGR " << modeInfoX2.sDetailedTiming.sOverscanGR << L" / Size " << modeInfoX2.sDetailedTiming.iSize);
			AVDebugWriteLine(L"(Horizontal) Total " << modeInfoX2.sDetailedTiming.sHTotal << L" / ActiveDisplay " << modeInfoX2.sDetailedTiming.sHDisplay << L" / SyncStart " << modeInfoX2.sDetailedTiming.sHSyncStart << L" / SyncWidth " << modeInfoX2.sDetailedTiming.sHSyncWidth << L" / OverscanLeft " << modeInfoX2.sDetailedTiming.sHOverscanLeft << L" / OverscanRight " << modeInfoX2.sDetailedTiming.sHOverscanRight);
			AVDebugWriteLine(L"(Vertical) Total " << modeInfoX2.sDetailedTiming.sVTotal << L" / ActiveDisplay " << modeInfoX2.sDetailedTiming.sVDisplay << L" / SyncStart " << modeInfoX2.sDetailedTiming.sVSyncStart << L" / SyncWidth " << modeInfoX2.sDetailedTiming.sVSyncWidth << L" / OverscanTop " << modeInfoX2.sDetailedTiming.sVOverscanTop << L" / OverscanBottom " << modeInfoX2.sDetailedTiming.sVOverscanBottom);

			//Set ADL display identifier
			ADLDisplayID displayID{};
			displayID.iDisplayLogicalAdapterIndex = adapterIndex;
			displayID.iDisplayLogicalIndex = displayIndex;

			//Convert custom resolution info to mode
			ADLDisplayModeX2 displayMode{};
			displayMode.iWidth = modeInfoX2.iPelsWidth;
			displayMode.iHeight = modeInfoX2.iPelsHeight;
			displayMode.iRefreshRate = modeInfoX2.iRefreshRate;

			//Remove custom resolution
			adl_Res0 = _ADL2_Display_ModeTimingOverride_Delete(adl_Context, displayID.iDisplayLogicalAdapterIndex, displayID, &displayMode, true);
			if (adl_Res0 == ADL_OK)
			{
				//Show notification
				ShowNotification(L"Custom resolution removed");
				AVDebugWriteLine(L"Custom resolution removed");

				//Reload display resolution
				disable_saving = true;
				DisplayList_Combined(false);
				disable_saving = false;

				//Return result
				return true;
			}
			else
			{
				//Show notification
				ShowNotification(L"Failed removing custom resolution");
				AVDebugWriteLine(L"Failed removing custom resolution: " << adl_Res0);

				//Return result
				return false;
			}
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	void MainPage::DisplayModeInfo_Calculate_Timings()
	{
		try
		{
			//Get custom resolution values
			int customPixelWidth = wstring_to_int(textbox_CustomResolution_Width().Text().c_str());
			int customPixelHeight = wstring_to_int(textbox_CustomResolution_Height().Text().c_str());
			int customRefreshRate = wstring_to_int(textbox_CustomResolution_RefreshRate().Text().c_str());
			int customPresentationMode = 0;
			int customTimingStandard = 0;

			//Enumeration index correction
			if (combobox_CustomResolution_Presentation().SelectedIndex() == 0)
			{
				//Progressive
				customPresentationMode = 0;
			}
			else if (combobox_CustomResolution_Presentation().SelectedIndex() == 1)
			{
				//Interlaced
				customPresentationMode = ADL_DL_TIMINGFLAG_INTERLACED;
			}

			//Enumeration index correction
			if (combobox_CustomResolution_TimingStandard().SelectedIndex() == 0)
			{
				//Display
				customTimingStandard = ADL_DL_MODETIMING_STANDARD_CUSTOM;
			}
			else if (combobox_CustomResolution_TimingStandard().SelectedIndex() == 1)
			{
				//CVT
				customTimingStandard = ADL_DL_MODETIMING_STANDARD_CVT;
			}
			else if (combobox_CustomResolution_TimingStandard().SelectedIndex() == 2)
			{
				//CVT-RB
				customTimingStandard = ADL_DL_MODETIMING_STANDARD_CVT_RB;
			}
			else if (combobox_CustomResolution_TimingStandard().SelectedIndex() == 3)
			{
				//GTF
				customTimingStandard = ADL_DL_MODETIMING_STANDARD_GTF;
			}
			else if (combobox_CustomResolution_TimingStandard().SelectedIndex() == 4)
			{
				//DMT
				customTimingStandard = ADL_DL_MODETIMING_STANDARD_DMT;
			}

			//Get custom timing mode info from adl
			auto infoMode = DisplayModeInfo_FromADL(adl_Display_AdapterIndex, adl_Display_DisplayIndex, customPresentationMode, customTimingStandard, customPixelWidth, customPixelHeight, customRefreshRate);
			if (infoMode.has_value())
			{
				//Update custom timing mode info variable
				displayCustomModeInfo = infoMode.value();

				//Set custom timing mode info to interface
				DisplayModeInfo_ToUI(infoMode.value(), false);

				//Validate pixel clock
				if (infoMode.value().sDetailedTiming.sPixelClock < 0)
				{
					//Adjust button colors
					SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
					button_Overlay_CustomResolution_Create().Background(colorIgnored);
				}
				else
				{
					//Adjust button colors
					SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
					button_Overlay_CustomResolution_Create().Background(colorValid);
				}
			}
			else
			{
				//Adjust button colors
				SolidColorBrush colorIgnored = Application::Current().Resources().Lookup(box_value(L"ApplicationIgnoredBrush")).as<SolidColorBrush>();
				button_Overlay_CustomResolution_Create().Background(colorIgnored);
			}
		}
		catch (...) {}
	}

	void MainPage::DisplayModeInfo_ToUI(ADLDisplayModeInfoX2 modeInfoX2, bool actualOnly)
	{
		try
		{
			//Get timing basics
			int resolutionWidth = modeInfoX2.sDetailedTiming.sHDisplay;
			int resolutionHeight = modeInfoX2.sDetailedTiming.sVDisplay;
			float refreshRate = (float)(modeInfoX2.sDetailedTiming.sPixelClock * 10000) / (float)(modeInfoX2.sDetailedTiming.sHTotal * modeInfoX2.sDetailedTiming.sVTotal);
			float horizontalRate = (float)(modeInfoX2.sDetailedTiming.sPixelClock * 10) / (float)modeInfoX2.sDetailedTiming.sHTotal;

			//Get timing details
			int frontPorchH = modeInfoX2.sDetailedTiming.sHSyncStart - modeInfoX2.sDetailedTiming.sHDisplay;
			int frontPorchV = modeInfoX2.sDetailedTiming.sVSyncStart - modeInfoX2.sDetailedTiming.sVDisplay;
			int backPorchH = modeInfoX2.sDetailedTiming.sHTotal - (modeInfoX2.sDetailedTiming.sHSyncStart + modeInfoX2.sDetailedTiming.sHSyncWidth);
			int backPorchV = modeInfoX2.sDetailedTiming.sVTotal - (modeInfoX2.sDetailedTiming.sVSyncStart + modeInfoX2.sDetailedTiming.sVSyncWidth);
			int blankingH = modeInfoX2.sDetailedTiming.sHTotal - modeInfoX2.sDetailedTiming.sHDisplay;
			int blankingV = modeInfoX2.sDetailedTiming.sVTotal - modeInfoX2.sDetailedTiming.sVDisplay;
			bool polarityH = (modeInfoX2.sDetailedTiming.sTimingFlags & ADL_DL_TIMINGFLAG_H_SYNC_POLARITY) == ADL_DL_TIMINGFLAG_H_SYNC_POLARITY;
			bool polarityV = (modeInfoX2.sDetailedTiming.sTimingFlags & ADL_DL_TIMINGFLAG_V_SYNC_POLARITY) == ADL_DL_TIMINGFLAG_V_SYNC_POLARITY;
			int syncWidthH = modeInfoX2.sDetailedTiming.sHSyncWidth;
			int syncWidthV = modeInfoX2.sDetailedTiming.sVSyncWidth;

			//Check update type
			if (actualOnly)
			{
				//Set actual timing details to interface
				textbox_CustomResolution_ActualRefreshRate().Text(float_to_wstring(refreshRate, 3)); //ReadOnly
			}
			else
			{
				//Set all timing details to interface
				textbox_CustomResolution_PixelClock().Text(number_to_wstring(modeInfoX2.sDetailedTiming.sPixelClock));
				textbox_CustomResolution_ActualRefreshRate().Text(float_to_wstring(refreshRate, 3)); //ReadOnly

				textbox_TimingTotal_Horizontal().Text(number_to_wstring(modeInfoX2.sDetailedTiming.sHTotal));
				textbox_TimingTotal_Vertical().Text(number_to_wstring(modeInfoX2.sDetailedTiming.sVTotal));

				textbox_TimingFrontPorch_Horizontal().Text(number_to_wstring(frontPorchH));
				textbox_TimingFrontPorch_Vertical().Text(number_to_wstring(frontPorchV));

				textbox_TimingSyncWidth_Horizontal().Text(number_to_wstring(syncWidthH));
				textbox_TimingSyncWidth_Vertical().Text(number_to_wstring(syncWidthV));

				combobox_TimingPolarity_Horizontal().SelectedIndex(polarityH ? 1 : 0);
				combobox_TimingPolarity_Vertical().SelectedIndex(polarityV ? 1 : 0);
			}
		}
		catch (...) {}
	}

	std::optional<ADLDisplayModeInfoX2> MainPage::DisplayModeInfo_FromADL(int adapterIndex, int displayIndex, int presentationMode, int timingStandard, int pixelWidth, int pixelHeight, int refreshRate)
	{
		try
		{
			//Set ADL display identifier
			ADLDisplayID displayID{};
			displayID.iDisplayLogicalAdapterIndex = adapterIndex;
			displayID.iDisplayLogicalIndex = displayIndex;

			//Check used timing standard
			if (timingStandard == ADL_DL_MODETIMING_STANDARD_CUSTOM)
			{
				//Get mode information from display

				//Create custom resolution mode
				ADLDisplayMode displayMode{};
				displayMode.iPelsWidth = pixelWidth;
				displayMode.iPelsHeight = pixelHeight;
				displayMode.iDisplayFrequency = refreshRate;

				//Generate custom resolution
				ADLDisplayModeInfo modeInfoX1{};
				adl_Res0 = _ADL2_Display_ModeTimingOverride_Get(adl_Context, displayID.iDisplayLogicalAdapterIndex, displayID.iDisplayLogicalIndex, &displayMode, &modeInfoX1);
				if (adl_Res0 == ADL_OK)
				{
					ADLDisplayModeInfoX2 modeInfoX2{};

					//Set missing display mode info
					modeInfoX2.iPelsWidth = pixelWidth;
					modeInfoX2.iPelsHeight = pixelHeight;
					modeInfoX2.iRefreshRate = refreshRate;
					modeInfoX2.iTimingStandard = timingStandard;

					//Convert display mode info X1 to X2
					modeInfoX2.sDetailedTiming.sTimingFlags = modeInfoX1.sDetailedTiming.sTimingFlags;
					modeInfoX2.sDetailedTiming.sHTotal = modeInfoX1.sDetailedTiming.sHTotal;
					modeInfoX2.sDetailedTiming.sHDisplay = modeInfoX1.sDetailedTiming.sHDisplay;
					modeInfoX2.sDetailedTiming.sHSyncStart = modeInfoX1.sDetailedTiming.sHSyncStart;
					modeInfoX2.sDetailedTiming.sHSyncWidth = modeInfoX1.sDetailedTiming.sHSyncWidth;
					modeInfoX2.sDetailedTiming.sVTotal = modeInfoX1.sDetailedTiming.sVTotal;
					modeInfoX2.sDetailedTiming.sVDisplay = modeInfoX1.sDetailedTiming.sVDisplay;
					modeInfoX2.sDetailedTiming.sVSyncStart = modeInfoX1.sDetailedTiming.sVSyncStart;
					modeInfoX2.sDetailedTiming.sVSyncWidth = modeInfoX1.sDetailedTiming.sVSyncWidth;
					modeInfoX2.sDetailedTiming.sPixelClock = modeInfoX1.sDetailedTiming.sPixelClock;
					modeInfoX2.sDetailedTiming.sHOverscanRight = modeInfoX1.sDetailedTiming.sHOverscanRight;
					modeInfoX2.sDetailedTiming.sHOverscanLeft = modeInfoX1.sDetailedTiming.sHOverscanLeft;
					modeInfoX2.sDetailedTiming.sVOverscanBottom = modeInfoX1.sDetailedTiming.sVOverscanBottom;
					modeInfoX2.sDetailedTiming.sVOverscanTop = modeInfoX1.sDetailedTiming.sVOverscanTop;
					modeInfoX2.sDetailedTiming.sOverscan8B = modeInfoX1.sDetailedTiming.sOverscan8B;
					modeInfoX2.sDetailedTiming.sOverscanGR = modeInfoX1.sDetailedTiming.sOverscanGR;

					//Manually calculate pixel clock
					//Note: Pixel clock does not get read correctly for all displays, manual calculation required when this happens.
					//if (modeInfoX2.sDetailedTiming.sPixelClock <= 0)
					{
						modeInfoX2.sDetailedTiming.sPixelClock = (modeInfoX2.sDetailedTiming.sHTotal * modeInfoX2.sDetailedTiming.sVTotal * modeInfoX2.iRefreshRate) / 10000;
						//AVDebugWriteLine(L"Custom resolution pixel clock invalid, manually calculated: " << modeInfoX2.sDetailedTiming.sPixelClock);
					}

					//Set presentation flag
					if (presentationMode == ADL_DL_TIMINGFLAG_INTERLACED)
					{
						//Interlaced
						displayCustomModeInfo.sDetailedTiming.sTimingFlags &= ~ADL_DL_TIMINGFLAG_DOUBLE_SCAN;
						displayCustomModeInfo.sDetailedTiming.sTimingFlags |= ADL_DL_TIMINGFLAG_INTERLACED;
					}
					else if (presentationMode == ADL_DL_TIMINGFLAG_DOUBLE_SCAN)
					{
						//Double Scan
						displayCustomModeInfo.sDetailedTiming.sTimingFlags &= ~ADL_DL_TIMINGFLAG_INTERLACED;
						displayCustomModeInfo.sDetailedTiming.sTimingFlags |= ADL_DL_TIMINGFLAG_DOUBLE_SCAN;
					}
					else
					{
						//Progressive
						displayCustomModeInfo.sDetailedTiming.sTimingFlags &= ~ADL_DL_TIMINGFLAG_INTERLACED;
						displayCustomModeInfo.sDetailedTiming.sTimingFlags &= ~ADL_DL_TIMINGFLAG_DOUBLE_SCAN;
					}

					//Show debug information
					AVDebugWriteLine(L"Custom resolution generated X1:");
					AVDebugWriteLine(L"(Basic) " << modeInfoX2.iPelsWidth << L"x" << modeInfoX2.iPelsHeight << L" @ " << modeInfoX2.iRefreshRate << L"Hz");
					AVDebugWriteLine(L"(Detailed) PixelClock " << modeInfoX2.sDetailedTiming.sPixelClock << L" / TimingStandard " << modeInfoX2.iTimingStandard << L" / TimingFlags " << modeInfoX2.sDetailedTiming.sTimingFlags << L" / Overscan8B " << modeInfoX2.sDetailedTiming.sOverscan8B << L" / OverscanGR " << modeInfoX2.sDetailedTiming.sOverscanGR << L" / Size " << modeInfoX2.sDetailedTiming.iSize);
					AVDebugWriteLine(L"(Horizontal) Total " << modeInfoX2.sDetailedTiming.sHTotal << L" / ActiveDisplay " << modeInfoX2.sDetailedTiming.sHDisplay << L" / SyncStart " << modeInfoX2.sDetailedTiming.sHSyncStart << L" / SyncWidth " << modeInfoX2.sDetailedTiming.sHSyncWidth << L" / OverscanLeft " << modeInfoX2.sDetailedTiming.sHOverscanLeft << L" / OverscanRight " << modeInfoX2.sDetailedTiming.sHOverscanRight);
					AVDebugWriteLine(L"(Vertical) Total " << modeInfoX2.sDetailedTiming.sVTotal << L" / ActiveDisplay " << modeInfoX2.sDetailedTiming.sVDisplay << L" / SyncStart " << modeInfoX2.sDetailedTiming.sVSyncStart << L" / SyncWidth " << modeInfoX2.sDetailedTiming.sVSyncWidth << L" / OverscanTop " << modeInfoX2.sDetailedTiming.sVOverscanTop << L" / OverscanBottom " << modeInfoX2.sDetailedTiming.sVOverscanBottom);

					//Return result
					return modeInfoX2;
				}
			}
			else
			{
				//Get mode information for standard

				//Create custom resolution mode
				ADLDisplayModeX2 displayMode{};
				displayMode.iWidth = pixelWidth;
				displayMode.iHeight = pixelHeight;
				displayMode.iRefreshRate = refreshRate;
				displayMode.iTimingStandard = timingStandard;

				//Generate custom resolution
				ADLDisplayModeInfoX2 modeInfoX2{};
				adl_Res0 = _ADL2_Display_ModeTimingOverrideX3_Get(adl_Context, displayID.iDisplayLogicalAdapterIndex, displayID, &displayMode, &modeInfoX2);
				if (adl_Res0 == ADL_OK)
				{
					//Set presentation flag
					if (presentationMode == ADL_DL_TIMINGFLAG_INTERLACED)
					{
						//Interlaced
						displayCustomModeInfo.sDetailedTiming.sTimingFlags &= ~ADL_DL_TIMINGFLAG_DOUBLE_SCAN;
						displayCustomModeInfo.sDetailedTiming.sTimingFlags |= ADL_DL_TIMINGFLAG_INTERLACED;
					}
					else if (presentationMode == ADL_DL_TIMINGFLAG_DOUBLE_SCAN)
					{
						//Double Scan
						displayCustomModeInfo.sDetailedTiming.sTimingFlags &= ~ADL_DL_TIMINGFLAG_INTERLACED;
						displayCustomModeInfo.sDetailedTiming.sTimingFlags |= ADL_DL_TIMINGFLAG_DOUBLE_SCAN;
					}
					else
					{
						//Progressive
						displayCustomModeInfo.sDetailedTiming.sTimingFlags &= ~ADL_DL_TIMINGFLAG_INTERLACED;
						displayCustomModeInfo.sDetailedTiming.sTimingFlags &= ~ADL_DL_TIMINGFLAG_DOUBLE_SCAN;
					}

					//Show debug information
					AVDebugWriteLine(L"Custom resolution generated X2:");
					AVDebugWriteLine(L"(Basic) " << modeInfoX2.iPelsWidth << L"x" << modeInfoX2.iPelsHeight << L" @ " << modeInfoX2.iRefreshRate << L"Hz");
					AVDebugWriteLine(L"(Detailed) PixelClock " << modeInfoX2.sDetailedTiming.sPixelClock << L" / TimingStandard " << modeInfoX2.iTimingStandard << L" / TimingFlags " << modeInfoX2.sDetailedTiming.sTimingFlags << L" / Overscan8B " << modeInfoX2.sDetailedTiming.sOverscan8B << L" / OverscanGR " << modeInfoX2.sDetailedTiming.sOverscanGR << L" / Size " << modeInfoX2.sDetailedTiming.iSize);
					AVDebugWriteLine(L"(Horizontal) Total " << modeInfoX2.sDetailedTiming.sHTotal << L" / ActiveDisplay " << modeInfoX2.sDetailedTiming.sHDisplay << L" / SyncStart " << modeInfoX2.sDetailedTiming.sHSyncStart << L" / SyncWidth " << modeInfoX2.sDetailedTiming.sHSyncWidth << L" / OverscanLeft " << modeInfoX2.sDetailedTiming.sHOverscanLeft << L" / OverscanRight " << modeInfoX2.sDetailedTiming.sHOverscanRight);
					AVDebugWriteLine(L"(Vertical) Total " << modeInfoX2.sDetailedTiming.sVTotal << L" / ActiveDisplay " << modeInfoX2.sDetailedTiming.sVDisplay << L" / SyncStart " << modeInfoX2.sDetailedTiming.sVSyncStart << L" / SyncWidth " << modeInfoX2.sDetailedTiming.sVSyncWidth << L" / OverscanTop " << modeInfoX2.sDetailedTiming.sVOverscanTop << L" / OverscanBottom " << modeInfoX2.sDetailedTiming.sVOverscanBottom);

					//Return result
					return modeInfoX2;
				}
			}
		}
		catch (...) {}
		//Return result
		AVDebugWriteLine(L"Failed generating display timings.");
		return std::nullopt;
	}

	void MainPage::DisplaySettings_Confirm_CustomResolution_Start()
	{
		try
		{
			//Reset switch time
			displayResolutionConfirmTimeSec = 12;
			displayResolutionConfirmType = 1;

			//Show overlay
			grid_Main().IsHitTestVisible(false);
			grid_Overlay_ConfirmResolution().Visibility(Visibility::Visible);
			textblock_Overlay_ConfirmResolution_SubText().Text(L"Removing custom resolution in " + number_to_wstring(displayResolutionConfirmTimeSec) + L" seconds...");

			//Resolution switch timer tick
			std::function<void(IInspectable const& sender, IInspectable const& e)> tickFunction = [&](auto, auto)
				{
					try
					{
						//Update countdown time
						displayResolutionConfirmTimeSec -= 1;

						//Update countdown text
						textblock_Overlay_ConfirmResolution_SubText().Text(L"Removing custom resolution in " + number_to_wstring(displayResolutionConfirmTimeSec) + L" seconds...");

						//Check if time is up and remove resolution
						if (displayResolutionConfirmTimeSec <= 0)
						{
							DisplaySettings_Confirm_CustomResolution_Stop(true);
						}
					}
					catch (...) {}
				};

			//Start resolution switch timer
			if (TimerResolutionCustom == NULL)
			{
				TimerResolutionCustom = winrt::Windows::UI::Xaml::DispatcherTimer();
				TimerResolutionCustom.Interval(TimeSpan(10000000));
				TimerResolutionCustom.Tick(tickFunction);
			}
			TimerResolutionCustom.Start();
		}
		catch (...) {}
	}

	void MainPage::DisplaySettings_Confirm_CustomResolution_Stop(bool removeResolution)
	{
		try
		{
			AVDebugWriteLine(L"Confirmed custom resolution, removing: " << removeResolution);

			//Stop resolution switch timer
			TimerResolutionCustom.Stop();

			//Hide overlay
			grid_Main().IsHitTestVisible(true);
			grid_Overlay_ConfirmResolution().Visibility(Visibility::Collapsed);

			if (removeResolution)
			{
				//Delete custom resolution
				CustomResolution_Remove(adl_Display_AdapterIndex, adl_Display_DisplayIndex, displayCustomModeInfo);
			}
		}
		catch (...) {}
	}
}