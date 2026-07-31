///
///  Copyright (c) 2008 - 2013 Advanced Micro Devices, Inc.

///  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
///  EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
///  WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.

/// \file oem_adapter.h
/// \brief Contains all customer display-related functions exposed by ADL for \ALL platforms.
///
/// This file contains all OEM or other customer adapter-related functions exposed by ADL for \ALL platforms.
/// All functions found in this file can be used as a reference to ensure
/// the specified function pointers can be used by the appropriate runtime
/// dynamic library loaders. This header file not for public release.

#ifndef OEM_ADAPTER_H_
#define OEM_ADAPTER_H_

#ifndef ADL_EXTERNC
#ifdef __cplusplus
#define ADL_EXTERNC extern "C"
#else
#define ADL_EXTERNC
#endif
#endif

#ifndef EXPOSED
#define EXPOSED
#endif /* EXPOSED */

/// \addtogroup ADAPTER
// @{
///\brief Function to get the VariBright capabilities
/// This function retrieves the VariBright capabilities for a specified display adapter.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  iSupported The pointer to an int variable which indicates if VariBright is supported ( \ref ADL_TRUE : supported, \ref ADL_FALSE : not supported)
/// \param[in]  iEnabled The pointer to an int variable which indicates if VariBright is enabled ( \ref ADL_TRUE : enabled, \ref ADL_FALSE : disabled)
/// \param[in]  iEnabled The pointer to an int variable receiving the VariBright version.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
///
/// \remarks Call this API first. Only if VariBright feature is supported and enabled call ADL_Adapter_VariBrightLevel_Get() or ADL_Adapter_VariBrightLevel_Set()
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Adapter_VariBright_Caps(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* iSupported, int* iEnabled, int* iVersion);

///\brief Function to get the VariBright capabilities
/// This function retrieves the VariBright capabilities for a specified display adapter.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  iSupported The pointer to an int variable which indicates if VariBright is supported ( \ref ADL_TRUE : supported, \ref ADL_FALSE : not supported)
/// \param[in]  iEnabled The pointer to an int variable which indicates if VariBright is enabled ( \ref ADL_TRUE : enabled, \ref ADL_FALSE : disabled)
/// \param[in]  iEnabled The pointer to an int variable receiving the VariBright version.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
///
/// \remarks Call this API first. Only if VariBright feature is supported and enabled call ADL_Adapter_VariBrightLevel_Get() or ADL_Adapter_VariBrightLevel_Set()
ADL_EXTERNC int EXPOSED ADL_Adapter_VariBright_Caps(int iAdapterIndex, int* iSupported, int* iEnabled, int* iVersion);

///\brief Function to enable or disable VariBright capabilities
/// This function enables or disables VariBright for a specified display adapter.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  iEnabled \ref ADL_TRUE : enables VariBright, \ref ADL_FALSE : disables VariBright.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
///
/// \remarks Call ADL_Adapter_VariBright_Caps() first to determine if VariBright feature is supported.
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Adapter_VariBrightEnable_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iEnabled);

///\brief Function to enable or disable VariBright capabilities
/// This function enables or disables VariBright for a specified display adapter.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  iEnabled \ref ADL_TRUE : enables VariBright, \ref ADL_FALSE : disables VariBright.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
///
/// \remarks Call ADL_Adapter_VariBright_Caps() first to determine if VariBright feature is supported.
ADL_EXTERNC int EXPOSED ADL_Adapter_VariBrightEnable_Set(int iAdapterIndex, int iEnabled);

///\brief Function to get the current VariBright level 
/// This function retrieves the VariBright level for a specified display adapter.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  iDefaultLevel The pointer to an int variable with the default VariBright level.
/// \param[in]  iNumberOfLevels The pointer to an int variable receiving the number of VariBright levels (the Maximum value for VariBright level).
/// \param[in]  iStep The pointer to an int variable receiving the VariBright step. Determines the increments of the VariBright transition from one level to another.
/// \param[in]  iCurrentLevel The pointer to an int variable receiving the Current VariBright level.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
///
/// \remarks Call ADL_Adapter_VariBright_Caps() first to determine if VariBright feature is supported.
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Adapter_VariBrightLevel_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* iDefaultLevel, int* iNumberOfLevels, int* iStep, int* iCurrentLevel);

