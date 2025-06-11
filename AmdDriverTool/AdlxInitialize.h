#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	bool MainPage::AdlxInitialize()
	{
		//Initialize ADLX
		adlx_Res0 = ppADLXHelper.Initialize();
		if (ADLX_FAILED(adlx_Res0))
		{
			AVDebugWriteLine("Failed initializing ADLX.");
			return false;
		}

		//Get display services
		adlx_Res0 = ppADLXHelper.GetSystemServices()->GetDisplaysServices(&ppDispServices);
		if (ADLX_FAILED(adlx_Res0))
		{
			AVDebugWriteLine("Failed getting display services.");
			return false;
		}

		//Get 3DSettings services
		adlx_Res0 = ppADLXHelper.GetSystemServices()->Get3DSettingsServices(&pp3DSettingsServices);
		if (ADLX_FAILED(adlx_Res0))
		{
			AVDebugWriteLine("Failed getting 3DSettings services.");
			return false;
		}

		//Get Performance Monitoring services
		adlx_Res0 = ppADLXHelper.GetSystemServices()->GetPerformanceMonitoringServices(&ppPerformanceMonitoringServices);
		if (ADLX_FAILED(adlx_Res0))
		{
			AVDebugWriteLine("Failed getting Performance Monitoring services.");
			return false;
		}

		//Get tuning services
		adlx_Res0 = ppADLXHelper.GetSystemServices()->GetGPUTuningServices((IADLXGPUTuningServices**)&ppGPUTuningServices);
		if (ADLX_FAILED(adlx_Res0))
		{
			AVDebugWriteLine("Failed getting tuning services.");
			return false;
		}

		//Get all gpus
		adlx_Res0 = ppADLXHelper.GetSystemServices()->GetGPUs(&ppGpuList);
		if (ADLX_FAILED(adlx_Res0))
		{
			AVDebugWriteLine("Failed getting all gpus.");
			return false;
		}

		//Get all displays
		adlx_Res0 = ppDispServices->GetDisplays(&ppDisplayList);
		if (ADLX_FAILED(adlx_Res0))
		{
			AVDebugWriteLine("Failed getting all displays.");
			return false;
		}

		AVDebugWriteLine("ADLX initialized.");
		return true;
	}
}