#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::FsrShowInformationIsEnabled()
	{
		try
		{
			//Get setting value from registry
			std::wstring resultString = RegistryGetString(HKEY_ENUM::CURRENT_USER, L"Environment", L"MLSR-WATERMARK");
			AVDebugWriteLine(L"FSR show information status: " << resultString);

			//Return result
			return resultString == L"1" || wstring_to_lower(resultString) == L"true";
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	bool MainPage::FsrShowInformationToggle(bool enabled)
	{
		try
		{
			//Toggle FSR watermark environment variables
			if (enabled)
			{
				RegistrySet(HKEY_ENUM::CURRENT_USER, L"Environment", L"MLSR-WATERMARK", L"TRUE");
				RegistrySet(HKEY_ENUM::CURRENT_USER, L"Environment", L"MLFI-WATERMARK", L"TRUE");
			}
			else
			{
				RegistryDelete(HKEY_ENUM::CURRENT_USER, L"Environment", L"MLSR-WATERMARK");
				RegistryDelete(HKEY_ENUM::CURRENT_USER, L"Environment", L"MLFI-WATERMARK");
			}

			//Signal environment variables change
			SendMessageTimeoutW(HWND_BROADCAST, WM_SETTINGCHANGE, NULL, (LPARAM)L"Environment", SMTO_ABORTIFHUNG, 2000, NULL);

			//Return result
			AVDebugWriteLine(L"Toggled FSR information status: " << enabled);
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine(L"Failed to toggle FSR information status (Exception)");
			return false;
		}
	}
}