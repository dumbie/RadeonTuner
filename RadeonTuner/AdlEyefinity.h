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
			int slsMapIndexOut = -1;
			int slsTargetCurrent = 0;
			int slsCreateOption = ADL_DISPLAY_SLSMAPCONFIG_CREATE_OPTION_RELATIVETO_CURRENTANGLE;

			int displayColumns = 1 + slider_Eyefinity_Columns().Value();
			int displayRows = 1 + slider_Eyefinity_Rows().Value();
			int displayCount = listview_EyefinityMonitorIndex().Items().Size();

			//Get display details in order
			std::vector<int> displayIndexes{};
			for (IInspectable displayItem : listview_EyefinityMonitorIndex().Items())
			{
				auto displayDetails = displayItem.as<RadeonTuner::DisplayDetailsIdl>();
				displayIndexes.push_back(displayDetails.IndexDisplay());
				AVDebugWriteLine(displayDetails.Name() << " (Index " << displayDetails.IndexDisplay() << ")");
			}

			//Get display orientation degree
			int displayOrientationDegree = 0;
			switch (combobox_EyefinityMonitorOrientation().SelectedIndex())
			{
			case 0:
				displayOrientationDegree = 0;
				break;
			case 1:
				displayOrientationDegree = 90;
				break;
			case 2:
				displayOrientationDegree = 180;
				break;
			case 3:
				displayOrientationDegree = 270;
				break;
			}

			//Get display bezel percentage
			int displayBezelPercentage = 0;

			AVDebugWriteLine("Setting SLS map to: C" << displayColumns << "/R" << displayRows << "/D" << displayCount << "/O" << displayOrientationDegree << "/B" << displayBezelPercentage);

			//Check maximum displays
			if (displayColumns + displayRows > 8)
			{
				AVDebugWriteLine("SLS display limit reached.");
				return false;
			}

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
			std::vector<ADLSLSTarget> slsTargets(displayCount);
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

			//Create SLS map
			adl_Res0 = _ADL2_Display_SLSMapConfig_Create(adl_Context, displayAdapterIndex, slsMap, displayCount, slsTargets.data(), displayBezelPercentage, &slsMapIndexOut, slsCreateOption);
			if (adl_Res0 != ADL_OK)
			{
				//Return result
				AVDebugWriteLine("Failed to create and set sls map configuration: " << adl_Res0);
				return false;
			}

			//Flush driver data
			//adl_Res0 = _ADL2_Flush_Driver_Data(adl_Context, adl_Display_DisplayIndex);

			//Return result
			AVDebugWriteLine("Created custom Eyefinity: " << adl_Res0 << " / " << slsMapIndexOut);
			return adl_Res0 == ADL_OK && slsMapIndexOut != -1;
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
			int slsMapIndexCount = 0;
			int* slsMapIndexList{};
			_ADL2_Display_SLSMapIndexList_Get(adl_Context, displayAdapterIndex, &slsMapIndexCount, &slsMapIndexList, ADL_DISPLAY_SLSMAPINDEXLIST_OPTION_ACTIVE);

			//Check index count
			if (slsMapIndexCount <= 0)
			{
				AVDebugWriteLine("Failed deleting all Eyefinity, no active sls.");
				return false;
			}

			//Delete SLS map configurations
			int slsDeleteCount = 0;
			for (int index = 0; index < slsMapIndexCount; index++)
			{
				AVDebugWriteLine("Deleting sls map configuration: " << slsMapIndexList[index]);
				adl_Res0 = _ADL2_Display_SLSMapConfig_Delete(adl_Context, displayAdapterIndex, slsMapIndexList[index]);
				if (adl_Res0 == ADL_OK) { slsDeleteCount++; }
			}

			//Get SLS map indexes
			int slsMapIndexCountNew = 0;
			int* slsMapIndexListNew{};
			_ADL2_Display_SLSMapIndexList_Get(adl_Context, displayAdapterIndex, &slsMapIndexCountNew, &slsMapIndexListNew, ADL_DISPLAY_SLSMAPINDEXLIST_OPTION_ACTIVE);

			//Flush driver data
			//adl_Res0 = _ADL2_Flush_Driver_Data(adl_Context, adl_Display_DisplayIndex);

			//Return result
			AVDebugWriteLine("Deleted all Eyefinity count: " << slsDeleteCount);
			return slsDeleteCount > 0 && (slsMapIndexCount != slsMapIndexCountNew);
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