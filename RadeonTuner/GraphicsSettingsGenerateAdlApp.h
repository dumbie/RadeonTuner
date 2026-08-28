#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	std::optional<GraphicsSettings> MainPage::GraphicsSettings_Generate_FromADLApp(int gpuAdapterIndex, AdlApplication& adlApplication, bool loadDefault)
	{
		try
		{
			AVDebugWriteLine(L"Generating application graphics settings for: " << adlApplication.ProfileName << L" / " << adlApplication.DriverArea << L" / " << adlApplication.FileName << L" / " << adlApplication.FilePath);
			GraphicsSettings graphicsSettings{};

			//Get graphics settings support
			GraphicsSettings graphicsSettingsSupport = GraphicsSettingsGetSupport(gpuAdapterIndex);

			//Device identifier
			graphicsSettings.DeviceId = AdlxGetGpuIdentifier(gpuAdapterIndex);

			//Device application
			graphicsSettings.Application = adlApplication.FileName;

			//FSR Upscaling Override
			//Note: When using Driver only software type this setting is disabled, Default type it is enabled by default
			try
			{
				//Set support
				graphicsSettings.FsrOverride.Support = graphicsSettingsSupport.FsrOverride.Support;

				//Set default
				graphicsSettings.FsrOverride.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"FsrOverride");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.FsrOverride.Current = convertedValue;
							break;
						}
					}
				}
				else
				{
					//Set current
					graphicsSettings.FsrOverride.Current = graphicsSettings.FsrOverride.Default;
				}
			}
			catch (...) {}

			//FSR Frame Generation Override
			try
			{
				//Set support
				graphicsSettings.MlfiOverride.Support = graphicsSettingsSupport.MlfiOverride.Support;

				//Set default
				graphicsSettings.MlfiOverride.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"MlfiOverride");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.MlfiOverride.Current = convertedValue;
							break;
						}
					}
				}
				else
				{
					//Set current
					graphicsSettings.MlfiOverride.Current = graphicsSettings.MlfiOverride.Default;
				}
			}
			catch (...) {}

			//FSR Multi Frame Generation Override
			try
			{
				//Set support
				graphicsSettings.MfgOverride.Support = graphicsSettingsSupport.MfgOverride.Support;

				//Set default
				graphicsSettings.MfgOverride.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"MfgOverride");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.MfgOverride.Current = convertedValue;
							break;
						}
					}
				}
				else
				{
					//Set current
					graphicsSettings.MfgOverride.Current = graphicsSettings.MfgOverride.Default;
				}
			}
			catch (...) {}

			//FSR Ray Regeneration Denoiser Override
			try
			{
				//Set support
				graphicsSettings.MldOverride.Support = graphicsSettingsSupport.MldOverride.Support;

				//Set default
				graphicsSettings.MldOverride.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"MldOverride");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.MldOverride.Current = convertedValue;
							break;
						}
					}
				}
				else
				{
					//Set current
					graphicsSettings.MldOverride.Current = graphicsSettings.MldOverride.Default;
				}
			}
			catch (...) {}

			//FSR Neural Radiance Caching Override
			try
			{
				//Set support
				graphicsSettings.NrcOverride.Support = graphicsSettingsSupport.NrcOverride.Support;

				//Set default
				graphicsSettings.NrcOverride.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"NrcOverride");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.NrcOverride.Current = convertedValue;
							break;
						}
					}
				}
				else
				{
					//Set current
					graphicsSettings.NrcOverride.Current = graphicsSettings.NrcOverride.Default;
				}
			}
			catch (...) {}

			//FSR Multi Frame Generation Ratio
			try
			{
				//Set support
				graphicsSettings.MfgRatio.Support = graphicsSettingsSupport.MfgRatio.Support;

				//Set default
				graphicsSettings.MfgRatio.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"MfgRatio");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);

							//Enumeration index correction
							if (convertedValue == 0)
							{
								graphicsSettings.MfgRatio.Current = 0;
							}
							else if (convertedValue == 2)
							{
								graphicsSettings.MfgRatio.Current = 1;
							}
							else if (convertedValue == 3)
							{
								graphicsSettings.MfgRatio.Current = 2;
							}
							else if (convertedValue == 4)
							{
								graphicsSettings.MfgRatio.Current = 3;
							}
							break;
						}
					}
				}
				else
				{
					//Set current
					graphicsSettings.MfgRatio.Current = graphicsSettings.MfgRatio.Default;
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

			//FSR Show Information
			{
				//Not supported
			}

			//FSR Latency Reduction
			try
			{
				//Set support
				graphicsSettings.DeLagEnabled.Support = graphicsSettingsSupport.DeLagEnabled.Support;

				//Set default
				graphicsSettings.DeLagEnabled.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"Dlg_PFEnable");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.DeLagEnabled.Current = convertedValue;
							break;
						}
					}
				}
				else
				{
					//Set current
					graphicsSettings.DeLagEnabled.Current = graphicsSettings.DeLagEnabled.Default;
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
				graphicsSettings.BoostMode.Support = graphicsSettingsSupport.BoostMode.Support;

				//Set default
				graphicsSettings.BoostMode.Default = 0;

				std::optional<AdlAppProperty> boostNormalProperty = AdlAppPropertyGet(adlApplication, L"Bst_PFEnable");
				std::optional<AdlAppProperty> boostAdaptiveProperty = AdlAppPropertyGet(adlApplication, L"Bst_AdaPFEnable");
				if (boostNormalProperty.has_value() && boostAdaptiveProperty.has_value())
				{
					//Set current
					int boostNormalValue = 0;
					for (AdlAppPropertyValue value : boostNormalProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							boostNormalValue = wstring_to_int(value.Value);
							break;
						}
					}

					int boostAdaptiveValue = 0;
					for (AdlAppPropertyValue value : boostAdaptiveProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							boostAdaptiveValue = wstring_to_int(value.Value);
							break;
						}
					}

					//Enumeration index correction
					if (boostNormalValue == 0 && boostAdaptiveValue == 0)
					{
						//Disabled
						graphicsSettings.BoostMode.Current = 0;
					}
					else if (boostNormalValue == 1 && boostAdaptiveValue == 0)
					{
						//Input-Based
						graphicsSettings.BoostMode.Current = 1;
					}
					else if (boostNormalValue == 0 && boostAdaptiveValue == 1)
					{
						//Scene-Based
						graphicsSettings.BoostMode.Current = 2;
					}
					else if (boostNormalValue == 1 && boostAdaptiveValue == 1)
					{
						//Multi-Modal
						graphicsSettings.BoostMode.Current = 3;
					}
				}
				else
				{
					//Set current
					graphicsSettings.BoostMode.Current = graphicsSettings.BoostMode.Default;
				}
			}
			catch (...) {}

			//Radeon Boost Minimum Resolution
			try
			{
				//Set support
				graphicsSettings.BoostMinResolution.Support = graphicsSettingsSupport.BoostMinResolution.Support;

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
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);
							graphicsSettings.BoostMinResolution.Current = convertedValue;
							break;
						}
					}
				}
				else
				{
					//Set current
					graphicsSettings.BoostMinResolution.Current = graphicsSettings.BoostMinResolution.Default;
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
				graphicsSettings.ChillEnabled.Support = graphicsSettingsSupport.ChillEnabled.Support;

				//Set default
				graphicsSettings.ChillEnabled.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"Chil_PFEnable");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.ChillEnabled.Current = convertedValue;
							break;
						}
					}
				}
				else
				{
					//Set current
					graphicsSettings.ChillEnabled.Current = graphicsSettings.ChillEnabled.Default;
				}
			}
			catch (...) {}

			//Radeon Chill Minimum Frame Rate
			try
			{
				//Set support
				graphicsSettings.ChillMinFps.Support = graphicsSettingsSupport.ChillMinFps.Support;

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
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);
							graphicsSettings.ChillMinFps.Current = convertedValue;
							break;
						}
					}
				}
				else
				{
					//Set current
					graphicsSettings.ChillMinFps.Current = graphicsSettings.ChillMinFps.Default;
				}
			}
			catch (...) {}

			//Radeon Chill Maximum Frame Rate
			try
			{
				//Set support
				graphicsSettings.ChillMaxFps.Support = graphicsSettingsSupport.ChillMaxFps.Support;

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
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);
							graphicsSettings.ChillMaxFps.Current = convertedValue;
							break;
						}
					}
				}
				else
				{
					//Set current
					graphicsSettings.ChillMaxFps.Current = graphicsSettings.ChillMaxFps.Default;
				}
			}
			catch (...) {}

			//Radeon Image Sharpening - Enabled
			try
			{
				//Set version
				graphicsSettings.RisVersion.Version = graphicsSettingsSupport.RisVersion.Version;

				//Set support
				graphicsSettings.RisEnabled.Support = graphicsSettingsSupport.RisEnabled.Support;

				//Set default
				graphicsSettings.RisEnabled.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"Ris_PFEnable");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.RisEnabled.Current = convertedValue;
							break;
						}
					}
				}
				else
				{
					//Set current
					graphicsSettings.RisEnabled.Current = graphicsSettings.RisEnabled.Default;
				}
			}
			catch (...) {}

			//Radeon Image Sharpening - Desktop
			{
				//Not supported
			}

			//Radeon Image Sharpening - Sharpness
			try
			{
				//Set support
				graphicsSettings.RisSharpeningDegree.Support = graphicsSettingsSupport.RisSharpeningDegree.Support;

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
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							float convertedValue = wstring_to_float(value.Value) * 100;
							graphicsSettings.RisSharpeningDegree.Current = convertedValue;
							break;
						}
					}
				}
				else
				{
					//Set current
					graphicsSettings.RisSharpeningDegree.Current = graphicsSettings.RisSharpeningDegree.Default;
				}
			}
			catch (...) {}

			//Enhanced Sync
			try
			{
				//Set support
				graphicsSettings.EnhancedSync.Support = graphicsSettingsSupport.EnhancedSync.Support;

				//Set default
				graphicsSettings.EnhancedSync.Default = 0;

				toggleswitch_RadeonEnhancedSync().IsEnabled(true);
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"TurboSync");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.EnhancedSync.Current = convertedValue;
							break;
						}
					}
				}
				else
				{
					//Set current
					graphicsSettings.EnhancedSync.Current = graphicsSettings.EnhancedSync.Default;
				}
			}
			catch (...) {}

			//Vertical Sync
			try
			{
				//Set support
				graphicsSettings.VerticalSync.Support = graphicsSettingsSupport.VerticalSync.Support;

				//Set default
				graphicsSettings.VerticalSync.Default = 1;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"VSyncControl");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);
							graphicsSettings.VerticalSync.Current = convertedValue;
							break;
						}
					}
				}
				else
				{
					//Set current
					graphicsSettings.VerticalSync.Current = graphicsSettings.VerticalSync.Default;
				}
			}
			catch (...) {}

			//Anti-Aliasing Override
			try
			{
				//Set support
				graphicsSettings.AntiAliasingOverride.Support = graphicsSettingsSupport.AntiAliasingOverride.Support;

				//Set default
				graphicsSettings.AntiAliasingOverride.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"AntiAlias");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							bool convertedValue = value.Value == L"2";
							graphicsSettings.AntiAliasingOverride.Current = convertedValue;
							break;
						}
					}
				}
				else
				{
					//Set current
					graphicsSettings.AntiAliasingOverride.Current = graphicsSettings.AntiAliasingOverride.Default;
				}
			}
			catch (...) {}

			//Anti-Aliasing Method
			try
			{
				//Set support
				graphicsSettings.AntiAliasingMethod.Support = graphicsSettingsSupport.AntiAliasingMethod.Support;

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
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							asdValue = wstring_to_int(value.Value);
							break;
						}
					}

					int aseValue = 0;
					for (AdlAppPropertyValue value : adlPropertyASE.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							aseValue = wstring_to_int(value.Value);
							break;
						}
					}

					int asttValue = 0;
					for (AdlAppPropertyValue value : adlPropertyASTT.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
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
				else
				{
					//Set current
					graphicsSettings.AntiAliasingMethod.Current = graphicsSettings.AntiAliasingMethod.Default;
				}
			}
			catch (...) {}

			//Anti-Aliasing Level
			try
			{
				//Set support
				graphicsSettings.AntiAliasingLevel.Support = graphicsSettingsSupport.AntiAliasingLevel.Support;

				//Set default
				graphicsSettings.AntiAliasingLevel.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"AntiAliasSmpls");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
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
				else
				{
					//Set current
					graphicsSettings.AntiAliasingLevel.Current = graphicsSettings.AntiAliasingLevel.Default;
				}
			}
			catch (...) {}

			//Enhanced Quality Anti-Aliasing
			try
			{
				//Set support
				graphicsSettings.AntiAliasingEnhancedQuality.Support = graphicsSettingsSupport.AntiAliasingEnhancedQuality.Support;

				//Set default
				graphicsSettings.AntiAliasingEnhancedQuality.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"EQAA");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.AntiAliasingEnhancedQuality.Current = convertedValue;
							break;
						}
					}
				}
				else
				{
					//Set current
					graphicsSettings.AntiAliasingEnhancedQuality.Current = graphicsSettings.AntiAliasingEnhancedQuality.Default;
				}
			}
			catch (...) {}

			//Morphological Anti-Aliasing
			try
			{
				//Set support
				graphicsSettings.AntiAliasingMorphological.Support = graphicsSettingsSupport.AntiAliasingMorphological.Support;

				//Set default
				graphicsSettings.AntiAliasingMorphological.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"MLF");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.AntiAliasingMorphological.Current = convertedValue;
							break;
						}
					}
				}
				else
				{
					//Set current
					graphicsSettings.AntiAliasingMorphological.Current = graphicsSettings.AntiAliasingMorphological.Default;
				}
			}
			catch (...) {}

			//Anisotropic Texture Filtering Override
			try
			{
				//Set support
				graphicsSettings.AnisotropicOverride.Support = graphicsSettingsSupport.AnisotropicOverride.Support;

				//Set default
				graphicsSettings.AnisotropicOverride.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"AnisoDegree");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
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
				else
				{
					//Set current
					graphicsSettings.AnisotropicOverride.Current = graphicsSettings.AnisotropicOverride.Default;
				}
			}
			catch (...) {}

			//Texture Filtering Quality
			try
			{
				//Set support
				graphicsSettings.TextureFilteringQuality.Support = graphicsSettingsSupport.TextureFilteringQuality.Support;

				//Set default
				graphicsSettings.TextureFilteringQuality.Default = 1;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"TFQ");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);
							graphicsSettings.TextureFilteringQuality.Current = convertedValue;
							break;
						}
					}
				}
				else
				{
					//Set current
					graphicsSettings.TextureFilteringQuality.Current = graphicsSettings.TextureFilteringQuality.Default;
				}
			}
			catch (...) {}

			//Surface Format Optimization
			try
			{
				//Set support
				graphicsSettings.SurfaceFormatOptimization.Support = graphicsSettingsSupport.SurfaceFormatOptimization.Support;

				//Set default
				graphicsSettings.SurfaceFormatOptimization.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"SrfcFrmtRplcmnt");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.SurfaceFormatOptimization.Current = convertedValue;
							break;
						}
					}
				}
				else
				{
					//Set current
					graphicsSettings.SurfaceFormatOptimization.Current = graphicsSettings.SurfaceFormatOptimization.Default;
				}
			}
			catch (...) {}

			//Tessellation Mode
			try
			{
				//Set support
				graphicsSettings.TessellationMode.Support = graphicsSettingsSupport.TessellationMode.Support;

				//Set default
				graphicsSettings.TessellationMode.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"Tessellation_OP");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);
							graphicsSettings.TessellationMode.Current = convertedValue;
							break;
						}
					}
				}
				else
				{
					//Set current
					graphicsSettings.TessellationMode.Current = graphicsSettings.TessellationMode.Default;
				}
			}
			catch (...) {}

			//Tessellation Level
			try
			{
				//Set support
				graphicsSettings.TessellationLevel.Support = graphicsSettingsSupport.TessellationLevel.Support;

				//Set default
				graphicsSettings.TessellationLevel.Default = 7;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"Tessellation");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
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
				else
				{
					//Set current
					graphicsSettings.TessellationLevel.Current = graphicsSettings.TessellationLevel.Default;
				}
			}
			catch (...) {}

			//OpenGL Triple Buffering
			try
			{
				//Set support
				graphicsSettings.OpenGLTripleBuffering.Support = graphicsSettingsSupport.OpenGLTripleBuffering.Support;

				//Set default
				graphicsSettings.OpenGLTripleBuffering.Default = 0;

				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adlApplication, L"EnableTrplBffr");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == adl_Gpu_UniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							graphicsSettings.OpenGLTripleBuffering.Current = convertedValue;
							break;
						}
					}
				}
				else
				{
					//Set current
					graphicsSettings.OpenGLTripleBuffering.Current = graphicsSettings.OpenGLTripleBuffering.Default;
				}
			}
			catch (...) {}

			//OpenGL 10-Bit Pixel Format
			{
				//Not supported
			}

			//Set current value to default value
			if (loadDefault)
			{
				graphicsSettings.SetCurrentToDefault();
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