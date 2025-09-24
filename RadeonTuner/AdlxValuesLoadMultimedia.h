#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesLoadMultimedia()
	{
		try
		{
			//Check services
			if (ppMultiMediaServices == NULL)
			{
				stackpanel_Multimedia().Opacity(0.20);
				stackpanel_Multimedia().IsHitTestVisible(false);
				AVDebugWriteLine("ADLX multimedia service is not available.");
				return;
			}

			//Get multimedia video super resolution
			try
			{
				IADLXVideoSuperResolutionPtr ppVideoSuperResolution;
				ppMultiMediaServices->GetVideoSuperResolution(ppGpuInfo, &ppVideoSuperResolution);
				adlx_Res0 = ppVideoSuperResolution->IsSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = ppVideoSuperResolution->IsEnabled(&adlx_Bool);
					toggleswitch_VideoSuperResolution().IsOn(adlx_Bool);

					//Enable or disable interface
					toggleswitch_VideoSuperResolution().IsEnabled(true);
				}
				else
				{
					//Enable or disable interface
					toggleswitch_VideoSuperResolution().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_VideoSuperResolution().IsEnabled(false);
			}

			//Get multimedia video upscale
			try
			{
				IADLXVideoUpscalePtr ppVideoupscale;
				ppMultiMediaServices->GetVideoUpscale(ppGpuInfo, &ppVideoupscale);
				adlx_Res0 = ppVideoupscale->IsSupported(&adlx_Bool);
				if (adlx_Bool)
				{
					adlx_Res0 = ppVideoupscale->IsEnabled(&adlx_Bool);
					adlx_Res0 = ppVideoupscale->GetSharpness(&adlx_Int0);
					adlx_Res0 = ppVideoupscale->GetSharpnessRange(&adlx_IntRange0);

					toggleswitch_VideoUpscale().IsOn(adlx_Bool);
					slider_VideoUpscale_Sharpening().Value(adlx_Int0);
					slider_VideoUpscale_Sharpening().Minimum(adlx_IntRange0.minValue);
					slider_VideoUpscale_Sharpening().Maximum(adlx_IntRange0.maxValue);
					slider_VideoUpscale_Sharpening().StepFrequency(adlx_IntRange0.step);

					//Enable or disable interface
					toggleswitch_VideoUpscale().IsEnabled(true);
					if (adlx_Bool)
					{
						slider_VideoUpscale_Sharpening().IsEnabled(true);
					}
					else
					{
						slider_VideoUpscale_Sharpening().IsEnabled(false);
					}
				}
				else
				{
					//Enable or disable interface
					toggleswitch_VideoUpscale().IsEnabled(false);
					slider_VideoUpscale_Sharpening().IsEnabled(false);
				}
			}
			catch (...)
			{
				//Enable or disable interface
				toggleswitch_VideoUpscale().IsEnabled(false);
				slider_VideoUpscale_Sharpening().IsEnabled(false);
			}

			//Set result
			AVDebugWriteLine("ADLX loaded multimedia values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading multimedia values.");
		}
	}
}