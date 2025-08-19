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

		//Get system services
		IADLXSystem* pSystemServices0 = ppADLXHelper.GetSystemServices();
		IADLXSystem1* pSystemServices1 = IADLXSystem1Ptr(ppADLXHelper.GetSystemServices()).GetPtr();
		IADLXSystem2* pSystemServices2 = IADLXSystem2Ptr(ppADLXHelper.GetSystemServices()).GetPtr();

		//Get multimedia services
		adlx_Res0 = pSystemServices2->GetMultimediaServices(&ppMultiMediaServices);
		if (ADLX_FAILED(adlx_Res0))
		{
			AVDebugWriteLine("Failed getting multimedia services.");
			return false;
		}

		//Get display services
		adlx_Res0 = pSystemServices0->GetDisplaysServices((IADLXDisplayServices**)&ppDispServices);
		if (ADLX_FAILED(adlx_Res0))
		{
			AVDebugWriteLine("Failed getting display services.");
			return false;
		}

		//Get 3DSettings services
		IADLX3DSettingsServicesPtr pp3DSettingsServices0;
		adlx_Res0 = pSystemServices0->Get3DSettingsServices(&pp3DSettingsServices0);
		if (ADLX_FAILED(adlx_Res0))
		{
			AVDebugWriteLine("Failed getting 3DSettings services.");
			return false;
		}
		pp3DSettingsServices = IADLX3DSettingsServices2Ptr(pp3DSettingsServices0);

		//Get Performance Monitoring services
		adlx_Res0 = pSystemServices0->GetPerformanceMonitoringServices(&ppPerformanceMonitoringServices);
		if (ADLX_FAILED(adlx_Res0))
		{
			AVDebugWriteLine("Failed getting Performance Monitoring services.");
			return false;
		}

		//Get tuning services
		adlx_Res0 = pSystemServices0->GetGPUTuningServices((IADLXGPUTuningServices**)&ppGPUTuningServices);
		if (ADLX_FAILED(adlx_Res0))
		{
			AVDebugWriteLine("Failed getting tuning services.");
			return false;
		}

		//Get all gpus
		adlx_Res0 = pSystemServices0->GetGPUs(&ppGpuList);
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