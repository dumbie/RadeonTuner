///
///  Copyright (c) 2008 - 2013 Advanced Micro Devices, Inc.

///  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
///  EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
///  WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.

/// \file oem_display.h
/// \brief Contains all customer display-related functions exposed by ADL for \ALL platforms.
///
/// This file contains all OEM or other customer display-related functions exposed by ADL for \ALL platforms.
/// All functions found in this file can be used as a reference to ensure
/// the specified function pointers can be used by the appropriate runtime
/// dynamic library loaders. This header file not for public release.

#ifndef OEM_DISPLAY_H_
#define OEM_DISPLAY_H_

#ifndef ADL_EXTERNC
#ifdef __cplusplus
#define ADL_EXTERNC extern "C"
#else
#define ADL_EXTERNC
#endif
#endif

#include "oem_structures.h"

/// \addtogroup DISPLAY
// @{
///\brief Function to retrieve the overlay OEM matrix.
/// 
/// This function retrieves the overlay OEM matrix.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index, which can be retrieved from the ADLDisplayInfo data structure.
/// \param[in]   iMatrixType The value storing the matrix type.
/// \param[out]  lpGamutMatrix The pointer to structure storing the retrieved overlay OEM matrix.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_GamutMapping_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int iMatrixType, ADLDisplayGamutMatrix* lpGamutMatrix);

///\brief Function to retrieve the overlay OEM matrix.
/// 
/// This function retrieves the overlay OEM matrix.
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index, which can be retrieved from the ADLDisplayInfo data structure.
/// \param[in]   iMatrixType The value storing the matrix type.
/// \param[out]  lpGamutMatrix The pointer to structure storing the retrieved overlay OEM matrix.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
ADL_EXTERNC int EXPOSED ADL_Display_GamutMapping_Get(int iAdapterIndex, int iDisplayIndex, int iMatrixType, ADLDisplayGamutMatrix* lpGamutMatrix);

///
///\brief Function to set the overlay OEM matrix.
/// 
/// This function sets the overlay OEM matrix.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index, which can be retrieved from the ADLDisplayInfo data structure.
/// \param[in]   iMatrixType The value storing the matrix type
/// \param[in]  lpGamutMatrix The pointer to the structure used to set overlay OEM matrix.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_GamutMapping_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int iMatrixType, ADLDisplayGamutMatrix* lpGamutMatrix);

///
///\brief Function to set the overlay OEM matrix.
/// 
/// This function sets the overlay OEM matrix.
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index, which can be retrieved from the ADLDisplayInfo data structure.
/// \param[in]   iMatrixType The value storing the matrix type
/// \param[in]  lpGamutMatrix The pointer to the structure used to set overlay OEM matrix.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
ADL_EXTERNC int EXPOSED ADL_Display_GamutMapping_Set(int iAdapterIndex, int iDisplayIndex, int iMatrixType, ADLDisplayGamutMatrix* lpGamutMatrix);

///
/// \brief Function to reset the overlay OEM matrix.
/// 
/// This function resets the overlay OEM matrix.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index, which can be retrieved from the ADLDisplayInfo data structure.
/// \param[in]   iMatrixType The matrix type.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_GamutMapping_Reset(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int iMatrixType);

///
/// \brief Function to reset the overlay OEM matrix.
/// 
/// This function resets the overlay OEM matrix.
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index, which can be retrieved from the ADLDisplayInfo data structure.
/// \param[in]   iMatrixType The matrix type.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
ADL_EXTERNC int EXPOSED ADL_Display_GamutMapping_Reset(int iAdapterIndex, int iDisplayIndex, int iMatrixType);

///
/// \brief Function to read/write native AUX channel of DP display 
///
/// This function reads or writes native AUX channel of DP display
/// \platform 
/// \ALL 
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in, out] lpData The pointer to the ADLDisplayNativeAUXChannelData strurcture.
///                 Defines how to set/get the data to/from the native aux channel of DP display.
///                 If the function return ADL_OK, check ADLDisplayNativeAUXChannelData.iAuxStatus for result status. 
///                 The value can be any ADL_ERR_AUX_FAILED_xxxx. Only \ref ADL_DISPLAY_AUX_STATUS_SUCESSFUL means the command is successful.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_NativeAUXChannel_Access(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLDisplayNativeAUXChannelData* lpData);

///
/// \brief Function to read/write native AUX channel of DP display 
///
/// This function reads or writes native AUX channel of DP display
/// \platform 
/// \ALL 
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in, out] lpData The pointer to the ADLDisplayNativeAUXChannelData strurcture.
///                 Defines how to set/get the data to/from the native aux channel of DP display.
///                 If the function return ADL_OK, check ADLDisplayNativeAUXChannelData.iAuxStatus for result status. 
///                 The value can be any ADL_ERR_AUX_FAILED_xxxx. Only \ref ADL_DISPLAY_AUX_STATUS_SUCESSFUL means the command is successful.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. 
ADL_EXTERNC int EXPOSED ADL_Display_NativeAUXChannel_Access(int iAdapterIndex, int iDisplayIndex, ADLDisplayNativeAUXChannelData* lpData);

///
/// \brief Function to get the Pixel Clock Capabilities 
///
/// This function reads the Pixel Clock Capabilities
/// \platform 
/// \ALL 
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in, out] lpPixelClockCaps The pointer to the ADLPixelClockCaps strurcture.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_PixelClockCaps_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLPixelClockCaps* lpPixelClockCaps);

///
/// \brief Function to get the Pixel Clock Capabilities 
///
/// This function reads the Pixel Clock Capabilities
/// \platform 
/// \ALL 
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in, out] lpPixelClockCaps The pointer to the ADLPixelClockCaps strurcture.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. 
ADL_EXTERNC int EXPOSED ADL_Display_PixelClockCaps_Get(int iAdapterIndex, int iDisplayIndex, ADLPixelClockCaps* lpPixelClockCaps);

