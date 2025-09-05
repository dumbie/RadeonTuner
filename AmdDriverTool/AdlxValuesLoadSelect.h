#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"
#include "AdlxValuesLoadFans.h"
#include "AdlxValuesLoadGraphics.h"
#include "AdlxValuesLoadMultimedia.h"
#include "AdlxValuesLoadPower.h"
#include "AdlxValuesLoadDisplay.h"
#include "AdlxValuesLoadTuning.h"

namespace winrt::AmdDriverTool::implementation
{
	//Fix ADLX missing Surface Format Optimization
	//Fix ADLX missing OpenGL Triple Buffering
	//Fix ADLX missing 10-Bit Pixel Format
	//Fix ADLX missing Display Color Enhancement
	//Fix ADLX missing Color Deficiency Correction
	//Fix ADLX missing AMD Privacy View
	//Fix ADLX missing AMD Noise Suppression
	//Fix ADLX missing Platform Compatibility (Group A, B, C)
	//Fix GetCustomResolution support (Custom Resolution Utility)
	//Fix IADLXEyefinityDesktop support
	//Fix Get3DLUT support
	//Fix GetGamut support
	//Fix GetGamma support

	void MainPage::AdlxValuesLoadSelectApp()
	{
		try
		{
			//Disable saving
			disable_saving = true;

			//Enable saving
			std::thread threadEnableSaving([]()
				{
					Sleep(1000);
					disable_saving = false;
				});
			threadEnableSaving.detach();

			//Set result
			AVDebugWriteLine("ADLX loaded app values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading app values.");
		}
	}

	void MainPage::AdlxValuesLoadSelectOther()
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
			AVDebugWriteLine("ADLX loaded other values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading other values.");
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

			//Enable saving
			std::thread threadEnableSaving([]()
				{
					Sleep(1000);
					disable_saving = false;
				});
			threadEnableSaving.detach();

			//Set result
			AVDebugWriteLine("ADLX loaded display values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading display values.");
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

			//Load tuning settings
			AdlxValuesLoadTuning();

			//Load fans settings
			AdlxValuesLoadFans();

			//Load graphics settings
			AdlxValuesLoadGraphics();

			//Load multimedia settings
			AdlxValuesLoadMultimedia();

			//Load gpu information
			AdlxInfoLoad();

			//Enable saving
			std::thread threadEnableSaving([]()
				{
					Sleep(1000);
					disable_saving = false;
				});
			threadEnableSaving.detach();

			//Set result
			AVDebugWriteLine("ADLX loaded gpu values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading gpu values.");
		}
	}
}