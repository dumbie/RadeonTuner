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

			//Get current and default settings
			GraphicsSettings graphicsSettings = GraphicsSettings_Generate_FromADLApp(adlApp).value();

			//Set default application properties
			std::vector<AdlAppProperty> adlAppProperties{};

			//FSR Upscaling Override
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"FsrOverride";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = number_to_wstring(graphicsSettings.FsrOverride.Default.value());
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//FSR Frame Generation Override
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"MlfiOverride";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = number_to_wstring(graphicsSettings.MlfiOverride.Default.value());
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//FSR Multi Frame Generation Override
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"MfgOverride";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = number_to_wstring(graphicsSettings.MfgOverride.Default.value());
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//FSR Multi Frame Generation Ratio
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"MfgRatio";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = number_to_wstring(graphicsSettings.MfgRatio.Default.value());
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//FSR Ray Regeneration Denoiser Override
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"MldOverride";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = number_to_wstring(graphicsSettings.MldOverride.Default.value());
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//FSR Neural Radiance Caching Override
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"NrcOverride";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = number_to_wstring(graphicsSettings.NrcOverride.Default.value());
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
				adlAppPropertyValue0.Value = number_to_wstring(graphicsSettings.DeLagEnabled.Default.value());
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Radeon Boost
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"Bst_PFEnable";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = number_to_wstring(graphicsSettings.BoostEnabled.Default.value());
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Radeon Boost Minimum Resolution
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"Bst_MaxScale";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = number_to_wstring(graphicsSettings.BoostMinResolution.Default.value());
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Radeon Chill
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"Chil_PFEnable";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = number_to_wstring(graphicsSettings.ChillEnabled.Default.value());
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Radeon Chill Minimum Frame Rate
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"Chil_MinFRate";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = number_to_wstring(graphicsSettings.ChillMinFps.Default.value());
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Radeon Chill Maximum Frame Rate
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"Chil_MaxFRate";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = number_to_wstring(graphicsSettings.ChillMaxFps.Default.value());
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Radeon Image Sharpening 1
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"Ris_PFEnable";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = number_to_wstring(graphicsSettings.RisEnabled.Default.value());
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Radeon Image Sharpening 1 Sharpness
			{
				float newValue = (float)graphicsSettings.RisSharpeningDegree.Default.value() / 100;

				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"Ris_SHDegree";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = float_to_wstring(newValue, 1);
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
				adlAppPropertyValue0.Value = number_to_wstring(graphicsSettings.EnhancedSync.Default.value());
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Vertical Sync
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"VSyncControl";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = number_to_wstring(graphicsSettings.VerticalSync.Default.value());
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
				adlAppPropertyValue0.Value = number_to_wstring(graphicsSettings.AntiAliasingOverride.Default.value());
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Anti-Aliasing Method
			{
				int newValue = graphicsSettings.AntiAliasingMethod.Default.value();

				//Enumeration index correction
				std::wstring setValueAsd = L"-1";
				std::wstring setValueAse = L"0";
				std::wstring setValueAstt = L"0";
				if (newValue == 0)
				{
					//Multisampling
					setValueAsd = L"-1";
					setValueAse = L"0";
					setValueAstt = L"0";
				}
				else if (newValue == 1)
				{
					//Adaptive Multisampling
					setValueAsd = L"1";
					setValueAse = L"0";
					setValueAstt = L"1";
				}
				else if (newValue == 2)
				{
					//Supersampling
					setValueAsd = L"1";
					setValueAse = L"1";
					setValueAstt = L"1";
				}

				{
					AdlAppProperty adlAppProperty0{};
					adlAppProperty0.Name = L"ASD";
					AdlAppPropertyValue adlAppPropertyValue0{};
					adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue0.Value = setValueAsd;
					adlAppProperty0.Values = { adlAppPropertyValue0 };
					adlAppProperties.push_back(adlAppProperty0);
				}
				{
					AdlAppProperty adlAppProperty0{};
					adlAppProperty0.Name = L"ASE";
					AdlAppPropertyValue adlAppPropertyValue0{};
					adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue0.Value = setValueAse;
					adlAppProperty0.Values = { adlAppPropertyValue0 };
					adlAppProperties.push_back(adlAppProperty0);
				}
				{
					AdlAppProperty adlAppProperty0{};
					adlAppProperty0.Name = L"ASTT";
					AdlAppPropertyValue adlAppPropertyValue0{};
					adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
					adlAppPropertyValue0.Value = setValueAstt;
					adlAppProperty0.Values = { adlAppPropertyValue0 };
					adlAppProperties.push_back(adlAppProperty0);
				}
			}

			//Anti-Aliasing Level
			{
				int newValue = graphicsSettings.AntiAliasingLevel.Default.value();

				//Enumeration index correction
				std::wstring setValue = L"2";
				if (newValue == 0)
				{
					setValue = L"2";
				}
				else if (newValue == 1)
				{
					setValue = L"4";
				}
				else if (newValue == 2)
				{
					setValue = L"8";
				}

				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"AntiAliasSmpls";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = setValue;
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Enhanced Quality Anti-Aliasing
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"EQAA";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = number_to_wstring(graphicsSettings.AntiAliasingEnhancedQuality.Default.value());
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Morphological Anti-Aliasing
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"MLF";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = number_to_wstring(graphicsSettings.AntiAliasingMorphological.Default.value());
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Anisotropic Texture Filtering Override
			{
				int newValue = graphicsSettings.AnisotropicOverride.Default.value();

				//Enumeration index correction
				std::wstring setValue = L"0";
				if (newValue == 0)
				{
					setValue = L"0";
				}
				else if (newValue == 1)
				{
					setValue = L"2";
				}
				else if (newValue == 2)
				{
					setValue = L"4";
				}
				else if (newValue == 3)
				{
					setValue = L"8";
				}
				else if (newValue == 4)
				{
					setValue = L"16";
				}

				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"AnisoDegree";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = setValue;
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Texture Filtering Quality
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"TFQ";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = number_to_wstring(graphicsSettings.TextureFilteringQuality.Default.value());
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Surface Format Optimization
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"SrfcFrmtRplcmnt";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = number_to_wstring(graphicsSettings.SurfaceFormatOptimization.Default.value());
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Tessellation Mode
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"Tessellation_OP";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = number_to_wstring(graphicsSettings.TessellationMode.Default.value());
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//Tessellation Level
			{
				int newValue = graphicsSettings.TessellationLevel.Default.value();

				//Enumeration index correction
				std::wstring setValue = L"1";
				if (newValue == 0)
				{
					setValue = L"1";
				}
				else if (newValue == 1)
				{
					setValue = L"2";
				}
				else if (newValue == 2)
				{
					setValue = L"4";
				}
				else if (newValue == 3)
				{
					setValue = L"6";
				}
				else if (newValue == 4)
				{
					setValue = L"8";
				}
				else if (newValue == 5)
				{
					setValue = L"16";
				}
				else if (newValue == 6)
				{
					setValue = L"32";
				}
				else if (newValue == 7)
				{
					setValue = L"64";
				}

				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"Tessellation";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = setValue;
				adlAppProperty0.Values = { adlAppPropertyValue0 };
				adlAppProperties.push_back(adlAppProperty0);
			}

			//OpenGL Triple Buffering
			{
				AdlAppProperty adlAppProperty0{};
				adlAppProperty0.Name = L"EnableTrplBffr";
				AdlAppPropertyValue adlAppPropertyValue0{};
				adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
				adlAppPropertyValue0.Value = number_to_wstring(graphicsSettings.OpenGLTripleBuffering.Default.value());
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