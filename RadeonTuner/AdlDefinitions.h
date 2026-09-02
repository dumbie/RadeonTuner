#pragma once
#include "pch.h"

//namespace ADLDefinitions
//{
//Main
typedef int(*ADL2_Main_Control_Create)(ADL_MAIN_MALLOC_CALLBACK callback, int iEnumConnectedAdapters, ADL_CONTEXT_HANDLE* context);
inline ADL2_Main_Control_Create _ADL2_Main_Control_Create;

typedef int (*ADL2_Main_Control_Destroy)(ADL_CONTEXT_HANDLE context);
inline ADL2_Main_Control_Destroy _ADL2_Main_Control_Destroy;

//User
typedef int (*ADL2_User_Settings_Notify)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADL_USER_SETTINGS iSetting, int iChanged);
inline ADL2_User_Settings_Notify _ADL2_User_Settings_Notify;

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
typedef int (*ADL2_Adapter_AdapterInfoX3_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* numAdapters, AdapterInfo** lppAdapterInfo);
inline ADL2_Adapter_AdapterInfoX3_Get _ADL2_Adapter_AdapterInfoX3_Get;

typedef int (*ADL2_Adapter_Active_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* lpStatus);
inline ADL2_Adapter_Active_Get _ADL2_Adapter_Active_Get;

typedef int (*ADL2_Adapter_VideoBiosInfo_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLBiosInfo* lpBiosInfo);
inline ADL2_Adapter_VideoBiosInfo_Get _ADL2_Adapter_VideoBiosInfo_Get;

typedef int (*ADL2_Adapter_Accessibility_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* lpAccessibility);
inline ADL2_Adapter_Accessibility_Get _ADL2_Adapter_Accessibility_Get;

typedef int (*ADL2_Adapter_MemoryInfoX4_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLMemoryInfoX4* lpMemoryInfoX4);
inline ADL2_Adapter_MemoryInfoX4_Get _ADL2_Adapter_MemoryInfoX4_Get;

typedef int (*ADL2_GcnAsicInfo_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLGcnInfo* gcnInfo);
inline ADL2_GcnAsicInfo_Get _ADL2_GcnAsicInfo_Get;

typedef int (*ADL2_Adapter_ChipSetInfo_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLChipSetInfo* lpChipSetInfo);
inline ADL2_Adapter_ChipSetInfo_Get _ADL2_Adapter_ChipSetInfo_Get;

typedef int(*ADL2_Adapter_ProductName_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, char* lpProductName);
inline ADL2_Adapter_ProductName_Get _ADL2_Adapter_ProductName_Get;

typedef int (*ADL2_Adapter_ID_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* lpAdapterID);
inline ADL2_Adapter_ID_Get _ADL2_Adapter_ID_Get;

typedef int (*ADL2_Adapter_DedicatedVRAMUsage_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* iVRAMUsageInMB);
inline ADL2_Adapter_DedicatedVRAMUsage_Get _ADL2_Adapter_DedicatedVRAMUsage_Get;

typedef int (*ADL2_Adapter_Feature_Caps)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADL_UIFEATURES_GROUP iFeatureID, int* iIsFeatureSupported);
inline ADL2_Adapter_Feature_Caps _ADL2_Adapter_Feature_Caps;

//Graphics
typedef int (*ADL2_Graphics_VersionsX3_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLVersionsInfoX2* lpVersionsInfo);
inline ADL2_Graphics_VersionsX3_Get _ADL2_Graphics_VersionsX3_Get;

//Graphics - FRTC Pro
typedef int (*ADL2_FRTCPro_Settings_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADL_FRTCPRO_Settings* FRTCPROSettings);
inline ADL2_FRTCPro_Settings_Get _ADL2_FRTCPro_Settings_Get;

typedef int (*ADL2_FRTCPro_Settings_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADL_FRTCPRO_Settings FRTCPROSettings, ADL_FRTCPRO_CHANGED_REASON changeReason);
inline ADL2_FRTCPro_Settings_Set _ADL2_FRTCPro_Settings_Set;

//Graphics - FRTC
typedef int (*ADL2_FPS_Caps)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* lpSupported, int* lpVersion);
inline ADL2_FPS_Caps _ADL2_FPS_Caps;

typedef int (*ADL2_FPS_Settings_Reset)(ADL_CONTEXT_HANDLE context, int iAdapterIndex);
inline ADL2_FPS_Settings_Reset _ADL2_FPS_Settings_Reset;

typedef int (*ADL2_FPS_Settings_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLFPSSettingsInput lpFPSSettings);
inline ADL2_FPS_Settings_Set _ADL2_FPS_Settings_Set;

