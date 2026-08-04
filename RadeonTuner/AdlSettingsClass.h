#pragma once
#include "pch.h"

struct SettingInt
{
	std::optional<int> Current;
	std::optional<int> Default;
	std::optional<bool> Support;
	std::optional<int> Minimum;
	std::optional<int> Maximum;
	std::optional<int> Step;
};

struct SettingFloat
{
	std::optional<float> Current;
	std::optional<float> Default;
	std::optional<bool> Support;
	std::optional<float> Minimum;
	std::optional<float> Maximum;
	std::optional<float> Step;
};

struct SettingString
{
	std::optional<std::wstring> Current;
	std::optional<std::wstring> Default;
	std::optional<bool> Support;
};