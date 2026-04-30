#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::Adl_Eyefinity_Create_Simple()
	{
		try
		{
			//Get simple Eyefinity
			IADLXSimpleEyefinityPtr eyefinitySimple;
			adlx_Res0 = ppDesktopServices->GetSimpleEyefinity(&eyefinitySimple);
			if (ADLX_FAILED(adlx_Res0))
			{
				AVDebugWriteLine("Failed to get simple Eyefinity: " << adlx_Res0);
				return false;
			}

			//Create simple Eyefinity
			IADLXEyefinityDesktopPtr eyefinityDesktop;
			adlx_Res0 = eyefinitySimple->Create(&eyefinityDesktop);

			//Return result
			AVDebugWriteLine("Created simple Eyefinity: " << adlx_Res0);
			return adlx_Res0 == ADLX_OK;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to create simple Eyefinity (Exception)");
			return false;
		}
	}

	bool MainPage::Adl_Eyefinity_Toggle(int displayAdapterIndex, bool setEnabled)
	{
		try
		{
			int iNumDisplayMap;
			ADLDisplayMap* lpDisplayMap = NULL;

			int iNumDisplayTarget;
			ADLDisplayTarget* lpDisplayTarget = NULL;

			//Get display map configuration
			adl_Res0 = _ADL2_Display_DisplayMapConfig_Get(adl_Context, displayAdapterIndex, &iNumDisplayMap, &lpDisplayMap, &iNumDisplayTarget, &lpDisplayTarget, ADL_DISPLAY_DISPLAYMAP_OPTION_GPUINFO);
			if (adl_Res0 != ADL_OK)
			{
				//Return result
				AVDebugWriteLine("Failed to get display map configuration: " << adl_Res0);
				return false;
			}

			//Get single large surface map index
			int iSlsMapIndex;
			adl_Res0 = _ADL2_Display_SLSMapIndex_Get(adl_Context, displayAdapterIndex, iNumDisplayTarget, lpDisplayTarget, &iSlsMapIndex);
			if (adl_Res0 != ADL_OK)
			{
				//Return result
				AVDebugWriteLine("Failed to get single large surface map index: " << adl_Res0);
				return false;
			}

			//Set single large surface map state
			adl_Res0 = _ADL2_Display_SLSMapConfig_SetState(adl_Context, displayAdapterIndex, iSlsMapIndex, setEnabled);

			//Return result
			AVDebugWriteLine("Set Eyefinity state: " << adl_Res0);
			return adl_Res0 == ADL_OK;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to set Eyefinity state (Exception)");
			return false;
		}
	}
}