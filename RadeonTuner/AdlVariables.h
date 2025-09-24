#pragma once
#include "pch.h"

//namespace ADLVariables
//{
//Variables
inline ADL_CONTEXT_HANDLE _ADL2_Context = NULL;

//Definitions
typedef int(*ADL2_MAIN_CONTROL_CREATE)(ADL_MAIN_MALLOC_CALLBACK callback, int iEnumConnectedAdapters, ADL_CONTEXT_HANDLE* context);
inline ADL2_MAIN_CONTROL_CREATE _ADL2_Main_Control_Create;

typedef int (*ADL2_MAIN_CONTROL_DESTROY)(ADL_CONTEXT_HANDLE context);
inline ADL2_MAIN_CONTROL_DESTROY _ADL2_Main_Control_Destroy;

typedef int (*ADL2_ApplicationProfiles_Applications_Get)(ADL_CONTEXT_HANDLE context, const wchar_t* driverArea, int* numApps, ADLApplicationRecord** adlApplications);
inline ADL2_ApplicationProfiles_Applications_Get _ADL2_ApplicationProfiles_Applications_Get;

typedef int (*ADL2_GRAPHICS_VERSIONSX2_GET)(ADL_CONTEXT_HANDLE context, ADLVersionsInfoX2* lpVersionsInfo);
inline ADL2_GRAPHICS_VERSIONSX2_GET _ADL2_Graphics_VersionsX2_Get;
//}