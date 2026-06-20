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
				//Get combobox items
				auto itemCollection = combobox_GpuSelect().Items();

				//Get all GPU's
				adl_List_Gpus = AdlGetGpuAll();
				int adapterCount = adl_List_Gpus.size();

				//Add all GPU's
				for (AdapterInfo adapterInfo : adl_List_Gpus)
				{
					//Add gpu to combobox
					itemCollection.Append(box_value(char_to_wstring(adapterInfo.strAdapterName)));
				}

				AVDebugWriteLine("Listed all GPU's: " << adapterCount);
			}

			//List all displays
			{
				//Get combobox items
				auto itemCollectionSelect = combobox_DisplaySelect().Items();
				auto itemCollectionEyefinity = winrt::single_threaded_observable_vector<winrt::Windows::Foundation::IInspectable>();

				//Get all displays
				adl_List_Displays = AdlGetDisplayAll();
				int displayCount = adl_List_Displays.size();

				//Add all displays
				for (ADLDisplayInfo displayInfo : adl_List_Displays)
				{
					//Get display name
					std::wstring displayNameString = char_to_wstring(displayInfo.strDisplayName);

					//Add display to combobox
					itemCollectionSelect.Append(box_value(displayNameString));

					//Get adapter and display index
					int displayAdapterIndex = displayInfo.displayID.iDisplayLogicalAdapterIndex;
					int displayDisplayIndex = displayInfo.displayID.iDisplayLogicalIndex;

					//Eyefinity displays list
					RadeonTuner::DisplayDetailsIdl displayDetails;
					displayDetails.IndexAdapter(displayAdapterIndex);
					displayDetails.IndexDisplay(displayDisplayIndex);
					displayDetails.Name(displayNameString);
					itemCollectionEyefinity.Append(box_value(displayDetails));

					//Set min and max rows and columns based on display count
					slider_Eyefinity_Rows().Minimum(1);
					slider_Eyefinity_Rows().Maximum(displayCount);
					slider_Eyefinity_Columns().Minimum(1);
					slider_Eyefinity_Columns().Maximum(displayCount);
				}
				listview_EyefinityMonitorIndex().ItemsSource(itemCollectionEyefinity);

				AVDebugWriteLine("Listed all displays: " << displayCount);
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
			AVDebugWriteLine("ADL values prepared.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADL values preparation failed.");
		}
	}
}