#include <iostream>
#include "table.h"
#include "predictor.h"
#include "parameter.h"

int main() {
    // Years will not be included because we will add
    // an offset of 1872 to the index
    std::vector<std::vector<double>> weather_table = create_table("./model/data.txt");

    std::vector<double> years;
    for (double index = 1872; index <= 2025; index++) {
        years.push_back(index);
    }

    enum class Period {
        JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC,
        ANNUAL, WNTR, SPRG, SMMR, FALL, FIRST, SECOND
    };

    std::vector<double> test_column = get_column(weather_table, static_cast<int>(Period::ANNUAL));
    LinearRegression annual = identify_parameters(years, test_column);
    annual.info();
    std::cout << std::to_string(annual.predict(2026)) << std::endl;

    return 0;
}