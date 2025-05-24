#pragma once

//Defines
#undef GetCurrentTime

//Includes
#include <string>
#include <thread>
#include <Windows.h>
#include <Windows.UI.Xaml.Hosting.DesktopWindowXamlSource.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.XamlTypeInfo.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Shapes.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.UI.Xaml.Markup.h>
#include <winrt/Windows.UI.Xaml.Media.h>

//Namespaces
using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Shapes;
using namespace Windows::UI::Xaml::Hosting;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Markup;
using namespace Windows::UI::Xaml::Media;

//Arnold Vink code
#include "..\..\ArnoldVinkCode\CPP\AVDebug.h"
#include "..\..\ArnoldVinkCode\CPP\AVFinally.h"
#include "..\..\ArnoldVinkCode\CPP\AVHighResDelay.h"
#include "..\..\ArnoldVinkCode\CPP\AVString.h"

//ADLX
#include "ADLX\ADLXHelper\Windows\Cpp\ADLXHelper.h"
#include "ADLX\Include\I3DSettings.h"
using namespace adlx;