///\brief Function to get the current VariBright level 
/// This function retrieves the VariBright level for a specified display adapter.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  iDefaultLevel The pointer to an int variable with the default VariBright level.
/// \param[in]  iNumberOfLevels The pointer to an int variable receiving the number of VariBright levels (the Maximum value for VariBright level).
/// \param[in]  iStep The pointer to an int variable receiving the VariBright step. Determines the increments of the VariBright transition from one level to another.
/// \param[in]  iCurrentLevel The pointer to an int variable receiving the Current VariBright level.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
///
/// \remarks Call ADL_Adapter_VariBright_Caps() first to determine if VariBright feature is supported.
ADL_EXTERNC int EXPOSED ADL_Adapter_VariBrightLevel_Get(int iAdapterIndex, int* iDefaultLevel, int* iNumberOfLevels, int* iStep, int* iCurrentLevel);

///\brief Function to set the current VariBright level 
/// This function sets the VariBright level for a specified display adapter.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  iCurrentLevel The VariBright level to be set. The range is from zero to iNumberOfLevels returned from ADL_Adapter_VariBrightLevel_Get()
/// \param[in]  iApplyImmediately If set to \ref ADL_TRUE the VariBright level is applied immediately. If \ref ADL_FALSE - the level is applied gradually.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results.
///
/// \remarks Call ADL_Adapter_VariBright_Caps() first to determine if VariBright feature is supported.
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Adapter_VariBrightLevel_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iCurrentLevel, int iApplyImmediately);

///\brief Function to set the current VariBright level 
/// This function sets the VariBright level for a specified display adapter.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  iCurrentLevel The VariBright level to be set. The range is from zero to iNumberOfLevels returned from ADL_Adapter_VariBrightLevel_Get()
/// \param[in]  iApplyImmediately If set to \ref ADL_TRUE the VariBright level is applied immediately. If \ref ADL_FALSE - the level is applied gradually.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results.
///
/// \remarks Call ADL_Adapter_VariBright_Caps() first to determine if VariBright feature is supported.
ADL_EXTERNC int EXPOSED ADL_Adapter_VariBrightLevel_Set(int iAdapterIndex, int iCurrentLevel, int iApplyImmediately);

///
/// \brief ADL local interface. Function to query a registry value by driver.
/// 
/// This function query a registry value by driver for a specified adapter.
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  szDriverSettings The name of registry value to be got.
/// \param[in]  iDriverPathOption The option of the driver path. See \ref Definitions for driver path options for values.
/// \param[in]  iType The type of registry value to be got. See \ref Definitions for registry value types for values
/// \param[in]  iSize The size of registry value to be got.
/// \param[out] lpSetting The pointer to registry value to be got.
/// \platform 
/// \WIN
/// \return If the function valid, the return value is 1. Otherwise it is 0. 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Adapter_DriverSettings_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, char* szDriverSettings, int iDriverPathOption, int iType, int iSize, char* lpSetting);

///
/// \brief ADL local interface. Function to query a registry value by driver.
/// 
/// This function query a registry value by driver for a specified adapter.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  szDriverSettings The name of registry value to be got.
/// \param[in]  iDriverPathOption The option of the driver path. See \ref Definitions for driver path options for values.
/// \param[in]  iType The type of registry value to be got. See \ref Definitions for registry value types for values
/// \param[in]  iSize The size of registry value to be got.
/// \param[out] lpSetting The pointer to registry value to be got.
/// \platform 
/// \WIN
/// \return If the function valid, the return value is 1. Otherwise it is 0. 
ADL_EXTERNC int EXPOSED ADL_Adapter_DriverSettings_Get(int iAdapterIndex, char* szDriverSettings, int iDriverPathOption, int iType, int iSize, char* lpSetting);

///
/// \brief ADL local interface. Function to set a registry value by driver.
/// 
/// This function set a registry value by driver for a specified adapter.
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  szDriverSettings The name of registry value to be set.
/// \param[in]  iDriverPathOption The option of the driver path. See \ref Definitions for driver path options for values.
/// \param[in]  iType The type of registry value to be got. See \ref Definitions for registry value types for values
/// \param[in]  iSize The size of registry value to be set.
/// \param[out] lpSetting The pointer to registry value to be set.
/// \platform 
/// \WIN
/// \return If the function valid, the return value is 1. Otherwise it is 0. 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Adapter_DriverSettings_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, char* szDriverSettings, int iDriverPathOption, int iType, int iSize, char* lpSetting);

