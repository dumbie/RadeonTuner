#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlxResetShaderCache()
	{
		try
		{
			//Fix remove Steam shader cache (HKEY_CURRENT_USER\Software\Valve\Steam\SteamPath)
			//Fix this method does not delete inuse shader files, Adrenalin Software has the same issue. *1
			//*1 Temporarily Disable GPU > Delete Cached Shaders > Enable GPU as workaround? 

			//Get shader cache locations
			std::wstring folderPathAppData = PathGetFolderKnown(FOLDERID_LocalAppData);
			std::wstring folderPathAppDataLow = PathGetFolderKnown(FOLDERID_LocalAppDataLow);

			std::wstring folderD3DSCache = PathMerge(folderPathAppData, L"D3DSCache");

			std::wstring folderAMDDX9Cache = PathMerge(folderPathAppData, L"AMD\\DX9Cache");
			std::wstring folderAMDDxCache = PathMerge(folderPathAppData, L"AMD\\DxCache");
			std::wstring folderAMDDxcCache = PathMerge(folderPathAppData, L"AMD\\DxcCache");
			std::wstring folderAMDOglCache = PathMerge(folderPathAppData, L"AMD\\OglCache");
			std::wstring folderAMDVkCache = PathMerge(folderPathAppData, L"AMD\\VkCache");

			std::wstring folderLowAMDDX9Cache = PathMerge(folderPathAppDataLow, L"AMD\\DX9Cache");
			std::wstring folderLowAMDDxCache = PathMerge(folderPathAppDataLow, L"AMD\\DxCache");
			std::wstring folderLowAMDDxcCache = PathMerge(folderPathAppDataLow, L"AMD\\DxcCache");
			std::wstring folderLowAMDOglCache = PathMerge(folderPathAppDataLow, L"AMD\\OglCache");
			std::wstring folderLowAMDVkCache = PathMerge(folderPathAppDataLow, L"AMD\\VkCache");

			//Delete shader cache locations
			FolderRemove(folderD3DSCache, true);

			FolderRemove(folderAMDDX9Cache, true);
			FolderRemove(folderAMDDxCache, true);
			FolderRemove(folderAMDDxcCache, true);
			FolderRemove(folderAMDOglCache, true);
			FolderRemove(folderAMDVkCache, true);

			FolderRemove(folderLowAMDDX9Cache, true);
			FolderRemove(folderLowAMDDxCache, true);
			FolderRemove(folderLowAMDDxcCache, true);
			FolderRemove(folderLowAMDOglCache, true);
			FolderRemove(folderLowAMDVkCache, true);

			//Return result
			AVDebugWriteLine("Shader cache reset.");
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed resetting shader cache.");
			return false;
		}
	}
}