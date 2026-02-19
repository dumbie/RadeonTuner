#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	std::wstring MainPage::AdlAppProfileGenerateName(std::wstring profileHeader)
	{
		try
		{
			//Create random guid
			GUID randomGuid;
			HRESULT hResult = CoCreateGuid(&randomGuid);

			//Convert guid to string
			std::wstring stringGuid;
			stringGuid.resize(68);
			hResult = StringFromGUID2(randomGuid, stringGuid.data(), stringGuid.size());

			//Return result
			return profileHeader + stringGuid;
		}
		catch (...) {}
		return L"";
	}

	bool MainPage::AdlAppExists(std::wstring fileName, std::wstring filePath, std::wstring driverArea)
	{
		try
		{
			//Get applications
			int adlApplicationsCount = 0;
			ADLApplicationRecord* adlApplications;
			adl_Res0 = _ADL2_ApplicationProfiles_Applications_Get(adl_Context, driverArea.c_str(), &adlApplicationsCount, &adlApplications);
			if (adl_Res0 == ADL_OK)
			{
				for (int i = 0; i < adlApplicationsCount; i++)
				{
					try
					{
						if (adlApplications[i].strFileName == fileName && adlApplications[i].strPathName == filePath && adlApplications[i].strArea == driverArea) { return true; }
					}
					catch (...) {}
				}
			}
		}
		catch (...) {}
		return false;
	}

	bool MainPage::AdlAppPropertyValid(std::wstring propertyName, std::wstring driverArea)
	{
		try
		{
			DATATYPES targetType;
			adl_Res0 = _ADL2_ApplicationProfiles_PropertyType_Get(adl_Context, driverArea.c_str(), propertyName.c_str(), &targetType);
			return adl_Res0 == ADL_OK;
		}
		catch (...) {}
		return false;
	}

	DATATYPES MainPage::AdlAppPropertyDataTypeGet(std::wstring propertyName, std::wstring driverArea)
	{
		try
		{
			DATATYPES targetType;
			adl_Res0 = _ADL2_ApplicationProfiles_PropertyType_Get(adl_Context, driverArea.c_str(), propertyName.c_str(), &targetType);
			if (adl_Res0 == ADL_OK)
			{
				return targetType;
			}
		}
		catch (...) {}
		return DT_Unknown;
	}

	ADLProfilePropertyType MainPage::AdlAppConvertDataTypeToPropertyType(DATATYPES dataType)
	{
		try
		{
			if (dataType == DT_Unknown || dataType == DT_Binary)
			{
				return ADL_PROFILEPROPERTY_TYPE_BINARY;
			}
			else if (dataType == DT_Qword)
			{
				return ADL_PROFILEPROPERTY_TYPE_QWORD;
			}
			else if (dataType == DT_Dword)
			{
				return ADL_PROFILEPROPERTY_TYPE_DWORD;
			}
			else if (dataType == DT_Boolean)
			{
				return ADL_PROFILEPROPERTY_TYPE_BOOLEAN;
			}
			else if (dataType == DT_Enumerated)
			{
				return ADL_PROFILEPROPERTY_TYPE_ENUMERATED;
			}
			else if (dataType == DT_Stringed)
			{
				return ADL_PROFILEPROPERTY_TYPE_STRING;
			}
		}
		catch (...){}
		return ADL_PROFILEPROPERTY_TYPE_BINARY;
	}

	std::vector<ADLPropertyRecordCreate> MainPage::AdlAppPropertyRecordCreateGet(std::vector<AdlAppProperty> adlAppProperties)
	{
		std::vector<ADLPropertyRecordCreate> recordProperties;
		try
		{
			for (AdlAppProperty property : adlAppProperties)
			{
				try
				{
					ADLPropertyRecordCreate propertyRecordCreate{};
					propertyRecordCreate.eType = AdlAppConvertDataTypeToPropertyType(property.Type);
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
}