#pragma once
#include "pch.h"

enum class AdlSettingGet
{
	Current,
	Default
};

struct AdlSettingVersion
{
	int Version;
};

struct AdlSettingInt
{
	std::optional<int> Current;
	std::optional<int> Default;
	std::optional<int> Minimum;
	std::optional<int> Maximum;
	std::optional<int> Step;
	bool Support;

	std::optional<int> Get(AdlSettingGet settingType, bool fallBack = false)
	{
		if (settingType == AdlSettingGet::Current)
		{
			if (Current.has_value())
			{
				return Current;
			}
			else if (fallBack && Default.has_value())
			{
				return Default;
			}
		}
		else if (settingType == AdlSettingGet::Default)
		{
			if (Default.has_value())
			{
				return Default;
			}
			else if (fallBack && Current.has_value())
			{
				return Current;
			}
		}
		return std::nullopt;
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

	std::optional<float> Get(AdlSettingGet settingType, bool fallBack = false)
	{
		if (settingType == AdlSettingGet::Current)
		{
			if (Current.has_value())
			{
				return Current;
			}
			else if (fallBack && Default.has_value())
			{
				return Default;
			}
		}
		else if (settingType == AdlSettingGet::Default)
		{
			if (Default.has_value())
			{
				return Default;
			}
			else if (fallBack && Current.has_value())
			{
				return Current;
			}
		}
		return std::nullopt;
	}
};

struct AdlSettingString
{
	std::optional<std::wstring> Current;
	std::optional<std::wstring> Default;
	bool Support;

	std::optional<std::wstring> Get(AdlSettingGet settingType, bool fallBack = false)
	{
		if (settingType == AdlSettingGet::Current)
		{
			if (Current.has_value())
			{
				return Current;
			}
			else if (fallBack && Default.has_value())
			{
				return Default;
			}
		}
		else if (settingType == AdlSettingGet::Default)
		{
			if (Default.has_value())
			{
				return Default;
			}
			else if (fallBack && Current.has_value())
			{
				return Current;
			}
		}
		return std::nullopt;
	}
};