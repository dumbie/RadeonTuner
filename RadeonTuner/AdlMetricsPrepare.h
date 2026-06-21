#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlMetricsPrepare()
	{
		try
		{
			//Check metrics handle
			if (adl_Metrics_Handle != NULL)
			{
				//Stop metrics reading
				adl_Res0 = _ADL2_Adapter_PMLog_Stop(adl_Context, adl_Gpu_AdapterIndex, adl_Metrics_Handle);
				AVDebugWriteLine("ADL metrics reading stopped: " << adl_Res0);

				//Destroy metrics device
				adl_Res0 = _ADL2_Device_PMLog_Device_Destroy(adl_Context, adl_Metrics_Handle);
				AVDebugWriteLine("ADL metrics device destroyed: " << adl_Res0);
			}

			//Create metrics device
			adl_Res0 = _ADL2_Device_PMLog_Device_Create(adl_Context, adl_Gpu_AdapterIndex, &adl_Metrics_Handle);
			if (adl_Res0 != ADL_OK)
			{
				AVDebugWriteLine("Failed creating ADL metrics device: " << adl_Res0);
				return false;
			}

			//Start metrics reading
			ADLPMLogStartInput adlMetricsInput{};
			adlMetricsInput.usSensors[0] = ADL_SENSOR_MAXTYPES;
			adlMetricsInput.ulSampleRate = adl_Metrics_UpdateRate;
			adl_Res0 = _ADL2_Adapter_PMLog_Start(adl_Context, adl_Gpu_AdapterIndex, &adlMetricsInput, &adl_Metrics_Output, adl_Metrics_Handle);
			if (adl_Res0 != ADL_OK)
			{
				AVDebugWriteLine("Failed starting ADL metrics reading: " << adl_Res0);
				return false;
			}

			//Set result
			AVDebugWriteLine("ADL metrics reading started: " << adl_Res0);
			return true;
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed starting ADL metrics read (Exception)");
			return false;
		}
	}
}