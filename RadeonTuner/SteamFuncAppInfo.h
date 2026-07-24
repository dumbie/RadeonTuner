#pragma once
#include "pch.h"
#include "SteamStructures.h"
#include "SteamFunctions.h"
namespace LauncherSteam
{
	using namespace LauncherSteam::Structures;
	using namespace LauncherSteam::Functions;
}

namespace LauncherSteam::AppInfo
{
	inline uint32_t readU32FromStream(std::ifstream& fileStream)
	{
		uint32_t returnValue;
		fileStream.read((char*)&returnValue, 4);
		return returnValue;
	}

	inline uint64_t readU64FromStream(std::ifstream& fileStream)
	{
		uint64_t returnValue;
		fileStream.read((char*)&returnValue, 8);
		return returnValue;
	}

	inline std::vector<std::string> readStringTableFromStream(std::ifstream& fileStream)
	{
		std::vector<std::string> stringTable{};
		try
		{
			//Get string count
			uint32_t stringCount = readU32FromStream(fileStream);
			if (stringCount == 0)
			{
				return stringTable;
			}

			//Reserve string table and read strings
			stringTable.reserve(stringCount);
			for (uint32_t i = 0; i < stringCount; ++i)
			{
				char tempChar;
				std::string stringValue;
				while (fileStream.get(tempChar) && tempChar != '\0')
				{
					stringValue.push_back(tempChar);
				}
				stringTable.push_back(stringValue);
			}
		}
		catch (...) {}
		//Return result
		return stringTable;
	}

	inline uint32_t readU32FromBuffer(const uint8_t* vdfDataBuffer)
	{
		uint32_t returnValue;
		std::memcpy(&returnValue, vdfDataBuffer, 4);
		return returnValue;
	}

	inline uint64_t readU64FromBuffer(const uint8_t* vdfDataBuffer)
	{
		uint64_t returnValue;
		std::memcpy(&returnValue, vdfDataBuffer, 8);
		return returnValue;
	}

	inline std::string readStringFromBuffer(const uint8_t** vdfDataBuffer)
	{
		std::string returnValue;
		while (*(*vdfDataBuffer) != 0)
		{
			returnValue.push_back((char)*(*vdfDataBuffer)++);
		}
		return returnValue;
	}

	inline VdfData parseVdfData(const uint8_t*& vdfDataStart, const uint8_t* vdfDataEnd, const std::vector<std::string>& stringTable)
	{
		VdfData vdfData;
		try
		{
			while (vdfDataStart < vdfDataEnd)
			{
				//Get key type
				uint8_t keyType = *vdfDataStart++;

				//Check key type
				if (keyType == 0x08)
				{
					break;
				}

				//Get key index and string
				uint32_t keyIndex = readU32FromBuffer(vdfDataStart);
				std::string keyString = stringTable[keyIndex];
				vdfDataStart += 4;

				//Check key type
				switch (keyType)
				{
				case 0x00:
				{
					//Object
					vdfData.children[keyString] = parseVdfData(vdfDataStart, vdfDataEnd, stringTable);
					break;
				}
				case 0x01:
				{
					//String
					vdfData.values[keyString] = readStringFromBuffer(&vdfDataStart);
					vdfDataStart += 1;
					break;
				}
				case 0x02:
				{
					//Int32
					vdfData.values[keyString] = number_to_string(readU32FromBuffer(vdfDataStart));
					vdfDataStart += 4;
					break;
				}
				case 0x07:
				{
					//Int64
					vdfData.values[keyString] = number_to_string(readU64FromBuffer(vdfDataStart));
					vdfDataStart += 8;
					break;
				}
				}
			}
		}
		catch (...) {}
		return vdfData;
	}