///
/// \brief Function to get the Current Pixel Clocks
///
/// This function reads the Current Pixel Clocks
/// \platform 
/// \ALL 
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in, out] lpCurrentPixelClock The pointer to the ADLCurrentPixelClock strurcture.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_CurrentPixelClock_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLCurrentPixelClock* lpCurrentPixelClock);

///
/// \brief Function to get the Current Pixel Clocks
///
/// This function reads the Current Pixel Clocks
/// \platform 
/// \ALL 
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in, out] lpCurrentPixelClock The pointer to the ADLCurrentPixelClock strurcture.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. 
ADL_EXTERNC int EXPOSED ADL_Display_CurrentPixelClock_Get(int iAdapterIndex, int iDisplayIndex, ADLCurrentPixelClock* lpCurrentPixelClock);

///
/// \brief Function to set the Pixel Clock Allowable Range 
///
/// This function writes the Pixel Clock Allowable Range 
/// \platform 
/// \ALL 
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in, out] lpPixelClockRange The pointer to the ADLPixelClockRange strurcture.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code.
/// 
/// \remarks Call ADL_Flush_Driver_Data() after to persist settings on reboot.
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_PixelClockAllowableRange_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLPixelClockRange* lpPixelClockRange);

///
/// \brief Function to set the Pixel Clock Allowable Range 
///
/// This function writes the Pixel Clock Allowable Range 
/// \platform 
/// \ALL 
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in, out] lpPixelClockRange The pointer to the ADLPixelClockRange strurcture.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code.
/// 
/// \remarks Call ADL_Flush_Driver_Data() after to persist settings on reboot.
ADL_EXTERNC int EXPOSED ADL_Display_PixelClockAllowableRange_Set(int iAdapterIndex, int iDisplayIndex, ADLPixelClockRange* lpPixelClockRange);

///
/// \brief Function to get the brightness information of monitor.
///
/// This function gets the brightness information of monitor.
/// \platform 
/// \ALL 
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[out] piCurrent The pointer to the data to get the current brightness of monitor.
/// \param[out] piMax The pointer to the data to get the max brightness of monitor.
/// \param[out] piMax The pointer to the data to get the min brightness of monitor.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code.
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_BackLight_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int* piCurrent, int* piMax, int* piMin);

///
/// \brief Function to get the brightness information of monitor.
///
/// This function gets the brightness information of monitor.
/// \platform 
/// \ALL 
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[out] piCurrent The pointer to the data to get the current brightness of monitor.
/// \param[out] piMax The pointer to the data to get the max brightness of monitor.
/// \param[out] piMax The pointer to the data to get the min brightness of monitor.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code.
ADL_EXTERNC int EXPOSED ADL_Display_BackLight_Get(int iAdapterIndex, int iDisplayIndex, int* piCurrent, int* piMax, int* piMin);

///
/// \brief Function to Set the brightness information of monitor.
///
/// This function sets the brightness information of monitor.
/// \platform 
/// \ALL 
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in] iValue The data to set the brightness of monitor.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code.
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_BackLight_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int iValue);

///
/// \brief Function to Set the brightness information of monitor.
///
/// This function sets the brightness information of monitor.
/// \platform 
/// \ALL 
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in] iValue The data to set the brightness of monitor.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code.
ADL_EXTERNC int EXPOSED ADL_Display_BackLight_Set(int iAdapterIndex, int iDisplayIndex, int iValue);

///
/// \brief Function to write and read large I2C packets up to \ref ADL_DL_I2C_MAXLARGEPAYLOADSIZE
/// 
/// This function writes and reads I2C.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in,out]  plI2C A pointer to the ADLI2CLargePayload structure.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_WriteAndReadI2CLargePayload(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLI2CLargePayload* plI2C);

///
/// \brief Function to write and read large I2C packets up to \ref ADL_DL_I2C_MAXLARGEPAYLOADSIZE
/// 
/// This function writes and reads I2C.
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in,out]  plI2C A pointer to the ADLI2CLargePayload structure.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
ADL_EXTERNC int EXPOSED ADL_Display_WriteAndReadI2CLargePayload(int iAdapterIndex, ADLI2CLargePayload* plI2C);


///
/// \brief Function for customer ADL API
///
/// This function exposes various driver functionality for customer request.
/// \platform
/// \ALL
/// \param[in]     iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]     iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in/out] pInfo A pointer to ADLRCCommand
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code.
ADL_EXTERNC int EXPOSED ADL_Display_RcDisplayAdjustment(int iAdapterIndex,
	int iDisplayIndex,
	ADLRcCommand* pInfo);

///
/// \brief Function for customer ADL API
///
/// \platform
/// \ALL
/// \param[in]     context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]     iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in/out] pInfo A pointer to ADLRcCommand.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_RcDisplayAdjustment(ADL_CONTEXT_HANDLE context,
	int iAdapterIndex,
	int iDisplayIndex,
	ADLRcCommand* pInfo);

///
///\brief Function to set the display monitor power state.
/// 
/// This function sets the display monitor power state on given adapter.
/// \platform
/// \VISTAWIN7  
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in]   nState The desired monitor power state to be set.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks
/// -# This API is only expected to be called when the Monitor is already be driven by the adapter (adapter attaches to desktop)
///	   - If the Adapter (referred by iAdapterIndex) is active (attached to a desktop), but Monitor is currently NOT driven by the GPU, this API will not do anything to the monitor, and API may still return \ref ADL_OK
///	   - If the Adapter (referred by iAdapterIndex) is NOT active (does not attach to a desktop), API may fail and return \ref ADL_ERR
/// \n\n
/// -# Power ON/OFF the monitor while the Monitor is already at ON/OFF state
///    - If Monitor is currently ON, and client calls this API to try Power-ON the monitor, this API will return \ref ADL_OK. User may experience a flash on some monitor because of Display Engine may be power-cycle-toggled. 
///    - If Monitor is currently OFF, and client calls this API to try Power-OFF the monitor, this API will return \ref ADL_OK
/// \n\n
/// -# Power ON the monitor while the Monitor is in time-out (power-saving) state
///    - If Monitor is currently time-out (powered-off by the OS), client calls this API to Power-ON the monitor, driver will Power-ON the monitor, and API will return \ref ADL_OK
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_MonitorPowerState_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADL_Display_MonitorPowerState nState);

