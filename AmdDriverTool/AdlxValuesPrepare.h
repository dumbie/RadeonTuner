#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::AdlxValuesPrepare()
	{
		try
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

			//List all scaling mode
			itemCollection = combobox_Display_ScalingMode().Items();
			itemCollection.Append(box_value(L"Preserve aspect ratio"));
			itemCollection.Append(box_value(L"Full panel"));
			itemCollection.Append(box_value(L"Center"));

			//List all color depth
			itemCollection = combobox_Display_ColorDepth().Items();
			itemCollection.Append(box_value(L"6 bits per color"));
			itemCollection.Append(box_value(L"8 bits per color"));
			itemCollection.Append(box_value(L"10 bits per color"));
			itemCollection.Append(box_value(L"12 bits per color"));
			itemCollection.Append(box_value(L"14 bits per color"));
			itemCollection.Append(box_value(L"16 bits per color"));

			//List all pixel format
			itemCollection = combobox_Display_PixelFormat().Items();
			itemCollection.Append(box_value(L"RGB 4:4:4 PC Standard (Full RGB)"));
			itemCollection.Append(box_value(L"YCbCr 4:4:4"));
			itemCollection.Append(box_value(L"YCbCr 4:2:2"));
			itemCollection.Append(box_value(L"RGB 4:4:4 Studio (Limited RGB)"));
			itemCollection.Append(box_value(L"YCbCr 4:2:0"));

			//List all vari-bright level
			itemCollection = combobox_Display_VariBright_Level().Items();
			itemCollection.Append(box_value(L"Maximize Brightness"));
			itemCollection.Append(box_value(L"Optimize Brightness"));
			itemCollection.Append(box_value(L"Balanced"));
			itemCollection.Append(box_value(L"Optimize Battery"));
			itemCollection.Append(box_value(L"Maximize Battery"));

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

			//List all Anisotropic texture filtering
			itemCollection = combobox_AnisotropicTextureFilteringQuality().Items();
			itemCollection.Append(box_value(L"2X"));
			itemCollection.Append(box_value(L"4X"));
			itemCollection.Append(box_value(L"8X"));
			itemCollection.Append(box_value(L"16X"));

			//List all tessellation mode
			itemCollection = combobox_Tessellation_Mode().Items();
			itemCollection.Append(box_value(L"AMD optimized"));
			itemCollection.Append(box_value(L"Use application settings"));
			itemCollection.Append(box_value(L"Override application settings"));

			//List all tessellation level
			itemCollection = combobox_Tessellation_Level().Items();
			itemCollection.Append(box_value(L"Off"));
			itemCollection.Append(box_value(L"2X"));
			itemCollection.Append(box_value(L"4X"));
			itemCollection.Append(box_value(L"6X"));
			itemCollection.Append(box_value(L"8X"));
			itemCollection.Append(box_value(L"16X"));
			itemCollection.Append(box_value(L"32X"));
			itemCollection.Append(box_value(L"64X"));

			//List all memory timing
			itemCollection = combobox_Memory_Timing().Items();
			itemCollection.Append(box_value(L"Default"));
			itemCollection.Append(box_value(L"Fast Timing 1"));
			itemCollection.Append(box_value(L"Fast Timing 2"));
			itemCollection.Append(box_value(L"Automatic Timing"));
			itemCollection.Append(box_value(L"Memory Timing 1"));
			itemCollection.Append(box_value(L"Memory Timing 2"));

			//List all smartshift max modes
			itemCollection = combobox_SmartShiftMaxMode().Items();
			itemCollection.Append(box_value(L"Auto"));
			itemCollection.Append(box_value(L"Manual"));

			//Set result
			AVDebugWriteLine("ADLX prepared.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX preparation failed.");
		}
	}
}