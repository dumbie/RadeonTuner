#pragma once
#include "pch.h"

//Registry
const std::vector<std::wstring> REGISTRY_FSR_OTA_CONTROL_STRING =
{
	L"Use latest production"
};

const std::vector<std::wstring> REGISTRY_FRAMEGEN_SEARCH_MODE_STRING =
{
	L"Automatic", L"Standard", L"High"
};

const std::vector<std::wstring> REGISTRY_FRAMEGEN_PERFORMANCE_MODE_STRING =
{
	L"Automatic", L"Quality", L"Performance"
};

const std::vector<std::wstring> REGISTRY_FRAMEGEN_RESPONSE_MODE_STRING =
{
	L"Blended Frame", L"Repeat Frame"
};

const std::vector<std::wstring> REGISTRY_TEXTURE_FILTERING_QUALITY_STRING =
{
	L"High", L"Standard", L"Performance"
};

//ADL

//ADLX
const std::vector<std::wstring> ADLX_RESULT_STRING =
{
	L"Succeeded", L"Already enabled", L"Already initialized", L"Unspecified failure", L"Invalid arguments", L"Incompatible version", L"Unknown interface", L"ADLX is terminated", L"ADL initialization failed", L"Not found", L"Invalid object", L"Orphaned object", L"Feature is not supported", L"Pending operation in progress", L"GPU is inactive", L"GPU is in use", L"Operation timed out", L"Feature is inactive"
};

const std::vector<std::wstring> ADLX_HG_TYPE_STRING =
{
	L"Hybrid Graphics system", L"AMD integrated GPU", L"Non-AMD integrated GPU"
};

const std::vector<std::wstring> ADLX_ASIC_FAMILY_TYPE_STRING =
{
	L"Unknown", L"Radeon", L"FirePro", L"FireMV", L"FireStream", L"Fusion", L"Embedded"
};

const std::vector<std::wstring> ADLX_PCI_BUS_TYPE_STRING =
{
	L"Unknown", L"PCI", L"AGP", L"PCIE 1.0", L"PCIE 2.0", L"PCIE 3.0", L"PCIE 4.0", L"PCIE 5.0", L"PCIE 6.0", L"PCIE 7.0", L"PCIE 8.0", L"PCIE 9.0", L"PCIE 10.0"
};

const std::vector<std::wstring> ADLX_DP_LINK_RATE_STRING =
{
	L"Unknown", L"1.62 Gbps/Lane", L"2.16 Gbps/Lane", L"2.43 Gbps/Lane", L"2.70 Gbps/Lane", L"4.32 Gbps/Lane", L"5.40 Gbps/Lane", L"8.10 Gbps/Lane", L"10 Gbps/Lane", L"13.5 Gbps/Lane", L"20 Gbps/Lane"
};

const std::vector<std::wstring> ADLX_GPU_TYPE_STRING =
{
	L"Unknown", L"Integrated", L"Discrete"
};

const std::vector<std::wstring> ADLX_DISPLAY_CONNECTOR_TYPE_STRING =
{
	L"Unknown", L"VGA", L"DVI-D", L"DVI-I", L"NTSC", L"JPN", L"Non-I2C JPN", L"Non-I2C NTSC", L"Proprietary", L"HDMI Type A", L"HDMI Type B", L"S-Video", L"Composite", L"RCA", L"DisplayPort", L"EDP", L"Wireless Display", L"USB Type-C"
};

const std::vector<std::wstring> ADLX_DISPLAY_TYPE_STRING =
{
	L"Unknown", L"Monitor", L"Television", L"LCD display", L"DFP display", L"Component video", L"Projector"
};

const std::vector<std::wstring> ADLX_DISPLAY_SCAN_TYPE_STRING =
{
	L"Progressive", L"Interlaced"
};

const std::vector<std::wstring> ADLX_DISPLAY_TIMING_POLARITY_STRING =
{
	L"Positive", L"Negative"
};

const std::vector<std::wstring> ADLX_SCALE_MODE_STRING =
{
	L"Preserve aspect ratio", L"Full panel", L"Center"
};

const std::vector<std::wstring> ADLX_COLOR_DEPTH_STRING =
{
	L"Unknown", L"6 bits per color", L"8 bits per color", L"10 bits per color", L"12 bits per color", L"14 bits per color", L"16 bits per color"
};

const std::vector<std::wstring> ADLX_PIXEL_FORMAT_STRING =
{
	L"Unknown", L"RGB 4:4:4 PC Standard (Full RGB)", L"YCbCr 4:4:4", L"YCbCr 4:2:2", L"RGB 4:4:4 Studio (Limited RGB)", L"YCbCr 4:2:0"
};

const std::vector<std::wstring> ADLX_TIMING_STANDARD_STRING =
{
	L"CVT", L"CVT-RB", L"GTF", L"DMT", L"Manual"
};

const std::vector<std::wstring> ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE_STRING =
{
	L"Always Off", L"Off, unless application specifies", L"On, unless application specifies", L"Always On"
};

const std::vector<std::wstring> ADLX_ANTI_ALIASING_MODE_STRING =
{
	L"Use application settings", L"Enhance application settings", L"Override application settings"
};

const std::vector<std::wstring> ADLX_ANTI_ALIASING_LEVEL_STRING =
{
	//Index 0, 2, 3, 4, 5, 8, 9
	L"Invalid", L"2X", L"2XEQ", L"4X", L"4XEQ", L"8X", L"8XEQ"
};

const std::vector<std::wstring> ADLX_ANTI_ALIASING_METHOD_STRING =
{
	L"Multisampling", L"Adaptive multisampling", L"Supersampling"
};

const std::vector<std::wstring> ADLX_ANISOTROPIC_FILTERING_LEVEL_STRING =
{
	//Index 0, 2, 4, 8, 16
	L"Invalid", L"2X", L"4X", L"8X", L"16X"
};

const std::vector<std::wstring> ADLX_TESSELLATION_MODE_STRING =
{
	L"AMD optimized", L"Use application settings", L"Override application settings"
};

const std::vector<std::wstring> ADLX_TESSELLATION_LEVEL_STRING =
{
	//Index 1, 2, 4, 6, 8, 16, 32, 64
	L"Off", L"2X", L"4X", L"6X", L"8X", L"16X", L"32X", L"64X"
};

const std::vector<std::wstring> ADLX_MEMORYTIMING_DESCRIPTION_STRING =
{
	L"Default", L"Fast Timing 1", L"Fast Timing 2", L"Automatic Timing", L"Memory Timing 1", L"Memory Timing 2"
};

const std::vector<std::wstring> ADLX_SSM_BIAS_MODE_STRING =
{
	L"Automatic", L"Manual"
};

//ADLX Custom
const std::vector<std::wstring> ADLX_SCE_PROFILE_STRING =
{
	L"Disabled", L"Vivid Gaming", L"Dynamic Contrast"
};

const std::vector<std::wstring> ADLX_VARIBRIGHT_LEVEL_STRING =
{
	L"Maximize Brightness", L"Optimize Brightness", L"Balanced", L"Optimize Battery", L"Maximize Battery"
};