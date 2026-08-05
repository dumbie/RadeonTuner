#pragma once
#include "App.h"

namespace AppVariables
{
	inline HINSTANCE hInstance = NULL;
	inline BOOL LaunchKeepActive = true;
	inline BOOL ApplicationExiting = false;
	inline std::wstring SaveDataPath = L"";
	inline AVSettingsJson Settings = AVSettingsJson();
	inline winrt::RadeonTuner::implementation::App App = winrt::RadeonTuner::implementation::App();
}