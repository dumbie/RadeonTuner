#pragma once
#include "pch.h"

struct AdlAppPropertyValue
{
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

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(AdlAppPropertyValue, GpuId, Value)
};

struct AdlAppProperty
{
	DATATYPES Type;
	std::wstring Name;
	std::vector<AdlAppPropertyValue> Values;

	std::wstring GetValuesString()
	{
		std::wstring valueString;
		for (AdlAppPropertyValue adlAppPropertyValue : Values)
		{
			valueString += adlAppPropertyValue.GetValueString();
		}
		return valueString;
	}

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(AdlAppProperty, Type, Name, Values)
};

struct AdlApplication
{
	std::wstring FileName;
	std::wstring FilePath;
	std::wstring ProfileName;
	std::wstring DriverArea;
	std::vector<AdlAppProperty> Properties{};

	bool Initialized()
	{
		return !FileName.empty();
	}

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(AdlApplication, FileName, FilePath, ProfileName, DriverArea, Properties)
};