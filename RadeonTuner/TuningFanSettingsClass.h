#pragma once
#include "pch.h"

struct TuningFanSettings
{
	//Settings
	std::optional<std::string> DeviceId;
	SettingInt CoreMin;
	SettingInt CoreMax;
	SettingInt MemoryTiming;
	SettingInt MemoryMax;
	SettingInt PowerLimit;
	SettingInt PowerVoltage;
	SettingInt PowerTDC;
	SettingInt FanZeroRpm;
	SettingInt FanSpeed0;
	SettingInt FanTemp0;
	SettingInt FanSpeed1;
	SettingInt FanTemp1;
	SettingInt FanSpeed2;
	SettingInt FanTemp2;
	SettingInt FanSpeed3;
	SettingInt FanTemp3;
	SettingInt FanSpeed4;
	SettingInt FanTemp4;

	//Custom
	SettingInt FanControl;
	SettingInt KeepActive;
	SettingInt PowerBoost;
	SettingInt PowerLimitPB;
	SettingInt PowerVoltagePB;
	SettingInt PowerTDCPB;

	//Variables (No export)
	int FanZeroTemp = -1;
	bool FanSupport = false;
	bool TuningSupport = false;
	bool PowerBoostUse = false;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(TuningFanSettings, DeviceId, CoreMin.Current, CoreMax.Current, MemoryTiming.Current, MemoryMax.Current, PowerLimit.Current, PowerVoltage.Current, PowerTDC.Current, FanZeroRpm.Current, FanSpeed0.Current, FanTemp0.Current, FanSpeed1.Current, FanTemp1.Current, FanSpeed2.Current, FanTemp2.Current, FanSpeed3.Current, FanTemp3.Current, FanSpeed4.Current, FanTemp4.Current, FanControl.Current, KeepActive.Current, PowerBoost.Current, PowerLimitPB.Current, PowerVoltagePB.Current, PowerTDCPB.Current)
};