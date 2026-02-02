#pragma once
#include "pch.h"

//namespace ADLDefinitions
//{
typedef int(*ADL2_MAIN_CONTROL_CREATE)(ADL_MAIN_MALLOC_CALLBACK callback, int iEnumConnectedAdapters, ADL_CONTEXT_HANDLE* context);
inline ADL2_MAIN_CONTROL_CREATE _ADL2_Main_Control_Create;

typedef int (*ADL2_MAIN_CONTROL_DESTROY)(ADL_CONTEXT_HANDLE context);
inline ADL2_MAIN_CONTROL_DESTROY _ADL2_Main_Control_Destroy;

typedef int (*ADL2_ApplicationProfiles_Applications_Get)(ADL_CONTEXT_HANDLE context, const wchar_t* driverArea, int* numApps, ADLApplicationRecord** adlApplications);
inline ADL2_ApplicationProfiles_Applications_Get _ADL2_ApplicationProfiles_Applications_Get;

typedef int(*ADL2_ApplicationProfiles_RemoveApplication)(ADL_CONTEXT_HANDLE context, const wchar_t* fileName, const wchar_t* path, const wchar_t* version, const wchar_t* driverArea);
inline ADL2_ApplicationProfiles_RemoveApplication _ADL2_ApplicationProfiles_RemoveApplication;

typedef int (*ADL2_ApplicationProfiles_ProfileOfAnApplicationX2_Search)(ADL_CONTEXT_HANDLE context, const wchar_t* fileName, const wchar_t* path, const wchar_t* version, const wchar_t* appProfileArea, ADLApplicationProfile** lppProfile);
inline ADL2_ApplicationProfiles_ProfileOfAnApplicationX2_Search _ADL2_ApplicationProfiles_ProfileOfAnApplicationX2_Search;

typedef int (*ADL2_ApplicationProfiles_ProfileApplicationX2_Assign)(ADL_CONTEXT_HANDLE context, const wchar_t* fileName, const wchar_t* path, const wchar_t* version, const wchar_t* title, const wchar_t* driverArea, const wchar_t* profileName);
inline ADL2_ApplicationProfiles_ProfileApplicationX2_Assign _ADL2_ApplicationProfiles_ProfileApplicationX2_Assign;

typedef int (*ADL2_ApplicationProfiles_Profile_Create)(ADL_CONTEXT_HANDLE context, const wchar_t* driverArea, const wchar_t* profileName, int numProperties, const ADLPropertyRecordCreate* propertyRecords);
inline ADL2_ApplicationProfiles_Profile_Create _ADL2_ApplicationProfiles_Profile_Create;

typedef int (*ADL2_ApplicationProfiles_Profile_Remove)(ADL_CONTEXT_HANDLE context, const wchar_t* driverArea, const wchar_t* profileName);
inline ADL2_ApplicationProfiles_Profile_Remove _ADL2_ApplicationProfiles_Profile_Remove;

typedef int (*ADL2_ApplicationProfiles_PropertyType_Get)(ADL_CONTEXT_HANDLE context, const wchar_t* driverArea, const wchar_t* propertyName, int* outType);
inline ADL2_ApplicationProfiles_PropertyType_Get _ADL2_ApplicationProfiles_PropertyType_Get;

typedef int(*ADL2_ADAPTER_REGVALUESTRING_SET)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDriverPathOption, const char* szSubKey, const char* szKeyName, int iSize, char* lpKeyValue);
inline ADL2_ADAPTER_REGVALUESTRING_SET _ADL2_Adapter_RegValueString_Set;

typedef int(*ADL2_ADAPTER_REGVALUESTRING_GET)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDriverPathOption, const char* szSubKey, const char* szKeyName, int iSize, char* lpKeyValue);
inline ADL2_ADAPTER_REGVALUESTRING_GET _ADL2_Adapter_RegValueString_Get;

typedef int(*ADL2_ADAPTER_REGVALUEINT_SET)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDriverPathOption, const char* szSubKey, const char* szKeyName, int lpKeyValue);
inline ADL2_ADAPTER_REGVALUEINT_SET _ADL2_Adapter_RegValueInt_Set;

typedef int(*ADL2_ADAPTER_REGVALUEINT_GET)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDriverPathOption, const char* szSubKey, const char* szKeyName, int* lpKeyValue);
inline ADL2_ADAPTER_REGVALUEINT_GET _ADL2_Adapter_RegValueInt_Get;
//}