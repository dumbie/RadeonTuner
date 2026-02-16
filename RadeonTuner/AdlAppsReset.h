#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "AdlVariables.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlAppDefaultPropertiesSet(AdlApplication& adlApp)
	{
		try
		{
			AVDebugWriteLine("Resetting application properties to defaults: " << adlApp.FileName << " / " << adlApp.FilePath << " / " << adlApp.DriverArea << " / " << gpuUniqueIdentifierHex);

			//Clear all application properties
			adlApp.Properties.clear();

			//Radeon FSR Upscaling Override
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"FsrOverride", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"FsrOverride";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"0";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//Radeon FSR Frame Generation Override
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"MlfiOverride", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"MlfiOverride";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"0";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//Radeon Anti-Lag
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"Dlg_PFEnable", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"Dlg_PFEnable";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"0";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//Radeon Boost
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"Bst_PFEnable", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"Bst_PFEnable";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"0";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//Radeon Boost Minimum Resolution
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"Bst_MaxScale", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"Bst_MaxScale";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"84";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//Radeon Chill
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"Chil_PFEnable", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"Chil_PFEnable";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"0";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//Radeon Chill Minimum
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"Chil_MinFRate", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"Chil_MinFRate";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"75";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//Radeon Chill Maximum
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"Chil_MaxFRate", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"Chil_MaxFRate";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"140";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//Radeon Image Sharpening
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"Ris_PFEnable", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"Ris_PFEnable";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"0";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//Radeon Image Sharpening Sharpness
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"Ris_SHDegree", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"Ris_SHDegree";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"0.8";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//Enhanced Sync
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"TurboSync", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"TurboSync";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"0";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//Vertical Refresh
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"VSyncControl", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"VSyncControl";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"1";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//Anti-Aliasing Override
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"AntiAlias", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"AntiAlias";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"1";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//Anti-Aliasing Method
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"ASD", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"ASD";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"-1";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"ASE", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"ASE";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"0";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"ASTT", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"ASTT";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"0";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//Anti-Aliasing Level
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"AntiAliasSmpls", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"AntiAliasSmpls";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"8"; //AMD Default 2
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//Enhanced Quality Anti-Aliasing
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"EQAA", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"EQAA";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"0";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//Morphological Anti-Aliasing
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"MLF", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"MLF";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"0";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//Anisotropic Texture Filtering Override
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"AnisoDegree", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"AnisoDegree";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"0";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//Texture Filtering Quality
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"TFQ", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"TFQ";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"1";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//Surface Format Optimization
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"SrfcFrmtRplcmnt", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"SrfcFrmtRplcmnt";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"0";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//Tessellation Mode
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"Tessellation_OP", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"Tessellation_OP";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"0";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//Tessellation Level
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"Tessellation", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"Tessellation";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"64";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//OpenGL Triple Buffering
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlAppPropertyTypeGet(L"EnableTrplBffr", adlApp.DriverArea);
				if (adlAppProperty.Type != AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
				{
					adlAppProperty.Name = L"EnableTrplBffr";
					AdlAppPropertyValue adlAppPropertyValue{};
					adlAppPropertyValue.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue.Value = L"0";
					adlAppProperty.Values.push_back(adlAppPropertyValue);
					adlApp.Properties.push_back(adlAppProperty);
				}
			}

			//Set result
			return true;
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed resetting application properties (Exception)");
			return false;
		}
	}
}