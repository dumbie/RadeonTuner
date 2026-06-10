#pragma once
#include "pch.h"

//namespace ADLDefinitions
//{
//Main
typedef int(*ADL2_Main_Control_Create)(ADL_MAIN_MALLOC_CALLBACK callback, int iEnumConnectedAdapters, ADL_CONTEXT_HANDLE* context);
inline ADL2_Main_Control_Create _ADL2_Main_Control_Create;

typedef int (*ADL2_Main_Control_Destroy)(ADL_CONTEXT_HANDLE context);
inline ADL2_Main_Control_Destroy _ADL2_Main_Control_Destroy;

//Applications
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

typedef int (*ADL2_ApplicationProfiles_PropertyType_Get)(ADL_CONTEXT_HANDLE context, const wchar_t* driverArea, const wchar_t* propertyName, DATATYPES* outType);
inline ADL2_ApplicationProfiles_PropertyType_Get _ADL2_ApplicationProfiles_PropertyType_Get;

typedef int (*ADL2_ApplicationProfiles_GetCustomization)(ADL_CONTEXT_HANDLE context, ADL_AP_DATABASE databaseIn, CUSTOMISATIONS* pCustomizationOut);
inline ADL2_ApplicationProfiles_GetCustomization _ADL2_ApplicationProfiles_GetCustomization;

//Registry
typedef int(*ADL2_Adapter_RegValueString_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDriverPathOption, const char* szSubKey, const char* szKeyName, int iSize, const wchar_t* lpKeyValue);
inline ADL2_Adapter_RegValueString_Set _ADL2_Adapter_RegValueString_Set;

typedef int(*ADL2_Adapter_RegValueString_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDriverPathOption, const char* szSubKey, const char* szKeyName, int iSize, wchar_t* lpKeyValue);
inline ADL2_Adapter_RegValueString_Get _ADL2_Adapter_RegValueString_Get;

typedef int(*ADL2_Adapter_RegValueInt_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDriverPathOption, const char* szSubKey, const char* szKeyName, int lpKeyValue);
inline ADL2_Adapter_RegValueInt_Set _ADL2_Adapter_RegValueInt_Set;

typedef int(*ADL2_Adapter_RegValueInt_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDriverPathOption, const char* szSubKey, const char* szKeyName, int* lpKeyValue);
inline ADL2_Adapter_RegValueInt_Get _ADL2_Adapter_RegValueInt_Get;

//Adapter
typedef int (*ADL2_Adapter_Accessibility_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* lpAccessibility);
inline ADL2_Adapter_Accessibility_Get _ADL2_Adapter_Accessibility_Get;

typedef int (*ADL2_Adapter_MemoryInfoX4_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLMemoryInfoX4* lpMemoryInfoX4);
inline ADL2_Adapter_MemoryInfoX4_Get _ADL2_Adapter_MemoryInfoX4_Get;

typedef int (*ADL2_GcnAsicInfo_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLGcnInfo* gcnInfo);
inline ADL2_GcnAsicInfo_Get _ADL2_GcnAsicInfo_Get;

typedef int (*ADL2_Adapter_ChipSetInfo_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLChipSetInfo* lpChipSetInfo);
inline ADL2_Adapter_ChipSetInfo_Get _ADL2_Adapter_ChipSetInfo_Get;

//Display
typedef int (*ADL2_Display_Color_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int iColorType, int* lpCurrent, int* lpDefault, int* lpMin, int* lpMax, int* lpStep);
inline ADL2_Display_Color_Get _ADL2_Display_Color_Get;

typedef int (*ADL2_Display_Color_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int iColorType, int iCurrent);
inline ADL2_Display_Color_Set _ADL2_Display_Color_Set;

typedef int (*ADL2_Display_ColorTemperatureSource_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int* lpTempSource);
inline ADL2_Display_ColorTemperatureSource_Get _ADL2_Display_ColorTemperatureSource_Get;

typedef int (*ADL2_Display_ColorTemperatureSource_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int iTempSource);
inline ADL2_Display_ColorTemperatureSource_Set _ADL2_Display_ColorTemperatureSource_Set;

