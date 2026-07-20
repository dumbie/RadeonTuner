#pragma once
#include "MainPage.g.h"

namespace winrt::RadeonTuner::implementation
{
	struct MainPage : MainPageT<MainPage>
	{
		MainPage() {}

		std::wstring AdlInitialize();
		void ADL_MemoryFree_Customizations(CUSTOMISATIONS* pCustomisations);

		std::vector<AdapterInfo> AdlGetGpuAll();
		std::optional<AdapterInfo> AdlGetGpuByDeviceId(std::wstring deviceId);
		std::optional<AdapterInfo> AdlGetGpuByAdapterIndex(int adapterIndex);
		std::vector<ADLDisplayInfo> AdlGetDisplayAll();
		std::vector<ADLDisplayInfo> AdlGetDisplayByAdapterIndex(int adapterIndex);
		std::optional<ADLDisplayInfo> AdlGetDisplayByDisplayIndex(int adapterIndex, int displayIndex);
		bool AdlDetectDisplayChange();

		bool AdlxValuesLoadApplicationList(bool selectFirst);
		void AdlAppInterfaceAddFile();
		void AdlAppInterfaceAddProcess();
		std::optional<std::reference_wrapper<AdlApplication>> AdlAppSelectedGet();
		std::vector<AdlApplication> AdlAppsLoad(std::wstring driverArea);
		std::wstring AdlAppAdd(std::wstring filePath, std::wstring driverArea);
		std::wstring AdlAppRemove(AdlApplication adlApp);
		bool AdlAppUnlock(AdlApplication adlApp, bool unlock);
		bool AdlAppsSetDefaults(AdlApplication& adlApp, bool clearProperties, bool addOnly);
		std::wstring AdlAppProfileGenerateName(std::wstring profileHeader);
		void AdlSetDefaultSettings();
		bool AdlCheckDriverOnlySoftware();

		bool Adl_Overdrive8_Reset(int gpuAdapterIndex);
		bool Adl_Overdrive8_Set_Values(int gpuAdapterIndex, std::vector<std::tuple<ADLOD8SettingId, int, bool>> saveSettings);
		std::optional<int> Adl_Overdrive8_Load_Value(int gpuAdapterIndex, ADLOD8SettingId settingId);
		std::optional<ADLOD8SingleInitSettingWrap> Adl_Overdrive8_Load_Default(int gpuAdapterIndex, ADLOD8SettingId settingId);
		bool Adl_Overdrive8_Feature_Supported(int gpuAdapterIndex, ADLOD8FeatureControl featureId);

		bool Adl_Eyefinity_Create_Custom(int displayAdapterIndex);
		bool Adl_Eyefinity_Delete_All(int displayAdapterIndex);
		bool Adl_Eyefinity_IsEnabled(int displayAdapterIndex);
		bool Adl_Eyefinity_Toggle(int displayAdapterIndex, bool setEnabled);

		bool AdlAppExists(std::wstring fileName, std::wstring filePath, std::wstring driverArea);
		bool AdlAppPropertyValid(std::wstring propertyName, std::wstring driverArea);
		DATATYPES AdlAppPropertyDataTypeGet(std::wstring propertyName, std::wstring driverArea);
		ADLProfilePropertyType AdlAppConvertDataTypeToPropertyType(DATATYPES dataType);
		std::vector<ADLPropertyRecordCreate> AdlAppPropertyRecordCreateGet(std::vector<AdlAppProperty> adlAppProperties);
		std::optional<AdlAppProperty> AdlAppPropertyGet(AdlApplication adlApp, std::wstring propertyName);
		bool AdlAppPropertySave(AdlApplication& adlApp);
		bool AdlAppPropertyUpdate(AdlApplication& adlApp, std::vector<AdlAppProperty> properties, bool addOnly);
		bool AdlAppPropertyUpdate(AdlApplication& adlApp, std::wstring propertyGpuId, std::wstring propertyName, std::wstring propertyValue);

		bool AdlRegistrySettingSet(int gpuAdapterIndex, std::string subKey, std::string keyName, std::wstring keyValue);
		bool AdlRegistrySettingSet(int gpuAdapterIndex, std::string subKey, std::string keyName, int keyValue);
		std::optional<std::wstring> AdlRegistrySettingGetString(int gpuAdapterIndex, std::string subKey, std::string keyName, bool decodeBinary);
		std::optional<INT> AdlRegistrySettingGetInt(int gpuAdapterIndex, std::string subKey, std::string keyName);

