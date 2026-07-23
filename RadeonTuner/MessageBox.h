#pragma once
#include "pch.h"
#include "MainPage.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::IAsyncOperation<int> MainPage::ShowMessageBox(std::wstring Question, std::wstring Description, std::vector<std::wstring> Answers)
	{
		try
		{
			//Set messagebox texts
			textblock_Overlay_MessageBox_Text().Text(Question);
			if (Description.empty())
			{
				textblock_Overlay_MessageBox_SubText().Visibility(Visibility::Collapsed);
			}
			else
			{
				textblock_Overlay_MessageBox_SubText().Text(Description);
				textblock_Overlay_MessageBox_SubText().Visibility(Visibility::Visible);
			}

			//Check messagebox answers
			if (Answers.size() == 0)
			{
				Answers = { L"Close" };
			}

			//Set messagebox answers
			listview_Overlay_MessageBox().Items().Clear();
			for (auto answer : Answers)
			{
				listview_Overlay_MessageBox().Items().Append(box_value(answer));
			}
			listview_Overlay_MessageBox().SelectedIndex(-1);

			//Show messagebox
			grid_Overlay_MessageBox().Visibility(Visibility::Visible);

			//Focus on listbox
			listview_Overlay_MessageBox().Focus(FocusState::Keyboard);

			//Update variables
			messageBoxComplete = false;

			//Wait in background
			while (!messageBoxComplete)
			{
				co_await AsyncTaskDelay(100, AppVariables::App.GetDispatcher());
			}

			//Hide and clear messagebox
			listview_Overlay_MessageBox().ItemsSource(NULL);
			grid_Overlay_MessageBox().Visibility(Visibility::Collapsed);

			//Get result
			auto selectedIndex = listview_Overlay_MessageBox().SelectedIndex();

			//Return result
			AVDebugWriteLine("MessageBox result: " << selectedIndex);
			co_return selectedIndex;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("MessageBox failed.");
			co_return -1;
		}
	}

	void MainPage::listview_Overlay_MessageBox_ItemClick(IInspectable const& sender, ItemClickEventArgs const& e)
	{
		try
		{
			//Update variables
			messageBoxComplete = true;
		}
		catch (...) {}
	}
}