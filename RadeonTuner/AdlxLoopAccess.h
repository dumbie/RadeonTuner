#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AppVariables.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	//Check selected device accessibility
	void MainPage::AdlxCheckSelectedDeviceAccess()
	{
		try
		{
			//Note: As alternative method you can use AdlGetGpuAll and AdlGetDisplayByAdapterIndex, check if identifier exists in list.
			//Note: Using Display_Modes_Get does not work when Eyefinity is enabled, can try using Display_SCE_State_Get as fallback.

			//Check GPU accessibility
			int lpAccess;
			adl_Res0 = _ADL2_Adapter_Accessibility_Get(adl_Context, adl_Gpu_AdapterIndex, &lpAccess);
			if (adl_Res0 != ADL_OK || lpAccess == 0)
			{
				AVDebugWriteLine("Selected GPU not available: " << adl_Gpu_AdapterIndex);
				std::function<void()> invokeVoid = [&]
					{
						AdlxValuesResetSelectGpu();
					};
				AppVariables::App.DispatcherInvoke(invokeVoid);
			}

			//Check display accessibility
			int numModes = -1;
			ADLMode* adlModeCurrent{};
			adl_Res0 = _ADL2_Display_Modes_Get(adl_Context, adl_Display_AdapterIndex, adl_Display_DisplayIndex, &numModes, &adlModeCurrent);
			if (adl_Res0 != ADL_OK || adlModeCurrent->iModeValue <= 0)
			{
				AVDebugWriteLine("Selected display not available: " << adl_Display_AdapterIndex << " / " << adl_Display_DisplayIndex);
				std::function<void()> invokeVoid = [&]
					{
						AdlxValuesResetSelectDisplay();
					};
				AppVariables::App.DispatcherInvoke(invokeVoid);
			}
		}
		catch (...) {}
	}
}