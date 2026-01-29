#pragma once
#include "pch.h"

struct GraphicsSettings
{
	std::optional<std::string> AppId;
	std::optional<int> WaitForVerticalRefresh;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(GraphicsSettings, AppId, WaitForVerticalRefresh)
};