///
/// \brief ADL local interface. Function to set a registry value by driver.
/// 
/// This function set a registry value by driver for a specified adapter.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  szDriverSettings The name of registry value to be set.
/// \param[in]  iDriverPathOption The option of the driver path. See \ref Definitions for driver path options for values.
/// \param[in]  iType The type of registry value to be got. See \ref Definitions for registry value types for values
/// \param[in]  iSize The size of registry value to be set.
/// \param[out] lpSetting The pointer to registry value to be set.
/// \platform 
/// \WIN
/// \return If the function valid, the return value is 1. Otherwise it is 0. 
ADL_EXTERNC int EXPOSED ADL_Adapter_DriverSettings_Set(int iAdapterIndex, char* szDriverSettings, int iDriverPathOption, int iType, int iSize, char* lpSetting);

///
/// \brief Function to retrieve true Hardware generated random number.
/// 
/// This function implements a lhEscape call to retrieve TRGN from hardware .
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iTRNGSize size of the requested TRNG
/// \param[in]  iTRNGBufferSize size of the trngBuffer
/// \param[out] trngBuffer The pointer where TRNG value is stored, buffer should be allocated at client side
/// \return If the function succeeds, the return value is \ref ADL_OK, or an ADL error code otherwise. \ref define_adl_results
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Adapter_TRNG_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iTRNGSize, int iTRNGBufferSize, char* lpTRNGBuffer);

///
/// \brief Function to retrieve encrypted Device ID based on the input random number.
/// 
/// This function implements a lhEscape call to retrieve Device ID from hardware .
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iRNDBufferSize size of the input random number buffer size
/// \param[in]  lpRNDBuffer the pointer where input random number is stored
/// \param[in]  iDeviceIDBufferSize size of the out deviceID buffer size
/// \param[out] lpDeviceIDBuffer The pointer where Device ID value is stored, buffer should be allocated at client side
/// \param[out] iDeviceIDSize size of the device ID
/// \return If the function succeeds, the return value is \ref ADL_OK, or an ADL error code otherwise. \ref define_adl_results
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Adapter_DeviceID_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iRNDBufferSize, char* lpRNDBuffer, int iDeviceIDBufferSize, char* lpDeviceIDBuffer, int* iDeviceIDSize);



///\brief Function to get the current GPU VRAM usage
/// This function retrieves the VRAM usage of given adapter
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  iVRAMUsageInMB The pointer to an int variable retrives the current usage of VRAM.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Adapter_VRAMUsage_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* iVRAMUsageInMB);

///
/// \brief ADL local interface. Retrieves extended adapter information for given adapter or all OS-known adapters.
///
/// This function retrieves information for passed adapter or if pass -1, information of all OS-known adapters in the system. OS-known adapters can include adapters that are physically present in the system (logical adapters)    
/// as well as ones that are no longer present in the system but are still recognized by the OS.
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter or -1 if all adapters are desired
/// \param[out]  number of items in the lppAdapterInfo array. Can pass NULL pointer if passing an adapter index (in which case only one AdapterInfo is returned)
/// \param[out]  lppAdapterInfoX2 pointer to the pointer of AdapterInfoX2 array. Initialize to NULL before calling this API. ADL will allocate the necessary memory, using the user provided callback function.
/// \platform 
/// \ALL
/// \return If the function valid, the return value is 1. Otherwise it is 0. 
/// \remarks This API uses the memory allocation callback function provided by the user.
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Adapter_AdapterInfoX4_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* numAdapters, AdapterInfoX2** lppAdapterInfoX2);

///
/// \brief ADL local interface. Retrieves adapter information for given adapter or all OS-known adapters.
/// 
/// This function retrieves information for passed adapter or if pass -1, information of all OS-known adapters in the system. OS-known adapters can include adapters that are physically present in the system (logical adapters)    
/// as well as ones that are no longer present in the system but are still recognized by the OS.
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter or -1 if all adapters are desired
/// \param[out]  number of items in the lppAdapterInfo array. Can pass NULL pointer if passign an adapter index (in which case only one AdapterInfo is returned)
/// \param[out]  lppAdapterInfo pointer to the pointer of AdapterInfo array. Initialize to NULL before calling this API. ADL will allocate the necessary memory, using the user provided callback function.
/// \platform 
/// \ALL
/// \return If the function valid, the return value is 1. Otherwise it is 0. 
/// \remarks This API uses the memory allocation callback function provided by the user.
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Adapter_AdapterInfoX3_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* numAdapters, AdapterInfo** lppAdapterInfo);