typedef int (*ADL2_Display_CVDC_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLCvdcType cvdcType, int* cvdcValue);
inline ADL2_Display_CVDC_Get _ADL2_Display_CVDC_Get;

typedef int (*ADL2_Display_CVDC_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLCvdcType cvdcType, int cvdcValue);
inline ADL2_Display_CVDC_Set _ADL2_Display_CVDC_Set;

typedef int (*ADL2_Display_DisplayMapConfig_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* lpNumDisplayMap, ADLDisplayMap** lppDisplayMap, int* lpNumDisplayTarget, ADLDisplayTarget** lppDisplayTarget, int iOptions);
inline ADL2_Display_DisplayMapConfig_Get _ADL2_Display_DisplayMapConfig_Get;

typedef int (*ADL2_Display_SLSMapIndex_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iADLNumDisplayTarget, ADLDisplayTarget* lpDisplayTarget, int* lpSLSMapIndex);
inline ADL2_Display_SLSMapIndex_Get _ADL2_Display_SLSMapIndex_Get;

typedef int (*ADL2_Display_SLSMapIndexList_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* lpNumSLSMapIndexList, int** lppSLSMapIndexList, int iOptions);
inline ADL2_Display_SLSMapIndexList_Get _ADL2_Display_SLSMapIndexList_Get;

typedef int (*ADL2_Display_SLSMapConfig_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iSLSMapIndex, ADLSLSMap* lpSLSMap, int* lpNumSLSTarget, ADLSLSTarget** lppSLSTarget, int* lpNumNativeMode, ADLSLSMode** lppNativeMode, int* lpNumStandardModeOffsets, ADLSLSOffset** lppStandardModeOffsets, int* lpNumBezelMode, ADLBezelTransientMode** lppBezelMode, int* lpNumTransientMode, ADLBezelTransientMode** lppTransientMode, int* lpNumSLSOffset, ADLSLSOffset** lppSLSOffset, int iOption);
inline ADL2_Display_SLSMapConfig_Get _ADL2_Display_SLSMapConfigX2_Get;

typedef int (*ADL2_Display_SLSMapConfig_Create)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLSLSMap SLSMap, int iNumTarget, ADLSLSTarget* lpSLSTarget, int iBezelModePercent, int* lpSLSMapIndex, int iOption);
inline ADL2_Display_SLSMapConfig_Create _ADL2_Display_SLSMapConfig_Create;

typedef int (*ADL2_Display_SLSMapConfig_Delete)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iSLSMapIndex);
inline ADL2_Display_SLSMapConfig_Delete _ADL2_Display_SLSMapConfig_Delete;

typedef int (*ADL2_Display_SLSMapConfigX2_Delete)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iNumSLSMapIndex, int* lpSLSMapIndexes);
inline ADL2_Display_SLSMapConfigX2_Delete _ADL2_Display_SLSMapConfigX2_Delete;

typedef int (*ADL2_Display_SLSMapConfig_SetState)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iNumSLSMapIndex, int iState);
inline ADL2_Display_SLSMapConfig_SetState _ADL2_Display_SLSMapConfig_SetState;

//Overdrive
typedef int (*ADL2_Overdrive8_Init_SettingX2_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* lpOverdrive8Capabilities, int* lpNumberOfFeatures, ADLOD8SingleInitSettingWrap** lppInitSettingList);
inline ADL2_Overdrive8_Init_SettingX2_Get _ADL2_Overdrive8_Init_SettingX2_Get;

typedef int (*ADL2_Overdrive8_Current_SettingX2_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* lpNumberOfFeatures, int** lppCurrentSettingList);
inline ADL2_Overdrive8_Current_SettingX2_Get _ADL2_Overdrive8_Current_SettingX2_Get;

typedef int (*ADL2_Overdrive8_Setting_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLOD8SetSetting* lpSetSetting, ADLOD8CurrentSetting* lpCurrentSetting);
inline ADL2_Overdrive8_Setting_Set _ADL2_Overdrive8_Setting_Set;

//Flush
typedef int (*ADL2_Flush_Driver_Data)(ADL_CONTEXT_HANDLE context, int iAdapterIndex);
inline ADL2_Flush_Driver_Data _ADL2_Flush_Driver_Data;
//}