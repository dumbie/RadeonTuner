#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlValuesLoadGraphics.h"
#include "MainVariables.h"
#include "AdlxValuesLoadMultimedia.h"
#include "AdlxValuesLoadPower.h"
#include "AdlxValuesLoadDisplay.h"
#include "AdlxValuesLoadTuning.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesLoadSelectApp()
	{
		try
		{
			//Check if picking is disabled
			if (disable_picking) { return; }

			//Disable saving
			disable_saving = true;

			//Get selected index
			adl_AppSelectedIndex = combobox_AppSelect().SelectedIndex();

			std::wstring applicationFileName = adl_AppSelected().FileName;
			std::wstring applicationFilePath = adl_AppSelected().FilePath;
			if (applicationFileName == L"*.*")
			{
				applicationFileName = L"Global";
				button_Graphics_Unlock().IsEnabled(false);
			}
			else
			{
				button_Graphics_Unlock().IsEnabled(true);
			}
			textblock_GraphicsOptions_Name().Text(applicationFileName);
			textblock_GraphicsOptions_Details().Text(applicationFilePath);
			AVDebugWriteLine("Selected app: " << applicationFileName);

			//Load application graphics settings
			AdlValuesLoadGraphicsApp();

			//Enable saving
			std::thread threadEnableSaving([]()
				{
					Sleep(1000);
					disable_saving = false;
				});
			threadEnableSaving.detach();

			//Set result
			AVDebugWriteLine("Loaded selected app values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed loading selected app values.");
		}
	}

	void MainPage::AdlxValuesLoadSelectPower()
	{
		try
		{
			//Disable saving
			disable_saving = true;

			//Load power settings
			AdlxValuesLoadPower();

			//Enable saving
			std::thread threadEnableSaving([]()
				{
					Sleep(1000);
					disable_saving = false;
				});
			threadEnableSaving.detach();

			//Set result
			AVDebugWriteLine("Loaded selected power values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed loading selected power values.");
		}
	}

	void MainPage::AdlxValuesLoadSelectDisplay()
	{
		try
		{
			//Disable saving
			disable_saving = true;

			//Get selected display
			int selectedDisplayIndex = combobox_DisplaySelect().SelectedIndex();
			ppDisplayList->At(selectedDisplayIndex, &ppDisplayInfo);
			if (ppDisplayInfo == NULL)
			{
				AVDebugWriteLine("Failed getting selected display.");
				return;
			}

			//Load display settings
			AdlxValuesLoadDisplay();

			//Load information
			AdlxInfoLoad();

			//Enable saving
			std::thread threadEnableSaving([]()
				{
					Sleep(1000);
					disable_saving = false;
				});
			threadEnableSaving.detach();

			//Set result
			AVDebugWriteLine("Loaded selected display values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed loading selected display values.");
		}
	}

	void MainPage::AdlxValuesLoadSelectGpu()
	{
		try
		{
			//Disable saving
			disable_saving = true;

			//Get selected GPU
			int selectedGpuIndex = combobox_GpuSelect().SelectedIndex();
			ppGpuList->At(selectedGpuIndex, (IADLXGPU**)&ppGpuInfo);
			if (ppGpuInfo == NULL)
			{
				AVDebugWriteLine("Failed getting selected gpu.");
				return;
			}

			//Get ADL adapter index
			ppAdlMapping->AdlAdapterIndexFromADLXGPU(ppGpuInfo, &adl_AdapterIndex);

			//Get gpu registry path
			const char* driverPath = NULL;
			adlx_Res0 = ppGpuInfo->DriverPath(&driverPath);
			gpuRegistryPath = string_to_wstring(driverPath);

			//Get gpu unique identifier
			adlx_Res0 = ppGpuInfo->UniqueId(&gpuUniqueIdentifier);
			gpuUniqueIdentifierHex = number_to_hexwstring(gpuUniqueIdentifier, 4);

			//Load keep active setting
			KeepActive_Load_UI();

			//Load tuning and fans settings
			AdlxValuesLoadTuning();

			//Load application graphics settings
			AdlValuesLoadGraphicsApp();

			//Load multimedia settings
			AdlxValuesLoadMultimedia();

			//Load information
			AdlxInfoLoad();

			//Enable saving
			std::thread threadEnableSaving([]()
				{
					Sleep(1000);
					disable_saving = false;
				});
			threadEnableSaving.detach();

			//Set result
			AVDebugWriteLine("Loaded selected gpu values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed loading selected gpu values.");
		}
	}
}