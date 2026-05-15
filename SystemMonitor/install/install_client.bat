@echo off
title Client Auto-start Installer
echo ====================================
echo   CLIENT OTOMATIK ISLEDIJI
echo ====================================
echo.

set "CLIENT_PATH=%~dp0..\client.exe"

if not exist "%CLIENT_PATH%" (
    echo [ERROR] client.exe tapylmady!
    pause
    exit /b 1
)

reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Run" /v "SystemMonitorClient" /t REG_SZ /d "%CLIENT_PATH%" /f

echo [OK] Client otomatik isledije gosuldy!
echo.
pause