#pragma once
#include "pch.h"

struct AdlAppPropertyValue
{
	//Unique identifier gpu header
	//Example: VsyncControl 0x1000::3;;0x2000::0;;
	std::wstring GpuId;
	std::wstring Value;

	std::wstring GetString()
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
	ADLProfilePropertyType Type;
	std::wstring Name;
	std::wstring DriverArea;
	std::vector<AdlAppPropertyValue> Values;

	bool UseGpuId()
	{
		return DriverArea == L"3D_User" && Type == ADL_PROFILEPROPERTY_TYPE_STRING;
	}

	std::wstring GetValuesString()
	{
		std::wstring valueString;
		for (AdlAppPropertyValue adlAppPropertyValue : Values)
		{
			valueString += adlAppPropertyValue.GetString();
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

	std::vector<ADLPropertyRecordCreate> GetRecordCreate()
	{
		std::vector<ADLPropertyRecordCreate> recordProperties;
		try
		{
			for (AdlAppProperty property : Properties)
			{
				try
				{
					ADLPropertyRecordCreate propertyRecordCreate{};
					propertyRecordCreate.eType = property.Type;
					propertyRecordCreate.strPropertyName = _wcsdup(property.Name.c_str());
					propertyRecordCreate.strPropertyValue = _wcsdup(property.GetValuesString().c_str());
					recordProperties.push_back(propertyRecordCreate);
				}
				catch (...) {}
			}
		}
		catch (...) {}
		return recordProperties;
	}
};