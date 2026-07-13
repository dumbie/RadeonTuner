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
		hstring _Name;
		hstring Name()
		{
			return _Name;
		}
		void Name(hstring value)
		{
			_Name = value;
		}

		//Resolution Width
		int _ResolutionWidth;
		int ResolutionWidth()
		{
			return _ResolutionWidth;
		}
		void ResolutionWidth(int value)
		{
			_ResolutionWidth = value;
		}

		//Resolution Height
		int _ResolutionHeight;
		int ResolutionHeight()
		{
			return _ResolutionHeight;
		}
		void ResolutionHeight(int value)
		{
			_ResolutionHeight = value;
		}

		//Refresh Rate
		float _RefreshRate;
		float RefreshRate()
		{
			return _RefreshRate;
		}
		void RefreshRate(float value)
		{
			_RefreshRate = value;
		}
	};
}

namespace winrt::RadeonTuner::factory_implementation
{
	struct DisplayDetailsIdl : DisplayDetailsIdlT<DisplayDetailsIdl, implementation::DisplayDetailsIdl> {};
}