///
///\brief Function to set the display monitor power state.
/// 
/// This function sets the display monitor power state on given adapter.
/// \platform
/// \VISTAWIN7  
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in]   nState The desired monitor power state to be set.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks
/// -# This API is only expected to be called when the Monitor is already be driven by the adapter (adapter attaches to desktop)
///	   - If the Adapter (referred by iAdapterIndex) is active (attached to a desktop), but Monitor is currently NOT driven by the GPU, this API will not do anything to the monitor, and API may still return \ref ADL_OK
///	   - If the Adapter (referred by iAdapterIndex) is NOT active (does not attach to a desktop), API may fail and return \ref ADL_ERR
/// \n\n
/// -# Power ON/OFF the monitor while the Monitor is already at ON/OFF state
///    - If Monitor is currently ON, and client calls this API to try Power-ON the monitor, this API will return \ref ADL_OK. User may experience a flash on some monitor because of Display Engine may be power-cycle-toggled. 
///    - If Monitor is currently OFF, and client calls this API to try Power-OFF the monitor, this API will return \ref ADL_OK
/// \n\n
/// -# Power ON the monitor while the Monitor is in time-out (power-saving) state
///    - If Monitor is currently time-out (powered-off by the OS), client calls this API to Power-ON the monitor, driver will Power-ON the monitor, and API will return \ref ADL_OK
ADL_EXTERNC int EXPOSED ADL_Display_MonitorPowerState_Set(int iAdapterIndex, int iDisplayIndex, ADL_Display_MonitorPowerState nState);


///
///\brief Function to retrieve current display mode timing override information.
/// 
/// This function retrieves current display mode timing override information for a specified display.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   displayID The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[out]  lpModeInfoOut The pointer to the ADLDisplayModeInfo structure storing the retrieved display mode information.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_TargetTiming_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLDisplayID displayID, ADLDisplayModeInfo* lpModeInfoOut);


///
///\brief Function to retrieve current display mode timing override information.
/// 
/// This function retrieves current display mode timing override information for a specified display.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   displayID The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[out]  lpModeInfoOut The pointer to the ADLDisplayModeInfo structure storing the retrieved display mode information.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_TargetTimingX2_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLDisplayID displayID, ADLDisplayModeInfoX2* lpModeInfoOut);

///
///\brief Function to retrieve current display mode timing override information.
/// 
/// This function retrieves current display mode timing override information for a specified display.
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   displayID The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[out]  lpModeInfoOut The pointer to the ADLDisplayModeInfo structure storing the retrieved display mode information.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
ADL_EXTERNC int EXPOSED ADL_Display_TargetTiming_Get(int iAdapterIndex, ADLDisplayID displayID, ADLDisplayModeInfo* lpModeInfoOut);

///
///\brief Function to set display mode timing override information.
/// 
/// This function sets display mode timing override information for a specified display.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in]   lpMode The pointer to the ADLDisplayModeInfo structure which sets the display mode timing override information.
/// \param[in]   iForceUpdate The value which forces the update of the timing override information.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// 
/// \remarks Call ADL_Flush_Driver_Data() after to persist settings on reboot.
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_ModeTimingOverrideX2_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLDisplayModeInfoX2* lpMode, int iForceUpdate);

///
///\brief Function to retrieve display mode timing override information.
/// 
/// This function retrieves display mode timing override information for a specified display.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   displayID The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in]   lpModeIn The pointer to the ADLDisplayMode structure storing the desired display mode.
/// \param[out]  lpModeInfoOut The pointer to the ADLDisplayModeInfo structure storing the retrieved display mode information.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_ModeTimingOverrideX3_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLDisplayID displayID, ADLDisplayModeX2* lpModeIn, ADLDisplayModeInfoX2* lpModeInfoOut);

///
///\brief Function to get the display mode timing override list.
/// 
/// This function retrieves display mode timing override list.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   displayID The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[out]  lpNumOfModes The pointer to the actual number of the retrieved overridden modes.
/// \param[out]  lpModeInfoList The pointer to the retrieved ADLDisplayModeInfo structure. This pointer must be allocated by the user.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_ModeTimingOverrideListX3_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLDisplayID displayID, int* lpNumOfModes, ADLDisplayModeInfoX2** lpModeInfoList);

// @}


///\ingroup DISPLAYAPI
///\defgroup SPLITAPIS Split Display APIs
/// This group outlines the Split Display related APIs.

/// \addtogroup SPLITAPIS
///
// @{

#if defined (_WIN32) || defined(_WIN64)



