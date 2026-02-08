#pragma once
#include "pch.h"

enum AdlAppPropertyType
{
	ADL_APP_PROPERTY_TYPE_UNKNOWN = -1,
	ADL_APP_PROPERTY_TYPE_BINARY,
	ADL_APP_PROPERTY_TYPE_BOOLEAN,
	ADL_APP_PROPERTY_TYPE_DWORD,
	ADL_APP_PROPERTY_TYPE_QWORD,
	ADL_APP_PROPERTY_TYPE_ENUMERATED,
	ADL_APP_PROPERTY_TYPE_STRING
};

struct AdlAppPropertyValue
{
	//Unique identifier gpu header
	//Example: VsyncControl 0x1000::3;;0x2000::0;;
	//GpuId 0x0000 seems to be working as global gpu
	std::wstring Name;
	std::wstring GpuId;
	std::wstring Value;

	std::wstring GetValueString()
	{
		if (!GpuId.empty())
		{
			return GpuId + L"::" + Value + L";;";
		}
		else
		{
			return Value;
		}
	}
};

struct AdlAppProperty
{
	AdlAppPropertyType Type;
	std::wstring Name;
	std::wstring DriverArea;
	std::vector<AdlAppPropertyValue> Values;

	bool UseGpuId()
	{
		return DriverArea == L"3D_User" && Type == AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_STRING;
	}

	std::wstring GetValuesString()
	{
		std::wstring valueString;
		for (AdlAppPropertyValue adlAppPropertyValue : Values)
		{
			valueString += adlAppPropertyValue.GetValueString();
		}
		return valueString;
	}
};

struct AdlApplication
{
	std::wstring AppTitle;
	std::wstring FileName;
	std::wstring FilePath;
	std::wstring ProfileName;
	std::wstring DriverArea;
	std::wstring Version;
	std::wstring Notes;
	ADL_AP_DATABASE RecordSource;
	std::vector<AdlAppProperty> Properties{};

	bool Initialized()
	{
		return !FileName.empty();
	}
};