#pragma once
#include "MainPage.g.h"

namespace winrt::RadeonTuner::implementation
{
	struct MainPage : MainPageT<MainPage>
	{
		MainPage() {}

		std::wstring AdlInitialize();
		void AdlValuesPrepare();

		bool AdlAppInterfaceListLoad();
		bool AdlAppInterfaceAddFile();
		bool AdlAppInterfaceAddProcess();
		std::vector<AdlApplication> AdlAppLoad(std::wstring driverArea);
		bool AdlAppAdd(std::wstring filePath, std::wstring driverArea);
		bool AdlAppRemove(AdlApplication adlApp);
		bool AdlAppUnlock(AdlApplication adlApp);
		bool AdlAppDefaultPropertiesSet(AdlApplication& adlApp);
		std::wstring AdlAppProfileGenerateName(std::wstring profileHeader);

		bool AdlAppExists(std::wstring fileName, std::wstring filePath, std::wstring driverArea);
		bool AdlAppPropertyValid(std::wstring propertyName, std::wstring driverArea);
		DATATYPES AdlAppPropertyDataTypeGet(std::wstring propertyName, std::wstring driverArea);
		ADLProfilePropertyType AdlAppConvertDataTypeToPropertyType(DATATYPES dataType);
		std::vector<ADLPropertyRecordCreate> AdlAppPropertyRecordCreateGet(std::vector<AdlAppProperty> adlAppProperties);
		std::optional<AdlAppProperty> AdlAppPropertyGet(AdlApplication adlApp, std::wstring propertyName);
		bool AdlAppPropertySet(AdlApplication& adlApp);
		bool AdlAppPropertyUpdate(AdlApplication& adlApp, std::vector<AdlAppPropertyValue> properties);
		bool AdlAppPropertyUpdate(AdlApplication& adlApp, std::wstring propertyGpuId, std::wstring propertyName, std::wstring propertyValue);

		bool AdlRegistrySettingSet(int adlAdapterIndex, std::string subKey, std::string key, std::string value);
		bool AdlRegistrySettingSet(int adlAdapterIndex, std::string subKey, std::string key, int value);
		std::optional<std::string> AdlRegistrySettingGetString(int adlAdapterIndex, std::string subKey, std::string key);
		std::optional<INT> AdlRegistrySettingGetInt(int adlAdapterIndex, std::string subKey, std::string key);

		std::wstring AdlxInitialize();
		std::wstring AdlxGetGpuIdentifier(IADLXGPU2Ptr ppGpuPtr);
		std::wstring AdlxGetDisplayIdentifier(IADLXDisplayPtr ppDisplayInfo);

		AdlApplication GraphicsSettings_Load(std::string loadPath);
		bool GraphicsSettings_Save(AdlApplication graphicsSettings, std::string savePath);

		DisplaySettings DisplaySettings_Load(std::string loadPath);
		bool DisplaySettings_Save(DisplaySettings displaySettings, std::string savePath);
		bool DisplaySettings_Convert_ToUI(DisplaySettings displaySettings);
		DisplaySettings DisplaySettings_Generate_FromUI();

		TuningFanSettings TuningFanSettings_Load(std::string loadPath);
		bool TuningFanSettings_Save(TuningFanSettings tuningFanSettings, std::string savePath);
		bool TuningFanSettings_Convert_ToUI(TuningFanSettings tuningFanSettings, bool disableUI);
		TuningFanSettings TuningFanSettings_Generate_FromUI(bool keepActive);
		TuningFanSettings TuningFanSettings_Generate_FromAdlxGpuPtr(IADLXGPU2Ptr ppGpuPtr);
		bool TuningFanSettings_Match(TuningFanSettings tuningFanSettings, TuningFanSettings tuningFanSettingsMatch);

		bool AdlxValuesResetDisplay();
		void AdlxValuesExportDisplay();
		void AdlxValuesImportDisplay();
		void AdlxValuesExportGraphics();
		void AdlxValuesImportGraphics();
		bool AdlxValuesResetGraphics();
		void AdlxValuesExportTuning();
		void AdlxValuesImportTuning();

