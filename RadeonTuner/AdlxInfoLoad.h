#pragma once
#include "pch.h"
#include "resource.h"
#include "MainPage.h"
#include "AdlxVariables.h"
#include "AppVariables.h"
#include "SettingEnumStrings.h"

namespace winrt::RadeonTuner::implementation
{
	std::wstring MainPage::AdlxInfoGpu()
	{
		try
		{
			//Set gpu information
			std::wstring gpu_info = L"";

			//Device name
			try
			{
				const char* productName = NULL;
				adlx_Res0 = ppGpuInfo->Name(&productName);
				gpu_info += L"Device name: " + char_to_wstring(productName);
			}
			catch (...) {}

			//Device codename
			try
			{
				const char* codeName = NULL;
				adlx_Res0 = ppGpuInfo->ProductName(&codeName);
				gpu_info += L"\nDevice codename: " + char_to_wstring(codeName);
			}
			catch (...) {}

			//Device identifier
			std::wstring device_id = AdlxGetGpuIdentifier(ppGpuInfo);
			if (!device_id.empty())
			{
				gpu_info += L"\nDevice identifier: " + device_id;
			}

			//Load driver version
			//Note: this may cause ntdll crash that cannot be catched with old drivers
			try
			{
				const char* driverVersion = NULL;
				const char* driverWindows = NULL;
				adlx_uint driverYear, driverMonth, driverDay;
				adlx_Res0 = ppGpuInfo->AMDSoftwareVersion(&driverVersion);
				adlx_Res0 = ppGpuInfo->AMDWindowsDriverVersion(&driverWindows);
				adlx_Res0 = ppGpuInfo->AMDSoftwareReleaseDate(&driverYear, &driverMonth, &driverDay);
				std::wstring driverDate = number_to_wstring(driverYear) + L"/" + number_to_wstring(driverMonth) + L"/" + number_to_wstring(driverDay);
				gpu_info += L"\nDriver version: " + char_to_wstring(driverVersion) + L" / " + char_to_wstring(driverWindows) + L" / " + driverDate;
			}
			catch (...) {}

			//Bios information
			try
			{
				const char* biosPart = NULL;
				const char* biosVersion = NULL;
				const char* biosDate = NULL;
				ppGpuInfo->BIOSInfo(&biosPart, &biosVersion, &biosDate);
				gpu_info += L"\nBios version: " + char_to_wstring(biosPart) + L" / " + char_to_wstring(biosVersion) + L" / " + char_to_wstring(biosDate);
			}
			catch (...) {}

			//Memory information
			try
			{
				adlx_uint totalVRAM;
				const char* typeVRAM = NULL;
				adlx_Res0 = ppGpuInfo->TotalVRAM(&totalVRAM);
				adlx_Res0 = ppGpuInfo->VRAMType(&typeVRAM);
				gpu_info += L"\nMemory: " + number_to_wstring(totalVRAM) + L"MB " + char_to_wstring(typeVRAM);
			}
			catch (...) {}

			//PCI bus information
			try
			{
				adlx_uint busLaneWidth = 0;
				ADLX_PCI_BUS_TYPE busType = UNDEFINED;
				adlx_Res0 = ppGpuInfo->PCIBusType(&busType);
				adlx_Res0 = ppGpuInfo->PCIBusLaneWidth(&busLaneWidth);
				//Fix what if bustype > busTypeStrings size
				gpu_info += L"\nBus type: " + ADLX_PCI_BUS_TYPE_STRING[busType];
				if (busLaneWidth > 0)
				{
					gpu_info += L" x" + number_to_wstring(busLaneWidth);
				}
			}
			catch (...) {}

			//Resizable BAR status
			try
			{
				IADLXSmartAccessMemoryPtr ppSmartAccessMemory;
				adlx_Res0 = ppGPUTuningServices->GetSmartAccessMemory(ppGpuInfo, &ppSmartAccessMemory);
				if (ppSmartAccessMemory != NULL)
				{
					adlx_Res0 = ppSmartAccessMemory->IsEnabled(&adlx_Bool);
					if (adlx_Bool)
					{
						gpu_info += L"\nResizable BAR / SAM: Enabled";
					}
					else
					{
						gpu_info += L"\nResizable BAR / SAM: Disabled";
					}
				}
			}
			catch (...) {}

			//Return information
			return gpu_info;
		}
		catch (...) {}
		return L"Failed to load gpu information.";
	}

