; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!
;https://www.gtk.org/docs/installations/windows


#define MyAppName "muposys-desk"
#define MyAppVersion "1.0.0-alpha"
#define MyAppPublisher "Octetos, Inc."
#define MyAppURL "https://www.example.com/"
#define MyAppExeName "mps-desk-v1.exe"
#define MyAppAssocName MyAppName + " File"
#define MyAppAssocExt ".mps"
#define MyAppAssocKey StringChange(MyAppAssocName, " ", "") + MyAppAssocExt

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{F0A89119-1B36-4FC6-A28B-E5C1E8846B66}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppName}
ChangesAssociations=yes
DisableProgramGroupPage=yes
; Uncomment the following line to run in non administrative install mode (install for current user only.)
;PrivilegesRequired=lowest
PrivilegesRequiredOverridesAllowed=commandline
OutputBaseFilename=mps-setup
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "bin\desk-installer\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
;Source: "bin\desk-installer\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion 
;Source: "bin\desk-installer\*.dll"; DestDir: "{app}"; Flags: ignoreversion   
Source: "bin\desk-installer\config-dev"; DestDir: "{app}"; Flags: ignoreversion
;Source: "bin\desk-installer\share\*"; DestDir: "{app}\share"; Flags: ignoreversion recursesubdirs  
;Source: "bin\desk-installer\etc\*"; DestDir: "{app}\etc"; Flags: ignoreversion recursesubdirs  
Source: "bin\desk-installer\muposys.glade"; DestDir: "{app}"; Flags: ignoreversion     

;Source: "..\..\core\bin\Release\octetos-core-3.dll"; DestDir: "{app}"; Flags: ignoreversion     
;Source: "..\..\cave\bin\Release\cave-mmsql-0.dll"; DestDir: "{app}"; Flags: ignoreversion   
;Source: "..\..\cave\bin\Release\cave-mmsql-1.dll"; DestDir: "{app}"; Flags: ignoreversion       
;Source: "..\core\bin\Release\muposys-core-1.dll"; DestDir: "{app}"; Flags: ignoreversion   
;Source: "bin\Release\muposys-desk-1.dll"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Registry]
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocExt}\OpenWithProgids"; ValueType: string; ValueName: "{#MyAppAssocKey}"; ValueData: ""; Flags: uninsdeletevalue
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}"; ValueType: string; ValueName: ""; ValueData: "{#MyAppAssocName}"; Flags: uninsdeletekey
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\{#MyAppExeName},0"
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\{#MyAppExeName}"" ""%1"""
Root: HKA; Subkey: "Software\Classes\Applications\{#MyAppExeName}\SupportedTypes"; ValueType: string; ValueName: ".myp"; ValueData: ""

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

