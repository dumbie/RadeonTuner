#pragma once
#include "MainPage.g.h"

namespace winrt::RadeonTuner::implementation
{
	struct MainPage : MainPageT<MainPage>
	{
		MainPage() {}

		void PointerMoved_AdjustCursor(IInspectable const& sender, PointerRoutedEventArgs const& e);
		winrt::IAsyncAction page_Loaded(IInspectable const& sender, RoutedEventArgs const& e);
		void listview_Main_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void button_Website_Project_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Website_Donation_Click(IInspectable const& sender, RoutedEventArgs const& e);

		std::wstring AdlInitialize();
		void ADL_MemoryFree_Customizations(CUSTOMISATIONS* pCustomisations);
		void AdlSetDefaultSettings();
		bool AdlCheckDriverOnlySoftware();

		std::vector<AdapterInfo> AdlGetGpuAll(bool ignoreDuplicate);
		std::optional<AdapterInfo> AdlGetGpuByDeviceId(std::wstring deviceId);
		std::optional<AdapterInfo> AdlGetGpuByAdapterIndex(int adapterIndex);
		std::vector<ADLDisplayInfo> AdlGetDisplayAll();
		std::vector<ADLDisplayInfo> AdlGetDisplayByAdapterIndex(int adapterIndex);
		std::optional<ADLDisplayInfo> AdlGetDisplayByDisplayIndex(int adapterIndex, int displayIndex);

		winrt::IAsyncOperation<winrt::IVector<RadeonTuner::AppPickerIdl>> AdlAppPickerAdd();
		winrt::IAsyncOperation<winrt::IVector<RadeonTuner::AppPickerIdl>> AdlAppPickerAddProcess();
		winrt::IAsyncOperation<winrt::IVector<RadeonTuner::AppPickerIdl>> AdlAppPickerAddLauncher();
		winrt::IAsyncOperation<winrt::IVector<RadeonTuner::AppPickerIdl>> AdlAppPickerRemoveAppGraphics();
		winrt::IAsyncOperation<winrt::IVector<RadeonTuner::AppPickerIdl>> AdlAppPickerRemoveAppTuning();
		winrt::IAsyncOperation<winrt::IVector<RadeonTuner::AppPickerIdl>> AdlAppPickerRemoveAppDisplay();
		winrt::IVector<RadeonTuner::AppPickerIdl> AdlAppPickerAddFile();

		std::vector<AdlApplication> AdlAppLoadAll(std::wstring driverArea, bool loadProperties);
		std::optional<AdlApplication> AdlAppLoadSearch(std::wstring driverArea, std::wstring fileName, std::wstring filePath);
		std::wstring AdlAppAdd(std::wstring filePath, std::wstring driverArea);
		std::wstring AdlAppRemove(AdlApplication adlApp);
		bool AdlAppRemoveAll();
		bool AdlAppSyncAll();
		bool AdlAppUnlock(AdlApplication& adlApp, bool unlock);
		bool AdlAppSetDefaults(AdlApplication& adlApp, bool clearProperties, bool addOnly);
		std::wstring AdlAppProfileGenerateName(std::wstring profileHeader);
		bool AdlAppExists(std::wstring fileName, std::wstring filePath, std::wstring driverArea);
		bool AdlAppPropertyValid(std::wstring propertyName, std::wstring driverArea);
		DATATYPES AdlAppPropertyDataTypeGet(std::wstring propertyName, std::wstring driverArea);
		ADLProfilePropertyType AdlAppConvertDataTypeToPropertyType(DATATYPES dataType);
		std::vector<ADLPropertyRecordCreate> AdlAppPropertyRecordCreateGet(std::vector<AdlAppProperty> adlAppProperties);
		std::optional<AdlAppProperty> AdlAppPropertyGet(AdlApplication adlApp, std::wstring propertyName);
		bool AdlAppPropertySave(AdlApplication& adlApp);
		bool AdlAppPropertyLoad(AdlApplication& adlApplication);
		bool AdlAppPropertyUpdate(AdlApplication& adlApp, std::vector<AdlAppProperty> properties, bool addOnly);
		bool AdlAppPropertyUpdate(AdlApplication& adlApp, std::wstring propertyGpuId, std::wstring propertyName, std::wstring propertyValue);

