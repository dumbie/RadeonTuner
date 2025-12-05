#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	//Load TuningFanSettings from file
	TuningFanSettings MainPage::TuningFanSettings_Load(std::string loadPath)
	{
		try
		{
			//Open settings file
			std::string jsonString = file_to_string(loadPath);

			//Parse settings file
			nlohmann::json jsonData = nlohmann::json::parse(jsonString);

			//Convert json to tuning fan settings
			return TuningFanSettings_Generate_FromJson(jsonData);
		}
		catch (...) {}
		return TuningFanSettings{};
	}

	//Save TuningFanSettings to file
	bool MainPage::TuningFanSettings_Save(TuningFanSettings tuningFanSettings, std::string savePath)
	{
		try
		{
			//Convert tuning fan settings
			nlohmann::json jsonData = TuningFanSettings_Convert_ToJson(tuningFanSettings);

			//Convert json to string
			std::string jsonString = jsonData.dump();

			//Save settings file
			return string_to_file(savePath, jsonString);
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	bool MainPage::TuningFanSettings_Convert_ToUI(TuningFanSettings tuningFanSettings, bool ignoreKeepActive)
	{
		try
		{
			if (!ignoreKeepActive && tuningFanSettings.KeepActive.has_value())
			{
				if (tuningFanSettings.KeepActive.value())
				{
					//Set button color
					SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
					button_Fan_Keep().Background(colorValid);
					button_Tuning_Keep().Background(colorValid);
				}
				else
				{
					//Set button color
					SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
					button_Fan_Keep().Background(colorInvalid);
					button_Tuning_Keep().Background(colorInvalid);
				}	
			}
			if (tuningFanSettings.CoreMin.has_value())
			{
				slider_Core_Min().Value(tuningFanSettings.CoreMin.value());
			}
			if (tuningFanSettings.CoreMax.has_value())
			{
				slider_Core_Max().Value(tuningFanSettings.CoreMax.value());
			}
			if (tuningFanSettings.MemoryMax.has_value())
			{
				slider_Memory_Max().Value(tuningFanSettings.MemoryMax.value());
			}
			if (tuningFanSettings.MemoryTiming.has_value())
			{
				combobox_Memory_Timing().SelectedIndex(tuningFanSettings.MemoryTiming.value());
			}
			if (tuningFanSettings.PowerLimit.has_value())
			{
				slider_Power_Limit().Value(tuningFanSettings.PowerLimit.value());
			}
			if (tuningFanSettings.PowerVoltage.has_value())
			{
				slider_Power_Voltage().Value(tuningFanSettings.PowerVoltage.value());
			}
			if (tuningFanSettings.PowerTDC.has_value())
			{
				slider_Power_TDC().Value(tuningFanSettings.PowerTDC.value());
			}
			if (tuningFanSettings.FanZeroRpm.has_value())
			{
				toggleswitch_Fan_Zero_Rpm().IsOn(tuningFanSettings.FanZeroRpm.value());
			}
			if (tuningFanSettings.FanSpeed0.has_value())
			{
				slider_Fan_Speed_0().Value(tuningFanSettings.FanSpeed0.value());
			}
			if (tuningFanSettings.FanTemp0.has_value())
			{
				slider_Fan_Temp_0().Value(tuningFanSettings.FanTemp0.value());
			}
			if (tuningFanSettings.FanSpeed1.has_value())
			{
				slider_Fan_Speed_1().Value(tuningFanSettings.FanSpeed1.value());
			}
			if (tuningFanSettings.FanTemp1.has_value())
			{
				slider_Fan_Temp_1().Value(tuningFanSettings.FanTemp1.value());
			}
			if (tuningFanSettings.FanSpeed2.has_value())
			{
				slider_Fan_Speed_2().Value(tuningFanSettings.FanSpeed2.value());
			}
			if (tuningFanSettings.FanTemp2.has_value())
			{
				slider_Fan_Temp_2().Value(tuningFanSettings.FanTemp2.value());
			}
			if (tuningFanSettings.FanSpeed3.has_value())
			{
				slider_Fan_Speed_3().Value(tuningFanSettings.FanSpeed3.value());
			}
			if (tuningFanSettings.FanTemp3.has_value())
			{
				slider_Fan_Temp_3().Value(tuningFanSettings.FanTemp3.value());
			}
			if (tuningFanSettings.FanSpeed4.has_value())
			{
				slider_Fan_Speed_4().Value(tuningFanSettings.FanSpeed4.value());
			}
			if (tuningFanSettings.FanTemp4.has_value())
			{
				slider_Fan_Temp_4().Value(tuningFanSettings.FanTemp4.value());
			}

			//Return result
			return true;
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}

	TuningFanSettings MainPage::TuningFanSettings_Generate_FromUI(bool keepActive)
	{
		TuningFanSettings tuningFanSettings{};
		try
		{
			//Device identifier
			std::wstring device_id_w = AdlxGetDeviceIdentifier(ppGpuInfo);
			if (!device_id_w.empty())
			{
				tuningFanSettings.DeviceId = wstring_to_string(device_id_w);
			}

			//Keep active
			tuningFanSettings.KeepActive = keepActive;

			if (slider_Core_Min().IsEnabled())
			{
				tuningFanSettings.CoreMin = (int)slider_Core_Min().Value();
			}
			if (slider_Core_Max().IsEnabled())
			{
				tuningFanSettings.CoreMax = (int)slider_Core_Max().Value();
			}
			if (slider_Memory_Max().IsEnabled())
			{
				tuningFanSettings.MemoryMax = (int)slider_Memory_Max().Value();
			}
			if (combobox_Memory_Timing().IsEnabled())
			{
				tuningFanSettings.MemoryTiming = (int)combobox_Memory_Timing().SelectedIndex();
			}
			if (slider_Power_Limit().IsEnabled())
			{
				tuningFanSettings.PowerLimit = (int)slider_Power_Limit().Value();
			}
			if (slider_Power_Voltage().IsEnabled())
			{
				tuningFanSettings.PowerVoltage = (int)slider_Power_Voltage().Value();
			}
			if (slider_Power_TDC().IsEnabled())
			{
				tuningFanSettings.PowerTDC = (int)slider_Power_TDC().Value();
			}
			if (toggleswitch_Fan_Zero_Rpm().IsEnabled())
			{
				tuningFanSettings.FanZeroRpm = (bool)toggleswitch_Fan_Zero_Rpm().IsOn();
			}
			if (slider_Fan_Speed_0().IsEnabled())
			{
				tuningFanSettings.FanSpeed0 = (int)slider_Fan_Speed_0().Value();
			}
			if (slider_Fan_Temp_0().IsEnabled())
			{
				tuningFanSettings.FanTemp0 = (int)slider_Fan_Temp_0().Value();
			}
			if (slider_Fan_Speed_1().IsEnabled())
			{
				tuningFanSettings.FanSpeed1 = (int)slider_Fan_Speed_1().Value();
			}
			if (slider_Fan_Temp_1().IsEnabled())
			{
				tuningFanSettings.FanTemp1 = (int)slider_Fan_Temp_1().Value();
			}
			if (slider_Fan_Speed_2().IsEnabled())
			{
				tuningFanSettings.FanSpeed2 = (int)slider_Fan_Speed_2().Value();
			}
			if (slider_Fan_Temp_2().IsEnabled())
			{
				tuningFanSettings.FanTemp2 = (int)slider_Fan_Temp_2().Value();
			}
			if (slider_Fan_Speed_3().IsEnabled())
			{
				tuningFanSettings.FanSpeed3 = (int)slider_Fan_Speed_3().Value();
			}
			if (slider_Fan_Temp_3().IsEnabled())
			{
				tuningFanSettings.FanTemp3 = (int)slider_Fan_Temp_3().Value();
			}
			if (slider_Fan_Speed_4().IsEnabled())
			{
				tuningFanSettings.FanSpeed4 = (int)slider_Fan_Speed_4().Value();
			}
			if (slider_Fan_Temp_4().IsEnabled())
			{
				tuningFanSettings.FanTemp4 = (int)slider_Fan_Temp_4().Value();
			}
		}
		catch (...) {}
		return tuningFanSettings;
	}

	TuningFanSettings MainPage::TuningFanSettings_Generate_FromJson(nlohmann::json jsonData)
	{
		TuningFanSettings tuningFanSettings{};
		try
		{
			if (jsonData.contains("DeviceId"))
			{
				std::string device_id_importa = jsonData["DeviceId"].get<std::string>();
				if (!device_id_importa.empty())
				{
					tuningFanSettings.DeviceId = device_id_importa;
				}
			}
			if (jsonData.contains("KeepActive"))
			{
				tuningFanSettings.KeepActive = (bool)jsonData["KeepActive"];
			}
			if (jsonData.contains("CoreMin"))
			{
				tuningFanSettings.CoreMin = (int)jsonData["CoreMin"];
			}
			if (jsonData.contains("CoreMax"))
			{
				tuningFanSettings.CoreMax = (int)jsonData["CoreMax"];
			}
			if (jsonData.contains("MemoryMax"))
			{
				tuningFanSettings.MemoryMax = (int)jsonData["MemoryMax"];
			}
			if (jsonData.contains("MemoryTiming"))
			{
				tuningFanSettings.MemoryTiming = (int)jsonData["MemoryTiming"];
			}
			if (jsonData.contains("PowerLimit"))
			{
				tuningFanSettings.PowerLimit = (int)jsonData["PowerLimit"];
			}
			if (jsonData.contains("PowerVoltage"))
			{
				tuningFanSettings.PowerVoltage = (int)jsonData["PowerVoltage"];
			}
			if (jsonData.contains("PowerTDC"))
			{
				tuningFanSettings.PowerTDC = (int)jsonData["PowerTDC"];
			}
			if (jsonData.contains("FanZeroRpm"))
			{
				tuningFanSettings.FanZeroRpm = (bool)jsonData["FanZeroRpm"];
			}
			if (jsonData.contains("FanSpeed0"))
			{
				tuningFanSettings.FanSpeed0 = (int)jsonData["FanSpeed0"];
			}
			if (jsonData.contains("FanTemp0"))
			{
				tuningFanSettings.FanTemp0 = (int)jsonData["FanTemp0"];
			}
			if (jsonData.contains("FanSpeed1"))
			{
				tuningFanSettings.FanSpeed1 = (int)jsonData["FanSpeed1"];
			}
			if (jsonData.contains("FanTemp1"))
			{
				tuningFanSettings.FanTemp1 = (int)jsonData["FanTemp1"];
			}
			if (jsonData.contains("FanSpeed2"))
			{
				tuningFanSettings.FanSpeed2 = (int)jsonData["FanSpeed2"];
			}
			if (jsonData.contains("FanTemp2"))
			{
				tuningFanSettings.FanTemp2 = (int)jsonData["FanTemp2"];
			}
			if (jsonData.contains("FanSpeed3"))
			{
				tuningFanSettings.FanSpeed3 = (int)jsonData["FanSpeed3"];
			}
			if (jsonData.contains("FanTemp3"))
			{
				tuningFanSettings.FanTemp3 = (int)jsonData["FanTemp3"];
			}
			if (jsonData.contains("FanSpeed4"))
			{
				tuningFanSettings.FanSpeed4 = (int)jsonData["FanSpeed4"];
			}
			if (jsonData.contains("FanTemp4"))
			{
				tuningFanSettings.FanTemp4 = (int)jsonData["FanTemp4"];
			}
		}
		catch (...) {}
		return tuningFanSettings;
	}

	nlohmann::json MainPage::TuningFanSettings_Convert_ToJson(TuningFanSettings tuningFanSettings)
	{
		nlohmann::json jsonData{};
		try
		{
			if (tuningFanSettings.DeviceId.has_value())
			{
				jsonData["DeviceId"] = tuningFanSettings.DeviceId.value();
			}
			if (tuningFanSettings.KeepActive.has_value())
			{
				jsonData["KeepActive"] = tuningFanSettings.KeepActive.value();
			}
			if (tuningFanSettings.CoreMin.has_value())
			{
				jsonData["CoreMin"] = tuningFanSettings.CoreMin.value();
			}
			if (tuningFanSettings.CoreMax.has_value())
			{
				jsonData["CoreMax"] = tuningFanSettings.CoreMax.value();
			}
			if (tuningFanSettings.MemoryTiming.has_value())
			{
				jsonData["MemoryTiming"] = tuningFanSettings.MemoryTiming.value();
			}
			if (tuningFanSettings.MemoryMax.has_value())
			{
				jsonData["MemoryMax"] = tuningFanSettings.MemoryMax.value();
			}
			if (tuningFanSettings.PowerLimit.has_value())
			{
				jsonData["PowerLimit"] = tuningFanSettings.PowerLimit.value();
			}
			if (tuningFanSettings.PowerVoltage.has_value())
			{
				jsonData["PowerVoltage"] = tuningFanSettings.PowerVoltage.value();
			}
			if (tuningFanSettings.PowerTDC.has_value())
			{
				jsonData["PowerTDC"] = tuningFanSettings.PowerTDC.value();
			}
			if (tuningFanSettings.FanZeroRpm.has_value())
			{
				jsonData["FanZeroRpm"] = tuningFanSettings.FanZeroRpm.value();
			}
			if (tuningFanSettings.FanSpeed0.has_value())
			{
				jsonData["FanSpeed0"] = tuningFanSettings.FanSpeed0.value();
			}
			if (tuningFanSettings.FanTemp0.has_value())
			{
				jsonData["FanTemp0"] = tuningFanSettings.FanTemp0.value();
			}
			if (tuningFanSettings.FanSpeed1.has_value())
			{
				jsonData["FanSpeed1"] = tuningFanSettings.FanSpeed1.value();
			}
			if (tuningFanSettings.FanTemp1.has_value())
			{
				jsonData["FanTemp1"] = tuningFanSettings.FanTemp1.value();
			}
			if (tuningFanSettings.FanSpeed2.has_value())
			{
				jsonData["FanSpeed2"] = tuningFanSettings.FanSpeed2.value();
			}
			if (tuningFanSettings.FanTemp2.has_value())
			{
				jsonData["FanTemp2"] = tuningFanSettings.FanTemp2.value();
			}
			if (tuningFanSettings.FanSpeed3.has_value())
			{
				jsonData["FanSpeed3"] = tuningFanSettings.FanSpeed3.value();
			}
			if (tuningFanSettings.FanTemp3.has_value())
			{
				jsonData["FanTemp3"] = tuningFanSettings.FanTemp3.value();
			}
			if (tuningFanSettings.FanSpeed4.has_value())
			{
				jsonData["FanSpeed4"] = tuningFanSettings.FanSpeed4.value();
			}
			if (tuningFanSettings.FanTemp4.has_value())
			{
				jsonData["FanTemp4"] = tuningFanSettings.FanTemp4.value();
			}
		}
		catch (...) {}
		return jsonData;
	}
}