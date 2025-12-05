#pragma once
#include "pch.h"

struct TuningFanSettings
{
	std::optional<std::string> DeviceId;
	std::optional<bool> KeepActive;
	std::optional<int> CoreMin;
	std::optional<int> CoreMax;
	std::optional<int> MemoryTiming;
	std::optional<int> MemoryMax;
	std::optional<int> PowerLimit;
	std::optional<int> PowerVoltage;
	std::optional<int> PowerTDC;
	std::optional<bool> FanZeroRpm;
	std::optional<int> FanSpeed0;
	std::optional<int> FanTemp0;
	std::optional<int> FanSpeed1;
	std::optional<int> FanTemp1;
	std::optional<int> FanSpeed2;
	std::optional<int> FanTemp2;
	std::optional<int> FanSpeed3;
	std::optional<int> FanTemp3;
	std::optional<int> FanSpeed4;
	std::optional<int> FanTemp4;
};