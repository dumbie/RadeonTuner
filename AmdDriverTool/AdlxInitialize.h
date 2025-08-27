#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	std::wstring MainPage::AdlxInitialize()
	{
		try
		{
			//Initialize ADLX
			adlx_Res0 = ppADLXHelper.Initialize();
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				AVDebugWriteLine("Failed initializing ADLX (" << adlx_Res0 << ")");
				return std::wstring(L"Failed initializing ADLX (") + number_to_wstring(adlx_Res0) + std::wstring(L")");
			}

			//Get system services
			IADLXSystem* pSystemServices0 = ppADLXHelper.GetSystemServices();
			IADLXSystem1* pSystemServices1 = IADLXSystem1Ptr(ppADLXHelper.GetSystemServices()).GetPtr();
			IADLXSystem2* pSystemServices2 = IADLXSystem2Ptr(ppADLXHelper.GetSystemServices()).GetPtr();

			//Get multimedia services
			adlx_Res0 = pSystemServices2->GetMultimediaServices(&ppMultiMediaServices);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				AVDebugWriteLine("Failed getting multimedia services.");
				return L"Failed getting multimedia services.";
			}

			//Get display services
			adlx_Res0 = pSystemServices0->GetDisplaysServices((IADLXDisplayServices**)&ppDispServices);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				AVDebugWriteLine("Failed getting display services.");
				return L"Failed getting display services.";
			}

			//Get 3DSettings services
			adlx_Res0 = pSystemServices0->Get3DSettingsServices((IADLX3DSettingsServices**)&pp3DSettingsServices);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				AVDebugWriteLine("Failed getting 3DSettings services.");
				return L"Failed getting 3DSettings services.";
			}

			//Get Performance Monitoring services
			adlx_Res0 = pSystemServices0->GetPerformanceMonitoringServices(&ppPerformanceMonitoringServices);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				AVDebugWriteLine("Failed getting Performance Monitoring services.");
				return L"Failed getting Performance Monitoring services.";
			}

			//Get tuning services
			adlx_Res0 = pSystemServices0->GetGPUTuningServices((IADLXGPUTuningServices**)&ppGPUTuningServices);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				AVDebugWriteLine("Failed getting tuning services.");
				return L"Failed getting tuning services.";
			}

			//Get all gpus
			adlx_Res0 = pSystemServices0->GetGPUs(&ppGpuList);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				AVDebugWriteLine("Failed getting GPUs list.");
				return L"Failed getting GPUs list.";
			}

			//Check any gpus
			if (ppGpuList->Size() == 0)
			{
				//Set result
				AVDebugWriteLine("Failed getting any GPUs.");
				return L"Failed getting any GPUs.";
			}

			//Get all displays
			adlx_Res0 = ppDispServices->GetDisplays(&ppDisplayList);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				AVDebugWriteLine("Failed getting displays list.");
				return L"Failed getting displays list.";
			}

			//Check any displays
			if (ppDisplayList->Size() == 0)
			{
				//Set result
				AVDebugWriteLine("Failed getting any displays.");
				return L"Failed getting any displays.";
			}

			//Set result
			AVDebugWriteLine("ADLX initialized.");
			return L"";
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed initializing (Exception)");
			return L"ADLX failed initializing (Exception)";
		}
	}
}