#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "predictor.h"

int main() {
    std::ifstream file("./model/data.txt");

    if (!file.is_open()) {
        std::cerr << "Impossible. There's no data file!" << std::endl;
        return 1;
    }

    // Years will not be included because we will add
    // an offset of 1872 to the index
    std::vector<std::vector<double>> weather_table;
    std::vector<double> years;
    double index = 1872;
    std::string line;

    while (std::getline(file, line)) {
        std::vector<double> weather_entry;
        std::string token;
        std::stringstream ss(line);
        
        while (std::getline(ss, token, ' ')) {
            weather_entry.push_back(std::stod(token));
        }
        
        weather_table.push_back(weather_entry);
        years.push_back(index);
        index++;
    }

    enum class Period {
        JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC,
        ANNUAL, WNTR, SPRG, SMMR, FALL, FIRST, SECOND
    };

    // Getting annual temps
    std::vector<double> test_column = get_column(weather_table, static_cast<int>(Period::ANNUAL));
    LinearRegression annual = calculate_lsrl(years, test_column);
    annual.info();
    std::cout << std::to_string(annual.predict(2026)) << std::endl;

    file.close();
    return 0;
}