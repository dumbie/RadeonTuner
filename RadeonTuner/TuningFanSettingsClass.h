#pragma once
#include "pch.h"

struct TuningFanSettings
{
	//Settings
	std::optional<std::wstring> DeviceId;
	std::optional<std::wstring> Application;
	AdlSettingInt CoreMin;
	AdlSettingInt CoreMax;
	AdlSettingInt MemoryTiming;
	AdlSettingInt MemoryMax;
	AdlSettingInt PowerLimit;
	AdlSettingInt PowerVoltage;
	AdlSettingInt PowerTDC;
	AdlSettingInt FanZeroRpm;
	AdlSettingInt FanSpeed0;
	AdlSettingInt FanTemp0;
	AdlSettingInt FanSpeed1;
	AdlSettingInt FanTemp1;
	AdlSettingInt FanSpeed2;
	AdlSettingInt FanTemp2;
	AdlSettingInt FanSpeed3;
	AdlSettingInt FanTemp3;
	AdlSettingInt FanSpeed4;
	AdlSettingInt FanTemp4;

	//Custom
	AdlSettingInt FanControl;
	AdlSettingInt KeepActive;

	//Variables (No export)
	int FanZeroTemp = -1;
	bool FanSupport = false;
	bool TuningSupport = false;
	bool UsingProfile = false;

	//Functions (No export)
	bool Global()
	{
		return Application.has_value() && Application.value() == L"Global";
	}

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(TuningFanSettings, DeviceId, Application, CoreMin.Current, CoreMax.Current, MemoryTiming.Current, MemoryMax.Current, PowerLimit.Current, PowerVoltage.Current, PowerTDC.Current, FanZeroRpm.Current, FanSpeed0.Current, FanTemp0.Current, FanSpeed1.Current, FanTemp1.Current, FanSpeed2.Current, FanTemp2.Current, FanSpeed3.Current, FanTemp3.Current, FanSpeed4.Current, FanTemp4.Current, FanControl.Current, KeepActive.Current)
};