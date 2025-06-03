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
		for (UINT i = 0; i < gpuList->Size(); i++)
		{
			const char* gpuName;
			gpuList->At(i, (IADLXGPU**)&gpuInfo);
			gpuInfo->Name(&gpuName);
			itemCollection.Append(box_value(char_to_wstring(gpuName)));
		}

		//List all displays
		itemCollection = combobox_DisplaySelect().Items();
		for (UINT i = 0; i < displayList->Size(); i++)
		{
			const char* displayName;
			displayList->At(i, &displayInfo);
			displayInfo->Name(&displayName);
			itemCollection.Append(box_value(char_to_wstring(displayName)));
		}

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

		//List all memory timing
		IADLXManualVRAMTuning2Ptr ppManualVRAMTuning;
		res = gpuTuningService->GetManualVRAMTuning(gpuInfo, (IADLXInterface**)&ppManualVRAMTuning);

		IADLXMemoryTimingDescriptionListPtr timingDescriptionListPtr;
		res = ppManualVRAMTuning->GetSupportedMemoryTimingDescriptionList(&timingDescriptionListPtr);

		itemCollection = combobox_Memory_Timing().Items();
		for (UINT i = 0; i < timingDescriptionListPtr->Size(); i++)
		{
			IADLXMemoryTimingDescriptionPtr timingDescriptionPtr;
			timingDescriptionListPtr->At(i, &timingDescriptionPtr);

			ADLX_MEMORYTIMING_DESCRIPTION timingDescription;
			res = timingDescriptionPtr->GetDescription(&timingDescription);

			if (timingDescription == ADLX_MEMORYTIMING_DESCRIPTION::MEMORYTIMING_DEFAULT)
			{
				itemCollection.Append(box_value(L"Default"));
			}
			else if (timingDescription == ADLX_MEMORYTIMING_DESCRIPTION::MEMORYTIMING_FAST_TIMING)
			{
				itemCollection.Append(box_value(L"Fast Timing"));
			}
		}

		AVDebugWriteLine("ADLX prepared.");
	}
}