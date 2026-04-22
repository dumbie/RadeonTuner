#pragma once
#include "pch.h"

struct TuningFanSettings
{
	//Settings
	std::optional<std::string> DeviceId;
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

	//Custom
	std::optional<bool> FanControl;
	std::optional<bool> KeepActive;
	std::optional<bool> PowerBoost;
	std::optional<int> PowerLimitPB;
	std::optional<int> PowerVoltagePB;
	std::optional<int> PowerTDCPB;

	//Status
	std::optional<bool> PowerBoostUse;

	//Support
	std::optional<bool> SupportFans;
	std::optional<bool> SupportTuning;

	//Interface
	std::optional<int> CoreMinMin;
	std::optional<int> CoreMinMax;
	std::optional<int> CoreMinStep;
	std::optional<bool> CoreMinSupport;
	std::optional<int> CoreMaxMin;
	std::optional<int> CoreMaxMax;
	std::optional<int> CoreMaxStep;
	std::optional<bool> CoreMaxSupport;
	std::optional<bool> MemoryTimingSupport;
	std::optional<int> MemoryMaxMin;
	std::optional<int> MemoryMaxMax;
	std::optional<int> MemoryMaxStep;
	std::optional<bool> MemoryMaxSupport;
	std::optional<int> PowerLimitMin;
	std::optional<int> PowerLimitMax;
	std::optional<int> PowerLimitStep;
	std::optional<bool> PowerLimitSupport;
	std::optional<int> PowerVoltageMin;
	std::optional<int> PowerVoltageMax;
	std::optional<int> PowerVoltageStep;
	std::optional<bool> PowerVoltageSupport;
	std::optional<int> PowerTDCMin;
	std::optional<int> PowerTDCMax;
	std::optional<int> PowerTDCStep;
	std::optional<bool> PowerTDCSupport;
	std::optional<bool> FanZeroRpmSupport;
	std::optional<int> FanSpeedMin0;
	std::optional<int> FanSpeedMax0;
	std::optional<int> FanSpeedStep0;
	std::optional<bool> FanSpeedSupport0;
	std::optional<int> FanTempMin0;
	std::optional<int> FanTempMax0;
	std::optional<int> FanTempStep0;
	std::optional<bool> FanTempSupport0;
	std::optional<int> FanSpeedMin1;
	std::optional<int> FanSpeedMax1;
	std::optional<int> FanSpeedStep1;
	std::optional<bool> FanSpeedSupport1;
	std::optional<int> FanTempMin1;
	std::optional<int> FanTempMax1;
	std::optional<int> FanTempStep1;
	std::optional<bool> FanTempSupport1;
	std::optional<int> FanSpeedMin2;
	std::optional<int> FanSpeedMax2;
	std::optional<int> FanSpeedStep2;
	std::optional<bool> FanSpeedSupport2;
	std::optional<int> FanTempMin2;
	std::optional<int> FanTempMax2;
	std::optional<int> FanTempStep2;
	std::optional<bool> FanTempSupport2;
	std::optional<int> FanSpeedMin3;
	std::optional<int> FanSpeedMax3;
	std::optional<int> FanSpeedStep3;
	std::optional<bool> FanSpeedSupport3;
	std::optional<int> FanTempMin3;
	std::optional<int> FanTempMax3;
	std::optional<int> FanTempStep3;
	std::optional<bool> FanTempSupport3;
	std::optional<int> FanSpeedMin4;
	std::optional<int> FanSpeedMax4;
	std::optional<int> FanSpeedStep4;
	std::optional<bool> FanSpeedSupport4;
	std::optional<int> FanTempMin4;
	std::optional<int> FanTempMax4;
	std::optional<int> FanTempStep4;
	std::optional<bool> FanTempSupport4;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(TuningFanSettings, DeviceId, CoreMin, CoreMax, MemoryTiming, MemoryMax, PowerLimit, PowerVoltage, PowerTDC, FanZeroRpm, FanSpeed0, FanTemp0, FanSpeed1, FanTemp1, FanSpeed2, FanTemp2, FanSpeed3, FanTemp3, FanSpeed4, FanTemp4, FanControl, KeepActive, PowerBoost, PowerLimitPB, PowerVoltagePB, PowerTDCPB)
};