		bool Adl_Overdrive8_Values_Reset(int gpuAdapterIndex);
		bool Adl_Overdrive8_Values_Set(int gpuAdapterIndex, std::vector<std::tuple<ADLOD8SettingId, int, bool>> saveSettings);
		std::optional<int> Adl_Overdrive8_Load_Value(int gpuAdapterIndex, ADLOD8SettingId settingId);
		std::optional<ADLOD8SingleInitSettingWrap> Adl_Overdrive8_Load_Default(int gpuAdapterIndex, ADLOD8SettingId settingId);
		bool Adl_Overdrive8_Feature_Supported(int gpuAdapterIndex, ADLOD8FeatureControl featureId);

		bool Adl_Eyefinity_Create_Custom(int displayAdapterIndex);
		bool Adl_Eyefinity_Delete_All(int displayAdapterIndex);
		bool Adl_Eyefinity_IsEnabled(int displayAdapterIndex);
		AdlCustomResult Adl_Eyefinity_Toggle(int displayAdapterIndex, bool setEnabled);
		bool Adl_Eyefinity_Automatic_IsEnabled();

		void button_Overlay_CustomResolution_Close_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Overlay_CustomResolution_Create_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_CustomResolution_ShowHide_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_CustomResolution_Remove_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void DisplayModeInfo_Calculate_Timings();
		void DisplayModeInfo_ToUI(ADLDisplayModeInfoX2 modeInfoX2, bool actualOnly);
		std::optional<ADLDisplayModeInfoX2> DisplayModeInfo_FromADL(int adapterIndex, int displayIndex, int presentationMode, int timingStandard, int pixelWidth, int pixelHeight, int refreshRate);
		winrt::IAsyncOperation<bool> CustomResolution_Create(int adapterIndex, int displayIndex, ADLDisplayModeInfoX2 modeInfoX2);
		winrt::IAsyncOperation<bool> CustomResolution_Remove(int adapterIndex, int displayIndex, ADLDisplayModeInfoX2 modeInfoX2);

		uint16_t AdlGammaRampClamp(float clampValue);
		AdlGammaRamp AdlGammaRampBuild(float redGain, float greenGain, float blueGain);
		void AdlGammaRampGet(AdlGammaRamp gammaRamp, float& redGain, float& greenGain, float& blueGain);

		bool AdlRegistrySettingSet(int gpuAdapterIndex, std::string subKey, std::string keyName, std::wstring keyValue);
		bool AdlRegistrySettingSet(int gpuAdapterIndex, std::string subKey, std::string keyName, int keyValue);
		std::optional<std::wstring> AdlRegistrySettingGetString(int gpuAdapterIndex, std::string subKey, std::string keyName, bool decodeBinary);
		std::optional<INT> AdlRegistrySettingGetInt(int gpuAdapterIndex, std::string subKey, std::string keyName);

		std::wstring AdlxGetGpuIdentifier(int adapterIndex);
		std::wstring AdlxGetDisplayIdentifier(int adapterIndex, int displayIndex);

		bool GraphicsSettings_Convert_ToUI_Adl(GraphicsSettings graphicsSettings);
		bool GraphicsSettings_Convert_ToUI_Profile(GraphicsSettings graphicsSettings, AdlSettingGet useType);
		std::optional<GraphicsSettings> GraphicsSettings_Generate_FromADLApp(int gpuAdapterIndex, AdlApplication& adlApplication, bool loadDefault);
		std::optional<GraphicsSettings> GraphicsSettings_Generate_FromADLRegistry(int gpuAdapterIndex, std::wstring application, bool loadDefault);
		GraphicsSettings GraphicsSettingsGetSupport(int gpuAdapterIndex);
		std::vector<GraphicsStatus> GraphicsStatus_Get();
		void GraphicsStatus_Update();

