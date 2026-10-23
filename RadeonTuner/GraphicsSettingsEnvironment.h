#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::EnvironmentSettingGet(std::wstring settingName)
	{
		try
		{
			//Get setting value from registry
			std::wstring resultString = RegistryGetString(HKEY_ENUM::CURRENT_USER, L"Environment", settingName);

			//Return result
			return resultString == L"1" || wstring_to_lower(resultString) == L"true";
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	bool MainPage::EnvironmentSettingRemove(std::wstring settingName)
	{
		try
		{
			//Remove setting value from registry
			return RegistryDelete(HKEY_ENUM::CURRENT_USER, L"Environment", settingName);
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	bool MainPage::EnvironmentSettingSet(std::wstring settingName, bool enabled)
	{
		try
		{
			//Toggle environment variables
			if (enabled)
			{
				RegistrySet(HKEY_ENUM::CURRENT_USER, L"Environment", settingName, L"1");
			}
			else
			{
				RegistrySet(HKEY_ENUM::CURRENT_USER, L"Environment", settingName, L"0");
			}

			//Signal environment variables change
			SendMessageTimeoutW(HWND_BROADCAST, WM_SETTINGCHANGE, NULL, (LPARAM)L"Environment", SMTO_ABORTIFHUNG, 2000, NULL);

			//Return result
			AVDebugWriteLine(L"Toggled environment setting: " << settingName << L" / " << enabled);
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine(L"Failed to toggle environment setting (Exception)");
			return false;
		}
	}
}