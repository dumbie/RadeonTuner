#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{

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

			int displayColumns = slider_Eyefinity_Rows().Value();
			int displayRows = slider_Eyefinity_Columns().Value();
			int displayCount = listview_EyefinityMonitorIndex().Items().Size();

			//Check maximum allowed displays
			if (displayColumns + displayRows > 8)
			{
				AVDebugWriteLine("SLS display allowed limit reached.");
				return false;
			}

			//Check maximum total displays
			if (((displayColumns + displayRows) - 2) >= displayCount)
			{
				AVDebugWriteLine("SLS display total limit reached.");
				return false;
			}

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

			AVDebugWriteLine("Setting SLS map to: R" << displayColumns << "/C" << displayRows << "/D" << displayCount << "/O" << displayOrientationDegree << "/B" << displayBezelPercentage);

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
			for (int x = 0; x < displayColumns; x++)
			{
				for (int y = 0; y < displayRows; y++)
				{
					//Set indexes
					slsTargets[slsTargetCurrent].iAdapterIndex = displayAdapterIndex;
					slsTargets[slsTargetCurrent].iSLSMapIndex = slsMapIndexIn;

					//Set display target
					slsTargets[slsTargetCurrent].displayTarget = ADLDisplayTarget{};
					slsTargets[slsTargetCurrent].displayTarget.displayID.iDisplayLogicalIndex = displayIndexes[slsTargetCurrent];
					slsTargets[slsTargetCurrent].displayTarget.displayID.iDisplayLogicalAdapterIndex = displayAdapterIndex;

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
				AVDebugWriteLine("Failed to create and set sls map configuration: " << adl_Res0 << " / " << displayAdapterIndex);
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

			//Check if Eyefinity is enabled
			if (!Adl_Eyefinity_IsEnabled(displayAdapterIndex))
			{
				AVDebugWriteLine("Cannot delete Eyefinity when it's not enabled.");
				return false;
			}

			AVDebugWriteLine("Deleting all Eyefinity for adapter: " << displayAdapterIndex);

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

	bool MainPage::Adl_Eyefinity_IsEnabled(int displayAdapterIndex)
	{
		try
		{
			//Enable SLS environment workaround
			SetEnvironmentVariableA("ADL_4KWORKAROUND_CANCEL", "TRUE");

			//Get display configuration
			int displayMapCount;
			AVFin<ADLDisplayMap*> displayMap = AVFin<ADLDisplayMap*>(AVFinMethod::FreeMarshal);

			int displayTargetCount;
			AVFin<ADLDisplayTarget*> displayTarget = AVFin<ADLDisplayTarget*>(AVFinMethod::FreeMarshal);

			adl_Res0 = _ADL2_Display_DisplayMapConfig_Get(adl_Context, displayAdapterIndex, &displayMapCount, &displayMap.Get(), &displayTargetCount, &displayTarget.Get(), ADL_DISPLAY_DISPLAYMAP_OPTION_GPUINFO);
			if (adl_Res0 != ADL_OK)
			{
				//Return result
				//AVDebugWriteLine("Failed to get display map configuration: " << adl_Res0);
				return false;
			}

			//Get current display resolution (SLS included)
			int displayWidth = displayMap.Get()->displayMode.iXRes;
			int displayHeight = displayMap.Get()->displayMode.iYRes;

			//Get SLS index
			int slsMapIndex = -1;
			adl_Res0 = _ADL2_Display_SLSMapIndex_Get(adl_Context, displayAdapterIndex, displayTargetCount, displayTarget.Get(), &slsMapIndex);
			if (adl_Res0 != ADL_OK)
			{
				//Return result
				//AVDebugWriteLine("Failed to get SLS index: " << adl_Res0);
				return false;
			}
			if (slsMapIndex <= 0)
			{
				//Return result
				//AVDebugWriteLine("No valid SLS index found.");
				return false;
			}

			//Get SLS configuration
			ADLSLSMap slsMap;

			int slsTargetsCount = 0;
			AVFin<ADLSLSTarget*> slsTargets = AVFin<ADLSLSTarget*>(AVFinMethod::FreeMarshal);

			int slsStandardModesCount = 0;
			AVFin<ADLSLSMode*> slsStandardModes = AVFin<ADLSLSMode*>(AVFinMethod::FreeMarshal);

			int slsBezelModesCount = 0;
			AVFin<ADLBezelTransientMode*> slsBezelModes = AVFin<ADLBezelTransientMode*>(AVFinMethod::FreeMarshal);

			int slsTransientModesCount = 0;
			AVFin<ADLBezelTransientMode*> slsTransientModes = AVFin<ADLBezelTransientMode*>(AVFinMethod::FreeMarshal);

			int slsStandardModesOffsetsCount = 0;
			AVFin<ADLSLSOffset*> slsStandardModesOffsets = AVFin<ADLSLSOffset*>(AVFinMethod::FreeMarshal);

			int slsBezelModesOffsetsCount = 0;
			AVFin<ADLSLSOffset*> slsBezelModesOffsets = AVFin<ADLSLSOffset*>(AVFinMethod::FreeMarshal);

			adl_Res0 = _ADL2_Display_SLSMapConfigX2_Get(adl_Context, displayAdapterIndex, slsMapIndex, &slsMap, &slsTargetsCount, &slsTargets.Get(), &slsStandardModesCount, &slsStandardModes.Get(), &slsStandardModesOffsetsCount, &slsStandardModesOffsets.Get(), &slsBezelModesCount, &slsBezelModes.Get(), &slsTransientModesCount, &slsTransientModes.Get(), &slsBezelModesOffsetsCount, &slsBezelModesOffsets.Get(), ADL_DISPLAY_SLSMAPCONFIG_GET_OPTION_RELATIVETO_CURRENTANGLE);
			if (adl_Res0 != ADL_OK)
			{
				//Return result
				//AVDebugWriteLine("Failed to get SLS map configuration: " << adl_Res0);
				return false;
			}

			//Check if Display resolution matches SLS resolution
			for (int i = 0; i < slsStandardModesCount; i++)
			{
				int slsWidth = slsStandardModes.Get()[i].displayMode.iXRes;
				int slsHeight = slsStandardModes.Get()[i].displayMode.iYRes;
				if (slsHeight == displayHeight && slsWidth == displayWidth)
				{
					//AVDebugWriteLine("Found matching Display and SLS resolution.");
					//AVDebugWriteLine("SLS Width: " << slsWidth << " / Display Width: " << displayWidth);
					//AVDebugWriteLine("SLS Height: " << slsHeight << " / Display Height: " << displayHeight);
					return true;
				}
			}
		}
		catch (...) {}
		//AVDebugWriteLine("No SLS configuration found.");
		return false;
	}

	bool MainPage::Adl_Eyefinity_Toggle(int displayAdapterIndex, bool setEnabled)
	{
		try
		{
			//Check if Eyefinity is enabled or disabled
			bool eyefinityEnabled = Adl_Eyefinity_IsEnabled(displayAdapterIndex);
			if (setEnabled && eyefinityEnabled)
			{
				//AVDebugWriteLine("Eyefinity is already enabled.");
				return true;
			}
			else if (!setEnabled && !eyefinityEnabled)
			{
				//AVDebugWriteLine("Eyefinity is already disabled.");
				return true;
			}

			//Fix set display to duplicate or extended mode to allow Eyefinity toggle

			//Enable SLS environment workaround
			SetEnvironmentVariableA("ADL_4KWORKAROUND_CANCEL", "TRUE");

			//Get display configuration
			int displayMapCount;
			AVFin<ADLDisplayMap*> displayMap = AVFin<ADLDisplayMap*>(AVFinMethod::FreeMarshal);

			int displayTargetCount;
			AVFin<ADLDisplayTarget*> displayTarget = AVFin<ADLDisplayTarget*>(AVFinMethod::FreeMarshal);

			adl_Res0 = _ADL2_Display_DisplayMapConfig_Get(adl_Context, displayAdapterIndex, &displayMapCount, &displayMap.Get(), &displayTargetCount, &displayTarget.Get(), ADL_DISPLAY_DISPLAYMAP_OPTION_GPUINFO);
			if (adl_Res0 != ADL_OK)
			{
				//Return result
				AVDebugWriteLine("Failed to get display map configuration: " << adl_Res0);
				return false;
			}

			//Get SLS index
			int slsMapIndex = -1;
			adl_Res0 = _ADL2_Display_SLSMapIndex_Get(adl_Context, displayAdapterIndex, displayTargetCount, displayTarget.Get(), &slsMapIndex);
			if (adl_Res0 != ADL_OK)
			{
				//Return result
				AVDebugWriteLine("Failed to get SLS map index: " << adl_Res0);
				return false;
			}
			if (slsMapIndex <= 0)
			{
				//Return result
				//AVDebugWriteLine("No valid SLS index found.");
				return false;
			}

			//Set SLS state
			adl_Res0 = _ADL2_Display_SLSMapConfig_SetState(adl_Context, displayAdapterIndex, slsMapIndex, setEnabled);

			//Return result
			AVDebugWriteLine("Set Eyefinity state: " << adl_Res0 << " / " << slsMapIndex << " / " << setEnabled);
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