		bool GraphicsSettings_Profiles_SaveToFile();
		bool GraphicsSettings_Profiles_LoadFromFile();
		bool GraphicsSettings_Profile_SaveToFile(GraphicsSettings graphicsSettings, std::wstring savePath);
		std::optional<GraphicsSettings> GraphicsSettings_Profile_LoadFromFile(std::wstring loadPath);
		bool GraphicsSettings_Profile_Add(GraphicsSettings graphicsSettingsAdd);
		bool GraphicsSettings_Profile_Replace(GraphicsSettings graphicsSettingsReplace);
		bool GraphicsSettings_Profile_Remove(std::wstring deviceId, std::wstring application);
		std::optional<std::reference_wrapper<GraphicsSettings>> GraphicsSettings_Profile_Get(std::wstring deviceId, std::wstring application);
		std::vector<std::wstring> GraphicsSettings_Profile_GetAllApps(std::wstring deviceId);
		bool GraphicsSettings_Match(GraphicsSettings settingsProfile, GraphicsSettings settingsAdl);

		bool DisplaySettings_Convert_ToUI_Adl(DisplaySettings displaySettings);
		bool DisplaySettings_Convert_ToUI_Profile(DisplaySettings displaySettings, AdlSettingGet useType);
		std::optional<DisplaySettings> DisplaySettings_Generate_FromADL(int adapterIndex, int displayIndex, std::wstring application, bool loadDefault);

		bool DisplaySettings_Profiles_SaveToFile();
		bool DisplaySettings_Profiles_LoadFromFile();
		bool DisplaySettings_Profile_SaveToFile(DisplaySettings displaySettings, std::wstring savePath);
		std::optional<DisplaySettings> DisplaySettings_Profile_LoadFromFile(std::wstring loadPath);
		bool DisplaySettings_Profile_Add(DisplaySettings displaySettingsAdd);
		bool DisplaySettings_Profile_Replace(DisplaySettings displaySettingsReplace);
		bool DisplaySettings_Profile_Remove(std::wstring deviceId, std::wstring application);
		std::optional<std::reference_wrapper<DisplaySettings>> DisplaySettings_Profile_Get(std::wstring deviceId, std::wstring application);
		std::vector<std::wstring> DisplaySettings_Profile_GetAllApps(std::wstring deviceId);
		bool DisplaySettings_Profile_Set_UsingGlobal();
		bool DisplaySettings_Profile_Set_Using(std::wstring deviceId, std::wstring application);
		bool DisplaySettings_Profile_Any_Using(std::wstring deviceId);
		bool DisplaySettings_Match(DisplaySettings settingsProfile, DisplaySettings settingsAdl, bool appProfileOnly);

		bool MultimediaSettings_Convert_ToUI_Adl(MultimediaSettings multimediaSettings);
		bool MultimediaSettings_Convert_ToUI_Profile(MultimediaSettings multimediaSettings, AdlSettingGet useType);
		std::optional<MultimediaSettings> MultimediaSettings_Generate_FromADL(int gpuAdapterIndex, std::wstring application, bool loadDefault);

		bool MultimediaSettings_Profiles_SaveToFile();
		bool MultimediaSettings_Profiles_LoadFromFile();
		bool MultimediaSettings_Profile_SaveToFile(MultimediaSettings multimediaSettings, std::wstring savePath);
		std::optional<MultimediaSettings> MultimediaSettings_Profile_LoadFromFile(std::wstring loadPath);
		bool MultimediaSettings_Profile_Add(MultimediaSettings multimediaSettingsAdd);
		bool MultimediaSettings_Profile_Replace(MultimediaSettings multimediaSettingsReplace);
		bool MultimediaSettings_Profile_Remove(std::wstring deviceId, std::wstring application);
		std::optional<std::reference_wrapper<MultimediaSettings>> MultimediaSettings_Profile_Get(std::wstring deviceId, std::wstring application);
		std::vector<std::wstring> MultimediaSettings_Profile_GetAllApps(std::wstring deviceId);
		bool MultimediaSettings_Profile_Set_UsingGlobal();
		bool MultimediaSettings_Profile_Set_Using(std::wstring deviceId, std::wstring application);
		bool MultimediaSettings_Profile_Any_Using(std::wstring deviceId);
		bool MultimediaSettings_Match(MultimediaSettings settingsProfile, MultimediaSettings settingsAdl);

