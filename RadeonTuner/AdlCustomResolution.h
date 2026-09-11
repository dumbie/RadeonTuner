#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	std::optional<ADLDisplayModeInfoX2> MainPage::GetDisplayModeInfo_FromADL(int adapterIndex, int displayIndex, int presentationMode, int timingStandard, int pixelWidth, int pixelHeight, int refreshRate)
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

					//Set presentation flag
					if (presentationMode == ADL_DL_TIMINGFLAG_DOUBLE_SCAN)
					{
						modeInfoX2.sDetailedTiming.sTimingFlags |= ADL_DL_TIMINGFLAG_DOUBLE_SCAN;
					}
					else if (presentationMode == ADL_DL_TIMINGFLAG_INTERLACED)
					{
						modeInfoX2.sDetailedTiming.sTimingFlags |= ADL_DL_TIMINGFLAG_INTERLACED;
					}

					//Get timing details
					//int resolutionWidth = modeInfoX2.sDetailedTiming.sHDisplay;
					//int resolutionHeight = modeInfoX2.sDetailedTiming.sVDisplay;
					//float refreshRate = (float)(modeInfoX2.sDetailedTiming.sPixelClock * 10000) / (float)(modeInfoX2.sDetailedTiming.sHTotal * modeInfoX2.sDetailedTiming.sVTotal);
					//float horizontalRate = (float)(modeInfoX2.sDetailedTiming.sPixelClock * 10) / (float)modeInfoX2.sDetailedTiming.sHTotal;
					int frontPorchH = modeInfoX2.sDetailedTiming.sHSyncStart - modeInfoX2.sDetailedTiming.sHDisplay;
					int frontPorchV = modeInfoX2.sDetailedTiming.sVSyncStart - modeInfoX2.sDetailedTiming.sVDisplay;
					int backPorchH = modeInfoX2.sDetailedTiming.sHTotal - (modeInfoX2.sDetailedTiming.sHSyncStart + modeInfoX2.sDetailedTiming.sHSyncWidth);
					int backPorchV = modeInfoX2.sDetailedTiming.sVTotal - (modeInfoX2.sDetailedTiming.sVSyncStart + modeInfoX2.sDetailedTiming.sVSyncWidth);
					int blankingH = modeInfoX2.sDetailedTiming.sHTotal - modeInfoX2.sDetailedTiming.sHDisplay;
					int blankingV = modeInfoX2.sDetailedTiming.sVTotal - modeInfoX2.sDetailedTiming.sVDisplay;
					int polarityH = (modeInfoX2.sDetailedTiming.sTimingFlags & ADL_DL_TIMINGFLAG_H_SYNC_POLARITY) == ADL_DL_TIMINGFLAG_H_SYNC_POLARITY;
					int polarityV = (modeInfoX2.sDetailedTiming.sTimingFlags & ADL_DL_TIMINGFLAG_V_SYNC_POLARITY) == ADL_DL_TIMINGFLAG_V_SYNC_POLARITY;

					//Show debug information
					AVDebugWriteLine(L"Generated custom basics: Width " << modeInfoX2.iPelsWidth << L" / Height " << modeInfoX2.iPelsHeight << L" / RefreshRate " << modeInfoX2.iRefreshRate << L" / Timing " << modeInfoX2.iTimingStandard << L" X2");
					AVDebugWriteLine(L"Generated custom details (General): PixelClock " << modeInfoX2.sDetailedTiming.sPixelClock << L" / TimingFlags " << modeInfoX2.sDetailedTiming.sTimingFlags);
					AVDebugWriteLine(L"Generated custom details (Horizontal): Total " << modeInfoX2.sDetailedTiming.sHTotal << L" / ActiveDisplay " << modeInfoX2.sDetailedTiming.sHDisplay << L" / FrontPorch " << frontPorchH << L" / BackPorch " << backPorchH << L" / Blanking " << blankingH << L" / SyncWidth " << modeInfoX2.sDetailedTiming.sHSyncWidth << L" / Polarity " << polarityH);
					AVDebugWriteLine(L"Generated custom details (Vertical): Total " << modeInfoX2.sDetailedTiming.sVTotal << L" / ActiveDisplay " << modeInfoX2.sDetailedTiming.sVDisplay << L" / FrontPorch " << frontPorchV << L" / BackPorch " << backPorchV << L" / Blanking " << blankingV << L" / SyncWidth " << modeInfoX2.sDetailedTiming.sVSyncWidth << L" / Polarity " << polarityV);

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
				displayMode.iScanType = presentationMode;

				//Generate custom resolution
				ADLDisplayModeInfoX2 modeInfoX2{};
				adl_Res0 = _ADL2_Display_ModeTimingOverrideX3_Get(adl_Context, displayID.iDisplayLogicalAdapterIndex, displayID, &displayMode, &modeInfoX2);
				if (adl_Res0 == ADL_OK)
				{
					//Get timing details
					//int resolutionWidth = modeInfoX2.sDetailedTiming.sHDisplay;
					//int resolutionHeight = modeInfoX2.sDetailedTiming.sVDisplay;
					//float refreshRate = (float)(modeInfoX2.sDetailedTiming.sPixelClock * 10000) / (float)(modeInfoX2.sDetailedTiming.sHTotal * modeInfoX2.sDetailedTiming.sVTotal);
					//float horizontalRate = (float)(modeInfoX2.sDetailedTiming.sPixelClock * 10) / (float)modeInfoX2.sDetailedTiming.sHTotal;
					int frontPorchH = modeInfoX2.sDetailedTiming.sHSyncStart - modeInfoX2.sDetailedTiming.sHDisplay;
					int frontPorchV = modeInfoX2.sDetailedTiming.sVSyncStart - modeInfoX2.sDetailedTiming.sVDisplay;
					int backPorchH = modeInfoX2.sDetailedTiming.sHTotal - (modeInfoX2.sDetailedTiming.sHSyncStart + modeInfoX2.sDetailedTiming.sHSyncWidth);
					int backPorchV = modeInfoX2.sDetailedTiming.sVTotal - (modeInfoX2.sDetailedTiming.sVSyncStart + modeInfoX2.sDetailedTiming.sVSyncWidth);
					int blankingH = modeInfoX2.sDetailedTiming.sHTotal - modeInfoX2.sDetailedTiming.sHDisplay;
					int blankingV = modeInfoX2.sDetailedTiming.sVTotal - modeInfoX2.sDetailedTiming.sVDisplay;
					int polarityH = (modeInfoX2.sDetailedTiming.sTimingFlags & ADL_DL_TIMINGFLAG_H_SYNC_POLARITY) == ADL_DL_TIMINGFLAG_H_SYNC_POLARITY;
					int polarityV = (modeInfoX2.sDetailedTiming.sTimingFlags & ADL_DL_TIMINGFLAG_V_SYNC_POLARITY) == ADL_DL_TIMINGFLAG_V_SYNC_POLARITY;

					//Show debug information
					AVDebugWriteLine(L"Generated custom basics: Width " << modeInfoX2.iPelsWidth << L" / Height " << modeInfoX2.iPelsHeight << L" / RefreshRate " << modeInfoX2.iRefreshRate << L" / Timing " << modeInfoX2.iTimingStandard << L" X2");
					AVDebugWriteLine(L"Generated custom details (General): PixelClock " << modeInfoX2.sDetailedTiming.sPixelClock << L" / TimingFlags " << modeInfoX2.sDetailedTiming.sTimingFlags);
					AVDebugWriteLine(L"Generated custom details (Horizontal): Total " << modeInfoX2.sDetailedTiming.sHTotal << L" / ActiveDisplay " << modeInfoX2.sDetailedTiming.sHDisplay << L" / FrontPorch " << frontPorchH << L" / BackPorch " << backPorchH << L" / Blanking " << blankingH << L" / SyncWidth " << modeInfoX2.sDetailedTiming.sHSyncWidth << L" / Polarity " << polarityH);
					AVDebugWriteLine(L"Generated custom details (Vertical): Total " << modeInfoX2.sDetailedTiming.sVTotal << L" / ActiveDisplay " << modeInfoX2.sDetailedTiming.sVDisplay << L" / FrontPorch " << frontPorchV << L" / BackPorch " << backPorchV << L" / Blanking " << blankingV << L" / SyncWidth " << modeInfoX2.sDetailedTiming.sVSyncWidth << L" / Polarity " << polarityV);

					//Return result
					return modeInfoX2;
				}
			}
		}
		catch (...) {}
		//Return result
		return std::nullopt;
	}
}