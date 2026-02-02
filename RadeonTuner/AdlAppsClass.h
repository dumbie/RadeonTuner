#pragma once
#include "pch.h"

struct AdlApps
{
	std::wstring AppTitle;
	std::wstring FileName;
	std::wstring FilePath;
	std::wstring ProfileName;
	std::wstring DriverArea;
	ADL_AP_DATABASE RecordSource;
	std::vector<ADLPropertyRecordCreate> PropertyRecords{};
};