#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

struct employee {
    int    num;
    char   name[10];
    double hours;
};

void runAndWait(const std::string& cmdLine) {
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    std::string cmd = cmdLine;
    BOOL ok = CreateProcessA(
        NULL,
        &cmd[0],
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    );

    if (!ok) {
        std::cerr << "CreateProcess failed: " << GetLastError() << "\n";
        return;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

int main() {
    std::string binFile;
    int count;
    std::cout << "Binary file name : "; std::cin >> binFile;
    std::cout << "Number of records: "; std::cin >> count;

    std::string creatorCmd = "Creator.exe " + binFile + " " + std::to_string(count);
    runAndWait(creatorCmd);

    std::cout << "\n--- Binary file contents ---\n";
    std::ifstream fin(binFile, std::ios::binary);
    if (!fin) {
        std::cerr << "Cannot open " << binFile << "\n";
        return 1;
    }
    employee emp;
    std::cout << "Num  Name       Hours\n";
    while (fin.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        std::cout << emp.num << "  " << emp.name << "  " << emp.hours << "\n";
    }
    fin.close();

    std::string reportFile;
    double rate;
    std::cout << "\nReport file name : "; std::cin >> reportFile;
    std::cout << "Hourly rate      : "; std::cin >> rate;

    std::string reporterCmd = "Reporter.exe " + binFile + " " + reportFile
        + " " + std::to_string(rate);
    runAndWait(reporterCmd);

    std::cout << "\n--- Report ---\n";
    std::ifstream rep(reportFile);
    if (!rep) {
        std::cerr << "Cannot open " << reportFile << "\n";
        return 1;
    }
    std::string line;
    while (std::getline(rep, line)) {
        std::cout << line << "\n";
    }

    return 0;
} 