typedef int (*ADL2_FPS_Settings_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLFPSSettingsOutput* lpFPSSettings);
inline ADL2_FPS_Settings_Get _ADL2_FPS_Settings_Get;

//Graphics - Chill
typedef int (*ADL2_Chill_Caps_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* iSupported, int* iCheckCaps);
inline ADL2_Chill_Caps_Get _ADL2_Chill_Caps_Get;

typedef int(*ADL2_CHILL_SettingsX2_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADL_CHILL_SETTINGS settings, ADL_CHILL_NOTFICATION_REASON changeReason, ADL_ERROR_REASON* errorReason);
inline ADL2_CHILL_SettingsX2_Set _ADL2_CHILL_SettingsX2_Set;

typedef int(*ADL2_CHILL_SettingsX2_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADL_CHILL_SETTINGS* settings);
inline ADL2_CHILL_SettingsX2_Get _ADL2_CHILL_SettingsX2_Get;

//Graphics - Boost
typedef int (*ADL2_BOOST_SettingsX4_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADL_BOOST_SETTINGSX4 settings, ADL_BOOST_NOTIFICATION_REASONX4 changeReason, ADL_ERROR_REASON2* errorReason);
inline ADL2_BOOST_SettingsX4_Set _ADL2_BOOST_SettingsX4_Set;

typedef int (*ADL2_BOOST_SettingsX4_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADL_BOOST_SETTINGSX4* settings);
inline ADL2_BOOST_SettingsX4_Get _ADL2_BOOST_SettingsX4_Get;

//Graphics - Enhanced Sync
typedef int (*ADL2_TurboSyncSupport_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* iSupported);
inline ADL2_TurboSyncSupport_Get _ADL2_TurboSyncSupport_Get;

//Graphics - Radeon Image Sharpening 1
typedef int(*ADL2_RIS_Settings_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADL_RIS_SETTINGS settings, ADL_RIS_NOTFICATION_REASON changeReason);
inline ADL2_RIS_Settings_Set _ADL2_RIS_Settings_Set;

typedef int(*ADL2_RIS_Settings_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADL_RIS_SETTINGS* settings);
inline ADL2_RIS_Settings_Get _ADL2_RIS_Settings_Get;

//Graphics - Radeon Image Sharpening 2
typedef int(*ADL2_RIS_SettingsX2_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADL_RIS2_SETTINGS settings, ADL_RIS2_NOTIFICATION_REASON changeReason);
inline ADL2_RIS_SettingsX2_Set _ADL2_RIS_SettingsX2_Set;

typedef int(*ADL2_RIS_SettingsX2_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADL_RIS2_SETTINGS* settings);
inline ADL2_RIS_SettingsX2_Get _ADL2_RIS_SettingsX2_Get;

//Graphics - Latency Reduction
typedef int (*ADL2_DELAG_SettingsX4_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADL_DELAG_SETTINGSX4 settings, ADL_DELAG_NOTIFICATION_REASONX4 changeReason, ADL_ERROR_REASON2* errorReason);
inline ADL2_DELAG_SettingsX4_Set _ADL2_DELAG_SettingsX4_Set;

typedef int (*ADL2_DELAG_SettingsX4_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADL_DELAG_SETTINGSX4* settings);
inline ADL2_DELAG_SettingsX4_Get _ADL2_DELAG_SettingsX4_Get;

//Graphics - Fluid Motion Frames
typedef int (*ADL2_DriverFrameGenerationSupport_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* iSupported);
inline ADL2_DriverFrameGenerationSupport_Get _ADL2_DriverFrameGenerationSupport_Get;

typedef int (*ADL2_DriverFrameGeneration_Settings_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* iEnabled);
inline ADL2_DriverFrameGeneration_Settings_Get _ADL2_DriverFrameGeneration_Settings_Get;

typedef int (*ADL2_DriverFrameGeneration_Settings_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iEnabled);
inline ADL2_DriverFrameGeneration_Settings_Set _ADL2_DriverFrameGeneration_Settings_Set;

//Graphics - FSR Upscaling Override
typedef int (*ADL2_DriverMLSRSupport_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* iSupported);
inline ADL2_DriverMLSRSupport_Get _ADL2_DriverMLSRSupport_Get;

//Graphics - FSR Frame Generation Override
typedef int (*ADL2_DriverMLFISupport_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* iSupported);
inline ADL2_DriverMLFISupport_Get _ADL2_DriverMLFISupport_Get;

