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

//Devices
inline int adl_Gpu_AdapterIndex = -1;
inline std::wstring adl_Gpu_RegistryPath;
inline std::wstring adl_Gpu_UniqueIdentifierHex;
inline std::wstring adl_Gpu_DeviceIdentifier;

//Display
inline int adl_Display_AdapterIndex = -1;
inline int adl_Display_DisplayIndex = -1;
inline std::wstring adl_Display_DeviceIdentifier;
inline int displayResolutionSwitchTimeSec = 15;
inline int displayResolutionRevertWidth = 0;
inline int displayResolutionRevertHeight = 0;
inline float displayResolutionRevertRefreshRate = 0.0F;
inline int displayResolutionRevertOrientation = 0;

//Timers
inline winrt::Windows::UI::Xaml::DispatcherTimer TimerNotification = NULL;
inline winrt::Windows::UI::Xaml::DispatcherTimer TimerResolutionSwitch = NULL;

//Settings
//Note: Do not use reference wrapper, loop uses cache and picks up changed settings before actually applied.
inline TuningFanSettings tuningFanSettingsProfile{ .Application = L"Global", .UsingProfile = true };
inline std::deque<TuningFanSettings> tuningFanSettingsCache{};

inline DisplaySettings displaySettingsProfile{ .Application = L"Global", .UsingProfile = true };
inline std::deque<DisplaySettings> displaySettingsCache{};

inline GraphicsSettings graphicsSettingsProfile{ .Application = L"Global" };
inline std::deque<GraphicsSettings> graphicsSettingsCache{};

inline MultimediaSettings multimediaSettingsProfile{ .Application = L"Global", .UsingProfile = true };
inline std::deque<MultimediaSettings> multimediaSettingsCache{};