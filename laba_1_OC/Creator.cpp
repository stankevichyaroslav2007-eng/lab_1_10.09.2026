#include <windows.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

struct employee {
    int    num;
    char   name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: Creator <filename> <count>\n";
        return 1;
    }

    const char* filename = argv[1];
    int count = std::atoi(argv[2]);

    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot create file: " << filename << "\n";
        return 1;
    }

    for (int i = 0; i < count; ++i) {
        employee emp;
        std::cout << "Employee " << (i + 1) << ":\n";
        std::cout << "  Number : "; std::cin >> emp.num;
        std::cout << "  Name   : "; std::cin >> emp.name;
        std::cout << "  Hours  : "; std::cin >> emp.hours;

        file.write(reinterpret_cast<const char*>(&emp), sizeof(employee));
    }

    file.close();
    std::cout << "Binary file \"" << filename << "\" created.\n";
    return 0;
}