		std::wstring AdlxGetGpuIdentifier(int adapterIndex);
		std::wstring AdlxGetDisplayIdentifier(int adapterIndex, int displayIndex);

		void GraphicsStatus_Update();
		std::vector<GraphicsStatus> GraphicsStatus_Get();
		std::optional<GraphicsSettings> GraphicsSettings_FileLoad(std::string loadPath);
		bool GraphicsSettings_FileSave(GraphicsSettings graphicsSettings, std::string savePath);
		bool GraphicsSettings_Convert_ToUI_ADL(GraphicsSettings graphicsSettings);
		bool GraphicsSettings_Convert_ToUI_Current(GraphicsSettings graphicsSettings);
		bool GraphicsSettings_Convert_ToUI_Default(GraphicsSettings graphicsSettings);
		std::optional<GraphicsSettings> GraphicsSettings_Generate_FromADLApp(AdlApplication& adlApplication);
		std::optional<GraphicsSettings> GraphicsSettings_Generate_FromADLRegistry(int gpuAdapterIndex);

		std::optional<DisplaySettings> DisplaySettings_FileLoad(std::string loadPath);
		bool DisplaySettings_FileSave(DisplaySettings displaySettings, std::string savePath);
		bool DisplaySettings_Convert_ToUI_Adl(DisplaySettings displaySettings);
		bool DisplaySettings_Convert_ToUI_Current(DisplaySettings displaySettings);
		bool DisplaySettings_Convert_ToUI_Default(DisplaySettings displaySettings);
		std::optional<DisplaySettings> DisplaySettings_Generate_FromADL(int adapterIndex, int displayIndex);

		bool Adl_Multimedia_Set_Mode(int gpuAdapterIndex);
		bool MultimediaSettings_Convert_ToUI_ADL(MultimediaSettings multimediaSettings);
		bool MultimediaSettings_Convert_ToUI_Current(MultimediaSettings multimediaSettings);
		bool MultimediaSettings_Convert_ToUI_Default(MultimediaSettings multimediaSettings);
		std::optional<MultimediaSettings> MultimediaSettings_Generate_FromADL(int gpuAdapterIndex);

		bool TuningFanSettings_Convert_ToUI_Adl(TuningFanSettings tuningFanSettings);
		bool TuningFanSettings_Convert_ToUI_Current(TuningFanSettings tuningFanSettings);
		std::optional<TuningFanSettings> TuningFanSettings_Generate_FromADL(int gpuAdapterIndex);
		bool TuningFanSettings_Profiles_SaveToFile();
		bool TuningFanSettings_Profiles_LoadFromFile();
		std::optional<TuningFanSettings> TuningFanSettings_Profile_LoadFromFile(std::string loadPath);
		bool TuningFanSettings_Profile_SaveToFile(TuningFanSettings tuningFanSettings, std::string savePath);
		bool TuningFanSettings_Match(TuningFanSettings tuningFanSettingsProfile, TuningFanSettings tuningFanSettingsGpu);
		bool TuningFanSettings_Profile_Add(TuningFanSettings tuningFanSettings);
		bool TuningFanSettings_Profile_Replace(TuningFanSettings tuningFanSettings);
		std::optional<std::reference_wrapper<TuningFanSettings>> TuningFanSettings_Profile_Get(std::wstring gpuIdentifier);
		bool TuningFanSettings_Profile_Remove(std::wstring gpuIdentifier);
		void TuningMetrics_Update();

		void AdlxValuesExportDisplay();
		void AdlxValuesImportDisplay();
		void AdlxValuesExportGraphics();
		void AdlxValuesImportGraphics();
		void AdlxValuesExportTuning();
		void AdlxValuesImportTuning();
		bool AdlxResetShaderCache();

		std::wstring AdlxValuesLoadDisplayList(bool selectFirst);
		std::wstring AdlxValuesLoadGpuList(bool selectFirst);
		void AdlxValuesLoadSelectApp();
		void AdlxValuesLoadSelectGpu();
		void AdlxValuesLoadSelectDisplay();
		void AdlValuesLoadGraphicsApp();
		void AdlValuesLoadGraphicsRegistry();
		void AdlxValuesLoadMultimedia();
		void AdlxValuesLoadDisplay();
		void AdlxValuesLoadTuning();
		std::wstring AdlxValuesPrepare();
		bool AdlTuningApply(int gpuAdapterIndex, TuningFanSettings tuningFanSettings);
		void AdlxInfoLoad();
		std::wstring AdlxInfoGpu();
		std::wstring AdlxInfoDisplay();
		std::wstring AdlxInfoApplication();
		void UpdateFanGraphGpu(TuningFanSettings tuningFanSettings);
		void UpdateFanGraphProfile();
		void ValidateFanSettings();
		void SettingLoad();
		void SettingAdmin();
		void SelectDefaultIndexes();
		void ShowExperimentalSettings(BOOL silent);
		void ShowNotification(std::wstring text);

