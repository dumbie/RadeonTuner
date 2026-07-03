#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlAppsSetDefaults(AdlApplication& adlApp, bool clearProperties, bool addOnly)
	{
		try
		{
			AVDebugWriteLine("Setting application graphics to defaults: " << clearProperties << " / " << addOnly << " / " << adlApp.FileName << " / " << adlApp.FilePath << " / " << adlApp.DriverArea << " / " << gpuUniqueIdentifierHex);

			//Clear all application properties
			if (clearProperties)
			{
				adlApp.Properties.clear();
			}

			//Set default application properties
			std::vector<AdlAppProperty> adlAppProperties{};

			//FSR Upscaling Override
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"FsrOverride";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"1";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//FSR Frame Generation Override
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"MlfiOverride";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"1";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//FSR Multi Frame Generation Override
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"MfgOverride";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"0";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//FSR Multi Frame Generation Ratio
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"MfgRatio";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"0";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//FSR Ray Regeneration Denoiser Override
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"MldOverride";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"0";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//FSR Neural Radiance Caching Override
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"NrcOverride";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"0";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//FSR Override Library
			{
				//Not supported
			}

			//FSR Over-The-Air Updates
			{
				//Not supported
			}

			//FSR Latency Reduction
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"Dlg_PFEnable";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"0";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Radeon Boost
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"Bst_PFEnable";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"0";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Radeon Boost Minimum Resolution
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"Bst_MaxScale";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"68";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Radeon Chill
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"Chil_PFEnable";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"0";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Radeon Chill Minimum Frame Rate
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"Chil_MinFRate";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"75";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Radeon Chill Maximum Frame Rate
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"Chil_MaxFRate";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"140";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Radeon Image Sharpening 1
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"Ris_PFEnable";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"0";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Radeon Image Sharpening 1 Sharpness
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"Ris_SHDegree";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"0.8";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Radeon Image Sharpening 2
			{
				//Not supported
			}

			//Enhanced Sync
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"TurboSync";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"0";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Vertical Sync
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"VSyncControl";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"1";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Frame Rate Target Control
			{
				//Not supported
			}

			//Anti-Aliasing Override
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"AntiAlias";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"1";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Anti-Aliasing Method
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"ASD";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"-1";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"ASE";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"0";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"ASTT";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"0";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Anti-Aliasing Level
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"AntiAliasSmpls";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"2";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Enhanced Quality Anti-Aliasing
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"EQAA";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"0";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Morphological Anti-Aliasing
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"MLF";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"0";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Anisotropic Texture Filtering Override
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"AnisoDegree";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"0";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Texture Filtering Quality
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"TFQ";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"1";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Surface Format Optimization
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"SrfcFrmtRplcmnt";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"0";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Tessellation Mode
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"Tessellation_OP";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"0";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Tessellation Level
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"Tessellation";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"64";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//OpenGL Triple Buffering
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"EnableTrplBffr";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = L"0";
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//OpenGL 10-Bit Pixel Format
			{
				//Not supported
			}

			//Update application properties
			AVDebugWriteLine("ADL graphics application values reset.");
			return AdlAppPropertyUpdate(adlApp, adlAppProperties, addOnly);
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed resetting application graphics (Exception)");
			return false;
		}
	}
}