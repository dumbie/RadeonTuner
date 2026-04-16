#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesPrepare()
	{
		try
		{
			//List all gpus
			auto itemCollection = combobox_GpuSelect().Items();
			UINT appendCount = ppGpuList->Size();
			for (UINT i = 0; i < appendCount; i++)
			{
				const char* gpuName;
				adlx_Res0 = ppGpuList->At(i, (IADLXGPU**)&ppGpuInfo);
				adlx_Res0 = ppGpuInfo->Name(&gpuName);
				itemCollection.Append(box_value(char_to_wstring(gpuName)));
			}

			//List all displays
			itemCollection = combobox_DisplaySelect().Items();
			appendCount = ppDisplayList->Size();
			for (UINT i = 0; i < appendCount; i++)
			{
				const char* displayName;
				adlx_Res0 = ppDisplayList->At(i, &ppDisplayInfo);
				adlx_Res0 = ppDisplayInfo->Name(&displayName);
				itemCollection.Append(box_value(char_to_wstring(displayName)));
			}

			//List all scaling mode
			itemCollection = combobox_Display_ScalingMode().Items();
			appendCount = ADLX_SCALE_MODE_STRING.size();
			for (UINT i = 0; i < appendCount; i++)
			{
				itemCollection.Append(box_value(ADLX_SCALE_MODE_STRING[i]));
			}

			//List all color depth
			itemCollection = combobox_Display_ColorDepth().Items();
			appendCount = ADLX_COLOR_DEPTH_STRING.size();
			for (UINT i = 1; i < appendCount; i++)
			{
				itemCollection.Append(box_value(ADLX_COLOR_DEPTH_STRING[i]));
			}

			//List all pixel format
			itemCollection = combobox_Display_PixelFormat().Items();
			appendCount = ADLX_PIXEL_FORMAT_STRING.size();
			for (UINT i = 1; i < appendCount; i++)
			{
				itemCollection.Append(box_value(ADLX_PIXEL_FORMAT_STRING[i]));
			}

			//List all display color enhancement
			itemCollection = combobox_Display_DisplayColorEnhancement().Items();
			appendCount = ADLX_SCE_PROFILE_STRING.size();
			for (UINT i = 0; i < appendCount; i++)
			{
				itemCollection.Append(box_value(ADLX_SCE_PROFILE_STRING[i]));
			}

			//List all vari-bright level
			itemCollection = combobox_Display_VariBright_Level().Items();
			appendCount = ADLX_VARIBRIGHT_LEVEL_STRING.size();
			for (UINT i = 0; i < appendCount; i++)
			{
				itemCollection.Append(box_value(ADLX_VARIBRIGHT_LEVEL_STRING[i]));
			}

			//List all vertical sync
			itemCollection = combobox_VerticalRefresh().Items();
			appendCount = ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE_STRING.size();
			for (UINT i = 0; i < appendCount; i++)
			{
				itemCollection.Append(box_value(ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE_STRING[i]));
			}

			//List all anti-aliasing method
			itemCollection = combobox_AntiAliasingMethod().Items();
			appendCount = ADLX_ANTI_ALIASING_METHOD_STRING.size();
			for (UINT i = 0; i < appendCount; i++)
			{
				itemCollection.Append(box_value(ADLX_ANTI_ALIASING_METHOD_STRING[i]));
			}

			//List all anti-aliasing level
			itemCollection = combobox_AntiAliasingLevel().Items();
			appendCount = ADLX_ANTI_ALIASING_LEVEL_STRING.size();
			for (UINT i = 0; i < appendCount; i++)
			{
				itemCollection.Append(box_value(ADLX_ANTI_ALIASING_LEVEL_STRING[i]));
			}

			//List all anisotropic texture filtering override
			itemCollection = combobox_AnisotropicTextureFiltering_Level().Items();
			appendCount = ADLX_ANISOTROPIC_FILTERING_LEVEL_STRING.size();
			for (UINT i = 0; i < appendCount; i++)
			{
				itemCollection.Append(box_value(ADLX_ANISOTROPIC_FILTERING_LEVEL_STRING[i]));
			}

			//List all tessellation mode
			itemCollection = combobox_Tessellation_Mode().Items();
			appendCount = ADLX_TESSELLATION_MODE_STRING.size();
			for (UINT i = 0; i < appendCount; i++)
			{
				itemCollection.Append(box_value(ADLX_TESSELLATION_MODE_STRING[i]));
			}

			//List all tessellation level
			itemCollection = combobox_Tessellation_Level().Items();
			appendCount = ADLX_TESSELLATION_LEVEL_STRING.size();
			for (UINT i = 0; i < appendCount; i++)
			{
				itemCollection.Append(box_value(ADLX_TESSELLATION_LEVEL_STRING[i]));
			}

			//List all memory timing
			//Fix only load available timings
			itemCollection = combobox_Memory_Timing().Items();
			appendCount = ADLX_MEMORYTIMING_DESCRIPTION_STRING.size();
			for (UINT i = 0; i < appendCount; i++)
			{
				itemCollection.Append(box_value(ADLX_MEMORYTIMING_DESCRIPTION_STRING[i]));
			}

			//List all smartshift max modes
			itemCollection = combobox_SmartShiftMaxMode().Items();
			appendCount = ADLX_SSM_BIAS_MODE_STRING.size();
			for (UINT i = 0; i < appendCount; i++)
			{
				itemCollection.Append(box_value(ADLX_SSM_BIAS_MODE_STRING[i]));
			}

			//List all texture filtering qualities
			itemCollection = combobox_TextureFilteringQuality().Items();
			appendCount = REGISTRY_TEXTURE_FILTERING_QUALITY_STRING.size();
			for (UINT i = 0; i < appendCount; i++)
			{
				itemCollection.Append(box_value(REGISTRY_TEXTURE_FILTERING_QUALITY_STRING[i]));
			}

			//List all fsr multi frame generation ratios
			itemCollection = combobox_MultiFrameGenerationRatio().Items();
			appendCount = ADL_FSR_MULTIFRAMEGEN_RATIO.size();
			for (UINT i = 0; i < appendCount; i++)
			{
				itemCollection.Append(box_value(ADL_FSR_MULTIFRAMEGEN_RATIO[i]));
			}

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