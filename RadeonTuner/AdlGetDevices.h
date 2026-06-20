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
			AdapterInfo* adapterInfoList{};
			adl_Res0 = _ADL2_Adapter_AdapterInfoX3_Get(adl_Context, -1, &adapterInfoCount, &adapterInfoList);
			for (int i = 0; i < adapterInfoCount; i++)
			{
				//Get adapter information
				AdapterInfo adapterInfo = adapterInfoList[i];

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

			//Return result
			//AVDebugWriteLine("Got all GPU's: " << adapterInfoFilterCount);
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
				std::wstring device_id = char_to_wstring(adapterInfo.strPNPString);
				device_id = wstring_get_between(device_id, L"\\", L"\\");

				//Check device identifier
				if (device_id == deviceId)
				{
					AVDebugWriteLine("Got GPU by device identifier: " << adapterInfo.iAdapterIndex << " / " << deviceId);
					return adapterInfo;
				}
			}

			//Return result
			AVDebugWriteLine("Failed to get GPU by device identifier (Not found)");
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
			AdapterInfo* adapterInfoList{};
			adl_Res0 = _ADL2_Adapter_AdapterInfoX3_Get(adl_Context, adapterIndex, &adapterInfoCount, &adapterInfoList);

			//Return result
			AVDebugWriteLine("Got GPU by adapter index: " << adapterIndex);
			return adapterInfoList[0];
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
			//Get all GPU's
			int displayConnectedCount = 0;
			for (AdapterInfo adapterInfo : AdlGetGpuAll())
			{
				//Get all displays connected to gpu
				int displayInfoCount = 0;
				ADLDisplayInfo* displayInfoList{};
				adl_Res0 = _ADL2_Display_DisplayInfo_Get(adl_Context, adapterInfo.iAdapterIndex, &displayInfoCount, &displayInfoList, true);
				for (int i = 0; i < displayInfoCount; i++)
				{
					ADLDisplayInfo displayInfo = displayInfoList[i];
					if ((displayInfo.iDisplayInfoValue & ADL_DISPLAY_DISPLAYINFO_DISPLAYCONNECTED) == ADL_DISPLAY_DISPLAYINFO_DISPLAYCONNECTED)
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

	std::vector<ADLDisplayInfo> MainPage::AdlGetDisplayAllByAdapterIndex(int adapterIndex)
	{
		std::vector<ADLDisplayInfo> displayList;
		try
		{
			//Get all displays connected to gpu
			int displayConnectedCount = 0;
			int displayInfoCount = 0;
			ADLDisplayInfo* displayInfoList{};
			adl_Res0 = _ADL2_Display_DisplayInfo_Get(adl_Context, adapterIndex, &displayInfoCount, &displayInfoList, true);
			for (int i = 0; i < displayInfoCount; i++)
			{
				ADLDisplayInfo displayInfo = displayInfoList[i];
				if ((displayInfo.iDisplayInfoValue & ADL_DISPLAY_DISPLAYINFO_DISPLAYCONNECTED) == ADL_DISPLAY_DISPLAYINFO_DISPLAYCONNECTED)
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

	std::optional<ADLDisplayInfo> MainPage::AdlGetDisplayByDisplayIndex(int displayIndex)
	{
		try
		{
			//Get all displays
			std::vector<ADLDisplayInfo> displayList = AdlGetDisplayAll();

			//Find display by identifier
			for (ADLDisplayInfo displayInfo : displayList)
			{
				if (displayInfo.displayID.iDisplayLogicalIndex == displayIndex)
				{
					//Return result
					AVDebugWriteLine("Got display by index: " << displayIndex);
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