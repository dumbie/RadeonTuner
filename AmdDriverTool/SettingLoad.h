#pragma once
#include "pch.h"
#include "MainPage.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::SettingLoad()
	{
		try
		{
			AVDebugWriteLine("Application settings loaded.");
		}
		catch (...) {}
	}
}