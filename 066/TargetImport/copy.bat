set SOURCE_DIR=E:\yuequnlei\work\ShipsDamage3DDisplay\Dll

set DEST_DIR=E:\yuequnlei\work\Warhead\source

set SHARE_DIR=E:\yuequnlei\work\ShipsDamage3DDisplay\Dll\share

xcopy %SOURCE_DIR%\bin\TargetImport.lib %DEST_DIR%\lib\ /S /F /R /Y /E
xcopy %SOURCE_DIR%\bin\TargetImportd.lib %DEST_DIR%\lib\ /S /F /R /Y /E

xcopy %SOURCE_DIR%\bin\TargetImport.dll %DEST_DIR%\bin\ /S /F /R /Y /E
xcopy %SOURCE_DIR%\bin\TargetImportd.dll %DEST_DIR%\bin\ /S /F /R /Y /E

xcopy %SOURCE_DIR%\TargetImport\ViewerWidget.h %DEST_DIR%\include\TargetImport\ /S /F /R /Y /E
xcopy %SOURCE_DIR%\TargetImport\TargetImportGlobal.h %DEST_DIR%\include\TargetImport\ /S /F /R /Y /E
xcopy %SOURCE_DIR%\TargetImport\ImportTargetWnd.h %DEST_DIR%\include\TargetImport\ /S /F /R /Y /E
xcopy %SOURCE_DIR%\TargetImport\TargetVisual.h %DEST_DIR%\include\TargetImport\ /S /F /R /Y /E
xcopy %SOURCE_DIR%\TargetImport\TargetInfo.h %DEST_DIR%\include\TargetImport\ /S /F /R /Y /E


xcopy %SOURCE_DIR%\bin\TargetImport.lib %SHARE_DIR%\lib\ /S /F /R /Y /E
xcopy %SOURCE_DIR%\bin\TargetImportd.lib %SHARE_DIR%\lib\ /S /F /R /Y /E

xcopy %SOURCE_DIR%\bin\TargetImport.dll %SHARE_DIR%\bin\ /S /F /R /Y /E
xcopy %SOURCE_DIR%\bin\TargetImportd.dll %SHARE_DIR%\bin\ /S /F /R /Y /E


xcopy %SOURCE_DIR%\TargetImport\ViewerWidget.h %SHARE_DIR%\include\ /S /F /R /Y /E
xcopy %SOURCE_DIR%\TargetImport\TargetImportGlobal.h %SHARE_DIR%\include\ /S /F /R /Y /E
xcopy %SOURCE_DIR%\TargetImport\ImportTargetWnd.h %SHARE_DIR%\include\ /S /F /R /Y /E
xcopy %SOURCE_DIR%\TargetImport\TargetVisual.h %SHARE_DIR%\include\ /S /F /R /Y /E
xcopy %SOURCE_DIR%\TargetImport\TargetInfo.h %SHARE_DIR%\include\ /S /F /R /Y /E


