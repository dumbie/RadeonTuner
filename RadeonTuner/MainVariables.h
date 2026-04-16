#pragma once
#include "pch.h"

inline bool disable_picking = true;
inline bool disable_saving = true;
inline bool disable_saving_settings = true;
inline bool radeon_Chill_Linked = false;

inline std::wstring gpuRegistryPath;
inline std::wstring gpuUniqueIdentifierHex;
inline int gpuUniqueIdentifier = -1;

inline bool adlx_Bool = false;
inline ADLX_RESULT adlx_Res0 = ADLX_FAIL;
inline ADLX_RESULT adlx_Res1 = ADLX_FAIL;
inline ADLX_IntRange adlx_IntRange0 = { 0, 0, 0 };
inline ADLX_IntRange adlx_IntRange1 = { 0, 0, 0 };
inline int adlx_Int0 = 0;
inline int adlx_Int1 = 0;
inline int adlx_Int2 = 0;
inline int adlx_Int3 = 0;
inline int adlx_Int4 = 0;
inline int adlx_Int5 = 0;

inline ADLXHelper ppADLXHelper;
inline IADLMapping* ppAdlMapping;

inline IADLXGPU2Ptr ppGpuInfo;
inline IADLXGPUListPtr ppGpuList;
inline IADLXDisplayPtr ppDisplayInfo;
inline IADLXDisplayListPtr ppDisplayList;

inline IADLXDisplayServices3Ptr ppDispServices;
inline IADLXMultimediaServicesPtr ppMultiMediaServices;
inline IADLX3DSettingsServices2Ptr pp3DSettingsServices;
inline IADLXPerformanceMonitoringServicesPtr ppPerformanceMonitoringServices;
inline IADLXPowerTuningServices1Ptr ppPowerTuningServices;
inline IADLXGPUTuningServices1Ptr ppGPUTuningServices;

inline int adl_Display_AdapterIndex = -1;
inline int adl_Display_DisplayIndex = -1;
inline int adl_Gpu_AdapterIndex = -1;
inline int adl_Res0 = ADL_ERR;

inline ADL_CONTEXT_HANDLE adl_Context = NULL;

//Fix use ObservableCollection instead
inline std::vector<std::wstring> powerBoostAppsCache{};
inline std::vector<TuningFanSettings> tuningFanSettingsCache{};

inline int adl_AppSelectedIndex = -1;
inline std::vector<AdlApplication> adl_Apps{};

//Fix replace with C++26 std::optional<T&>
inline AdlApplication& adl_AppSelected()
{
	if (adl_Apps.size() > 0 && adl_AppSelectedIndex >= 0)
	{
		return adl_Apps[adl_AppSelectedIndex];
	}
	else
	{
		static AdlApplication adlApplicationDefaults{};
		return adlApplicationDefaults;
	}
}