// @}


/// \ingroup ADL_API
///\defgroup MMREARCHITECTURE Multi-Media APIs
/// This group outlines Multi-Media specific APIs.

/// \addtogroup MMREARCHITECTURE
// @{

/// \brief Function to obtain the list of Multi-Media features
/// 
/// The function is used to obtain the list of Multi-Media feature names for a specific display adapter.
/// \platform
/// \VISTAWIN7
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out]  lppName is pointer to the pointer of ADLFeatureName array. Initialize to NULL before  calling this API. ADL will allocate the necessary memory, using the user provided callback function.
/// \param[out]  lpFeatureCount The number of all available features.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API uses the memory allocation callback function provided by the user.
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_MMD_FeatureList_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLFeatureName** lppName, int* lpFeatureCount);

/// \brief Function to obtain the list of Multi-Media features
/// 
/// The function is used to obtain the list of Multi-Media feature names for a specific display adapter.
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out]  lppName is pointer to the pointer of ADLFeatureName array. Initialize to NULL before  calling this API. ADL will allocate the necessary memory, using the user provided callback function.
/// \param[out]  lpFeatureCount The number of all available features.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API uses the memory allocation callback function provided by the user.
ADL_EXTERNC int EXPOSED ADL_MMD_FeatureList_Get(int iAdapterIndex, ADLFeatureName** lppName, int* lpFeatureCount);


/// \brief Function to obtain capabilities of Multi-Media features
/// 
/// The function is used to obtain the capabilities for a set of specific Multi-Media features for a specific display adapter.
/// \platform
/// \VISTAWIN7
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  lppFeatureCaps The pointer to the pointer to the retrieved Feature Caps array. Initialize to NULL before calling this API.
/// \param[out]  lpFeatureCount The pointer to the number of ADLFeatureCaps elements in the retrieved list.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API uses the memory allocation callback function provided by the user.
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_MMD_Features_Caps(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLFeatureCaps** lppFeatureCaps, int* lpFeatureCount);

/// \brief Function to obtain capabilities of Multi-Media features
/// 
/// The function is used to obtain the capabilities for a set of specific Multi-Media features for a specific display adapter.
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  lppFeatureCaps The pointer to the pointer to the retrieved Feature Caps array. Initialize to NULL before calling this API.
/// \param[out]  lpFeatureCount The pointer to the number of ADLFeatureCaps elements in the retrieved list.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API uses the memory allocation callback function provided by the user.
ADL_EXTERNC int EXPOSED ADL_MMD_Features_Caps(int iAdapterIndex, ADLFeatureCaps** lppFeatureCaps, int* lpFeatureCount);


/// \brief Function to obtain the values and state of a Multi-Media feature
/// 
/// The function is used to obtain the values and state of a single Multi-Media feature for a specific display adapter.
/// \platform
/// \VISTAWIN7
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out]  lppFeatureValues The pointer to the pointer to the retrieved ADLFeatureValues array. Initialize to NULL before calling this API.
/// \param[out]  lpFeatureCount The pointer to the number of ADLFeatureValues elements in the retrieved list.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API uses the memory allocation callback function provided by the user.
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_MMD_FeatureValues_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLFeatureValues** lppFeatureValues, int* lpFeatureCount);

/// \brief Function to obtain the values and state of a Multi-Media feature
/// 
/// The function is used to obtain the values and state of a single Multi-Media feature for a specific display adapter.
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out]  lppFeatureValues The pointer to the pointer to the retrieved ADLFeatureValues array. Initialize to NULL before calling this API.
/// \param[out]  lpFeatureCount The pointer to the number of ADLFeatureValues elements in the retrieved list.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API uses the memory allocation callback function provided by the user.
ADL_EXTERNC int EXPOSED ADL_MMD_FeatureValues_Get(int iAdapterIndex, ADLFeatureValues** lppFeatureValues, int* lpFeatureCount);


/// \brief Function to set the current value of a Multi-Media feature
/// 
/// The function is used to set the current value of a single Multi-Media feature and optionally provide the handle of SetEvent object.
/// \platform
/// \VISTAWIN7
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  lpFeatureValues A pointer to the ADLFeatureValues array. Refer to ADLFeatureValues structure for more information.
/// \param[in]  iFeatureCount The number of ADLFeatureValues elements in the array.
/// \param[in]  ClientID The Client ID of the caller. It is recommended to provide a valid Client ID to avoid raising caller?s event object, immediately after the current value is set.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_MMD_FeatureValues_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLFeatureValues* lpFeatureValues, int iFeatureCount, int ClientID);

