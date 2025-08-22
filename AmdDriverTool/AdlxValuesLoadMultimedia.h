#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::AdlxValuesLoadMultimedia()
	{
		try
		{
			////Get multimedia video super resolution
			//IADLXVideoSuperResolutionPtr ppVideoSuperResolution;
			//ppMultiMediaServices->GetVideoSuperResolution(ppGpuInfo, &ppVideoSuperResolution);
			//adlx_Res0 = ppVideoSuperResolution->IsSupported(&adlx_Bool);
			//if (adlx_Bool)
			//{
			//	AVDebugWriteLine("Yes ppVideoSuperResolution support.");
			//}
			//else
			//{
			//	AVDebugWriteLine("No ppVideoSuperResolution support.");
			//}

			////Get multimedia video upscale
			//IADLXVideoUpscalePtr ppVideoupscale;
			//ppMultiMediaServices->GetVideoUpscale(ppGpuInfo, &ppVideoupscale);
			//adlx_Res0 = ppVideoupscale->IsSupported(&adlx_Bool);
			//if (adlx_Bool)
			//{
			//	AVDebugWriteLine("Yes ppVideoupscale support.");
			//}
			//else
			//{
			//	AVDebugWriteLine("No ppVideoupscale support.");
			//}

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