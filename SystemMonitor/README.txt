# System Monitor - Ulgam Gözegçilik Programmasy

Windows kompýuterleri üçin ulgam monitori (CPU, RAM, status)

## 📦 Göçürip alyş

1. **Actions** bölümine giriň
2. Iň soňky **build** işini saýlaň
3. **Artifacts** -> **SystemMonitor-EXE** göçürip alyň
4. ZIP-i açyp, `server.exe` we `client.exe` çykaryň

## 🚀 Işlediş

### 1 kompýuterde test:
server.exe # Ilki serwer
client.exe # Soň klient


### 2 kompýuterde:
- **Server**: `server.exe` işlediň
- **Client**: client.cpp-de IP-ni üýtgedip gaýtadan ýükläň

## ⚙️ Awtozapusk goşmak

```batch
install\install_server.bat  (administrator)
install\install_client.bat  (administrator)



 Doly papka gurluşy (hazirki ýagdaý)
 SystemMonitor/
│
├── build.bat                 (kompilyasiya ucin)
│
├── server/
│   ├── server.cpp           (kod)
│   └── (server.exe bu yerde doreyer)
│
├── client/
│   ├── client.cpp           (kod)
│   └── (client.exe bu yerde doreyer)
│
└── install/
    ├── install_server.bat   (serweri awtozapusk etmek)
    ├── install_client.bat   (klienti awtozapusk etmek)
    └── uninstall.bat        (ayyrmak ucin)

 Kompilyasiya etmek (EXE öwürmek)
Eger MinGW gurnan bolsaňyz:
1. SystemMonitor papkasyny açyň
2. build.bat faýlyna goşa klik ediň
3. Kompilyasiya tamamlanýança garaşyň
4. server\server.exe we client\client.exe döreýär

Visual Studio gurnan bolsaňyz:
1. Visual Studio-ni acyn
2. File -> New -> Project
3. Console App (C++) -> server
4. server.cpp koduny gosun
5. Build -> Build Solution (Ctrl+Shift+B)
6. Client ucin hem solay edin

Programmany işletmek
Test etmek (1-nji kompýuterde):
1. server\server.exe goşa klik ediň (Konsol penjiresi acylyar)
2. client\client.exe goşa klik ediň (Başga konsol penjiresi acylyar)
3. Klient maglumatlary iberyar, serwer kabul edyar

Hakyky ulgamda (2 kompýuterde):
# Kompýuter 1 (Serwer)
1. server\server.exe isledin
2. Firewall-da 8888 portuny acyn

# Kompýuter 2 (Klient)
1. client.cpp icinde server IP-ni uytgedin:
   server.sin_addr.s_addr = inet_addr("192.168.1.100"); # Serwerin IP
2. client.exe isledin


 Awtozapusk goşmak
 1. install papkasyny acyn
2. install_server.bat sag klik -> Run as Administrator
3. install_client.bat sag klik -> Run as Administrator
4. Kompyuteri gaytadan yuklanynda programmalar oz-ozunden isleyar

Işleýändigini barlamak
Serwerde (computers.csv faýly döreýär):
Name,IP,CPU%,RAM%,Status,LastUpdate,Priority
DESKTOP-ABC123,192.168.1.101,45.2,38.5,NORMAL,Mon Jan 20 15:30:00 2025,NORMAL
DESKTOP-XYZ789,192.168.1.102,92.3,88.1,CRITICAL,Mon Jan 20 15:30:05 2025,CRITICAL

Serwer konsolynda:
=== SYSTEM MONITOR SERVER ===
Aktiw kompýuterler: 2
=============================

[⚠️ KRITIK] DESKTOP-XYZ789 (192.168.1.102)
   CPU: 92.3%  RAM: 88.1%
   Status: CRITICAL

[✅ NORMAL] DESKTOP-ABC123 (192.168.1.101)
   CPU: 45.2%  RAM: 38.5%
   Status: NORMAL