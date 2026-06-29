//Pragma
#pragma once
#pragma comment(lib, "Shell32.lib")

//Includes
#include <Windows.h>
#undef GetCurrentTime
#include <string>
#include <thread>
#include <functional>
#include <iostream>
#include <regex>
#include <ranges>
#include <Windows.UI.Xaml.Hosting.DesktopWindowXamlSource.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.XamlTypeInfo.h>
#include <winrt/Windows.Devices.Input.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Input.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Data.h>
#include <winrt/Windows.UI.Xaml.Shapes.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.UI.Xaml.Markup.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Xaml.Input.h>

//Namespaces
namespace winrt
{
	using namespace Windows::Devices::Input;
	using namespace Windows::Foundation;
	using namespace Windows::Foundation::Collections;
	using namespace Windows::UI::Core;
	using namespace Windows::UI::Input;
	using namespace Windows::UI::Xaml;
	using namespace Windows::UI::Xaml::Controls;
	using namespace Windows::UI::Xaml::Controls::Primitives;
	using namespace Windows::UI::Xaml::Shapes;
	using namespace Windows::UI::Xaml::Hosting;
	using namespace Windows::UI::Xaml::Markup;
	using namespace Windows::UI::Xaml::Media;
	using namespace Windows::UI::Xaml::Input;
}

//Arnold Vink Code
#include "..\..\ArnoldVinkCode\CPP\AVPch.h"

//ADL
#include "ADL\adl_sdk.h"

//Classes
#include "AdlAppsClass.h"
#include "DisplaySettingsClass.h"
#include "GraphicsSettingsClass.h"
#include "GraphicsStatusClass.h"
#include "TuningFanSettingsClass.h"