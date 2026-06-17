You can find driver bug workarounds in the code by searching for: //DriverBug#

#DriverBug#1
Bug or limitation in newer AMD drivers does not allow separate app settings for each GPU so settings must unfortunately be set the same for all GPU's.
In older drivers you needed to set the used GpuID at 'UMD\AppGpuId' but for some reason in newer drivers this value seems to be ignored breaking support for separate settings.
Driver stores settings like this GpuId1::SettingOn;;GpuId2::SettingOff;; but only the first value is used ignoring 'UMD\AppGpuId'.
Note: this workaround breaks profile compatibility with Radeon Software but does make settings work on old and new drivers.
Note: changing GPU Preference in Windows graphics settings does not adapt to settings set for each GPU it uses the same settings for all GPU's. (App profile and KMD registry)

#DriverBug#2
Bug in AMD driver does not sort paths by length and trims \ from ending so it will pick wrong profile depending on which one was added or changed last.
Example: 'C:\Path Longer*' and 'C:\Path Long*' will use application profile 'C:\Path Long*' on 'C:\Path Longer*' when the executable name is the same.
Note: this workaround breaks profile compatibility with Radeon Software but allows user to move app folders.
Workaround#1: Update settings using identical executable name with shortest path last to make the app come on top of the list.
Workaround#2: Remove and re-add all applications sorted by file path length after each setting change to fix the list order.
Workaround#3: Set the file path as wildcard making identical file names share the same profile... not ideal with names like game.exe

#DriverBug#3
Bug in AMD driver sets Anti-Aliasing level to wrong value.
When using the 'Override Application Settings' and set it to 8xEQ without having EQAA enabled it sets to 8x instead, picking 8xEQ in the combobox should also enable EQAA but it does not.
To manually enable EQAA you first need to select 'Enhance Application Settings' before using 'Override Application Settings' to workaround this issue.

#DriverBug#4
Bug in AMD driver resets Anisotropic level to 2x when disabled and enabled.

#DriverBug#5
Using Latency Reduction in Global application profile (*.*) causes it to be used for all processes using 3D rendering including Windows system apps.
AMD driver does not seem to check for sytem processes to ignore like ApplicationFrameHost, StartMenuExperienceHost and MsEdgeWebView2.
This can cause higher CPU load at all times because one of those system processes is always running and using Latency Reduction.

#DriverBug#6
AMD Radeon Fluid Motion Frames does not work when Radeon Software is not running in the background breaking support for it in RadeonTuner using the 'Driver Only' or 'Minimal' software installation type.
Radeon Software reads Graphics settings from '%LOCALAPPDATA%\AMD\CN\gmdb.blb' and if an application is added and AFMF is enabled in Global (DrvFrameGenEnabled) or in GMDB it sends a signal to the game process to enable AFMF.