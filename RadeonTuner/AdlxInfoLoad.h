#pragma once
#include "pch.h"
#include "resource.h"
#include "MainPage.h"
#include "MainVariables.h"
#include "AppVariables.h"
#include "SettingEnumStrings.h"

namespace winrt::RadeonTuner::implementation
{
	std::wstring MainPage::AdlxInfoGpu()
	{
		try
		{
			//Fix missing Pixel and Texture Fillrate, Shaders Count, Bus Width, Fabrication Technology, Transistor Count, Resizable Bar.

			//Set gpu information
			std::wstring gpu_info = L"";

			//Get gpu information
			std::optional<AdapterInfo> gpuInfo = AdlGetGpuByAdapterIndex(adl_Gpu_AdapterIndex);
			if (gpuInfo.has_value())
			{
				AdapterInfo adapterInfo = gpuInfo.value();

				//Device name
				gpu_info += L"Device name: " + char_to_wstring(adapterInfo.strAdapterName);

				//Device identifier
				std::wstring device_id = char_to_wstring(adapterInfo.strPNPString);
				device_id = wstring_get_between(device_id, L"\\", L"\\");
				gpu_info += L"\nDevice identifier: " + device_id;
			}

			////Device codename
			//Note: this can cause ntdll crash that cannot be catched on certain gpu's
			//try
			//{
			//	const int productNameSize = 32;
			//	char productNameBuffer[productNameSize]{};
			//	adl_Res0 = _ADL2_Adapter_ProductName_Get(adl_Context, adl_Gpu_AdapterIndex, productNameBuffer);
			//	if (adl_Res0 == ADL_OK)
			//	{
			//		gpu_info += L"\nDevice codename: " + char_to_wstring(productNameBuffer);
			//	}
			//}
			//catch (...) {}

			//Driver information
			try
			{
				ADLVersionsInfoX2 driverInfo{};
				adl_Res0 = _ADL2_Graphics_VersionsX3_Get(adl_Context, adl_Gpu_AdapterIndex, &driverInfo);
				if (adl_Res0 == ADL_OK)
				{
					gpu_info += L"\nDriver version: " + char_to_wstring(driverInfo.strCrimsonVersion) + L" / " + char_to_wstring(driverInfo.strDriverVer);
				}
			}
			catch (...) {}

			//Bios information
			try
			{
				ADLBiosInfo biosInfo{};
				adl_Res0 = _ADL2_Adapter_VideoBiosInfo_Get(adl_Context, adl_Gpu_AdapterIndex, &biosInfo);
				if (adl_Res0 == ADL_OK)
				{
					gpu_info += L"\nBios version: " + char_to_wstring(biosInfo.strPartNumber) + L" / " + char_to_wstring(biosInfo.strVersion) + L" / " + char_to_wstring(biosInfo.strDate);
				}
			}
			catch (...) {}

			//Memory information
			try
			{
				ADLMemoryInfoX4 lpMemoryInfoX4{};
				adl_Res0 = _ADL2_Adapter_MemoryInfoX4_Get(adl_Context, adl_Gpu_AdapterIndex, &lpMemoryInfoX4);
				if (adl_Res0 == ADL_OK)
				{
					gpu_info += L"\nMemory details: " + number_to_wstring(lpMemoryInfoX4.iMemorySize / 1024 / 1024) + L"MB ";
					gpu_info += char_to_wstring(lpMemoryInfoX4.strMemoryType);

					if (lpMemoryInfoX4.iVramVendorRevId > 0)
					{
						gpu_info += L" (" + VramVendorNameFromId(lpMemoryInfoX4.iVramVendorRevId) + L")";
					}
					if (lpMemoryInfoX4.iMemoryBandwidth > 0)
					{
						gpu_info += L"\nMemory bandwidth: " + number_to_wstring(lpMemoryInfoX4.iMemoryBandwidth) + L"MB/s";
					}
				}
			}
			catch (...) {}

			//Asic Information
			try
			{
				ADLGcnInfo gcnInfo{};
				adl_Res0 = _ADL2_GcnAsicInfo_Get(adl_Context, adl_Gpu_AdapterIndex, &gcnInfo);
				if (adl_Res0 == ADL_OK)
				{
					if (gcnInfo.CuCount > 0)
					{
						gpu_info += L"\nCompute (WGP) units: " + number_to_wstring(gcnInfo.CuCount);
					}
					if (gcnInfo.RopCount > 0)
					{
						gpu_info += L"\nRender output units: " + number_to_wstring(gcnInfo.RopCount);
					}
					if (gcnInfo.TexCount > 0)
					{
						gpu_info += L"\nTexture mapping units: " + number_to_wstring(gcnInfo.TexCount);
					}
				}
			}
			catch (...) {}

			//PCI Bus information
			try
			{
				ADLChipSetInfo adlChipSetInfo{};
				adl_Res0 = _ADL2_Adapter_ChipSetInfo_Get(adl_Context, adl_Gpu_AdapterIndex, &adlChipSetInfo);
				if (adl_Res0 == ADL_OK)
				{
					if (adlChipSetInfo.iBusType > 0)
					{
						gpu_info += L"\nBus type: " + ADLX_PCI_BUS_TYPE_STRING[adlChipSetInfo.iBusType + 1];
						if (adlChipSetInfo.iCurrentPCIELaneWidth > 0)
						{
							gpu_info += L" (x" + number_to_wstring(adlChipSetInfo.iCurrentPCIELaneWidth) + L" / x" + number_to_wstring(adlChipSetInfo.iMaxPCIELaneWidth) + L")";
						}
					}
				}
			}
			catch (...) {}

			//Return information
			AVDebugWriteLine("Loaded gpu information.");
			return gpu_info;
		}
		catch (...) {}
		return L"Failed to load gpu information.";
	}

	std::wstring MainPage::AdlxInfoDisplay()
	{
		try
		{
			//Fix missing Current Resolution, FreeSync Range and HDR status, Refresh rate, Pixel clock

			//Set display information
			std::wstring display_info = L"";

			//Get connected displays
			std::vector<ADLDisplayInfo> displayList = AdlGetDisplayByAdapterIndex(adl_Gpu_AdapterIndex);
			for (ADLDisplayInfo displayInfo : displayList)
			{
				//Display name
				display_info += L"Display name: " + char_to_wstring(displayInfo.strDisplayName);

				//Connector type
				display_info += L" (" + ADLX_DISPLAY_CONNECTOR_TYPE_STRING[displayInfo.iDisplayConnector - 1] + L")\n";
			}

			//Check connected displays
			if (displayList.empty())
			{
				display_info = L"No connected displays on selected GPU.";
			}

			//Trim string ending
			display_info = wstring_trim_right(display_info);

			//Return information
			AVDebugWriteLine("Loaded display information.");
			return display_info;
		}
		catch (...) {}
		return L"Failed to load display information.";
	}

	std::wstring MainPage::AdlxInfoApplication()
	{
		try
		{
			//Get version
			std::wstring app_version = L"V" + string_to_wstring(GetVersionFromResource(AppVariables::hInstance));

			//Return version
			AVDebugWriteLine("Loaded application information.");
			return L"Made by Arnold Vink\n" + app_version;
		}
		catch (...) {}
		return L"Failed to load application information.";
	}

	void MainPage::AdlxInfoLoad()
	{
		try
		{
			//Set information
			textblock_GpuInfo().Text(AdlxInfoGpu());
			textblock_DisplayInfo().Text(AdlxInfoDisplay());
			textblock_AppInfo().Text(AdlxInfoApplication());

			//Set result
			AVDebugWriteLine("ADLX loaded information.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading information.");
		}
	}
}