///
/// \brief Function to retrieve the current Split Display setting for the input display. (Win7).
/// 
/// This function retrieves the Split Display capabilities and settings base on the input display ID.
/// \platform
/// \Win7
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in] iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in] displayID The display IDs. Refer to the ADLDisplayID structure for more information. 
/// \param[out] lpSplitDisplayCaps The pointer to the retrieved Split Display capabilities. Refer to the ADLSplitDisplayCaps structure for more information. 
/// \param[out] lpCurrentState The pointer to the retrieved the current Split Display state which is enable or disable. Refer to the ADLSplitDisplayState structure for more information. 
/// \param[out] lpCurrentMode The pointer to the retrieved the current Split Display mode which is 4:3 Left or 1:1. Refer to the ADLSplitDisplayMode structure for more information. 
/// \param[out] lpCurrentType The pointer to the retrieved the current Split Display type. Refer to the ADLSplitDisplayType structure for more information. 
/// \param[out] lpNumSiblingType The pointer to the retrieved the the number of sibling type usually one.
/// \param[out] lppSiblingType The pointer to the pointer to the retrieved array of sibling types. Refer to the ADLSplitDisplayType structure for more information. 
/// \param[out] lpDefaultState The pointer to the retrieved the defalut Split Display state which is enable or disable. Refer to the ADLSplitDisplayState structure for more information. 
/// \param[out] lpDefaultMode The pointer to the retrieved the default Split Display mode which is 4:3 Left or 1:1. Refer to the ADLSplitDisplayMode structure for more information. 
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks	This API is in Prototype stage. Do not use for shipping products!
///				Application must free the memory after calling this function.
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_SplitDisplay_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex,
	ADLDisplayID displayID,
	ADLSplitDisplayCaps* lpSplitDisplayCaps,
	ADLSplitDisplayState* lpCurrentState,
	ADLSplitDisplayMode* lpCurrentMode,
	ADLSplitDisplayType* lpCurrentType,
	int* lpNumSiblingType,
	ADLSplitDisplayType** lppSiblingType,
	ADLSplitDisplayState* lpDefaultState,
	ADLSplitDisplayMode* lpDefaultMode);

///
/// \brief Function to retrieve the current Split Display setting for the input display. (Win7).
/// 
/// This function retrieves the Split Display capabilities and settings base on the input display ID.
/// \platform
/// \Win7
/// \param[in] iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in] displayID The display IDs. Refer to the ADLDisplayID structure for more information. 
/// \param[out] lpSplitDisplayCaps The pointer to the retrieved Split Display capabilities. Refer to the ADLSplitDisplayCaps structure for more information. 
/// \param[out] lpCurrentState The pointer to the retrieved the current Split Display state which is enable or disable. Refer to the ADLSplitDisplayState structure for more information. 
/// \param[out] lpCurrentMode The pointer to the retrieved the current Split Display mode which is 4:3 Left or 1:1. Refer to the ADLSplitDisplayMode structure for more information. 
/// \param[out] lpCurrentType The pointer to the retrieved the current Split Display type. Refer to the ADLSplitDisplayType structure for more information. 
/// \param[out] lpNumSiblingType The pointer to the retrieved the the number of sibling type usually one.
/// \param[out] lppSiblingType The pointer to the pointer to the retrieved array of sibling types. Refer to the ADLSplitDisplayType structure for more information. 
/// \param[out] lpDefaultState The pointer to the retrieved the defalut Split Display state which is enable or disable. Refer to the ADLSplitDisplayState structure for more information. 
/// \param[out] lpDefaultMode The pointer to the retrieved the default Split Display mode which is 4:3 Left or 1:1. Refer to the ADLSplitDisplayMode structure for more information. 
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks	This API is in Prototype stage. Do not use for shipping products!
///				Application must free the memory after calling this function.

ADL_EXTERNC int EXPOSED ADL_Display_SplitDisplay_Get(int iAdapterIndex,
	ADLDisplayID displayID,
	ADLSplitDisplayCaps* lpSplitDisplayCaps,
	ADLSplitDisplayState* lpCurrentState,
	ADLSplitDisplayMode* lpCurrentMode,
	ADLSplitDisplayType* lpCurrentType,
	int* lpNumSiblingType,
	ADLSplitDisplayType** lppSiblingType,
	ADLSplitDisplayState* lpDefaultState,
	ADLSplitDisplayMode* lpDefaultMode);


///
/// \brief Function to set the current Split Display settings for the input display. (Win7).
/// 
/// This function allows user to enable or disable Split Display. In addition, it allows user to set the Split Display mode.
/// Make sure to disable related extended/cloned display devices before enabling Split display mode.
/// \platform
/// \Win7
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in] iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in] displayID The display IDs. Refer to the ADLDisplayID structure for more information. 
/// \param[in] currentState The current Split Display state which is enable or disable to be set. Refer to the ADLSplitDisplayState structure for more information. 
/// \param[in] currentMode The current Split Display mode which is 4:3 Left or 1:1 to be set. Refer to the ADLSplitDisplayMode structure for more information. 
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks	This API is in Prototype stage. Do not use for shipping products!
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_SplitDisplay_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex,
	ADLDisplayID displayID,
	ADLSplitDisplayState currentState,
	ADLSplitDisplayMode currentMode);

///
/// \brief Function to set the current Split Display settings for the input display. (Win7).
/// 
/// This function allows user to enable or disable Split Display. In addition, it allows user to set the Split Display mode.
/// Make sure to disable related extended/cloned display devices before enabling Split display mode.
/// \platform
/// \Win7
/// \param[in] iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in] displayID The display IDs. Refer to the ADLDisplayID structure for more information. 
/// \param[in] currentState The current Split Display state which is enable or disable to be set. Refer to the ADLSplitDisplayState structure for more information. 
/// \param[in] currentMode The current Split Display mode which is 4:3 Left or 1:1 to be set. Refer to the ADLSplitDisplayMode structure for more information. 
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks	This API is in Prototype stage. Do not use for shipping products!
ADL_EXTERNC int EXPOSED ADL_Display_SplitDisplay_Set(int iAdapterIndex,
	ADLDisplayID displayID,
	ADLSplitDisplayState currentState,
	ADLSplitDisplayMode currentMode);




///
/// \brief Function to check the current desktop configuration if it is valid for Split Display. (Win7).
/// 
/// This function checks the current desktop configuration to see it is valid for Split Display. 
/// If it is not a valid desktop configuration, this function will restore the desktop configuration.
/// \platform
/// \Win7
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in] iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in] displayID The display IDs. Refer to the ADLDisplayID structure for more information. 
/// \param[out] lpResultMask The result mask value. Refer to ADL_DISPLAY_SPLITDISPLAY_DESKTOPCONFIGURATION_XXX.
/// \param[out] lpResultValue Result after the Restore Desktop Configuration. Refer to ADL_DISPLAY_SPLITDISPLAY_DESKTOPCONFIGURATION_XXX.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks	This API is in Prototype stage. Do not use for shipping products!
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_SplitDisplay_RestoreDesktopConfiguration(ADL_CONTEXT_HANDLE context, int iAdapterIndex,
	ADLDisplayID displayID,
	int* lpResultMask,
	int* lpResultValue);

