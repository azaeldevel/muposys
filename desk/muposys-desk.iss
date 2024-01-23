
#define MyAppName "muposys"
#define MyAppVersion "3.0.0-alpha-v1"
#define MyAppPublisher "Octetos, Inc."
#define MyAppURL "https://github.com/azaeldevel/muposys"
#define MyAppExeName "mps-desk-v1.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{5A4B55ED-907B-4DCD-8A9E-9864F8F462E5}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppName}
DisableProgramGroupPage=yes
; Uncomment the following line to run in non administrative install mode (install for current user only.)
;PrivilegesRequired=lowest
PrivilegesRequiredOverridesAllowed=dialog
OutputDir=desk-installer
OutputBaseFilename=muposys-setup
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "desk-installer\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion
Source: "desk-installer\cave-mmsql-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "desk-installer\cave-mmsql-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "desk-installer\libconfig++-11.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "desk-installer\libgcc_s_seh-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "desk-installer\libmariadb.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "desk-installer\libstdc++-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "desk-installer\mps-desk-v1.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "desk-installer\muposys-core-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "desk-installer\octetos-core-3.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "desk-installer\config-dev"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

