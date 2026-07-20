#include "table.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

std::vector<std::vector<double>> create_table(std::string filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Impossible. There's no data file!" << std::endl;
        std::exit(1);
    }

    std::vector<std::vector<double>> table;
    std::string line;

    while (std::getline(file, line)) {
        std::vector<double> entry;
        std::string token;
        std::stringstream ss(line);
        
        while (std::getline(ss, token, ' ')) {
            entry.push_back(std::stod(token));
        }
        
        table.push_back(entry);
    }

    file.close();
    return table;
}

std::vector<double> get_column(std::vector<std::vector<double>> entry_table, int index) {
    std::vector<double> column;

    for (std::vector<double> row : entry_table) {
        column.push_back(row[index]);
    }

    return column;
}