	std::wstring MainPage::AdlxInfoDisplay()
	{
		try
		{
			//Set display information
			std::wstring display_info = L"";

			//Display name
			try
			{
				const char* displayName = NULL;
				adlx_Res0 = ppDisplayInfo->Name(&displayName);
				display_info += L"Display name: " + char_to_wstring(displayName);
			}
			catch (...) {}

			//Native resolution
			try
			{
				adlx_int hResolution, vResolution;
				adlx_Res0 = ppDisplayInfo->NativeResolution(&hResolution, &vResolution);
				display_info += L"\nNative resolution: " + number_to_wstring(hResolution) + L"x" + number_to_wstring(vResolution);
			}
			catch (...) {}

			//Refresh rate
			try
			{
				adlx_double refreshRate;
				adlx_Res0 = ppDisplayInfo->RefreshRate(&refreshRate);
				display_info += L"\nRefresh rate: " + number_to_wstring((int)refreshRate) + L" Hz";
			}
			catch (...) {}

			//Pixel clock
			try
			{
				adlx_uint pixelClock;
				adlx_Res0 = ppDisplayInfo->PixelClock(&pixelClock);
				display_info += L"\nPixel clock: " + number_to_wstring(pixelClock) + L" KHz";
			}
			catch (...) {}

			//Connector type
			try
			{
				ADLX_DISPLAY_CONNECTOR_TYPE connectType;
				adlx_Res0 = ppDisplayInfo->ConnectorType(&connectType);
				display_info += L"\nConnector type: " + ADLX_DISPLAY_CONNECTOR_TYPE_STRING[connectType];
			}
			catch (...) {}

			//Scan type
			try
			{
				ADLX_DISPLAY_SCAN_TYPE scanType;
				adlx_Res0 = ppDisplayInfo->ScanType(&scanType);
				display_info += L"\nScan type: " + ADLX_DISPLAY_SCAN_TYPE_STRING[scanType];
			}
			catch (...) {}

			//Get display connectivity experience
			IADLXDisplayConnectivityExperiencePtr ppDisplayConnectivityExperience;
			try
			{
				adlx_Res0 = ppDispServices->GetDisplayConnectivityExperience(ppDisplayInfo, &ppDisplayConnectivityExperience);
			}
			catch (...) {}

			//DP link rate
			try
			{
				ADLX_DP_LINK_RATE dpLinkRate;
				adlx_Res0 = ppDisplayConnectivityExperience->GetDPLinkRate(&dpLinkRate);
				if (dpLinkRate > 0)
				{
					display_info += L"\nDP link rate: " + ADLX_DP_LINK_RATE_STRING[dpLinkRate];
				}
			}
			catch (...) {}

			//Link protection
			try
			{
				adlx_bool linkProtection;
				adlx_Res0 = ppDisplayConnectivityExperience->IsEnabledLinkProtection(&linkProtection);
				std::wstring linkProtectionString = linkProtection ? L"Disabled" : L"Enabled";
				display_info += L"\nLink protection: " + linkProtectionString;
			}
			catch (...) {}

			//Fix add current resolution, FreeSync range and HDR status

			//Return information
			return display_info;
		}
		catch (...) {}
		return L"Failed to load display information.";
	}

	std::wstring MainPage::AdlxInfoApplication()
	{
		try
		{
			//Get versions
			std::wstring app_version = L"V" + string_to_wstring(GetVersionFromResource(AppVariables::hInstance));
			std::wstring adlx_version = L" / ADLX " + char_to_wstring(ppADLXHelper.QueryVersion());

			return L"Made by Arnold Vink\n" + app_version + adlx_version;
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

	std::wstring MainPage::AdlxGetGpuIdentifier(IADLXGPU2Ptr ppGpuPtr)
	{
		std::wstring device_id = L"";
		try
		{
			const char* vendorId = NULL;
			adlx_Res0 = ppGpuPtr->VendorId(&vendorId);
			if (vendorId != NULL)
			{
				device_id += char_to_wstring(vendorId);
				device_id += L" ";
			}

			const char* deviceId = NULL;
			adlx_Res0 = ppGpuPtr->DeviceId(&deviceId);
			if (deviceId != NULL)
			{
				device_id += char_to_wstring(deviceId);
				device_id += L" - ";
			}

			const char* subSystemVendorId = NULL;
			adlx_Res0 = ppGpuPtr->SubSystemVendorId(&subSystemVendorId);
			if (subSystemVendorId != NULL)
			{
				device_id += char_to_wstring(subSystemVendorId);
				device_id += L" ";
			}

			const char* subSystemId = NULL;
			adlx_Res0 = ppGpuPtr->SubSystemId(&subSystemId);
			if (subSystemId != NULL)
			{
				device_id += char_to_wstring(subSystemId);
				device_id += L" - ";
			}

			const char* revisionId = NULL;
			adlx_Res0 = ppGpuPtr->RevisionId(&revisionId);
			if (revisionId != NULL)
			{
				device_id += char_to_wstring(revisionId);
				device_id += L" - ";
			}

			int uniqueId = -1;
			adlx_Res0 = ppGpuPtr->UniqueId(&uniqueId);
			if (uniqueId > 0)
			{
				device_id += number_to_wstring(uniqueId);
			}
		}
		catch (...) {}
		return device_id;
	}

	std::wstring MainPage::AdlxGetDisplayIdentifier(IADLXDisplayPtr ppDisplayInfo)
	{
		std::wstring device_id = L"";
		try
		{
			uint32_t manufacturerId = NULL;
			adlx_Res0 = ppDisplayInfo->ManufacturerID(&manufacturerId);
			if (manufacturerId != NULL)
			{
				device_id += number_to_wstring(manufacturerId);
				device_id += L" ";
			}

			const char* displayName = NULL;
			adlx_Res0 = ppDisplayInfo->Name(&displayName);
			if (displayName != NULL)
			{
				device_id += char_to_wstring(displayName);
				device_id += L" ";
			}

			size_t uniqueId = -1;
			adlx_Res0 = ppDisplayInfo->UniqueId(&uniqueId);
			if (uniqueId > 0)
			{
				device_id += number_to_wstring(uniqueId);
			}
		}
		catch (...) {}
		return device_id;
	}
}