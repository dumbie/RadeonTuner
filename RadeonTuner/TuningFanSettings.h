#pragma once
#include "pch.h"

struct TuningFanSettings
{
	std::string DeviceId;
	int CoreMin;
	int CoreMax;
	int MemoryTiming;
	int MemoryMax;
	int PowerLimit;
	int PowerVoltage;
	int PowerTDC;
	bool FanZeroRpm;
	int FanSpeed0;
	int FanTemp0;
	int FanSpeed1;
	int FanTemp1;
	int FanSpeed2;
	int FanTemp2;
	int FanSpeed3;
	int FanTemp3;
	int FanSpeed4;
	int FanTemp4;
};