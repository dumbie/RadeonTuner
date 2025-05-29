#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AppVariables.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::AdlxUpdateLoop()
	{
		while (true)
		{
			Sleep(1000);

			//Get GPU metrics support
			IADLXGPUMetricsPtr gpuMetrics;
			res = perfMonitoringService->GetCurrentGPUMetrics(gpuInfo, &gpuMetrics);

			//Get GPU usage
			double gpuUsage = 0;
			res = gpuMetrics->GPUUsage(&gpuUsage);

			//Get GPU speed core
			int gpuSpeedCore = 0;
			res = gpuMetrics->GPUClockSpeed(&gpuSpeedCore);

			//Get GPU speed memory
			int gpuSpeedMemory = 0;
			res = gpuMetrics->GPUVRAMClockSpeed(&gpuSpeedMemory);

			//Get GPU power watt
			double gpuWatt = 0;
			res = gpuMetrics->GPUPower(&gpuWatt);

			//Get GPU power voltage
			int gpuVoltage = 0;
			res = gpuMetrics->GPUVoltage(&gpuVoltage);

			//Get GPU fan speed
			int gpuFanSpeed = 0;
			res = gpuMetrics->GPUFanSpeed(&gpuFanSpeed);

			//Get GPU temperature core
			double gpuTemperatureCore = 0;
			res = gpuMetrics->GPUTemperature(&gpuTemperatureCore);

			//Get GPU temperature hotspot
			double gpuTemperatureHotspot = 0;
			res = gpuMetrics->GPUHotspotTemperature(&gpuTemperatureHotspot);

			//Get GPU temperature intake
			double gpuTemperatureIntake = 0;
			res = gpuMetrics->GPUIntakeTemperature(&gpuTemperatureIntake);
			//Fix hide intake temperature if not supported

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
					textblock_Current_Temp_Hotspot().Text(number_to_wstring((int)gpuTemperatureHotspot) + L"°C Hotspot");
					textblock_Current_Temp_Intake().Text(number_to_wstring((int)gpuTemperatureIntake) + L"°C Intake");
				};
			AppVariables::App.DispatcherInvoke(updateFunction);
		}
	}
}