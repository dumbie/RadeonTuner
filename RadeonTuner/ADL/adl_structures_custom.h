typedef struct ADLOD8SingleInitSettingWrap : ADLOD8SingleInitSetting
{
	bool IsSupported()
	{
		return minValue != maxValue;
	}
};

typedef struct ADL_RIS2_NOTIFICATION_REASON
{
	unsigned int GlobalSharpeningModeChanged; //Set when Global sharpening mode value is changed
	unsigned int GlobalSharpeningDegreeChanged; //Set when Global sharpening degree value is changed
	unsigned int GlobalSharpenDesktopChanged; //Set when Global sharpen desktop value is changed
};

typedef struct ADL_RIS2_SETTINGS
{
	int GlobalSharpeningMode; //Global mode value (0 = off / 1 = on / 2 = off + desktop / 3 = on + desktop)
	int GlobalSharpeningDegree; //Global sharpening value
	int GlobalSharpeningDegree_MinLimit; //Global sharpening slider min limit value
	int GlobalSharpeningDegree_MaxLimit; //Global sharpening slider max limit value
	int GlobalSharpeningDegree_Step; //Global sharpening step  value
};

enum ADLCvdcType
{
	CVDC_ENABLED,
	CVDC_PROTANOPIA,
	CVDC_DEUTERANOPIA,
	CVDC_TRITANOPIA
};

enum OD8SettingsRegistryFlags
{
	GpuTuning = 1 << 0,
	MemoryTuning = 1 << 1,
	FanTuningOff = 1 << 5,
	FanTuningOn = 1 << 6,
	PowerTuning = 1 << 8,
	Default = 1 << 12
};

enum OD8_OPTIMZED_POWER_MODES
{
	Quiet = 0,
	Balanced = 1,
	Custom = 3,
	Rage = 4
};