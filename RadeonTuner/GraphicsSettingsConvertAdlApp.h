#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	std::optional<GraphicsSettings> MainPage::GraphicsSettings_Generate_FromADLApp(AdlApplication& adlApplication)
	{
		try
		{
			//Fix find way to check if setting is supported and disable interface. (ADL2_Adapter_Feature_Caps)

			GraphicsSettings graphicsSettings{};

			//FSR Upscaling Override
			try
			{
				//Set support
				graphicsSettings.FsrOverride.Support = true;

				//Set default
				graphicsSettings.FsrOverride.Default = 1;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"FsrOverride");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.FsrOverride.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//FSR Frame Generation Override
			try
			{
				//Set support
				graphicsSettings.MlfiOverride.Support = true;

				//Set default
				graphicsSettings.MlfiOverride.Default = 1;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"MlfiOverride");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.MlfiOverride.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//FSR Multi Frame Generation Override
			try
			{
				//Set support
				graphicsSettings.MfgOverride.Support = true;

				//Set default
				graphicsSettings.MfgOverride.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"MfgOverride");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.MfgOverride.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//FSR Ray Regeneration Denoiser Override
			try
			{
				//Set support
				graphicsSettings.MldOverride.Support = true;

				//Set default
				graphicsSettings.MldOverride.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"MldOverride");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.MldOverride.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//FSR Neural Radiance Caching Override
			try
			{
				//Set support
				graphicsSettings.NrcOverride.Support = true;

				//Set default
				graphicsSettings.NrcOverride.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"NrcOverride");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.NrcOverride.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//FSR Multi Frame Generation Ratio
			try
			{
				//Set support
				graphicsSettings.MfgRatio.Support = true;

				//Set default
				graphicsSettings.MfgRatio.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"MfgRatio");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);
							graphicsSettings.MfgRatio.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//FSR Override Library
			{
				//Not supported
			}

			//FSR Over-The-Air Updates
			{
				//Not supported
			}

			//FSR Latency Reduction
			try
			{
				//Set support
				graphicsSettings.DeLagEnabled.Support = true;

				//Set default
				graphicsSettings.DeLagEnabled.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"Dlg_PFEnable");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.DeLagEnabled.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//Radeon Fluid Motion Frames
			{
				//Not supported
			}

			//Radeon Boost
			try
			{
				//Set support
				graphicsSettings.BoostEnabled.Support = true;

				//Set default
				graphicsSettings.BoostEnabled.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"Bst_PFEnable");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.BoostEnabled.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//Radeon Boost Minimum Resolution
			try
			{
				//Set support
				graphicsSettings.BoostMinResolution.Support = true;

				//Set default
				graphicsSettings.BoostMinResolution.Default = 84;

				//Set interface
				graphicsSettings.BoostMinResolution.Minimum = 50;
				graphicsSettings.BoostMinResolution.Maximum = 84;
				graphicsSettings.BoostMinResolution.Step = 17;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"Bst_MaxScale");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);
							graphicsSettings.BoostMinResolution.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//Radeon Frame Rate Target Control
			{
				//Not supported
			}

			//Radeon Chill
			try
			{
				//Set support
				graphicsSettings.ChillEnabled.Support = true;

				//Set default
				graphicsSettings.ChillEnabled.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"Chil_PFEnable");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.ChillEnabled.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//Radeon Chill Minimum Frame Rate
			try
			{
				//Set support
				graphicsSettings.ChillMinFps.Support = true;

				//Set default
				graphicsSettings.ChillMinFps.Default = 75;

				//Set interface
				graphicsSettings.ChillMinFps.Minimum = 30;
				graphicsSettings.ChillMinFps.Maximum = 300;
				graphicsSettings.ChillMinFps.Step = 1;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"Chil_MinFRate");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);
							graphicsSettings.ChillMinFps.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//Radeon Chill Maximum Frame Rate
			try
			{
				//Set support
				graphicsSettings.ChillMaxFps.Support = true;

				//Set default
				graphicsSettings.ChillMaxFps.Default = 140;

				//Set interface
				graphicsSettings.ChillMaxFps.Minimum = 30;
				graphicsSettings.ChillMaxFps.Maximum = 300;
				graphicsSettings.ChillMaxFps.Step = 1;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"Chil_MaxFRate");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);
							graphicsSettings.ChillMaxFps.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//Radeon Image Sharpening 1
			try
			{
				//Set support
				graphicsSettings.RisEnabled.Support = true;

				//Set default
				graphicsSettings.RisEnabled.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"Ris_PFEnable");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.RisEnabled.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//Radeon Image Sharpening 1 Sharpness
			try
			{
				//Set support
				graphicsSettings.RisSharpeningDegree.Support = true;

				//Set default
				graphicsSettings.RisSharpeningDegree.Default = 80;

				//Set interface
				graphicsSettings.RisSharpeningDegree.Minimum = 10;
				graphicsSettings.RisSharpeningDegree.Maximum = 100;
				graphicsSettings.RisSharpeningDegree.Step = 10;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"Ris_SHDegree");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							float convertedValue = wstring_to_float(value.Value) * 100;
							graphicsSettings.RisSharpeningDegree.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//Radeon Image Sharpening 2
			{
				//Not supported
			}

			//Enhanced Sync
			try
			{
				//Set support
				graphicsSettings.EnhancedSync.Support = true;

				//Set default
				graphicsSettings.EnhancedSync.Default = 0;

				toggleswitch_RadeonEnhancedSync().IsEnabled(true);
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"TurboSync");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.EnhancedSync.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//Vertical Sync
			try
			{
				//Set support
				graphicsSettings.VerticalSync.Support = true;

				//Set default
				graphicsSettings.VerticalSync.Default = 1;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"VSyncControl");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);
							graphicsSettings.VerticalSync.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//Anti-Aliasing Override
			try
			{
				//Set support
				graphicsSettings.AntiAliasingOverride.Support = true;

				//Set default
				graphicsSettings.AntiAliasingOverride.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"AntiAlias");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = value.Value == L"2";
							graphicsSettings.AntiAliasingOverride.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//Anti-Aliasing Method
			try
			{
				//Set support
				graphicsSettings.AntiAliasingMethod.Support = true;

				//Set default
				graphicsSettings.AntiAliasingMethod.Default = 0;

				std::optional<AdlAppProperty> adlPropertyASD = AdlAppPropertyGet(adlApplication, L"ASD");
				std::optional<AdlAppProperty> adlPropertyASE = AdlAppPropertyGet(adlApplication, L"ASE");
				std::optional<AdlAppProperty> adlPropertyASTT = AdlAppPropertyGet(adlApplication, L"ASTT");
				if (adlPropertyASD.has_value() && adlPropertyASE.has_value() && adlPropertyASTT.has_value())
				{
					//Set current
					int asdValue = -1;
					for (AdlAppPropertyValue value : adlPropertyASD.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							asdValue = wstring_to_int(value.Value);
							break;
						}
					}

					int aseValue = 0;
					for (AdlAppPropertyValue value : adlPropertyASE.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							aseValue = wstring_to_int(value.Value);
							break;
						}
					}

					int asttValue = 0;
					for (AdlAppPropertyValue value : adlPropertyASTT.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							asttValue = wstring_to_int(value.Value);
							break;
						}
					}

					//Enumeration index correction
					if (asdValue == -1 && aseValue == 0 && asttValue == 0)
					{
						//Multisampling
						graphicsSettings.AntiAliasingMethod.Current = 0;
					}
					else if (asdValue == 1 && aseValue == 0 && asttValue == 1)
					{
						//Adaptive Multisampling
						graphicsSettings.AntiAliasingMethod.Current = 1;
					}
					else if (asdValue == 1 && aseValue == 1 && asttValue == 1)
					{
						//Supersampling
						graphicsSettings.AntiAliasingMethod.Current = 2;
					}
				}
			}
			catch (...) {}

			//Anti-Aliasing Level
			try
			{
				//Set support
				graphicsSettings.AntiAliasingLevel.Support = true;

				//Set default
				graphicsSettings.AntiAliasingLevel.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"AntiAliasSmpls");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);

							//Enumeration index correction
							if (convertedValue == 2)
							{
								graphicsSettings.AntiAliasingLevel.Current = 0;
							}
							else if (convertedValue == 4)
							{
								graphicsSettings.AntiAliasingLevel.Current = 1;
							}
							else if (convertedValue == 8)
							{
								graphicsSettings.AntiAliasingLevel.Current = 2;
							}
							break;
						}
					}
				}
			}
			catch (...) {}

			//Enhanced Quality Anti-Aliasing
			try
			{
				//Set support
				graphicsSettings.AntiAliasingEnhancedQuality.Support = true;

				//Set default
				graphicsSettings.AntiAliasingEnhancedQuality.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"EQAA");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.AntiAliasingEnhancedQuality.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//Morphological Anti-Aliasing
			try
			{
				//Set support
				graphicsSettings.AntiAliasingMorphological.Support = true;

				//Set default
				graphicsSettings.AntiAliasingMorphological.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"MLF");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.AntiAliasingMorphological.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//Anisotropic Texture Filtering Override
			try
			{
				//Set support
				graphicsSettings.AnisotropicOverride.Support = true;

				//Set default
				graphicsSettings.AnisotropicOverride.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"AnisoDegree");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);

							//Enumeration index correction
							if (convertedValue == 0)
							{
								graphicsSettings.AnisotropicOverride.Current = 0;
							}
							else if (convertedValue == 2)
							{
								graphicsSettings.AnisotropicOverride.Current = 1;
							}
							else if (convertedValue == 4)
							{
								graphicsSettings.AnisotropicOverride.Current = 2;
							}
							else if (convertedValue == 8)
							{
								graphicsSettings.AnisotropicOverride.Current = 3;
							}
							else if (convertedValue == 16)
							{
								graphicsSettings.AnisotropicOverride.Current = 4;
							}
							break;
						}
					}
				}
			}
			catch (...) {}

			//Texture Filtering Quality
			try
			{
				//Set support
				graphicsSettings.TextureFilteringQuality.Support = true;

				//Set default
				graphicsSettings.TextureFilteringQuality.Default = 1;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"TFQ");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);
							graphicsSettings.TextureFilteringQuality.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//Surface Format Optimization
			try
			{
				//Set support
				graphicsSettings.SurfaceFormatOptimization.Support = true;

				//Set default
				graphicsSettings.SurfaceFormatOptimization.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"SrfcFrmtRplcmnt");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.SurfaceFormatOptimization.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//Tessellation Mode
			try
			{
				//Set support
				graphicsSettings.TessellationMode.Support = true;

				//Set default
				graphicsSettings.TessellationMode.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"Tessellation_OP");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);
							graphicsSettings.TessellationMode.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//Tessellation Level
			try
			{
				//Set support
				graphicsSettings.TessellationLevel.Support = true;

				//Set default
				graphicsSettings.TessellationLevel.Default = 7;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"Tessellation");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);

							//Enumeration index correction
							if (convertedValue == 1)
							{
								graphicsSettings.TessellationLevel.Current = 0;
							}
							else if (convertedValue == 2)
							{
								graphicsSettings.TessellationLevel.Current = 1;
							}
							else if (convertedValue == 4)
							{
								graphicsSettings.TessellationLevel.Current = 2;
							}
							else if (convertedValue == 6)
							{
								graphicsSettings.TessellationLevel.Current = 3;
							}
							else if (convertedValue == 8)
							{
								graphicsSettings.TessellationLevel.Current = 4;
							}
							else if (convertedValue == 16)
							{
								graphicsSettings.TessellationLevel.Current = 5;
							}
							else if (convertedValue == 32)
							{
								graphicsSettings.TessellationLevel.Current = 6;
							}
							else if (convertedValue == 64)
							{
								graphicsSettings.TessellationLevel.Current = 7;
							}
							break;
						}
					}
				}
			}
			catch (...) {}

			//OpenGL Triple Buffering
			try
			{
				//Set support
				graphicsSettings.OpenGLTripleBuffering.Support = true;

				//Set default
				graphicsSettings.OpenGLTripleBuffering.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"EnableTrplBffr");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.OpenGLTripleBuffering.Current = convertedValue;
							break;
						}
					}
				}
			}
			catch (...) {}

			//OpenGL 10-Bit Pixel Format
			{
				//Not supported
			}

			//Return result
			return graphicsSettings;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to generate graphics settings from ADL app.");
			return std::nullopt;
		}
	}
}