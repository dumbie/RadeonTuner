#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AppVariables.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxLoopMetrics()
	{
		while (true)
		{
			try
			{
				//Fix skip when window is not visible

				//Delay next update
				Sleep(1000);

				//Check services
				if (ppPerformanceMonitoringServices == NULL)
				{
					std::function<void()> updateFunction = [&]
						{
							border_Status().Visibility(Visibility::Collapsed);
						};
					AppVariables::App.DispatcherInvoke(updateFunction);
					AVDebugWriteLine("ADLX performance monitoring service is not available.");
					return;
				}

				//Get GPU metrics support
				IADLXGPUMetricsPtr ppGpuMetrics;
				adlx_Res0 = ppPerformanceMonitoringServices->GetCurrentGPUMetrics(ppGpuInfo, &ppGpuMetrics);

				//Get GPU usage
				double gpuUsage = 0;
				adlx_Res0 = ppGpuMetrics->GPUUsage(&gpuUsage);

				//Get GPU speed core
				int gpuSpeedCore = 0;
				adlx_Res0 = ppGpuMetrics->GPUClockSpeed(&gpuSpeedCore);

				//Get GPU speed memory
				int gpuSpeedMemory = 0;
				adlx_Res0 = ppGpuMetrics->GPUVRAMClockSpeed(&gpuSpeedMemory);

				//Get GPU power watt
				double gpuWatt = 0;
				adlx_Res0 = ppGpuMetrics->GPUPower(&gpuWatt);

				//Get GPU power voltage
				int gpuVoltage = 0;
				adlx_Res0 = ppGpuMetrics->GPUVoltage(&gpuVoltage);

				//Get GPU fan speed
				int gpuFanSpeed = 0;
				adlx_Res0 = ppGpuMetrics->GPUFanSpeed(&gpuFanSpeed);

				//Get GPU temperature core
				double gpuTemperatureCore = 0;
				adlx_Res0 = ppGpuMetrics->GPUTemperature(&gpuTemperatureCore);

				//Get GPU temperature hotspot
				double gpuTemperatureHotspot = 0;
				adlx_Res0 = ppGpuMetrics->GPUHotspotTemperature(&gpuTemperatureHotspot);
				bool gpuTemperatureHotspotSupported = ADLX_SUCCEEDED(adlx_Res0);

				//Get GPU temperature intake
				double gpuTemperatureIntake = 0;
				adlx_Res0 = ppGpuMetrics->GPUIntakeTemperature(&gpuTemperatureIntake);
				bool gpuTemperatureIntakeSupported = ADLX_SUCCEEDED(adlx_Res0);

				//Update current statistics
				std::function<void()> updateFunction = [&]
					{
						textblock_Current_Gpu_Usage().Text(number_to_wstring((int)gpuUsage) + L"%");
						textblock_Current_Core_Speed().Text(number_to_wstring(gpuSpeedCore) + L"MHz");
						textblock_Current_Memory_Speed().Text(number_to_wstring(gpuSpeedMemory) + L"MTs");

						textblock_Current_Power_Watt().Text(number_to_wstring((int)gpuWatt) + L"W");
						textblock_Current_Power_Voltage().Text(number_to_wstring(gpuVoltage) + L"mV");

						textblock_Current_Fan_Speed().Text(number_to_wstring(gpuFanSpeed) + L"RPM");
						textblock_Current_Temp_Core().Text(number_to_wstring((int)gpuTemperatureCore) + L"°C Core");

						if (gpuTemperatureHotspotSupported)
						{
							textblock_Current_Temp_Hotspot().Text(number_to_wstring((int)gpuTemperatureHotspot) + L"°C Hotspot");
						}
						else
						{
							textblock_Current_Temp_Hotspot().Text(L"");
						}

						if (gpuTemperatureIntakeSupported)
						{
							textblock_Current_Temp_Intake().Text(number_to_wstring((int)gpuTemperatureIntake) + L"°C Intake");
						}
						else
						{
							textblock_Current_Temp_Intake().Text(L"");
						}
					};
				AppVariables::App.DispatcherInvoke(updateFunction);
			}
			catch (...) {}
		}
	}
}