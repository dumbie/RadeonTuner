#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlAppSetUmdGpuId()
	{
		try
		{
			//DriverBug#1
			//Bug or limitation in newer AMD drivers does not allow separate app settings for each GPU so settings must unfortunately be set the same for all GPU's.
			//In older drivers you needed to set the used GpuID at 'UMD\AppGpuId' but for some reason in newer drivers this value seems to be ignored breaking support for separate settings.
			//Driver stores settings like this GpuId1::SettingOn;;GpuId2::SettingOff;; but only the first value is used ignoring 'UMD\AppGpuId'.
			//Note: this workaround breaks profile compatibility with Radeon Software but does make settings work on old and new drivers.

			//Set gpu unique identifier
			gpuUniqueIdentifierHex = L"0x0001";

			for (UINT i = 0; i < ppGpuList->Size(); i++)
			{
				//Get gpu pointer
				IADLXGPU2Ptr ppGpuPtr;
				adlx_Res0 = ppGpuList->At(i, (IADLXGPU**)&ppGpuPtr);

				//Get ADL adapter index
				int adapterIndex;
				adlx_Res0 = ppAdlMapping->AdlAdapterIndexFromADLXGPU(ppGpuPtr, &adapterIndex);

				//Get gpu unique identifier
				//int identifierInt;
				//adlx_Res0 = ppGpuPtr->UniqueId(&identifierInt);
				//std::string identifierHex = number_to_hexstring(identifierInt, 4);

				//Set gpu application identifier
				AdlRegistrySettingSet(adapterIndex, "UMD", "AppGpuId", "0x0001");
			}
		}
		catch (...) {}
	}

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
			auto adlApplications = AVFin<ADLApplicationRecord*>(AVFinMethod::Custom);
			adl_Res0 = _ADL2_ApplicationProfiles_Applications_Get(adl_Context, driverArea.c_str(), &adlApplicationsCount, &adlApplications.Get());

			//Set memory releaser
			adlApplications.SetReleaser([&](auto releasePointer)
				{
					for (int i = 0; i < adlApplicationsCount; i++)
					{
						delete[](releasePointer[i].strFileName);
						delete[](releasePointer[i].strPathName);
						delete[](releasePointer[i].strArea);
						delete[](releasePointer[i].strTitle);
						delete[](releasePointer[i].strVersion);
						delete[](releasePointer[i].strNotes);
						delete[](releasePointer[i].strProfileName);
					}
					delete[](releasePointer);
				});

			//Check result
			if (adl_Res0 == ADL_OK)
			{
				for (int i = 0; i < adlApplicationsCount; i++)
				{
					try
					{
						bool fileNameMatch = wstring_to_lower(adlApplications.Get()[i].strFileName) == wstring_to_lower(fileName);
						bool filePathMatch = wstring_to_lower(adlApplications.Get()[i].strPathName) == wstring_to_lower(filePath);
						bool driverAreaMatch = adlApplications.Get()[i].strArea == driverArea;
						if (fileNameMatch && filePathMatch && driverAreaMatch) { return true; }
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
		catch (...) {}
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