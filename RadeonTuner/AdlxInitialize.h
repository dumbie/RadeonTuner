#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	//Memory release
	void __stdcall ADL_Main_Memory_Free_Client(void** lpBuffer)
	{
		if (nullptr != lpBuffer && nullptr != *lpBuffer)
		{
			free(*lpBuffer);
			*lpBuffer = nullptr;
		}
	}

	std::wstring MainPage::AdlxInitialize()
	{
		try
		{
			//Initialize ADLX
			adlx_Res0 = ppADLXHelper.InitializeWithCallerAdl(_ADL2_Context, ADL_Main_Memory_Free_Client);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				AVDebugWriteLine("Failed initializing ADLX (" << adlx_Res0 << ")");
				return std::wstring(L"Failed initializing ADLX (") + number_to_wstring(adlx_Res0) + std::wstring(L")");
			}

			//Get ADL mapping
			ppAdlMapping = ppADLXHelper.GetAdlMapping();

			//Get system services
			IADLXSystem* pSystemServices0 = ppADLXHelper.GetSystemServices();
			IADLXSystem2* pSystemServices2 = IADLXSystem2Ptr(pSystemServices0);

			if (pSystemServices0 != NULL)
			{
				//Get display services
				adlx_Res0 = pSystemServices0->GetDisplaysServices((IADLXDisplayServices**)&ppDispServices);
				if (ADLX_FAILED(adlx_Res0))
				{
					//Set result
					AVDebugWriteLine("Failed getting display services.");
				}

				//Get 3DSettings services
				adlx_Res0 = pSystemServices0->Get3DSettingsServices((IADLX3DSettingsServices**)&pp3DSettingsServices);
				if (ADLX_FAILED(adlx_Res0))
				{
					//Set result
					AVDebugWriteLine("Failed getting 3DSettings services.");
				}

				//Get Performance Monitoring services
				adlx_Res0 = pSystemServices0->GetPerformanceMonitoringServices(&ppPerformanceMonitoringServices);
				if (ADLX_FAILED(adlx_Res0))
				{
					//Set result
					AVDebugWriteLine("Failed getting Performance Monitoring services.");
				}

				//Get gpu tuning services
				adlx_Res0 = pSystemServices0->GetGPUTuningServices((IADLXGPUTuningServices**)&ppGPUTuningServices);
				if (ADLX_FAILED(adlx_Res0))
				{
					//Set result
					AVDebugWriteLine("Failed getting gpu tuning services.");
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
			}

			if (pSystemServices2 != NULL)
			{
				//Get multimedia services
				adlx_Res0 = pSystemServices2->GetMultimediaServices(&ppMultiMediaServices);
				if (ADLX_FAILED(adlx_Res0))
				{
					//Set result
					AVDebugWriteLine("Failed getting multimedia services.");
				}

				//Get power tuning services
				adlx_Res0 = pSystemServices2->GetPowerTuningServices((IADLXPowerTuningServices**)&ppPowerTuningServices);
				if (ADLX_FAILED(adlx_Res0))
				{
					//Set result
					AVDebugWriteLine("Failed getting power tuning services.");
				}
			}

			if (ppDispServices != NULL)
			{
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