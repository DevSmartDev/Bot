;NSIS Modern User Interface
;Welcome/Finish Page Example Script
;Written by Joost Verburg

;--------------------------------
;Include Modern UI

   !include "MUI2.nsh"
   !include "EnvVarUpdate.nsh" #download http://nsis.sourceforge.net/mediawiki/images/a/ad/EnvVarUpdate.7z

;   !include "StrFunc.nsh"
 ;  !include "WordFunc.nsh"
 ;  !include "registry.nsh"
 ;  !include "LogicLib.nsh"
 ;  !include "WinVer.nsh"
;--------------------------------
;General

;------------------------------
;Include Mime Type
	!include "FileAssociation.nsh"
;

Name "SmartStreetLight"
SetCompressor /SOLID bzip2
OutFile "spl_setup.exe"
 ;Default installation folder
InstallDir $PROGRAMFILES\icdrec\spl
LicenseText "License"
LicenseData "license.txt"

!define VERSION  ${__DATE__}
!define PATH	$R8
!define SETUP_NAME "spl"
!define TEMP1 $R0 ;Temp variable
!define PACKAGE "SmartStreetLight" ;Temp variable
!define DIR_REGISTRY "SOFTWARE\icdrec\spl"
!define DIR_UNINSTALL_REGISTRY "Software\Microsoft\Windows\CurrentVersion\Uninstall\spl"
;------------------------------------------------------------


BrandingText "spl Installer"
;Icon "C:\Program Files (x86)\NSISPortable\App\NSIS\Contrib\Graphics\Icons\arrow2-install.ico"
; MUI Settings / Icons
!define MUI_ICON  "light.ico"
!define MUI_UNICON  "light.ico"
CRCCheck          on
ShowInstDetails   show
VIProductVersion  0.0.0.1

VIAddVersionKey   ProductName    SplSetup
VIAddVersionKey   ProductVersion  "${VERSION}"
VIAddVersionKey   CompanyName     "icdrec"
VIAddVersionKey   FileVersion     "${VERSION}"
VIAddVersionKey   FileDescription "spl software"
VIAddVersionKey   LegalCopyright  ""


ShowInstDetails show

XPStyle on


;--------------------------------
;Interface Settings
 !define MUI_ABORTWARNING
 ;Show all languages, despite user's codepage
 !define MUI_LANGDLL_ALLLANGUAGES
;--------------------------------
;Language Selection Dialog Settings
  ;Remember the installer language
  !define MUI_LANGDLL_REGISTRY_ROOT "HKCU" 
  !define MUI_LANGDLL_REGISTRY_KEY ${DIR_REGISTRY}
  !define MUI_LANGDLL_REGISTRY_VALUENAME "Install software"

;--------------------------------
;Pages



!define MUI_LICENSEPAGE_RADIOBUTTONS
!insertmacro MUI_PAGE_WELCOME
	!insertmacro MUI_PAGE_LICENSE $(license)
	!insertmacro MUI_PAGE_COMPONENTS
	!insertmacro MUI_PAGE_DIRECTORY
        !insertmacro MUI_PAGE_INSTFILES
	!insertmacro MUI_PAGE_FINISH
	!insertmacro MUI_UNPAGE_WELCOME
	!insertmacro MUI_UNPAGE_CONFIRM
	!insertmacro MUI_UNPAGE_INSTFILES
	!insertmacro MUI_UNPAGE_FINISH
;--------------------------------
;Languages

  !insertmacro MUI_LANGUAGE "English" ;first language is the default language
  


;--------------------------------
;Reserve Files

  ;If you are using solid compression, files that are required before
  ;the actual installation should be stored first in the data block,
  ;because this will make your installer start faster.

  

LicenseLangString license  ${LANG_ENGLISH} "license.txt"

;--------------------------------

