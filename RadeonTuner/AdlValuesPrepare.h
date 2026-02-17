#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlValuesPrepare()
	{
		try
		{
			//Add global user application
			AdlAppAdd(L"*.*", L"3D_User");

			//Load and list applications
			AdlAppInterfaceListLoad();

			//Set result
			AVDebugWriteLine("ADL prepared.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADL preparation failed.");
		}
	}
}