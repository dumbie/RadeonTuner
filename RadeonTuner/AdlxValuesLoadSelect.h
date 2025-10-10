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
#include "RegValuesLoad.h"

namespace winrt::RadeonTuner::implementation
{
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
			AVDebugWriteLine("ADLX loaded power values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading power values.");
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

			//Load registry settings
			RegValuesLoad();

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