#pragma once
#include "pch.h"

//namespace ADLXVariables
//{
inline bool disable_saving = true;

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
inline IADLXGPU2Ptr ppGpuInfo;
inline IADLXGPUListPtr ppGpuList;
inline IADLXDisplayPtr ppDisplayInfo;
inline IADLXDisplayListPtr ppDisplayList;
inline IADLXDisplayServices3Ptr ppDispServices;
inline IADLXMultimediaServicesPtr ppMultiMediaServices;
inline IADLX3DSettingsServices2Ptr pp3DSettingsServices;
inline IADLXPerformanceMonitoringServicesPtr ppPerformanceMonitoringServices;
inline IADLXGPUTuningServices1Ptr ppGPUTuningServices;
//}