		bool TuningFanSettings_Convert_ToUI_Adl(TuningFanSettings tuningFanSettings);
		bool TuningFanSettings_Convert_ToUI_Profile(TuningFanSettings tuningFanSettings, AdlSettingGet useType);
		std::optional<TuningFanSettings> TuningFanSettings_Generate_FromADL(int gpuAdapterIndex, std::wstring application, bool loadDefault);
		bool TuningFanSettings_Match(TuningFanSettings settingsProfile, TuningFanSettings settingsAdl);
		void TuningMetrics_Update();

		bool TuningFanSettings_Profiles_SaveToFile();
		bool TuningFanSettings_Profiles_LoadFromFile();
		bool TuningFanSettings_Profile_SaveToFile(TuningFanSettings tuningFanSettings, std::wstring savePath);
		std::optional<TuningFanSettings> TuningFanSettings_Profile_LoadFromFile(std::wstring loadPath);
		bool TuningFanSettings_Profile_Add(TuningFanSettings tuningFanSettingsAdd);
		bool TuningFanSettings_Profile_Replace(TuningFanSettings tuningFanSettingsReplace);
		bool TuningFanSettings_Profile_Remove(std::wstring deviceId, std::wstring application);
		std::optional<std::reference_wrapper<TuningFanSettings>> TuningFanSettings_Profile_Get(std::wstring deviceId, std::wstring application);
		std::vector<std::wstring> TuningFanSettings_Profile_GetAllApps(std::wstring deviceId);
		bool TuningFanSettings_Profile_Set_UsingGlobal();
		bool TuningFanSettings_Profile_Set_Using(std::wstring deviceId, std::wstring application);
		bool TuningFanSettings_Profile_Any_Using(std::wstring deviceId);

		void AdlxValuesExportDisplay();
		winrt::IAsyncAction AdlxValuesImportDisplay();
		void AdlxValuesExportGraphics();
		void AdlxValuesImportGraphics();
		void AdlxValuesExportTuning();
		winrt::IAsyncAction AdlxValuesImportTuning();
		bool AdlxResetShaderCache();

		bool AdlGraphicsSettingsApply(int gpuAdapterIndex, std::wstring gpuUniqueIdentifierHex, AdlApplication& adlApp, GraphicsSettings graphicsSettings, AdlSettingGet settingGet);
		bool AdlMultimediaSettingsApply(int gpuAdapterIndex, MultimediaSettings multimediaSettings, AdlSettingGet settingGet);
		bool AdlTuningFanSettingsApply(int gpuAdapterIndex, TuningFanSettings tuningFanSettings, AdlSettingGet settingGet);
		bool AdlDisplaySettingsApply(int displayAdapterIndex, int displayDisplayIndex, DisplaySettings targetSettings, DisplaySettings adlSettings, AdlSettingGet settingGet, bool appProfileOnly);

		void AdlxValuesResetSelectGpu();
		void AdlxValuesResetSelectDisplay();
		winrt::IAsyncAction AdlxValuesLoadSelectTuningApp(int gpuAdapterIndex, std::wstring application);
		winrt::IAsyncAction AdlxValuesLoadSelectDisplayApp(int dispAdapterIndex, int dispDisplayIndex, std::wstring application);
		winrt::IAsyncAction AdlxValuesLoadSelectGraphicsApp(int gpuAdapterIndex, std::wstring application);
		winrt::IAsyncAction AdlxValuesLoadSelectMultimediaApp(int gpuAdapterIndex, std::wstring application);
		winrt::IAsyncAction AdlxValuesLoadSelectGpu(AdapterInfo adapterInfo);
		winrt::IAsyncAction AdlxValuesLoadSelectDisplay(ADLDisplayInfo displayInfo);
		void AdlxValuesLoadEyefinityDisplays();
		void AdlxValuesPrepare();
		void AdlxInfoLoad();
		std::wstring AdlxInfoGpu();
		std::wstring AdlxInfoDisplay();
		std::wstring AdlxInfoApplication();
		void UpdateFanGraphGpu(TuningFanSettings tuningFanSettings);
		void UpdateFanGraphProfile();
		void ValidateFanSettings();
		winrt::IAsyncAction SettingLoad();
		void SettingAdmin();
		void SelectDefaultIndexes();
		void ShowExperimentalSettings(BOOL silent);
		void ShowNotification(std::wstring text);