/// \brief Function to set the current value of a Multi-Media feature
/// 
/// The function is used to set the current value of a single Multi-Media feature and optionally provide the handle of SetEvent object.
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  lpFeatureValues A pointer to the ADLFeatureValues array. Refer to ADLFeatureValues structure for more information.
/// \param[in]  iFeatureCount The number of ADLFeatureValues elements in the array.
/// \param[in]  ClientID The Client ID of the caller. It is recommended to provide a valid Client ID to avoid raising caller?s event object, immediately after the current value is set.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
ADL_EXTERNC int EXPOSED ADL_MMD_FeatureValues_Set(int iAdapterIndex, ADLFeatureValues* lpFeatureValues, int iFeatureCount, int ClientID);


/// \brief Function to get MM video adjust info
///
/// The function is used to get multi-media video adjustment information.
/// 
/// \platform
/// \VISTAWIN7
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex			The ADL index handle of the desired adapter.
/// \param[out] lppMMVideoData			The pointer to the pointer to the retrieved MM Video data structure.
/// \param[out]	lpCount					The number of returned video data structure.
/// \param[out] lpLetApplicationDecide	If it is true, disable the all settings and let application make decision. Otherwise, using driver settings.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_MMD_VideoAdjustInfo_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLMMVideoData** lppMMVideoData, int* lpCount, int* lpLetApplicationDecide);

/// \brief Function to get MM video adjust info
///
/// The function is used to get multi-media video adjustment information.
/// 
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex			The ADL index handle of the desired adapter.
/// \param[out] lppMMVideoData			The pointer to the pointer to the retrieved MM Video data structure.
/// \param[out]	lpCount					The number of returned video data structure.
/// \param[out] lpLetApplicationDecide	If it is true, disable the all settings and let application make decision. Otherwise, using driver settings.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
ADL_EXTERNC int EXPOSED ADL_MMD_VideoAdjustInfo_Get(int iAdapterIndex, ADLMMVideoData** lppMMVideoData, int* lpCount, int* lpLetApplicationDecide);

/// \brief Function to set MM video adjust info
///
/// The function is used to set multi-media video adjustment information.
/// 
/// \platform
/// \VISTAWIN7
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex			The ADL index handle of the desired adapter.
/// \param[in]	lpMMVideoSetData		The pointer to the pointer to the MM Video data structure to be set.
/// \param[in]	iCount					The number of video data structure to be set.
/// \param[in]	iCommittedFlag			Committed flag, the value can be ADL_TURE or ADL_FALSE. ( \ref ADL_TRUE : committed, \ref ADL_FALSE : uncommitted)
/// \param[in]	iLetApplicationDecide	If it is \ref ADL_TRUE, disable all the settings and let application make decision. Otherwise(\ref ADL_FALSE), using driver settings.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_MMD_VideoAdjustInfo_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLMMVideoSetData* lpMMVideoSetData, int iCount, int iCommittedFlag, int iLetApplicationDecide);

/// \brief Function to set MM video adjust info
///
/// The function is used to set multi-media video adjustment information.
/// 
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex			The ADL index handle of the desired adapter.
/// \param[in]	lpMMVideoSetData		The pointer to the pointer to the MM Video data structure to be set.
/// \param[in]	iCount					The number of video data structure to be set.
/// \param[in]	iCommittedFlag			Committed flag, the value can be ADL_TURE or ADL_FALSE. ( \ref ADL_TRUE : committed, \ref ADL_FALSE : uncommitted)
/// \param[in]	iLetApplicationDecide	If it is \ref ADL_TRUE, disable all the settings and let application make decision. Otherwise(\ref ADL_FALSE), using driver settings.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
ADL_EXTERNC int EXPOSED ADL_MMD_VideoAdjustInfo_Set(int iAdapterIndex, ADLMMVideoSetData* lpMMVideoSetData, int iCount, int iCommittedFlag, int iLetApplicationDecide);

