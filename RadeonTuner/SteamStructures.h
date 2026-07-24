#pragma once
#include "pch.h"

namespace LauncherSteam::Structures
{
	struct VdfData
	{
		std::unordered_map<std::string, std::string> values;
		std::unordered_map<std::string, VdfData> children;
	};

	struct SteamAppInfoBasic
	{
		uint32_t appid;
		std::optional<std::string> name;
		std::optional<std::string> executable;
	};

	struct SteamLibraryFoldersBasic
	{
		std::string path;
		std::optional<std::vector<std::string>> apps;
	};
}