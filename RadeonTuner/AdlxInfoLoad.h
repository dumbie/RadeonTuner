#pragma once
#include "pch.h"
#include "resource.h"
#include "MainPage.h"
#include "AdlxVariables.h"
#include "AppVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxInfoLoad()
	{
		try
		{
			//Device information string
			std::wstring device_info = L"";

			//Device name
			try
			{
				const char* productName = NULL;
				adlx_Res0 = ppGpuInfo->Name(&productName);
				device_info += L"Device name: " + char_to_wstring(productName);
			}
			catch (...) {}

			//Device codename
			try
			{
				const char* codeName = NULL;
				adlx_Res0 = ppGpuInfo->ProductName(&codeName);
				device_info += L"\nDevice codename: " + char_to_wstring(codeName);
			}
			catch (...) {}

			//Device identifier
			std::wstring device_id = AdlxGetDeviceIdentifier();
			if (!device_id.empty())
			{
				device_info += L"\nDevice identifier: " + device_id;
			}

			//Load driver version
			try
			{
				const char* driverVersion = NULL;
				const char* driverWindows = NULL;
				adlx_uint driverYear, driverMonth, driverDay;
				adlx_Res0 = ppGpuInfo->AMDSoftwareVersion(&driverVersion);
				adlx_Res0 = ppGpuInfo->AMDWindowsDriverVersion(&driverWindows);
				adlx_Res0 = ppGpuInfo->AMDSoftwareReleaseDate(&driverYear, &driverMonth, &driverDay);
				std::wstring driverDate = number_to_wstring(driverYear) + L"/" + number_to_wstring(driverMonth) + L"/" + number_to_wstring(driverDay);
				device_info += L"\nDriver version: " + char_to_wstring(driverVersion) + L" / " + char_to_wstring(driverWindows) + L" / " + driverDate;
			}
			catch (...) {}

			//Bios information
			try
			{
				const char* biosPart = NULL;
				const char* biosVersion = NULL;
				const char* biosDate = NULL;
				ppGpuInfo->BIOSInfo(&biosPart, &biosVersion, &biosDate);
				device_info += L"\nBios version: " + char_to_wstring(biosPart) + L" / " + char_to_wstring(biosVersion) + L" / " + char_to_wstring(biosDate);
			}
			catch (...) {}

			//Memory information
			try
			{
				adlx_uint totalVRAM;
				const char* typeVRAM = NULL;
				adlx_Res0 = ppGpuInfo->TotalVRAM(&totalVRAM);
				adlx_Res0 = ppGpuInfo->VRAMType(&typeVRAM);
				device_info += L"\nMemory: " + number_to_wstring(totalVRAM) + L"MB " + char_to_wstring(typeVRAM);
			}
			catch (...) {}

			//PCI bus information
			try
			{
				adlx_uint busLaneWidth = 0;
				ADLX_PCI_BUS_TYPE busType = UNDEFINED;
				adlx_Res0 = ppGpuInfo->PCIBusType(&busType);
				adlx_Res0 = ppGpuInfo->PCIBusLaneWidth(&busLaneWidth);
				std::vector<std::wstring> busTypeStrings = { L"Unknown", L"PCI", L"AGP", L"PCIE 1.0", L"PCIE 2.0", L"PCIE 3.0", L"PCIE 4.0", L"PCIE 5.0", L"PCIE 6.0" };
				//Fix what if bustype > busTypeStrings size
				device_info += L"\nBus type: " + busTypeStrings[busType] + L" x" + number_to_wstring(busLaneWidth);
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
						device_info += L"\nResizable BAR / SAM: Enabled";
					}
					else
					{
						device_info += L"\nResizable BAR / SAM: Disabled";
					}
				}
			}
			catch (...) {}

			//Set application version
			device_info += L"\n\nMade by Arnold Vink\nV" + string_to_wstring(GetVersionFromResource(AppVariables::hInstance));

			//Set device information
			textblock_DeviceInfo().Text(device_info);

			//Set result
			AVDebugWriteLine("ADLX loaded information.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading information.");
		}
	}

	std::wstring MainPage::AdlxGetDeviceIdentifier()
	{
		std::wstring device_id = L"";
		try
		{
			const char* vendorId = NULL;
			adlx_Res0 = ppGpuInfo->VendorId(&vendorId);
			if (vendorId != NULL)
			{
				device_id += char_to_wstring(vendorId);
				device_id += L" ";
			}

			const char* deviceId = NULL;
			adlx_Res0 = ppGpuInfo->DeviceId(&deviceId);
			if (deviceId != NULL)
			{
				device_id += char_to_wstring(deviceId);
				device_id += L" - ";
			}

			const char* subSystemVendorId = NULL;
			adlx_Res0 = ppGpuInfo->SubSystemVendorId(&subSystemVendorId);
			if (subSystemVendorId != NULL)
			{
				device_id += char_to_wstring(subSystemVendorId);
				device_id += L" ";
			}

			const char* subSystemId = NULL;
			adlx_Res0 = ppGpuInfo->SubSystemId(&subSystemId);
			if (subSystemId != NULL)
			{
				device_id += char_to_wstring(subSystemId);
				device_id += L" - ";
			}

			const char* revisionId = NULL;
			adlx_Res0 = ppGpuInfo->RevisionId(&revisionId);
			if (revisionId != NULL)
			{
				device_id += char_to_wstring(revisionId);
				device_id += L" - ";
			}

			int uniqueId = -1;
			adlx_Res0 = ppGpuInfo->UniqueId(&uniqueId);
			if (uniqueId > 0)
			{
				device_id += number_to_wstring(uniqueId);
			}
		}
		catch (...) {}
		return device_id;
	}

	void MainPage::button_Website_Project_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			ShellExecuteW(0, 0, L"https://projects.arnoldvink.com", 0, 0, 0);
		}
		catch (...) {}
	}

	void MainPage::button_Website_Donation_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			ShellExecuteW(0, 0, L"https://donation.arnoldvink.com", 0, 0, 0);
		}
		catch (...) {}
	}

	void MainPage::button_Fps_Overlayer_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			ShellExecuteW(0, 0, L"https://github.com/dumbie/FpsOverlayer", 0, 0, 0);
		}
		catch (...) {}
	}

	void MainPage::button_Check_Update_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Download releases from Github
			std::string releasesJson = DownloadString("https://api.github.com", "repos/dumbie/RadeonTuner/releases/latest", "RadeonTuner", "");

			//Parse json data
			nlohmann::json parsedJson = nlohmann::json::parse(releasesJson);

			//Get available version
			std::string availableVersion = parsedJson["name"];

			//Get current version
			std::string currentVersion = "v" + GetVersionFromResource(AppVariables::hInstance);

			//Check if version matches
			if (currentVersion != availableVersion)
			{
				int messageResult = MessageBoxW(NULL, L"Newer version has been found, would you like to update the application to the newest version available?", L"RadeonTuner", MB_YESNO);
				if (messageResult == IDYES)
				{
					ShellExecuteW(0, 0, L"https://github.com/dumbie/RadeonTuner/releases", 0, 0, 0);
				}
			}
			else
			{
				MessageBoxW(NULL, L"No new application update has been found.", L"RadeonTuner", MB_OK);
			}
		}
		catch (...)
		{
			MessageBoxW(NULL, L"Failed checking for application update.", L"RadeonTuner", MB_OK);
		}
	}
}