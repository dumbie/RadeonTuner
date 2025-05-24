#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::combobox_VerticalRefresh_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Get vertical refresh value
		auto newValue = sender.as<ComboBox>().SelectedIndex();

		//Set vertical refresh setting
		IADLX3DWaitForVerticalRefreshPtr vsync;
		res = d3dSettingSrv->GetWaitForVerticalRefresh(gpuInfo, &vsync);
		res = vsync->SetMode((ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE)newValue);
		if (!ADLX_SUCCEEDED(res))
		{
			//Set result
			textblock_Status().Text(L"Failed setting vertical refresh");
			AVDebugWriteLine(L"Failed setting vertical refresh");
		}
		else
		{
			//Set result
			textblock_Status().Text(L"Vertical refresh set to " + number_to_wstring(newValue));
			AVDebugWriteLine(L"Vertical refresh set to " << newValue);
		}
	}
}