#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

struct Computer {
    string name;
    string ip;
    string cpu_usage;
    string ram_usage;
    string status;
    string last_time;
    int is_critical;
};

void saveToCSV(vector<Computer>& comps) {
    ofstream file("computers.csv");
    file << "Name,IP,CPU%,RAM%,Status,LastUpdate,Priority\n";
    for (auto& c : comps) {
        file << c.name << "," << c.ip << "," << c.cpu_usage << "," << c.ram_usage << ","
             << c.status << "," << c.last_time << "," << (c.is_critical ? "CRITICAL" : "NORMAL") << "\n";
    }
    file.close();
}

string checkStatus(string cpu, string ram) {
    float cpu_val = stof(cpu);
    float ram_val = stof(ram);
    if (cpu_val > 80 || ram_val > 85) return "CRITICAL";
    else if (cpu_val > 60 || ram_val > 70) return "WARNING";
    else return "NORMAL";
}

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    
    SOCKET srv = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    addr.sin_addr.s_addr = INADDR_ANY;
    
    bind(srv, (sockaddr*)&addr, sizeof(addr));
    listen(srv, 5);
    
    cout << "================================\n";
    cout << "  SYSTEM MONITOR SERVER\n";
    cout << "  Port: 8888\n";
    cout << "================================\n";
    cout << "Server is working...\n\n";
    
    vector<Computer> computers;
    
    while (true) {
        sockaddr_in client;
        int clen = sizeof(client);
        SOCKET cli = accept(srv, (sockaddr*)&client, &clen);
        
        char buffer[512] = {0};
        recv(cli, buffer, 512, 0);
        
        string data(buffer);
        string name, cpu, ram, ip;
        vector<string> parts;
        size_t pos = 0, prev = 0;
        
        while ((pos = data.find('|', prev)) != string::npos) {
            parts.push_back(data.substr(prev, pos - prev));
            prev = pos + 1;
        }
        parts.push_back(data.substr(prev));
        
        if (parts.size() >= 4) {
            name = parts[0];
            cpu = parts[1];
            ram = parts[2];
            ip = parts[3];
        }
        
        time_t now = time(0);
        string time_str = ctime(&now);
        time_str.pop_back();
        
        string status = checkStatus(cpu, ram);
        int critical = (status == "CRITICAL") ? 1 : 0;
        
        bool found = false;
        for (auto& comp : computers) {
            if (comp.name == name) {
                comp.cpu_usage = cpu;
                comp.ram_usage = ram;
                comp.status = status;
                comp.last_time = time_str;
                comp.is_critical = critical;
                found = true;
                break;
            }
        }
        
        if (!found) {
            Computer comp;
            comp.name = name;
            comp.ip = ip;
            comp.cpu_usage = cpu;
            comp.ram_usage = ram;
            comp.status = status;
            comp.last_time = time_str;
            comp.is_critical = critical;
            computers.push_back(comp);
        }
        
        sort(computers.begin(), computers.end(), [](Computer& a, Computer& b) {
            return a.is_critical > b.is_critical;
        });
        
        saveToCSV(computers);
        
        system("cls");
        cout << "=== SYSTEM MONITOR SERVER ===\n";
        cout << "Aktiw kompýuterler: " << computers.size() << "\n";
        cout << "=============================\n\n";
        
        for (auto& comp : computers) {
            cout << "[" << (comp.is_critical ? "⚠️ KRITIK" : "✅ NORMAL") << "] ";
            cout << comp.name << " (" << comp.ip << ")\n";
            cout << "   CPU: " << comp.cpu_usage << "%  RAM: " << comp.ram_usage << "%\n";
            cout << "   Status: " << comp.status << "\n\n";
        }
        
        string response = "RECEIVED:" + status;
        send(cli, response.c_str(), response.length(), 0);
        closesocket(cli);
    }
    
    closesocket(srv);
    WSACleanup();
    return 0;
}