		void AdlxValuesLoadSelectApp();
		void AdlxValuesLoadSelectPower();
		void AdlxValuesLoadSelectGpu();
		void AdlxValuesLoadSelectDisplay();
		void AdlValuesLoadGraphicsApp();
		void AdlxValuesLoadMultimedia();
		void AdlxValuesLoadPower();
		void AdlxValuesLoadDisplay();
		void AdlxValuesLoadTuning();
		void AdlxValuesPrepare();
		bool AdlxApplyTuning(IADLXGPU2Ptr ppGpuPtr, TuningFanSettings tuningFanSettings);
		bool AdlxResetTuning();
		void AdlxInfoLoad();
		std::wstring AdlxInfoGpu();
		std::wstring AdlxInfoDisplay();
		std::wstring AdlxInfoApplication();
		void UpdateFanGraph();
		void ValidateFanSettings();
		void SettingLoad();
		void SettingAdmin();
		void SelectIndexesAdl();
		void SelectIndexesAdlx();
		void SelectIndexesMenu();
		void ShowNotification(std::wstring text);

		void AdlxLoopDevice();
		void AdlxLoopMetrics();
		void AdlxLoopKeepActive();

		void KeepActive_Load_UI();
		bool KeepActive_Export();
		bool KeepActive_Enable();
		bool KeepActive_Disable();
		bool KeepActive_Toggle();

		void page_Loaded(IInspectable const& sender, RoutedEventArgs const& e);
		void listbox_Main_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void button_Tuning_Apply_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Tuning_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Tuning_Import_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Tuning_Export_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Website_Project_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Website_Donation_Click(IInspectable const& sender, RoutedEventArgs const& e);

		void combobox_VerticalRefresh_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void toggleswitch_RadeonChill_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void slider_RadeonChill_Min_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_RadeonChill_Max_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void toggleswitch_RadeonEnhancedSync_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_FreeSync_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_Display_ColorDepth_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_Display_PixelFormat_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void slider_Fan_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_Contrast_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_Saturation_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void toggleswitch_RadeonAntiLag_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Reset_Shader_Cache_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_RadeonBoost_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void slider_RadeonBoost_MinRes_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void toggleswitch_RadeonImageSharpening_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void slider_RadeonImageSharpening_Sharpening_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void combobox_AntiAliasingMethod_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_AntiAliasingLevel_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void toggleswitch_MorphologicalAntiAliasing_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_AnisotropicTextureFiltering_Level_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_Tessellation_Mode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_Tessellation_Level_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void toggleswitch_VSR_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_GPUScaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_IntegerScaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_Display_ScalingMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void toggleswitch_HDCPSupport_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_VariBright_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_Display_VariBright_Level_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void slider_Display_ColorTemperature_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_Brightness_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_Hue_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_VideoUpscale_Sharpening_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void toggleswitch_VideoUpscale_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_VideoSuperResolution_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_FreeSyncColorAccuracy_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void slider_Display_RelativeVoltageSwing_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_RelativePreEmphasis_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void toggleswitch_DynamicRefreshRateControl_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_SmartShiftEco_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_SmartShiftMaxMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void slider_SmartShiftMaxBias_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void toggleswitch_Window_Top_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Check_Update_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_GpuSelect_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_DisplaySelect_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_AppSelect_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void button_Fps_Overlayer_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Fan_Zero_Rpm_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Tuning_Keep_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Tuning_Keep_PointerPressed(IInspectable const& sender, PointerRoutedEventArgs const& e);
		void toggleswitch_OpenGLTripleBuffering_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Close_Tray_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_TextureFilteringQuality_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void toggleswitch_SurfaceFormatOptimization_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Shortcut_Startup_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Shortcut_StartMenu_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Shortcut_ContextMenu_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_StartWindowVisible_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_FsrOverrideUpscaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_FsrOverrideFrameGen_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_Display_DisplayColorEnhancement_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void slider_Display_Protanopia_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_Deuteranopia_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_Tritanopia_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void button_Graphics_Import_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Graphics_Export_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Display_Import_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Display_Export_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Graphics_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Graphics_AddExe_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Graphics_AddProcess_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Graphics_Remove_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Graphics_Unlock_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_EQAA_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_AntiAliasingOverride_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Display_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e);
	};
}

namespace winrt::RadeonTuner::factory_implementation
{
	struct MainPage : MainPageT<MainPage, implementation::MainPage>
	{
	};
}