#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"
#include "DisplayDetailsIdl.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesPrepare()
	{
		try
		{
			//List all gpus
			{
				auto itemCollection = combobox_GpuSelect().Items();
				UINT appendCount = ppGpuList->Size();
				for (UINT i = 0; i < appendCount; i++)
				{
					const char* gpuName;
					IADLXGPU2Ptr gpuInfo;
					adlx_Res0 = ppGpuList->At(i, (IADLXGPU**)&gpuInfo);
					adlx_Res0 = gpuInfo->Name(&gpuName);
					itemCollection.Append(box_value(char_to_wstring(gpuName)));
				}
			}

			//List all displays
			{
				auto itemCollection = combobox_DisplaySelect().Items();
				auto itemCollectionEyefinity = winrt::single_threaded_observable_vector<winrt::Windows::Foundation::IInspectable>();
				UINT appendCount = ppDisplayList->Size();
				for (UINT i = 0; i < appendCount; i++)
				{
					//Get display details
					const char* displayName;
					IADLXDisplayPtr displayInfo;
					adlx_Res0 = ppDisplayList->At(i, (IADLXDisplay**)&displayInfo);
					adlx_Res0 = displayInfo->Name(&displayName);
					auto displayNameString = char_to_wstring(displayName);

					//Display select
					itemCollection.Append(box_value(displayNameString));

					//Get ADL display index
					int ppNullptr;
					int displayAdapterIndex;
					int displayDisplayIndex;
					adlx_Res0 = ppAdlMapping->ADLIdsFromADLXDisplay(displayInfo, &displayAdapterIndex, &displayDisplayIndex, &ppNullptr, &ppNullptr, &ppNullptr);

					//Eyefinity
					RadeonTuner::DisplayDetailsIdl displayDetails;
					displayDetails.IndexAdapter(displayAdapterIndex);
					displayDetails.IndexDisplay(displayDisplayIndex);
					displayDetails.Name(displayNameString);
					itemCollectionEyefinity.Append(box_value(displayDetails));

					//Set maximum rows and columns based on display count
					slider_Eyefinity_Columns().Maximum(appendCount);
					slider_Eyefinity_Rows().Maximum(appendCount);
				}
				listview_EyefinityMonitorIndex().ItemsSource(itemCollectionEyefinity);
			}

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
				auto itemCollection = combobox_VerticalRefresh().Items();
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
				auto itemCollection = combobox_AnisotropicTextureFiltering_Level().Items();
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

			//List all smartshift max modes
			{
				auto itemCollection = combobox_SmartShiftMaxMode().Items();
				UINT appendCount = ADLX_SSM_BIAS_MODE_STRING.size();
				for (UINT i = 0; i < appendCount; i++)
				{
					itemCollection.Append(box_value(ADLX_SSM_BIAS_MODE_STRING[i]));
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

			//List all Eyefinity orientations
			{
				auto itemCollection = combobox_EyefinityMonitorOrientation().Items();
				UINT appendCount = ADL_EYEFINITY_ORIENTATIONS.size();
				for (UINT i = 0; i < appendCount; i++)
				{
					itemCollection.Append(box_value(ADL_EYEFINITY_ORIENTATIONS[i]));
				}
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