@echo off
title Server Auto-start Installer
echo ====================================
echo   SERVER OTOMATIK ISLEDIJI
echo ====================================
echo.

set "SERVER_PATH=%~dp0..\server.exe"

if not exist "%SERVER_PATH%" (
    echo [ERROR] server.exe tapylmady!
    echo Yer: %SERVER_PATH%
    pause
    exit /b 1
)

reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Run" /v "SystemMonitorServer" /t REG_SZ /d "%SERVER_PATH%" /f

if %errorlevel% equ 0 (
    echo [OK] Server otomatik isledije gosuldy!
) else (
    echo [ERROR] Registry-e gosup bolmady!
)

echo.
pause