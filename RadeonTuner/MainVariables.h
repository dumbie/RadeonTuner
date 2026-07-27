#pragma once
#include "pch.h"

//Status
inline bool disable_saving = true;
inline bool disable_saving_settings = true;
inline bool radeon_Chill_Linked = false;
inline bool messageBoxComplete = false;
inline bool appPickerCompleted = false;
inline bool appPickerSelected = false;
inline bool appPickerCancel = false;

//ADL
inline int adl_Res0 = ADL_ERR;
inline int adl_Res1 = ADL_ERR;
inline ADL_CONTEXT_HANDLE adl_Context = NULL;

//Application
inline AdlApplication adl_App_Current{};
inline AdlApplication adl_App_Global{ .Global = true, .FileName = L"Global", .FilePath = L"Registry" };

//Videocard
inline int adl_Gpu_AdapterIndex = -1;
inline std::wstring adl_Gpu_RegistryPath;
inline std::wstring adl_Gpu_UniqueIdentifierHex;

//Display
inline int adl_Display_AdapterIndex = -1;
inline int adl_Display_DisplayIndex = -1;
inline int displayResolutionSwitchTimeSec = 15;
inline int displayResolutionRevertWidth = 0;
inline int displayResolutionRevertHeight = 0;
inline float displayResolutionRevertRefreshRate = 0.0F;
inline int displayResolutionRevertOrientation = 0;

//Timers
inline winrt::Windows::UI::Xaml::DispatcherTimer TimerNotification = NULL;
inline winrt::Windows::UI::Xaml::DispatcherTimer TimerResolutionSwitch = NULL;

//Settings
inline TuningFanSettings tuningFanSettingsCurrent{};
inline GraphicsSettings graphicsSettingsCurrent{};
inline DisplaySettings displaySettingsCurrent{};
inline MultimediaSettings multimediaSettingsCurrent{};

//Cache
//Fix use ObservableCollection and DataContext binding instead
inline std::vector<std::wstring> eyefinityAppsCache{};
inline std::vector<std::wstring> powerBoostAppsCache{};
inline std::vector<TuningFanSettings> tuningFanSettingsCache{};