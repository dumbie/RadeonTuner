#pragma once
#include "pch.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::IAsyncAction MainPage::button_GpuSelect_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { co_return; }

			//Get all gpu's
			std::vector<AdapterInfo> listGpus = AdlGetGpuAll();

			//List all GPU's
			std::vector<std::wstring> messageAnswers{};
			for (AdapterInfo adapterInfo : listGpus)
			{
				messageAnswers.push_back(char_to_wstring(adapterInfo.strAdapterName));
			}

			//Show selection prompt
			int messageResult = co_await ShowMessageBox(L"Select graphics card", L"Select the graphics card you want to adjust.", messageAnswers);

			//Get selected GPU
			AdapterInfo adapterInfo = listGpus[messageResult];

			//Load selected GPU values
			co_await AdlxValuesLoadSelectGpu(adapterInfo);
		}
		catch (...) {}
	}

	winrt::IAsyncAction MainPage::button_DisplaySelect_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { co_return; }

			//Get all displays
			std::vector<ADLDisplayInfo> displayList = AdlGetDisplayAll();

			//List all displays
			std::vector<std::wstring> messageAnswers{};
			for (ADLDisplayInfo displayInfo : displayList)
			{
				messageAnswers.push_back(char_to_wstring(displayInfo.strDisplayName));
			}

			//Show selection prompt
			int messageResult = co_await ShowMessageBox(L"Select display", L"Select the display you want to adjust.", messageAnswers);

			//Get selected display
			ADLDisplayInfo displayInfo = displayList[messageResult];

			//Load selected display values
			co_await AdlxValuesLoadSelectDisplay(displayInfo);
		}
		catch (...) {}
	}

	winrt::IAsyncAction MainPage::button_AppSelect_Graphics_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { co_return; }

			//Get all applications
			std::vector<std::wstring> messageAnswers = GraphicsSettings_Profile_GetAllApps(adl_Gpu_DeviceIdentifier);

			//Add global application
			messageAnswers.insert(messageAnswers.begin(), L"Global");

			//Show selection prompt
			int messageResult = co_await ShowMessageBox(L"Select application", L"Select the application you want to adjust.", messageAnswers);

			//Get selected application
			std::wstring selectedApplication = messageAnswers[messageResult];

			//Load graphics settings
			co_await AdlxValuesLoadSelectGraphicsApp(adl_Gpu_AdapterIndex, selectedApplication);
		}
		catch (...) {}
	}

	winrt::IAsyncAction MainPage::button_AppSelect_Tuning_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { co_return; }

			//Get all applications
			std::vector<std::wstring> messageAnswers = TuningFanSettings_Profile_GetAllApps(adl_Gpu_DeviceIdentifier);

			//Add global application
			messageAnswers.insert(messageAnswers.begin(), L"Global");

			//Show selection prompt
			int messageResult = co_await ShowMessageBox(L"Select application", L"Select the application you want to adjust.", messageAnswers);

			//Get selected application
			std::wstring selectedApplication = messageAnswers[messageResult];

			//Load tuning and fans settings
			co_await AdlxValuesLoadSelectTuningApp(adl_Gpu_AdapterIndex, selectedApplication);
		}
		catch (...) {}
	}

	winrt::IAsyncAction MainPage::button_AppSelect_Display_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { co_return; }

			//Get all applications
			std::vector<std::wstring> messageAnswers = DisplaySettings_Profile_GetAllApps(adl_Display_DeviceIdentifier);

			//Add global application
			messageAnswers.insert(messageAnswers.begin(), L"Global");

			//Show selection prompt
			int messageResult = co_await ShowMessageBox(L"Select application", L"Select the application you want to adjust.", messageAnswers);

			//Get selected application
			std::wstring selectedApplication = messageAnswers[messageResult];

			//Load display settings
			co_await AdlxValuesLoadSelectDisplayApp(adl_Display_AdapterIndex, adl_Display_DisplayIndex, selectedApplication);
		}
		catch (...) {}
	}
}