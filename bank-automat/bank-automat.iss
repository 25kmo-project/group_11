[Setup]
AppName=bank-automat
AppVersion=1.0.0
AppPublisher=Group X
DefaultDirName={autopf}\bank-automat
DefaultGroupName=bank-automat
OutputDir=output
OutputBaseFilename=Bank-Automat-Setup
Compression=lzma
SolidCompression=yes
ArchitecturesInstallIn64BitMode=x64
PrivilegesRequired=admin
UninstallDisplayIcon={app}\bank-automat.exe

[Files]
Source: "build\bank-automat.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\*.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
Source: "build\platforms\*"; DestDir: "{app}\platforms"; Flags: ignoreversion recursesubdirs
Source: "build\styles\*"; DestDir: "{app}\styles"; Flags: ignoreversion recursesubdirs

[Icons]
Name: "{group}\bank-automat"; Filename: "{app}\bank-automat.exe"
Name: "{autodesktop}\bank-automat"; Filename: "{app}\bank-automat.exe"

[Run]
Filename: "{app}\bank-automat.exe"; Description: "Launches ATM app."; Flags: nowait postinstall skipifsilent