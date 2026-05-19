#pragma once
#include "DisplayDetailsIdl.g.h"

namespace winrt::RadeonTuner::implementation
{
	struct DisplayDetailsIdl : DisplayDetailsIdlT<DisplayDetailsIdl>
	{
		//Default
		DisplayDetailsIdl() {}

		//IndexAdapter
		int _IndexAdapter = 0;
		int IndexAdapter()
		{
			return _IndexAdapter;
		}
		void IndexAdapter(int value)
		{
			_IndexAdapter = value;
		}

		//IndexDisplay
		int _IndexDisplay = 0;
		int IndexDisplay()
		{
			return _IndexDisplay;
		}
		void IndexDisplay(int value)
		{
			_IndexDisplay = value;
		}

		//Name
		std::wstring _Name;
		hstring Name()
		{
			return _Name.c_str();
		}
		void Name(hstring value)
		{
			_Name = value.c_str();
		}
	};
}

namespace winrt::RadeonTuner::factory_implementation
{
	struct DisplayDetailsIdl : DisplayDetailsIdlT<DisplayDetailsIdl, implementation::DisplayDetailsIdl>
	{
	};
}