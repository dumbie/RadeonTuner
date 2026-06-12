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
			//Remove global user application
			AdlApplication globalApp{};
			globalApp.FileName = L"*.*";
			globalApp.FilePath = L"*\\*";
			AdlAppRemove(globalApp);

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