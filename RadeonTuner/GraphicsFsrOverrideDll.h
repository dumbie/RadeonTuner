#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	//Update FSR dll path text
	void MainPage::FsrOverrideDllUpdateTextPathInfo(std::wstring dllPath)
	{
		try
		{
			//Check if dll path is empty
			if (wstring_empty_whitespace(dllPath))
			{
				dllPath = FsrOverrideDllGetPathDefault();
			}

			//Get system32 path and convert to lower case
			std::wstring dllPathLower = wstring_to_lower(dllPath);
			std::wstring system32pathLower = wstring_to_lower(PathGetFolderKnown(FOLDERID_System));

			//Check and set dll path text
			if (wstring_contains(dllPathLower, system32pathLower))
			{
				textblock_FsrDllLoadPath().Text(L"Using default driver FSR library file.");
			}
			else
			{
				textblock_FsrDllLoadPath().Text(L"Using custom set FSR library file.");
			}
		}
		catch (...)
		{
			//Set dll path text
			textblock_FsrDllLoadPath().Text(L"Using unknown FSR library file.");
		}
	}

	//Update FSR dll version text
	void MainPage::FsrOverrideDllUpdateTextVersion(std::wstring dllPath)
	{
		try
		{
			//Check if dll path is empty
			if (wstring_empty_whitespace(dllPath))
			{
				dllPath = FsrOverrideDllGetPathDefault();
			}

			//Get dll version
			std::string dllVersion = GetVersionFromFile(dllPath);
			std::wstring dllVersionW = string_to_wstring(dllVersion);

			//Get fsr version
			//Fix read FSR version directly from amdxcffx64.dll UpdateFfxApiProviderEx
			std::wstring fsrVersionW = L"";
			if (wstring_empty_whitespace(dllVersionW))
			{
				fsrVersionW = L" FSR ?";
			}
			else if (dllVersionW == L"1.0.0.38222" || dllVersionW == L"1.0.0.38733" || dllVersionW == L"1.0.0.39037")
			{
				fsrVersionW = L" FSR 4.0.0 Preview";
			}
			else if (dllVersionW == L"1.0.0.39849")
			{
				fsrVersionW = L" FSR 4.0.0";
			}
			else if (dllVersionW == L"1.0.0.40394")
			{
				fsrVersionW = L" FSR 4.0.1";
			}
			else if (dllVersionW == L"1.0.2.44374")
			{
				fsrVersionW = L" FSR 4.0.2";
			}
			else if (dllVersionW == L"2.1.0.551")
			{
				fsrVersionW = L" FSR 4.0.3";
			}
			else if (dllVersionW == L"2.1.0.968" || dllVersionW == L"2.2.0.1328" || dllVersionW == L"2.2.0.0")
			{
				fsrVersionW = L" FSR 4.1.0";
			}
			else if (dllVersionW == L"2.3.0.2740" || dllVersionW == L"2.3.0.2913" || dllVersionW == L"2.3.0.0")
			{
				fsrVersionW = L" FSR 4.1.1";
			}
			else
			{
				fsrVersionW = L" FSR ?";
			}

			//Set version information
			textblock_FsrDllVersion().Text(dllVersionW + fsrVersionW);
		}
		catch (...)
		{
			//Set version information
			textblock_FsrDllVersion().Text(L"?.?.?.?");
		}
	}

	//Get set FSR Override Library
	std::wstring MainPage::FsrOverrideDllGetPathSet(bool globalPath)
	{
		try
		{
			std::wstring dllPath = L"";

			//Check application type
			if (globalPath)
			{
				//Get dll path
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "FsrOvrDLLPath", true);
				if (adlRegistry.has_value())
				{
					dllPath = adlRegistry.value();
				}
			}

			//Return result
			return dllPath;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine(L"Failed getting set FSR Override Library. (Exception)");
			return L"";
		}
	}

	//Get default FSR Override Library
	std::wstring MainPage::FsrOverrideDllGetPathDefault()
	{
		try
		{
			//Get driver installation directory
			const int driverPathSize = 260;
			char driverPathBuffer[driverPathSize]{};
			adl_Res0 = _ADL2_Driver_Path_Get(adl_Context, adl_Gpu_AdapterIndex, driverPathSize, driverPathBuffer);
			if (adl_Res0 == ADL_OK)
			{
				//Convert to string
				std::string driverPath = std::string(driverPathBuffer);

				//Add dll file name to path
				driverPath += "amdxcffx64.dll";

				//Return result
				AVDebugWriteLine(L"Default FSR Override Library: " << driverPath.c_str());
				return string_to_wstring(driverPath);
			}
			else
			{
				//Return result
				AVDebugWriteLine(L"Failed getting default FSR Override Library: " << adl_Res0);
				return L"";
			}
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine(L"Failed getting default FSR Override Library. (Exception)");
			return L"";
		}
	}
}