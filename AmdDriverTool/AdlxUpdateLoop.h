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

			//Fix show gpu usage

			//Get GPU metrics support
			IADLXGPUMetricsPtr gpuMetrics;
			res = perfMonitoringService->GetCurrentGPUMetrics(gpuInfo, &gpuMetrics);

			//Get GPU speed core
			int gpuSpeedCore = 0;
			res = gpuMetrics->GPUClockSpeed(&gpuSpeedCore);

			//Get GPU speed vram
			int gpuSpeedVram = 0;
			res = gpuMetrics->GPUVRAMClockSpeed(&gpuSpeedVram);

			//Get GPU watt
			double gpuWatt = 0;
			res = gpuMetrics->GPUPower(&gpuWatt);

			//Get GPU voltage
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
					textblock_GPU_Speed_Core().Text(number_to_wstring(gpuSpeedCore) + L"MHz");
					textblock_GPU_Speed_VRAM().Text(number_to_wstring(gpuSpeedVram) + L"MHz");

					textblock_GPU_Watt().Text(number_to_wstring((int)gpuWatt) + L"W");
					textblock_GPU_Voltage().Text(number_to_wstring(gpuVoltage) + L"mV");

					textblock_GPU_Fan_Speed().Text(number_to_wstring(gpuFanSpeed) + L"RPM");
					textblock_GPU_Temp_Core().Text(number_to_wstring((int)gpuTemperatureCore) + L"°C Core");
					textblock_GPU_Temp_Hotspot().Text(number_to_wstring((int)gpuTemperatureHotspot) + L"°C Hotspot");
					textblock_GPU_Temp_Intake().Text(number_to_wstring((int)gpuTemperatureIntake) + L"°C Intake");
				};
			AppVariables::App.DispatcherInvoke(updateFunction);
		}
	}
}