	inline std::vector<SteamAppInfoBasic> GetApps(std::string vdfPath)
	{
		std::vector<SteamAppInfoBasic> appInfos{};
		try
		{
			//Check vdf path
			if (vdfPath.empty())
			{
				//Get Steam install directory
				std::wstring steamInstallPath = SteamInstallPath();
				std::wstring appInfoPath = steamInstallPath + L"\\appcache\\appinfo.vdf";
				vdfPath = wstring_to_string(appInfoPath);
				AVDebugWriteLine("Steam appinfo.vdf path: " << appInfoPath.c_str());
			}

			//Open vdf file
			std::ifstream fileStream(vdfPath, std::ios::binary);
			if (!fileStream.is_open())
			{
				AVDebugWriteLine("Failed opening Steam appinfo.vdf: " << vdfPath.c_str());
				return appInfos;
			}

			//Get header information
			uint32_t headMagic = readU32FromStream(fileStream);
			uint32_t headVersion = headMagic & 0xFF;
			uint32_t headUniverse = readU32FromStream(fileStream);
			AVDebugWriteLine("Steam appinfo.vdf Magic: " << headMagic << " Version: " << headVersion << " Universe: " << headUniverse);
			if (headVersion != 41)
			{
				AVDebugWriteLine("Unsupported Steam appinfo version: " << headVersion);
				return appInfos;
			}

			//Set stream position
			int64_t posStringTable = readU64FromStream(fileStream);
			std::streampos posHeaderEnd = fileStream.tellg();

			//Read string table
			fileStream.clear();
			fileStream.seekg(posStringTable);
			std::vector<std::string> stringTable = readStringTableFromStream(fileStream);

			//Read app information
			fileStream.clear();
			fileStream.seekg(posHeaderEnd);
			while (true)
			{
				//Get application identifier
				uint32_t appIdentifier = readU32FromStream(fileStream);
				if (appIdentifier <= 0)
				{
					//AVDebugWriteLine("Finished reading Steam appinfo file.");
					break;
				}

				//Get application information
				uint32_t appSize = readU32FromStream(fileStream);

				//Set stream position
				std::streampos posInfoStateStart = fileStream.tellg();
				std::streampos posAppEnd = posInfoStateStart + (std::streampos)appSize;

				uint32_t appInfoState = readU32FromStream(fileStream);
				uint32_t appLastUpdated = readU32FromStream(fileStream);
				uint64_t appToken = readU64FromStream(fileStream);

				uint8_t appSha1Hash[20];
				fileStream.read((char*)appSha1Hash, 20);

				uint32_t appChangeNumber = readU32FromStream(fileStream);

				uint8_t appSha1Binary[20];
				fileStream.read((char*)appSha1Binary, 20);

				//Set stream position
				std::streampos posVdfDataStart = fileStream.tellg();

				//Get application VDF data
				size_t appDataSize = posAppEnd - posVdfDataStart;
				std::vector<uint8_t> appData(appDataSize);
				fileStream.read((char*)appData.data(), appDataSize);

				//Parse VDF data
				const uint8_t* vdfDataStart = appData.data();
				const uint8_t* vdfDataEnd = appData.data() + appData.size();
				VdfData vdfData = parseVdfData(vdfDataStart, vdfDataEnd, stringTable);

				//Get application information
				std::string name;
				std::string executable;
				if (vdfData.children.count("appinfo"))
				{
					//Get appinfo child
					auto& childAppInfo = vdfData.children["appinfo"];

					//Get common child
					if (childAppInfo.children.count("common"))
					{
						auto& childCommon = childAppInfo.children["common"];
						if (childCommon.values.count("name"))
						{
							name = childCommon.values["name"];
						}
					}

					//Get config and launch child
					if (childAppInfo.children.count("config"))
					{
						auto& childConfig = childAppInfo.children["config"];
						if (childConfig.children.count("launch"))
						{
							auto& childLaunch = childConfig.children["launch"];
							for (auto& subLaunch : childLaunch.children)
							{
								if (subLaunch.second.values.count("executable"))
								{
									executable = subLaunch.second.values["executable"];
									break;
								}
							}
						}
					}
				}

				//Check if name or executable is empty
				if (name.empty() || executable.empty())
				{
					continue;
				}

				//AVDebugWriteLine("AppID: " << appIdentifier << " / Name: " << name.c_str() << " / Executable: " << executable.c_str());

				//Append application
				SteamAppInfoBasic appInfo{};
				appInfo.appid = appIdentifier;
				appInfo.name = name;
				appInfo.executable = executable;
				appInfos.push_back(appInfo);
			}
		}
		catch (...) {}
		//Return result
		AVDebugWriteLine("Steam appinfo loaded: " << appInfos.size());
		return appInfos;
	}
}