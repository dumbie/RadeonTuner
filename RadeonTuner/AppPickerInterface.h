#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::IAsyncOperation<winrt::IVector<RadeonTuner::AppPickerIdl>> MainPage::AdlAppPickerAdd()
	{
		auto applist = winrt::single_threaded_observable_vector<RadeonTuner::AppPickerIdl>();
		try
		{
			//Select application source
			std::vector<std::wstring> messageAnswers{ L"Executable file", L"Game from launcher", L"Running process", L"Cancel" };
			int messageResult = co_await ShowMessageBox(L"Add application", L"Select the source you want to add an application from.", messageAnswers);

			//Show application picker
			if (messageResult == 0)
			{
				//Show file dialog
				co_return AdlAppPickerAddFile();
			}
			else if (messageResult == 1)
			{
				//Show launcher dialog
				co_return co_await AdlAppPickerAddLauncher();
			}
			else if (messageResult == 2)
			{
				//Show process dialog
				co_return co_await AdlAppPickerAddProcess();
			}
		}
		catch (...) {}
		//Return result
		co_return applist;
	}

	winrt::IVector<RadeonTuner::AppPickerIdl> MainPage::AdlAppPickerAddFile()
	{
		auto selectedList = winrt::single_threaded_observable_vector<RadeonTuner::AppPickerIdl>();
		try
		{
			//Show file dialog
			std::wstring importPath = filepicker_open(NULL, L"Select application executable...", { { L"Executable files", L"*.exe" }, { L"Binary files", L"*.bin" } });

			//Check file path
			if (importPath.empty())
			{
				return selectedList;
			}

			//Extract file name from path
			std::wstring fileName = PathGetFileName(importPath);

			//Append application picker item
			RadeonTuner::AppPickerIdl appPicker;
			appPicker.ExePath(importPath);
			appPicker.ExeName(fileName);
			selectedList.Append(appPicker);
		}
		catch (...) {}
		//Return result
		return selectedList;
	}

	winrt::IAsyncOperation<winrt::IVector<RadeonTuner::AppPickerIdl>> MainPage::AdlAppPickerAddProcess()
	{
		auto selectedList = winrt::single_threaded_observable_vector<RadeonTuner::AppPickerIdl>();
		try
		{
			//Get running processes
			auto pickerList = winrt::single_threaded_observable_vector<RadeonTuner::AppPickerIdl>();
			std::vector<AVProcess> processList = Get_ProcessAll();
			for (AVProcess process : processList)
			{
				try
				{
					//Check if process is valid
					if (!process.Validate())
					{
						continue;
					}

					//Get application main window handle
					HWND windowHandleMain = process.WindowHandleMain();

					//Check if application has valid main window
					if (windowHandleMain == NULL)
					{
						continue;
					}

					//Add process
					RadeonTuner::AppPickerIdl appPicker;
					appPicker.Detail(number_to_wstring(process.Identifier()));
					appPicker.AppName(process.ExeNameNoExt());
					appPicker.ExeName(process.ExeName());
					pickerList.Append(appPicker);
				}
				catch (...) {}
			}

			//Show application picker
			button_Overlay_AppPicker_Confirm().Visibility(Visibility::Visible);
			button_Overlay_AppPicker_Cancel().Visibility(Visibility::Visible);
			button_Overlay_AppPicker_Confirm().Content(box_value(L"Add selected"));
			textblock_Overlay_AppPicker_Text().Text(L"Add processes");
			grid_Overlay_AppPicker().Visibility(Visibility::Visible);

			//Set combobox items source
			listview_Overlay_AppPicker().ItemsSource(pickerList);

			//Update variables
			appPickerCompleted = false;
			appPickerCancel = false;

			//Wait in background
			while (!appPickerCompleted && !appPickerCancel)
			{
				co_await AsyncTaskDelay(100, AppVariables::App.GetDispatcher());
			}

			//Append selected items
			if (appPickerCompleted)
			{
				//Get selected items
				auto selectedItems = listview_Overlay_AppPicker().SelectedItems();
				for (auto const& itemBoxed : selectedItems)
				{
					//Unbox selected item
					RadeonTuner::AppPickerIdl itemUnboxed = itemBoxed.as<RadeonTuner::AppPickerIdl>();
					selectedList.Append(itemUnboxed);
				}
			}

			//Hide overlay and clear items
			grid_Overlay_AppPicker().Visibility(Visibility::Collapsed);
			listview_Overlay_AppPicker().ItemsSource(NULL);
		}
		catch (...) {}
		//Return result
		co_return selectedList;
	}

	winrt::IAsyncOperation<winrt::IVector<RadeonTuner::AppPickerIdl>> MainPage::AdlAppPickerAddLauncher()
	{
		auto selectedList = winrt::single_threaded_observable_vector<RadeonTuner::AppPickerIdl>();
		try
		{
			//Set executable filter words
			//Note: Some games use a launcher before running the actual game executable, using this list we can filter out some launchers.
			std::vector<std::wstring> executableFilter{ L"launcher", L"launcer", L"starter", L"config", L"setup", L"tools", L"install", L"bootstrapper", L"dedicated", L"server", L"service", L"boot.exe" };

			//Create application picker list
			auto pickerList = winrt::single_threaded_observable_vector<RadeonTuner::AppPickerIdl>();

			//Get library folders from Steam
			std::vector<uint32_t> installedAppIds{};
			auto libraryFolders = LauncherSteam::LibraryFolders::GetLibraryFolders("");
			for (const auto& folder : libraryFolders)
			{
				if (folder.apps.has_value())
				{
					for (const auto& appId : folder.apps.value())
					{
						installedAppIds.push_back(std::stoul(appId));
					}
				}
			}

			//Get games from Steam
			auto launcherApps = LauncherSteam::AppInfo::GetApps("");
			for (const auto& app : launcherApps)
			{
				try
				{
					//Check if app is installed
					if (std::find(installedAppIds.begin(), installedAppIds.end(), app.appid) == installedAppIds.end())
					{
						continue;
					}

					auto appName = app.name;
					auto appExecutable = app.executable;
					if (appName.has_value() && appExecutable.has_value())
					{
						//Application name
						std::wstring appNameW = string_to_wstring(appName.value());

						//Executable name
						std::wstring exeNameW = string_to_wstring(appExecutable.value());
						exeNameW = PathGetFileName(exeNameW);
						std::wstring exeNameLowerW = wstring_to_lower(exeNameW);

						//Check if executable contains exe
						if (exeNameLowerW.find(L".exe") == std::wstring::npos)
						{
							continue;
						}

						//Check executable filter strings
						bool filtered = false;
						for (const auto& filterString : executableFilter)
						{
							if (exeNameLowerW.find(filterString) != std::wstring::npos)
							{
								filtered = true;
								break;
							}
						}
						if (filtered)
						{
							continue;
						}

						//Add game
						RadeonTuner::AppPickerIdl appPicker;
						appPicker.IconPath(L"/Assets/Cross.png");
						appPicker.Detail(exeNameW);
						appPicker.AppName(appNameW);
						appPicker.ExeName(exeNameW);
						pickerList.Append(appPicker);
					}
				}
				catch (...) {}
			}

			//Sort applications by name
			auto count = pickerList.Size();
			for (uint32_t i = 0; i < count; i++)
			{
				for (uint32_t j = i + 1; j < count; j++)
				{
					auto a = pickerList.GetAt(i);
					auto b = pickerList.GetAt(j);
					if (a.AppName() > b.AppName())
					{
						pickerList.SetAt(i, b);
						pickerList.SetAt(j, a);
					}
				}
			}

			//Show application picker
			button_Overlay_AppPicker_Confirm().Visibility(Visibility::Visible);
			button_Overlay_AppPicker_Cancel().Visibility(Visibility::Visible);
			button_Overlay_AppPicker_Confirm().Content(box_value(L"Add selected"));
			textblock_Overlay_AppPicker_Text().Text(L"Add games");
			grid_Overlay_AppPicker().Visibility(Visibility::Visible);

			//Set combobox items source
			listview_Overlay_AppPicker().ItemsSource(pickerList);

			//Update variables
			appPickerCompleted = false;
			appPickerCancel = false;

			//Wait in background
			while (!appPickerCompleted && !appPickerCancel)
			{
				co_await AsyncTaskDelay(100, AppVariables::App.GetDispatcher());
			}

			//Append selected items
			if (appPickerCompleted)
			{
				//Get selected items
				auto selectedItems = listview_Overlay_AppPicker().SelectedItems();
				for (auto const& itemBoxed : selectedItems)
				{
					//Unbox selected item
					RadeonTuner::AppPickerIdl itemUnboxed = itemBoxed.as<RadeonTuner::AppPickerIdl>();
					selectedList.Append(itemUnboxed);
				}
			}

			//Hide overlay and clear items
			grid_Overlay_AppPicker().Visibility(Visibility::Collapsed);
			listview_Overlay_AppPicker().ItemsSource(NULL);
		}
		catch (...) {}
		//Return result
		co_return selectedList;
	}

	winrt::IAsyncOperation<winrt::IVector<RadeonTuner::AppPickerIdl>> MainPage::AdlAppPickerRemoveApp()
	{
		auto selectedList = winrt::single_threaded_observable_vector<RadeonTuner::AppPickerIdl>();
		try
		{
			//Get all applications
			auto appListIdl = winrt::single_threaded_observable_vector<RadeonTuner::AppPickerIdl>();
			std::vector<AdlApplication> appList = AdlAppsLoad(L"3D_User");

			//Check applications
			if (appList.size() == 0)
			{
				co_return selectedList;
			}

			//Append applications
			for (AdlApplication app : appList)
			{
				try
				{
					//Add application
					RadeonTuner::AppPickerIdl appPicker;
					appPicker.AppName(app.FileName);
					appPicker.ExeName(app.FileName);
					appPicker.ExePath(app.FilePath);
					appListIdl.Append(appPicker);
				}
				catch (...) {}
			}

			//Show application picker
			button_Overlay_AppPicker_Confirm().Visibility(Visibility::Visible);
			button_Overlay_AppPicker_Cancel().Visibility(Visibility::Visible);
			button_Overlay_AppPicker_Confirm().Content(box_value(L"Remove selected"));
			textblock_Overlay_AppPicker_Text().Text(L"Remove applications");
			grid_Overlay_AppPicker().Visibility(Visibility::Visible);

			//Set combobox items source
			listview_Overlay_AppPicker().ItemsSource(appListIdl);

			//Update variables
			appPickerCompleted = false;
			appPickerCancel = false;

			//Wait in background
			while (!appPickerCompleted && !appPickerCancel)
			{
				co_await AsyncTaskDelay(100, AppVariables::App.GetDispatcher());
			}

			//Append selected items
			if (appPickerCompleted)
			{
				//Get selected items
				auto selectedItems = listview_Overlay_AppPicker().SelectedItems();
				for (auto const& itemBoxed : selectedItems)
				{
					//Unbox selected item
					RadeonTuner::AppPickerIdl itemUnboxed = itemBoxed.as<RadeonTuner::AppPickerIdl>();
					selectedList.Append(itemUnboxed);
				}
			}

			//Hide overlay and clear items
			grid_Overlay_AppPicker().Visibility(Visibility::Collapsed);
			listview_Overlay_AppPicker().ItemsSource(NULL);
		}
		catch (...) {}
		//Return result
		co_return selectedList;
	}
}