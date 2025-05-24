#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::AdlxInitialize()
	{
		//Initialize ADLX
		res = g_ADLXHelp.Initialize();
		if (!ADLX_SUCCEEDED(res))
		{
			AVDebugWriteLine("Failed initializing ADLX.");
			return;
		}

		//Get all gpus
		res = g_ADLXHelp.GetSystemServices()->GetGPUs(&gpus);
		if (!ADLX_SUCCEEDED(res))
		{
			AVDebugWriteLine("Failed getting all gpus.");
			return;
		}

		//List all gpus 
		for (UINT i = 0; i < gpus->Size(); i++)
		{
			const char* gpuName;
			gpus->At(i, &gpuInfo);
			gpuInfo->Name(&gpuName);
			combobox_GpuSelect().Items().Append(box_value(char_to_wstring(gpuName)));
		}

		//Get 3DSettings services
		res = g_ADLXHelp.GetSystemServices()->Get3DSettingsServices(&d3dSettingSrv);
		if (!ADLX_SUCCEEDED(res))
		{
			AVDebugWriteLine("Failed getting 3DSettings services.");
			return;
		}

		AVDebugWriteLine("ADLX initialized.");
	}

	void MainPage::AdlxLoadValues()
	{
		//Get selected GPU
		int selectedIndex = combobox_GpuSelect().SelectedIndex();
		res = gpus->At(selectedIndex, &gpuInfo);
		if (!ADLX_SUCCEEDED(res))
		{
			AVDebugWriteLine("Failed getting selected gpu.");
			return;
		}

		//Get chill settings
		IADLX3DChillPtr d3dChill;
		res = d3dSettingSrv->GetChill(gpuInfo, &d3dChill);
		res = d3dChill->IsEnabled(&adxl_Bool);
		res = d3dChill->GetMinFPS(&adxl_Int0);
		res = d3dChill->GetMaxFPS(&adxl_Int1);
		toggleswitch_Chill().IsOn(adxl_Bool);
		textBox_Chill_Min().Text(number_to_hstring(adxl_Int0));
		textBox_Chill_Max().Text(number_to_hstring(adxl_Int1));
		if (!adxl_Bool)
		{
			textBox_Chill_Min().IsEnabled(false);
			textBox_Chill_Max().IsEnabled(false);
		}

		//Get vertical refresh settings
		IADLX3DWaitForVerticalRefreshPtr vsync;
		res = d3dSettingSrv->GetWaitForVerticalRefresh(gpuInfo, &vsync);
		ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE currentMode;
		vsync->GetMode(&currentMode);
		combobox_VerticalRefresh().SelectedIndex(currentMode);

		//Get fan settings
		PointCollection fanPoints;
		fanPoints.Append(Point{ 10, 10 });
		fanPoints.Append(Point{ 20, 20 });
		fanPoints.Append(Point{ 30, 30 });
		fanPoints.Append(Point{ 50, 50 });
		fanPoints.Append(Point{ 60, 60 });
		fanPoints.Append(Point{ 100, 100 });
		polyline_Chart().Points(fanPoints);

		//Set result
		AVDebugWriteLine("ADLX loaded values.");
	}
}