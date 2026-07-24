#pragma once
#include "pch.h"

namespace LauncherSteam::Functions
{
	inline std::wstring SteamInstallPath()
	{
		try
		{
			std::wstring registryPathW = L"Software\\Valve\\Steam";
			std::wstring registryValueW = L"InstallPath";
			return RegistryGetString(HKEY_ENUM::LOCAL_MACHINE, registryPathW, registryValueW);
		}
		catch (...) {}
		return L"";
	}
}