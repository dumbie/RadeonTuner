#pragma once
#include "pch.h"

namespace winrt::RadeonTuner::implementation
{
	std::vector<AdapterInfo> MainPage::AdlGetGpuAll()
	{
		std::vector<AdapterInfo> gpuList;
		try
		{
			int adapterInfoCount = 0;
			int adapterInfoFilterCount = 0;
			auto adapterInfoList = AVFin<AdapterInfo*>(AVFinMethod::FreeMarshal);
			adl_Res0 = _ADL2_Adapter_AdapterInfoX3_Get(adl_Context, -1, &adapterInfoCount, &adapterInfoList.Get());
			for (int i = 0; i < adapterInfoCount; i++)
			{
				//Get adapter information
				AdapterInfo adapterInfo = adapterInfoList.Get()[i];

				//Check if adapter vendor is AMD
				if (adapterInfo.iVendorID != 1002 && adapterInfo.iVendorID != -1002)
				{
					continue;
				}

				//Check if we have access to GPU
				//Note: checks if driver is not installed for (integrated) gpu or device is disabled in device manager
				//Fix ADL2_Adapter_Accessibility_Get always fails when using DCH / UWP or downgraded driver
				int lpAccess;
				adl_Res0 = _ADL2_Adapter_Accessibility_Get(adl_Context, adapterInfo.iAdapterIndex, &lpAccess);
				if (adl_Res0 != ADL_OK)
				{
					//AVDebugWriteLine("GPU is not accessible: " << adapterInfo.iAdapterIndex << " / " << lpAccess << " / " << adapterInfo.strUDID);
					continue;
				}

				//Check if GPU is present and exists
				if (adapterInfo.iPresent != true || adapterInfo.iExist != true)
				{
					//AVDebugWriteLine("GPU is not present or does not exist: " << adapterInfo.iAdapterIndex << " / " << adapterInfo.strUDID);
					continue;
				}

				//Check duplicate adapter
				bool duplicate = false;
				for (AdapterInfo listInfo : gpuList)
				{
					if (string_contains(listInfo.strPNPString, adapterInfo.strPNPString))
					{
						duplicate = true;
						break;
					}
				}

				//Add adapter to list
				if (!duplicate)
				{
					gpuList.push_back(adapterInfo);
					adapterInfoFilterCount++;
				}
			}

			//Sort GPU list by asic family
			//Note: Prioritize dedicated GPU over integrated GPU to select it by default.
			try
			{
				size_t rotatePos = 0;
				for (size_t i = 0; i < gpuList.size(); i++)
				{
					//Get adapter index
					int gpuAdapterIndex = gpuList[i].iAdapterIndex;

					//Get asic family type
					int asicTypes = -1;
					int asicValid = -1;
					adl_Res0 = _ADL2_Adapter_ASICFamilyType_Get(adl_Context, gpuAdapterIndex, &asicTypes, &asicValid);

					//Check asic family type
					bool asicGpuDedicated = (asicTypes & ADL_ASIC_DISCRETE) == ADL_ASIC_DISCRETE;
					//bool asicGpuIntegrated = (asicTypes & ADL_ASIC_INTEGRATED) == ADL_ASIC_INTEGRATED;

					//Move dedicated gpu to top of list
					if (asicGpuDedicated)
					{
						//AVDebugWriteLine("Dedicated GPU detected, moving it to top of list.");
						std::rotate(gpuList.begin() + rotatePos, gpuList.begin() + i, gpuList.begin() + i + 1);
						rotatePos++;
					}
				}
			}
			catch (...) {}

			//Return result
			//AVDebugWriteLine("Got all GPU's: " << adapterInfoFilterCount << " / " << adapterInfoCount);
			return gpuList;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to get all GPU's (Exception)");
			return gpuList;
		}
	}

	std::optional<AdapterInfo> MainPage::AdlGetGpuByDeviceId(std::wstring deviceId)
	{
		try
		{
			//Get all GPU's
			for (AdapterInfo adapterInfo : AdlGetGpuAll())
			{
				//Device identifier
				std::wstring adapterDeviceId = char_to_wstring(adapterInfo.strPNPString);
				adapterDeviceId = wstring_get_between(adapterDeviceId, L"\\", L"\\");

				//Check device identifier
				if (adapterDeviceId == deviceId)
				{
					AVDebugWriteLine("Got GPU by device identifier: " << adapterInfo.iAdapterIndex << " / " << adapterInfo.strPNPString);
					return adapterInfo;
				}
			}

			//Return result
			AVDebugWriteLine(L"Failed to get GPU by device identifier (Not found) " << deviceId);
			return std::nullopt;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to get GPU by device identifier (Exception)");
			return std::nullopt;
		}
	}

	std::optional<AdapterInfo> MainPage::AdlGetGpuByAdapterIndex(int adapterIndex)
	{
		try
		{
			int adapterInfoCount = 0;
			auto adapterInfoList = AVFin<AdapterInfo*>(AVFinMethod::FreeMarshal);
			adl_Res0 = _ADL2_Adapter_AdapterInfoX3_Get(adl_Context, adapterIndex, &adapterInfoCount, &adapterInfoList.Get());

			//Get result
			AdapterInfo adapterInfo = adapterInfoList.Get()[0];

			//Return result
			AVDebugWriteLine("Got GPU by adapter index: " << adapterIndex << " / " << adapterInfo.strPNPString);
			return adapterInfo;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to get GPU by adapter index (Exception)");
			return std::nullopt;
		}
	}