/// \brief Function to get MM video capabilities
///
/// The function is used to get current multi-media video capabilities.
/// 
/// \platform
/// \VISTAWIN7
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex			The ADL index handle of the desired adapter.
/// \param[in]	iVAControllerIndex		Controller index.
/// \param[in]	iVADisplayIndex			Display index.
/// \param[out] lpStandardVideoCaps		Standard video caps
/// \param[out]	lpHDVideoCaps			High-Definition Video caps
/// \param[out] lpGenericCaps			Generic Video caps
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_MMD_Video_Caps(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iVAControllerIndex, int iVADisplayIndex,
	LPADLMMVideoCaps lpStandardVideoCaps, LPADLMMVideoCaps lpHDVideoCaps, LPADLMMVideoGenericCaps lpGenericCaps);

/// \brief Function to get MM video capabilities
///
/// The function is used to get current multi-media video capabilities.
/// 
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex			The ADL index handle of the desired adapter.
/// \param[in]	iVAControllerIndex		Controller index.
/// \param[in]	iVADisplayIndex			Display index.
/// \param[out] lpStandardVideoCaps		Standard video caps
/// \param[out]	lpHDVideoCaps			High-Definition Video caps
/// \param[out] lpGenericCaps			Generic Video caps
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
ADL_EXTERNC int EXPOSED ADL_MMD_Video_Caps(int iAdapterIndex, int iVAControllerIndex, int iVADisplayIndex,
	LPADLMMVideoCaps lpStandardVideoCaps, LPADLMMVideoCaps lpHDVideoCaps, LPADLMMVideoGenericCaps lpGenericCaps);

///  \brief Retrieves capabilities of specific Video Color Feature.
///
///	 Use the call to determine if given Video color feature is supported by the driver, is it currently enabled, what are range, step , and default values of the feature. 
/// \platform
/// \VISTAWIN7
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter 
/// \param[in]  iFeature contains \ref ADLVideoColorFeature value. Id of Video Color feature.
/// \param[out]  lpCaps is reference to instance of \ref ADLVideoColorCaps structure that contains current capabilities of the feature.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error  code. 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_MMD_VideoColor_Caps(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLVideoColorFeature iFeature, LPADLVideoColorCaps lpCaps);

///  \brief Retrieves capabilities of specific Video Color Feature.
///
///	 Use the call to determine if given Video color feature is supported by the driver, is it currently enabled, what are range, step , and default values of the feature. 
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter 
/// \param[in]  iFeature contains \ref ADLVideoColorFeature value. Id of Video Color feature.
/// \param[out]  lpCaps is reference to instance of \ref ADLVideoColorCaps structure that contains current capabilities of the feature.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error  code. 
ADL_EXTERNC int EXPOSED ADL_MMD_VideoColor_Caps(int iAdapterIndex, ADLVideoColorFeature iFeature, LPADLVideoColorCaps lpCaps);

///  \brief Sends new value of Video Color feature to the driver.
///
///	 The function allows changing value of such Avivo Video color features as tint, brightness, saturation, contrast, color vibrance, gamma, skin tone correction strength.
/// \platform
/// \VISTAWIN7
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter 
/// \param[in]  iFeature contains \ref ADLVideoColorFeature value. Id of Video Color feature.
/// \param[in]  iValue new value of the feature.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error  code. 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_MMD_VideoColor_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLVideoColorFeature iFeature, float iValue);

///  \brief Sends new value of Video Color feature to the driver.
///
///	 The function allows changing value of such Avivo Video color features as tint, brightness, saturation, contrast, color vibrance, gamma, skin tone correction strength.
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter 
/// \param[in]  iFeature contains \ref ADLVideoColorFeature value. Id of Video Color feature.
/// \param[in]  iValue new value of the feature.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error  code. 
ADL_EXTERNC int EXPOSED ADL_MMD_VideoColor_Set(int iAdapterIndex, ADLVideoColorFeature iFeature, float iValue);

///  \brief Gets current value of Video Color feature from the driver.
///
///	 The function reads current value of such features as tint, brightness, saturation, contrast, color vibrance, gamma, skin tone correction strength.
/// \platform
/// \VISTAWIN7
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter 
/// \param[in]  iFeature contains \ref ADLVideoColorFeature value. Id of Video Color feature.
/// \param[out]  iValue current value of the feature.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error  code. 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_MMD_VideoColor_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLVideoColorFeature iFeature, float* iValue);