		void AdlxLoopDevice();
		void AdlxLoopMetrics();
		void AdlxLoopKeepActive();

		bool PowerBoost_Applications_List(bool selectFirst);
		bool PowerBoost_Applications_LoadFromFile();
		bool PowerBoost_Applications_SaveToFile();
		void button_PowerBoost_AddExe_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_PowerBoost_Remove_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_PowerBoost_Toggled(IInspectable const& sender, RoutedEventArgs const& e);

		bool Eyefinity_Applications_List(bool selectFirst);
		bool Eyefinity_Applications_LoadFromFile();
		bool Eyefinity_Applications_SaveToFile();
		void button_Eyefinity_AppAddExe_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Eyefinity_AppRemove_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Eyefinity_Remove_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Eyefinity_Create_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Eyefinity_Disable_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Eyefinity_Enable_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Eyefinity_Automatic_Toggled(IInspectable const& sender, RoutedEventArgs const& e);

		void page_Loaded(IInspectable const& sender, RoutedEventArgs const& e);
		void listbox_Main_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void button_Tuning_Apply_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Tuning_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Tuning_Import_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Tuning_Export_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Website_Project_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Website_Donation_Click(IInspectable const& sender, RoutedEventArgs const& e);

		void combobox_VerticalSync_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void toggleswitch_RadeonChill_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void slider_RadeonChill_Min_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_RadeonChill_Max_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void button_RadeonChill_Link_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_RadeonEnhancedSync_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_FreeSync_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_Display_ColorDepth_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_Display_PixelFormat_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void slider_Fan_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_Contrast_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_Saturation_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void toggleswitch_FsrLatencyReduction_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Graphics_Clear_ShaderCache_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_RadeonBoost_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
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
		void toggleswitch_VSR_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_GpuScaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_IntegerScaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_Display_ScalingMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void toggleswitch_HDCPSupport_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_VariBright_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_Display_VariBright_Level_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void slider_Display_ColorTemperature_Kelvin_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_Brightness_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_Hue_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Video_Sharpening_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void toggleswitch_Video_Upscaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Window_Top_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Check_Update_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_GpuSelect_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_DisplaySelect_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_AppSelect_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
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
		void toggleswitch_FsrOverrideUpscaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_FsrOverrideFrameGeneration_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_Display_DisplayColorEnhancement_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void slider_Display_Protanopia_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_Deuteranopia_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_Tritanopia_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void button_Graphics_Import_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Graphics_Export_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Display_Import_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Display_Export_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Graphics_Reset_Settings_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Graphics_AddExe_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Graphics_AddProcess_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Graphics_Remove_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_AntiAliasingEnhancedQuality_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_AntiAliasingOverride_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Display_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Overlay_Exit_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Display_ColorTemperature_Control_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Display_CVDC_Control_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_FsrOverrideMultiFrameGeneration_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_FsrOverrideRayRegeneration_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_FsrOverrideNeuralRadianceCaching_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_MultiFrameGenerationRatio_SelectionChanged(IInspectable const& sender, Controls::SelectionChangedEventArgs const& e);
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
		void toggleswitch_HdrEnabled_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_Display_HdrMediaProfile_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void button_Overlay_DriverCleanup_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Multimedia_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e);
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
		void slider_Power_Limit_PB_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Power_Voltage_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Power_Voltage_PB_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Power_TDC_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Power_TDC_PB_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Video_Brightness_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void combobox_Display_Resolution_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_Display_RefreshRate_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_Display_Orientation_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void DisplayList_Resolution(bool waitUpdate);
		void DisplayList_RefreshRate();
		void DisplayList_SelectCurrent_Values();
		void DisplaySettings_Resolution_Revert();
		void DisplaySettings_Confirm_Resolution_Start();
		void DisplaySettings_Confirm_Resolution_Stop(bool revertResolution);
		void button_Overlay_ConfirmResolution_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Overlay_RevertResolution_Click(IInspectable const& sender, RoutedEventArgs const& e);
	};
}

namespace winrt::RadeonTuner::factory_implementation
{
	struct MainPage : MainPageT<MainPage, implementation::MainPage> {};
}