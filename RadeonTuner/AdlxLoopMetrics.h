#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AppVariables.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	//Fix skip when window is not visible
	//Fix check if AFMF, FSR Latency Reduction, FSR Upscaling or FSR Feature Override is active and update status
	//Applications that are currently hooked by driver can be found at Computer\HKEY_CURRENT_USER\Software\AMD\HKIDs
	//amdihk64.dll NotifyFidelityFXStatus NotifyFidelityFXGameVersion

	void MainPage::AdlxLoopMetrics()
	{
		while (true)
		{
			try
			{
				//Delay next loop
				Sleep(adl_Metrics_UpdateRate);

				//Check if loop is allowed
				if (AppVariables::ApplicationExiting)
				{
					return;
				}

				//Set metrics variables
				int gpuUsageCore = -1;
				int gpuUsageMemory = -1;
				int gpuSpeedCore = -1;
				int gpuSpeedMemory = -1;
				int gpuWatt = -1;
				int gpuVoltage = -1;
				int gpuFanSpeedRpm = -1;
				int gpuFanSpeedPercentage = -1;
				int gpuTemperatureCore = -1;
				int gpuTemperatureMemory = -1;
				int gpuTemperatureHotspot = -1;
				int gpuTemperatureIntake = -1;

				////Get metrics logging data using query
				//ADLPMLogDataOutput adl_Metrics_Logging_Output;
				//adl_Res0 = _ADL2_New_QueryPMLogData_Get(adl_Context, adl_Gpu_AdapterIndex, &adl_Metrics_Logging_Output);
				//AVDebugWriteLine(adl_Metrics_Logging_Output.sensors[ADL_PMLOG_INFO_ACTIVITY_GFX].value);

				//Get metrics logging data
				ADLPMLogData* adl_Metrics_Logging = (ADLPMLogData*)(adl_Metrics_Output.pLoggingAddress);
				if (adl_Metrics_Logging == NULL)
				{
					AVDebugWriteLine("ADL metrics logging data is empty.");
					continue;
				}

				//Loop through all metrics
				int index = 0;
				while (adl_Metrics_Logging->ulValues[index][0] != ADL_SENSOR_MAXTYPES)
				{
					int currentSensor = adl_Metrics_Logging->ulValues[index][0];
					int currentValue = adl_Metrics_Logging->ulValues[index][1];
					if (currentSensor == ADL_PMLOG_INFO_ACTIVITY_GFX)
					{
						gpuUsageCore = currentValue;
					}
					else if (currentSensor == ADL_PMLOG_CLK_GFXCLK)
					{
						gpuSpeedCore = currentValue;
					}
					else if (currentSensor == ADL_PMLOG_INFO_ACTIVITY_MEM)
					{
						gpuUsageMemory = currentValue;
					}
					else if (currentSensor == ADL_PMLOG_CLK_MEMCLK)
					{
						gpuSpeedMemory = currentValue;
					}
					else if (currentSensor == ADL_PMLOG_GFX_POWER)
					{
						//Integrated
						gpuWatt = currentValue;
					}
					else if (currentSensor == ADL_PMLOG_BOARD_POWER)
					{
						//Dedicated
						gpuWatt = currentValue;
					}
					else if (currentSensor == ADL_PMLOG_GFX_VOLTAGE)
					{
						gpuVoltage = currentValue;
					}
					else if (currentSensor == ADL_PMLOG_FAN_RPM)
					{
						//Dedicated
						gpuFanSpeedRpm = currentValue;
					}
					else if (currentSensor == ADL_PMLOG_FAN_PERCENTAGE)
					{
						//Dedicated
						gpuFanSpeedPercentage = currentValue;
					}
					else if (currentSensor == ADL_PMLOG_TEMPERATURE_GFX)
					{
						//Integrated
						gpuTemperatureCore = currentValue;
					}
					else if (currentSensor == ADL_PMLOG_TEMPERATURE_EDGE)
					{
						//Dedicated
						gpuTemperatureCore = currentValue;
					}
					else if (currentSensor == ADL_PMLOG_TEMPERATURE_MEM)
					{
						gpuTemperatureMemory = currentValue;
					}
					else if (currentSensor == ADL_PMLOG_TEMPERATURE_HOTSPOT)
					{
						gpuTemperatureHotspot = currentValue;
					}
					else if (currentSensor == ADL_PMLOG_TEMPERATURE_INTAKE)
					{
						gpuTemperatureIntake = currentValue;
					}

					//Move to next metric
					index++;
				}

				//Update current statistics
				std::function<void()> updateFunction = [&]
					{
						if (gpuUsageCore >= 0 && gpuUsageCore <= 20000)
						{
							textblock_Current_Gpu_Usage().Text(number_to_wstring(gpuUsageCore) + L"%");
						}
						else
						{
							textblock_Current_Gpu_Usage().Text(L"...");
						}

						if (gpuSpeedCore >= 0 && gpuSpeedCore <= 20000)
						{
							textblock_Current_Core_Speed().Text(number_to_wstring(gpuSpeedCore) + L"MHz");
						}
						else
						{
							textblock_Current_Core_Speed().Text(L"");
						}

						if (gpuUsageMemory >= 0 && gpuUsageMemory <= 20000)
						{
							textblock_Current_Memory_Usage().Text(number_to_wstring(gpuUsageMemory) + L"%");
						}
						else
						{
							textblock_Current_Memory_Usage().Text(L"");
						}

						if (gpuSpeedMemory >= 0 && gpuSpeedMemory <= 20000)
						{
							textblock_Current_Memory_Speed().Text(number_to_wstring(gpuSpeedMemory) + L"MTs");
						}
						else
						{
							textblock_Current_Memory_Speed().Text(L"");
						}

						if (gpuWatt >= 0 && gpuWatt <= 20000)
						{
							textblock_Current_Power_Watt().Text(number_to_wstring(gpuWatt) + L"W");
						}
						else
						{
							textblock_Current_Power_Watt().Text(L"");
						}

						if (gpuVoltage >= 0 && gpuVoltage <= 20000)
						{
							textblock_Current_Power_Voltage().Text(number_to_wstring(gpuVoltage) + L"mV");
						}
						else
						{
							textblock_Current_Power_Voltage().Text(L"");
						}

						if (gpuFanSpeedRpm >= 0 && gpuFanSpeedRpm <= 20000)
						{
							textblock_Current_Fan_Speed().Text(number_to_wstring(gpuFanSpeedRpm) + L"RPM");
						}
						else
						{
							textblock_Current_Fan_Speed().Text(L"");
						}

						if (gpuTemperatureCore >= 0 && gpuTemperatureCore <= 20000)
						{
							textblock_Current_Temp_Core().Text(number_to_wstring(gpuTemperatureCore) + L"°C Core");
						}
						else
						{
							textblock_Current_Temp_Core().Text(L"");
						}

						if (gpuTemperatureMemory >= 0 && gpuTemperatureMemory <= 20000)
						{
							textblock_Current_Temp_Memory().Text(number_to_wstring((int)gpuTemperatureMemory) + L"°C Memory");
						}
						else
						{
							textblock_Current_Temp_Memory().Text(L"");
						}

						if (gpuTemperatureHotspot >= 0 && gpuTemperatureHotspot <= 20000)
						{
							textblock_Current_Temp_Hotspot().Text(number_to_wstring((int)gpuTemperatureHotspot) + L"°C Hotspot");
						}
						else
						{
							textblock_Current_Temp_Hotspot().Text(L"");
						}

						if (gpuTemperatureIntake >= 0 && gpuTemperatureIntake <= 20000)
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