Section "-${SETUP_NAME}' Files" SecDummy

        SetOutPath "$INSTDIR"
	File /r ${PACKAGE}\bin
	File /r ${PACKAGE}\include
        File /r ${PACKAGE}\lib
        File /r ${PACKAGE}\share
        ${EnvVarUpdate} $0 "PATH" "A" "HKLM" $INSTDIR\bin
	WriteUninstaller $INSTDIR\Uninstall.exe
	; Write the installation path into the registry
	WriteRegStr HKLM ${DIR_REGISTRY} "Install_Dir" "$INSTDIR"
	; Write the uninstall keys for Windows
	WriteRegStr HKLM ${DIR_UNINSTALL_REGISTRY} "DisplayName" ${SETUP_NAME}
	WriteRegStr HKLM ${DIR_UNINSTALL_REGISTRY} "UninstallString" '$INSTDIR\Uninstall.exe'
	WriteRegDWORD HKLM ${DIR_UNINSTALL_REGISTRY} "NoModify" 1
	WriteRegDWORD HKLM ${DIR_UNINSTALL_REGISTRY} "NoRepair" 1
	# later, inside a section:
	${registerExtension} "$INSTDIR\bin\SmartPublicLight.exe" ".spl" "SPL File"
SectionEnd


Section "Links in Start Menu"
	CreateDirectory "$SMPROGRAMS\spl"
	CreateShortCut "$SMPROGRAMS\spl\spl.lnk" "$INSTDIR\bin\SmartPublicLight.exe"
	CreateShortCut "$SMPROGRAMS\spl\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
SectionEnd

Section "Links in Desktop"
	CreateShortCut "$DESKTOP\spl.lnk" "$INSTDIR\bin\SmartPublicLight.exe"
SectionEnd
;Function LaunchLink
;   ExecShell "" "$DESKTOP\spl.lnk"
;FunctionEnd
;--------------------------------
;Installer Functions
Function .onInit
     ;process exists
		Processes::FindProcess "SmartPublicLight.exe"
		StrCmp $R0 "1" pro_equal pro_no_equal

		pro_equal:
			MessageBox MB_YESNO|MB_ICONQUESTION "spl is already running. Do you want to exit the program to continue setup?$\n Warring: your project may be lost, you should backup before setup." IDNO NoAbort_pro
				Processes::KillProcess "SmartPublicLight.exe"
				Goto pro_no_equal
			NoAbort_pro:
				Quit

		pro_no_equal:
	;--------------------
        ReCheckUninstall:
	ReadRegStr $1 HKLM "${DIR_REGISTRY}\" "Install_Dir"
	${If} '$1' != ""
	    IfFileExists "$1\Uninstall.exe"  msgUninstall continue
	    msgUninstall:
                        MessageBox MB_YESNO "Do you want to uninstall the available spl software and continue to setup $1?" IDNO NoAbort1
			ExecWait  '"$1\Uninstall.exe" _?=$1' $0
			;MessageBox MB_OK "result= $0"
			${If} $0 <> 0
				MessageBox MB_OK "Error: uninstall spl"
			        goto  continue
                        ${EndIf}
                                ;goto  continue
                                goto ReCheckUninstall
                                
	     NoAbort1:
		Quit
         ${EndIf}
         continue:
FunctionEnd


;--------------------------------
;Uninstaller Section

Section "Uninstall"
	MessageBox MB_YESNO "Do you want to uninstall ${SETUP_NAME}?" IDYES NoAbort
		Quit
NoAbort:
	; ------------- delete file ---------------------
	RMDir /r $INSTDIR\bin
	RMDir /r $INSTDIR\include
        RMDir /r $INSTDIR\lib
        RMDir /r $INSTDIR\share
        RMDir /r "$SMPROGRAMS\spl"
	DeleteRegKey /ifempty HKCU ${DIR_REGISTRY}
	DeleteRegKey HKLM ${DIR_UNINSTALL_REGISTRY}
	DeleteRegKey HKLM ${DIR_REGISTRY}
	${un.EnvVarUpdate} $0 "PATH" "R" "HKLM" $INSTDIR
        Delete $INSTDIR\Uninstall.exe
        ;RMDir /r $INSTDIR
	${unregisterExtension} ".spl" "SPL File"
SectionEnd

;--------------------------------
;Uninstaller Functions

Function un.onInit


FunctionEnd


