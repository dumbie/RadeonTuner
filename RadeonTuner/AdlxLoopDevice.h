#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AppVariables.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	//Note: ADL throws EXCEPTION_ACCESS_VIOLATION when you no longer have access but can't catch this in ADLX because ADLX keeps returning invalid values instead of returning errors.
	//Fix reinitialize ADLX automatically so a restart is not needed.

	void MainPage::AdlxLoopDevice()
	{
		while (true)
		{
			try
			{
				//Delay next update
				Sleep(2000);

				//Check if loop is allowed
				if (AppVariables::ApplicationExiting)
				{
					return;
				}

				//Check if we have access to video card
				bool hasAccess = true;
				try
				{
					int lpAccess;
					adl_Res0 = _ADL2_Adapter_Accessibility_Get(adl_Context, adl_AdapterIndex, &lpAccess);
					hasAccess = adl_Res0 == ADL_OK;
				}
				catch (...)
				{
					hasAccess = false;
				}

				//Disable interface when access is lost
				if (!hasAccess)
				{
					std::function<void()> updateFunction = [&]
						{
							grid_Main().IsHitTestVisible(false);
							grid_Overlay().Visibility(Visibility::Visible);
							textblock_Overlay_Text().Text(L"Access to video card has been lost, please restart RadeonTuner.");
							textblock_Overlay_Sub_Text().Text(L"This could have been caused by a driver update or failure.");
						};
					AppVariables::App.DispatcherInvoke(updateFunction);
					return;
				}
			}
			catch (...) {}
		}
	}
}