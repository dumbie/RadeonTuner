#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::AdlxValuesPrepare()
	{
		//List all gpus
		auto itemCollection = combobox_GpuSelect().Items();
		for (UINT i = 0; i < ppGpuList->Size(); i++)
		{
			const char* gpuName;
			ppGpuList->At(i, (IADLXGPU**)&ppGpuInfo);
			ppGpuInfo->Name(&gpuName);
			itemCollection.Append(box_value(char_to_wstring(gpuName)));
		}

		//List all displays
		itemCollection = combobox_DisplaySelect().Items();
		for (UINT i = 0; i < ppDisplayList->Size(); i++)
		{
			const char* displayName;
			ppDisplayList->At(i, &ppDisplayInfo);
			ppDisplayInfo->Name(&displayName);
			itemCollection.Append(box_value(char_to_wstring(displayName)));
		}

		//List all applications
		itemCollection = combobox_AppSelect().Items();
		itemCollection.Append(box_value(L"Global"));

		//List all color depth
		itemCollection = combobox_Display_ColorDepth().Items();
		itemCollection.Append(box_value(L"6 bpc"));
		itemCollection.Append(box_value(L"8 bpc"));
		itemCollection.Append(box_value(L"10 bpc"));
		itemCollection.Append(box_value(L"12 bpc"));
		itemCollection.Append(box_value(L"14 bpc"));
		itemCollection.Append(box_value(L"16 bpc"));

		//List all pixel format
		itemCollection = combobox_Display_PixelFormat().Items();
		itemCollection.Append(box_value(L"RGB 4:4:4 PC Standard (Full RGB)"));
		itemCollection.Append(box_value(L"YCbCr 4:4:4"));
		itemCollection.Append(box_value(L"YCbCr 4:2:2"));
		itemCollection.Append(box_value(L"RGB 4:4:4 Studio (Limited RGB)"));
		itemCollection.Append(box_value(L"YCbCr 4:2:0"));

		//List all vertical sync
		itemCollection = combobox_VerticalRefresh().Items();
		itemCollection.Append(box_value(L"Always Off"));
		itemCollection.Append(box_value(L"Off, unless application specifies"));
		itemCollection.Append(box_value(L"On, unless application specifies"));
		itemCollection.Append(box_value(L"Always On"));

		//List all anti-aliasing mode
		itemCollection = combobox_AntiAliasingMode().Items();
		itemCollection.Append(box_value(L"Use application settings"));
		itemCollection.Append(box_value(L"Enhance application settings"));
		itemCollection.Append(box_value(L"Override application settings"));

		//List all anti-aliasing method
		itemCollection = combobox_AntiAliasingMethod().Items();
		itemCollection.Append(box_value(L"Multisampling"));
		itemCollection.Append(box_value(L"Adaptive multisampling"));
		itemCollection.Append(box_value(L"Supersampling"));

		//List all anti-aliasing level
		itemCollection = combobox_AntiAliasingLevel().Items();
		itemCollection.Append(box_value(L"2X"));
		itemCollection.Append(box_value(L"2XEQ"));
		itemCollection.Append(box_value(L"4X"));
		itemCollection.Append(box_value(L"4XEQ"));
		itemCollection.Append(box_value(L"8X"));
		itemCollection.Append(box_value(L"8XEQ"));

		//List all memory timing
		adlx_Res0 = ppGPUTuningServices->IsSupportedManualVRAMTuning(ppGpuInfo, &adlx_Bool);
		if (adlx_Bool)
		{
			IADLXManualVRAMTuning2Ptr ppManualVRAMTuning;
			adlx_Res0 = ppGPUTuningServices->GetManualVRAMTuning(ppGpuInfo, (IADLXInterface**)&ppManualVRAMTuning);
			adlx_Res0 = ppManualVRAMTuning->IsSupportedMemoryTiming(&adlx_Bool);
			if (adlx_Bool)
			{
				IADLXMemoryTimingDescriptionListPtr memoryTimingDescriptionListPtr;
				adlx_Res0 = ppManualVRAMTuning->GetSupportedMemoryTimingDescriptionList(&memoryTimingDescriptionListPtr);

				itemCollection = combobox_Memory_Timing().Items();
				for (UINT i = 0; i < memoryTimingDescriptionListPtr->Size(); i++)
				{
					IADLXMemoryTimingDescriptionPtr memoryTimingDescriptionPtr;
					memoryTimingDescriptionListPtr->At(i, &memoryTimingDescriptionPtr);

					ADLX_MEMORYTIMING_DESCRIPTION memoryTimingDescription;
					adlx_Res0 = memoryTimingDescriptionPtr->GetDescription(&memoryTimingDescription);

					if (memoryTimingDescription == ADLX_MEMORYTIMING_DESCRIPTION::MEMORYTIMING_DEFAULT)
					{
						itemCollection.Append(box_value(L"Default"));
					}
					else if (memoryTimingDescription == ADLX_MEMORYTIMING_DESCRIPTION::MEMORYTIMING_FAST_TIMING)
					{
						itemCollection.Append(box_value(L"Fast Timing 1"));
					}
					else if (memoryTimingDescription == ADLX_MEMORYTIMING_DESCRIPTION::MEMORYTIMING_FAST_TIMING_LEVEL_2)
					{
						itemCollection.Append(box_value(L"Fast Timing 2"));
					}
					else if (memoryTimingDescription == ADLX_MEMORYTIMING_DESCRIPTION::MEMORYTIMING_AUTOMATIC)
					{
						itemCollection.Append(box_value(L"Automatic Timing"));
					}
					else if (memoryTimingDescription == ADLX_MEMORYTIMING_DESCRIPTION::MEMORYTIMING_MEMORYTIMING_LEVEL_1)
					{
						itemCollection.Append(box_value(L"Memory Timing 1"));
					}
					else if (memoryTimingDescription == ADLX_MEMORYTIMING_DESCRIPTION::MEMORYTIMING_MEMORYTIMING_LEVEL_2)
					{
						itemCollection.Append(box_value(L"Memory Timing 2"));
					}
					else
					{
						itemCollection.Append(box_value(L"Unknown Timing"));
					}
				}
			}
		}

		AVDebugWriteLine("ADLX prepared.");
	}
}