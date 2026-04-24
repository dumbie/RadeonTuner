#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlTuningReset(int gpuAdapterIndex)
	{
		try
		{
			//Reset gpu tuning and fan settings
			if (!Adl_Overdrive_Reset(gpuAdapterIndex))
			{
				//Set result
				ShowNotification(L"Failed resetting tuning and fans settings");
				AVDebugWriteLine(L"Failed resetting tuning and fans settings");
				return false;
			}
			else
			{
				//Set result
				ShowNotification(L"Tuning and fans settings reset");
				AVDebugWriteLine(L"Tuning and fans settings reset");
				return true;
			}
		}
		catch (...)
		{
			//Set result
			ShowNotification(L"Failed resetting tuning and fans settings");
			AVDebugWriteLine(L"Failed resetting tuning and fans settings");
			return false;
		}
	}
}