#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::Adl_Eyefinity_Create_Simple()
	{
		try
		{
			//Enable SLS environment workaround
			SetEnvironmentVariableA("ADL_4KWORKAROUND_CANCEL", "TRUE");

			//Get simple Eyefinity
			IADLXSimpleEyefinityPtr eyefinitySimple;
			adlx_Res0 = ppDesktopServices->GetSimpleEyefinity(&eyefinitySimple);
			if (ADLX_FAILED(adlx_Res0))
			{
				AVDebugWriteLine("Failed to get simple Eyefinity: " << adlx_Res0);
				return false;
			}

			//Create simple Eyefinity
			IADLXEyefinityDesktopPtr eyefinityDesktop;
			adlx_Res0 = eyefinitySimple->Create(&eyefinityDesktop);

			//Return result
			AVDebugWriteLine("Created simple Eyefinity: " << adlx_Res0);
			return adlx_Res0 == ADLX_OK;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to create simple Eyefinity (Exception)");
			return false;
		}
	}

	bool MainPage::Adl_Eyefinity_Create_Custom(int displayAdapterIndex)
	{
		try
		{
			//Enable SLS environment workaround
			SetEnvironmentVariableA("ADL_4KWORKAROUND_CANCEL", "TRUE");

			//Set SLS variables
			int slsMapIndexIn = -1;
			int slsMapIndexOut = 0;
			int slsTargetCurrent = 0;
			int slsCreateOption = ADL_DISPLAY_SLSMAPCONFIG_CREATE_OPTION_RELATIVETO_CURRENTANGLE;

			int displayColumns = 1;
			int displayRows = 2;
			int displayCount = 2;
			int* displayIndexes = new int[] { 8, 12 };
			//int* displayIndexes = new int[] { 12, 8 };
			int displayOrientationDegree = 0; //0, 90, 180, 270
			int displayBezelPercentage = 0;

			//Set SLS map
			ADLSLSMap slsMap{};
			slsMap.iAdapterIndex = displayAdapterIndex;
			slsMap.iSLSMapIndex = slsMapIndexIn;
			slsMap.iSLSMapValue = ADL_DISPLAY_SLSMAP_SLSLAYOUTMODE_FILL;
			slsMap.iNumNativeMode = 0;
			slsMap.iNumBezelMode = 0;
			slsMap.iOrientation = displayOrientationDegree;
			slsMap.grid.iSLSGridColumn = displayColumns;
			slsMap.grid.iSLSGridRow = displayRows;

			//Set SLS targets
			ADLSLSTarget* slsTargets = new ADLSLSTarget[displayCount];
			for (int x = 0; x < displayRows; x++)
			{
				for (int y = 0; y < displayColumns; y++)
				{
					//Set indexes
					slsTargets[slsTargetCurrent].iAdapterIndex = displayAdapterIndex;
					slsTargets[slsTargetCurrent].iSLSMapIndex = slsMapIndexIn;

					//Set display target
					slsTargets[slsTargetCurrent].displayTarget = ADLDisplayTarget{};
					slsTargets[slsTargetCurrent].displayTarget.displayID.iDisplayLogicalIndex = displayIndexes[slsTargetCurrent];
					slsTargets[slsTargetCurrent].displayTarget.displayID.iDisplayPhysicalIndex = displayIndexes[slsTargetCurrent];

					//Set view size
					slsTargets[slsTargetCurrent].viewSize = ADLMode{};
					slsTargets[slsTargetCurrent].viewSize.iAdapterIndex = displayAdapterIndex;

					//Set grid position
					slsTargets[slsTargetCurrent].iSLSGridPositionX = x;
					slsTargets[slsTargetCurrent].iSLSGridPositionY = y;

					//Move to next target
					slsTargetCurrent++;
				}
			}

			//Set SLS map
			adl_Res0 = _ADL2_Display_SLSMapConfig_Create(adl_Context, displayAdapterIndex, slsMap, displayCount, slsTargets, displayBezelPercentage, &slsMapIndexOut, slsCreateOption);
			if (adl_Res0 != ADL_OK)
			{
				//Return result
				AVDebugWriteLine("Failed to create and set sls map configuration: " << adl_Res0);
				return false;
			}

			//Flush driver data
			//adl_Res0 = _ADL2_Flush_Driver_Data(adl_Context, adl_Display_DisplayIndex);

			//Return result
			AVDebugWriteLine("Created custom Eyefinity: " << adl_Res0);
			return adl_Res0 == ADL_OK;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to create custom Eyefinity (Exception)");
			return false;
		}
	}

	bool MainPage::Adl_Eyefinity_Delete_All(int displayAdapterIndex)
	{
		try
		{
			//Enable SLS environment workaround
			SetEnvironmentVariableA("ADL_4KWORKAROUND_CANCEL", "TRUE");

			AVDebugWriteLine("Deleting all Eyefinity for adapter: " << displayAdapterIndex);

			//Fix if (!Adl_Eyefinity_IsEnabled()) { return false; }

			//Get SLS map indexes
			int lpNumSLSMapIndexList = 0;
			int* lppSLSMapIndexList{};
			_ADL2_Display_SLSMapIndexList_Get(adl_Context, displayAdapterIndex, &lpNumSLSMapIndexList, &lppSLSMapIndexList, ADL_DISPLAY_SLSMAPINDEXLIST_OPTION_ACTIVE);

			//Check index count
			if (lpNumSLSMapIndexList <= 0)
			{
				AVDebugWriteLine("Failed deleting all Eyefinity, no active sls.");
				return false;
			}

			//Delete SLS map configurations
			int slsDeleteCount = 0;
			for (int index = 0; index < lpNumSLSMapIndexList; index++)
			{
				AVDebugWriteLine("Deleting sls map configuration: " << lppSLSMapIndexList[index]);
				adl_Res0 = _ADL2_Display_SLSMapConfig_Delete(adl_Context, displayAdapterIndex, lppSLSMapIndexList[index]);
				if (adl_Res0 == ADL_OK) { slsDeleteCount++; }
			}

			//Flush driver data
			//adl_Res0 = _ADL2_Flush_Driver_Data(adl_Context, adl_Display_DisplayIndex);

			//Return result
			AVDebugWriteLine("Deleted all Eyefinity count: " << slsDeleteCount);
			return slsDeleteCount == lpNumSLSMapIndexList;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to delete all Eyefinity (Exception)");
			return false;
		}
	}

	bool MainPage::Adl_Eyefinity_IsEnabled()
	{
		try
		{
			//Fix find way to check if Eyefinity is currently enabled
			//Compare if ADLDisplayMap.displayMode.iXYRes matches current monitor max xyRes
		}
		catch (...) {}
		return false;
	}

	bool MainPage::Adl_Eyefinity_Toggle(int displayAdapterIndex, bool setEnabled)
	{
		try
		{
			//Fix do not enable when already enabled to prevent flicker
			//if (Adl_Eyefinity_IsEnabled()) { return; }

			//Enable SLS environment workaround
			SetEnvironmentVariableA("ADL_4KWORKAROUND_CANCEL", "TRUE");

			//Get display map configuration
			int numDisplayMap;
			AVFin<ADLDisplayMap*> lpDisplayMap = AVFin<ADLDisplayMap*>(AVFinMethod::FreeMarshal);

			int numDisplayTarget;
			AVFin<ADLDisplayTarget*> lpDisplayTarget = AVFin<ADLDisplayTarget*>(AVFinMethod::FreeMarshal);

			adl_Res0 = _ADL2_Display_DisplayMapConfig_Get(adl_Context, displayAdapterIndex, &numDisplayMap, &lpDisplayMap.Get(), &numDisplayTarget, &lpDisplayTarget.Get(), ADL_DISPLAY_DISPLAYMAP_OPTION_GPUINFO);
			if (adl_Res0 != ADL_OK)
			{
				//Return result
				AVDebugWriteLine("Failed to get display map configuration: " << adl_Res0);
				return false;
			}

			//Get single large surface map index
			int slsMapIndex;
			adl_Res0 = _ADL2_Display_SLSMapIndex_Get(adl_Context, displayAdapterIndex, numDisplayTarget, lpDisplayTarget.Get(), &slsMapIndex);
			if (adl_Res0 != ADL_OK)
			{
				//Return result
				AVDebugWriteLine("Failed to get single large surface map index: " << adl_Res0);
				return false;
			}

			//Set single large surface map state
			adl_Res0 = _ADL2_Display_SLSMapConfig_SetState(adl_Context, displayAdapterIndex, slsMapIndex, setEnabled);

			//Return result
			AVDebugWriteLine("Set Eyefinity state: " << adl_Res0 << " / " << setEnabled);
			return adl_Res0 == ADL_OK;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to set Eyefinity state (Exception)");
			return false;
		}
	}
}