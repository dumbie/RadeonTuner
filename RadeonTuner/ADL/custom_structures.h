typedef struct ADLOD8SingleInitSettingWrap : ADLOD8SingleInitSetting
{
	bool IsSupported()
	{
		return minValue != maxValue;
	}
};

typedef struct ADL_RIS2_NOTIFICATION_REASON
{
	unsigned int GlobalEnableChanged; //Set when Global enable value is changed
	unsigned int GlobalSharpeningDegreeChanged; //Set when Global sharpening Degree value is changed
	unsigned int GlobalDesktopChanged; //Set when Desktop value is changed
};

typedef struct ADL_RIS2_SETTINGS
{
	int GlobalEnable; //Global enable value
	int GlobalSharpeningDegree; //Global sharpening value
	int GlobalSharpeningDegree_MinLimit; //Global sharpening slider min limit value
	int GlobalSharpeningDegree_MaxLimit; //Global sharpening slider max limit value
	int GlobalSharpeningDegree_Step; //Global sharpening step value
	int GlobalDesktop; //Global desktop value
};

typedef struct ADL_BOOST_SETTINGSX4
{
	int Hotkey; // Hotkey value
	int GlobalEnable; //Global enable value
	int GlobalMinRes; //Global Min Resolution value
	int GlobalMinRes_MinLimit; //Global Min Resolution slider min limit value
	int GlobalMinRes_MaxLimit; //Global Min Resolution slider max limit value
	int GlobalMinRes_Step; //Global Min Resolution step value
	int VsrSupported; //Allows for interop with Upscaling/RSR
	int Unknown1; //Unknown1 value
	int AdaptiveVrsEnabled; //Adaptive Vrs enabled value
};

typedef struct ADL_BOOST_NOTIFICATION_REASONX4
{
	int HotkeyChanged; //Set when Hotkey value is changed
	int GlobalEnableChanged; //Set when Global enable value is changed
	int GlobalMinResChanged; //Set when Global min resolution value is changed
	int Unknown1Changed; //Set when Unknown1 value is changed
	int AdaptiveVrsChanged; //Set when Adaptive Vrs enable value is changed
};

typedef struct ADL_DELAG_SETTINGSX4
{
	int Hotkey; //Hotkey value
	int GlobalEnable; //Global enable value
	int GlobalLimitFPS; //Global Limit FPS
	int GlobalLimitFPS_MinLimit; //Global Limit FPS slider min limit value
	int GlobalLimitFPS_MaxLimit; //Global Limit FPS slider max limit value
	int GlobalLimitFPS_Step; //Global Limit FPS step  value
	int Unknown1; //Unknown1 value
	int Unknown2; //Unknown2 value
	int IndicatorHotKey; //IndicatorHotKey value
};

typedef struct ADL_DELAG_NOTIFICATION_REASONX4
{
	int HotkeyChanged; //Set when Hotkey value is changed
	int GlobalEnableChanged; //Set when Global enable value is changed
	int GlobalLimitFPSChanged; //Set when Global enable value is changed
	int Unknown1Changed; //Set when Unknown1 value is changed
	int Unknown2Changed; //Set when Unknown2 value is changed
	int IndicatorHotKeyChanged; //Set when IndicatorHotKey value is changed
};

typedef struct AdlGammaRamp
{
	uint32_t rgb[1024];
};

enum class ADLCvdcType : int
{
	CVDC_ENABLED,
	CVDC_PROTANOPIA,
	CVDC_DEUTERANOPIA,
	CVDC_TRITANOPIA
};

enum class ADLColorEnhancementType : int
{
	SCE_Disabled = 1 << 0,
	SCE_VividGaming = 1 << 1,
	SCE_DynamicContrast = 1 << 3
};

enum class OD8SettingsRegistryFlags : int
{
	GpuTuning = 1 << 0,
	MemoryTuning = 1 << 1,
	FanTuningOff = 1 << 5,
	FanTuningOn = 1 << 6,
	PowerTuning = 1 << 8,
	Default = 1 << 12
};

enum class OD8_OPTIMZED_POWER_MODES : int
{
	Quiet = 0,
	FavorEfficiency = 0,
	Balanced = 1,
	Custom = 3,
	Default = 3,
	Rage = 4,
	FavorPerformance = 4
};

enum class AdlDeepBitDepth : int
{
	DISPLAY_8BIT_MODE_STATE = 0,
	DISPLAY_10BIT_MODE_STATE = 1
};

enum class AdlCustomResult : int
{
	CUSTOM_OK = 0,
	CUSTOM_ERROR,
	CUSTOM_ALREADY,
	CUSTOM_INVALID_ARGUMENT
};