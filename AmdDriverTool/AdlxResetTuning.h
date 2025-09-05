#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	bool MainPage::AdlxResetTuning()
	{
		try
		{
			//Reset gpu tuning and fan settings
			adlx_Res0 = ppGPUTuningServices->ResetToFactory(ppGpuInfo);
			if (ADLX_FAILED(adlx_Res0))
			{
				//Set result
				textblock_Status().Text(L"Tuning and fans reset failed");
				AVDebugWriteLine(L"Tuning and fans reset failed");
				return false;
			}
			else
			{
				//Set result
				textblock_Status().Text(L"Tuning and fans reset");
				AVDebugWriteLine(L"Tuning and fans reset");
				return true;
			}
		}
		catch (...)
		{
			//Set result
			textblock_Status().Text(L"Tuning and fans reset exception");
			AVDebugWriteLine(L"Tuning and fans reset exception");
			return false;
		}
	}
}