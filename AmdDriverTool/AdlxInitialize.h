#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::AdlxInitialize()
	{
		//Initialize ADLX
		res = g_ADLXHelp.Initialize();
		if (ADLX_FAILED(res))
		{
			AVDebugWriteLine("Failed initializing ADLX.");
			return;
		}

		//Get display services
		res = g_ADLXHelp.GetSystemServices()->GetDisplaysServices(&displayService);
		if (ADLX_FAILED(res))
		{
			AVDebugWriteLine("Failed getting display services.");
			return;
		}

		//Get 3DSettings services
		res = g_ADLXHelp.GetSystemServices()->Get3DSettingsServices(&d3dSettingSrv);
		if (ADLX_FAILED(res))
		{
			AVDebugWriteLine("Failed getting 3DSettings services.");
			return;
		}

		//Get Performance Monitoring services
		res = g_ADLXHelp.GetSystemServices()->GetPerformanceMonitoringServices(&perfMonitoringService);
		if (ADLX_FAILED(res))
		{
			AVDebugWriteLine("Failed getting Performance Monitoring services.");
			return;
		}

		//Get tuning services
		res = g_ADLXHelp.GetSystemServices()->GetGPUTuningServices((IADLXGPUTuningServices**)&gpuTuningService);
		if (ADLX_FAILED(res))
		{
			AVDebugWriteLine("Failed getting tuning services.");
			return;
		}

		//Get all gpus
		res = g_ADLXHelp.GetSystemServices()->GetGPUs(&gpuList);
		if (ADLX_FAILED(res))
		{
			AVDebugWriteLine("Failed getting all gpus.");
			return;
		}

		//Get all displays
		res = displayService->GetDisplays(&displayList);
		if (ADLX_FAILED(res))
		{
			AVDebugWriteLine("Failed getting all displays.");
			return;
		}

		//List all gpus 
		for (UINT i = 0; i < gpuList->Size(); i++)
		{
			const char* gpuName;
			gpuList->At(i, (IADLXGPU**)&gpuInfo);
			gpuInfo->Name(&gpuName);
			combobox_GpuSelect().Items().Append(box_value(char_to_wstring(gpuName)));
		}

		//List all displays 
		for (UINT i = 0; i < displayList->Size(); i++)
		{
			const char* displayName;
			displayList->At(i, &displayInfo);
			displayInfo->Name(&displayName);
			combobox_DisplaySelect().Items().Append(box_value(char_to_wstring(displayName)));
		}

		AVDebugWriteLine("ADLX initialized.");
	}
}