#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

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
			//Main
			_ADL2_Main_Control_Create = (ADL2_Main_Control_Create)GetProcAddress(hInstance, "ADL2_Main_Control_Create");
			if (_ADL2_Main_Control_Create == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Main_Control_Create");
				return L"Failed to init _ADL2_Main_Control_Create";
			}

			_ADL2_Main_Control_Destroy = (ADL2_Main_Control_Destroy)GetProcAddress(hInstance, "ADL2_Main_Control_Destroy");
			if (_ADL2_Main_Control_Destroy == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Main_Control_Destroy");
				return L"Failed to init _ADL2_Main_Control_Destroy";
			}

			//Application
			_ADL2_ApplicationProfiles_Applications_Get = (ADL2_ApplicationProfiles_Applications_Get)GetProcAddress(hInstance, "ADL2_ApplicationProfiles_Applications_Get");
			if (_ADL2_ApplicationProfiles_Applications_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_ApplicationProfiles_Applications_Get");
				return L"Failed to init _ADL2_ApplicationProfiles_Applications_Get";
			}

			_ADL2_ApplicationProfiles_RemoveApplication = (ADL2_ApplicationProfiles_RemoveApplication)GetProcAddress(hInstance, "ADL2_ApplicationProfiles_RemoveApplication");
			if (_ADL2_ApplicationProfiles_RemoveApplication == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_ApplicationProfiles_RemoveApplication");
				return L"Failed to init _ADL2_ApplicationProfiles_RemoveApplication";
			}

			_ADL2_ApplicationProfiles_ProfileOfAnApplicationX2_Search = (ADL2_ApplicationProfiles_ProfileOfAnApplicationX2_Search)GetProcAddress(hInstance, "ADL2_ApplicationProfiles_ProfileOfAnApplicationX2_Search");
			if (_ADL2_ApplicationProfiles_ProfileOfAnApplicationX2_Search == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_ApplicationProfiles_ProfileOfAnApplicationX2_Search");
				return L"Failed to init _ADL2_ApplicationProfiles_ProfileOfAnApplicationX2_Search";
			}

			_ADL2_ApplicationProfiles_ProfileApplicationX2_Assign = (ADL2_ApplicationProfiles_ProfileApplicationX2_Assign)GetProcAddress(hInstance, "ADL2_ApplicationProfiles_ProfileApplicationX2_Assign");
			if (_ADL2_ApplicationProfiles_ProfileApplicationX2_Assign == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_ApplicationProfiles_ProfileApplicationX2_Assign");
				return L"Failed to init _ADL2_ApplicationProfiles_ProfileApplicationX2_Assign";
			}

			_ADL2_ApplicationProfiles_Profile_Create = (ADL2_ApplicationProfiles_Profile_Create)GetProcAddress(hInstance, "ADL2_ApplicationProfiles_Profile_Create");
			if (_ADL2_ApplicationProfiles_Profile_Create == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_ApplicationProfiles_Profile_Create");
				return L"Failed to init _ADL2_ApplicationProfiles_Profile_Create";
			}

			_ADL2_ApplicationProfiles_Profile_Remove = (ADL2_ApplicationProfiles_Profile_Remove)GetProcAddress(hInstance, "ADL2_ApplicationProfiles_Profile_Remove");
			if (_ADL2_ApplicationProfiles_Profile_Remove == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_ApplicationProfiles_Profile_Remove");
				return L"Failed to init _ADL2_ApplicationProfiles_Profile_Remove";
			}

			_ADL2_ApplicationProfiles_PropertyType_Get = (ADL2_ApplicationProfiles_PropertyType_Get)GetProcAddress(hInstance, "ADL2_ApplicationProfiles_PropertyType_Get");
			if (_ADL2_ApplicationProfiles_PropertyType_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_ApplicationProfiles_PropertyType_Get");
				return L"Failed to init _ADL2_ApplicationProfiles_PropertyType_Get";
			}

			_ADL2_ApplicationProfiles_GetCustomization = (ADL2_ApplicationProfiles_GetCustomization)GetProcAddress(hInstance, "ADL2_ApplicationProfiles_GetCustomization");
			if (_ADL2_ApplicationProfiles_GetCustomization == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_ApplicationProfiles_GetCustomization");
				return L"Failed to init _ADL2_ApplicationProfiles_GetCustomization";
			}

			//Registry
			_ADL2_Adapter_RegValueInt_Get = (ADL2_Adapter_RegValueInt_Get)GetProcAddress(hInstance, "ADL2_Adapter_RegValueInt_Get");
			if (_ADL2_Adapter_RegValueInt_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_RegValueInt_Get");
				return L"Failed to init _ADL2_Adapter_RegValueInt_Get";
			}

			_ADL2_Adapter_RegValueInt_Set = (ADL2_Adapter_RegValueInt_Set)GetProcAddress(hInstance, "ADL2_Adapter_RegValueInt_Set");
			if (_ADL2_Adapter_RegValueInt_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_RegValueInt_Set");
				return L"Failed to init _ADL2_Adapter_RegValueInt_Set";
			}

			_ADL2_Adapter_RegValueString_Get = (ADL2_Adapter_RegValueString_Get)GetProcAddress(hInstance, "ADL2_Adapter_RegValueString_Get");
			if (_ADL2_Adapter_RegValueString_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_RegValueString_Get");
				return L"Failed to init _ADL2_Adapter_RegValueString_Get";
			}

			_ADL2_Adapter_RegValueString_Set = (ADL2_Adapter_RegValueString_Set)GetProcAddress(hInstance, "ADL2_Adapter_RegValueString_Set");
			if (_ADL2_Adapter_RegValueString_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_RegValueString_Set");
				return L"Failed to init _ADL2_Adapter_RegValueString_Set";
			}

			//Adapter
			_ADL2_Adapter_Accessibility_Get = (ADL2_Adapter_Accessibility_Get)GetProcAddress(hInstance, "ADL2_Adapter_Accessibility_Get");
			if (_ADL2_Adapter_Accessibility_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_Accessibility_Get");
				return L"Failed to init _ADL2_Adapter_Accessibility_Get";
			}

			//Create ADL main control
			if (_ADL2_Main_Control_Create(ADL_Main_Memory_Alloc, 1, &adl_Context) != ADL_OK)
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