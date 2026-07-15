#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"
#include "DisplayDetailsIdl.h"

namespace winrt::RadeonTuner::implementation
{
	std::wstring MainPage::AdlxValuesPrepare()
	{
		try
		{
			//List all scaling mode
			{
				auto itemCollection = combobox_Display_ScalingMode().Items();
				UINT appendCount = ADLX_SCALE_MODE_STRING.size();
				for (UINT i = 0; i < appendCount; i++)
				{
					itemCollection.Append(box_value(ADLX_SCALE_MODE_STRING[i]));
				}
			}

			//List all color depth
			{
				auto itemCollection = combobox_Display_ColorDepth().Items();
				UINT appendCount = ADLX_COLOR_DEPTH_STRING.size();
				for (UINT i = 1; i < appendCount; i++)
				{
					itemCollection.Append(box_value(ADLX_COLOR_DEPTH_STRING[i]));
				}
			}

			//List all pixel format
			{
				auto itemCollection = combobox_Display_PixelFormat().Items();
				UINT appendCount = ADLX_PIXEL_FORMAT_STRING.size();
				for (UINT i = 1; i < appendCount; i++)
				{
					itemCollection.Append(box_value(ADLX_PIXEL_FORMAT_STRING[i]));
				}
			}

			//List all display color enhancement
			{
				auto itemCollection = combobox_Display_DisplayColorEnhancement().Items();
				UINT appendCount = ADLX_SCE_PROFILE_STRING.size();
				for (UINT i = 0; i < appendCount; i++)
				{
					itemCollection.Append(box_value(ADLX_SCE_PROFILE_STRING[i]));
				}
			}

			//List all vari-bright level
			{
				auto itemCollection = combobox_Display_VariBright_Level().Items();
				UINT appendCount = ADLX_VARIBRIGHT_LEVEL_STRING.size();
				for (UINT i = 0; i < appendCount; i++)
				{
					itemCollection.Append(box_value(ADLX_VARIBRIGHT_LEVEL_STRING[i]));
				}
			}

			//List all vertical sync
			{
				auto itemCollection = combobox_VerticalSync().Items();
				UINT appendCount = ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE_STRING.size();
				for (UINT i = 0; i < appendCount; i++)
				{
					itemCollection.Append(box_value(ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE_STRING[i]));
				}
			}

			//List all anti-aliasing method
			{
				auto itemCollection = combobox_AntiAliasingMethod().Items();
				UINT appendCount = ADLX_ANTI_ALIASING_METHOD_STRING.size();
				for (UINT i = 0; i < appendCount; i++)
				{
					itemCollection.Append(box_value(ADLX_ANTI_ALIASING_METHOD_STRING[i]));
				}
			}

			//List all anti-aliasing level
			{
				auto itemCollection = combobox_AntiAliasingLevel().Items();
				UINT appendCount = ADLX_ANTI_ALIASING_LEVEL_STRING.size();
				for (UINT i = 0; i < appendCount; i++)
				{
					itemCollection.Append(box_value(ADLX_ANTI_ALIASING_LEVEL_STRING[i]));
				}
			}

			//List all anisotropic texture filtering override
			{
				auto itemCollection = combobox_AnisotropicTextureFiltering().Items();
				UINT appendCount = ADLX_ANISOTROPIC_FILTERING_LEVEL_STRING.size();
				for (UINT i = 0; i < appendCount; i++)
				{
					itemCollection.Append(box_value(ADLX_ANISOTROPIC_FILTERING_LEVEL_STRING[i]));
				}
			}

			//List all tessellation mode
			{
				auto itemCollection = combobox_Tessellation_Mode().Items();
				UINT appendCount = ADLX_TESSELLATION_MODE_STRING.size();
				for (UINT i = 0; i < appendCount; i++)
				{
					itemCollection.Append(box_value(ADLX_TESSELLATION_MODE_STRING[i]));
				}
			}

			//List all tessellation level
			{
				auto itemCollection = combobox_Tessellation_Level().Items();
				UINT appendCount = ADLX_TESSELLATION_LEVEL_STRING.size();
				for (UINT i = 0; i < appendCount; i++)
				{
					itemCollection.Append(box_value(ADLX_TESSELLATION_LEVEL_STRING[i]));
				}
			}

			//List all memory timing
			//Fix only load available timings
			{
				auto itemCollection = combobox_Memory_Timing().Items();
				UINT appendCount = ADLX_MEMORYTIMING_DESCRIPTION_STRING.size();
				for (UINT i = 0; i < appendCount; i++)
				{
					itemCollection.Append(box_value(ADLX_MEMORYTIMING_DESCRIPTION_STRING[i]));
				}
			}

			//List all texture filtering qualities
			{
				auto itemCollection = combobox_TextureFilteringQuality().Items();
				UINT appendCount = REGISTRY_TEXTURE_FILTERING_QUALITY_STRING.size();
				for (UINT i = 0; i < appendCount; i++)
				{
					itemCollection.Append(box_value(REGISTRY_TEXTURE_FILTERING_QUALITY_STRING[i]));
				}
			}

			//List all fsr multi frame generation ratios
			{
				auto itemCollection = combobox_MultiFrameGenerationRatio().Items();
				UINT appendCount = ADL_FSR_MULTIFRAMEGEN_RATIO.size();
				for (UINT i = 0; i < appendCount; i++)
				{
					itemCollection.Append(box_value(ADL_FSR_MULTIFRAMEGEN_RATIO[i]));
				}
			}

			//List all Display orientations
			{
				auto itemCollection = combobox_Display_Orientation().Items();
				UINT appendCount = ADL_DISPLAY_ORIENTATIONS.size();
				for (UINT i = 0; i < appendCount; i++)
				{
					itemCollection.Append(box_value(ADL_DISPLAY_ORIENTATIONS[i]));
				}
			}

			//List all Eyefinity orientations
			{
				auto itemCollection = combobox_EyefinityMonitorOrientation().Items();
				UINT appendCount = ADL_DISPLAY_ORIENTATIONS.size();
				for (UINT i = 0; i < appendCount; i++)
				{
					itemCollection.Append(box_value(ADL_DISPLAY_ORIENTATIONS[i]));
				}
			}

			//List all HDR Media Profiles
			{
				auto itemCollection = combobox_Display_HdrMediaProfile().Items();
				UINT appendCount = ADL_HDR_TYPE_PREFERENCE.size();
				for (UINT i = 0; i < appendCount; i++)
				{
					itemCollection.Append(box_value(ADL_HDR_TYPE_PREFERENCE[i]));
				}
			}

			//List all FSR Over-The-Air Updates
			{
				auto itemCollection = combobox_FsrOtaUpdates().Items();
				UINT appendCount = REGISTRY_FSR_OTA_CONTROL_STRING.size();
				for (UINT i = 0; i < appendCount; i++)
				{
					itemCollection.Append(box_value(REGISTRY_FSR_OTA_CONTROL_STRING[i]));
				}
			}

			//List all fluid motion search modes
			{
				auto itemCollection = combobox_FrameGenSearchMode().Items();
				UINT appendCount = REGISTRY_FRAMEGEN_SEARCH_MODE_STRING.size();
				for (UINT i = 0; i < appendCount; i++)
				{
					itemCollection.Append(box_value(REGISTRY_FRAMEGEN_SEARCH_MODE_STRING[i]));
				}
			}

			//List all fluid motion performance modes
			{
				auto itemCollection = combobox_FrameGenPerfMode().Items();
				UINT appendCount = REGISTRY_FRAMEGEN_PERFORMANCE_MODE_STRING.size();
				for (UINT i = 0; i < appendCount; i++)
				{
					itemCollection.Append(box_value(REGISTRY_FRAMEGEN_PERFORMANCE_MODE_STRING[i]));
				}
			}

			//List all fluid motion response modes
			{
				auto itemCollection = combobox_FrameGenResponseMode().Items();
				UINT appendCount = REGISTRY_FRAMEGEN_RESPONSE_MODE_STRING.size();
				for (UINT i = 0; i < appendCount; i++)
				{
					itemCollection.Append(box_value(REGISTRY_FRAMEGEN_RESPONSE_MODE_STRING[i]));
				}
			}

			//List all fluid motion algorithm modes
			{
				auto itemCollection = combobox_FrameGenAlgorithm().Items();
				UINT appendCount = REGISTRY_FRAMEGEN_ALGORITHM_MODE_STRING.size();
				for (UINT i = 0; i < appendCount; i++)
				{
					itemCollection.Append(box_value(REGISTRY_FRAMEGEN_ALGORITHM_MODE_STRING[i]));
				}
			}

			//Load and list all displays
			std::wstring displayResult = AdlxValuesLoadDisplayList(true);
			if (!displayResult.empty())
			{
				return displayResult;
			}

			//Load and list all gpus
			std::wstring gpuResult = AdlxValuesLoadGpuList(true);
			if (!gpuResult.empty())
			{
				return gpuResult;
			}

			//Remove global user application
			AdlApplication globalApp{};
			globalApp.FileName = L"*.*";
			globalApp.FilePath = L"*\\*";
			AdlAppRemove(globalApp);

			//Load and list applications
			AdlxValuesLoadApplicationList(true);

			//Set result
			AVDebugWriteLine("ADL values prepared.");
			return L"";
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADL values preparation failed.");
			return L"ADL values preparation failed.";
		}
	}
}