//Graphics - FSR Ray Regeneration Denoiser Override
typedef int (*ADL2_DriverMLDSupport_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* iSupported);
inline ADL2_DriverMLDSupport_Get _ADL2_DriverMLDSupport_Get;

//Graphics - FSR Multi Frame Generation Override
typedef int (*ADL2_DriverMFGSupport_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* iSupported);
inline ADL2_DriverMFGSupport_Get _ADL2_DriverMFGSupport_Get;

//Graphics - FSR Neural Radiance Caching Override
typedef int (*ADL2_DriverNRCSupport_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* iSupported);
inline ADL2_DriverNRCSupport_Get _ADL2_DriverNRCSupport_Get;

//Display
typedef int (*ADL2_Display_DisplayInfo_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* lpNumDisplays, ADLDisplayInfo** lppInfo, int iForceDetect);
inline ADL2_Display_DisplayInfo_Get _ADL2_Display_DisplayInfo_Get;

typedef int (*ADL2_Display_Property_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLDisplayProperty* lpDisplayProperty);
inline ADL2_Display_Property_Get _ADL2_Display_Property_Get;

typedef int (*ADL2_Display_Property_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLDisplayProperty* lpDisplayProperty);
inline ADL2_Display_Property_Set _ADL2_Display_Property_Set;

typedef int (*ADL2_DFP_GPUScalingEnable_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int* lpSupport, int* lpCurrent, int* lpDefault);
inline ADL2_DFP_GPUScalingEnable_Get _ADL2_DFP_GPUScalingEnable_Get;

typedef int(*ADL2_DFP_GPUScalingEnable_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int iCurrent);
inline ADL2_DFP_GPUScalingEnable_Set _ADL2_DFP_GPUScalingEnable_Set;

typedef int(*ADL2_Display_PreservedAspectRatio_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int* lpSupport, int* lpCurrent, int* lpDefault);
inline ADL2_Display_PreservedAspectRatio_Get _ADL2_Display_PreservedAspectRatio_Get;

typedef int(*ADL2_Display_PreservedAspectRatio_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int iCurrent);
inline ADL2_Display_PreservedAspectRatio_Set _ADL2_Display_PreservedAspectRatio_Set;

typedef int(*ADL2_Display_ImageExpansion_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int* lpSupport, int* lpCurrent, int* lpDefault);
inline ADL2_Display_ImageExpansion_Get _ADL2_Display_ImageExpansion_Get;

typedef int(*ADL2_Display_ImageExpansion_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int iCurrent);
inline ADL2_Display_ImageExpansion_Set _ADL2_Display_ImageExpansion_Set;

typedef int(*ADL2_Display_FreeSyncState_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int* lpCurrent, int* lpDefault, int* lpMinRefreshRateInMicroHz, int* lpMaxRefreshRateInMicroHz);
inline ADL2_Display_FreeSyncState_Get _ADL2_Display_FreeSyncState_Get;

typedef int (*ADL2_Display_FreeSyncState_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int iSetting, int iRefreshRateInMicroHz);
inline ADL2_Display_FreeSyncState_Set _ADL2_Display_FreeSyncState_Set;

typedef int (*ADL2_Display_ColorDepth_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int* lpColorDepth);
inline ADL2_Display_ColorDepth_Get _ADL2_Display_ColorDepth_Get;

typedef int (*ADL2_Display_ColorDepth_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int iColorDepth);
inline ADL2_Display_ColorDepth_Set _ADL2_Display_ColorDepth_Set;

typedef int(*ADL2_Display_PixelFormat_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int* lpPixelFormat);
inline ADL2_Display_PixelFormat_Get _ADL2_Display_PixelFormat_Get;

typedef int (*ADL2_Display_PixelFormat_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int iPixelFormat);
inline ADL2_Display_PixelFormat_Set _ADL2_Display_PixelFormat_Set;

typedef int (*ADL2_Display_Color_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int iColorType, int* lpCurrent, int* lpDefault, int* lpMin, int* lpMax, int* lpStep);
inline ADL2_Display_Color_Get _ADL2_Display_Color_Get;

typedef int (*ADL2_Display_Color_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int iColorType, int iCurrent);
inline ADL2_Display_Color_Set _ADL2_Display_Color_Set;

typedef int (*ADL2_Display_ColorTemperatureSource_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int* lpTempSource);
inline ADL2_Display_ColorTemperatureSource_Get _ADL2_Display_ColorTemperatureSource_Get;

typedef int (*ADL2_Display_ColorTemperatureSource_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int iTempSource);
inline ADL2_Display_ColorTemperatureSource_Set _ADL2_Display_ColorTemperatureSource_Set;

