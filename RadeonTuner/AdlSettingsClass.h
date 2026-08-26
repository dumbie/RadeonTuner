#pragma once
#include "pch.h"

enum class AdlSettingGet
{
	Current,
	Default
};

struct AdlSettingInt
{
	std::optional<int> Current;
	std::optional<int> Default;
	std::optional<int> Minimum;
	std::optional<int> Maximum;
	std::optional<int> Step;
	bool Support;

	std::optional<int> Get(AdlSettingGet settingType)
	{
		return settingType == AdlSettingGet::Current ? Current : Default;
	}
};

struct AdlSettingFloat
{
	std::optional<float> Current;
	std::optional<float> Default;
	std::optional<float> Minimum;
	std::optional<float> Maximum;
	std::optional<float> Step;
	bool Support;

	std::optional<float> Get(AdlSettingGet settingType)
	{
		return settingType == AdlSettingGet::Current ? Current : Default;
	}
};

struct AdlSettingString
{
	std::optional<std::wstring> Current;
	std::optional<std::wstring> Default;
	bool Support;

	std::optional<std::wstring> Get(AdlSettingGet settingType)
	{
		return settingType == AdlSettingGet::Current ? Current : Default;
	}
};