///
/// \brief Function to check the current desktop configuration if it is valid for Split Display. (Win7).
/// 
/// This function checks the current desktop configuration to see it is valid for Split Display. 
/// If it is not a valid desktop configuration, this function will restore the desktop configuration.
/// \platform
/// \Win7
/// \param[in] iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in] displayID The display IDs. Refer to the ADLDisplayID structure for more information. 
/// \param[out] lpResultMask The result mask value. Refer to ADL_DISPLAY_SPLITDISPLAY_DESKTOPCONFIGURATION_XXX.
/// \param[out] lpResultValue Result after the Restore Desktop Configuration. Refer to ADL_DISPLAY_SPLITDISPLAY_DESKTOPCONFIGURATION_XXX.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks	This API is in Prototype stage. Do not use for shipping products!
ADL_EXTERNC int EXPOSED ADL_Display_SplitDisplay_RestoreDesktopConfiguration(int iAdapterIndex,
	ADLDisplayID displayID,
	int* lpResultMask,
	int* lpResultValue);



///
/// \brief Function to check the adapter if it supports Split Display. (Win7).
/// 
/// This function checks the adapter if it supports Split Display. 
/// If it doesn't support split display, the caller can avoid further actions (i.e. checking each display for this adapter).
/// \platform
/// \Win7
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in] iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out] lpResultMask The result mask value. Refer to ADL_DISPLAY_SPLITDISPLAY_CAPS_SUPPORTED.
/// \param[out] lpResultValue Result. Refer to ADL_DISPLAY_SPLITDISPLAY_CAPS_SUPPORTED.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks	This API is in Prototype stage. Do not use for shipping products!
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_SplitDisplay_Caps(ADL_CONTEXT_HANDLE context, int iAdapterIndex,
	int* lpResultMask,
	int* lpResultValue);

///
/// \brief Function to check the adapter if it supports Split Display. (Win7).
/// 
/// This function checks the adapter if it supports Split Display. 
/// If it doesn't support split display, the caller can avoid further actions (i.e. checking each display for this adapter).
/// \platform
/// \Win7
/// \param[in] iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out] lpResultMask The result mask value. Refer to ADL_DISPLAY_SPLITDISPLAY_CAPS_SUPPORTED.
/// \param[out] lpResultValue Result. Refer to ADL_DISPLAY_SPLITDISPLAY_CAPS_SUPPORTED.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks	This API is in Prototype stage. Do not use for shipping products!
ADL_EXTERNC int EXPOSED ADL_Display_SplitDisplay_Caps(int iAdapterIndex,
	int* lpResultMask,
	int* lpResultValue);



///
///\brief Function to get the packet information. \b HDMI \b only
/// 
/// This function retrieves the packet information.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[out]  lpInfoPacket The pointer to structure storing the retrieved the packet information.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_InfoPacket_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLDisplayDataPacket* lpInfoPacket);

///
///\brief Function to get the packet information. \b HDMI \b only
/// 
/// This function retrieves the packet information.
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[out]  lpInfoPacket The pointer to structure storing the retrieved the packet information.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
ADL_EXTERNC int EXPOSED ADL_Display_InfoPacket_Get(int iAdapterIndex, int iDisplayIndex, ADLDisplayDataPacket* lpInfoPacket);


///
///\brief Function to set the packet information. \b HDMI \b only
/// 
/// This function sets the packet information.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in]   lpInfoPacket The pointer to the structure that sets the packet information.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_InfoPacket_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLDisplayDataPacket* lpInfoPacket);

///
///\brief Function to set the packet information. \b HDMI \b only
/// 
/// This function sets the packet information.
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in]   lpInfoPacket The pointer to the structure that sets the packet information.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
ADL_EXTERNC int EXPOSED ADL_Display_InfoPacket_Set(int iAdapterIndex, int iDisplayIndex, ADLDisplayDataPacket* lpInfoPacket);

#endif


// @}


/// \addtogroup COLOR
///
// @{

///\brief Function to get the current ADLGamutInfo setting for the display. 
/// This function get the ADLGamutInfo setting for a specified display.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[in ]  gamut         The gamut reference - whether it is related to graphics or video, source or destination
/// \param[out]  ADLGamutInfo  driver supplies the mask of supported gamut spaces and white points, driver supports this feature from NI ASIC.
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_Gamut_Caps(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLGamutReference gamut, ADLGamutInfo* lpCap);

///\brief Function to get the current ADLGamutInfo setting for the display. 
/// This function get the ADLGamutInfo setting for a specified display.
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[in ]  gamut         The gamut reference - whether it is related to graphics or video, source or destination
/// \param[out]  ADLGamutInfo  driver supplies the mask of supported gamut spaces and white points, driver supports this feature from NI ASIC.
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
ADL_EXTERNC int EXPOSED ADL_Display_Gamut_Caps(int iAdapterIndex, int iDisplayIndex, ADLGamutReference gamut, ADLGamutInfo* lpCap);

///\brief Function to get the current ADLGamutData setting for the display. 
/// This function get the ADLGamutData setting for a specified display.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[in ]  gamut       . The gamut reference - whether it is related to graphics or video, source or destination
/// \param[out]  ADLGamutData  driver supplies the currently used gamut, driver supports this feature from NI ASIC.
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_Gamut_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLGamutReference gamut, ADLGamutData* lpSource);

///\brief Function to get the current ADLGamutData setting for the display. 
/// This function get the ADLGamutData setting for a specified display.
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[in ]  gamut       . The gamut reference - whether it is related to graphics or video, source or destination
/// \param[out]  ADLGamutData  driver supplies the currently used gamut, driver supports this feature from NI ASIC.
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
ADL_EXTERNC int EXPOSED ADL_Display_Gamut_Get(int iAdapterIndex, int iDisplayIndex, ADLGamutReference gamut, ADLGamutData* lpSource);

