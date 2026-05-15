#include <iostream>
#include <string>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

string getComputerName() {
    char name[256];
    DWORD size = 256;
    GetComputerNameA(name, &size);
    return string(name);
}

string getLocalIP() {
    char hostname[256];
    gethostname(hostname, 256);
    hostent* host = gethostbyname(hostname);
    if (host) {
        in_addr addr;
        addr.s_addr = *(u_long*)host->h_addr_list[0];
        return string(inet_ntoa(addr));
    }
    return "127.0.0.1";
}

string getCPUusage() {
    static FILETIME prevIdle = {0}, prevKernel = {0}, prevUser = {0};
    FILETIME idle, kernel, user;
    
    GetSystemTimes(&idle, &kernel, &user);
    
    ULARGE_INTEGER idleTime, kernelTime, userTime;
    idleTime.LowPart = idle.dwLowDateTime;
    idleTime.HighPart = idle.dwHighDateTime;
    kernelTime.LowPart = kernel.dwLowDateTime;
    kernelTime.HighPart = kernel.dwHighDateTime;
    userTime.LowPart = user.dwLowDateTime;
    userTime.HighPart = user.dwHighDateTime;
    
    if (prevIdle.dwLowDateTime != 0) {
        ULARGE_INTEGER prevIdleTime, prevKernelTime, prevUserTime;
        prevIdleTime.LowPart = prevIdle.dwLowDateTime;
        prevIdleTime.HighPart = prevIdle.dwHighDateTime;
        prevKernelTime.LowPart = prevKernel.dwLowDateTime;
        prevKernelTime.HighPart = prevKernel.dwHighDateTime;
        prevUserTime.LowPart = prevUser.dwLowDateTime;
        prevUserTime.HighPart = prevUser.dwHighDateTime;
        
        ULONGLONG idleDelta = idleTime.QuadPart - prevIdleTime.QuadPart;
        ULONGLONG kernelDelta = kernelTime.QuadPart - prevKernelTime.QuadPart;
        ULONGLONG userDelta = userTime.QuadPart - prevUserTime.QuadPart;
        ULONGLONG totalDelta = kernelDelta + userDelta;
        
        double percent = 100.0 - (idleDelta * 100.0 / totalDelta);
        char buf[10];
        sprintf_s(buf, "%.1f", percent);
        return string(buf);
    }
    
    prevIdle = idle;
    prevKernel = kernel;
    prevUser = user;
    return "0.0";
}

string getRAMusage() {
    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(mem);
    GlobalMemoryStatusEx(&mem);
    
    double total = (double)mem.ullTotalPhys / (1024*1024*1024);
    double free = (double)mem.ullAvailPhys / (1024*1024*1024);
    double used = total - free;
    double percent = (used / total) * 100.0;
    
    char buf[10];
    sprintf_s(buf, "%.1f", percent);
    return string(buf);
}

int main() {
    cout << "=== CLIENT ISHLEYAR ===\n";
    cout << "Servere maglumat iberilyar...\n\n";
    
    while (true) {
        WSADATA wsa;
        WSAStartup(MAKEWORD(2, 2), &wsa);
        
        SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_port = htons(8888);
        server.sin_addr.s_addr = inet_addr("127.0.0.1");
        
        string name = getComputerName();
        string ip = getLocalIP();
        string cpu = getCPUusage();
        string ram = getRAMusage();
        
        string data = name + "|" + cpu + "|" + ram + "|" + ip;
        
        if (connect(sock, (sockaddr*)&server, sizeof(server)) == 0) {
            send(sock, data.c_str(), data.length(), 0);
            char response[256] = {0};
            recv(sock, response, 256, 0);
            cout << "[" << name << "] CPU:" << cpu << "% RAM:" << ram << "% => " << response << endl;
        } else {
            cout << "❌ Serwere birikip bolmady!\n";
        }
        
        closesocket(sock);
        WSACleanup();
        Sleep(5000);
    }
    
    return 0;
}