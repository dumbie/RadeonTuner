#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlVariables.h"

namespace winrt::RadeonTuner::implementation
{
	//Memory allocation
	void* __stdcall ADL_Main_Memory_Alloc(int iSize)
	{
		void* lpBuffer = malloc(iSize);
		return lpBuffer;
	}

	std::wstring MainPage::AdlInitialize()
	{
		try
		{
			//Initialize ADL library
			HINSTANCE hInstance = LoadLibraryW(L"atiadlxx.dll");
			if (hInstance == NULL)
			{
				hInstance = LoadLibraryW(L"atiadlxy.dll");
			}
			if (hInstance == NULL)
			{
				//Set result
				AVDebugWriteLine("ADL library not found");
				return L"ADL library not found";
			}

			//Initialize definitions
			_ADL2_Main_Control_Create = (ADL2_MAIN_CONTROL_CREATE)GetProcAddress(hInstance, "ADL2_Main_Control_Create");
			if (_ADL2_Main_Control_Create == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Main_Control_Create");
				return L"Failed to init _ADL2_Main_Control_Create";
			}

			_ADL2_Main_Control_Destroy = (ADL2_MAIN_CONTROL_DESTROY)GetProcAddress(hInstance, "ADL2_Main_Control_Destroy");
			if (_ADL2_Main_Control_Destroy == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Main_Control_Destroy");
				return L"Failed to init _ADL2_Main_Control_Destroy";
			}

			_ADL2_ApplicationProfiles_Applications_Get = (ADL2_ApplicationProfiles_Applications_Get)GetProcAddress(hInstance, "ADL2_ApplicationProfiles_Applications_Get");
			if (_ADL2_ApplicationProfiles_Applications_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_ApplicationProfiles_Applications_Get");
				return L"Failed to init _ADL2_ApplicationProfiles_Applications_Get";
			}

			//Create ADL main control
			if (_ADL2_Main_Control_Create(ADL_Main_Memory_Alloc, 1, &_ADL2_Context) != ADL_OK)
			{
				//Set result
				AVDebugWriteLine("Failed to create ADL main control");
				return L"Failed to create ADL main control";
			}

			//Set result
			AVDebugWriteLine("ADL initialized.");
			return L"";
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADL failed initializing (Exception)");
			return L"ADL failed initializing (Exception)";
		}
	}
}