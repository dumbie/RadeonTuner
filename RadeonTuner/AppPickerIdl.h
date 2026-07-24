#pragma once
#include "AppPickerIdl.g.h"

namespace winrt::RadeonTuner::implementation
{
	struct AppPickerIdl : AppPickerIdlT<AppPickerIdl>
	{
		//Default
		AppPickerIdl() {}

		//Identifier
		int _Identifier = -1;
		int Identifier()
		{
			return _Identifier;
		}
		void Identifier(int value)
		{
			_Identifier = value;
		}

		//AppName
		hstring _AppName = L"";
		hstring AppName()
		{
			return _AppName;
		}
		void AppName(hstring value)
		{
			_AppName = value;
		}

		//IconPath
		hstring _IconPath = L"/Assets/Apps.png";
		hstring IconPath()
		{
			return _IconPath;
		}
		void IconPath(hstring value)
		{
			_IconPath = value;
		}

		//ExePath
		hstring _ExePath = L"";
		hstring ExePath()
		{
			return _ExePath;
		}
		void ExePath(hstring value)
		{
			_ExePath = value;
		}

		//ExeName
		hstring _ExeName = L"";
		hstring ExeName()
		{
			return _ExeName;
		}
		void ExeName(hstring value)
		{
			_ExeName = value;
		}

		//LauncherName
		hstring _LauncherName = L"";
		hstring LauncherName()
		{
			return _LauncherName;
		}
		void LauncherName(hstring value)
		{
			_LauncherName = value;
		}

		//Detail
		hstring _Detail = L"";
		hstring Detail()
		{
			return _Detail;
		}
		void Detail(hstring value)
		{
			_Detail = value;
		}
	};
}

namespace winrt::RadeonTuner::factory_implementation
{
	struct AppPickerIdl : AppPickerIdlT<AppPickerIdl, implementation::AppPickerIdl> {};
}