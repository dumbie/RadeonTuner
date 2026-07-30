#pragma once
#include "pch.h"

namespace winrt::RadeonTuner::implementation
{
	//Cursor cache
	inline CoreCursorType cursorCurrent = CoreCursorType::Custom;
	inline CoreCursor cursorHand{ CoreCursorType::Hand, 0 };
	inline CoreCursor cursorArrow{ CoreCursorType::Arrow, 0 };
	inline CoreCursor cursorBeam{ CoreCursorType::IBeam, 0 };
	inline CoreCursor cursorHelp{ CoreCursorType::Help, 0 };
	inline CoreCursor cursorSizeNorthSouth{ CoreCursorType::SizeNorthSouth, 0 };
	inline CoreCursor cursorSizeWestEast{ CoreCursorType::SizeWestEast, 0 };

	/// <summary>
	/// Adjust mouse cursor to hovered framework element
	/// Usage: this.PointerMoved += PointerMoved_AdjustCursor; 
	/// </summary>
	void MainPage::PointerMoved_AdjustCursor(IInspectable const& sender, PointerRoutedEventArgs const& e)
	{
		try
		{
			//Note: WinUI2 does not show specific cursors when hovering over elements, using this as workaround.

			//Get original source element
			auto element = e.OriginalSource().try_as<winrt::Windows::UI::Xaml::FrameworkElement>();
			while (element)
			{
				if (element.try_as<winrt::Windows::UI::Xaml::Controls::Slider>())
				{
					if (cursorCurrent != CoreCursorType::SizeWestEast)
					{
						cursorCurrent = CoreCursorType::SizeWestEast;
						Window::Current().CoreWindow().PointerCursor(cursorSizeWestEast);
					}
					return;
				}
				if (element.try_as<winrt::Windows::UI::Xaml::Controls::Primitives::ScrollBar>())
				{
					if (cursorCurrent != CoreCursorType::SizeNorthSouth)
					{
						cursorCurrent = CoreCursorType::SizeNorthSouth;
						Window::Current().CoreWindow().PointerCursor(cursorSizeNorthSouth);
					}
					return;
				}
				else if (element.try_as<winrt::Windows::UI::Xaml::Controls::Button>())
				{
					if (cursorCurrent != CoreCursorType::Hand)
					{
						cursorCurrent = CoreCursorType::Hand;
						Window::Current().CoreWindow().PointerCursor(cursorHand);
					}
					return;
				}
				else if (element.try_as<winrt::Windows::UI::Xaml::Controls::ToggleSwitch>())
				{
					if (cursorCurrent != CoreCursorType::Hand)
					{
						cursorCurrent = CoreCursorType::Hand;
						Window::Current().CoreWindow().PointerCursor(cursorHand);
					}
					return;
				}
				else if (element.try_as<winrt::Windows::UI::Xaml::Controls::CheckBox>())
				{
					if (cursorCurrent != CoreCursorType::Hand)
					{
						cursorCurrent = CoreCursorType::Hand;
						Window::Current().CoreWindow().PointerCursor(cursorHand);
					}
					return;
				}
				else if (element.try_as<winrt::Windows::UI::Xaml::Controls::ComboBox>())
				{
					if (cursorCurrent != CoreCursorType::Hand)
					{
						cursorCurrent = CoreCursorType::Hand;
						Window::Current().CoreWindow().PointerCursor(cursorHand);
					}
					return;
				}
				else if (element.try_as<winrt::Windows::UI::Xaml::Controls::ListViewItem>())
				{
					if (cursorCurrent != CoreCursorType::Hand)
					{
						cursorCurrent = CoreCursorType::Hand;
						Window::Current().CoreWindow().PointerCursor(cursorHand);
					}
					return;
				}
				else if (element.try_as<winrt::Windows::UI::Xaml::Controls::TextBox>())
				{
					if (cursorCurrent != CoreCursorType::IBeam)
					{
						cursorCurrent = CoreCursorType::IBeam;
						Window::Current().CoreWindow().PointerCursor(cursorBeam);
					}
					return;
				}
				else if (winrt::Windows::UI::Xaml::Controls::ToolTipService::GetToolTip(element) != NULL)
				{
					if (cursorCurrent != CoreCursorType::Help)
					{
						cursorCurrent = CoreCursorType::Help;
						Window::Current().CoreWindow().PointerCursor(cursorHelp);
					}
					return;
				}

				//Loop visual tree parent
				element = winrt::Windows::UI::Xaml::Media::VisualTreeHelper::GetParent(element).try_as<winrt::Windows::UI::Xaml::FrameworkElement>();
			}

			//Set default cursor
			if (cursorCurrent != CoreCursorType::Arrow)
			{
				cursorCurrent = CoreCursorType::Arrow;
				Window::Current().CoreWindow().PointerCursor(cursorArrow);
			}
		}
		catch (...) {}
	}
}