///\brief Function to set the current ADLGamutData setting for the display. 
/// This function sets the ADLGamutData setting for a specified display.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[in ]  gamut         The gamut reference - whether it is related to graphics or video, source or destination
/// \param[in ]  ADLGamutData  to be set, the method sets the new gamut or saves the requested gamut if the current destination if gamut from EDID.
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_Gamut_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLGamutReference gamut, const ADLGamutData* lpSource);

///\brief Function to set the current ADLGamutData setting for the display. 
/// This function sets the ADLGamutData setting for a specified display.
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[in ]  gamut         The gamut reference - whether it is related to graphics or video, source or destination
/// \param[in ]  ADLGamutData  to be set, the method sets the new gamut or saves the requested gamut if the current destination if gamut from EDID.
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
ADL_EXTERNC int EXPOSED ADL_Display_Gamut_Set(int iAdapterIndex, int iDisplayIndex, ADLGamutReference gamut, const ADLGamutData* lpSource);

/// DEPRECATED - Replaced with ADL_Display_RegammaR1_Set
/// \brief 
/// \Function to set requested re gamma coefficients setting for the display. 
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[in ]  lpRegamma coefficients to be used to build the display gamma curve
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_ReGammaCoefficients_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, const ADLReGammaCoefficients* lpRegamma);

/// DEPRECATED - Replaced with ADL_Display_RegammaR1_Set
/// \brief 
/// \Function to set requested re gamma coefficients setting for the display. 
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[in ]  lpRegamma coefficients to be used to build the display gamma curve
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
ADL_EXTERNC int EXPOSED ADL_Display_ReGammaCoefficients_Set(int iAdapterIndex, int iDisplayIndex, const ADLReGammaCoefficients* lpRegamma);

/// DEPRECATED - Replaced with ADL_Display_RegammaR1_Get
/// \brief 
/// \Function to get the re gamma coefficients setting for the display. 
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[out]  lpRegamma coefficients currently in use to build ideal re gamma curve
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_ReGammaCoefficients_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLReGammaCoefficients* lpRegamma);

/// DEPRECATED - Replaced with ADL_Display_RegammaR1_Get
/// \brief 
/// \Function to get the re gamma coefficients setting for the display. 
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[out]  lpRegamma coefficients currently in use to build ideal re gamma curve
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
ADL_EXTERNC int EXPOSED ADL_Display_ReGammaCoefficients_Get(int iAdapterIndex, int iDisplayIndex, ADLReGammaCoefficients* lpRegamma);


///\brief Function to set given re gamma  for the display. It could be a display gamma or coefficients
/// This function sets the ADL2_Display_Regamma_Set setting for a specified display.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[in ]  lpRegamma it has  2 options :  coefficients to build the display gamma curve or direct display gamma curve
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_Regamma_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, const ADLRegamma* lpRegamma);

///\brief Function to set given re gamma  for the display. It could be a display gamma or coefficients
/// This function sets the ADL_Display_Regamma_Set setting for a specified display.
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[in ]  lpRegamma it has  2 options :  coefficients to build the display gamma curve or direct display gamma curve
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
ADL_EXTERNC int EXPOSED ADL_Display_Regamma_Set(int iAdapterIndex, int iDisplayIndex, const ADLRegamma* lpRegamma);

///\brief Function to get the current re gamma for the given display
/// This function gets the ADL2_Display_Regamma_Get setting for a specified display.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[out]  lpRegamma used by driver. It has  2 options :  coefficients to build the display gamma curve or direct display gamma curve
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_Regamma_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLRegamma* lpRegamma);

///\brief Function to get the current re gamma for the given display
/// This function gets the ADL_Display_Regamma_Get setting for a specified display.
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[out]  lpRegamma used by driver. It has  2 options :  coefficients to build the display gamma curve or direct display gamma curve
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
ADL_EXTERNC int EXPOSED ADL_Display_Regamma_Get(int iAdapterIndex, int iDisplayIndex, ADLRegamma* lpRegamma);

///\brief 
/// This function sets the given re-gamma for the display. The gamma may come direct from the panel's information or from set coefficients that will build an ideal gamma curve. 
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[in ]  lpRegammaEx The gamma curve; where the curve is either coming direct from display information or will be built by coefficients. 
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_RegammaR1_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, const ADLRegammaEx* lpRegammaEx);

///\brief 
/// This function sets the given re-gamma for the display. The gamma may come direct from the panel's information or from set coefficients that will build an ideal gamma curve. 
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[in ]  lpRegammaEx The gamma curve; where the curve is either coming direct from display information or will be built by coefficients. 
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
ADL_EXTERNC int EXPOSED ADL_Display_RegammaR1_Set(int iAdapterIndex, int iDisplayIndex, const ADLRegammaEx* lpRegammaEx);

///\brief 
/// This function get the current regamma setting for the given display.  The value of this gamma may have originally been set from values direct from the display or coefficients that built the original curve.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[out]  lpRegammaEx The gamma curve; where the curve either came directly from the display or built by coefficients. 
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_RegammaR1_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLRegammaEx* lpRegammaEx);

///\brief 
/// This function get the current regamma setting for the given display.  The value of this gamma may have originally been set from values direct from the display or coefficients that built the original curve.
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[out]  lpRegammaEx The gamma curve; where the curve either came directly from the display or built by coefficients. 
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
ADL_EXTERNC int EXPOSED ADL_Display_RegammaR1_Get(int iAdapterIndex, int iDisplayIndex, ADLRegammaEx* lpRegammaEx);


///\brief 
/// This function gets the current source content attributes
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[out]  lpContentAttributes The source content attributes
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_SourceContentAttribute_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, ADLHDRContentInfo* lpContentAttributes);

