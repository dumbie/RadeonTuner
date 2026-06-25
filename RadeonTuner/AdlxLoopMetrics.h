#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AppVariables.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxLoopMetrics()
	{
		while (true)
		{
			try
			{
				//Delay next loop
				Sleep(1000);

				//Check if loop is allowed
				if (AppVariables::ApplicationExiting)
				{
					return;
				}

				//Check if window is visible
				if (!AppVariables::App.GetIsWindowVisible())
				{
					continue;
				}

				//Update tuning metrics
				TuningMetrics_Update();

				//Update graphics status
				GraphicsStatus_Update();
			}
			catch (...) {}
		}
	}
}