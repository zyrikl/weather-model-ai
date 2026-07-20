#pragma once

#include <fstream>
#include <vector>

std::vector<std::vector<double>> create_table(std::string filename);
std::vector<double> get_column(std::vector<std::vector<double>> entry_table, int index);