	std::vector<ADLDisplayInfo> MainPage::AdlGetDisplayAll()
	{
		std::vector<ADLDisplayInfo> displayList;
		try
		{
			//Fix when a display is connected but has no power DisplayInfo_Get may return invalid values instead of no values.
			//Fix ADL2_Display_DisplayInfo_Get always fails when using DCH / UWP or downgraded driver

			//Get all GPU's
			int displayConnectedCount = 0;
			for (AdapterInfo adapterInfo : AdlGetGpuAll())
			{
				//Get all displays connected to gpu
				int displayInfoCount = 0;
				auto displayInfoList = AVFin<ADLDisplayInfo*>(AVFinMethod::FreeMarshal);
				adl_Res0 = _ADL2_Display_DisplayInfo_Get(adl_Context, adapterInfo.iAdapterIndex, &displayInfoCount, &displayInfoList.Get(), true);
				for (int i = 0; i < displayInfoCount; i++)
				{
					ADLDisplayInfo displayInfo = displayInfoList.Get()[i];
					bool validIndex = displayInfo.displayID.iDisplayLogicalAdapterIndex >= 0 && displayInfo.displayID.iDisplayLogicalIndex >= 0 && displayInfo.displayID.iDisplayLogicalAdapterIndex <= 2048 && displayInfo.displayID.iDisplayLogicalIndex <= 2048;
					bool displayConnected = (displayInfo.iDisplayInfoValue & ADL_DISPLAY_DISPLAYINFO_DISPLAYCONNECTED) == ADL_DISPLAY_DISPLAYINFO_DISPLAYCONNECTED;
					bool displayMapped = (displayInfo.iDisplayInfoValue & ADL_DISPLAY_DISPLAYINFO_DISPLAYMAPPED) == ADL_DISPLAY_DISPLAYINFO_DISPLAYMAPPED;
					if (validIndex && displayConnected && displayMapped)
					{
						displayList.push_back(displayInfo);
						displayConnectedCount++;
					}
				}
			}

			//Return result
			//AVDebugWriteLine("Got all displays: " << displayConnectedCount);
			return displayList;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to get all displays (Exception)");
			return displayList;
		}
	}

	std::vector<ADLDisplayInfo> MainPage::AdlGetDisplayByAdapterIndex(int adapterIndex)
	{
		std::vector<ADLDisplayInfo> displayList;
		try
		{
			//Get all displays connected to gpu
			int displayConnectedCount = 0;
			int displayInfoCount = 0;
			auto displayInfoList = AVFin<ADLDisplayInfo*>(AVFinMethod::FreeMarshal);
			adl_Res0 = _ADL2_Display_DisplayInfo_Get(adl_Context, adapterIndex, &displayInfoCount, &displayInfoList.Get(), true);
			//Fix ADL2_Display_DisplayInfo_Get always fails when using DCH / UWP or downgraded driver
			for (int i = 0; i < displayInfoCount; i++)
			{
				ADLDisplayInfo displayInfo = displayInfoList.Get()[i];
				bool validIndex = displayInfo.displayID.iDisplayLogicalAdapterIndex >= 0 && displayInfo.displayID.iDisplayLogicalIndex >= 0 && displayInfo.displayID.iDisplayLogicalAdapterIndex <= 2048 && displayInfo.displayID.iDisplayLogicalIndex <= 2048;
				bool displayConnected = (displayInfo.iDisplayInfoValue & ADL_DISPLAY_DISPLAYINFO_DISPLAYCONNECTED) == ADL_DISPLAY_DISPLAYINFO_DISPLAYCONNECTED;
				bool displayMapped = (displayInfo.iDisplayInfoValue & ADL_DISPLAY_DISPLAYINFO_DISPLAYMAPPED) == ADL_DISPLAY_DISPLAYINFO_DISPLAYMAPPED;
				if (validIndex && displayConnected && displayMapped)
				{
					displayList.push_back(displayInfo);
					displayConnectedCount++;
				}
			}

			//Return result
			AVDebugWriteLine("Got all displays by adapter index: " << adapterIndex << " / " << displayConnectedCount);
			return displayList;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to get all displays by adapter index (Exception)");
			return displayList;
		}
	}

	std::optional<ADLDisplayInfo> MainPage::AdlGetDisplayByDisplayIndex(int adapterIndex, int displayIndex)
	{
		try
		{
			//Get all displays
			std::vector<ADLDisplayInfo> displayList = AdlGetDisplayAll();

			//Find display by identifier
			for (ADLDisplayInfo displayInfo : displayList)
			{
				if (displayInfo.displayID.iDisplayLogicalAdapterIndex == adapterIndex && displayInfo.displayID.iDisplayLogicalIndex == displayIndex)
				{
					//Return result
					AVDebugWriteLine("Got display by index: " << adapterIndex << " / " << displayIndex << " / " << displayInfo.strDisplayName);
					return displayInfo;
				}
			}

			//Return result
			AVDebugWriteLine("Failed to get display by index (Not found)");
			return std::nullopt;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to get display by index (Exception)");
			return std::nullopt;
		}
	}
}