///\brief 
/// his function gets the current source content attributes
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[out]  lpContentAttributes The source content attributes
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
ADL_EXTERNC int EXPOSED ADL_Display_SourceContentAttribute_Get(int iAdapterIndex, int iDisplayIndex, ADLHDRContentInfo* lpContentAttributes);

///\brief 
/// This function sets the source content attributes
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[in]  lpContentAttributes The source content attributes
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_SourceContentAttribute_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, const ADLHDRContentInfo* lpContentAttributes);

///\brief 
/// his function gets the current source content attributes
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[in]  lpContentAttributes The source content attributes
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
ADL_EXTERNC int EXPOSED ADL_Display_SourceContentAttribute_Set(int iAdapterIndex, int iDisplayIndex, const ADLHDRContentInfo* lpContentAttributes);


// @}

/// \addtogroup AVIVO COLOR
///
// @{

#if defined (_WIN32) || defined(_WIN64)

///\brief Function to get the current, default, min, max, and step size for a given AVIVO color adjustment  
/// This function gets the current, default, min, max, and step size for a given AVIVO color adjustment
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  iAdjustmentType The desired color adjustment type.
/// \param[out] lpCurrent The pointer to the current color value.
/// \param[out] lpDefault The pointer to the default color value.
/// \param[out] lpMin The pointer to the minimum color value.
/// \param[out] lpMax The pointer to the maximum color value.
/// \param[out] lpStep The pointer to the increment size of the color adjustment setting.
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_AvivoColor_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iAdjustmentType, int* lpCurrent, int* lpDefault, int* lpMin, int* lpMax, int* lpStep);

///\brief Function to get the current, default, min, max, and step size for a given AVIVO color adjustment  
/// This function gets the current, default, min, max, and step size for a given AVIVO color adjustment
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  iAdjustmentType The desired color adjustment type.
/// \param[out] lpCurrent The pointer to the current color value.
/// \param[out] lpDefault The pointer to the default color value.
/// \param[out] lpMin The pointer to the minimum color value.
/// \param[out] lpMax The pointer to the maximum color value.
/// \param[out] lpStep The pointer to the increment size of the color adjustment setting.
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
ADL_EXTERNC int EXPOSED ADL_Display_AvivoColor_Get(int iAdapterIndex, int iAdjustmentType, int* lpCurrent, int* lpDefault, int* lpMin, int* lpMax, int* lpStep);

///\brief Function to set the current value for a given AVIVO color adjustment  
/// This function sets the current value for a given AVIVO color adjustment
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  iAdjustmentType The desired color adjustment type.
/// \param[out] iCurrent The current value that should be set for the adjustment.
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_AvivoCurrentColor_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iAdjustmentType, int iCurrent);

///\brief Function to set the current value for a given AVIVO color adjustment  
/// This function sets the current value for a given AVIVO color adjustment
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  iAdjustmentType The desired color adjustment type.
/// \param[out] iCurrent The current value that should be set for the adjustment.
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
ADL_EXTERNC int EXPOSED ADL_Display_AvivoCurrentColor_Set(int iAdapterIndex, int iAdjustmentType, int iCurrent);

///\brief Function to set the default value for a given AVIVO color adjustment  
/// This function sets the default value for a given AVIVO color adjustment
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  iAdjustmentType The desired color adjustment type.
/// \param[out] iDefault The current value that should be set for the adjustment.
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_AvivoDefaultColor_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iAdjustmentType, int iDefault);

///\brief Function to set the default value for a given AVIVO color adjustment  
/// This function sets the default value for a given AVIVO color adjustment
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  iAdjustmentType The desired color adjustment type.
/// \param[out] iDefault The current value that should be set for the adjustment.
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
ADL_EXTERNC int EXPOSED ADL_Display_AvivoDefaultColor_Set(int iAdapterIndex, int iAdjustmentType, int iDefault);

#endif
// @}

/// \ingroup DISPLAYAPI
///\defgroup REMDISPLAY Remote Display APIs
/// This group outlines Remote Display Related APIs.

/// \addtogroup REMDISPLAY
///
// @{

///
///\brief Function to acquire wireless display path
/// 
/// This function acquires the wireless display for a specified display path
/// This function will be replaced by ADL2_RemoteDisplay_Display_Acquire
/// \platform
/// \WIN7 and \WIN8
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   displayID  The structure stores the display target information.
/// \param[in]   lpRemoteDisplayCaps The pointer to the ADLRemoteDisplayCaps structure storing EDID and remote display capabilities.
/// \param[out]  lpRemoteDisplayHandle The pointer to the ADLRemoteDisplayHandle type storing handle returned from driver.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \remarks This API is in Prototype stage. Do not use for shipping products!
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_RemoteDisplay_Display_Acquire(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLDisplayID displayID, ADLRemoteDisplayCaps* lpRemoteDisplayCaps, ADLRemoteDisplayHandle* lpRemoteDisplayHandle);

///
///\brief Function to acquire wireless display path
/// 
/// This function acquires the wireless display for a specified display path
/// This function will be replaced by ADL_RemoteDisplay_Display_Acquire
/// \platform
/// \WIN7 and \WIN8
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   displayID  The structure stores the display target information.
/// \param[in]   lpRemoteDisplayCaps The pointer to the ADLRemoteDisplayCaps structure storing EDID and remote display capabilities.
/// \param[out]  lpRemoteDisplayHandle The pointer to the ADLRemoteDisplayHandle type storing handle returned from driver.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \remarks This API is in Prototype stage. Do not use for shipping products!
ADL_EXTERNC int EXPOSED ADL_RemoteDisplay_Display_Acquire(int iAdapterIndex, ADLDisplayID displayID, ADLRemoteDisplayCaps* lpRemoteDisplayCaps, ADLRemoteDisplayHandle* lpRemoteDisplayHandle);