//Display - Modes
typedef int (*ADL2_Display_Modes_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int* lpNumModes, ADLMode** lppModes);
inline ADL2_Display_Modes_Get _ADL2_Display_Modes_Get;

typedef int (*ADL2_Display_Modes_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int iNumModes, ADLMode* lpModes);
inline ADL2_Display_Modes_Set _ADL2_Display_Modes_Set;

typedef int (*ADL2_Display_PossibleMode_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* lpNumModes, ADLMode** lppModes);
inline ADL2_Display_PossibleMode_Get _ADL2_Display_PossibleMode_Get;

//Display - CVDC
typedef int (*ADL2_Display_CVDC_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLCvdcType cvdcType, int* cvdcValue);
inline ADL2_Display_CVDC_Get _ADL2_Display_CVDC_Get;

typedef int (*ADL2_Display_CVDC_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLCvdcType cvdcType, int cvdcValue);
inline ADL2_Display_CVDC_Set _ADL2_Display_CVDC_Set;

//Display - Eyefinity
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

//Display - HDCP
typedef int (*ADL2_Display_HDCP_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLHDCPSettings* lpHDCPSettings);
inline ADL2_Display_HDCP_Get _ADL2_Display_HDCP_Get;

typedef int (*ADL2_Display_HDCP_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int iSetToDefault, int iEnable);
inline ADL2_Display_HDCP_Set _ADL2_Display_HDCP_Set;

//Display - VariBright
typedef int (*ADL2_Adapter_VariBright_CapsX2)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* iSupported, int* iEnabled, int* iVersion, int* iUnknown);
inline ADL2_Adapter_VariBright_CapsX2 _ADL2_Adapter_VariBright_CapsX2;

typedef int (*ADL2_Adapter_VariBrightEnable_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iEnabled);
inline ADL2_Adapter_VariBrightEnable_Set _ADL2_Adapter_VariBrightEnable_Set;

typedef int (*ADL2_Adapter_VariBrightLevel_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* iDefaultLevel, int* iNumberOfLevels, int* iStep, int* iCurrentLevel);
inline ADL2_Adapter_VariBrightLevel_Get _ADL2_Adapter_VariBrightLevel_Get;

typedef int (*ADL2_Adapter_VariBrightLevel_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iCurrentLevel, int iApplyImmediately);
inline ADL2_Adapter_VariBrightLevel_Set _ADL2_Adapter_VariBrightLevel_Set;

//Display - Color Enhancement
typedef int(*ADL2_Display_SCE_State_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int sceType);
inline ADL2_Display_SCE_State_Set _ADL2_Display_SCE_State_Set;

typedef int (*ADL2_Display_SCE_State_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int* sceType, int* sceStatus);
inline ADL2_Display_SCE_State_Get _ADL2_Display_SCE_State_Get;

//Display - HDR State
typedef int (*ADL2_Display_HDRState_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLDisplayID displayID, int* iSupport, int* iEnable);
inline ADL2_Display_HDRState_Get _ADL2_Display_HDRState_Get;

typedef int (*ADL2_Display_HDRState_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLDisplayID displayID, int iEnable);
inline ADL2_Display_HDRState_Set _ADL2_Display_HDRState_Set;

//Display - EDID
typedef int (*ADL2_Display_EdidData_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLDisplayEDIDData* lpEDIDData);
inline ADL2_Display_EdidData_Get _ADL2_Display_EdidData_Get;

typedef int (*ADL2_Display_EdidData_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLDisplayEDIDData lpEDIDData);
inline ADL2_Display_EdidData_Set _ADL2_Display_EdidData_Set;

//Display - DDC
typedef int (*ADL2_Display_DDCInfo2_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLDDCInfo2* lpInfo);
inline ADL2_Display_DDCInfo2_Get _ADL2_Display_DDCInfo2_Get;

//Display - CRU
typedef int (*ADL2_Display_CustomizedMode_Add)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLCustomMode customMode);
inline ADL2_Display_CustomizedMode_Add _ADL2_Display_CustomizedMode_Add;

typedef int (*ADL2_Display_CustomizedMode_Delete)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int iIndex);
inline ADL2_Display_CustomizedMode_Delete _ADL2_Display_CustomizedMode_Delete;

typedef int (*ADL2_Display_CustomizedModeList_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLCustomMode* lpCustomModeList, int iBuffSize);
inline ADL2_Display_CustomizedModeList_Get _ADL2_Display_CustomizedModeList_Get;

typedef int (*ADL2_Display_CustomizedModeListNum_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int* lpListNum);
inline ADL2_Display_CustomizedModeListNum_Get _ADL2_Display_CustomizedModeListNum_Get;

