#pragma once
#include "pch.h"
#include "resource.h"
#include "MainPage.h"
#include "AdlxVariables.h"
#include "AppVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::AdlxInfoLoad()
	{
		//Device information string
		std::wstring device_info = L"";

		//Vendor identifier
		const char* vendorId = nullptr;
		adlx_Res0 = ppGpuInfo->VendorId(&vendorId);
		device_info += L"Vendor identifier: " + char_to_wstring(vendorId);

		//Product name
		const char* productName = nullptr;
		adlx_Res0 = ppGpuInfo->ProductName(&productName);
		device_info += L"\nProduct name: " + char_to_wstring(productName);

		//Load driver version
		const char* driverVersion = nullptr;
		const char* driverWindows = nullptr;
		adlx_uint driverYear, driverMonth, driverDay;
		adlx_Res0 = ppGpuInfo->AMDSoftwareVersion(&driverVersion);
		adlx_Res0 = ppGpuInfo->AMDWindowsDriverVersion(&driverWindows);
		adlx_Res0 = ppGpuInfo->AMDSoftwareReleaseDate(&driverYear, &driverMonth, &driverDay);
		std::wstring driverDate = number_to_wstring(driverYear) + L"/" + number_to_wstring(driverMonth) + L"/" + number_to_wstring(driverDay);
		device_info += L"\nDriver version: " + char_to_wstring(driverVersion) + L" / " + char_to_wstring(driverWindows) + L" / " + driverDate;

		//Load bios version
		const char* biosPart = nullptr;
		const char* biosVersion = nullptr;
		const char* biosDate = nullptr;
		ppGpuInfo->BIOSInfo(&biosPart, &biosVersion, &biosDate);
		device_info += L"\nBios version: " + char_to_wstring(biosPart) + L" / " + char_to_wstring(biosVersion) + L" / " + char_to_wstring(biosDate);

		//Total memory
		adlx_uint totalVRAM;
		const char* typeVRAM = nullptr;
		adlx_Res0 = ppGpuInfo->TotalVRAM(&totalVRAM);
		adlx_Res0 = ppGpuInfo->VRAMType(&typeVRAM);
		device_info += L"\nMemory: " + number_to_wstring(totalVRAM) + L"MB " + char_to_wstring(typeVRAM);

		//PCI bus information
		adlx_uint busLaneWidth = 0;
		ADLX_PCI_BUS_TYPE busType = UNDEFINED;
		adlx_Res0 = ppGpuInfo->PCIBusType(&busType);
		adlx_Res0 = ppGpuInfo->PCIBusLaneWidth(&busLaneWidth);
		std::vector<std::wstring> busTypeStrings = { L"Unknown", L"PCI", L"AGP", L"PCIE 1.0", L"PCIE 2.0", L"PCIE 3.0", L"PCIE 4.0", L"PCIE 5.0" };
		//Fix what if bustype > busTypeStrings size
		device_info += L"\nBus type: " + busTypeStrings[busType] + L" x" + number_to_wstring(busLaneWidth);

		//Load Resizable BAR status
		IADLXSmartAccessMemoryPtr ppSmartAccessMemory;
		adlx_Res0 = ppGPUTuningServices->GetSmartAccessMemory(ppGpuInfo, &ppSmartAccessMemory);
		adlx_Res0 = ppSmartAccessMemory->IsEnabled(&adlx_Bool);
		if (adlx_Bool)
		{
			device_info += L"\nResizable BAR / SAM: Enabled";
		}
		else
		{
			device_info += L"\nResizable BAR / SAM: Disabled";
		}

		//Set application version
		device_info += L"\n\nMade by Arnold Vink\n" + string_to_wstring(GetVersionFromResource(AppVariables::hInstance));

		//Set device information
		textblock_DeviceInfo().Text(device_info);

		//Set result
		AVDebugWriteLine("ADLX loaded info.");
	}
}