@echo off
title SystemMonitor Uninstaller
echo ====================================
echo   SYSTEM MONITOR - AYIRMAK
echo ====================================
echo.

reg delete "HKCU\Software\Microsoft\Windows\CurrentVersion\Run" /v "SystemMonitorServer" /f 2>nul
reg delete "HKCU\Software\Microsoft\Windows\CurrentVersion\Run" /v "SystemMonitorClient" /f 2>nul

echo [OK] Otomatik isledijiden ayyryldy!
echo.
pause