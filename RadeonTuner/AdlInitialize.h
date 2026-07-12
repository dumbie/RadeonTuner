#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	//Memory allocation
	void* __stdcall ADL_MemoryAlloc_Main(int iSize)
	{
		void* lpBuffer = malloc(iSize);
		return lpBuffer;
	}

	//Memory free
	void __stdcall ADL_MemoryFree_Main(void** lpBuffer)
	{
		if (*lpBuffer != NULL)
		{
			free(*lpBuffer);
			*lpBuffer = NULL;
		}
	}

	void MainPage::ADL_MemoryFree_Customizations(CUSTOMISATIONS* pCustomisations)
	{
		try
		{
			if (pCustomisations != NULL)
			{
				//Areas
				AREA* areaCurrent = pCustomisations->HeadArea;
				while (areaCurrent)
				{
					//Get next area
					AREA* areaNext = areaCurrent->NextArea;

					//Free DriverComponent
					if (areaCurrent->DriverComponent)
					{
						free(areaCurrent->DriverComponent->NameOfDriver);
						free(areaCurrent->DriverComponent);
					}

					//Free Properties
					PROPERTY* propertyCurrent = areaCurrent->HeadProperty;
					while (propertyCurrent)
					{
						PROPERTY* propertyNext = propertyCurrent->NextProperty;
						free(propertyCurrent->NameOfProperty);
						free(propertyCurrent->SetOfValidEnumStringsTokenised);
						free(propertyCurrent);
						propertyCurrent = propertyNext;
					}

					//Free current area
					free(areaCurrent);
					areaCurrent = areaNext;
				}

				//Profiles
				PROFILE* profileCurrent = pCustomisations->HeadProfile;
				while (profileCurrent)
				{
					//Get next profile
					PROFILE* profileNext = profileCurrent->NextProfile;

					//Free strings
					free(profileCurrent->NameOfThisProfile);
					free(profileCurrent->NotesAboutThisProfile);

					//Free Values
					VALUE* valueCurrent = profileCurrent->HeadValue;
					while (valueCurrent)
					{
						VALUE* valueNext = valueCurrent->NextValue;
						free(valueCurrent->DataOfValue);
						free(valueCurrent);
						valueCurrent = valueNext;
					}

					//Free current profile
					free(profileCurrent);
					profileCurrent = profileNext;
				}

				//Applications
				APPLICATION* appCurrent = pCustomisations->HeadApplication;
				while (appCurrent)
				{
					//Get next application
					APPLICATION* appNext = appCurrent->NextApplication;

					//Free strings
					free(appCurrent->TitleOfApplicationRecord);
					free(appCurrent->FilenameOfThisApplication);
					free(appCurrent->PartialPathOfApplication);
					free(appCurrent->Version);

					//Free uses
					USE* useCurrent = appCurrent->HeadUse;
					while (useCurrent)
					{
						USE* useNext = useCurrent->NextUse;
						free(useCurrent->NameOfTheProfileToUse);
						free(useCurrent);
						useCurrent = useNext;
					}

					//Free current application
					free(appCurrent);
					appCurrent = appNext;
				}

				//Strings
				free(pCustomisations->Content);
				free(pCustomisations->Release);
				free(pCustomisations->Format);

				//Nullify pointer
				pCustomisations = NULL;
			}
		}
		catch (...) {}
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
			}

			_ADL2_Main_Control_Destroy = (ADL2_Main_Control_Destroy)GetProcAddress(hInstance, "ADL2_Main_Control_Destroy");
			if (_ADL2_Main_Control_Destroy == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Main_Control_Destroy");
			}

			//User
			_ADL2_User_Settings_Notify = (ADL2_User_Settings_Notify)GetProcAddress(hInstance, "ADL2_User_Settings_Notify");
			if (_ADL2_User_Settings_Notify == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_User_Settings_Notify");
			}

			//Application
			_ADL2_ApplicationProfiles_Applications_Get = (ADL2_ApplicationProfiles_Applications_Get)GetProcAddress(hInstance, "ADL2_ApplicationProfiles_Applications_Get");
			if (_ADL2_ApplicationProfiles_Applications_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_ApplicationProfiles_Applications_Get");
			}

			_ADL2_ApplicationProfiles_RemoveApplication = (ADL2_ApplicationProfiles_RemoveApplication)GetProcAddress(hInstance, "ADL2_ApplicationProfiles_RemoveApplication");
			if (_ADL2_ApplicationProfiles_RemoveApplication == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_ApplicationProfiles_RemoveApplication");
			}

			_ADL2_ApplicationProfiles_ProfileOfAnApplicationX2_Search = (ADL2_ApplicationProfiles_ProfileOfAnApplicationX2_Search)GetProcAddress(hInstance, "ADL2_ApplicationProfiles_ProfileOfAnApplicationX2_Search");
			if (_ADL2_ApplicationProfiles_ProfileOfAnApplicationX2_Search == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_ApplicationProfiles_ProfileOfAnApplicationX2_Search");
			}

			_ADL2_ApplicationProfiles_ProfileApplicationX2_Assign = (ADL2_ApplicationProfiles_ProfileApplicationX2_Assign)GetProcAddress(hInstance, "ADL2_ApplicationProfiles_ProfileApplicationX2_Assign");
			if (_ADL2_ApplicationProfiles_ProfileApplicationX2_Assign == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_ApplicationProfiles_ProfileApplicationX2_Assign");
			}

			_ADL2_ApplicationProfiles_Profile_Create = (ADL2_ApplicationProfiles_Profile_Create)GetProcAddress(hInstance, "ADL2_ApplicationProfiles_Profile_Create");
			if (_ADL2_ApplicationProfiles_Profile_Create == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_ApplicationProfiles_Profile_Create");
			}

			_ADL2_ApplicationProfiles_Profile_Remove = (ADL2_ApplicationProfiles_Profile_Remove)GetProcAddress(hInstance, "ADL2_ApplicationProfiles_Profile_Remove");
			if (_ADL2_ApplicationProfiles_Profile_Remove == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_ApplicationProfiles_Profile_Remove");
			}

			_ADL2_ApplicationProfiles_PropertyType_Get = (ADL2_ApplicationProfiles_PropertyType_Get)GetProcAddress(hInstance, "ADL2_ApplicationProfiles_PropertyType_Get");
			if (_ADL2_ApplicationProfiles_PropertyType_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_ApplicationProfiles_PropertyType_Get");
			}

			_ADL2_ApplicationProfiles_GetCustomization = (ADL2_ApplicationProfiles_GetCustomization)GetProcAddress(hInstance, "ADL2_ApplicationProfiles_GetCustomization");
			if (_ADL2_ApplicationProfiles_GetCustomization == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_ApplicationProfiles_GetCustomization");
			}

			//Registry
			_ADL2_Adapter_RegValueInt_Get = (ADL2_Adapter_RegValueInt_Get)GetProcAddress(hInstance, "ADL2_Adapter_RegValueInt_Get");
			if (_ADL2_Adapter_RegValueInt_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_RegValueInt_Get");
			}

			_ADL2_Adapter_RegValueInt_Set = (ADL2_Adapter_RegValueInt_Set)GetProcAddress(hInstance, "ADL2_Adapter_RegValueInt_Set");
			if (_ADL2_Adapter_RegValueInt_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_RegValueInt_Set");
			}

			_ADL2_Adapter_RegValueString_Get = (ADL2_Adapter_RegValueString_Get)GetProcAddress(hInstance, "ADL2_Adapter_RegValueString_Get");
			if (_ADL2_Adapter_RegValueString_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_RegValueString_Get");
			}

			_ADL2_Adapter_RegValueString_Set = (ADL2_Adapter_RegValueString_Set)GetProcAddress(hInstance, "ADL2_Adapter_RegValueString_Set");
			if (_ADL2_Adapter_RegValueString_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_RegValueString_Set");
			}

			//Adapter
			_ADL2_Adapter_AdapterInfoX3_Get = (ADL2_Adapter_AdapterInfoX3_Get)GetProcAddress(hInstance, "ADL2_Adapter_AdapterInfoX3_Get");
			if (_ADL2_Adapter_AdapterInfoX3_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_AdapterInfoX3_Get");
			}

			_ADL2_Adapter_Active_Get = (ADL2_Adapter_Active_Get)GetProcAddress(hInstance, "ADL2_Adapter_Active_Get");
			if (_ADL2_Adapter_Active_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_Active_Get");
			}

			_ADL2_Adapter_VideoBiosInfo_Get = (ADL2_Adapter_VideoBiosInfo_Get)GetProcAddress(hInstance, "ADL2_Adapter_VideoBiosInfo_Get");
			if (_ADL2_Adapter_VideoBiosInfo_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_VideoBiosInfo_Get");
			}

			_ADL2_Adapter_Accessibility_Get = (ADL2_Adapter_Accessibility_Get)GetProcAddress(hInstance, "ADL2_Adapter_Accessibility_Get");
			if (_ADL2_Adapter_Accessibility_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_Accessibility_Get");
			}

			_ADL2_Adapter_MemoryInfoX4_Get = (ADL2_Adapter_MemoryInfoX4_Get)GetProcAddress(hInstance, "ADL2_Adapter_MemoryInfoX4_Get");
			if (_ADL2_Adapter_MemoryInfoX4_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_MemoryInfoX4_Get");
			}

			_ADL2_GcnAsicInfo_Get = (ADL2_GcnAsicInfo_Get)GetProcAddress(hInstance, "ADL2_GcnAsicInfo_Get");
			if (_ADL2_GcnAsicInfo_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_GcnAsicInfo_Get");
			}

			_ADL2_Adapter_ChipSetInfo_Get = (ADL2_Adapter_ChipSetInfo_Get)GetProcAddress(hInstance, "ADL2_Adapter_ChipSetInfo_Get");
			if (_ADL2_Adapter_ChipSetInfo_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_ChipSetInfo_Get");
			}

			_ADL2_Adapter_ProductName_Get = (ADL2_Adapter_ProductName_Get)GetProcAddress(hInstance, "ADL2_Adapter_ProductName_Get");
			if (_ADL2_Adapter_ProductName_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_ProductName_Get");
			}

			_ADL2_Adapter_ID_Get = (ADL2_Adapter_ID_Get)GetProcAddress(hInstance, "ADL2_Adapter_ID_Get");
			if (_ADL2_Adapter_ID_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_ID_Get");
			}

			//Graphics
			_ADL2_Graphics_VersionsX3_Get = (ADL2_Graphics_VersionsX3_Get)GetProcAddress(hInstance, "ADL2_Graphics_VersionsX3_Get");
			if (_ADL2_Graphics_VersionsX3_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Graphics_VersionsX3_Get");
			}

			_ADL2_FRTCPro_Settings_Get = (ADL2_FRTCPro_Settings_Get)GetProcAddress(hInstance, "ADL2_FRTCPro_Settings_Get");
			if (_ADL2_FRTCPro_Settings_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_FRTCPro_Settings_Get");
			}

			_ADL2_FRTCPro_Settings_Set = (ADL2_FRTCPro_Settings_Set)GetProcAddress(hInstance, "ADL2_FRTCPro_Settings_Set");
			if (_ADL2_FRTCPro_Settings_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_FRTCPro_Settings_Set");
			}

			_ADL2_FPS_Settings_Reset = (ADL2_FPS_Settings_Reset)GetProcAddress(hInstance, "ADL2_FPS_Settings_Reset");
			if (_ADL2_FPS_Settings_Reset == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_FPS_Settings_Reset");
			}

			_ADL2_FPS_Settings_Set = (ADL2_FPS_Settings_Set)GetProcAddress(hInstance, "ADL2_FPS_Settings_Set");
			if (_ADL2_FPS_Settings_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_FPS_Settings_Set");
			}

			_ADL2_FPS_Settings_Get = (ADL2_FPS_Settings_Get)GetProcAddress(hInstance, "ADL2_FPS_Settings_Get");
			if (_ADL2_FPS_Settings_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_FPS_Settings_Get");
			}

			_ADL2_CHILL_SettingsX2_Set = (ADL2_CHILL_SettingsX2_Set)GetProcAddress(hInstance, "ADL2_CHILL_SettingsX2_Set");
			if (_ADL2_CHILL_SettingsX2_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_CHILL_SettingsX2_Set");
			}

			_ADL2_CHILL_SettingsX2_Get = (ADL2_CHILL_SettingsX2_Get)GetProcAddress(hInstance, "ADL2_CHILL_SettingsX2_Get");
			if (_ADL2_CHILL_SettingsX2_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_CHILL_SettingsX2_Get");
			}

			_ADL2_BOOST_SettingsX2_Set = (ADL2_BOOST_SettingsX2_Set)GetProcAddress(hInstance, "ADL2_BOOST_SettingsX2_Set");
			if (_ADL2_BOOST_SettingsX2_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_BOOST_SettingsX2_Set");
			}

			_ADL2_BOOST_Settings_GetX2 = (ADL2_BOOST_Settings_GetX2)GetProcAddress(hInstance, "ADL2_BOOST_Settings_GetX2");
			if (_ADL2_BOOST_Settings_GetX2 == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_BOOST_Settings_GetX2");
			}

			_ADL2_RIS_Settings_Set = (ADL2_RIS_Settings_Set)GetProcAddress(hInstance, "ADL2_RIS_Settings_Set");
			if (_ADL2_RIS_Settings_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_RIS_Settings_Set");
			}

			_ADL2_RIS_Settings_Get = (ADL2_RIS_Settings_Get)GetProcAddress(hInstance, "ADL2_RIS_Settings_Get");
			if (_ADL2_RIS_Settings_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_RIS_Settings_Get");
			}

			_ADL2_RIS_SettingsX2_Set = (ADL2_RIS_SettingsX2_Set)GetProcAddress(hInstance, "ADL2_RIS_SettingsX2_Set");
			if (_ADL2_RIS_SettingsX2_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_RIS_SettingsX2_Set");
			}

			_ADL2_RIS_SettingsX2_Get = (ADL2_RIS_SettingsX2_Get)GetProcAddress(hInstance, "ADL2_RIS_SettingsX2_Get");
			if (_ADL2_RIS_SettingsX2_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_RIS_SettingsX2_Get");
			}

			_ADL2_DELAG_SettingsX2_Set = (ADL2_DELAG_SettingsX2_Set)GetProcAddress(hInstance, "ADL2_DELAG_SettingsX2_Set");
			if (_ADL2_DELAG_SettingsX2_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_DELAG_SettingsX2_Set");
			}

			_ADL2_DELAG_SettingsX2_Get = (ADL2_DELAG_SettingsX2_Get)GetProcAddress(hInstance, "ADL2_DELAG_SettingsX2_Get");
			if (_ADL2_DELAG_SettingsX2_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_DELAG_SettingsX2_Get");
			}

			//Display
			_ADL2_Display_DisplayInfo_Get = (ADL2_Display_DisplayInfo_Get)GetProcAddress(hInstance, "ADL2_Display_DisplayInfo_Get");
			if (_ADL2_Display_DisplayInfo_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_DisplayInfo_Get");
			}

			_ADL2_Display_Property_Get = (ADL2_Display_Property_Get)GetProcAddress(hInstance, "ADL2_Display_Property_Get");
			if (_ADL2_Display_Property_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_Property_Get");
			}

			_ADL2_Display_Property_Set = (ADL2_Display_Property_Set)GetProcAddress(hInstance, "ADL2_Display_Property_Set");
			if (_ADL2_Display_Property_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_Property_Set");
			}

			_ADL2_DFP_GPUScalingEnable_Get = (ADL2_DFP_GPUScalingEnable_Get)GetProcAddress(hInstance, "ADL2_DFP_GPUScalingEnable_Get");
			if (_ADL2_DFP_GPUScalingEnable_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_DFP_GPUScalingEnable_Get");
			}

			_ADL2_DFP_GPUScalingEnable_Set = (ADL2_DFP_GPUScalingEnable_Set)GetProcAddress(hInstance, "ADL2_DFP_GPUScalingEnable_Set");
			if (_ADL2_DFP_GPUScalingEnable_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_DFP_GPUScalingEnable_Set");
			}

			_ADL2_Display_PreservedAspectRatio_Get = (ADL2_Display_PreservedAspectRatio_Get)GetProcAddress(hInstance, "ADL2_Display_PreservedAspectRatio_Get");
			if (_ADL2_Display_PreservedAspectRatio_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_PreservedAspectRatio_Get");
			}

			_ADL2_Display_PreservedAspectRatio_Set = (ADL2_Display_PreservedAspectRatio_Set)GetProcAddress(hInstance, "ADL2_Display_PreservedAspectRatio_Set");
			if (_ADL2_Display_PreservedAspectRatio_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_PreservedAspectRatio_Set");
			}

			_ADL2_Display_ImageExpansion_Get = (ADL2_Display_ImageExpansion_Get)GetProcAddress(hInstance, "ADL2_Display_ImageExpansion_Get");
			if (_ADL2_Display_ImageExpansion_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_ImageExpansion_Get");
			}

			_ADL2_Display_ImageExpansion_Set = (ADL2_Display_ImageExpansion_Set)GetProcAddress(hInstance, "ADL2_Display_ImageExpansion_Set");
			if (_ADL2_Display_ImageExpansion_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_ImageExpansion_Set");
			}

			_ADL2_Display_FreeSyncState_Get = (ADL2_Display_FreeSyncState_Get)GetProcAddress(hInstance, "ADL2_Display_FreeSyncState_Get");
			if (_ADL2_Display_FreeSyncState_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_FreeSyncState_Get");
			}

			_ADL2_Display_FreeSyncState_Set = (ADL2_Display_FreeSyncState_Set)GetProcAddress(hInstance, "ADL2_Display_FreeSyncState_Set");
			if (_ADL2_Display_FreeSyncState_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_FreeSyncState_Set");
			}

			_ADL2_Display_ColorDepth_Get = (ADL2_Display_ColorDepth_Get)GetProcAddress(hInstance, "ADL2_Display_ColorDepth_Get");
			if (_ADL2_Display_ColorDepth_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_ColorDepth_Get");
			}

			_ADL2_Display_ColorDepth_Set = (ADL2_Display_ColorDepth_Set)GetProcAddress(hInstance, "ADL2_Display_ColorDepth_Set");
			if (_ADL2_Display_ColorDepth_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_ColorDepth_Set");
			}

			_ADL2_Display_PixelFormat_Get = (ADL2_Display_PixelFormat_Get)GetProcAddress(hInstance, "ADL2_Display_PixelFormat_Get");
			if (_ADL2_Display_PixelFormat_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_PixelFormat_Get");
			}

			_ADL2_Display_PixelFormat_Set = (ADL2_Display_PixelFormat_Set)GetProcAddress(hInstance, "ADL2_Display_PixelFormat_Set");
			if (_ADL2_Display_PixelFormat_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_PixelFormat_Set");
			}

			_ADL2_Display_Color_Get = (ADL2_Display_Color_Get)GetProcAddress(hInstance, "ADL2_Display_Color_Get");
			if (_ADL2_Display_Color_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_Color_Get");
			}

			_ADL2_Display_Color_Set = (ADL2_Display_Color_Set)GetProcAddress(hInstance, "ADL2_Display_Color_Set");
			if (_ADL2_Display_Color_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_Color_Set");
			}

			_ADL2_Display_ColorTemperatureSource_Get = (ADL2_Display_ColorTemperatureSource_Get)GetProcAddress(hInstance, "ADL2_Display_ColorTemperatureSource_Get");
			if (_ADL2_Display_ColorTemperatureSource_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_ColorTemperatureSource_Get");
			}

			_ADL2_Display_ColorTemperatureSource_Set = (ADL2_Display_ColorTemperatureSource_Set)GetProcAddress(hInstance, "ADL2_Display_ColorTemperatureSource_Set");
			if (_ADL2_Display_ColorTemperatureSource_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_ColorTemperatureSource_Set");
			}

			//Display - Mode
			_ADL2_Display_Modes_Get = (ADL2_Display_Modes_Get)GetProcAddress(hInstance, "ADL2_Display_Modes_Get");
			if (_ADL2_Display_Modes_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_Modes_Get");
			}

			_ADL2_Display_Modes_Set = (ADL2_Display_Modes_Set)GetProcAddress(hInstance, "ADL2_Display_Modes_Set");
			if (_ADL2_Display_Modes_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_Modes_Set");
			}

			_ADL2_Display_PossibleMode_Get = (ADL2_Display_PossibleMode_Get)GetProcAddress(hInstance, "ADL2_Display_PossibleMode_Get");
			if (_ADL2_Display_PossibleMode_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_PossibleMode_Get");
			}

			//Display - CVDC
			_ADL2_Display_CVDC_Get = (ADL2_Display_CVDC_Get)GetProcAddress(hInstance, "ADL2_Display_CVDC_Get");
			if (_ADL2_Display_CVDC_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_CVDC_Get");
			}

			_ADL2_Display_CVDC_Set = (ADL2_Display_CVDC_Set)GetProcAddress(hInstance, "ADL2_Display_CVDC_Set");
			if (_ADL2_Display_CVDC_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_CVDC_Set");
			}

			//Display - Eyefinity
			_ADL2_Display_DisplayMapConfig_Get = (ADL2_Display_DisplayMapConfig_Get)GetProcAddress(hInstance, "ADL2_Display_DisplayMapConfig_Get");
			if (_ADL2_Display_DisplayMapConfig_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_DisplayMapConfig_Get");
			}

			_ADL2_Display_SLSMapIndex_Get = (ADL2_Display_SLSMapIndex_Get)GetProcAddress(hInstance, "ADL2_Display_SLSMapIndex_Get");
			if (_ADL2_Display_SLSMapIndex_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_SLSMapIndex_Get");
			}

			_ADL2_Display_SLSMapIndexList_Get = (ADL2_Display_SLSMapIndexList_Get)GetProcAddress(hInstance, "ADL2_Display_SLSMapIndexList_Get");
			if (_ADL2_Display_SLSMapIndexList_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_SLSMapIndexList_Get");
			}

			_ADL2_Display_SLSMapConfigX2_Get = (ADL2_Display_SLSMapConfig_Get)GetProcAddress(hInstance, "ADL2_Display_SLSMapConfig_Get");
			if (_ADL2_Display_SLSMapConfigX2_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_SLSMapConfigX2_Get");
			}

			_ADL2_Display_SLSMapConfig_Create = (ADL2_Display_SLSMapConfig_Create)GetProcAddress(hInstance, "ADL2_Display_SLSMapConfig_Create");
			if (_ADL2_Display_SLSMapConfig_Create == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_SLSMapConfig_Create");
			}

			_ADL2_Display_SLSMapConfig_Delete = (ADL2_Display_SLSMapConfig_Delete)GetProcAddress(hInstance, "ADL2_Display_SLSMapConfig_Delete");
			if (_ADL2_Display_SLSMapConfig_Delete == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_SLSMapConfig_Delete");
			}

			_ADL2_Display_SLSMapConfigX2_Delete = (ADL2_Display_SLSMapConfigX2_Delete)GetProcAddress(hInstance, "ADL2_Display_SLSMapConfigX2_Delete");
			if (_ADL2_Display_SLSMapConfigX2_Delete == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_SLSMapConfigX2_Delete");
			}

			_ADL2_Display_SLSMapConfig_SetState = (ADL2_Display_SLSMapConfig_SetState)GetProcAddress(hInstance, "ADL2_Display_SLSMapConfig_SetState");
			if (_ADL2_Display_SLSMapConfig_SetState == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_SLSMapConfig_SetState");
			}

			//Display - HDCP
			_ADL2_Display_HDCP_Get = (ADL2_Display_HDCP_Get)GetProcAddress(hInstance, "ADL2_Display_HDCP_Get");
			if (_ADL2_Display_HDCP_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_HDCP_Get");
			}

			_ADL2_Display_HDCP_Set = (ADL2_Display_HDCP_Set)GetProcAddress(hInstance, "ADL2_Display_HDCP_Set");
			if (_ADL2_Display_HDCP_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_HDCP_Set");
			}

			//Display - VariBright
			_ADL2_Adapter_VariBright_Caps = (ADL2_Adapter_VariBright_Caps)GetProcAddress(hInstance, "ADL2_Adapter_VariBright_Caps");
			if (_ADL2_Adapter_VariBright_Caps == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_VariBright_Caps");
			}

			_ADL2_Adapter_VariBrightEnable_Set = (ADL2_Adapter_VariBrightEnable_Set)GetProcAddress(hInstance, "ADL2_Adapter_VariBrightEnable_Set");
			if (_ADL2_Adapter_VariBrightEnable_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_VariBrightEnable_Set");
			}

			_ADL2_Adapter_VariBrightLevel_Get = (ADL2_Adapter_VariBrightLevel_Get)GetProcAddress(hInstance, "ADL2_Adapter_VariBrightLevel_Get");
			if (_ADL2_Adapter_VariBrightLevel_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_VariBrightLevel_Get");
			}

			_ADL2_Adapter_VariBrightLevel_Set = (ADL2_Adapter_VariBrightLevel_Set)GetProcAddress(hInstance, "ADL2_Adapter_VariBrightLevel_Set");
			if (_ADL2_Adapter_VariBrightLevel_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_VariBrightLevel_Set");
			}

			//Display - Color Enhancement
			_ADL2_Display_SCE_State_Set = (ADL2_Display_SCE_State_Set)GetProcAddress(hInstance, "ADL2_Display_SCE_State_Set");
			if (_ADL2_Display_SCE_State_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_SCE_State_Set");
			}

			_ADL2_Display_SCE_State_Get = (ADL2_Display_SCE_State_Get)GetProcAddress(hInstance, "ADL2_Display_SCE_State_Get");
			if (_ADL2_Display_SCE_State_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_SCE_State_Get");
			}

			//Display - HDR State
			_ADL2_Display_HDRState_Get = (ADL2_Display_HDRState_Get)GetProcAddress(hInstance, "ADL2_Display_HDRState_Get");
			if (_ADL2_Display_HDRState_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_HDRState_Get");
			}

			_ADL2_Display_HDRState_Set = (ADL2_Display_HDRState_Set)GetProcAddress(hInstance, "ADL2_Display_HDRState_Set");
			if (_ADL2_Display_HDRState_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_HDRState_Set");
			}

			//Display - HDR Type Preference
			_ADL2_Display_HdrTypePreference_Get = (ADL2_Display_HdrTypePreference_Get)GetProcAddress(hInstance, "ADL2_Display_HdrTypePreference_Get");
			if (_ADL2_Display_HdrTypePreference_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_HdrTypePreference_Get");
			}

			_ADL2_Display_HdrTypePreference_Set = (ADL2_Display_HdrTypePreference_Set)GetProcAddress(hInstance, "ADL2_Display_HdrTypePreference_Set");
			if (_ADL2_Display_HdrTypePreference_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_HdrTypePreference_Set");
			}

			//Display - EDID
			_ADL2_Display_EdidData_Get = (ADL2_Display_EdidData_Get)GetProcAddress(hInstance, "ADL2_Display_EdidData_Get");
			if (_ADL2_Display_EdidData_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_EdidData_Get");
			}

			_ADL2_Display_EdidData_Set = (ADL2_Display_EdidData_Set)GetProcAddress(hInstance, "ADL2_Display_EdidData_Set");
			if (_ADL2_Display_EdidData_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_EdidData_Set");
			}

			//Display - DDC
			_ADL2_Display_DDCInfo2_Get = (ADL2_Display_DDCInfo2_Get)GetProcAddress(hInstance, "ADL2_Display_DDCInfo2_Get");
			if (_ADL2_Display_DDCInfo2_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Display_DDCInfo2_Get");
			}

			//Multimedia
			_ADL2_MMD_Features_Caps = (ADL2_MMD_Features_Caps)GetProcAddress(hInstance, "ADL2_MMD_Features_Caps");
			if (_ADL2_MMD_Features_Caps == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_MMD_Features_Caps");
			}

			_ADL2_MMD_FeatureValues_Set = (ADL2_MMD_FeatureValues_Set)GetProcAddress(hInstance, "ADL2_MMD_FeatureValues_Set");
			if (_ADL2_MMD_FeatureValues_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_MMD_FeatureValues_Set");
			}

			_ADL2_MMD_FeatureValues_Get = (ADL2_MMD_FeatureValues_Get)GetProcAddress(hInstance, "ADL2_MMD_FeatureValues_Get");
			if (_ADL2_MMD_FeatureValues_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_MMD_FeatureValues_Get");
			}

			//Driver
			_ADL2_Driver_Path_Get = (ADL2_Driver_Path_Get)GetProcAddress(hInstance, "ADL2_Driver_Path_Get");
			if (_ADL2_Driver_Path_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Driver_Path_Get");
			}

			//Overdrive
			_ADL2_Overdrive_Caps = (ADL2_Overdrive_Caps)GetProcAddress(hInstance, "ADL2_Overdrive_Caps");
			if (_ADL2_Overdrive_Caps == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Overdrive_Caps");
			}

			_ADL2_Overdrive8_Init_SettingX2_Get = (ADL2_Overdrive8_Init_SettingX2_Get)GetProcAddress(hInstance, "ADL2_Overdrive8_Init_SettingX2_Get");
			if (_ADL2_Overdrive8_Init_SettingX2_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Overdrive8_Init_SettingX2_Get");
			}

			_ADL2_Overdrive8_Current_SettingX2_Get = (ADL2_Overdrive8_Current_SettingX2_Get)GetProcAddress(hInstance, "ADL2_Overdrive8_Current_SettingX2_Get");
			if (_ADL2_Overdrive8_Current_SettingX2_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Overdrive8_Current_SettingX2_Get");
			}

			_ADL2_Overdrive8_Setting_Set = (ADL2_Overdrive8_Setting_Set)GetProcAddress(hInstance, "ADL2_Overdrive8_Setting_Set");
			if (_ADL2_Overdrive8_Setting_Set == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Overdrive8_Setting_Set");
			}

			//Metrics
			_ADL2_New_QueryPMLogData_Get = (ADL2_New_QueryPMLogData_Get)GetProcAddress(hInstance, "ADL2_New_QueryPMLogData_Get");
			if (_ADL2_New_QueryPMLogData_Get == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_New_QueryPMLogData_Get");
			}

			_ADL2_Device_PMLog_Device_Create = (ADL2_Device_PMLog_Device_Create)GetProcAddress(hInstance, "ADL2_Device_PMLog_Device_Create");
			if (_ADL2_Device_PMLog_Device_Create == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Device_PMLog_Device_Create");
			}

			_ADL2_Device_PMLog_Device_Destroy = (ADL2_Device_PMLog_Device_Destroy)GetProcAddress(hInstance, "ADL2_Device_PMLog_Device_Destroy");
			if (_ADL2_Device_PMLog_Device_Destroy == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Device_PMLog_Device_Destroy");
			}

			_ADL2_Adapter_PMLog_Start = (ADL2_Adapter_PMLog_Start)GetProcAddress(hInstance, "ADL2_Adapter_PMLog_Start");
			if (_ADL2_Adapter_PMLog_Start == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_PMLog_Start");
			}

			_ADL2_Adapter_PMLog_Stop = (ADL2_Adapter_PMLog_Stop)GetProcAddress(hInstance, "ADL2_Adapter_PMLog_Stop");
			if (_ADL2_Adapter_PMLog_Stop == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Adapter_PMLog_Stop");
			}

			//Flush
			_ADL2_Flush_Driver_Data = (ADL2_Flush_Driver_Data)GetProcAddress(hInstance, "ADL2_Flush_Driver_Data");
			if (_ADL2_Flush_Driver_Data == NULL)
			{
				//Set result
				AVDebugWriteLine("Failed to init _ADL2_Flush_Driver_Data");
			}

			//Create ADL main control
			adl_Res0 = _ADL2_Main_Control_Create(ADL_MemoryAlloc_Main, 1, &adl_Context);
			if (adl_Res0 != ADL_OK)
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