//Display - Gamma
typedef int (*ADL2_Adapter_Gamma_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, AdlGammaRamp lpGammaRamp);
inline ADL2_Adapter_Gamma_Set _ADL2_Adapter_Gamma_Set;

typedef int (*ADL2_Adapter_Gamma_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, AdlGammaRamp* lpGammaRamp);
inline ADL2_Adapter_Gamma_Get _ADL2_Adapter_Gamma_Get;

//Display - OpenGL 10-Bit Pixel Format
typedef int (*ADL2_Workstation_DeepBitDepthX2_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* lpDefDBDState, int* lpCurDBDState);
inline ADL2_Workstation_DeepBitDepthX2_Get _ADL2_Workstation_DeepBitDepthX2_Get;

typedef int (*ADL2_Workstation_DeepBitDepthX2_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDBDState);
inline ADL2_Workstation_DeepBitDepthX2_Set _ADL2_Workstation_DeepBitDepthX2_Set;

//Multimedia
typedef int(*ADL2_MMD_Features_Caps)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLFeatureCaps** lppFeatureCaps, int* lpFeatureCount);
inline ADL2_MMD_Features_Caps _ADL2_MMD_Features_Caps;

typedef int (*ADL2_MMD_FeatureValues_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLFeatureValues* lpFeatureValues, int iFeatureCount, int clientID);
inline ADL2_MMD_FeatureValues_Set _ADL2_MMD_FeatureValues_Set;

typedef int(*ADL2_MMD_FeatureValues_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLFeatureValues** lppFeatureValues, int* lpFeatureCount);
inline ADL2_MMD_FeatureValues_Get _ADL2_MMD_FeatureValues_Get;

//Driver
typedef int (*ADL2_Driver_Path_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iSize, char* lpDriverPath);
inline ADL2_Driver_Path_Get _ADL2_Driver_Path_Get;

//Overdrive
typedef int (*ADL2_Overdrive_Caps)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* iSupported, int* iEnabled, int* iVersion);
inline ADL2_Overdrive_Caps _ADL2_Overdrive_Caps;

typedef int (*ADL2_Overdrive8_Init_SettingX2_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* lpOverdrive8Capabilities, int* lpNumberOfFeatures, ADLOD8SingleInitSettingWrap** lppInitSettingList);
inline ADL2_Overdrive8_Init_SettingX2_Get _ADL2_Overdrive8_Init_SettingX2_Get;

typedef int (*ADL2_Overdrive8_Current_SettingX2_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* lpNumberOfFeatures, int** lppCurrentSettingList);
inline ADL2_Overdrive8_Current_SettingX2_Get _ADL2_Overdrive8_Current_SettingX2_Get;

typedef int (*ADL2_Overdrive8_Setting_Set)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLOD8SetSetting* lpSetSetting, ADLOD8CurrentSetting* lpCurrentSetting);
inline ADL2_Overdrive8_Setting_Set _ADL2_Overdrive8_Setting_Set;

//Metrics
typedef int (*ADL2_New_QueryPMLogData_Get)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLPMLogDataOutput* lpDataOutput);
inline ADL2_New_QueryPMLogData_Get _ADL2_New_QueryPMLogData_Get;

typedef int (*ADL2_Device_PMLog_Device_Create)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADL_D3DKMT_HANDLE* pDevice);
inline ADL2_Device_PMLog_Device_Create _ADL2_Device_PMLog_Device_Create;

typedef int (*ADL2_Device_PMLog_Device_Destroy)(ADL_CONTEXT_HANDLE context, ADL_D3DKMT_HANDLE hDevice);
inline ADL2_Device_PMLog_Device_Destroy _ADL2_Device_PMLog_Device_Destroy;

typedef int (*ADL2_Adapter_PMLog_Start)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLPMLogStartInput* pPMLogStartInput, ADLPMLogStartOutput* pPMLogStartOutput, ADL_D3DKMT_HANDLE hDevice);
inline ADL2_Adapter_PMLog_Start _ADL2_Adapter_PMLog_Start;

typedef int (*ADL2_Adapter_PMLog_Stop)(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADL_D3DKMT_HANDLE hDevice);
inline ADL2_Adapter_PMLog_Stop _ADL2_Adapter_PMLog_Stop;

//Flush
typedef int (*ADL2_Flush_Driver_Data)(ADL_CONTEXT_HANDLE context, int iAdapterIndex);
inline ADL2_Flush_Driver_Data _ADL2_Flush_Driver_Data;
//}