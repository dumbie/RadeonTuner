#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	//Load settings from file
	std::optional<AdlApplication> MainPage::GraphicsSettings_FileLoad(std::string loadPath)
	{
		try
		{
			//Open settings file
			std::string jsonString = file_to_string(loadPath);

			//Convert json to struct
			return jsonstring_to_struct<AdlApplication>(jsonString);
		}
		catch (...) {}
		return std::nullopt;
	}

	//Save settings to file
	bool MainPage::GraphicsSettings_FileSave(AdlApplication graphicsSettings, std::string savePath)
	{
		try
		{
			//Convert json to string
			std::string jsonString = struct_to_jsonstring(graphicsSettings, true);

			//Save settings file
			return string_to_file(savePath, jsonString);
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	//Update FSR dll version text
	void MainPage::FsrOverrideDllUpdateVersion(std::wstring dllPath)
	{
		try
		{
			//Get dll version
			std::string dllVersion = GetVersionFromFile(dllPath);
			std::wstring dllVersionW = string_to_wstring(dllVersion);

			//Get fsr version
			//Fix read FSR version directly from amdxcffx64.dll UpdateFfxApiProviderEx
			std::wstring fsrVersionW = L"";
			if (dllVersionW == L"1.0.0.38222" || dllVersionW == L"1.0.0.38733" || dllVersionW == L"1.0.0.39037")
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
			else if (dllVersionW == L"2.3.0.0")
			{
				fsrVersionW = L" FSR 4.1.1";
			}

			//Set version information
			textblock_FsrDllVersion().Text(dllVersionW + fsrVersionW);
		}
		catch (...) {}
	}

	//Get default FSR Override dll path
	std::wstring MainPage::FsrOverrideDllDefaultPath()
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
				AVDebugWriteLine(L"Default FSR Override dll path: " << driverPath.c_str());
				return string_to_wstring(driverPath);
			}
			else
			{
				//Return result
				AVDebugWriteLine(L"Failed getting default FSR Override dll path: " << adl_Res0);
				return L"";
			}
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine(L"Failed getting default FSR Override dll path. (Exception)");
			return L"";
		}
	}
}