		void AdlxLoopMetrics();
		void AdlxLoopProfile();

		void AdlxCheckSelectedDeviceAccess();
		void AdlxCheckDisplayEyefinityAutomatic(std::vector<std::wstring> processExeRunning);
		void AdlxCheckDisplayApplicationProfile(std::vector<std::wstring> processExeRunning);
		void AdlxCheckTuningApplicationProfile(std::vector<std::wstring> processExeRunning);

		winrt::IAsyncAction button_Eyefinity_Overlay_Remove_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_Eyefinity_Overlay_Create_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_Eyefinity_Disable_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_Eyefinity_Enable_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Eyefinity_Automatic_Toggled(IInspectable const& sender, RoutedEventArgs const& e);

		winrt::IAsyncAction button_Tuning_Apply_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_Tuning_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_Tuning_Import_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Tuning_Export_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_AppSelect_Tuning_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_AppAdd_Tuning_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_AppRemove_Tuning_Click(IInspectable const& sender, RoutedEventArgs const& e);

		winrt::IAsyncAction button_AppSelect_Graphics_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_Graphics_Clear_ShaderCache_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_Graphics_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_AppAdd_Graphics_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_AppRemove_Graphics_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Graphics_Import_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Graphics_Export_Click(IInspectable const& sender, RoutedEventArgs const& e);

		void combobox_VerticalSync_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void toggleswitch_RadeonChill_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void slider_RadeonChill_Min_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_RadeonChill_Max_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void button_RadeonChill_Link_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_RadeonEnhancedSync_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_Display_ColorDepth_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_Display_PixelFormat_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void slider_Fan_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_Contrast_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_Saturation_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void toggleswitch_FsrLatencyReduction_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void slider_RadeonBoost_MinResolution_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void toggleswitch_RadeonImageSharpening1_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void slider_RadeonImageSharpening1_Sharpening_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void toggleswitch_RadeonImageSharpening2_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_RadeonImageSharpening2_Desktop_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void slider_RadeonImageSharpening2_Sharpening_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void combobox_AntiAliasingMethod_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_AntiAliasingLevel_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void toggleswitch_MorphologicalAntiAliasing_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_AnisotropicTextureFiltering_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_Tessellation_Mode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_Tessellation_Level_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void toggleswitch_Display_VSR_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Display_GpuScaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Display_IntegerScaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_Display_ScalingMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void toggleswitch_Display_HDCPSupport_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Display_VariBright_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_Display_VariBright_Level_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void slider_Display_ColorTemperature_Kelvin_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_Brightness_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_Hue_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Video_Sharpening_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void toggleswitch_Video_Upscaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Window_Top_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_Update_Check_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_Update_Launch_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Fps_Overlayer_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Fan_Zero_Rpm_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void slider_Core_Min_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Core_Max_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void toggleswitch_OpenGLTripleBuffering_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Close_Tray_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_TextureFilteringQuality_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void toggleswitch_SurfaceFormatOptimization_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Shortcut_Startup_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Shortcut_StartMenu_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Shortcut_ContextMenu_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_StartWindowVisible_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_StartCheckUpdate_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_FsrOverrideUpscaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_FsrOverrideFrameGeneration_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_Display_DisplayColorEnhancement_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void slider_Display_Protanopia_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_Deuteranopia_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_Tritanopia_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		winrt::IAsyncAction button_Display_Import_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Display_Export_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_AntiAliasingEnhancedQuality_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_AntiAliasingOverride_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_Display_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Display_ColorTemperature_Control_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Display_CVDC_Control_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_FsrOverrideMultiFrameGeneration_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_FsrOverrideRayRegeneration_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_FsrOverrideNeuralRadianceCaching_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_FsrMultiFrameGenerationRatio_SelectionChanged(IInspectable const& sender, Controls::SelectionChangedEventArgs const& e);
		void toggleswitch_ShowExperimental_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Fan_Control_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_OpenGL10BitPixelFormat_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Frtc_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void slider_Frtc_FrameRateTarget_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);

