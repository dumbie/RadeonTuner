#pragma once
#include "pch.h"

inline bool disable_picking = true;
inline bool disable_saving = true;
inline bool disable_saving_settings = true;
inline bool radeon_Chill_Linked = false;

inline std::wstring gpuRegistryPath;
inline std::wstring gpuUniqueIdentifierHex;
inline int gpuUniqueIdentifier = -1;

inline ADL_CONTEXT_HANDLE adl_Context = NULL;

inline std::vector<AdapterInfo> adl_List_Gpus{};
inline std::vector<ADLDisplayInfo> adl_List_Displays{};
inline int adl_Display_AdapterIndex = -1;
inline int adl_Display_DisplayIndex = -1;
inline int adl_Gpu_AdapterIndex = -1;
inline int adl_Res0 = ADL_ERR;
inline int adl_Res1 = ADL_ERR;

inline winrt::Windows::UI::Xaml::DispatcherTimer TimerNotification = NULL;
inline winrt::Windows::UI::Xaml::DispatcherTimer TimerResolutionSwitch = NULL;

inline int displayResolutionSwitchTimeSec = 15;
inline int displayResolutionRevertWidth = 0;
inline int displayResolutionRevertHeight = 0;
inline int displayResolutionRevertRefreshRate = 0;
inline int displayResolutionRevertOrientation = 0;

inline int adl_AppSelectedIndex = -1;
inline std::vector<AdlApplication> adl_Apps_Cache{};

//Fix use ObservableCollection and DataContext binding instead
inline std::vector<std::wstring> eyefinityAppsCache{};
inline std::vector<std::wstring> powerBoostAppsCache{};
inline std::vector<TuningFanSettings> tuningFanSettingsCache{};

inline TuningFanSettings tuningFanSettingsCurrent{};
inline GraphicsSettings graphicsSettingsCurrent{};
inline DisplaySettings displaySettingsCurrent{};
inline MultimediaSettings multimediaSettingsCurrent{};