///
///\brief Function to release wireless display path
/// 
/// This function releases the wireless display for a specified display path
/// This function will be replaced by ADL2_RemoteDisplay_Display_Release
/// \platform
/// \WIN7 and \WIN8
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   displayID  The structure stores the display target information.
/// \param[in]   lpRemoteDisplayHandle The pointer returned from ADL_RemoteDisplay_Acquire().
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \remarks This API is in Prototype stage. Do not use for shipping products!
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_RemoteDisplay_Display_Release(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLDisplayID displayID, ADLRemoteDisplayHandle remoteDisplayHandle);

///
///\brief Function to release wireless display path
/// 
/// This function releases the wireless display for a specified display path
/// This function will be replaced by ADL_RemoteDisplay_Display_Release
/// \platform
/// \WIN7 and \WIN8
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   displayID  The structure stores the display target information.
/// \param[in]   lpRemoteDisplayHandle The pointer returned from ADL_RemoteDisplay_Acquire().
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \remarks This API is in Prototype stage. Do not use for shipping products!
ADL_EXTERNC int EXPOSED ADL_RemoteDisplay_Display_Release(int iAdapterIndex, ADLDisplayID displayID, ADLRemoteDisplayHandle remoteDisplayHandle);
// @}

/// \addtogroup DISPSHARP
// @{
///\brief Function to get sharpness information setting for the display. 
/// This function gets sharpness information setting for a specified display.
/// \platform
/// \ALL
/// \param[in]   context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[out]  lpCurrent The pointer to the current sharpness value.
/// \param[out]  lpDefault The pointer to the default sharpness value.
/// \param[out]  lpMin The pointer to the minimum sharpness value.
/// \param[out]  lpMax The pointer to the maximum sharpness value.
/// \param[out]  lpStep The pointer to the increment size of the sharpness adjustment setting.
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_Sharpness_Info_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int* lpCurrent, int* lpDefault, int* lpMin, int* lpMax, int* lpStep);


///\brief Function to get sharpness information setting for the display. 
/// This function gets sharpness information setting for a specified display.
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[out]  lpCurrent The pointer to the current sharpness value.
/// \param[out]  lpDefault The pointer to the default sharpness value.
/// \param[out]  lpMin The pointer to the minimum sharpness value.
/// \param[out]  lpMax The pointer to the maximum sharpness value.
/// \param[out]  lpStep The pointer to the increment size of the sharpness adjustment setting.
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
ADL_EXTERNC int EXPOSED ADL_Display_Sharpness_Info_Get(int iAdapterIndex, int iDisplayIndex, int* lpCurrent, int* lpDefault, int* lpMin, int* lpMax, int* lpStep);

///\brief Function to get the current sharpness setting for the display. 
/// This function gets the current sharpness setting for a specified display.
/// \platform
/// \ALL
/// \param[in]   context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[out]  sharpness
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_Sharpness_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int* pSharpness);


///\brief Function to get the current sharpness setting for the display. 
/// This function gets the current sharpness setting for a specified display.
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[out]  sharpness
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
ADL_EXTERNC int EXPOSED ADL_Display_Sharpness_Get(int iAdapterIndex, int iDisplayIndex, int* pSharpness);

///\brief Function to set the display sharpness setting for the display. 
/// This function sets the display sharpness setting for a specified display.
/// \platform
/// \ALL
/// \param[in]   context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[in ]  sharpness
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_Sharpness_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int sharpness);

///\brief Function to set the display sharpness setting for the display. 
/// This function sets the display sharpness setting for a specified display.
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[in ]  sharpness
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
ADL_EXTERNC int EXPOSED ADL_Display_Sharpness_Set(int iAdapterIndex, int iDisplayIndex, int sharpness);

///
///\brief Function to get the information of Sharpness Feature Support.
/// This function retrieves the Sharpness Feature Support for a specified adapter and display.
/// \platform
/// \ALL
/// \param[in]   context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]   iAdapterIndex The index of the desired adapter.
/// \param[in]   iDisplayIndex The index of the desired display.
/// \param[out]  lpCaps Indicates sharpness feature support.
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Display_Sharpness_Caps(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDisplayIndex, int* lpCaps);

///
///\brief Function to get the information of Sharpness Feature Support. 
/// This function retrieves the SSharpness Feature Support for a specified adapter and display.
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The index of the desired adapter.
/// \param[in]   iDisplayIndex The index of the desired display.
/// \param[out]  lpCaps Indicates sharpness feature support.
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results
ADL_EXTERNC int EXPOSED ADL_Display_Sharpness_Caps(int iAdapterIndex, int iDisplayIndex, int* lpCaps);

///
///\brief Function to run submit DP AUX MSG (MSG Transaction) to get or set MST display or its branch settings.
/// 
/// This function provides means for applications to get or set MST display or its branches settings.
/// \platform
/// \ALL
/// \param[in]  context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in]  iOption Combination of \ref ADL_MST_COMMANDLINE_BRANCH_MSG and ADL_MST_COMMANDLINE_BROADCAST  
/// \param[in]  iMsgSequeuceNo The index of message sequence index. It should be 0 or 1
/// \param[in]  iNumOfRelativeAddress The size of the device relative address.
/// \param[in]  lpRelativeAddress The relative address of the device relative address
/// \param[in]  iCommandLineLen The size of the command line buffer.
/// \param[in]  lpCommandLineBuf The pointer to the command line buffer.
/// \param[out] lpReplyBufLen The pointer to the size of the reply buffer.
/// \param[out] lpReplyBufBuf The pointer to the reply buffer.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks The applications need to allocate memory for both command line and reply buffer. The Max number of buffer is 255.

ADL_EXTERNC int EXPOSED ADL2_Display_DpMstAuxMsg_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex,
	int iDisplayIndex,
	int iOption, int iMsgSequeueNo,
	int iNumOfRelativeAddress, char* lpRelativeAddress,
	int iCommandLineLen, char* lpCommandLineBuf,
	int* lpReplyLen, char* lpReplyBuf);
// @}

#endif /* OEM_DISPLAY_H_ */