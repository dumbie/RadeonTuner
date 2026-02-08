#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "AdlVariables.h"

namespace winrt::RadeonTuner::implementation
{
	std::wstring MainPage::AdlAppProfileGenerateName()
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
			return L"RADT" + stringGuid;
		}
		catch (...) {}
		return L"";
	}

	bool MainPage::AdlAppPropertyExists(std::wstring propertyName, std::wstring driverArea)
	{
		try
		{
			int targetType;
			adl_Res0 = _ADL2_ApplicationProfiles_PropertyType_Get(adl_Context, driverArea.c_str(), propertyName.c_str(), &targetType);
			return adl_Res0 == ADL_OK;
		}
		catch (...) {}
		return false;
	}

	AdlAppPropertyType MainPage::AdlAppPropertyTypeGet(std::wstring propertyName, std::wstring driverArea)
	{
		try
		{
			int targetType;
			adl_Res0 = _ADL2_ApplicationProfiles_PropertyType_Get(adl_Context, driverArea.c_str(), propertyName.c_str(), &targetType);
			if (adl_Res0 == ADL_OK)
			{
				if (targetType == 1)
				{
					return AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_BINARY;
				}
				else if (targetType == 2)
				{
					return AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_QWORD;
				}
				else if (targetType == 3)
				{
					return AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_DWORD;
				}
				else if (targetType == 4)
				{
					return AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_BOOLEAN;
				}
				else if (targetType == 5)
				{
					return AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_ENUMERATED;
				}
				else if (targetType == 6)
				{
					return AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_STRING;
				}
			}
		}
		catch (...) {}
		return AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN;
	}

	std::vector<ADLPropertyRecordCreate> MainPage::AdlAppPropertyRecordCreateGet(AdlApplication adlApp)
	{
		std::vector<ADLPropertyRecordCreate> recordProperties;
		try
		{
			for (AdlAppProperty property : adlApp.Properties)
			{
				try
				{
					ADLPropertyRecordCreate propertyRecordCreate{};
					propertyRecordCreate.eType = (ADLProfilePropertyType)property.Type;
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