		void button_FsrDllLoadPath_Set_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_FsrDllLoadPath_Default_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void textbox_FsrDllLoadPath_TextChanged(IInspectable const& sender, TextBoxTextChangingEventArgs const& e);
		void FsrOverrideDllUpdateTextPathInfo(std::wstring dllPath);
		void FsrOverrideDllUpdateTextVersion(std::wstring dllPath);
		std::wstring FsrOverrideDllGetPathDefault();
		std::wstring FsrOverrideDllGetPathSet(bool globalPath);

		bool FsrShowInformationIsEnabled();
		bool FsrShowInformationToggle(bool enabled);

		void DisplaySettings_Resolution_Revert();
		void DisplaySettings_Confirm_Resolution_Start();
		winrt::IAsyncAction DisplaySettings_Confirm_Resolution_Stop(bool revertResolution);
		void button_Overlay_ConfirmResolution_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Overlay_RevertResolution_Click(IInspectable const& sender, RoutedEventArgs const& e);

		void DisplaySettings_Confirm_CustomResolution_Start();
		void DisplaySettings_Confirm_CustomResolution_Stop(bool revertResolution);
		winrt::IAsyncAction combobox_CustomResolution_TimingStandard_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		winrt::IAsyncAction textbox_CustomResolution_Resolution_TextChanged(IInspectable const& sender, TextChangedEventArgs const& e);
		winrt::IAsyncAction textbox_CustomResolution_RefreshRate_TextChanged(IInspectable const& sender, TextChangedEventArgs const& e);
		void combobox_CustomResolution_Presentation_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void textbox_CustomResolution_PixelClock_TextChanged(IInspectable const& sender, TextChangedEventArgs const& e);
		void textbox_TimingTotal_TextChanged(IInspectable const& sender, TextChangedEventArgs const& e);
		void textbox_TimingFrontPorch_TextChanged(IInspectable const& sender, TextChangedEventArgs const& e);
		void textbox_TimingSyncWidth_TextChanged(IInspectable const& sender, TextChangedEventArgs const& e);
		void combobox_TimingPolarity_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);

		void LaunchDriverCleanup();
		winrt::IAsyncAction DisplayList_Combined(bool waitUpdate);
		winrt::IAsyncAction DisplayList_SelectCurrent_Values(bool waitUpdate);
		winrt::IAsyncAction DisplayList_Resolution(bool waitUpdate);
		winrt::IAsyncAction DisplayList_RefreshRate(bool waitUpdate);
		winrt::IAsyncOperation<int> ShowMessageBox(std::wstring Question, std::wstring Description, std::vector<std::wstring> Answers);

		void toggleswitch_Display_HdrEnabled_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_Multimedia_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_FsrOtaUpdates_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void toggleswitch_FrameGenEnabled_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_FrameGenSearchMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_FrameGenPerfMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_FrameGenResponseMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_FrameGenAlgorithm_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void toggleswitch_KeepActive_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_Memory_Timing_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void slider_Memory_Max_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Power_Limit_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Power_Voltage_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Power_TDC_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Video_Brightness_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void combobox_Display_Resolution_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_Display_RefreshRate_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_Display_Orientation_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void listview_Overlay_MessageBox_ItemClick(IInspectable const& sender, ItemClickEventArgs const& e);
		void button_Overlay_AppPicker_Confirm_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void listview_Overlay_AppPicker_ItemClick(IInspectable const& sender, ItemClickEventArgs const& e);
		void button_Overlay_AppPicker_Cancel_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_GpuSelect_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_DisplaySelect_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_AppSelect_Display_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_AppAdd_Display_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_AppRemove_Display_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_Multimedia_Apply_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_Display_Apply_Click(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction button_Graphics_Apply_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Eyefinity_Manage_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_RadeonBoost_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_Display_FreeSyncMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void toggleswitch_FsrShowInformation_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		winrt::IAsyncAction toggleswitch_SkipSupportCheckGraphics_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_Memory_Ecc_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
	};
}

namespace winrt::RadeonTuner::factory_implementation
{
	struct MainPage : MainPageT<MainPage, implementation::MainPage> {};
}