///  \brief Gets current value of Video Color feature from the driver.
///
///	 The function reads current value of such features as tint, brightness, saturation, contrast, color vibrance, gamma, skin tone correction strength.
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter 
/// \param[in]  iFeature contains \ref ADLVideoColorFeature value. Id of Video Color feature.
/// \param[out]  iValue current value of the feature.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error  code. 
ADL_EXTERNC int EXPOSED ADL_MMD_VideoColor_Get(int iAdapterIndex, ADLVideoColorFeature iFeature, float* iValue);

// @}


/// \addtogroup OVERDRIVE5
// @{

///  \brief Function to check for Power Control (long run GPU power limit) capabilities
///
/// The output parameter of the function lets the caller know about whether or not Power Control (long run GPU power limit) feature is available.  Supported only on GPUs with PowerTune Technology.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out] lpSupported is ADL_TRUE if feature is supported, otherwise it is ADL_FALSE.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Overdrive5_PowerControlAbsValue_Caps(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* lpSupported);

///  \brief Function to check for Power Control (long run GPU power limit) capabilities
///
/// The output parameter of the function lets the caller know about whether or not Power Control (long run GPU power limit) feature is available.  Supported only on GPUs with PowerTune Technology.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out] lpSupported is ADL_TRUE if feature is supported, otherwise it is ADL_FALSE.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 

ADL_EXTERNC int EXPOSED ADL_Overdrive5_PowerControlAbsValue_Caps(int iAdapterIndex, int* lpSupported);

///  \brief Function to get absolute values of Power Control (GPU power limit)
///
/// The parameters of the function allow the caller to obtain absolute value of the long run GPU power limit.  Supported only on GPUs with PowerTune Technology.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle  of the desired adapter 
/// \param[out]  lpCurrentValue pointer to the current value of long run GPU power limit 
/// \param[out]  lpDefaultValue pointer to the Default value of long run GPU power limit 
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error  code. 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Overdrive5_PowerControlAbsValue_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int* lpCurrentValue, int* lpDefaultValue);

///  \brief Function to get absolute values of Power Control (GPU power limit)
///
/// The parameters of the function allow the caller to obtain absolute value of the long run GPU power limit.  Supported only on GPUs with PowerTune Technology.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle  of the desired adapter 
/// \param[out]  lpCurrentValue pointer to the current value of long run GPU power limit 
/// \param[out]  lpDefaultValue pointer to the Default value of long run GPU power limit 
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error  code. 

ADL_EXTERNC int EXPOSED ADL_Overdrive5_PowerControlAbsValue_Get(int iAdapterIndex, int* lpCurrentValue, int* lpDefaultValue);

///  \brief Function to set absolute value of Power Control (long run GPU power limit)
///
/// The parameters of the function allow the caller to set absolute value of the long run GPU power limit, extends existing ADL_Overdrive5_PowerControl_Set API.  Supported only on GPUs with PowerTune Technology.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter 
/// \param[in]  iValue New value of long run GPU power limit  
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error  code. 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Overdrive5_PowerControlAbsValue_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iValue);

///  \brief Function to set absolute value of Power Control (long run GPU power limit)
///
/// The parameters of the function allow the caller to set absolute value of the long run GPU power limit, extends existing ADL_Overdrive5_PowerControl_Set API.  Supported only on GPUs with PowerTune Technology.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter 
/// \param[in]  iValue New value of long run GPU power limit  
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error  code. 

ADL_EXTERNC int EXPOSED ADL_Overdrive5_PowerControlAbsValue_Set(int iAdapterIndex, int iValue);


typedef enum _TEMPERATURE_TYPE
{
	TEMPERATURE_TYPE_INVALID = 0,
	TEMPERATURE_TYPE_EDGE = 1,
	TEMPERATURE_TYPE_HBM = 2,
	TEMPERATURE_TYPE_VRVDDC = 3,
	TEMPERATURE_TYPE_VRMVDD = 4,
	TEMPERATURE_TYPE_LIQUID = 5,
	TEMPERATURE_TYPE_PLX = 6,
	TEMPERATURE_TYPE_MAXTYPES = 6
} TEMPERATURE_TYPE;

// @}

/// \addtogroup OVERDRIVE6
// @{

///  \brief Function returns the temperature of the specified adapter, depending on the temperature typer requested.
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  eTemperatureType The enum for TEMPERATURE_TYPE to specify the power type.
/// \param[out] iTemperature The int pointer containing the temperature.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error  code.
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process and to assure that ADL API are thread-safe. Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Overdrive6_TemperatureEx_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, TEMPERATURE_TYPE eTemperatureType, int* iTemperature);


