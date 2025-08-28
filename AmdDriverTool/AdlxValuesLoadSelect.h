#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"
#include "AdlxValuesLoadFans.h"
#include "AdlxValuesLoadGraphics.h"
#include "AdlxValuesLoadMultimedia.h"
#include "AdlxValuesLoadDisplay.h"
#include "AdlxValuesLoadTuning.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::AdlxValuesLoadSelect()
	{
		try
		{
			//Fix ADLX missing Surface Format Optimization
			//Fix ADLX missing OpenGL Triple Buffering
			//Fix ADLX missing 10-Bit Pixel Format
			//Fix ADLX missing Display Color Enhancement
			//Fix ADLX missing Color Deficiency Correction
			//Fix ADLX missing AMD Privacy View
			//Fix ADLX missing AMD Noise Suppression
			//Fix ADLX missing Color Temperature Control
			//Fix GetCustomResolution support (Custom Resolution Utility)
			//Fix IADLXEyefinityDesktop support
			//Fix Get3DLUT support
			//Fix GetGamut support
			//Fix GetGamma support
			//Fix IADLXDisplayConnectivityExperiencePtr GetRelativeVoltageSwing support
			//Fix IADLXDisplayConnectivityExperiencePtr GetRelativePreEmphasis support
			//Fix IADLXDisplayFreeSyncColorAccuracy support

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

			//Get selected display
			int selectedDisplayIndex = combobox_DisplaySelect().SelectedIndex();
			ppDisplayList->At(selectedDisplayIndex, &ppDisplayInfo);
			if (ppDisplayInfo == NULL)
			{
				AVDebugWriteLine("Failed getting selected display.");
				return;
			}

			//Load fans settings
			AdlxValuesLoadFans();

			//Load graphics settings
			AdlxValuesLoadGraphics();

			//Load multimedia settings
			AdlxValuesLoadMultimedia();

			//Load display settings
			AdlxValuesLoadDisplay();

			//Load tuning settings
			AdlxValuesLoadTuning();

			//Enable saving
			std::thread threadEnableSaving([]()
				{
					Sleep(1000);
					disable_saving = false;
				});
			threadEnableSaving.detach();

			//Set result
			AVDebugWriteLine("ADLX loaded values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading values.");
		}
	}
}