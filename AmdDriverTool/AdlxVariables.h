#pragma once
#include "pch.h"

//namespace ADLXVariables
//{
inline bool disable_saving = true;

inline bool adxl_Bool = false;
inline ADLX_IntRange adxl_IntRange = { 0, 0, 0 };
inline int adxl_Int0 = 0;
inline int adxl_Int1 = 0;
inline int adxl_Int2 = 0;
inline int adxl_Int3 = 0;
inline int adxl_Int4 = 0;
inline int adxl_Int5 = 0;
inline ADLX_RESULT res = ADLX_FAIL;

inline ADLXHelper g_ADLXHelp;
inline IADLXGPU2Ptr gpuInfo;
inline IADLXGPUListPtr gpuList;
inline IADLXDisplayPtr displayInfo;
inline IADLXDisplayListPtr displayList;
inline IADLXDisplayServicesPtr displayService;
inline IADLX3DSettingsServicesPtr d3dSettingSrv;
inline IADLXPerformanceMonitoringServicesPtr perfMonitoringService;
inline IADLXGPUTuningServices1Ptr gpuTuningService;
inline IADLXManualFanTuningPtr manualFanTuning;
//}