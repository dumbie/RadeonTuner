#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	//Fix check if AFMF is active and update status
	//Note: Adrenalin Software Boost, Delag, RIS and Chill overlay status when running a game is not the actual active state it just shows if the setting is Enabled or Disabled.
	//Note: Applications that are currently hooked by driver can be found at Computer\HKEY_CURRENT_USER\Software\AMD\HKIDs
	//Note: amdihk64.dll NotifyFidelityFXStatus NotifyFidelityFXGameVersion

	std::vector<GraphicsStatus> MainPage::GraphicsStatus_Get()
	{
		std::vector<GraphicsStatus> graphicsStatusList{};
		try
		{
			//Get hook status from registry
			auto regValuesHKID = RegistryGetValuesAll(HKEY_ENUM::CURRENT_USER, L"Software\\AMD\\HKIDs");
			for (RegValue regValue : regValuesHKID)
			{
				//Extract process id and name
				std::wstring valueName = regValue.Name.value();
				auto valueNameSplit = wstring_split(valueName, L'*');
				int processId = whexstring_to_int(valueNameSplit[0]);
				std::wstring processName = std::wstring(valueNameSplit[1]);

				//Check if process is running
				AVProcess avProcess = AVProcess(processId);
				if (!avProcess.Running())
				{
					//AVDebugWriteLine("Hooked process not running: " << processId << " / " << processName);
					continue;
				}

				//Create graphics status
				GraphicsStatus graphicsStatus{};
				graphicsStatus.ProcessId = processId;
				graphicsStatus.ProcessName = processName;

				//Set regex string
				std::wstring regexString = regValue.DataString.value();

				////Render api
				//{
				//	std::wsmatch regexMatch;
				//	std::wregex regexPattern(L"api\\?(.*?)\\*");
				//	if (std::regex_search(regexString, regexMatch, regexPattern))
				//	{
				//		graphicsStatus.RenderApi = regexMatch[1].str();
				//	}
				//}

				//FSR Override Upscaling
				//Note: Upscale only works when fsr3_upscale_ver is atleast v1.0.0.36329
				{
					std::wsmatch regexMatch;
					std::wregex regexPattern(L"fsr4_upscale\\?(.*?)\\*");
					if (std::regex_search(regexString, regexMatch, regexPattern))
					{
						std::wstring matchString = regexMatch[1].str();
						bool settingActive = !matchString.empty() && wstring_starts_with(matchString, L"1_");
						if (settingActive)
						{
							graphicsStatus.FsrOverrideUpscaling = true;
						}
					}
				}

				//FSR Override Frame Generation
				//Note: MLFI only works when fsr3_upscale_ver is atleast v1.0.1.41314
				{
					std::wsmatch regexMatch;
					std::wregex regexPattern(L"fsr4_mlfi\\?(.*?)\\*");
					if (std::regex_search(regexString, regexMatch, regexPattern))
					{
						std::wstring matchString = regexMatch[1].str();
						bool settingActive = !matchString.empty() && wstring_starts_with(matchString, L"1_");
						if (settingActive)
						{
							graphicsStatus.FsrOverrideFrameGeneration = true;
						}
					}
				}

				//FSR Override Multi Frame Generation
				{
					std::wsmatch regexMatch;
					std::wregex regexPattern(L"fsr4_mfg\\?(.*?)\\*");
					if (std::regex_search(regexString, regexMatch, regexPattern))
					{
						std::wstring matchString = regexMatch[1].str();
						bool settingActive = !matchString.empty() && wstring_starts_with(matchString, L"1_");
						if (settingActive)
						{
							graphicsStatus.FsrOverrideMultiFrameGeneration = true;
						}
					}
				}

				//FSR Override Ray Regeneration Denoiser
				{
					std::wsmatch regexMatch;
					std::wregex regexPattern(L"fsr4_mld\\?(.*?)\\*");
					if (std::regex_search(regexString, regexMatch, regexPattern))
					{
						std::wstring matchString = regexMatch[1].str();
						bool settingActive = !matchString.empty() && wstring_starts_with(matchString, L"1_");
						if (settingActive)
						{
							graphicsStatus.FsrOverrideRayRegenerationDenoiser = true;
						}
					}
				}

				//FSR Override Neural Radiance Caching
				{
					std::wsmatch regexMatch;
					std::wregex regexPattern(L"fsr4_nrc\\?(.*?)\\*");
					if (std::regex_search(regexString, regexMatch, regexPattern))
					{
						std::wstring matchString = regexMatch[1].str();
						bool settingActive = !matchString.empty() && wstring_starts_with(matchString, L"1_");
						if (settingActive)
						{
							graphicsStatus.FsrOverrideNeuralRadianceCaching = true;
						}
					}
				}

				//Fluid Motion Frames
				//Fix check frame generation lag > 0ms and check if render api process uses is supported
				//ADL2_Adapter_FrameMetrics_Get

				//FSR Latency Reduction
				//Fix Check all process threads if latency reduction is hooked and active
				//32bit DX11 amdxx32.dll!AmdD3D11CreateDeviceAndSwapChainExt with realtime priority

				//Radeon Chill
				//Fix Check all process threads if chill is hooked and active

				//Radeon Boost
				//Fix Check all process threads if boost is hooked and active

				//Add process to status list
				graphicsStatusList.push_back(graphicsStatus);
			}
		}
		catch (...) {}
		return graphicsStatusList;
	}

	void MainPage::GraphicsStatus_Update()
	{
		try
		{
			//Get current status
			std::vector<GraphicsStatus> graphicsStatusList = GraphicsStatus_Get();

			//Update current status
			std::function<void()> updateFunction = [=]
				{
					//FSR Override Upscaling
					{
						auto filteredList = graphicsStatusList | std::views::filter([](const GraphicsStatus& x) { return x.FsrOverrideUpscaling; });
						bool filteredAny = std::ranges::begin(filteredList) != std::ranges::end(filteredList);
						if (filteredAny)
						{
							image_FsrOverrideUpscaling_Status().Visibility(Visibility::Visible);

							std::wstring tooltipStringNew = L"This setting is active on:";
							for (GraphicsStatus graphicsStatus : filteredList)
							{
								tooltipStringNew += L"\n(" + number_to_wstring(graphicsStatus.ProcessId) + L") " + graphicsStatus.ProcessName;
							}

							//Set updated tooltip text
							wstring_to_tooltip(image_FsrOverrideUpscaling_Status(), tooltipStringNew);
						}
						else
						{
							image_FsrOverrideUpscaling_Status().Visibility(Visibility::Collapsed);
						}
					}

					//FSR Override Frame Generation
					{
						auto filteredList = graphicsStatusList | std::views::filter([](const GraphicsStatus& x) { return x.FsrOverrideFrameGeneration; });
						bool filteredAny = std::ranges::begin(filteredList) != std::ranges::end(filteredList);
						if (filteredAny)
						{
							image_FsrOverrideFrameGeneration_Status().Visibility(Visibility::Visible);

							std::wstring tooltipStringNew = L"This setting is active on:";
							for (GraphicsStatus graphicsStatus : filteredList)
							{
								tooltipStringNew += L"\n(" + number_to_wstring(graphicsStatus.ProcessId) + L") " + graphicsStatus.ProcessName;
							}

							//Set updated tooltip text
							wstring_to_tooltip(image_FsrOverrideFrameGeneration_Status(), tooltipStringNew);
						}
						else
						{
							image_FsrOverrideFrameGeneration_Status().Visibility(Visibility::Collapsed);
						}
					}

					//FSR Override Multi Frame Generation
					{
						auto filteredList = graphicsStatusList | std::views::filter([](const GraphicsStatus& x) { return x.FsrOverrideMultiFrameGeneration; });
						bool filteredAny = std::ranges::begin(filteredList) != std::ranges::end(filteredList);
						if (filteredAny)
						{
							image_FsrOverrideMultiFrameGeneration_Status().Visibility(Visibility::Visible);

							std::wstring tooltipStringNew = L"This setting is active on:";
							for (GraphicsStatus graphicsStatus : filteredList)
							{
								tooltipStringNew += L"\n(" + number_to_wstring(graphicsStatus.ProcessId) + L") " + graphicsStatus.ProcessName;
							}

							//Set updated tooltip text
							wstring_to_tooltip(image_FsrOverrideMultiFrameGeneration_Status(), tooltipStringNew);
						}
						else
						{
							image_FsrOverrideMultiFrameGeneration_Status().Visibility(Visibility::Collapsed);
						}
					}

					//FSR Override Ray Regeneration Denoiser
					{
						auto filteredList = graphicsStatusList | std::views::filter([](const GraphicsStatus& x) { return x.FsrOverrideRayRegenerationDenoiser; });
						bool filteredAny = std::ranges::begin(filteredList) != std::ranges::end(filteredList);
						if (filteredAny)
						{
							image_FsrOverrideRayRegeneration_Status().Visibility(Visibility::Visible);

							std::wstring tooltipStringNew = L"This setting is active on:";
							for (GraphicsStatus graphicsStatus : filteredList)
							{
								tooltipStringNew += L"\n(" + number_to_wstring(graphicsStatus.ProcessId) + L") " + graphicsStatus.ProcessName;
							}

							//Set updated tooltip text
							wstring_to_tooltip(image_FsrOverrideRayRegeneration_Status(), tooltipStringNew);
						}
						else
						{
							image_FsrOverrideRayRegeneration_Status().Visibility(Visibility::Collapsed);
						}
					}

					//FSR Override Neural Radiance Caching
					{
						auto filteredList = graphicsStatusList | std::views::filter([](const GraphicsStatus& x) { return x.FsrOverrideNeuralRadianceCaching; });
						bool filteredAny = std::ranges::begin(filteredList) != std::ranges::end(filteredList);
						if (filteredAny)
						{
							image_FsrOverrideNeuralRadianceCaching_Status().Visibility(Visibility::Visible);

							std::wstring tooltipStringNew = L"This setting is active on:";
							for (GraphicsStatus graphicsStatus : filteredList)
							{
								tooltipStringNew += L"\n(" + number_to_wstring(graphicsStatus.ProcessId) + L") " + graphicsStatus.ProcessName;
							}

							//Set updated tooltip text
							wstring_to_tooltip(image_FsrOverrideNeuralRadianceCaching_Status(), tooltipStringNew);
						}
						else
						{
							image_FsrOverrideNeuralRadianceCaching_Status().Visibility(Visibility::Collapsed);
						}
					}

					//image_FrameGenEnabled_Status
					//image_FsrLatencyReduction_Status
					//image_RadeonChill_Status
					//image_RadeonBoost_Status
					//image_RadeonImageSharpening1_Status
					//image_RadeonImageSharpening2_Status
				};
			AppVariables::App.DispatcherInvoke(updateFunction);
		}
		catch (...) {}
	}
}