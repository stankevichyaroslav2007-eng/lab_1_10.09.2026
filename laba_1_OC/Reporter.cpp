#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>

struct employee {
    int    num;
    char   name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: Reporter <binfile> <reportfile> <rate>\n";
        return 1;
    }

    const char* binFile = argv[1];
    const char* reportFile = argv[2];
    double rate = std::atof(argv[3]);

    std::ifstream fin(binFile, std::ios::binary);
    if (!fin) {
        std::cerr << "Cannot open: " << binFile << "\n";
        return 1;
    }

    std::vector<employee> employees;
    employee emp;
    while (fin.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        employees.push_back(emp);
    }
    fin.close();

    std::sort(employees.begin(), employees.end(),
        [](const employee& a, const employee& b) {
            return std::strcmp(a.name, b.name) < 0;
        });

    std::ofstream fout(reportFile);
    if (!fout) {
        std::cerr << "Cannot create: " << reportFile << "\n";
        return 1;
    }

    fout << "Report for file \"" << binFile << "\"\n";
    fout << "----------------------------------------------\n";
    fout << "Num  Name       Hours    Salary\n";
    fout << "----------------------------------------------\n";

    for (const auto& e : employees) {
        double salary = e.hours * rate;
        fout.width(4);  fout << e.num << " ";
        fout.width(10); fout << e.name << " ";
        fout.width(8);  fout << e.hours << " ";
        fout.width(10); fout << salary << "\n";
    }

    fout.close();
    std::cout << "Report written to \"" << reportFile << "\"\n";
    return 0;
}