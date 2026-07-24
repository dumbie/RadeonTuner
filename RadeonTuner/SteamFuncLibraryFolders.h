#pragma once
#include "pch.h"
#include "SteamStructures.h"
#include "SteamFunctions.h"
namespace LauncherSteam
{
	using namespace LauncherSteam::Structures;
	using namespace LauncherSteam::Functions;
}

namespace LauncherSteam::LibraryFolders
{
	inline std::vector<SteamLibraryFoldersBasic> GetLibraryFolders(std::string vdfPath)
	{
		std::vector<SteamLibraryFoldersBasic> result{};
		try
		{
			//Check vdf path
			if (vdfPath.empty())
			{
				//Get Steam install directory
				std::wstring steamInstallPath = SteamInstallPath();
				std::wstring appInfoPath = steamInstallPath + L"\\steamapps\\libraryfolders.vdf";
				vdfPath = wstring_to_string(appInfoPath);
				AVDebugWriteLine("Steam libraryfolders.vdf path: " << appInfoPath.c_str());
			}

			//Open vdf file
			std::ifstream fileStream(vdfPath, std::ios::binary);
			if (!fileStream.is_open())
			{
				AVDebugWriteLine("Failed opening libraryfolders.vdf: " << vdfPath.c_str());
				return result;
			}

			//Read all keys and values
			char tempChar;
			VdfData dataRoot;
			std::vector<VdfData*> dataArray{ &dataRoot };
			while (fileStream.get(tempChar))
			{
				//Skip whitespace
				if (std::isspace(tempChar))
				{
					continue;
				}

				//Check key
				if (tempChar == '"')
				{
					//Read key
					std::string stringKey;
					while (fileStream.get(tempChar) && tempChar != '"')
					{
						stringKey.push_back(tempChar);
					}

					//Skip whitespace
					while (fileStream.get(tempChar) && std::isspace(tempChar))
					{
						continue;
					}

					//Check opening
					if (tempChar == '{')
					{
						VdfData* current = dataArray.back();
						dataArray.push_back(&current->children[stringKey]);
						continue;
					}

					//Read value
					if (tempChar == '"')
					{
						std::string stringValue;
						while (fileStream.get(tempChar) && tempChar != '"')
						{
							stringValue.push_back(tempChar);
						}
						VdfData* current = dataArray.back();
						current->values[stringKey] = stringValue;
						continue;
					}
				}

				//Check closing
				if (tempChar == '}')
				{
					if (dataArray.size() > 1)
					{
						dataArray.pop_back();
					}
					continue;
				}
			}

			//Get library folders information
			if (dataRoot.children.count("libraryfolders"))
			{
				auto& childLibrary = dataRoot.children["libraryfolders"];
				for (auto& folderData : childLibrary.children)
				{
					SteamLibraryFoldersBasic folderBasic;

					//Extract path
					if (folderData.second.values.count("path"))
					{
						folderBasic.path = folderData.second.values["path"];
					}

					//Extract applications
					if (folderData.second.children.count("apps"))
					{
						folderBasic.apps = std::vector<std::string>{};
						for (auto& appData : folderData.second.children["apps"].values)
						{
							folderBasic.apps.value().push_back(appData.first);
						}
					}

					//Add folder to result
					result.push_back(folderBasic);
				}
			}
		}
		catch (...) {}
		//Return result
		AVDebugWriteLine("Steam library folders loaded: " << result.size());
		return result;
	}
}