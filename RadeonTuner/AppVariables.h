#pragma once
#include "App.h"

namespace AppVariables
{
	inline HINSTANCE hInstance = NULL;
	inline AVSettingsJson Settings = AVSettingsJson();
	inline winrt::RadeonTuner::implementation::App App = winrt::RadeonTuner::implementation::App();
	inline winrt::Windows::UI::Xaml::DispatcherTimer TimerNotification = NULL;
}