// @}

/// \addtogroup OVERDRIVE6
// @{

///  \brief Function Requests to Acquire or Release I2C of the specified adapter .
/// \platform
/// \ALL
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iControl int to specify whether to acquire or release I2C.  #define CWDDEPM_I2C_RELEASE    0  #define CWDDEPM_I2C_ACQUIRE    1
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error  code.
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process and to assure that ADL API are thread-safe. Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Overdrive6_ControlI2C(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iControl);

// @}

/// \addtogroup CHILL
// @{
///\brief Function to notify DX via KMD that Chill settings have changed.
/// This function communicates DX via KMD that user changed chill settings.
/// \platform
/// \WIN
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  iChanged \ref ADL_TRUE   \ref ADL_FALSE 
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
///
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Chill_Settings_Notify(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iChanged);

// @}

///
/// \brief ADL local interface. Function to set a driver registry integer value.
/// 
/// This function sets a driver registry integer value for a specified adapter by specifying the subkey path and key name.
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex		The ADL index handle of the desired adapter.
/// \param[in]  iDriverPathOption	The option of the driver path. 0: Current; 1: function1; 2: function2; 0xFFFF for all device.
/// \param[in]  szSubKey			The path of registry subkey to be accessed. This is a null terminated string and the parameter can be NULL.
/// \param[in]  szKeyName			The name of registry value to be set. This is a null terminated string.
/// \param[in]  iKeyValue			The integer registry value to be set.
/// \platform 
/// \WIN
/// \return If the function valid, the return value is 1. Otherwise it is 0. 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Adapter_RegValueInt_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDriverPathOption, char* szSubKey, char* szKeyName, int iKeyValue);

/// \brief ADL local interface. Function to set a driver registry string value.
/// 
/// This function sets a driver registry string value for a specified adapter by specifying the subkey path and key name.
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex		The ADL index handle of the desired adapter.
/// \param[in]  iDriverPathOption	The option of the driver path. 0: Current; 1: function1; 2: function2; 0xFFFF for all device.
/// \param[in]  szSubKey			The path of registry sub key to be accessed. This is a null terminated string and the parameter can be NULL.
/// \param[in]  szKeyName			The name of registry value to be set. This is a null terminated string.
/// \param[in]  iSize				The size of registry value to be set.
/// \param[in]	lpKeyValue			The pointer to registry value to be set.
/// \platform 
/// \WIN
/// \return If the function valid, the return value is 1. Otherwise it is 0. 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Adapter_RegValueString_Set(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDriverPathOption, char* szSubKey, char* szKeyName, int iSize, char* lpKeyValue);

///
/// \brief ADL local interface. Function to query a string registry value set by driver.
/// 
/// This function queries a driver registry string value for a specified adapter by specifying the subkey path and key name.
/// \param[in] context: Client's ADL context handle \ref ADL_CONTEXT_HANDLE obtained from \ref ADL2_Main_Control_Create.
/// \param[in]  iAdapterIndex		The ADL index handle of the desired adapter.
/// \param[in]  iDriverPathOption	The option of the driver path. 0: Current; 1: function1; 2: function2; 0xFFFF for all device.
/// \param[in]  szSubKey			The path of registry sub key to be accessed. This is a null terminated string and the parameter can be NULL.
/// \param[in]  szKeyName			The name of registry value to be got. This is a null terminated string.
/// \param[in]  iSize				The size of registry value to be got.
/// \param[out] lpKeyValue			The pointer to registry value to be got.
/// \platform 
/// \WIN
/// \return If the function valid, the return value is 1. Otherwise it is 0. 
/// \remarks Clients can use ADL2 version of the API to assure that there is no interference with other ADL clients that are running in the same process . Such clients have to call \ref ADL2_Main_Control_Create first to obtain \ref ADL_CONTEXT_HANDLE instance that has to be passed to each subsequent ADL2 call and finally destroyed using \ref ADL2_Main_Control_Destroy.
ADL_EXTERNC int EXPOSED ADL2_Adapter_RegValueString_Get(ADL_CONTEXT_HANDLE context, int iAdapterIndex, int iDriverPathOption, char* szSubKey, char* szKeyName, int iSize, char* lpKeyValue);

// @}

#endif /* OEM_DISPLAY_H_ */